/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef HYPERCALL_H
#define HYPERCALL_H

#include <bao.h>
#include <arch/hypercall.h>

enum Hypercall_ID {
    HC_INVAL = 0,
    HC_IPC = 1,
    HC_PMU_CONFIG_COUNTER = 2,
    HC_PMU_START_COUNTER = 3,
    HC_PMU_STOP_COUNTER = 4,
    HC_REGULATOR_GET_MAX_BUDGET = 5,
    HC_REGULATOR_PERIODIC_TIMER_HANDLER = 6,
    HC_PMU_HANDLER = 7,
    HC_PMU_GET_COUNTER_VALUE = 9,
    HC_PMU_RESET_COUNTER = 10,
    HC_REGULATOR_CHECK_COUNTER = 11,
    HC_REGULATOR_BUDGET_DEPLETED = 12,
    HC_REGULATOR_CHECK_PERIOD = 13,
    HC_REGULATOR_PERIOD_EXPIRED = 14,
    HC_REGULATOR_GET_RAW_PMU_VALUES = 15,
    HC_REGULATOR_GET_TOTAL_USED_BUDGET = 16,
    HC_REGULATOR_GET_CURRENT_USED_BUDGET = 17,
    HC_REGULATOR_GET_NEW_BUDGET = 18,
    HC_SEC_MONITOR = 19 // Security monitor hypercall
};

enum {
    HC_E_SUCCESS = 0,
    HC_E_FAILURE = 1,
    HC_E_INVAL_ID = 2,
    HC_E_INVAL_ARGS = 3
};

typedef unsigned long (*hypercall_handler)(unsigned long arg0,
                                           unsigned long arg1,
                                           unsigned long arg2);

long int hypercall(unsigned long id);

#endif /* HYPERCALL_H */
