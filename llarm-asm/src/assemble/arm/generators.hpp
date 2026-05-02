#pragma once

#include "../../id/instruction_id.hpp"
#include "../../interpreter/operand_struct.hpp"
#include "../../interpreter/IR_struct.hpp"

#include <llarm/shared/types.hpp>

using namespace internal;

namespace internal::generators {
    u32 data_instruction(const arm_id id, const operand_struct& arg);
    u32 ls_instruction(const arm_id id, const operand_struct& arg);
    
    u32 ls_misc_instruction(const arm_id id, const operand_struct& arg);
    u32 ls_mul_instruction(const arm_id id, const operand_struct& arg);
    u32 ls_coproc_instruction(const arm_id id, const operand_struct& arg);

    // defined in encoders/special.cpp
    u32 mul(const operand_struct& arg);
    u32 swp(const operand_struct& arg);
    u32 swpb(const operand_struct& arg);
    u32 mla(const operand_struct& args);
    u32 mrs(const operand_struct& args);
    u32 msr_imm(const operand_struct& args);
    u32 msr_reg(const operand_struct& args);
    u32 swi(const operand_struct& args);
    u32 clz(const operand_struct& args);
    u32 mcr(const operand_struct& args);
    u32 mrc(const operand_struct& args);
    u32 cdp(const operand_struct& args);
    u32 b(const operand_struct& args);
    u32 bl(const operand_struct& args);
    u32 bkpt(const operand_struct& args);
    u32 blx1(const operand_struct& args);
    u32 blx2(const operand_struct& args);
    u32 bx(const operand_struct& args);
    u32 mcrr(const operand_struct& args, const bool is_mcrr2 = false);
    u32 mrrc(const operand_struct& args, const bool is_mrrc2 = false);
    u32 cps(const operand_struct& args);
    u32 cpy(const operand_struct& args);
    u32 srs(const operand_struct& args);
    u32 strex(const operand_struct& args);
    u32 ldrex(const operand_struct& args);
    u32 usad8(const operand_struct& args);
    u32 usada8(const operand_struct& args);
    u32 setend(const operand_struct& args);
    u32 rfe(const operand_struct& args);
    u32 usat16(const operand_struct& args);
    u32 usat(const operand_struct& args);

    // defined in encoders/special_grouping.cpp
    u32 q_instructions(const arm_id id, const operand_struct& args);
    u32 mul_instructions(const arm_id id, const operand_struct& args);
    u32 dsp_mul_instructions(const arm_id id, const operand_struct& args);
    u32 saturate_instructions(const arm_id id, const operand_struct& args);
    u32 signed_mul_instructions(const arm_id id, const operand_struct& args);
    u32 signed_mul_1111_instructions(const arm_id id, const operand_struct& args);
    u32 ssat_instruction(const arm_id id, const operand_struct& args);
    u32 pkh_instruction(const arm_id id, const operand_struct& args);
    u32 sign_extend_rotate_instructions(const arm_id id, const operand_struct& args);
    u32 sign_extend_rotate_no_Rn_instructions(const arm_id id, const operand_struct& args);
    u32 rev_instructions(const arm_id id, const operand_struct& args);
    u32 mul_high_low_instructions(const arm_id id, const operand_struct& args);

    // defined in encoders/vfp.cpp
    u32 vfp_Dd_Dm_instructions(const arm_id id, const operand_struct& args);
    u32 vfp_Dd_Dn_Dm_instructions(const arm_id id, const operand_struct& args);
    u32 vfp_Sd_Sm_instructions(const arm_id id, const operand_struct& args);
    u32 vfp_Sd_Sn_Sm_instructions(const arm_id id, const operand_struct& args);
    u32 vfp_Dd_Sm_instructions(const arm_id id, const operand_struct& args);
    u32 vfp_Sd_Dm_instructions(const arm_id id, const operand_struct& args);

    // defined in encoders/vfp_mul.cpp
    u32 vfp_mul_instructions(const arm_id id, const operand_struct& args);

    // defined in vfp.cpp
    u32 fcmpezd(const operand_struct& args);
    u32 fcmpzd(const operand_struct& args);
    u32 fcmpezs(const operand_struct& args);
    u32 fcmpzs(const operand_struct& args);
    u32 fldmd(const operand_struct& args);
    u32 fldms(const operand_struct& args);
    u32 fldmx(const operand_struct& args);
    u32 fmdhr(const operand_struct& args);
    u32 fmdlr(const operand_struct& args);
    u32 fmrdh(const operand_struct& args);
    u32 fmrdl(const operand_struct& args);
    u32 fmrs(const operand_struct& args);
    u32 fmrx(const operand_struct& args);
    u32 fmsr(const operand_struct& args);
    u32 fmxr(const operand_struct& args);
    u32 fmstat(const operand_struct& args);

    u32 arm(const IR_arm_struct& IR);
}