#pragma once

#include "../../id/instruction_id.hpp"

#include "shared/types.hpp"

#include "../arguments.hpp"

using namespace internal;

namespace internal::generators {
    bool is_imm_encodable(const u32 imm);
    void encode_imm(u32 &binary, const u32 imm);

    u32 data_instruction(const arm_id instruction, const arguments &arg);
    u32 ls_instruction(const arm_id instruction, const arguments &arg);
    u32 ls_misc_instruction(const arm_id instruction, const arguments &arg);
    u32 ls_mul_instruction(const arm_id instruction, const arguments &arg);
    u32 ls_coproc_instruction(const arm_id id, const arguments &arg);

    // defined in encoders/special.cpp
    u32 mul(const arguments &arg);
    u32 swp(const arguments &arg);
    u32 swpb(const arguments &arg);
    u32 mla(const arguments &args);
    u32 mrs(const arguments &args);
    u32 msr_imm(const arguments &args);
    u32 msr_reg(const arguments &args);
    u32 swi(const arguments &args);
    u32 clz(const arguments &args);
    u32 mcr(const arguments &args);
    u32 mrc(const arguments &args);
    u32 cdp(const arguments &args);
    u32 b(const arguments &args);
    u32 bl(const arguments &args);
    u32 bkpt(const arguments &args);
    u32 blx1(const arguments &args);
    u32 blx2(const arguments &args);
    u32 bx(const arguments &args);
    u32 mcrr(const arguments &args);
    u32 mrrc(const arguments &args);

    // defined in encoders/special_grouping.cpp
    u32 q_instructions(const arm_id id, const arguments &args);
    u32 mul_instructions(const arm_id id, const arguments &args);
    u32 dsp_mul_instructions(const arm_id id, const arguments &args);

    // defined in encoders/vfp.cpp
    u32 vfp_Dd_Dm_instructions(const arm_id id, const arguments &args);
    u32 vfp_Dd_Dn_Dm_instructions(const arm_id id, const arguments &args);
    u32 vfp_Sd_Sm_instructions(const arm_id id, const arguments &args);
    u32 vfp_Sd_Sn_Sm_instructions(const arm_id id, const arguments &args);
    u32 vfp_Dd_Sm_instructions(const arm_id id, const arguments &args);
    u32 vfp_Sd_Dm_instructions(const arm_id id, const arguments &args);

    // defined in encoders/vfp_mul.cpp
    u32 vfp_mul_instructions(const arm_id id, const arguments &args);

    // defined in vfp.cpp
    u32 fcmpezd(const arguments &args);
    u32 fcmpzd(const arguments &args);
    u32 fcmpezs(const arguments &args);
    u32 fcmpzs(const arguments &args);
    u32 fldmd(const arguments &args);
    u32 fldms(const arguments &args);
    u32 fldmx(const arguments &args);
    u32 fmdhr(const arguments &args);
    u32 fmdlr(const arguments &args);
    u32 fmrdh(const arguments &args);
    u32 fmrdl(const arguments &args);
    u32 fmrs(const arguments &args);
    u32 fmrx(const arguments &args);
    u32 fmsr(const arguments &args);
    u32 fmxr(const arguments &args);
    u32 fmstat(const arguments &args);

    u32 arm(const arm_id id, const arguments &args);
}