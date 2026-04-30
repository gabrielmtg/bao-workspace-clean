#ifndef GLOBALS_H
#define GLOBALS_H

#include "FreeRTOS.h"
#include "queue.h"

#define HC_SEC_MONITOR 19
#define SMCC64_FID_VND_HYP_SRVC 0x86000000 | 0x40000000
// #define HC_REGULATOR_GET_RAW_PMU_VALUES 15

// Event IDs for Initial Configuration (ARMv8)
#define ARMV8_EVENT_BR_MIS_PRED         0x10
#define ARMV8_EVENT_L1D_CACHE_REFILL    0x03
#define ARMV8_EVENT_INST_RETIRED        0x08
#define ARMV8_EVENT_CPU_CYCLES          0x11

#define OTHER_TASK_PRIORITY 1
#define TASK_STACK_SIZE 1024

typedef struct {
  unsigned long timestamp;
  unsigned long branch_misses;
  unsigned long cache_misses;
  unsigned long instructions;
  unsigned long cpu_cycles;
  unsigned long l2_cache_access;
  unsigned long det_status;          // 0=WARMUP, 1=BENIGN, 2=ATTACK
  unsigned long det_probability_pct; // probabilidade * 100 (inteiro)
} PMU_data;

typedef struct {
    PMU_data data;
    float output;
    uint64_t core_id;
    uint32_t label;     // scenario label (regulation.h)
    uint32_t bench_id;  // benchmark/attack ID lido via IPC
} FANN_sample;

// Queue for communication between monitoring task and FANN task
extern QueueHandle_t xPmuQueue;
// Global variable for attack control
extern volatile float g_label_atual;

// Helper function to read the ARM timer counter
static inline uint64_t get_hardware_timer_count(void) {
    uint64_t val;
    asm volatile("isb \n mrs %0, cntvct_el0" : "=r" (val));
    return val;
}

// Helper function to read the ARM timer frequency
static inline uint64_t get_hardware_timer_freq(void) {
    uint64_t freq;
    asm volatile("mrs %0, cntfrq_el0" : "=r" (freq));
    return freq;
}

#endif