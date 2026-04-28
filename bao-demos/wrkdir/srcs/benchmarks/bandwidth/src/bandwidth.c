#include "../inc/bandwidth.h"


int64_t bench_read(int *g_mem_ptr)
{
	int g_nread = 0;
	int i;
	int64_t sum = 0;

	for (i = 0; i < BW_DEFAULT_ALLOC_SIZE/4; i += (CACHE_LINE_SIZE))
		sum += g_mem_ptr[i];
	    
	g_nread += BW_DEFAULT_ALLOC_SIZE;
	return sum;
}

int bench_write(int *g_mem_ptr)
{
	int g_nread = 0;
	register int i;
	
	for (i = 0; i < BW_DEFAULT_ALLOC_SIZE/4; i+= (CACHE_LINE_SIZE))
		g_mem_ptr[i] = i;

	g_nread += BW_DEFAULT_ALLOC_SIZE;
	return g_nread;
}


