#include "../inc/armageddon.h"
#include <stdio.h>
#include <unistd.h>

uint8_t shared_probe_data[4096] __attribute__((aligned(4096))); 
volatile uint8_t *target_addr = &shared_probe_data[2048];

uint64_t calibrate_threshold() {
    uint64_t hit_time = 0, miss_time = 0;
    int samples = 1000;

    for(int i=0; i<samples; i++) {
        volatile uint8_t reload = *target_addr;
        asm volatile("" : : "r"(reload) : "memory"); 
        hit_time += arm_measure_access((void*)target_addr);
    }
    hit_time /= samples;

    for(int i=0; i<samples; i++) {
        arm_flush((void*)target_addr);
        miss_time += arm_measure_access((void*)target_addr);
    }
    miss_time /= samples;

    uint64_t threshold = (hit_time + miss_time) / 2;
    return threshold;
}

void simulate_victim_access() {
    volatile uint8_t dummy = *target_addr;
    asm volatile("" : : "r"(dummy) : "memory"); 
}

void execute_flush_reload_attack(uint64_t threshold) {
    int hits = 0;
    int probes = 0;

    while(probes < 1000) {
        arm_flush((void*)target_addr);
        
        if ((probes % 3) == 0) { 
            simulate_victim_access();
        }

        uint64_t time = arm_measure_access((void*)target_addr);
        probes++;

        if (time < threshold) {
            hits++;
        }
    }
}

int main() {
    uint64_t threshold = calibrate_threshold();
    
    while(1) {
        execute_flush_reload_attack(threshold);
        usleep(1000);
    }
    return 0;
}