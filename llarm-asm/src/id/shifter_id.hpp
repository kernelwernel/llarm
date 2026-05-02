#pragma once

#include <llarm/shared/types.hpp>

namespace internal {
    enum class shifter_id : u8 {
        UNKNOWN,
        NONE,

        // addressing mode 1: data processing
        DATA_IMM,
        DATA_RRX,
        DATA_REG,
        DATA_IMM_LSL,
        DATA_IMM_LSR,
        DATA_IMM_ASR,
        DATA_IMM_ROR,
        DATA_REG_LSL,
        DATA_REG_LSR,
        DATA_REG_ASR,
        DATA_REG_ROR,
        
        // addressing mode 2: load store unsigned byte
        LS_IMM,
        LS_IMM_PRE,
        LS_IMM_POST,
        LS_REG,
        LS_REG_PRE,
        LS_REG_POST,
        LS_SCALED_LSL,
        LS_SCALED_LSR,
        LS_SCALED_ASR,
        LS_SCALED_ROR,
        LS_SCALED_RRX,
        LS_SCALED_PRE_LSL,
        LS_SCALED_PRE_LSR,
        LS_SCALED_PRE_ASR,
        LS_SCALED_PRE_ROR,
        LS_SCALED_PRE_RRX,
        LS_SCALED_POST_LSL,
        LS_SCALED_POST_LSR,
        LS_SCALED_POST_ASR,
        LS_SCALED_POST_ROR,
        LS_SCALED_POST_RRX,
        
        // addressing mode 3: miscellaneous load and store
        LS_MISC_IMM,
        LS_MISC_IMM_PRE,
        LS_MISC_IMM_POST,
        LS_MISC_REG,
        LS_MISC_REG_PRE,
        LS_MISC_REG_POST,
        
        // addressing mode 4: load store multiple
        LS_MUL_INC_AFTER,
        LS_MUL_INC_BEFORE,
        LS_MUL_DEC_AFTER,
        LS_MUL_DEC_BEFORE,
        
        // addressing mode 5: load and store coprocessor
        LS_COPROC_IMM,
        LS_COPROC_IMM_PRE,
        LS_COPROC_IMM_POST,
        LS_COPROC_UNINDEXED,
        
        // vfp addressing modes (too lazy to categorise all 5 of them honestly)
        VFP_SINGLE,
        VFP_SINGLE_SCALAR,
        VFP_SINGLE_MIXED,
        VFP_SINGLE_VECTOR,
        VFP_SINGLE_MONADIC,
        VFP_SINGLE_MONADIC_SCALAR_TO_SCALAR,
        VFP_SINGLE_MONADIC_SCALAR_TO_VECTOR,
        VFP_SINGLE_MONADIC_VECTOR_TO_VECTOR,
        VFP_DOUBLE,
        VFP_DOUBLE_SCALAR,
        VFP_DOUBLE_MIXED,
        VFP_DOUBLE_VECTOR,
        VFP_DOUBLE_MONADIC,
        VFP_DOUBLE_MONADIC_SCALAR_TO_SCALAR,
        VFP_DOUBLE_MONADIC_SCALAR_TO_VECTOR,
        VFP_DOUBLE_MONADIC_VECTOR_TO_VECTOR,
        VFP_LS_MUL,
        VFP_LS_MUL_UNINDEXED,
        VFP_LS_MUL_INC,
        VFP_LS_MUL_DEC,
        VFP_LS_MUL_SPECIAL,

        // edgecases for USAT instruction, has a unique shifter argument component
        USAT_LSL,
        USAT_ASR
    };


    enum class shifter_category : u8 {
        DATA,
        LS,
        LS_MISC,
        LS_MUL,
        LS_COPROC,
        VFP_SINGLE,
        VFP_SINGLE_MONADIC,
        VFP_DOUBLE,
        VFP_DOUBLE_MONADIC,
        VFP_LS_MUL,
    };
}