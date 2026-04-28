// Filename: pmu.h
// Author: Everaldo Pereira Gomes

#ifndef PMU_H
#define PMU_H

#include <stdint.h>

#define DEBUG 0

#define ASM __asm__ volatile
#define MAX_INT 4294967295U

#define BOARD_CORE_0_PMU_IRQ 48
#define BOARD_CORE_1_PMU_IRQ 49
#define BOARD_CORE_2_PMU_IRQ 50
#define BOARD_CORE_3_PMU_IRQ 51

#define PRINT_REG(REG)                           \
    {                                            \
        uint32_t value;                          \
        ASM("mrs %0, " #REG : "=r"(value)::);    \
        printk("Reg %s val: %u\n", #REG, value); \
    }

void PMU_config();
void PMU_config_counter(const uint8_t counter, uint32_t r_budget,
                        uint32_t w_budget, const uint8_t event,
                        const uint8_t task_num);
void PMU_start_counter(const uint8_t counter);
void PMU_stop_counter(const uint8_t counter);
uint32_t PMU_get_counter_value(const uint8_t counter);
void PMU_reset_counter(const uint8_t counter);
void PMU_reset_all_counters();
void PMU_print_all_counters(const char* msg);

long int PMU_secure_monitor();

void PMU_interrupt_handler();
void PMU_general();

enum PMU_events {
    SW_INCR = 0x00,
    L1I_REFILL = 0x01,
    L1I_TLB_REFILL = 0x02,
    L1D_REFILL = 0x03,
    L1D_ACCESS = 0x04,
    L1D_TLB_REFILL = 0x05,
    INSTRUCTIONS_ARCHITECTURALLY_EXECUTED_L = 0x06,
    INSTRUCTIONS_ARCHITECTURALLY_EXECUTED_S = 0x07,
    INSTRUCTIONS_ARCHITECTURALLY_EXECUTED = 0x08,
    EXCEPTION_TAKEN = 0x09,
    EXCEPTION_RETURN = 0x0A,
    CHANGE_TO_CONTEXT_ID_RETIRED = 0x0B,
    BRANCHES_ARCHITECTURALLY_EXECUTED = 0x0C,
    IMMEDIATE_BRANCH = 0x0D,
    RETURN_EXECUTED = 0x0E,
    UNALIGNED_LOAD_STORE = 0x0F,
    MISPREDICTED_BRANCH = 0x10,
    CPU_CYCLE = 0x11,
    PREDICTABLE_BRANCH_EXECUTED = 0x12,
    DATA_MEMORY_ACCESS = 0x13,
    L1I_ACCESS = 0x14,
    L1D_WRITEBACK = 0x15,
    L2D_ACCESS = 0x16,
    L2D_REFILL = 0x17,
    L2D_WRITEBACK = 0x18,
    BUS_ACCESS = 0x19,
    LOCAL_MEMORY_ERROR = 0x1A,
    INSTRUCTION_SPECULATIVELY_EXECUTED = 0x1B,
    TTBR_WRITE_RETIRED = 0x1C,
    BUS_CYCLE = 0x1D,
    CHAIN = 0x1E,
    LL_CACHE_MISS_RD = 0x37,
    L1D_CACHE_LD = 0x40,
    L1D_CACHE_ST = 0x41,
    L1D_CACHE_REFILL_LD = 0x42,
    L1D_CACHE_REFILL_ST = 0x43,
    L1D_CACHE_WB_VICTIM = 0x46,
    L1D_CACHE_WB_CLEAN = 0x47,
    L1D_CACHE_INVAL = 0x48,
    L1D_TLB_REFILL_LD = 0x4C,
    L1D_TLB_REFILL_ST = 0x4D,
    L2D_CACHE_LD = 0x50,
    L2D_CACHE_ST = 0x51,
    L2D_CACHE_REFILL_LD = 0x52,
    L2D_CACHE_REFILL_ST = 0x53,
    L2D_CACHE_WB_VICTIM = 0x56,
    L2D_CACHE_WB_CLEAN = 0x57,
    L2D_CACHE_INVAL = 0x58,
    BUS_ACCESS_LD = 0x60,
    BUS_ACCESS_ST = 0x61,
    BUS_ACCESS_SHARED = 0x62,
    BUS_ACCESS_NOT_SHARED = 0x63,
    BUS_ACCESS_NORMAL = 0x64,
    BUS_ACCESS_PERIPH = 0x65,
    MEM_ACCESS_LD = 0x66,
    MEM_ACCESS_ST = 0x67,
    UNALIGNED_LD_SPEC = 0x68,
    UNALIGNED_ST_SPEC = 0x69,
    UNALIGNED_LDST_SPEC = 0x6A,
    LDREX_SPEC = 0x6C,
    STREX_PASS_SPEC = 0x6D,
    STREX_FAIL_SPEC = 0x6E,
    LD_SPEC = 0x70,
    ST_SPEC = 0x71,
    LDST_SPEC = 0x72,
    DP_SPEC = 0x73,
    ASE_SPEC = 0x74,
    VFP_SPEC = 0x75,
    PC_WRITE_SPEC = 0x76,
    CRYPTO_SPEC = 0x77,
    BR_IMMED_SPEC = 0x78,
    BR_RETURN_SPEC = 0x79,
    BR_INDIRECT_SPEC = 0x7A,
    ISB_SPEC = 0x7C,
    DSB_SPEC = 0x7D,
    DMB_SPEC = 0x7E,
    EXC_UNDEF = 0x81,
    EXC_SVC = 0x82,
    EXC_PABORT = 0x83,
    EXC_DABORT = 0x84,
    EXC_IRQ = 0x86,
    EXC_FIQ = 0x87,
    EXC_SMC = 0x88,
    EXC_HVC = 0x8A,
    EXC_TRAP_PABORT = 0x8B,
    EXC_TRAP_DABORT = 0x8C,
    EXC_TRAP_OTHER = 0x8D,
    EXC_TRAP_IRQ = 0x8E,
    EXC_TRAP_FIQ = 0x8F,
    RC_LD_SPEC = 0x90,
    RC_ST_SPEC = 0x91,
};

#endif
