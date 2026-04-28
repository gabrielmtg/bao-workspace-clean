// Filename: pmu.c
// Author: Everaldo Pereira Gomes


#include "../inc/pmu.h"


void start_cycle_counting(const uint8_t counter)
{
	// conf
	ASM("msr pmuserenr_el0, %0"  :: "r" (1 << 0));
	ASM("msr PMCR_EL0, %0"       :: "r" ((1 << 0) | (1 << 1) | (1 << 2)));

	if (counter == 4)
	{
		ASM("msr pmevcntr4_el0, %0"  :: "r" (0) :);
		ASM("msr pmevtyper4_el0, %0" :: "r" (CPU_CYCLE));
	}
	else if (counter == 5)
	{
		ASM("msr pmevcntr5_el0, %0"  :: "r" (0) :);
		ASM("msr pmevtyper5_el0, %0" :: "r" (CPU_CYCLE));
	}

	ASM("msr pmintenset_el1, %0" :: "r" (1 << counter));

	//start
	ASM("msr pmcntenset_el0, %0" :: "r" (1 << counter));
}


uint32_t get_cycle_counting(const uint8_t counter)
{
	// stop
	ASM("msr pmcntenclr_el0, %0" :: "r" (1 << counter));
	ASM("msr pmintenclr_el1, %0" :: "r" (1 << counter));
	ASM("msr pmovsclr_el0, %0"   :: "r" (1 << counter));

	// get val
	uint32_t cycles = 0;

	if (counter == 4)
	{
		ASM("mrs %0, pmevcntr4_el0" : "=r" (cycles) ::);		
	}
	else if (counter == 5)
	{
		ASM("mrs %0, pmevcntr5_el0" : "=r" (cycles) ::);
	}
	    
	return cycles;
}


void reset_counter(const uint8_t counter)
{
	if (counter == 0)
		ASM("msr pmevcntr0_el0, %0" :: "r" (0):);
	else if (counter == 1)
		ASM("msr pmevcntr1_el0, %0" :: "r" (0):);
	else if (counter == 2)
		ASM("msr pmevcntr2_el0, %0" :: "r" (0):);
	else if (counter == 3)
		ASM("msr pmevcntr3_el0, %0" :: "r" (0):);
	else if (counter == 4)
		ASM("msr pmevcntr4_el0, %0" :: "r" (0):);
	else if (counter == 5)
		ASM("msr pmevcntr5_el0, %0" :: "r" (0):);
}
