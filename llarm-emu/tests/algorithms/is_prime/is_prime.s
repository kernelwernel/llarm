    .syntax unified
    .arch armv4t
    .arm
    .text
    .global _start

    @ Primality test via trial division (no hardware divide on ARMv4T)
    @ Candidate: 97  ->  r0 = 1 (prime) on halt
    @ Change the immediate in _start to test other values
_start:
    mov r0, #97             @ candidate n = 97

    cmp r0, #2
    blt not_prime           @ n < 2: not prime
    beq is_prime            @ n == 2: prime

    tst r0, #1              @ test LSB
    beq not_prime           @ even (and > 2): not prime

    mov r1, #3              @ first odd divisor to try

trial_loop:
    mul r2, r1, r1          @ r2 = divisor^2  (ARMv4: rd != rm, r2 != r1)
    cmp r2, r0              @ if divisor^2 > n, n is prime
    bgt is_prime

    @ compute n mod divisor by repeated subtraction
    mov r2, r0              @ r2 = n
mod_loop:
    cmp r2, r1
    blt mod_done
    sub r2, r2, r1          @ r2 -= divisor
    b mod_loop

mod_done:
    cmp r2, #0              @ remainder == 0 means divisible
    beq not_prime

    add r1, r1, #2          @ next odd divisor
    b trial_loop

is_prime:
    mov r0, #1              @ r0 = 1 (prime)
    .word 0xE7FFDEAD        @ halt

not_prime:
    mov r0, #0              @ r0 = 0 (not prime)
    .word 0xE7FFDEAD        @ halt
