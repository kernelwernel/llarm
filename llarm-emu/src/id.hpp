#pragma once

#include "shared/types.hpp"

namespace id {
    enum class exception_mode : u8 {
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
        GE, // greater-than-or-equal-to bits
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
        R15, // program counter (this is not the same as R15 due to 26-bit arch restraints)
        CPSR,
        SPSR,
        SPSR_svc,
        SPSR_abt,
        SPSR_und,
        SPSR_irq,
        SPSR_fiq,
    };

    enum class mode : u8 {
        USER = 1,   // normal program execution mode
        SUPERVISOR, // protected mode for the OS
        ABORT,      // implements virtual memory and/or memory protection
        UNDEFINED,  // supports software emulation of hardware coprocessors
        FIQ,        // high-speed data transfer or channel process
        IRQ,        // general purpose interrupt handling
        SYSTEM,     // runs privileged OS tasks (ARMv4 and above)
        USER_26,
        FIQ_26,
        IRQ_26,
        SUPERVISOR_26
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
        THUMB,
        JAZELLE
    };

    enum class arguments : u8 {
        NULL_ARG = 0,
        HELP,
        VERBOSE,
        THUMB_ARG
    };

    enum class cp : u8 {
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

    // coprocessor registers and bits
    enum class cp15 : u16 {
        UNKNOWN = 0,
        R0_ID, // DO NOT MODIFY/REARRANGE SINCE IT'S USED AS A STARTING INDEX
        R0_ID_REVISION,
        R0_ID_IMPLEMENTOR,
        R0_ID_PPN, // PPN = primary part number
        R0_ID_PRE7_ID,
        R0_ID_PRE7_REVISION,
        R0_ID_7_REVISION,
        R0_ID_7_PPN,
        R0_ID_7_PPN_TOP,
        R0_ID_7_VARIANT,
        R0_ID_7_A,
        R0_ID_7_IMPLEMENTOR,
        R0_ID_POST7_IMPLEMENTOR,
        R0_ID_POST7_VARIANT,
        R0_ID_POST7_ARCHITECTURE,
        R0_ID_POST7_PPN,
        R0_ID_POST7_PPN_TOP,
        R0_ID_POST7_REVISION,

        R0_CACHE,
        R0_CACHE_CTYPE,
        R0_CACHE_S,
        R0_CACHE_DSIZE,
        R0_CACHE_DSIZE_LEN,
        R0_CACHE_DSIZE_M,
        R0_CACHE_DSIZE_ASSOC,
        R0_CACHE_DSIZE_SIZE,
        R0_CACHE_ISIZE,
        R0_CACHE_ISIZE_LEN,
        R0_CACHE_ISIZE_M,
        R0_CACHE_ISIZE_ASSOC,
        R0_CACHE_ISIZE_SIZE,

        R1,
        R1_M, // MMU or MPU enable/disable
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

        R2,
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

        R3,
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
        R3_PU_INST,
        R3_PU_INST_B0,
        R3_PU_INST_B1,
        R3_PU_INST_B2,
        R3_PU_INST_B3,
        R3_PU_INST_B4,
        R3_PU_INST_B5,
        R3_PU_INST_B6,
        R3_PU_INST_B7,
        R3_PU_DATA,
        R3_PU_DATA_B0,
        R3_PU_DATA_B1,
        R3_PU_DATA_B2,
        R3_PU_DATA_B3,
        R3_PU_DATA_B4,
        R3_PU_DATA_B5,
        R3_PU_DATA_B6,
        R3_PU_DATA_B7,

        R4,
        R4_MMU,
        R4_PU,

        R5,
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
        R5_PU_INST,
        R5_PU_INST_AP0,
        R5_PU_INST_AP1,
        R5_PU_INST_AP2,
        R5_PU_INST_AP3,
        R5_PU_INST_AP4,
        R5_PU_INST_AP5,
        R5_PU_INST_AP6,
        R5_PU_INST_AP7,
        R5_PU_DATA,
        R5_PU_DATA_AP0,
        R5_PU_DATA_AP1,
        R5_PU_DATA_AP2,
        R5_PU_DATA_AP3,
        R5_PU_DATA_AP4,
        R5_PU_DATA_AP5,
        R5_PU_DATA_AP6,
        R5_PU_DATA_AP7,

