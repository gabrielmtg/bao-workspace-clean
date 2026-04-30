#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "tasks_project.h"
#include "queue.h"

#include "../inc/globals.h"

#include "pmu_monitor.h"


//==============================================================================
//monitor
//==============================================================================

void task_monitor(void *arg) {
    const TickType_t xPeriod = pdMS_TO_TICKS(200);
    TickType_t xLastWakeTime = xTaskGetTickCount();
    
    printf("TIMESTAMP, CPU_CYCLES, INSTRUCTIONS, CACHE_MISSES, BRANCH_MISSES, LABEL, DET_STATUS, DET_PROB, BENCH_ID\n");
    fflush(stdout);

    // Initialize IPC shared memory with zeros to avoid garbage in labels
    ipc_init_channels();

    uint64_t timer_freq;
    asm volatile("mrs %0, cntfrq_el0" : "=r"(timer_freq));

    // PMU registers are initialized by the hypervisor (timer_arch_init)
    // DO NOT call init_pmu_registers() here — conflicts with EL2 config

    while(1) {
        vTaskDelayUntil(&xLastWakeTime, xPeriod);

        collect_and_process_pmu_sample(timer_freq);

        // UART serial dump in dump_history_to_serial takes a long time, causing vTaskDelayUntil
        // to try to "compensate" for missed delays by running instantly without waiting.
        // This reads cached hypervisor data, generating 100% duplicate data.
        // The logic below detects if a large delay occurred and resynchronizes the timer.
        TickType_t current_tick = xTaskGetTickCount();
        if ((current_tick - xLastWakeTime) > xPeriod) {
            xLastWakeTime = current_tick;
        }
    }
}

