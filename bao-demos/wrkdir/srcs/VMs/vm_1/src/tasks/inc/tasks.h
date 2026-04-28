#ifndef TASKS_H
#define TASKS_H

void task_orchestrator(void *arg);

// Benchmark runner functions (one iteration each)
void run_bandwidth(void);
void run_disparity(void);
void run_fft(void);
void run_qsort_bench(void);
void run_dijkstra(void);
void run_sha(void);
void run_sorting(void);

#endif