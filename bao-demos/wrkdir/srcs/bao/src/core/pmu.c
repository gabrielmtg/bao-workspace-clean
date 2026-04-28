// Filename: pmu.c
// Author: Everaldo Pereira Gomes
//         João Almeida (https://github.com/nynepebbles/)

#include <pmu.h>
#include <regulator.h>

#include <cpu.h>
#include <vm.h>


static inline void PMU_interrupt_enable(const uint8_t cpu_id)
{
    if (cpu_id == 0)
        interrupts_arch_enable(BOARD_CORE_0_PMU_IRQ, true);
    else if (cpu_id == 1)
        interrupts_arch_enable(BOARD_CORE_1_PMU_IRQ, true);
    else if (cpu_id == 2)
        interrupts_arch_enable(BOARD_CORE_2_PMU_IRQ, true);
    else if (cpu_id == 3)
        interrupts_arch_enable(BOARD_CORE_3_PMU_IRQ, true);
}

static inline void PMU_interrupt_disable(const uint8_t cpu_id)
{
    if (cpu_id == 0)
        interrupts_arch_enable(BOARD_CORE_0_PMU_IRQ, false);
    else if (cpu_id == 1)
        interrupts_arch_enable(BOARD_CORE_1_PMU_IRQ, false);
    else if (cpu_id == 2)
        interrupts_arch_enable(BOARD_CORE_2_PMU_IRQ, false);
    else if (cpu_id == 3)
        interrupts_arch_enable(BOARD_CORE_3_PMU_IRQ, false);
}

void PMU_interrupt_handler()
{
    uint32_t overflow_reg_val = 0;
    ASM("mrs %0, PMOVSSET_EL0" : "=r"(overflow_reg_val)::);

    PMU_interrupt_disable(cpu()->id);

    if (overflow_reg_val & (1 << 0)) {
        vcpu_inject_irq(cpu()->vcpu, PMU_0_OVERFLOWED_ID);
    } else if (overflow_reg_val & (1 << 1)) {
        vcpu_inject_irq(cpu()->vcpu, PMU_1_OVERFLOWED_ID);
    } else {
        PRINT("\t\tINVALID PMU_interrupt_handler call. undefined.");
        // vcpu_inject_irq(cpu()->vcpu, GUEST_SUSPEND_TASK_1_BUDGET_ID);
    }
}

void PMU_config()
{
    ASM("msr pmuserenr_el0, %0" ::"r"(1 << 0));
    ASM("msr PMCR_EL0, %0" ::"r"((1 << 0) | (1 << 1) | (1 << 2) | (1 << 6)));
    ASM("msr PMINTENSET_EL1, %0" ::"r"(0x1F << 0));
    PMU_interrupt_enable(cpu()->id);
}

void PMU_config_counter(const uint8_t counter_pair, uint32_t r_budget,
                        uint32_t w_budget, const uint8_t event,
                        const uint8_t t_num)
{
    PMU_config();

    reg_conf[cpu()->id].vm.defined_pmu_read_val = r_budget;
    reg_conf[cpu()->id].vm.defined_pmu_write_val = w_budget;

    r_budget = (uint32_t)MAX_INT - r_budget;
    w_budget = (uint32_t)MAX_INT - w_budget;

    if (true) {
        ASM("msr pmevcntr0_el0, %0" ::"r"(0) :);
        ASM("msr pmevtyper0_el0, %0" ::"r"(MEM_ACCESS_LD));
        ASM("msr pmintenset_el1, %0" ::"r"(1 << 0));
        ASM("msr pmevcntr0_el0,  %0" ::"r"(r_budget));

        ASM("msr pmevcntr1_el0, %0" ::"r"(0) :);
        ASM("msr pmevtyper1_el0, %0" ::"r"(MEM_ACCESS_ST));
        ASM("msr pmintenset_el1, %0" ::"r"(1 << 1));
        ASM("msr pmevcntr1_el0,  %0" ::"r"(w_budget));
    }

    if (true) {
        ASM("msr pmevcntr2_el0, %0" ::"r"(0) :);
        ASM("msr pmevtyper2_el0, %0" ::"r"(CPU_CYCLE));
        // ASM("msr pmintenset_el1, %0" ::"r"(1 << 2));
        ASM("msr pmevcntr2_el0,  %0" ::"r"(0));

        ASM("msr pmevcntr3_el0, %0" ::"r"(0) :);
        ASM("msr pmevtyper3_el0, %0" ::"r"(
            INSTRUCTIONS_ARCHITECTURALLY_EXECUTED));
        // ASM("msr pmintenset_el1, %0" ::"r"(1 << 3));
        ASM("msr pmevcntr3_el0,  %0" ::"r"(0));
    }

    if (true) {
        ASM("msr pmevcntr4_el0, %0" ::"r"(0) :);
        ASM("msr pmevtyper4_el0, %0" ::"r"(L1D_REFILL));
        // ASM("msr pmintenset_el1, %0" ::"r"(1 << 4));
        ASM("msr pmevcntr4_el0,  %0" ::"r"(0));

        ASM("msr pmevcntr5_el0, %0" ::"r"(0) :);
        ASM("msr pmevtyper5_el0, %0" ::"r"(MISPREDICTED_BRANCH));
        // ASM("msr pmintenset_el1, %0" ::"r"(1 << 5));
        ASM("msr pmevcntr5_el0,  %0" ::"r"(0));
    }
}

