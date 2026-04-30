#ifndef GLOBALS_H
#define GLOBALS_H

#include "FreeRTOS.h"
#include "queue.h"

#define HC_SEC_MONITOR 19
#define SMCC64_FID_VND_HYP_SRVC 0x86000000 | 0x40000000

#define OTHER_TASK_PRIORITY 1
#define TASK_STACK_SIZE 4096

// IPC shared memory (Channel 2: VM0 <-> VM2)
#define IPC_BASE_ADDR 0x70000000

typedef struct {
    volatile uint32_t signal_ready;   // VM2 -> VM0
    volatile uint32_t resume;         // VM0 -> VM2
    volatile uint32_t current_label;  // VM2 -> VM0: benchmark ID
} IPC_Channel;

// Benchmark labels
#define LABEL_NONE       0
#define LABEL_BANDWIDTH  1
#define LABEL_DISPARITY  2
#define LABEL_FFT        3
#define LABEL_QSORT      4
#define LABEL_DIJKSTRA   5
#define LABEL_SHA        6
#define LABEL_SORTING    7

#define NUM_BENCHMARKS   7

// Simple PRNG (Linear Congruential Generator) for random benchmark selection
static uint32_t _prng_state = 0;

static inline void prng_seed_from_timer(void) {
    uint64_t val;
    asm volatile("isb \n mrs %0, cntvct_el0" : "=r" (val));
    _prng_state = (uint32_t)(val ^ (val >> 32));
    if (_prng_state == 0) _prng_state = 1;
}

static inline uint32_t prng_range(uint32_t min, uint32_t max) {
    _prng_state = _prng_state * 1664525u + 1013904223u;
    return min + (_prng_state % (max - min + 1));
}

// Timing
#define BENCHMARK_DURATION_MS  (10 * 60 * 1000)  // 10 minutes
#define SYNC_INTERVAL_MS       (15 * 1000)        // 15 seconds

typedef struct {
  unsigned long timestamp;
  unsigned long branch_misses;
  unsigned long cache_misses;
  unsigned long instructions;
  unsigned long cpu_cycles;
} PMU_data;

typedef struct {
    PMU_data data;
    float output;
} FANN_sample;

extern QueueHandle_t xPmuQueue;
extern volatile float g_label_atual;

static inline uint64_t get_hardware_timer_count(void) {
    uint64_t val;
    asm volatile("isb \n mrs %0, cntvct_el0" : "=r" (val));
    return val;
}

static inline uint64_t get_hardware_timer_freq(void) {
    uint64_t freq;
    asm volatile("mrs %0, cntfrq_el0" : "=r" (freq));
    return freq;
}

#endif