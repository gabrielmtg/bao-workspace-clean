/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef GENERIC_TIMER_H
#define GENERIC_TIMER_H

#include <bao.h>

// definitions for timer.c

#define GENERIC_TIMER_ENABLE    (0x1)   //bit 0
#define GENERIC_TIMER_IMASK     (0x2)   //bit 1
#define GENERIC_TIMER_ISTATUS   (0x4)   //bit 2

#define GENERIC_TIMER_CNTCTL_CNTCR_EN   (0x1)

#define PMU_MAX_CPUS 4

// global variables to store collected PMU data, to be sent to the VM
typedef struct {
    uint64_t timestamp;
    uint64_t cpu_cycles;
    uint64_t instructions;
    uint64_t branch_misses;
    uint64_t cache_misses;
    uint64_t l2_cache_access;
    uint64_t det_status;          // 0=WARMUP, 1=BENIGN, 2=ATTACK
    uint64_t det_probability_pct; // probability * 100 (integer)
} pmu_data_t;

// global array to store PMU data from each CPU
extern volatile pmu_data_t g_pmu_data[PMU_MAX_CPUS];

void timer_arch_init(void);

struct generic_timer_cntctrl  {
    uint32_t CNTCR;
    uint32_t CNTSR;
    uint64_t CNTCV;
    uint8_t res0[0x20-0x10];
    uint32_t CNTDIF0;
    uint32_t CNTDIF[0];
    uint8_t res1[0xfd0-0x24];
    uint32_t CounterID[12];
} __attribute__((packed, aligned(PAGE_SIZE)));

#endif /* GENERIC_TIMER_H */