void PMU_start_counter(const uint8_t counter)
{
    for (uint8_t i = 0; i < PMU_COUNT; i++) {
        ASM("msr pmcntenset_el0, %0" ::"r"((1 << (counter + i))));
    }
}

void PMU_stop_counter(const uint8_t counter)  // Parameter is no longer needed
{
    // Stop all 6 counters at once
    ASM("msr pmcntenclr_el0, %0" ::"r"(0b111111));

    // ONLY clear interrupts/overflows for the ones that have them (0 & 1)
    ASM("msr pmintenclr_el1, %0" ::"r"(0b11));
    ASM("msr pmovsclr_el0, %0" ::"r"(0b11));
}

uint32_t PMU_get_counter_value(const uint8_t counter)
{
    uint32_t v = 0;

    if (counter == 0)
        ASM("mrs %0, pmevcntr0_el0" : "=r"(v)::);
    else if (counter == 1)
        ASM("mrs %0, pmevcntr1_el0" : "=r"(v)::);
    else if (counter == 2)
        ASM("mrs %0, pmevcntr2_el0" : "=r"(v)::);
    else if (counter == 3)
        ASM("mrs %0, pmevcntr3_el0" : "=r"(v)::);
    else if (counter == 4)
        ASM("mrs %0, pmevcntr4_el0" : "=r"(v)::);
    else if (counter == 5)
        ASM("mrs %0, pmevcntr5_el0" : "=r"(v)::);

    return v;
}

void PMU_reset_counter(const uint8_t counter)
{
    if (counter == 0)
        ASM("msr pmevcntr0_el0, %0" ::"r"(0) :);
    else if (counter == 1)
        ASM("msr pmevcntr1_el0, %0" ::"r"(0) :);
    else if (counter == 2)
        ASM("msr pmevcntr2_el0, %0" ::"r"(0) :);
    else if (counter == 3)
        ASM("msr pmevcntr3_el0, %0" ::"r"(0) :);
    else if (counter == 4)
        ASM("msr pmevcntr4_el0, %0" ::"r"(0) :);
    else if (counter == 5)
        ASM("msr pmevcntr5_el0, %0" ::"r"(0) :);
}

void PMU_reset_all_counters()
{
    ASM("msr pmevcntr0_el0, %0\n\t"
        "msr pmevcntr1_el0, %0\n\t"
        "msr pmevcntr2_el0, %0\n\t"
        "msr pmevcntr3_el0, %0\n\t"
        "msr pmevcntr4_el0, %0\n\t"
        "msr pmevcntr5_el0, %0\n\t" : : "r"(0) :);
}

void PMU_print_all_counters(const char* msg)
{
    uint32_t c0, c1, c2, c3, c4, c5;
    c0 = c1 = c2 = c3 = c4 = c5 = 0;

    ASM("mrs %0, pmevcntr0_el0\n\t"
        "mrs %1, pmevcntr1_el0\n\t"
        "mrs %2, pmevcntr2_el0\n\t"
        "mrs %3, pmevcntr3_el0\n\t"
        "mrs %4, pmevcntr4_el0\n\t"
        "mrs %5, pmevcntr5_el0\n\t" : "=r"(c0),
        "=r"(c1), "=r"(c2), "=r"(c3), "=r"(c4), "=r"(c5)::);

    PRINT("Counters: %s", msg);
    PRINT("C0: %u", c0);
    PRINT("C1: %u", c1);
    PRINT("C2: %u", c2);
    PRINT("C3: %u", c3);
    PRINT("C4: %u", c4);
    PRINT("C5: %u", c5);
}

long int PMU_secure_monitor(void)
{
    unsigned long c0, c1, c2, c3;
    // Stop all counters
    ASM("msr pmcntenclr_el0, %0" ::"r"(0b1111));
    //  Read counter values
    ASM("mrs %0, pmevcntr0_el0" : "=r"(c0));
    ASM("mrs %0, pmevcntr1_el0" : "=r"(c1));
    ASM("mrs %0, pmevcntr2_el0" : "=r"(c2));
    ASM("mrs %0, pmevcntr3_el0" : "=r"(c3));
    // Save counter values to VCPU registers
    vcpu_writereg(cpu()->vcpu, 1, c1);
    vcpu_writereg(cpu()->vcpu, 2, c2);
    vcpu_writereg(cpu()->vcpu, 3, c3);
    // Reset and restart counters
    ASM("msr pmevcntr0_el0, %0" ::"r"(0));
    ASM("msr pmevcntr1_el0, %0" ::"r"(0));
    ASM("msr pmevcntr2_el0, %0" ::"r"(0));
    ASM("msr pmevcntr3_el0, %0" ::"r"(0));
    ASM("msr pmcntenset_el0, %0" ::"r"(0b1111));
    return (long int)c0;
}