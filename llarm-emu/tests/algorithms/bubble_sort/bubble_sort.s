    .syntax unified
    .arch armv4t
    .arm
    .text
    .global _start

    @ Bubble sort: sorts an 8-element array ascending in-place
    @ Sorted result: 3, 11, 12, 22, 25, 47, 64, 90
_start:
    ldr r0, =array          @ r0 = base address of array
    mov r1, #8              @ r1 = passes remaining

outer_loop:
    subs r1, r1, #1         @ passes--
    beq halt
    mov r2, #0              @ i = 0

inner_loop:
    cmp r2, r1              @ if i >= passes, next outer iteration
    bge outer_loop
    lsl r3, r2, #2          @ r3 = i * 4 (byte offset)
    ldr r4, [r0, r3]        @ r4 = array[i]
    add r6, r3, #4          @ r6 = (i+1) * 4
    ldr r5, [r0, r6]        @ r5 = array[i+1]
    cmp r4, r5
    ble no_swap
    str r5, [r0, r3]        @ array[i]   = smaller value
    str r4, [r0, r6]        @ array[i+1] = larger value
no_swap:
    add r2, r2, #1          @ i++
    b inner_loop

halt:
    .word 0xE7FFDEAD        @ halt

    .data
array:
    .word 64, 25, 12, 22, 11, 90, 3, 47
