    .syntax unified
    .arch armv4t
    .arm
    .text
    .global _start

    @ Multiply instructions: MUL, MLA, UMULL, SMULL, UMLAL, SMLAL
    @ ARMv4 constraint: in MUL/MLA, Rd != Rm
_start:
    @ MUL: r0 = 6 * 7 = 42
    mov r1, #6
    mov r2, #7
    mul r0, r1, r2          @ r0 = 42  (rd=r0 != rm=r1 ✓)

    @ MLA: r3 = 6 * 7 + 10 = 52
    mov r4, #10
    mla r3, r1, r2, r4      @ r3 = 52  (rd=r3 != rm=r1 ✓)

    @ UMULL: 64-bit unsigned multiply: 0xFFFFFFFF * 2 = 0x1FFFFFFFE
    mvn r5, #0              @ r5 = 0xFFFFFFFF
    mov r6, #2
    umull r7, r8, r5, r6    @ r8:r7 = 0x1_FFFFFFFE
    @ expected: r7 = 0xFFFFFFFE, r8 = 0x1

    @ SMULL: 64-bit signed multiply: -5 * 6 = -30 = 0xFFFFFFE2
    mvn r1, #4              @ r1 = ~4 = -5
    mov r2, #6
    smull r3, r4, r1, r2    @ r4:r3 = -30
    @ expected: r3 = 0xFFFFFFE2, r4 = 0xFFFFFFFF (sign-extended)

    @ UMLAL: 64-bit unsigned multiply-accumulate: 3*4 + 100 = 112
    mov r1, #3
    mov r2, #4
    mov r5, #100
    mov r6, #0              @ r6:r5 = 100
    umlal r5, r6, r1, r2    @ r6:r5 += 12  → r5 = 112, r6 = 0

    @ SMLAL: 64-bit signed multiply-accumulate: -5*6 + 50 = 20
    mvn r1, #4              @ r1 = -5
    mov r2, #6
    mov r3, #50
    mov r4, #0              @ r4:r3 = 50
    smlal r3, r4, r1, r2    @ r4:r3 += -30  → r3 = 20, r4 = 0

    .word 0xE7FFDEAD        @ halt
    @ expected: r0=42, r3(MLA)=52, r7=0xFFFFFFFE, r8=1
    @            r3(SMLAL)=20, r5(UMLAL)=112
