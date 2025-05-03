#include "shared/types.hpp"

#include <string>

namespace internal::patterns {
    // general ARM instructions
    std::string S_Rd_Rn_data(const u32 code, const sv instruction);
    std::string Rn_data(const u32 code, const sv instruction);
    std::string S_Rd_data(const u32 code, const sv instruction);
    std::string psr_fields(const u32 code);

    std::string mul_Hi_Lo(const u32 code, const sv instruction);

    // ARM DSP instructions
    std::string dsp_Rd_Rm_Rn(const u32 code, const sv instruction);

    // ARM VFP instructions 
    std::string vfp_Dd_Dm(const u32 code, const sv instruction);
    std::string vfp_Dd_Dn_Dm(const u32 code, const sv instruction);
    std::string vfp_Sd_Sm(const u32 code, const sv instruction);
    std::string vfp_Sd_Sm_Z(const u32 code, const sv semi_instruction);
    std::string vfp_Sd_Dm_Z(const u32 code, const sv semi_instruction);
    std::string vfp_Sd_Sn_Sm(const u32 code, const sv instruction);
    std::string vfp_Dd_Sm(const u32 code, const sv instruction);
    std::string vfp_Rd_Dn(const u32 code, const sv instruction);
    std::string vfp_Dn_Rd(const u32 code, const sv instruction);
    std::string vfp_Sd(const u32 code, const sv instruction);
    std::string vfp_Dd(const u32 code, const sv instruction);
}