#pragma once

#include "../../instruction_id.hpp"
#include "../../shifter_id.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"

using namespace internal;

namespace internal::generators {
    enum class vfp_special_regs : u8 {
        NONE,
        FPSID,
        FPSCR,
        FPEXC
    };

    struct arguments {
        u8 flags;
        u8 cond;
        u8 PSR_field_mask;
        u8 first_reg;
        u8 second_reg;
        u8 third_reg;
        u8 fourth_reg;
        u8 coproc;
        u8 first_CR_reg;
        u8 second_CR_reg;
        u8 third_CR_reg;
        shifter_enum shifter;
        u16 reg_list;
        u32 first_int;
        u32 second_int;
        u32 third_int;
        vfp_special_regs vfp_special_reg;
        
        bool has_S() const { return (flags & 1); }
        bool has_Z() const { return shared::util::bit_fetch(flags, 1); }
        bool has_minus() const { return shared::util::bit_fetch(flags, 2); }
        bool has_spsr() const { return shared::util::bit_fetch(flags, 3); }
        bool has_x() const { return shared::util::bit_fetch(flags, 4); }
        bool has_y() const { return shared::util::bit_fetch(flags, 5); }
        bool has_preindex() const { return shared::util::bit_fetch(flags, 6); }
    };

    bool is_imm_encodable(const u32 imm);
    void encode_imm(u32 &binary, const u32 imm);

    u32 data_instruction(const id::arm instruction, const arguments &arg);
    u32 ls_instruction(const id::arm instruction, const arguments &arg);
    u32 ls_misc_instruction(const id::arm instruction, const arguments &arg);
    u32 ls_mul_instruction(const id::arm instruction, const arguments &arg);
    u32 ls_coproc_instruction(const id::arm id, const arguments &arg);

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
    u32 blx2(const arguments &args);
    u32 bx(const arguments &args);
    u32 mcrr(const arguments &args);
    u32 mrrc(const arguments &args);

    // defined in encoders/special_grouping.cpp
    u32 q_instructions(const id::arm id, const arguments &args);
    u32 mul_instructions(const id::arm id, const arguments &args);
    u32 dsp_mul_instructions(const id::arm id, const arguments &args);

    // defined in encoders/vfp.cpp
    u32 vfp_Dd_Dm_instructions(const id::arm id, const arguments &args);
    u32 vfp_Dd_Dn_Dm_instructions(const id::arm id, const arguments &args);
    u32 vfp_Sd_Sm_instructions(const id::arm id, const arguments &args);
    u32 vfp_Sd_Sn_Sm_instructions(const id::arm id, const arguments &args);
    u32 vfp_Dd_Sm_instructions(const id::arm id, const arguments &args);
    u32 vfp_Sd_Dm_instructions(const id::arm id, const arguments &args);

    // defined in encoders/vfp_mul.cpp
    u32 vfp_mul_instructions(const id::arm id, const arguments &args);

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

    u32 arm(const id::arm id, const arguments &args);
}







    /*
            switch (id) {
                case id::thumb::UNDEFINED: return "UNDEFINED";
                case id::thumb::ADC: return "ADC";
                case id::thumb::ADD1: return "ADD1";
                case id::thumb::ADD2: return "ADD2";
                case id::thumb::ADD3: return "ADD3";
                case id::thumb::ADD4: return "ADD4";
                case id::thumb::ADD5: return "ADD5";
                case id::thumb::ADD6: return "ADD6";
                case id::thumb::ADD7: return "ADD7";
                case id::thumb::SBC: return "SBC";
                case id::thumb::SUB1: return "SUB1";
                case id::thumb::SUB2: return "SUB2";
                case id::thumb::SUB3: return "SUB3";
                case id::thumb::SUB4: return "SUB4";
                case id::thumb::MUL: return "MUL";
                case id::thumb::AND: return "AND";
                case id::thumb::ASR1: return "ASR1";
                case id::thumb::ASR2: return "ASR2";
                case id::thumb::BIC: return "BIC";
                case id::thumb::EOR: return "EOR";
                case id::thumb::LSL1: return "LSL1";
                case id::thumb::LSL2: return "LSL2";
                case id::thumb::LSR1: return "LSR1";
                case id::thumb::LSR2: return "LSR2";
                case id::thumb::NEG: return "NEG";
                case id::thumb::ORR: return "ORR";
                case id::thumb::ROR: return "ROR";
                case id::thumb::TST: return "TST";
                case id::thumb::CMN: return "CMN";
                case id::thumb::CMP1: return "CMP1";
                case id::thumb::CMP2: return "CMP2";
                case id::thumb::CMP3: return "CMP3";
                case id::thumb::MOV1: return "MOV1";
                case id::thumb::MOV2: return "MOV2";
                case id::thumb::MOV3: return "MOV3";
                case id::thumb::MVN: return "MVN";
                case id::thumb::B1: return "B1";
                case id::thumb::B2: return "B2";
                case id::thumb::BL: return "BL";
                case id::thumb::BLX1: return "BLX1";
                case id::thumb::BLX2: return "BLX2";
                case id::thumb::BX: return "BX";
                case id::thumb::NOP: return "NOP";
                case id::thumb::BKPT: return "BKPT";
                case id::thumb::SWI: return "SWI";
                case id::thumb::LDMIA: return "LDMIA";
                case id::thumb::LDR1: return "LDR1";
                case id::thumb::LDR2: return "LDR2";
                case id::thumb::LDR3: return "LDR3";
                case id::thumb::LDR4: return "LDR4";
                case id::thumb::LDRB1: return "LDRB1";
                case id::thumb::LDRB2: return "LDRB2";
                case id::thumb::LDRH1: return "LDRH1";
                case id::thumb::LDRH2: return "LDRH2";
                case id::thumb::LDRSB: return "LDRSB";
                case id::thumb::LDRSH: return "LDRSH";
                case id::thumb::POP: return "POP";
                case id::thumb::PUSH: return "PUSH";
                case id::thumb::STMIA: return "STMIA";
                case id::thumb::STR1: return "STR1";
                case id::thumb::STR2: return "STR2";
                case id::thumb::STR3: return "STR3";
                case id::thumb::STRB1: return "STRB1";
                case id::thumb::STRB2: return "STRB2";
                case id::thumb::STRH1: return "STRH1";
                case id::thumb::STRH2: return "STRH2";
            }
*/