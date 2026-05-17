    .syntax unified
    .arch armv5t
    .arm
    .text
    .global _start

@ Exception vector table at 0x0
_start:
    b       reset_handler       @ 0x00 Reset
    b       .                   @ 0x04 Undefined instruction
    b       swi_handler         @ 0x08 SWI
    b       bkpt_handler        @ 0x0C Prefetch Abort (BKPT)
    b       .                   @ 0x10 Data Abort
    nop                         @ 0x14 Reserved
    b       .                   @ 0x18 IRQ
    b       .                   @ 0x1C FIQ

@ Prefetch Abort handler (used by BKPT in ARMv5T)
@ LR_abt = aborting instruction + 4, so movs pc, lr resumes at next instruction
bkpt_handler:
    movs    pc, lr

@ SWI handler
@ LR_svc = instruction after SWI, so movs pc, lr resumes normally
swi_handler:
    movs    pc, lr

reset_handler:
    mov r0, #0              @ progress counter

    @ NOP: no operation, PC advances normally
    nop
    nop
    nop
    add r0, r0, #1          @ r0 = 1 (confirms NOPs didn't stall)

    @ BKPT: software breakpoint; fires Prefetch Abort, handler returns to next instruction
    bkpt #0xAB

    add r0, r0, #1          @ r0 = 2 (reached after bkpt handler returns)

    @ SWI: software interrupt; handler returns to next instruction
    swi #0

    add r0, r0, #1          @ r0 = 3 (reached after swi handler returns)

    .word 0xE7FFDEAD        @ halt  (r0 = 3)
