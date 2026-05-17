    .syntax unified
    .arch armv4t
    .text
    .global _start

@ ARM startup: set up stack, call Thumb fibonacci, halt on return
    .arm
_start:
    mov     sp, #0x7000         @ stack within 32KB RAM
    ldr     lr, =_halt          @ return address (ARM mode, bit 0 = 0)
    ldr     r0, =fib_main + 1   @ Thumb entry with interworking bit set
    bx      r0                  @ switch to Thumb, jump to fib_main

_halt:
    .word   0xE7FFDEAD
    .ltorg

@ Thumb fibonacci: compute fib(10) = 55 iteratively, result in r0
    .thumb
    .thumb_func
fib_main:
    movs    r0, #0              @ prev = 0
    movs    r1, #1              @ curr = 1
    movs    r2, #0              @ i = 0
    movs    r3, #10             @ n = 10
.L_loop:
    cmp     r2, r3
    bge     .L_done
    movs    r4, r1              @ tmp = curr
    adds    r1, r0, r1          @ curr = prev + curr
    movs    r0, r4              @ prev = tmp
    adds    r2, r2, #1          @ i++
    b       .L_loop
.L_done:
    bx      lr                  @ return to ARM _halt, r0 = 55
