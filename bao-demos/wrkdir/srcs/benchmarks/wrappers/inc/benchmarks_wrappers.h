#ifndef BENCHMARKS_H
#define BENCHMARKS_H

#include <stdint.h>

#define NUM_INTS (BW_DEFAULT_ALLOC_SIZE / sizeof(int))
#define CACHE_LINE_INTS (CACHE_LINE_SIZE / sizeof(int)) // 16 indices = 64 bytes

extern uint32_t qsort_input_data[164][3];

typedef struct {
    int *mem_ptr;
    int64_t sum;
} bandwidth_context_fann_t;

void bandwidth_wrapper_fann(void *context);
void disparity_wrapper_fann();
void qsort_wrapper_fann();
void dijkstra_wrapper_fann();
void sha_wrapper_fann();
void fft_wrapper_fann();
void sorting_wrapper_fann();

void task_bandwidth(void *arg);
void task_disparity(void *arg);
void task_qsort(void *arg);
void task_dijkstra(void *arg);
void task_sha(void *arg);
void task_fft(void *arg);
void task_sorting(void *arg);

#endif