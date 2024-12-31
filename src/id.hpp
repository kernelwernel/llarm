#pragma once

#include "types.hpp"

namespace id {
    enum class exception : u8 {
        RESET = 1,
        UNDEFINED,
        SWI, // software interrupt
        PREFETCH_ABORT, // instruction fetch memory abort
        DATA_ABORT, // data access memory abort
        IRQ, // interrupt
        FIQ, // fast interrupt
    };

    enum class exception_priority : u8  {
        RESET = 1,
        DATA_ABORT,
        FIQ,
        IRQ,
        PREFETCH_ABORT,
        UNDEFINED, 
        SWI = 6 // UNDEFINED and SWI both have the same priority level of 6
    };

    enum class cpsr : u8 {
        M = 0,   // processor mode bits
        T = 5,   // Thumb state bit
        F,   // FIQ disable bit
        I,   // IRQ disable bit
        A,   // imprecise data abort disable bit
        E,   // data endianness bit
        IT,  // if-then state bits
        GRE, // greater-than-or-equal-to bits (it's GE but there's a conflict with a different macro so yeah)
        DNM, // the "do not modify" bits
        J = 26,   // Java state bit
        Q,   // sticky overflow bit
        V,   // overflow bit
        C,   // carry/borrow/extend bit
        Z,   // zero bit
        N    // negative/less than bit
    };

    enum class reg : u8 {
        R0 = 1,
        R1,
        R2,
        R3,
        R4,
        R5,
        R6,
        R7,
        R8,
        R8_fiq,
        R9,
        R9_fiq,
        R10,
        R10_fiq,
        R11,
        R11_fiq,
        R12,
        IP = R12, // intra-procedure-call scratch register
        R12_fiq,
        R13,
        SP = R13, // stack pointer
        R13_fiq,
        R13_irq,
        R13_und,
        R13_svc,
        R13_abt,
        R14,
        LR = R14, // link register
        R14_fiq,
        R14_irq,
        R14_und,
        R14_svc,
        R14_abt,
        PC,
        R15 = PC, // program counter
        CPSR,
        SPSR_svc,
        SPSR_abt,
        SPSR_und,
        SPSR_irq,
        SPSR_fiq,
        CURRENT_SPSR
    };

    enum class instruction : u8 {
        UNKNOWN = 0,
        T_UNKNOWN = UNKNOWN,
        NOP,

        T_ADC,
        T_ADD1,
        T_ADD2,
        T_ADD3,
        T_ADD4,
        T_ADD5,
        T_ADD6,
        T_ADD7,
        T_SBC,
        T_SUB1,
        T_SUB2,
        T_SUB3,
        T_SUB4,
        T_MUL,
        T_AND,
        T_ASR1,
        T_ASR2,
        T_BIC,
        T_EOR,
        T_LSL1,
        T_LSL2,
        T_LSR1,
        T_LSR2,
        T_NEG,
        T_ORR,
        T_ROR,
        T_TST,
        T_CMN,
        T_CMP1,
        T_CMP2,
        T_CMP3,
        T_MOV1,
        T_MOV2,
        T_MOV3,
        T_MVN,
        T_B1,
        T_B2,
        T_BL,
        T_BLX1,
        T_BLX2,
        T_BX,
        T_NOP,
        T_BKPT,
        T_SWI,
        T_LDMIA,
        T_LDR1,
        T_LDR2,
        T_LDR3,
        T_LDR4,
        T_LDRB1,
        T_LDRB2,
        T_LDRH1,
        T_LDRH2,
        T_LDRSB,
        T_LDRSH,
        T_POP,
        T_PUSH,
        T_STMIA,
        T_STR1,
        T_STR2,
        T_STR3,
        T_STRB1,
        T_STRH1,
        T_STRH2,
    };

    enum class mode : u8 {
        USER = 1,   // normal program execution mode
        SUPERVISOR, // protected mode for the OS
        ABORT,      // implements virtual memory and/or memory protection
        UNDEFINED,  // supports software emulation of hardware coprocessors
        FIQ,        // high-speed data transfer or channel process
        IRQ,        // general purpose interrupt handling
        SYSTEM      // runs privileged OS tasks (ARMv4 and above)
    };

