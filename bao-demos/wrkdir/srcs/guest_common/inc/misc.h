// Filename: misc.h
// Author: Everaldo Pereira Gomes
//         João Almeida (https://github.com/nynepebbles/)

#ifndef MISC_H
#define MISC_H

#include "benchmarks.h"
#include "regulation.h"
#include <stdint.h>
#include <stdio.h>

void print_end_info_no_reg(const uint8_t vm_num, const uint8_t task_num,
                           const char *task_name);
void print_end_info_reg(const uint8_t vm_num, const uint8_t task_num,
                        const char *task_name);

void print_end_bench_info_reg(info_t info);
void print_csv_header();
void print_vm_header();

void print_vm_info(struct VM vm_info, Benchmark *b);

#endif
