#ifndef SPECTRE_H
#define SPECTRE_H

#include <stdint.h>
#include <stddef.h>


extern unsigned int array1_size;
extern uint8_t unused1[64];
extern uint8_t array1[16];
extern uint8_t unused2[64]; 
extern uint8_t array2[256 * 512];
extern char *secret;
extern volatile uint8_t temp_spectre ;

void victim_function(size_t x);
void read_memory_byte_spectre(int cache_hit_threshold, size_t malicious_x, uint8_t value[2], int score[2]);
void execute_spectre_attack(int cache_hit_threshold, size_t starting_malicious_x, int bytes_to_read);
void task_spectre(void *arg);

#endif