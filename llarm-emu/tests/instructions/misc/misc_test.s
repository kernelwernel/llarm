    .syntax unified
    .arch armv5t
    .arm
    .text
    .global _start

    @ Miscellaneous instructions: NOP, BKPT, SWI
_start:
    mov r0, #0              @ progress counter

    @ NOP: no operation, PC advances normally
    nop
    nop
    nop
    add r0, r0, #1          @ r0 = 1 (confirms NOPs didn't stall)

    @ BKPT: software breakpoint; emulator may trap or continue
    @ Placed here so execution can optionally stop/log at this point
    bkpt #0xAB

    add r0, r0, #1          @ r0 = 2 (reached if emulator resumes after bkpt)

    @ SWI (software interrupt): triggers supervisor call
    @ Without an OS handler, the emulator may log or ignore it
    swi #0

    add r0, r0, #1          @ r0 = 3 (reached if emulator resumes after swi)

    .word 0xE7FFDEAD        @ halt
    @ r0 value at halt depends on emulator behavior for bkpt/swi:
    @   r0=1 if emulator halts on bkpt
    @   r0=2 if bkpt resumed but swi halts
    @   r0=3 if both resumed normally
