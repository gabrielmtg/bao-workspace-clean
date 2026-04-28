/**
 * fp_context.h — Save/restore NEON/FP registers for EL2 interrupt context
 * ========================================================================
 * On AArch64 the NEON/FP register file consists of 32 × 128-bit registers
 * (q0-q31) plus two 32-bit control/status registers (FPCR, FPSR).
 *
 * The Bao VM_EXIT macro only saves general-purpose registers (x0-x30).
 * If the hypervisor uses floating-point instructions (e.g. the MLP detector)
 * inside an interrupt handler, it will silently corrupt the guest's FP state.
 *
 * These helpers save and restore the full FP context around the critical
 * section so that VMs are never affected.
 *
 * Memory cost : 528 bytes per context  (32×16 + 2×8)
 * Time cost   : ~50-100 cycles on Cortex-A72 (negligible vs 200 ms period)
 */

#ifndef FP_CONTEXT_H
#define FP_CONTEXT_H

#include <stdint.h>

/* ── FP context structure ─────────────────────────────────────────────────── */
typedef struct {
    __uint128_t q[32];   /* q0-q31  (each covers the matching d and s regs) */
    uint64_t    fpcr;    /* Floating-Point Control Register                  */
    uint64_t    fpsr;    /* Floating-Point Status Register                   */
} __attribute__((aligned(16))) fp_context_t;

/* ── Save all NEON/FP registers into *ctx ─────────────────────────────────── */
static inline void fp_context_save(fp_context_t *ctx)
{
    __asm__ volatile(
        "stp  q0,  q1,  [%0, #(16* 0)] \n"
        "stp  q2,  q3,  [%0, #(16* 2)] \n"
        "stp  q4,  q5,  [%0, #(16* 4)] \n"
        "stp  q6,  q7,  [%0, #(16* 6)] \n"
        "stp  q8,  q9,  [%0, #(16* 8)] \n"
        "stp  q10, q11, [%0, #(16*10)] \n"
        "stp  q12, q13, [%0, #(16*12)] \n"
        "stp  q14, q15, [%0, #(16*14)] \n"
        "stp  q16, q17, [%0, #(16*16)] \n"
        "stp  q18, q19, [%0, #(16*18)] \n"
        "stp  q20, q21, [%0, #(16*20)] \n"
        "stp  q22, q23, [%0, #(16*22)] \n"
        "stp  q24, q25, [%0, #(16*24)] \n"
        "stp  q26, q27, [%0, #(16*26)] \n"
        "stp  q28, q29, [%0, #(16*28)] \n"
        "stp  q30, q31, [%0, #(16*30)] \n"
        "mrs  x1, fpcr                  \n"
        "mrs  x2, fpsr                  \n"
        "add  x3, %0, #(16*32)          \n"
        "stp  x1, x2,   [x3]            \n"
        : : "r" (ctx) : "x1", "x2", "x3", "memory"
    );
}

/* ── Restore all NEON/FP registers from *ctx ──────────────────────────────── */
static inline void fp_context_restore(const fp_context_t *ctx)
{
    __asm__ volatile(
        "ldp  q0,  q1,  [%0, #(16* 0)] \n"
        "ldp  q2,  q3,  [%0, #(16* 2)] \n"
        "ldp  q4,  q5,  [%0, #(16* 4)] \n"
        "ldp  q6,  q7,  [%0, #(16* 6)] \n"
        "ldp  q8,  q9,  [%0, #(16* 8)] \n"
        "ldp  q10, q11, [%0, #(16*10)] \n"
        "ldp  q12, q13, [%0, #(16*12)] \n"
        "ldp  q14, q15, [%0, #(16*14)] \n"
        "ldp  q16, q17, [%0, #(16*16)] \n"
        "ldp  q18, q19, [%0, #(16*18)] \n"
        "ldp  q20, q21, [%0, #(16*20)] \n"
        "ldp  q22, q23, [%0, #(16*22)] \n"
        "ldp  q24, q25, [%0, #(16*24)] \n"
        "ldp  q26, q27, [%0, #(16*26)] \n"
        "ldp  q28, q29, [%0, #(16*28)] \n"
        "ldp  q30, q31, [%0, #(16*30)] \n"
        "add  x3, %0, #(16*32)          \n"
        "ldp  x1,  x2,  [x3]            \n"
        "msr  fpcr, x1                  \n"
        "msr  fpsr, x2                  \n"
        : : "r" (ctx) : "x1", "x2", "x3", "memory"
    );
}

#endif /* FP_CONTEXT_H */
