#ifndef BANDWIDTH_H
#define BANDWIDTH_H

#include <stdint.h>
#include <stdio.h>

#define CACHE_LINE_SIZE 64
#define BW_DEFAULT_ALLOC_SIZE 1024 * 1024 * 10



//int64_t bench_read();
int64_t bench_read(int *g_mem_ptr);
int bench_write(int *g_mem_ptr);

#endif
