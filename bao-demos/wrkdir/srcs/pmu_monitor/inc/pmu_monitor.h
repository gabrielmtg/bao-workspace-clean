#ifndef PMU_MONITOR_H
#define PMU_MONITOR_H

#include "../../VMs/vm_0/src/tasks/inc/globals.h"
#include <stdint.h>


unsigned long hypercall(unsigned long hc_id, unsigned long arg);
void bao_get_pmu_data(uint8_t target_cpu, PMU_data *data); 
void task_monitor(void *arg);
void collect_and_process_pmu_sample(uint64_t timer_freq);
void ipc_init_channels(void);
void init_pmu_registers();

#endif