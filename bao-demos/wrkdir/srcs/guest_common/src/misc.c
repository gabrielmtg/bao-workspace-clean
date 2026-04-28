// Filename: misc.c
//         João Almeida (https://github.com/nynepebbles/)

#include "../inc/misc.h"
#include "../inc/regulation.h"

#define PRINT_CSV 1

typedef struct {
  int64_t total_calc_r;
  int64_t total_calc_w;
  //
  int64_t PMU_counter_used_budget;
  int64_t PMU_counter_used_budget_r;
  int64_t PMU_counter_used_budget_w;
  //
  int64_t PMU_counter_used_budget_r_per_period[PERIOD_QNT];
  int64_t PMU_counter_used_budget_w_per_period[PERIOD_QNT];
  //
  int64_t calc_per_period_read[PERIOD_QNT];
  int64_t calc_per_period_write[PERIOD_QNT];
  //
  int64_t total_cycles;
  int64_t total_instructions;
  int64_t total_cache_misses;
  int64_t total_mispredicts;
  int64_t cycles[PERIOD_QNT];
  int64_t instructions[PERIOD_QNT];
  int64_t cache_misses[PERIOD_QNT];
  int64_t mispredicts[PERIOD_QNT];
} BenchmarkData;

void write_used_budget(struct VM vm_info, BenchmarkData *d) {
  //
  d->PMU_counter_used_budget_r = 0;
  d->PMU_counter_used_budget_w = 0;
  d->PMU_counter_used_budget = 0;
  for (uint8_t i = 0; i < PERIOD_QNT; i++) {
    int64_t period_read_used = vm_info.used_r_budget_period[i];
    int64_t period_write_used = vm_info.used_w_budget_period[i];

    d->PMU_counter_used_budget_r_per_period[i] = period_read_used;
    d->PMU_counter_used_budget_w_per_period[i] = period_write_used;
    d->PMU_counter_used_budget_r += period_read_used;
    d->PMU_counter_used_budget_w += period_write_used;
    d->PMU_counter_used_budget += period_read_used + period_write_used;
  }
}

void write_calc_budget(struct VM vm_info, BenchmarkData *d) {
  // printf("\tCalc per period \n\t\tr ");

  d->total_calc_r = 0;
  d->total_calc_w = 0;
  for (uint8_t i = 0; i < PERIOD_QNT; i++) {
    int64_t period_calc_read = vm_info.calc_r_budget_period[i];
    int64_t period_calc_write = vm_info.calc_w_budget_period[i];

    d->calc_per_period_read[i] = period_calc_read;
    d->calc_per_period_write[i] = period_calc_write;
    d->total_calc_r += period_calc_read;
    d->total_calc_w += period_calc_write;
  }
}

void write_raw(struct VM vm_info, BenchmarkData *d) {
  d->total_cycles = 0;
  d->total_instructions = 0;
  d->total_cache_misses = 0;
  d->total_mispredicts = 0;
  for (uint8_t i = 0; i < PERIOD_QNT; i++) {
    d->cycles[i] = vm_info.PMU_raw_values[2][i];
    d->instructions[i] = vm_info.PMU_raw_values[3][i];
    d->cache_misses[i] = vm_info.PMU_raw_values[4][i];
    d->mispredicts[i] = vm_info.PMU_raw_values[5][i];
    //
    d->total_cycles += d->cycles[i];
    d->total_instructions += d->instructions[i];
    d->total_cache_misses += d->cache_misses[i];
    d->total_mispredicts += d->mispredicts[i];
  }
}

void print_vm_header() {
  printf("budget_function,PMU_counter_used_budget,");
  printf("PMU_counter_used_budget_r,PMU_counter_used_budget_w,");
  printf("total_calc_r,total_calc_w,");

  printf("total_cycles,");
  printf("total_instructions,");
  printf("total_cache_misses,");
  printf("total_mispredicts,");
  //
  for (int i = 0; i < PERIOD_QNT; i++) {
    printf("cycles[%d],", i);
  }
  for (int i = 0; i < PERIOD_QNT; i++) {
    printf("instructions[%d],", i);
  }
  for (int i = 0; i < PERIOD_QNT; i++) {
    printf("cache_misses[%d],", i);
  }
  for (int i = 0; i < PERIOD_QNT; i++) {
    printf("mispredicts[%d],", i);
  }
  //
  for (int i = 0; i < PERIOD_QNT; i++) {
    printf("used_budget_read[%d],", i);
  }
  for (int i = 0; i < PERIOD_QNT; i++) {
    printf("used_budget_write[%d],", i);
  }
  for (int i = 0; i < PERIOD_QNT; i++) {
    printf("calculated_read[%d],", i);
  }
  for (int i = 0; i < PERIOD_QNT; i++) {
    printf("calculated_write[%d],", i);
  }
  printf("\n");
}

void print_array(int64_t values[PERIOD_QNT]) {
  for (int i = 0; i < PERIOD_QNT; i++) {
    printf("%ld,", values[i]);
  }
}

void print_task_array(int64_t values[TASK_QUANTITY]) {
  for (int i = 0; i < TASK_QUANTITY; i++) {
    printf("%ld,", values[i]);
  }
}

void print_compact(int64_t values[PERIOD_QNT]) {
  for (int i = 0; i < PERIOD_QNT; i++) {
    printf("%s", values[i] ? "O" : "-");
  }
  printf(",");
}

void print_vm_info(struct VM vm_info, Benchmark *b) {
  BenchmarkData info;
  write_used_budget(vm_info, &info);
  write_calc_budget(vm_info, &info);
  write_raw(vm_info, &info);
  // write_period_duration(vm_info, &info);
  // write_others(vm_info, &info);
  // write_clock_cycle(vm_info, &info);

  // printf("%ld,", info.period_duration_total);
  // printf("%s,", benchmark_get_formula_name(b));
  printf("%ld,", info.PMU_counter_used_budget);
  printf("%ld,", info.PMU_counter_used_budget_r);
  printf("%ld,", info.PMU_counter_used_budget_w);
  printf("%ld,", info.total_calc_r);
  printf("%ld,", info.total_calc_w);

  printf("%ld,", info.total_cycles);
  printf("%ld,", info.total_instructions);
  printf("%ld,", info.total_cache_misses);
  printf("%ld,", info.total_mispredicts);

  print_array(info.cycles);
  print_array(info.instructions);
  print_array(info.cache_misses);
  print_array(info.mispredicts);

  print_array(info.PMU_counter_used_budget_r_per_period);
  print_array(info.PMU_counter_used_budget_w_per_period);
  // print_compact(info.has_overflowed);
  // printf("%lu,", info.total_clock);
  // print_task_array(info.completed_runs_per_task);
  // print_array(info.used_budget_per_period_read);
  // print_array(info.used_budget_per_period_write);
  print_array(info.calc_per_period_read);
  print_array(info.calc_per_period_write);
  // print_array(info.period_duration);
  // print_array(info.clock_per_period);

  printf("\n");
}
