    .syntax unified
    .arch armv4t
    .arm
    .text
    .global _start

    @ Math instructions: ADD, ADC, SUB, SBC, RSB, RSC
    @ All results verifiable by inspecting registers at halt
_start:
    @ ADD: r2 = 15 + 10 = 25
    mov r0, #15
    mov r1, #10
    add r2, r0, r1

    @ ADC: add with carry; force C=1 via overflow, then adc
    mov r0, #0x7FFFFFFF
    adds r0, r0, r0         @ 0x7FFFFFFF + 0x7FFFFFFF overflows, C=1
    adc r3, r2, r1          @ r3 = 25 + 10 + 1 = 36

    @ SUB: r4 = 25 - 10 = 15
    mov r2, #25
    sub r4, r2, r1          @ r4 = 15

    @ SBC: subtract with carry; C=1 from earlier adds means borrow=0
    @ first set C=1 cleanly: CMP sets C=1 when no borrow (Rn >= operand)
    cmp r2, #0              @ 25 >= 0, so C=1 (no borrow)
    sbc r5, r2, r1          @ r5 = 25 - 10 - (1-C) = 25 - 10 - 0 = 15

    @ RSB: r6 = 100 - r2 = 75  (reverse subtract: Rd = operand - Rn)
    rsb r6, r2, #100        @ r6 = 100 - 25 = 75

    @ RSC: reverse subtract with carry; C=1 from cmp above
    cmp r2, #0              @ C=1
    rsc r7, r1, #20         @ r7 = 20 - 10 - (1-C) = 20 - 10 - 0 = 10

    .word 0xE7FFDEAD        @ halt
    @ expected: r3=36, r4=15, r5=15, r6=75, r7=10
