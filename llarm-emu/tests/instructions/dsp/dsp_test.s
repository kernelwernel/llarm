    .syntax unified
    .arch armv5te
    .arm
    .text
    .global _start

    @ DSP extension instructions (ARMv5TE): QADD, QSUB, QDADD, QDSUB,
    @   SMLABT, SMULBB, SMULWB, LDRD, STRD
_start:
    @ QADD: signed saturating add; 100 + 200 = 300 (no saturation)
    mov r0, #100
    mov r1, #200
    qadd r2, r0, r1         @ r2 = 300

    @ QADD saturation: 0x7FFFFFFF + 1 clamps to 0x7FFFFFFF
    ldr r0, =0x7FFFFFFF
    mov r1, #1
    qadd r3, r0, r1         @ r3 = 0x7FFFFFFF (saturated)

    @ QSUB: signed saturating subtract; 50 - 30 = 20
    mov r0, #50
    mov r1, #30
    qsub r4, r0, r1         @ r4 = 20

    @ QDADD: Rd = Rm + sat(2*Rn); 10 + sat(2*5) = 20
    mov r0, #10
    mov r1, #5
    qdadd r5, r0, r1        @ r5 = 20

    @ QDSUB: Rd = Rm - sat(2*Rn); 20 - sat(2*4) = 12
    mov r0, #20
    mov r1, #4
    qdsub r6, r0, r1        @ r6 = 12

    @ SMLABT: Rd = Rm[15:0] * Rs[31:16] + Rn
    @ r0[15:0]=2, r1[31:16]=5, r2(accum)=10  → 2*5+10 = 20
    ldr r0, =0x00030002     @ lo=2, hi=3
    ldr r1, =0x00050004     @ lo=4, hi=5
    mov r2, #10
    smlabt r3, r0, r1, r2   @ r3 = 2*5 + 10 = 20

    @ SMULBB: Rd = Rm[15:0] * Rs[15:0]
    @ r0[15:0]=2, r1[15:0]=4  → 2*4 = 8
    smulbb r4, r0, r1       @ r4 = 8

    @ SMULWB: Rd = (Rm * Rs[15:0]) >> 16
    @ 0x10000 * 3 = 196608 >> 16 = 3
    ldr r0, =0x00010000     @ 65536
    ldr r1, =0x00000003
    smulwb r5, r0, r1       @ r5 = 3

    @ LDRD / STRD: load/store doubleword (Rd must be even-numbered)
    ldr r0, =pair_data
    ldrd r6, r7, [r0]       @ r6 = pair_data[0], r7 = pair_data[1]
    ldr r0, =pair_out
    strd r6, r7, [r0]       @ store them back out

    .word 0xE7FFDEAD        @ halt
    @ expected: r2=300, r3=0x7FFFFFFF, r4=20(qsub), r5=20(qdadd), r6=12
    @            r3(smlabt)=20, r4(smulbb)=8, r5(smulwb)=3
    @            r6=0x11111111, r7=0x22222222 (from pair_data)

    .data
    .align 3                @ 8-byte aligned for LDRD
pair_data:
    .word 0x11111111, 0x22222222
pair_out:
    .space 8
