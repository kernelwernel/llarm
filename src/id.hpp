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

    enum class arm_instruction : u8 {
        UNKNOWN = 0,
        NOP
    }

    enum class thumb_instruction : u8 {
        UNKNOWN = 0,
        ADC,
        ADD1,
        ADD2,
        ADD3,
        ADD4,
        ADD5,
        ADD6,
        ADD7,
        SBC,
        SUB1,
        SUB2,
        SUB3,
        SUB4,
        MUL,
        AND,
        ASR1,
        ASR2,
        BIC,
        EOR,
        LSL1,
        LSL2,
        LSR1,
        LSR2,
        NEG,
        ORR,
        ROR,
        TST,
        CMN,
        CMP1,
        CMP2,
        CMP3,
        MOV1,
        MOV2,
        MOV3,
        MVN,
        B1,
        B2,
        BL,
        BLX1,
        BLX2,
        BX,
        NOP,
        BKPT,
        SWI,
        LDMIA,
        LDR1,
        LDR2,
        LDR3,
        LDR4,
        LDRB1,
        LDRB2,
        LDRH1,
        LDRH2,
        LDRSB,
        LDRSH,
        POP,
        PUSH,
        STMIA,
        STR1,
        STR2,
        STR3,
        STRB1,
        STRH1,
        STRH2
    };

    enum class jazelle_instruction : u8 {
        UNKNOWN = 0,
        AALOAD,
        AASTORE,
        ACONST_NULL,
        ALOAD,
        ALOAD_0,
        ALOAD_1,
        ALOAD_2,
        ALOAD_3,
        ANEWARRAY,
        ARETURN,
        ARRAYLENGTH,
        ASTORE,
        ASTORE_0,
        ASTORE_1,
        ASTORE_2,
        ASTORE_3,
        ATHROW,
        BALOAD,
        BASTORE,
        BIPUSH,
        BREAKPOINT,
        CALOAD,
        CASTORE,
        CHECKCAST,
        D2F,
        D2I,
        D2L,
        DADD,
        DALOAD,
        DASTORE,
        DCMPG,
        DCMPL,
        DCONST_0,
        DCONST_1,
        DDIV,
        DLOAD,
        DLOAD_0,
        DLOAD_1,
        DLOAD_2,
        DLOAD_3,
        DMUL,
        DNEG,
        DREM,
        DRETURN,
        DSTORE,
        DSTORE_0,
        DSTORE_1,
        DSTORE_2,
        DSTORE_3,
        DSUB,
        DUP,
        DUP_X1,
        DUP_X2,
        DUP2,
        DUP2_X1,
        DUP2_X2,
        F2D,
        F2I,
        F2L,
        FADD,
        FALOAD,
        FASTORE,
        FCMPG,
        FCMPL,
        FCONST_0,
        FCONST_1,
        FCONST_2,
        FDIV,
        FLOAD,
        FLOAD_0,
        FLOAD_1,
        FLOAD_2,
        FLOAD_3,
        FMUL,
        FNEG,
        FREM,
        FRETURN,
        FSTORE,
        FSTORE_0,
        FSTORE_1,
        FSTORE_2,
        FSTORE_3,
        FSUB,
        GETFIELD,
        GETSTATIC,
        GOTO,
        GOTO_W,
        I2B,
        I2C,
        I2D,
        I2F,
        I2L,
        I2S,
        IADD,
        IALOAD,
        IAND,
        IASTORE,
        ICONST_M1,
        ICONST_0,
        ICONST_1,
        ICONST_2,
        ICONST_3,
        ICONST_4,
        ICONST_5,
        IDIV,
        IF_ACMPEQ,
        IF_ACMPNE,
        IF_ICMPEQ,
        IF_ICMPGE,
        IF_ICMPGT,
        IF_ICMPLE,
        IF_ICMPLT,
        IF_ICMPNE,
        IFEQ,
        IFGE,
        IFGT,
        IFLE,
        IFLT,
        IFNE,
        IFNONNULL,
        IFNULL,
        IINC,
        ILOAD,
        ILOAD_0,
        ILOAD_1,
        ILOAD_2,
        ILOAD_3,
        IMPDEP1,
        IMPDEP2,
        IMUL,
        INEG,
        INSTANCEOF,
        INVOKEDYNAMIC,
        INVOKEINTERFACE,
        INVOKESPECIAL,
        INVOKESTATIC,
        INVOKEVIRTUAL,
        IOR,
        IREM,
        IRETURN,
        ISHL,
        ISHR,
        ISTORE,
        ISTORE_0,
        ISTORE_1,
        ISTORE_2,
        ISTORE_3,
        ISUB,
        IUSHR,
        IXOR,
        JSR, // DEPRECATED
        JSR_W, // DEPRECATED
        L2D,
        L2F,
        L2I,
        LADD,
        LALOAD,
        LAND,
        LASTORE,
        LCMP,
        LCONST_0,
        LCONST_1,
        LDC,
        LDC_W,
        LDC2_W,
        LDIV,
        LLOAD,
        LLOAD_0,
        LLOAD_1,
        LLOAD_2,
        LLOAD_3,
        LMUL,
        LNEG,
        LOOKUPSWITCH,
        LOR,
        LREM,
        LRETURN,
        LSHL,
        LSHR,
        LSTORE,
        LSTORE_0,
        LSTORE_1,
        LSTORE_2,
        LSTORE_3,
        LSUB,
        LUSHR,
        LXOR,
        MONITORENTER,
        MONITOREXIT,
        MULTIANEWARRAY,
        NEW,
        NEWARRAY,
        NOP,
        POP,
        POP2,
        PUTFIELD,
        PUTSTATIC,
        RET, // DEPRECATED
        RETURN,
        SALOAD,
        SASTORE,
        SIPUSH,
        SWAP,
        TABLESWITCH,
        WIDE
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

    // coprocessor registers and bits
    enum class cp : u8 {
        NULL_REG = 0,
        CP15_R0_ID,
        CP15_R0_ID_IMPLEMENTOR,
        CP15_R0_ID_PPN, // PPN = primary part number
        CP15_R0_ID_PPN_TOP,
        CP15_R0_ID_PPN_LOWER,
        CP15_R0_ID_REVISION,
        CP15_R0_ID_POST7_VARIANT,
        CP15_R0_ID_POST7_ARCH,
        CP15_R0_ID_7_VARIANT,
        CP15_R0_ID_7_A,
        CP15_R0_ID_PRE7_ID,
        CP15_R0_CACHE,
        CP15_R0_CACHE_CTYPE,
        CP15_R0_CACHE_S,
        CP15_R0_CACHE_DSIZE,
        CP15_R0_CACHE_ISIZE,

        CP15_R1_CONTROL,
        CP15_R1_M, // MMU or Protection Unit enable disable
        CP15_R1_A, // alignment fault checking
        CP15_R1_C, // unified cache
        CP15_R1_W, // write buffer
        CP15_R1_P, // 26-bit backwards-compatibility configurations (PROG32)
        CP15_R1_D, // 26-bit backwards-compatibility configurations (DATA32)
        CP15_R1_L, // abort model of the processor
        CP15_R1_B, // endianness of the memory system
        CP15_R1_S, // system protection bit
        CP15_R1_R, // ROM protection bit
        CP15_R1_F, // IMPLEMENTATION DEFINED
        CP15_R1_Z, // branch prediction
        CP15_R1_I, // instruction cache
        CP15_R1_V, // high vectors
        CP15_R1_RR, // cache strategy
        CP15_R1_L4, // ARMv5+ backwards compatibility

        CP15_R2_MMU,
        CP15_R2_MMU_TRANSLATION_BASE,
        CP15_R2_PU,
        CP15_R2_PU_C0,
        CP15_R2_PU_C1,
        CP15_R2_PU_C2,
        CP15_R2_PU_C3,
        CP15_R2_PU_C4,
        CP15_R2_PU_C5,
        CP15_R2_PU_C6,
        CP15_R2_PU_C7,

        CP15_R3_MMU,
        CP15_R3_MMU_D0,
        CP15_R3_MMU_D1,
        CP15_R3_MMU_D2,
        CP15_R3_MMU_D3,
        CP15_R3_MMU_D4,
        CP15_R3_MMU_D5,
        CP15_R3_MMU_D6,
        CP15_R3_MMU_D7,
        CP15_R3_MMU_D8,
        CP15_R3_MMU_D9,
        CP15_R3_MMU_D10,
        CP15_R3_MMU_D11,
        CP15_R3_MMU_D12,
        CP15_R3_MMU_D13,
        CP15_R3_MMU_D14,
        CP15_R3_MMU_D15,
        CP15_R3_PU,
        CP15_R3_PU_B0,
        CP15_R3_PU_B1,
        CP15_R3_PU_B2,
        CP15_R3_PU_B3,
        CP15_R3_PU_B4,
        CP15_R3_PU_B5,
        CP15_R3_PU_B6,
        CP15_R3_PU_B7,

        CP15_R4_MMU,
        CP15_R4_PU,

        CP15_R5_MMU,
        CP15_R5_MMU_DOMAIN,
        CP15_R5_MMU_STATUS,
        CP15_R5_PU,
        CP15_R5_PU_AP0,
        CP15_R5_PU_AP1,
        CP15_R5_PU_AP2,
        CP15_R5_PU_AP3,
        CP15_R5_PU_AP4,
        CP15_R5_PU_AP5,
        CP15_R5_PU_AP6,
        CP15_R5_PU_AP7,

        CP15_R6_MMU,
        CP15_R6_MMU_FAR, // fault address
        CP15_R6_PU,
        CP15_R6_PU_BASE_ADDRESS, 
        CP15_R6_PU_SIZE,
        CP15_R6_PU_E,  

        CP15_R7_CACHE,
        CP15_R7_CACHE_INDEX,
        CP15_R7_CACHE_SET,

        CP15_R8_MMU,
        CP15_R8_PU,

        CP15_R9_CACHE,
        CP15_R9_CACHE_INDEX,
        CP15_R9_CACHE_L,

        CP15_R10_MMU,
        CP15_R10_MMU_BASE,
        CP15_R10_MMU_VICTIM,
        CP15_R10_MMU_P,
        CP15_R10_PU,

        CP15_R11_RESERVED,
        CP15_
        CP15_R12_RESERVED,

        CP15_R13_PID,
        //CP15_ ????????????????/
        CP15_R14_RESERVED,

        CP15_R15_IMPL
    };


    enum class memory : u8 {
        NO_ACCESS_PERMISSION = 1,
        READ_WRITE,
        READ
    };


    enum class first_level_descriptor : u8 {
        FAULT = 1, 
        COARSE_PAGE_TABLE, 
        SECTION,
        FINE_PAGE_TABLE,
    };

    enum class second_level_descriptor : u8 {
        FAULT = 1, 
        LARGE,
        SMALL,
        TINY
    };

    enum class product_family : u8 {
        ARM1 = 1,
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
        ARMv1 = 1,
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
        ARMv1 = 1,
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
        ARM3 = 1,
        ARM600,
        ARM610,
        ARM620
    };

    enum class implementor : u8 {
        ARM = 1,
        BRCM, // broadcom 
        DEC, // digital equipment corporation
        MOTOROLA,
        QUALCOMM,
        MARVELL, 
        INTEL,
        CHARM // custom
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