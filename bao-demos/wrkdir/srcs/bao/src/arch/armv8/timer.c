#include <bao.h>
#include <arch/sysregs.h>
#include <arch/generic_timer.h>
#include <interrupts.h>
#include <cpu.h>
#include <arch/detector.h>
#include <arch/fp_context.h>

#define MRS(v, r) __asm__ volatile("mrs %0, " #r : "=r" (v))
#define MSR(r, v) __asm__ volatile("msr " #r ", %0" : : "r" (v))
#define ISB()     __asm__ volatile("isb")

#define TIMMER_PERIOD 200000 // 200ms 
#define CNTHP_IRQ 26 // ID do timer fisico EL2

//eventos pmu
#define PMU_EVT_INST_RETIRED     0x08
#define PMU_EVT_L2D_CACHE_REFILL 0x17
#define PMU_EVT_L2D_CACHE        0x16
#define PMU_EVT_BR_MIS_PRED      0x10

//mascara para habilitar o contador de ciclos e os contadores de eventos
#define PMU_ENABLE_ALL  ((1UL << 31) | (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3))

volatile pmu_data_t g_pmu_data[PMU_MAX_CPUS];

// contexto FP por CPU — protege os registradores NEON/FP das VMs
// durante a execucao do detector (que usa float)
static fp_context_t s_fp_ctx[PMU_MAX_CPUS];

// funcao para transformar microsegundos em ticks do timer
static uint64_t us_to_ticks(uint64_t us) {
    uint64_t freq;
    MRS(freq, cntfrq_el0); // sysreg_cntfrq_el0_read
    return (us * freq) / 1000000;
}

static void pmu_init_registers(void) {
    uint64_t val;

    //desabilita o PMU globalmente (PMCR.E = 0)
    MRS(val, pmcr_el0);
    val &= ~(1 << 0);
    MSR(pmcr_el0, val);

    //desabilita explicitamente os contadores individuais
    val = PMU_ENABLE_ALL;
    MSR(pmcntenclr_el0, val); 

    //configura o filtro de ciclos — exclui EL2 (bit 27 = NSH)
    //para contar apenas ciclos das VMs (EL1/EL0), nao do hypervisor
    #define PMU_FILTER_EXCLUDE_EL2  (1UL << 27)
    __asm__ volatile("msr pmccfiltr_el0, %0" :: "r" (PMU_FILTER_EXCLUDE_EL2));

    //configura contadores usando registradores DIRETOS (evita bugs do pmselr indireto)

    //Contador 0: branch misses — exclui EL2
    __asm__ volatile("msr pmevtyper0_el0, %0" :: "r" ((uint64_t)(PMU_EVT_BR_MIS_PRED | PMU_FILTER_EXCLUDE_EL2)));

    //Contador 1: L2 cache misses (LLC no RPi4) — exclui EL2
    __asm__ volatile("msr pmevtyper1_el0, %0" :: "r" ((uint64_t)(PMU_EVT_L2D_CACHE_REFILL | PMU_FILTER_EXCLUDE_EL2)));

    //Contador 2: L2 cache access (total de acessos ao LLC) — exclui EL2
    __asm__ volatile("msr pmevtyper2_el0, %0" :: "r" ((uint64_t)(PMU_EVT_L2D_CACHE | PMU_FILTER_EXCLUDE_EL2)));

    //Contador 3: instrucoes — exclui EL2
    __asm__ volatile("msr pmevtyper3_el0, %0" :: "r" ((uint64_t)(PMU_EVT_INST_RETIRED | PMU_FILTER_EXCLUDE_EL2)));

    ISB();

    //habilita os contadores
    val = PMU_ENABLE_ALL;
    MSR(pmcntenset_el0, val);

    //reset e enable global
    MRS(val, pmcr_el0);
    val |= (1 << 0) | (1 << 1) | (1 << 2); // Enable, Reset Counters, Reset Cycle
    MSR(pmcr_el0, val);
}

