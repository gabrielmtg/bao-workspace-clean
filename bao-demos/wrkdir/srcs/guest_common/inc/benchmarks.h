#ifndef BENCHMARKS_H
#define BENCHMARKS_H

#include <stdint.h>
#include <stdlib.h>

// #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#//

// void empty_wrapper(void *context);
// void bandwidth_wrapper(void *context);
// void dijkstra_wrapper(void *context);
// void disparity_wrapper(void *context);
// void fft_wrapper(void *context);
// void mser_wrapper(void *context);
// void qsort_wrapper(void *context);
// void sha_wrapper(void *context);
// void sorting_wrapper(void *context);

// #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#//

#define BENCH_ARRAY_INDEX 0
#define NUM_BENCHMARKS 1280
#define FORMULA_COUNT 11

typedef enum {
  // LR_FORMULA, // <not implemented>
  EWMA_V2_FORMULA,
  SW_V2_FORMULA,
  AFC_V2_FORMULA,
  LR_V2_FORMULA,
  AMBP_V2_FORMULA,
  PIC_V2_FORMULA,
  //
  EWMA_FORMULA,
  SW_FORMULA,
  AFC_FORMULA,
  AMBP_FORMULA,
  PIC_FORMULA,
  // FORMULA_COUNT,
} formula_t;

typedef struct {
  int index;
  void (*pointer)(void *context);
  const char *name;
  void *context;
} Function;

typedef struct {
  Function function;
  int task_num;
  int periodicity;
  int task_overruns;
  int task_underruns;
} info_t;

typedef struct {
  // Function functions[NUM_BENCHMARKS];
  info_t info[NUM_BENCHMARKS];
  formula_t formula;
  size_t info_size;
} Benchmark;

void initialize_all_benchmark_contexts();
void free_all_benchmark_contexts();

Benchmark *benchmark_create();
void benchmark_init(Benchmark *b);
void benchmark_destroy(Benchmark *b);

const char *benchmark_get_formula_name(Benchmark *b);
formula_t benchmark_get_formula(Benchmark *b);
void benchmark_set_formula(Benchmark *b, formula_t formula);

info_t *benchmark_add_info(Benchmark *b, int vm_num, int task_num,
                           int periodicity);
info_t *benchmark_get_info(Benchmark *b, int vm_num, int task_num);

#endif
