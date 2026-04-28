#include <FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <portmacro.h>
#include <sysregs.h>
#include <gic.h>
#include <irq.h>
#include <stdio.h>

static uint64_t timer_step = 0;
#define GICD_BASE 0xF9010000U
#define GICC_BASE 0xF9020000U

void FreeRTOS_ClearTickInterrupt(){
    sysreg_cntv_tval_el0_write(timer_step);
}

static void tick_handler_wrapper(unsigned id) {
    FreeRTOS_Tick_Handler();
}

void FreeRTOS_SetupTickInterrupt()
{
	//printf("FreeRTOS_SetupTickInterrupt\n");

	const uint32_t irq_num[] = {27};
	const uint32_t qnt = sizeof(irq_num) / sizeof(uint32_t);
	
	for (uint32_t i = 0; i < qnt; i++)
	{
		irq_set_handler(irq_num[i], tick_handler_wrapper);
		irq_enable(irq_num[i]);
		irq_set_prio(irq_num[i], portLOWEST_USABLE_INTERRUPT_PRIORITY << portPRIORITY_SHIFT);
	}
    
    uint64_t freq = sysreg_cntfrq_el0_read();
    timer_step = freq / configTICK_RATE_HZ;
    sysreg_cntv_tval_el0_write(timer_step);
    sysreg_cntv_ctl_el0_write(1); // enable timer
}

void vApplicationIRQHandler(uint32_t ulICCIAR){
	//printf("FreeRTOS vApplicationIRQHandler %d\n", ulICCIAR);
	//uint32_t *p = (uint32_t*)(GICC_BASE + 0x0);
	//*p &= ~(1 << 9);
	
	/* if (ulICCIAR == 0) */
	/* { */
	/* 	p = (uint32_t*)(GICC_BASE + 0x10); */
	/* 	*p &= ~(0x3FFF << 0); */
	/* } */
	/* else if (ulICCIAR == 1) */
	/* { */
	/* 	p = (uint32_t*)(GICC_BASE + 0x10); */
	/* 	*p &= ~(0x3FFF << 0); */
	/* 	*p |= 0x3 << 0; */

	/* 	p = (uint32_t*)(GICC_BASE + 0x24); */
	/* 	*p |= 0x3 << 0; */
	/* } */

	//*p |= 1 << 0;

	/* p = (uint32_t*)(GICC_BASE + 0x1000); */
	/* *p &= ~(0x1FFF << 0); */
	/* *p |= 1 << 0; */

	/* p = (uint32_t*)(GICC_BASE + 0x20); */
	/* uint32_t a = *p; */
	
	/* p = (uint32_t*)(GICC_BASE + 0x24); */
	/* *p &= ~(0x1FFF << 0); */
	/* *p |= 1 << 0; */
	
	//GICD
	/* p = (uint32_t*)(GICD_BASE + 0xF10); */
	/* *p &= ~(0xFFFFFFFF) << 0; */
	/* *p |= 0xFFFFFFFF << 0; */

	/* p = (uint32_t*)(GICD_BASE + 0x180); */
	/* *p |= 1 << 0; */
	
	/* p = (uint32_t*)(GICD_BASE + 0x280); */
	/* *p |= 1 << 0; */

	/* p = (uint32_t*)(GICD_BASE + 0x380); */
	/* *p |= 1 << 0; */
	
	//printf(">> %p, %u\n", p, *p);
	
    irq_handle(ulICCIAR);
}

