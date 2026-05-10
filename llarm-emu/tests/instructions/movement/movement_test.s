    .syntax unified
    .arch armv4t
    .arm
    .text
    .global _start

    @ Movement instructions: MOV, MVN, MRS, MSR
_start:
    @ MOV immediate
    mov r0, #42             @ r0 = 42

    @ MOV register with shift
    mov r1, r0, lsl #1      @ r1 = 84

    @ MOV with rotate (ARM rotated immediate: 0xFF rotated 24 = 0xFF000000)
    mov r2, #0xFF000000     @ r2 = 0xFF000000

    @ MVN: bitwise NOT of immediate
    mvn r3, #0              @ r3 = 0xFFFFFFFF

    @ MVN register
    mvn r4, r0              @ r4 = ~42 = 0xFFFFFFD5

    @ MRS: read CPSR into general-purpose register
    mrs r5, cpsr            @ r5 = current CPSR value

    @ MSR: write to CPSR flags field only (safe in any mode)
    msr cpsr_f, #0xF0000000 @ set N, Z, C, V flags
    mrs r6, cpsr            @ r6 should have bits[31:28] = 0xF

    @ Clear the flags we set
    msr cpsr_f, #0x00000000 @ clear N, Z, C, V
    mrs r7, cpsr            @ r7 flags bits should be 0

    .word 0xE7FFDEAD        @ halt
    @ expected: r0=42, r1=84, r2=0xFF000000, r3=0xFFFFFFFF
    @            r6[31:28]=0xF, r7[31:28]=0x0
