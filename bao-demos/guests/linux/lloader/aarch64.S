#define STRINGIFY2(X) #X
#define STRINGIFY(X) STRINGIFY2(X)

.section .nloader, "a"
.global _start
_start:
    /* make sure all exceptions disabled */
    msr daifset, 0xf

    /* make sure mmu disable */
    mrs	x0, sctlr_el1
    ldr w1, =0x1005
    bic	x0, x0, x1
    msr	sctlr_el1, x0

    isb

    /* Set GPIO 8 and 9 to ALT4 for UART4 */
    ldr x0, =0xfe200000
    ldr w1, [x0]
    /* clear bits 24-29 */
    ldr w2, =0x3f000000
    bic w1, w1, w2
    /* set bits 24-29 to 011 011 (0x1B000000) */
    ldr w2, =0x1b000000
    orr w1, w1, w2
    str w1, [x0]

    /* boot protocol */
    ldr x0, =__dtb_start
    mov x1, xzr
    mov x2, xzr
    mov x3, xzr
    
    /* jump to linux */
    ldr x4, =_start
    ldr x5, =__linux_start
    sub x4, x5, x4
    adr x5, _start
    add x5, x5, x4


    /* ===== Initialize PL011 UART4 at 0xfe201800 ===== */
    ldr x6, =0xfe201800

    /* 1. Disable UART4: CR = 0 */
    str wzr, [x6, #0x30]

    /* 2. Wait for UART to finish: poll UARTFR bit 3 (BUSY) */
1:  ldr w7, [x6, #0x18]
    tbnz w7, #3, 1b

    /* 3. Clear all interrupts: ICR = 0x7FF */
    mov w7, #0x7FF
    str w7, [x6, #0x44]

    /* 4. Set baud rate for 115200 @ 48MHz clock:
     *    IBRD = 48000000 / (16 * 115200) = 26
     *    FBRD = round((0.04167) * 64) = 3
     */
    mov w7, #26
    str w7, [x6, #0x24]       /* UARTIBRD */
    mov w7, #3
    str w7, [x6, #0x28]       /* UARTFBRD */

    /* 5. Set LCR_H: 8 bits, FIFO enabled, no parity
     *    bit 4 = FEN (FIFO enable)
     *    bits 5-6 = WLEN = 11 (8 bits)
     *    = 0x70
     */
    mov w7, #0x70
    str w7, [x6, #0x2C]       /* UARTLCR_H */

    /* 6. Disable all interrupts: IMSC = 0 */
    str wzr, [x6, #0x38]

    /* 7. Enable UART4: CR = UARTEN | TXE | RXE = 0x301 */
    mov w7, #0x301
    str w7, [x6, #0x30]       /* UARTCR */

    br x5

.section .linux, "a"
    .incbin STRINGIFY(IMAGE)

.section .dtb, "a"
    .incbin STRINGIFY(DTB)

.section .initrd, "a"
    .incbin STRINGIFY(INITRD)
 
