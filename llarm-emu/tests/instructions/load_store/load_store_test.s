    .syntax unified
    .arch armv4t
    .arm
    .text
    .global _start

    @ Load/Store instructions: LDR, STR, LDRB, STRB, LDRH, STRH,
    @   LDRSB, LDRSH, LDM, STM, SWP, SWPB
_start:
    ldr r0, =buffer         @ r0 = base address of scratch buffer

    @ STR / LDR: 32-bit word
    ldr r1, =0xDEADBEEF
    str r1, [r0]            @ mem[base+0] = 0xDEADBEEF
    ldr r2, [r0]            @ r2 = 0xDEADBEEF

    @ STR with immediate offset / LDR pre-indexed
    ldr r1, =0x12345678
    str r1, [r0, #4]        @ mem[base+4] = 0x12345678
    ldr r3, [r0, #4]        @ r3 = 0x12345678

    @ STRB / LDRB: byte (zero-extended on load)
    mov r1, #0xAB
    strb r1, [r0, #8]       @ mem[base+8] = 0xAB
    ldrb r4, [r0, #8]       @ r4 = 0x000000AB

    @ STRH / LDRH: halfword (zero-extended on load)
    ldr r1, =0x1234
    strh r1, [r0, #10]      @ mem[base+10] = 0x1234
    ldrh r5, [r0, #10]      @ r5 = 0x00001234

    @ LDRSB: load signed byte (sign-extended)
    mov r1, #0xFF           @ 0xFF = -1 when sign-extended
    strb r1, [r0, #12]
    ldrsb r6, [r0, #12]     @ r6 = 0xFFFFFFFF

    @ LDRSH: load signed halfword (sign-extended)
    ldr r1, =0x8000         @ 0x8000 = -32768 when sign-extended
    strh r1, [r0, #14]
    ldrsh r7, [r0, #14]     @ r7 = 0xFFFF8000

    @ STM / LDM: store and load multiple registers
    mov r1, #10
    mov r2, #20
    mov r3, #30
    add r8, r0, #16         @ r8 = base+16
    stm r8, {r1, r2, r3}    @ mem[base+16..24] = 10, 20, 30
    mov r1, #0
    mov r2, #0
    mov r3, #0
    ldm r8, {r1, r2, r3}    @ r1=10, r2=20, r3=30

    @ SWP: atomically swap register and memory word
    add r9, r0, #28         @ r9 = base+28
    ldr r1, =0xCAFEBABE
    str r1, [r9]            @ mem[base+28] = 0xCAFEBABE
    ldr r2, =0x0000FEED
    swp r3, r2, [r9]        @ r3 = old mem (0xCAFEBABE), mem = 0x0000FEED

    @ SWPB: atomically swap byte
    mov r1, #0xAA
    strb r1, [r9, #4]       @ mem[base+32] = 0xAA
    mov r2, #0x55
    add r10, r9, #4
    swpb r4, r2, [r10]      @ r4 = 0xAA, mem[base+32] = 0x55

    .word 0xE7FFDEAD        @ halt
    @ expected: r2=0xDEADBEEF, r3=0x12345678, r4=0xAB, r5=0x1234
    @            r6=0xFFFFFFFF, r7=0xFFFF8000
    @            r1=10, r2=20, r3=0xCAFEBABE (after swp)

    .data
    .align 2
buffer:
    .space 64