//leitura dos dados da pmu usando registradores DIRETOS
static inline void pmu_collect_data(void) {
    uint64_t val;

    cpuid_t id = cpu()->id;
    if (id >= PMU_MAX_CPUS) return;

    //cpu cycles
    MRS(val, pmccntr_el0);
    g_pmu_data[id].cpu_cycles = val;

    //branch misses (Contador 0) — acesso direto
    __asm__ volatile("mrs %0, pmevcntr0_el0" : "=r" (val));
    g_pmu_data[id].branch_misses = val;

    //cache misses (Contador 1) — acesso direto
    __asm__ volatile("mrs %0, pmevcntr1_el0" : "=r" (val));
    g_pmu_data[id].cache_misses = val;

    //L2 cache access (Contador 2) — acesso direto
    __asm__ volatile("mrs %0, pmevcntr2_el0" : "=r" (val));
    g_pmu_data[id].l2_cache_access = val;

    //instrucoes (Contador 3) — acesso direto
    __asm__ volatile("mrs %0, pmevcntr3_el0" : "=r" (val));
    g_pmu_data[id].instructions = val;

    //timestamp
    MRS(val, cntpct_el0); 
    g_pmu_data[id].timestamp = val;

    // reinicializa os registradores para a proxima coleta
    // (pmu_init_registers() ja faz reset completo e enable)
    pmu_init_registers();
}

void timer_handler(irqid_t irq_id) {
    // desabilita o timer temporariamente
    uint32_t ctl;
    MRS(ctl, cnthp_ctl_el2);
    ctl |= GENERIC_TIMER_IMASK; 
    MSR(cnthp_ctl_el2, ctl);

    cpuid_t id = cpu()->id;

    // Cada core coleta e processa seus proprios dados de forma independente.
    //
    // CORRECAO: a versao anterior centralizava a inferencia no core 1, que lia
    // os dados do core 2 sem garantia de sincronizacao (dado potencialmente
    // desatualizado do intervalo anterior). Alem disso, o core 0 nunca era
    // processado. Esta versao elimina ambos os problemas:
    //   - Sem sincronizacao entre cores (sem risco de dados obsoletos).
    //   - Todos os PMU_MAX_CPUS cores sao monitorados.
    //   - Espelha exatamente o pipeline Python: uma linha (um core) por vez.
    if (id < PMU_MAX_CPUS) {
        // Passo 1: coleta os dados da PMU deste core e reseta os contadores,
        // garantindo que cada amostra represente exatamente um intervalo de 200ms.
        pmu_collect_data();

        // Passo 2: executa a inferencia para este core.
        // O detector agora possui arrays PER-CPU (s_ring[cpu_id]),
        // entao nao e mais necessario nenhum spinlock. Execucao 100% paralela.
        fp_context_save(&s_fp_ctx[id]);

        pmu_sample_t s = {
            .cpu_cycles      = g_pmu_data[id].cpu_cycles,
            .instructions    = g_pmu_data[id].instructions,
            .cache_misses    = g_pmu_data[id].cache_misses,
            .branch_misses   = g_pmu_data[id].branch_misses,
            .l2_cache_access = g_pmu_data[id].l2_cache_access,
        };

        det_output_t out = detector_process_sample(id, &s);

        // armazena o resultado do detector para este core
        g_pmu_data[id].det_status          = (uint64_t)out.status;
        g_pmu_data[id].det_probability_pct = (uint64_t)(out.probability * 100);

        fp_context_restore(&s_fp_ctx[id]);
    }

    // reprograma o proximo disparo
    uint64_t current_cnt;
    MRS(current_cnt, cntpct_el0);
    MSR(cnthp_cval_el2, current_cnt + us_to_ticks(TIMMER_PERIOD));

    // reabilita o timer
    ctl &= ~GENERIC_TIMER_IMASK;
    MSR(cnthp_ctl_el2, ctl);

    // limpa a gic
    interrupts_arch_clear(irq_id);
}

void timer_arch_init(void) {
    // inicializa os registradores da PMU
    pmu_init_registers();

    // inicializa o detector de interferencia (zera ring buffers internos)
    detector_init();

    // habilita o timer fisico EL2
    uint32_t ctl = GENERIC_TIMER_ENABLE;
    MSR(cnthp_ctl_el2, ctl);

    // define o primeiro disparo
    uint64_t current_cnt;
    MRS(current_cnt, cntpct_el0);
    MSR(cnthp_cval_el2, current_cnt + us_to_ticks(TIMMER_PERIOD));

    interrupts_reserve(CNTHP_IRQ, timer_handler);
    interrupts_arch_enable(CNTHP_IRQ, true);
}