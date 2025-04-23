#pragma once

#include "shared/types.hpp"
#include "shared/util.hpp"
#include "shared/out.hpp"

// reference: A5-1

namespace internal::shifters {

    // note: 
    //  - "LS" = "load store"
    //  - "PRE" = "pre-indexed"
    //  - "POST" = "post-indexed"
    enum class mode : u8 {
        DATA_IMM,
        DATA_IMM_LSL,
        DATA_IMM_LSR,
        DATA_IMM_ASR,
        DATA_IMM_ROR,
        DATA_REG,
        DATA_REG_LSL,
        DATA_REG_LSR,
        DATA_REG_ASR,
        DATA_REG_ROR,
        DATA_RRX,

        LS_IMM,
        LS_IMM_PRE,
        LS_IMM_POST,
        LS_REG,
        LS_REG_PRE,
        LS_REG_POST,
        LS_REG_SCALED_LSL,
        LS_REG_SCALED_LSR,
        LS_REG_SCALED_ASR,
        LS_REG_SCALED_ROR,
        LS_REG_SCALED_RRX,
        LS_REG_SCALED_PRE_LSL,
        LS_REG_SCALED_PRE_LSR,
        LS_REG_SCALED_PRE_ASR,
        LS_REG_SCALED_PRE_ROR,
        LS_REG_SCALED_PRE_RRX,
        LS_REG_SCALED_POST_LSL,
        LS_REG_SCALED_POST_LSR,
        LS_REG_SCALED_POST_ASR,
        LS_REG_SCALED_POST_ROR,
        LS_REG_SCALED_POST_RRX,

        LS_MISC_IMM,
        LS_MISC_IMM_PRE,
        LS_MISC_IMM_POST,
        LS_MISC_REG,
        LS_MISC_REG_PRE,
        LS_MISC_REG_POST,

        LS_MUL_INC_AFTER,
        LS_MUL_INC_BEFORE,
        LS_MUL_DEC_AFTER,
        LS_MUL_DEC_BEFORE,

        LS_COPROC_IMM,
        LS_COPROC_IMM_PRE,
        LS_COPROC_IMM_POST,
        LS_COPROC_UNINDEXED
    };

    mode identify_data_shifter(const u32 code);
    mode identify_ls_shifter(const u32 code);
    mode identify_ls_misc_shifter(const u32 code);
    mode identify_ls_mul_shifter(const u32 code);
    mode identify_ls_coproc_shifter(const u32 code);

    std::string shifter_to_string(const mode mode, const u32 code);

    // defined in modes/data.cpp
    std::string data_reg_pattern(const u32 code, const sv mode);
    std::string data_imm_pattern(const u32 code, const sv mode);
    std::string data_imm(const u32 code);
    std::string data_reg(const u32 code);
    std::string data_rrx(const u32 code);

    // defined in modes/ls.cpp
    std::string ls_imm(const u32 code);
    std::string ls_imm_pre(const u32 code);
    std::string ls_imm_post(const u32 code);
    std::string ls_reg(const u32 code);
    std::string ls_reg_pre(const u32 code);
    std::string ls_reg_post(const u32 code);
    std::string ls_reg_scaled(const u32 code, const sv mode);
    std::string ls_reg_scaled_pre(const u32 code, const sv mode);
    std::string ls_reg_scaled_post(const u32 code, const sv mode);
    std::string ls_reg_scaled_rrx(const u32 code);
    std::string ls_reg_scaled_pre_rrx(const u32 code);
    std::string ls_reg_scaled_post_rrx(const u32 code);

    // defined in modes/ls_misc.cpp
    std::string ls_misc_imm(const u32 code);
    std::string ls_misc_imm_pre(const u32 code);
    std::string ls_misc_imm_post(const u32 code);
    std::string ls_misc_reg(const u32 code);
    std::string ls_misc_reg_pre(const u32 code);
    std::string ls_misc_reg_post(const u32 code);

    std::string ls_coproc_imm(const u32 code);
    std::string ls_coproc_imm_pre(const u32 code);
    std::string ls_coproc_imm_post(const u32 code);
    std::string ls_coproc_unindexed(const u32 code);
}