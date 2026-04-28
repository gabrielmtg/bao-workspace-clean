#ifndef MELTDOWN_H
#define MELTDOWN_H

#include <stdint.h>

extern uint8_t array[256 * 512];
extern uint8_t secret_data; 
extern void *kernel_address; 

void try_meltdown_read(void *addr);
int measure_cache_meltdown(int threshold);
void execute_meltdown_attack(int cache_hit_threshold, uint32_t duration_ms);
void task_meltdown(void *arg);

#endif