/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>

#include <cpu.h>
#include <mem.h>
#include <interrupts.h>
#include <console.h>
#include <platform.h>
#include <vmm.h>
#include <regulator.h>
#include <arch/generic_timer.h>

#define DMA_BASE 0xFE007000
#define DMA_CHANNEL_0 (DMA_BASE + 0x000)
#define DMA_BASE 0xFE007000   // Physical base address of DMA
#define DMA_SIZE 0x1000       // Size of the MMIO region (4KB)
#define DMA_PAGE_SIZE 0x1000  // Typical page size
#define SEC_HYP 1
static vaddr_t dma_vaddr = INVALID_VA;  // Virtual address after mapping

/*

SEC_HYP_GLOBAL = 0, ok 0x4a000
    SEC_HYP_IMAGE, ok 0x4a000
    SEC_HYP_PRIVATE, ok 0x3000
    SEC_HYP_VM, ok 0x0
    SEC_HYP_ANY, error
    SEC_VM_ANY = 0, ok 0x4a000
    SEC_UNKNOWN = -1,
*/
void dma_map_mmio(void)
{
    struct addr_space *as = &cpu()->as;
    size_t num_pages = DMA_SIZE / DMA_PAGE_SIZE;

    dma_vaddr =
        mem_alloc_map_dev(as, SEC_VM_ANY, INVALID_VA, DMA_BASE, num_pages);

    if (dma_vaddr == INVALID_VA) printk("ERROR!!!\n");

    printk("DMA MMIO mapped at virtual address: %p\n", (void *)dma_vaddr);
}

void test_dma_access(void)
{
    if (dma_vaddr == INVALID_VA) {
        printk("DMA MMIO not mapped!\n");
        return;
    }

    volatile uint32_t *DMA_CS = (uint32_t *)(dma_vaddr);
    printk("DMA Control Status register at %p: 0x%x\n", DMA_CS, *DMA_CS);
}

/* typedef struct */
/* { */
/*     uint32_t TI; */
/*     uint32_t SOURCE_AD; */
/*     uint32_t DEST_AD; */
/*     uint32_t TXFR_LEN; */
/*     uint32_t STRIDE; */
/*     uint32_t NEXTCONBK; */
/*     uint32_t RESERVED[2]; */
/* } DMA_ctrl_block; */

/* DMA_ctrl_block dma_cb_cpu0 __attribute__((aligned(32))) = { */
/*     .TI = 0x00000000, */
/*     .SOURCE_AD = 0x2000, */
/*     .DEST_AD = 0x0, */
/*     .TXFR_LEN = 1024, */
/*     .NEXTCONBK = 0x00000000 */
/* }; */

/* void setup_dma(uintptr_t dma_channel, DMA_ctrl_block *cb) */
/* { */
/*     volatile uint32_t *DMA_CS = (volatile uint32_t *)(dma_channel + 0x00); */
/* 	printk("%u %lx\n", DMA_CS, *DMA_CS); */

/* 	//volatile uint32_t *DMA_CONBLK_AD = (volatile uint32_t *)(dma_channel +
 * 0x04); */
/*     // Reset DMA */
/*     //\*DMA_CS |= (1 << 31); */

/*     /\* // Set Control Block address safely using uintptr_t *\/ */
/*     //\*DMA_CONBLK_AD = (uintptr_t)cb; */

/*     /\* // Enable DMA *\/ */
/*     /\* *DMA_CS = (1 << 0); // Set ACTIVE bit *\/ */
/* } */

void init(cpuid_t cpu_id, paddr_t load_addr)
{
    /**
     * These initializations must be executed first and in fixed order.
     */

    cpu_init(cpu_id, load_addr);
    mem_init(load_addr);

    /* -------------------------------------------------------------- */
    console_init();

    if (cpu()->id == CPU_MASTER) {
        // working cycles count
        /* ASM("msr PMCR_EL0, %0"       :: "r" ((1 << 0) | (1 << 1) | (1 << 2) |
         * (1 << 6))); */
        /* ASM("msr PMCCFILTR_EL0, %0" :: "r" (0x1 << 27)); */
        /* ASM("msr PMCNTENSET_el0, %0" :: "r" (1 << 31)); */

        // printk("sizeof(uint64_t) %d\n", sizeof(uint64_t));
        // printk("sizeof(unsigned long long) %d\n", sizeof(unsigned long
        // long));
        // printk("BENCH_ARRAY_INDEX %d\n", BENCH_ARRAY_INDEX);
        init_regulation_config();

        // working cycles count
        // uint64_t v = 0;
        /* ASM("mrs %0, PMCCNTR_el0" : "=r" (v)::); */
        /* printk("1: %u\n", v); */
        /* while(1); */

        // dma_map_mmio();  // Step 1: Map the DMA MMIO region
        // test_dma_access();  // Step 2: Read and print a register to verify

        // printk("====================");
        // while(1);

        /* volatile uint32_t *DMA_CS = (uint32_t *)(DMA_CHANNEL_0); */
        /* printk("%p %x\n", DMA_CS, *DMA_CS); */
        // setup_dma(DMA_CHANNEL_0, &dma_cb_cpu0);
    }

    interrupts_init();
    timer_arch_init();
    vmm_init();

    /* Should never reach here */
    printk("bao before infinite loop\n");
    while (1);
}
