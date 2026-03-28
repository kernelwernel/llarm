/* Minimal bare-metal startup for VersatilePB (ARM926EJ-S, ARMv5TE)
 * Used when running under qemu-system-arm with semihosting. */

    .section .text.startup
    .global  _start
    .arm

_start:
    /* Set stack pointer to the top of VersatilePB SDRAM (128 MB @ 0x00000000) */
    mov     sp, #0x08000000

    bl      main

    /* SYS_EXIT semihosting call: exit with the return value of main */
    mov     r4, r0                  /* save exit code                       */
    sub     sp, sp, #8              /* allocate exit-block on stack         */
    ldr     r5, =0x20026            /* ADP_Stopped_ApplicationExit          */
    str     r5, [sp, #0]
    str     r4, [sp, #4]
    mov     r0, #0x18               /* SYS_EXIT                             */
    mov     r1, sp
    svc     0x123456
.Lhang:
    b       .Lhang                  /* should never reach here              */
