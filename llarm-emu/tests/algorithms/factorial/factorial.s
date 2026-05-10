    .syntax unified
    .arch armv4t
    .arm
    .text
    .global _start

    @ Iterative factorial: computes 10! = 3628800
    @ Result in r0 on halt
_start:
    mov r0, #10             @ n = 10
    mov r1, #1              @ accumulator = 1

factorial_loop:
    cmp r0, #1
    ble factorial_done
    mul r1, r0, r1          @ accumulator *= n  (ARMv4: rd != rm)
    sub r0, r0, #1          @ n--
    b factorial_loop

factorial_done:
    mov r0, r1              @ r0 = 3628800
    .word 0xE7FFDEAD        @ halt
