#pragma once

#include "../../../../id/shifter_id.hpp"
#include "../../../../settings.hpp"

#include <llarm/shared/types.hpp>

#include <string>

// reference: A5-1

namespace internal::shifters {
    std::string data(const u32 code, const settings& settings);
    std::string data(const u32 code, const shifter_id id, const settings& settings);
    std::string ls(const u32 code, const settings& settings);
    std::string ls_misc(const u32 code, const settings& settings);
    std::string ls_mul(const u32 code, const settings& settings);
    std::string ls_coproc(const u32 code, const settings& settings);
    std::string vfp_ls_mul(const u32 code, const settings& settings);

    shifter_id identify_data_shifter(const u32 code);
    shifter_id identify_ls_shifter(const u32 code);
    shifter_id identify_ls_misc_shifter(const u32 code);
    shifter_id identify_ls_mul_shifter(const u32 code);
    shifter_id identify_ls_coproc_shifter(const u32 code);
    shifter_id identify_vfp_ls_mul_shifter(const u32 code);

    std::string shifter_to_string(const shifter_id shifter, const u32 code, const settings& settings);

    // defined in modes/data.cpp
    std::string data_reg_pattern(const u32 code, const std::string &mode, const settings& settings);
    std::string data_imm_pattern(const u32 code, const std::string &mode, const settings& settings);
    std::string data_imm(const u32 code, const settings& settings);
    std::string data_reg(const u32 code, const settings& settings);
    std::string data_rrx(const u32 code, const settings& settings);

    // defined in modes/ls.cpp
    std::string ls_imm(const u32 code, const settings& settings);
    std::string ls_imm_pre(const u32 code, const settings& settings);
    std::string ls_imm_post(const u32 code, const settings& settings);
    std::string ls_reg(const u32 code, const settings& settings);
    std::string ls_reg_pre(const u32 code, const settings& settings);
    std::string ls_reg_post(const u32 code, const settings& settings);
    std::string ls_reg_scaled(const u32 code, const std::string &mode, const settings& settings);
    std::string ls_reg_scaled_pre(const u32 code, const std::string &mode, const settings& settings);
    std::string ls_reg_scaled_post(const u32 code, const std::string &mode, const settings& settings);
    std::string ls_reg_scaled_rrx(const u32 code, const settings& settings);
    std::string ls_reg_scaled_pre_rrx(const u32 code, const settings& settings);
    std::string ls_reg_scaled_post_rrx(const u32 code, const settings& settings);

    // defined in modes/ls_misc.cpp
    std::string ls_misc_imm(const u32 code, const settings& settings);
    std::string ls_misc_imm_pre(const u32 code, const settings& settings);
    std::string ls_misc_imm_post(const u32 code, const settings& settings);
    std::string ls_misc_reg(const u32 code, const settings& settings);
    std::string ls_misc_reg_pre(const u32 code, const settings& settings);
    std::string ls_misc_reg_post(const u32 code, const settings& settings);

    // defined in modes/ls_coproc.cpp
    std::string ls_coproc_imm(const u32 code, const settings& settings);
    std::string ls_coproc_imm_pre(const u32 code, const settings& settings);
    std::string ls_coproc_imm_post(const u32 code, const settings& settings);
    std::string ls_coproc_unindexed(const u32 code, const settings& settings);

    // defined in modes/ls_mul.cpp
    std::string ls_mul_inc_after(const settings& settings);
    std::string ls_mul_inc_before(const settings& settings);
    std::string ls_mul_dec_after(const settings& settings);
    std::string ls_mul_dec_before(const settings& settings);

    // defined in modes/vfp.cpp
    std::string vfp_ls_mul_unindexed(const settings& settings);
    std::string vfp_ls_mul_inc(const settings& settings);
    std::string vfp_ls_mul_dec(const settings& settings);
}