    enum class cond : u8 {
        EQ = 1,
        NE,
        CS,
        CC,
        MI,
        PL,
        VS,
        VC,
        HI,
        LS,
        GE,
        LT,
        GT,
        LE,
        AL,
        NV
    };

    enum class instruction_sets : u8 {
        ARM = 1,
        THUMB
    };

    enum class arguments : u8 {
        NULL_ARG = 0,
        HELP,
        VERBOSE,
        THUMB_ARG
    };

    enum class coprocessor : u8 {
        CP0 = 1,
        CP1,
        CP2,
        CP3,
        CP4,
        CP5,
        CP6,
        CP7,
        CP8,
        CP9,
        CP10, // vector floating point architecture (VFP)
        CP11, // vector floating point architecture (VFP)
        CP12,
        CP13,
        CP14,
        CP15  // system control
    };

    enum class cp_reg : u8 {
        CP15_R0 = 1,
        CP15_R1,
        CP15_R2,
        CP15_R3,
        CP15_R4,
        CP15_R5,
        CP15_R6,
        CP15_R7,
        CP15_R8,
        CP15_R9,
        CP15_R10,
        CP15_R11,
        CP15_R12,
        CP15_R13,
        CP15_R14,
        CP15_R15
        // more can be added here for different registers
    };


    enum class cp15 : u8 {
        NULL_REG = 0,
        R0_ID,
        R0_CACHE,

        R1_CONTROL,
        R1_M, // MMU or Protection Unit enable disable
        R1_A, // alignment fault checking
        R1_C, // unified cache
        R1_W, // write buffer
        R1_P, // 26-bit backwards-compatibility configurations (PROG32)
        R1_D, // 26-bit backwards-compatibility configurations (DATA32)
        R1_L, // abort model of the processor
        R1_B, // endianness of the memory system
        R1_S, // system protection bit
        R1_R, // ROM protection bit
        R1_F, // IMPLEMENTATION DEFINED
        R1_Z, // branch prediction
        R1_I, // instruction cache
        R1_V, // high vectors
        R1_RR, // cache strategy
        R1_L4, // ARMv5+ backwards compatibility

        R2_MMU,
        R2_MMU_TRANSLATION_BASE,
        R2_PU,
        R2_PU_C0,
        R2_PU_C1,
        R2_PU_C2,
        R2_PU_C3,
        R2_PU_C4,
        R2_PU_C5,
        R2_PU_C6,
        R2_PU_C7,
    
        R3_MMU,
        R3_MMU_D0,
        R3_MMU_D1,
        R3_MMU_D2,
        R3_MMU_D3,
        R3_MMU_D4,
        R3_MMU_D5,
        R3_MMU_D6,
        R3_MMU_D7,
        R3_MMU_D8,
        R3_MMU_D9,
        R3_MMU_D10,
        R3_MMU_D11,
        R3_MMU_D12,
        R3_MMU_D13,
        R3_MMU_D14,
        R3_MMU_D15,
        R3_PU,
        R3_PU_B0,
        R3_PU_B1,
        R3_PU_B2,
        R3_PU_B3,
        R3_PU_B4,
        R3_PU_B5,
        R3_PU_B6,
        R3_PU_B7,

        R4_MMU,
        R4_PU,

        R5_MMU,
        R5_MMU_DOMAIN,
        R5_MMU_STATUS,
        R5_PU,
        R5_PU_AP0,
        R5_PU_AP1,
        R5_PU_AP2,
        R5_PU_AP3,
        R5_PU_AP4,
        R5_PU_AP5,
        R5_PU_AP6,
        R5_PU_AP7,

        R6_MMU,
        R6_MMU_FAR, // fault address
        R6_PU,
        R6_PU_BASE_ADDRESS, 
        R6_PU_SIZE,
        R6_PU_E,  

        R7_CACHE,
        R7_CACHE_INDEX,
        R7_CACHE_SET,

        R8_MMU,
        R8_PU,

        R9_CACHE,
        R9_CACHE_INDEX,
        R9_CACHE_L,

        R10_MMU,
        R10_MMU_BASE,
        R10_MMU_VICTIM,
        R10_MMU_P,
        R10_PU,

        R11_RESERVED,
        
        R12_RESERVED,

        R13_PID,
        
        R14_RESERVED,

        R15_IMPL
    }


    enum class memory : u8 {
        NO_ACCESS_PERMISSION,
        READ_WRITE,
        READ
    };
}