        R6_MMU,
        R6_MMU_FAR, // fault address
        R6_PU_0_BASE_ADDRESS, 
        R6_PU_1_BASE_ADDRESS, 
        R6_PU_2_BASE_ADDRESS, 
        R6_PU_3_BASE_ADDRESS, 
        R6_PU_4_BASE_ADDRESS, 
        R6_PU_5_BASE_ADDRESS, 
        R6_PU_6_BASE_ADDRESS, 
        R6_PU_7_BASE_ADDRESS, 
        R6_PU_0_SIZE,
        R6_PU_1_SIZE,
        R6_PU_2_SIZE,
        R6_PU_3_SIZE,
        R6_PU_4_SIZE,
        R6_PU_5_SIZE,
        R6_PU_6_SIZE,
        R6_PU_7_SIZE,
        R6_PU_0_E,  
        R6_PU_1_E,  
        R6_PU_2_E,  
        R6_PU_3_E,  
        R6_PU_4_E,  
        R6_PU_5_E,  
        R6_PU_6_E,  
        R6_PU_7_E,  
        R6_PU_0,
        R6_PU_1,
        R6_PU_2,
        R6_PU_3,
        R6_PU_4,
        R6_PU_5,
        R6_PU_6,
        R6_PU_7,

        R6_PU_INST_0_BASE_ADDRESS, 
        R6_PU_INST_1_BASE_ADDRESS, 
        R6_PU_INST_2_BASE_ADDRESS, 
        R6_PU_INST_3_BASE_ADDRESS, 
        R6_PU_INST_4_BASE_ADDRESS, 
        R6_PU_INST_5_BASE_ADDRESS, 
        R6_PU_INST_6_BASE_ADDRESS, 
        R6_PU_INST_7_BASE_ADDRESS, 
        R6_PU_INST_0_SIZE,
        R6_PU_INST_1_SIZE,
        R6_PU_INST_2_SIZE,
        R6_PU_INST_3_SIZE,
        R6_PU_INST_4_SIZE,
        R6_PU_INST_5_SIZE,
        R6_PU_INST_6_SIZE,
        R6_PU_INST_7_SIZE,
        R6_PU_INST_0_E,  
        R6_PU_INST_1_E,  
        R6_PU_INST_2_E,  
        R6_PU_INST_3_E,  
        R6_PU_INST_4_E,  
        R6_PU_INST_5_E,  
        R6_PU_INST_6_E,  
        R6_PU_INST_7_E,  
        R6_PU_INST_0,
        R6_PU_INST_1,
        R6_PU_INST_2,
        R6_PU_INST_3,
        R6_PU_INST_4,
        R6_PU_INST_5,
        R6_PU_INST_6,
        R6_PU_INST_7,
        
        R6_PU_DATA_0_BASE_ADDRESS, 
        R6_PU_DATA_1_BASE_ADDRESS, 
        R6_PU_DATA_2_BASE_ADDRESS, 
        R6_PU_DATA_3_BASE_ADDRESS, 
        R6_PU_DATA_4_BASE_ADDRESS, 
        R6_PU_DATA_5_BASE_ADDRESS, 
        R6_PU_DATA_6_BASE_ADDRESS, 
        R6_PU_DATA_7_BASE_ADDRESS, 
        R6_PU_DATA_0_SIZE,
        R6_PU_DATA_1_SIZE,
        R6_PU_DATA_2_SIZE,
        R6_PU_DATA_3_SIZE,
        R6_PU_DATA_4_SIZE,
        R6_PU_DATA_5_SIZE,
        R6_PU_DATA_6_SIZE,
        R6_PU_DATA_7_SIZE,
        R6_PU_DATA_0_E,  
        R6_PU_DATA_1_E,  
        R6_PU_DATA_2_E,  
        R6_PU_DATA_3_E,  
        R6_PU_DATA_4_E,  
        R6_PU_DATA_5_E,  
        R6_PU_DATA_6_E,  
        R6_PU_DATA_7_E,  
        R6_PU_DATA_0,
        R6_PU_DATA_1,
        R6_PU_DATA_2,
        R6_PU_DATA_3,
        R6_PU_DATA_4,
        R6_PU_DATA_5,
        R6_PU_DATA_6,
        R6_PU_DATA_7,

        R7,
        R7_CACHE_INDEX,
        R7_CACHE_SET,

        R8_MMU, // write-only functionalities
        R8_PU, // reserved

        R9,
        R9_CACHE_INDEX,
        R9_CACHE_L,

        R10,
        R10_MMU,
        R10_MMU_BASE,
        R10_MMU_VICTIM,
        R10_MMU_P,
        R10_PU,

