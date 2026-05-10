    .syntax unified
    .arch armv5te
    .fpu vfp
    .arm
    .text
    .global _start

    @ VFP (Vector Floating Point) instructions:
    @   FLDS, FSTS, FADDS, FSUBS, FMULS, FDIVS, FSQRTS,
    @   FCMPS, FMSTAT, FABSS, FNEGS, FCPYS,
    @   FLDD, FSTD, FADDD, FSUBD, FMULD, FDIVD, FSQRTD,
    @   FMSR, FMRS, FSITOS, FTOSIS
_start:
    ldr r0, =float_vals     @ pointer to single-precision constants

    @ FLDS: load single-precision float from memory
    flds s0, [r0]           @ s0 = 3.0f
    flds s1, [r0, #4]       @ s1 = 4.0f
    flds s2, [r0, #8]       @ s2 = 9.0f

    @ FADDS: s3 = 3.0 + 4.0 = 7.0
    fadds s3, s0, s1

    @ FSUBS: s4 = 4.0 - 3.0 = 1.0
    fsubs s4, s1, s0

    @ FMULS: s5 = 3.0 * 4.0 = 12.0
    fmuls s5, s0, s1

    @ FDIVS: s6 = 12.0 / 4.0 = 3.0
    fdivs s6, s5, s1

    @ FSQRTS: s7 = sqrt(9.0) = 3.0
    fsqrts s7, s2

    @ FABSS: s8 = |s4| = 1.0 (s4 is already positive, but verify)
    fabss s8, s4

    @ FNEGS: s9 = -s0 = -3.0
    fnegs s9, s0

    @ FCPYS: s10 = s3 (copy 7.0)
    fcpys s10, s3

    @ FMSR: move ARM integer register to VFP single register
    @ Write the bit pattern for 2.0f (0x40000000) via r1
    ldr r1, =0x40000000     @ IEEE 754 for 2.0f
    fmsr s11, r1            @ s11 = 2.0f

    @ FMRS: move VFP single register to ARM integer register
    fmrs r2, s3             @ r2 = bit pattern of s3 (7.0f = 0x40E00000)

    @ FCMPS + FMSTAT: compare singles and transfer flags to CPSR
    fcmps s0, s1            @ 3.0 < 4.0  → N=0,Z=0,C=1,V=0 in FPSCR
    fmstat                  @ copy FPSCR[31:28] → CPSR[31:28]

    @ FSITOS: convert signed integer to single; s12 = float(-5)
    ldr r1, =float_neg5_bits
    fmsr s12, r1
    @ (s12 now holds bit pattern; use FSITOS to actually convert)
    ldr r1, =int_neg5
    fmsr s13, r1
    fsitos s14, s13         @ s14 = (float)(-5) = -5.0f

    @ FTOSIS: convert single to signed integer (truncate toward zero)
    ftosis s15, s3          @ s15 = (int)7.0 = 7

    @ Double precision
    ldr r0, =double_vals
    fldd d0, [r0]           @ d0 = 3.0
    fldd d1, [r0, #8]       @ d1 = 4.0

    faddd d2, d0, d1        @ d2 = 7.0
    fmuld d3, d0, d1        @ d3 = 12.0
    fsqrtd d4, d1           @ d4 = sqrt(4.0) = 2.0

    ldr r0, =double_out
    fstd d2, [r0]           @ store 7.0 to memory

    .word 0xE7FFDEAD        @ halt

    .data
    .align 2
float_vals:
    .float 3.0              @ s0
    .float 4.0              @ s1
    .float 9.0              @ s2

int_neg5:
    .word -5

float_neg5_bits:
    .float -5.0

    .align 3                @ 8-byte aligned for double
double_vals:
    .double 3.0             @ d0
    .double 4.0             @ d1

double_out:
    .space 8
