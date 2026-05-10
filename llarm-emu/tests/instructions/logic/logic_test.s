    .syntax unified
    .arch armv5t
    .arm
    .text
    .global _start

    @ Logic instructions: AND, ORR, EOR, BIC, CLZ, TST, TEQ, CMP, CMN
    @ CLZ requires ARMv5T+
_start:
    @ AND: r1 = 0xFF & 0x0F = 0x0F
    mov r0, #0xFF
    and r1, r0, #0x0F

    @ ORR: r2 = 0xF0 | 0x0F = 0xFF
    mov r2, #0xF0
    orr r2, r2, #0x0F

    @ EOR: r3 = 0xFF ^ 0xAA = 0x55
    eor r3, r0, #0xAA

    @ BIC: r4 = 0xFF & ~0x0F = 0xF0  (bit clear)
    bic r4, r0, #0x0F

    @ CLZ: count leading zeros; bit 20 set → 11 leading zeros
    mov r5, #0x00100000
    clz r6, r5              @ r6 = 11

    @ TST: AND and set flags, no result stored
    @ 0xFF & 0x80 = 0x80, N=1 Z=0
    tst r0, #0x80

    @ TEQ: EOR and set flags, no result stored
    @ 0xFF ^ 0xFF = 0, Z=1
    mov r7, #0xFF
    teq r7, #0xFF

    @ CMP: subtract and set flags; 10 - 10 = 0, Z=1
    mov r8, #10
    cmp r8, #10

    @ CMN: add and set flags; -10 + 10 = 0, Z=1
    mvn r9, #9              @ r9 = ~9 = -10 (two's complement)
    cmn r9, #10

    .word 0xE7FFDEAD        @ halt
    @ expected: r1=0x0F, r2=0xFF, r3=0x55, r4=0xF0, r6=11