        R11,
        R12,
        R13,
        R13_PID,
        R14,
        R15 // DO NOT MODIFY/REARRANGE SINCE IT'S USED AS AN ENDING INDEX
    };


    enum class memory : u8 {
        NO_ACCESS_PERMISSION = 1,
        READ_WRITE,
        READ
    };


    enum class first_level : u8 {
        FAULT = 1, 
        COARSE, 
        FINE,
        SECTION
    };

    enum class second_level : u8 {
        FAULT = 1, 
        LARGE,
        SMALL,
        TINY
    };

    enum class access_perm : u8 {
        NO_ACCESS,
        READ_ONLY,
        READ_WRITE,
        UNPREDICTABLE,
    };

    enum class access_type : u8 {
        READ,
        WRITE,
        READ_WRITE,
        INSTRUCTION_FETCH
    };

    enum class access_domain : u8 {
        NO_ACCESS,
        CLIENT,
        RESERVED,
        MANAGER
    };

    enum class aborts : u8 {
        NO_ABORT,
        ALIGNMENT,
        ABORT,
        PREFETCH_ABORT,
        ADDRESS_EXCEPTION,
        TRANSLATION,
        SECTION_TRANSLATION,
        PAGE_TRANSLATION,
        PAGE_DOMAIN,
        SUB_PAGE_PERMISSION,
        SECTION_DOMAIN,
        SECTION_PERMISSION
    };

    enum class pu_region : u8 { // pu = protection unit
        REGION_0 = 0,
        REGION_1,
        REGION_2,
        REGION_3,
        REGION_4,
        REGION_5,
        REGION_6,
        REGION_7
    };

    enum class vfp_exception : u8 {
        INVALID_OPERATION,
        DIV_BY_ZERO,
        OVERFLOW,
        UNDERFLOW,
        INEXACT
    };

    enum class vfp_reg : u8 {
        S0,
        S1,
        S2,
        S3,
        S4,
        S5, 
        S6,
        S7, 
        S8, 
        S9, 
        S10,
        S11, 
        S12, 
        S13, 
        S14,
        S15,
        S16, 
        S17, 
        S18, 
        S19,
        S20,
        S21,
        S22,
        S23,
        S24,
        S25,
        S26,
        S27,
        S28,
        S29,
        S30,
        S31,
        D0,
        D1,
        D2,
        D3,
        D4,
        D5, 
        D6,
        D7, 
        D8, 
        D9, 
        D10,
        D11, 
        D12, 
        D13, 
        D14,
        D15,
        FPSID,
        FPSID_IMPLEMENTOR,
        FPSID_SW,
        FPSID_FORMAT,
        FPSID_SNG,
        FPSID_ARCH,
        FPSID_PART_NUM,
        FPSID_VARIANT,
        FPSID_REVISION,
        FPSCR,
        FPSCR_N,
        FPSCR_Z,
        FPSCR_C,
        FPSCR_V,
        FPSCR_FZ,
        FPSCR_RMODE,
        FPSCR_STRIDE,
        FPSCR_LEN,
        FPSCR_IXE,
        FPSCR_UFE,
        FPSCR_OFE,
        FPSCR_DZE,
        FPSCR_IOE,
        FPSCR_IXC,
        FPSCR_UFC,
        FPSCR_OFC,
        FPSCR_DZC,
        FPSCR_IOC,
        FPEXC,
        FPEXC_EX,
        FPEXC_EN
    };

    enum class product_family : u8 {
        UNKNOWN = 0,
        ARM1,
        ARM2,
        ARM2aS,
        ARM6,
        ARM7,
        ARM7T,
        ARM7EJ,
        ARM8,
        ARM9T,
        ARM9E,
        ARM10E,
        ARM11,
        SecurCore,
        CORTEX_M,
        CORTEX_R,
        CORTEX_A_32,
        CORTEX_A_64,
        CORTEX_X,
        NEOVERSE,
    };

    enum class arch : u8 {
        UNKNOWN = 0,
        ARMv1,
        ARMv2,
        ARMv3,
        ARMv4,
        ARMv5,
        ARMv6,
        ARMv7,
        ARMv8,
        ARMv9
    };

