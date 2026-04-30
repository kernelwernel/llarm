#pragma once

#include "../../../settings.hpp"

#include <llarm/shared/types.hpp>

#include <string>

namespace internal::patterns {

    // general ARM instructions
    std::string S_Rd_Rn_data(const u32 code, const std::string& instruction, const settings& settings);
    std::string Rn_data(const u32 code, const std::string& instruction, const settings& settings);
    std::string S_Rd_data(const u32 code, const std::string& instruction, const settings& settings, const bool aliasing = false);
    std::string psr_fields(const u32 code);
    std::string Rd_Rm(const u32 code, const std::string& instruction, const settings& settings);
    std::string Rd_Rn_Rm_rotate(const u32 code, const std::string& instruction, const settings& settings);
    std::string Rd_Rm_rotate(const u32 code, const std::string& instruction, const settings& settings);
    std::string mul_Hi_Lo(const u32 code, const std::string& instruction, const settings& settings);
    std::string mul_Rd_Rm_Rs_Rn(const u32 code, const std::string& instruction, const char* extra, const settings& settings);
    std::string mul_RdLo_RdHi_Rm_Rs_X(const u32 code, const std::string& instruction, const settings& settings);
    std::string mul_RdLo_RdHi_Rm_Rs(const u32 code, const std::string& instruction, const settings& settings);
    std::string mul_Rd_Rm_Rs_X(const u32 code, const std::string& instruction, const char* extra, const settings& settings);

    std::string sat_Rd_Rn_Rm(const u32 code, const std::string& instruction, const settings& settings);
    std::string dsp_Rd_Rm_Rn(const u32 code, const std::string& instruction, const settings& settings);

    // ARM VFP instructions 
    std::string vfp_Dd_Dm(const u32 code, const std::string& instruction, const settings& settings);
    std::string vfp_Dd_Dn_Dm(const u32 code, const std::string& instruction, const settings& settings);
    std::string vfp_Sd_Sm(const u32 code, const std::string& instruction, const settings& settings);
    std::string vfp_Sd_Sm_Z(const u32 code, const std::string&semi_instruction, const settings& settings);
    std::string vfp_Sd_Dm_Z(const u32 code, const std::string&semi_instruction, const settings& settings);
    std::string vfp_Sd_Sn_Sm(const u32 code, const std::string& instruction, const settings& settings);
    std::string vfp_Dd_Sm(const u32 code, const std::string& instruction, const settings& settings);
    std::string vfp_Rd_Dn(const u32 code, const std::string& instruction, const settings& settings);
    std::string vfp_Dn_Rd(const u32 code, const std::string& instruction, const settings& settings);
    std::string vfp_Sd(const u32 code, const std::string& instruction, const settings& settings);
    std::string vfp_Dd(const u32 code, const std::string& instruction, const settings& settings);
}