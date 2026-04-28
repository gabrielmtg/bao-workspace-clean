#ifndef ZOMBIELOAD_H
#define ZOMBIELOAD_H

#include <stdint.h>

#define FILL_BUFFER_SIZE (64 * 1024)

extern uint8_t zombie_noise_buffer[FILL_BUFFER_SIZE];
extern uint8_t array[256 * 512];


void generate_mds_traffic();
void execute_zombieload_attack(uint8_t secret_val, int cache_hit_threshold, uint32_t duration_ms);
void task_zombieload(void *arg);

#endif