    enum class specific_arch : u8 {
        UNKNOWN = 0,
        ARMv1,
        ARMv2,
        ARMv2a,
        ARMv3,
        ARMv4,
        ARMv4T,
        ARMv5, // assuming this exists, idk
        ARMv5T, // same
        ARMv5TE,
        ARMv5TEJ,
        ARMv6,
        ARMv6T2,
        ARMv6Z,
        ARMv6K,
        ARMv6_M,
        ARMv7_A,
        ARMv7_M,
        ARMv7_R,
        ARMv7E_M,
        ARMv8_A,
        ARMv8_R,
        ARMv8_M_BASELINE,
        ARMv8_M_MAINLINE,
        ARMv8_1_M_MAINLINE,
        ARMv8_2_A,
        ARMv8_3_A,
        ARMv8_4_A, // third party
        ARMv8_5_A, // third party
        ARMv8_6_A, // third party
        ARMv9_A,
        ARMv9_2_A,
    };

    enum class processor : u8 {
        // TODO  (https://en.wikipedia.org/wiki/List_of_ARM_processors)
        // https://sourceware.org/binutils/docs/as/ARM-Options.html
        UNKNOWN = 0,
        ARM1,
        ARM2,
        ARM250,
        ARM3,
        ARM60,
        ARM600,
        ARM610,
        ARM620, // where?
        ARM700,
        ARM710,
        ARM710a,
        ARM7TDMI_S,
        ARM710T,
        ARM720T,
        ARM740T,
        ARM7EJ_S,
        ARM810,
        ARM9TDMI,
        ARM920T,
        ARM922T,
        ARM940T,
        ARM946E_S,
        ARM966E_S,
        ARM968E_S,
        ARM926EJ_S,
        ARM996HS,
        ARM1020E,
        ARM1022E,
        ARM1026EJ_S,
        ARM1136JF_S,
        ARM1156T2F_S,
        ARM1176JZF_S,
        ARM11MPCore,
        SC000,
        SC100,
        SC300,
        Cortex_M0,
        Cortex_M0_PLUS,
        Cortex_M1,
        Cortex_M3,
        Cortex_M4,
        Cortex_M7,
        Cortex_M23,
        Cortex_M33,
        Cortex_M35P,
        Cortex_M52,
        Cortex_M55,
        Cortex_M85,
        Cortex_R4,
        Cortex_R5,
        Cortex_R7,
        Cortex_R8,
        Cortex_R52,
        Cortex_R52_PLUS,
        Cortex_R82,
        Cortex_A5,
        Cortex_A7,
        Cortex_A8,
        Cortex_A9,
        Cortex_A12,
        Cortex_A15,
        Cortex_A17,
        Cortex_A32,
        Cortex_A34,
        Cortex_A35,
        Cortex_A53,
        Cortex_A57,
        Cortex_A72,
        Cortex_A73,
        Cortex_A55,
        Cortex_A65,
        Cortex_A65AE,
        Cortex_A75,
        Cortex_A76,
        Cortex_A76AE,
        Cortex_A77,
        Cortex_A78,
        Cortex_A78AE,
        Cortex_A78C,
        Cortex_A510,
        Cortex_A710,
        Cortex_A715,
        Cortex_A520,
        Cortex_A720,
        Cortex_A725,
        Cortex_X1,
        Cortex_X2,
        Cortex_X3,
        Cortex_X4,
        Cortex_X925,
        Neoverse_N1,
        Neoverse_E1,
        Neoverse_V1,
        Neoverse_N2,
        Neoverse_V2,
        Neoverse_N3,
        Neoverse_V3,

        // custom processors intended for specific use cases 
        // if no real-world ARM processor is being used or set

        LLARM_FAST,     // meant to be as fast as possible (no mmu,mpu and cache because it takes longer to emulate those)
        LLARM_MINIMAL,  // the minimal working example (no mmu/mpu, no cache, no vfp, no dsp, no thumb, etc...)
        LLARM_FULL,     // all features are present
        LLARM_DEFAULT,  // default options for stability reasons
    };

    enum class implementor : u8 {
        ARM = 1,
        BRCM, // broadcom 
        DEC, // digital equipment corporation
        MOTOROLA,
        QUALCOMM,
        MARVELL, 
        INTEL,
        LLARM // custom
    };

    enum class error : u8 {
        UNKNOWN = 0,
        REG_26_NO_COMPAT
    };

    enum class warning : u8 {
        UNKNOWN = 0,
        SBZ, 
        UNPREDICTABLE,
        DNM
    };

    enum class dev_warning : u8 {
        UNKNOWN = 0,
        TRIM_IS_ALL_ZERO
    };

    enum class dev_error : u8 {
        UNKNOWN = 0,
        TRIM_IS_ALL_ZERO
    };
}