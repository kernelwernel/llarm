    .syntax unified
    .arch armv4t
    .arm
    .text
    .global _start

_start:
    ldr r0, =0x10000000 @ UART base

    @ Enable UART: set UARTEN (bit 0) in UARTCR.
    @ TXE (bit 8) and RXE (bit 9) are already set at reset (0x0300).
    ldr r1, =0x0301
    str r1, [r0, #0x30]

    @ Print the test string byte by byte.
    adr r2, msg
1:
    ldrb r3, [r2], #1
    cmp r3, #0
    beq 2f
    str r3, [r0] @ write to UARTDR (offset 0x000)
    b 1b
2:
    b 2b @ halt

msg:
    .asciz  "Hello, UART!\n"