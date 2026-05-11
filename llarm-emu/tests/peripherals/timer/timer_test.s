    .syntax unified
    .arch armv4t
    .arm
    .text
    .global _start

@ Exception vector table (must reside at 0x0)
_start:
    b       reset_handler       @ 0x00 Reset
    b       .                   @ 0x04 Undefined instruction
    b       .                   @ 0x08 SWI
    b       .                   @ 0x0C Prefetch abort
    b       .                   @ 0x10 Data abort
    nop                         @ 0x14 Reserved
    b       irq_handler         @ 0x18 IRQ
    b       .                   @ 0x1C FIQ

reset_handler:
    @ Enable UART (UARTCR = UARTEN|TXE|RXE = 0x0301)
    ldr     r0, =0x10000000
    ldr     r1, =0x0301
    str     r1, [r0, #0x30]

    @ Enable VIC source 4 (SP804 timer)
    ldr     r0, =0xFFFFF000
    mov     r1, #(1 << 4)
    str     r1, [r0, #0x010]    @ VICINTENABLE

    @ Configure SP804 Timer1:
    @   Load = 100 ticks, periodic 32-bit mode, interrupt enabled
    ldr     r0, =0x101E2000
    mov     r1, #100
    str     r1, [r0, #0x000]    @ Timer1Load
    mov     r1, #0xE2           @ TimerEn | Periodic | IntEnable | 32-bit
    str     r1, [r0, #0x008]    @ Timer1Control

    @ IRQs are already enabled (CPSR.I = 0 at reset)
spin:
    b       spin

irq_handler:
    @ Clear Timer1 interrupt
    ldr     r0, =0x101E2000
    str     r0, [r0, #0x00C]    @ Timer1IntClr (any write)

    @ Disable Timer1 so it does not fire again
    mov     r1, #0
    str     r1, [r0, #0x008]    @ Timer1Control

    @ Signal end-of-interrupt to VIC
    ldr     r0, =0xFFFFF000
    str     r0, [r0, #0x030]    @ VICVECTADDR

    @ Print success message via UART
    ldr     r0, =0x10000000
    ldr     r1, =msg
print_loop:
    ldrb    r2, [r1], #1
    cmp     r2, #0
    beq     halt
    str     r2, [r0]            @ UARTDR
    b       print_loop
halt:
    .word   0xE7FFDEAD

    .ltorg

msg:
    .asciz  "Timer IRQ fired.\n"
