    .syntax unified
    .arch armv4t
    .arm
    .text
    .global _start

    @ Branch instructions: B, BL, BX, and condition codes
    @ r0 counts correctly-taken branches; r1 counts erroneously-taken ones
_start:
    mov r0, #0              @ correct-branch counter
    mov r1, #0              @ error counter

    @ B: unconditional branch skips the poison instruction
    b b_landed
    add r1, r1, #1          @ should be skipped
b_landed:
    add r0, r0, #1          @ r0 = 1

    @ BEQ: taken when Z=1
    cmp r0, #1              @ 1 == 1, Z=1
    beq eq_landed
    add r1, r1, #1
eq_landed:
    add r0, r0, #1          @ r0 = 2

    @ BNE: taken when Z=0
    cmp r0, #99             @ 2 != 99, Z=0
    bne ne_landed
    add r1, r1, #1
ne_landed:
    add r0, r0, #1          @ r0 = 3

    @ BLT / BGT
    mov r2, #5
    cmp r2, #10             @ 5 < 10, N=1
    blt lt_landed
    add r1, r1, #1
lt_landed:
    add r0, r0, #1          @ r0 = 4

    cmp r2, #3              @ 5 > 3
    bgt gt_landed
    add r1, r1, #1
gt_landed:
    add r0, r0, #1          @ r0 = 5

    @ BL: branch with link, calls subroutine
    bl my_func              @ lr = return address
    @ r2 = 42 on return

    @ BX: used inside my_func to return; verify return worked
    add r0, r0, #1          @ r0 = 6 (only if BX returned correctly)

    .word 0xE7FFDEAD        @ halt
    @ expected: r0=6, r1=0, r2=42

my_func:
    mov r2, #42
    bx lr                   @ return via BX
