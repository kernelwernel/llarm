    .syntax unified
    .arch armv4t
    .arm
    .text
    .global _start

    @ Sum of array: adds all elements of an 8-element array
    @ Expected result: 360 in r0 on halt
_start:
    ldr r1, =array          @ r1 = &array[0]
    mov r2, #8              @ r2 = array length
    mov r0, #0              @ r0 = sum = 0
    mov r3, #0              @ r3 = i = 0

sum_loop:
    cmp r3, r2
    bge sum_done
    ldr r4, [r1, r3, lsl #2]   @ r4 = array[i]
    add r0, r0, r4              @ sum += array[i]
    add r3, r3, #1              @ i++
    b sum_loop

sum_done:
    .word 0xE7FFDEAD        @ halt  (r0 = 360)

    .data
array:
    .word 10, 20, 30, 40, 50, 60, 70, 80
