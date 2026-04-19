#include "patterns.hpp"
#include "../../disassemble.hpp"
#include "../arm/shifter_operands/shifters.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>

#include <string>

#include "../util.hpp"

using namespace internal;


std::string patterns::S_Rd_Rn_data(const u32 code, const std::string&instruction, const settings& settings) {
    const std::string shifter_operand = shifters::data(code, settings);

    const std::string Rd = util::reg_string(code, 12, 15, settings);
    const std::string Rn = util::reg_string(code, 16, 19, settings);

    const char* S = (llarm::util::bit_fetch(code, 20) ? "S" : "");

    const bool suf = settings.cond_always_suffix;

    return util::make_string(
        instruction, (suf ? S : ""), util::cond(code, settings), (suf ? "" : S), " ", Rd, ", ", Rn, ", ", shifter_operand
    );
}


std::string patterns::Rn_data(const u32 code, const std::string&instruction, const settings& settings) {
    const std::string shifter_operand = shifters::data(code, settings);

    const std::string Rn = util::reg_string(code, 16, 19, settings);

    return util::make_string(
        instruction,  util::cond(code, settings), " ", Rn, ", ", shifter_operand
    );
}


std::string patterns::S_Rd_data(const u32 code, const std::string&instruction, const settings& settings, const bool aliasing) {
    const shifter_id shift_id = shifters::identify_data_shifter(code);
    
    const std::string Rd = util::reg_string(code, 12, 15, settings);

    if (settings.equivalent_alias && aliasing) {
        const char* alias_inst = ERROR;

        bool is_reg = false;
        bool is_imm = false;

        switch (shift_id) {
            case shifter_id::DATA_REG_LSL: alias_inst = "LSL"; is_reg = true; break;
            case shifter_id::DATA_REG_LSR: alias_inst = "LSR"; is_reg = true; break;
            case shifter_id::DATA_REG_ASR: alias_inst = "ASR"; is_reg = true; break;
            case shifter_id::DATA_REG_ROR: alias_inst = "ROR"; is_reg = true; break;
            case shifter_id::DATA_IMM_LSR: alias_inst = "LSR"; is_imm = true; break;
            case shifter_id::DATA_IMM_LSL: alias_inst = "LSL"; is_imm = true; break;
            case shifter_id::DATA_IMM_ASR: alias_inst = "ASR"; is_imm = true; break;
            case shifter_id::DATA_IMM_ROR: alias_inst = "ROR"; is_imm = true; break;
            case shifter_id::DATA_RRX: alias_inst = "RRX"; break;
            default: break;
        }

        if (alias_inst != ERROR) {
            const std::string second = util::reg_string(code, 0, 3, settings);;
            std::string third = {};

            if (is_reg) {
                third = util::reg_string(code, 8, 11, settings);
            } else if (is_imm) {
                u8 shift_imm = llarm::util::bit_range<u8>(code, 7, 11); 

                if (shift_imm == 0) {
                    shift_imm = 32;
                }

                if (settings.hex) {
                    third += "#";
                    third += util::hex(shift_imm, settings);
                } else {
                    third += std::to_string(shift_imm);
                }
            }

            return util::make_string(
                alias_inst, util::cond(code, settings), " ", Rd, ", ", second, (third.empty() ? "" : ", "), third
            );
        }
    }

    const std::string shifter_operand = shifters::data(code, shift_id, settings);

    const char* S = (llarm::util::bit_fetch(code, 20) ? "S" : "");
    const bool suf = settings.cond_always_suffix;

    return util::make_string(
        instruction, (suf ? S : ""), util::cond(code, settings), (suf ? "" : S), " ", Rd, ", ", shifter_operand
    );
}


std::string patterns::psr_fields(const u32 code) {
    const bool R = (llarm::util::bit_fetch(code, 22));
    
    std::string fields(5, '\0');

    fields += (R ? "SPSR" : "CPSR");

    const u8 field_mask = llarm::util::bit_range<u8>(code, 16, 19);

    if (field_mask != 0) {
        fields += '_';

        // capstone does it in this order, so i'm replicating it
        if (llarm::util::bit_fetch(field_mask, 3)) { fields += 'f'; }
        if (llarm::util::bit_fetch(field_mask, 2)) { fields += 's'; }
        if (llarm::util::bit_fetch(field_mask, 1)) { fields += 'x'; }
        if (field_mask & 1) { fields += 'c'; }
    }

    return fields;
}


std::string patterns::mul_Hi_Lo(const u32 code, const std::string&instruction, const settings& settings) {
    const std::string Rm = util::reg_string(code, 0, 3, settings);
    const std::string Rs = util::reg_string(code, 8, 11, settings);
    const std::string RdHi = util::reg_string(code, 16, 19, settings);
    const std::string RdLo = util::reg_string(code, 12, 15, settings);

    const char* S = (llarm::util::bit_fetch(code, 20) ? "S" : "");

    const bool suf = settings.cond_always_suffix;

    return util::make_string(
        instruction, (suf ? S : ""), util::cond(code, settings), (suf ? "" : S), " ", RdLo, ", ", RdHi, ", ", Rm, ", ", Rs
    );
}




std::string patterns::dsp_Rd_Rm_Rn(const u32 code, const std::string&instruction, const settings& settings) {
    const std::string Rd = util::reg_string(code, 12, 15, settings);
    const std::string Rm = util::reg_string(code, 0, 3, settings);
    const std::string Rn = util::reg_string(code, 16, 19, settings);

    return util::make_string(
        instruction, util::cond(code, settings), " ", Rd, ", ", Rm, ", ", Rn
    );
}

std::string patterns::vfp_Dd_Dm(const u32 code, const std::string&instruction, const settings& settings) {
    const std::string Dd = util::reg_string(code, 12, 15, settings, util::prefix::D);
    const std::string Dm = util::reg_string(code, 0, 3, settings, util::prefix::D);

    return util::make_string(
        instruction, util::cond(code, settings), " ", Dd, ", ", Dm
    ); 
}


std::string patterns::vfp_Dd_Dn_Dm(const u32 code, const std::string&instruction, const settings& settings) {
    const std::string Dd = util::reg_string(code, 12, 15, settings, util::prefix::D);
    const std::string Dn = util::reg_string(code, 16, 19, settings, util::prefix::D);
    const std::string Dm = util::reg_string(code, 0, 3, settings, util::prefix::D);

    return util::make_string(
        instruction, util::cond(code, settings), " ", Dd, ", ", Dn, ", ", Dm
    );
}


std::string patterns::vfp_Sd_Sm(const u32 code, const std::string&instruction, const settings& settings) {
    const bool D = (llarm::util::bit_fetch(code, 22));
    const bool M = (llarm::util::bit_fetch(code, 5));

    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D, settings);
    const std::string Sm = util::vfp_reg_string_bits(code, 0, 3, M, settings);

    return util::make_string(
        instruction, util::cond(code, settings),  " ", Sd, ", ", Sm
    ); 
}


std::string patterns::vfp_Sd_Sm_Z(const u32 code, const std::string&semi_instruction, const settings& settings) {
    const bool D = (llarm::util::bit_fetch(code, 22));
    const bool M = (llarm::util::bit_fetch(code, 5));

    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D, settings);
    const std::string Sm = util::vfp_reg_string_bits(code, 0, 3, M, settings);

    const char* Z = (llarm::util::bit_fetch(code, 7) ? "ZS" : "S");

    std::string tmp = util::make_string(semi_instruction, Z, util::cond(code, settings), " ", Sd, ", ", Sm);

    if (settings.capitals == false) {
        llarm::util::to_lower(tmp);
    }

    return tmp;
}


std::string patterns::vfp_Sd_Dm_Z(const u32 code, const std::string&semi_instruction, const settings& settings) {
    const bool D = (llarm::util::bit_fetch(code, 22));
   
    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D, settings);
    const std::string Dm = util::reg_string(code, 0, 3,  settings, util::prefix::D);

    const char* Z = (llarm::util::bit_fetch(code, 7) ? "ZD" : "D");

    std::string tmp = util::make_string(semi_instruction, Z, util::cond(code, settings), " ", Sd, ", ", Dm);

    if (settings.capitals == false) {
        llarm::util::to_lower(tmp);
    }

    return tmp;
}


std::string patterns::vfp_Sd_Sn_Sm(const u32 code, const std::string&instruction, const settings& settings) {
    const bool D = (llarm::util::bit_fetch(code, 22));
    const bool N = (llarm::util::bit_fetch(code, 7));
    const bool M = (llarm::util::bit_fetch(code, 5));

    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D, settings);
    const std::string Sn = util::vfp_reg_string_bits(code, 16, 19, N, settings);
    const std::string Sm = util::vfp_reg_string_bits(code, 0, 3, M, settings);

    return util::make_string(
        instruction, util::cond(code, settings),  " ", Sd, ", ", Sn, ", ", Sm
    );
}


std::string patterns::vfp_Dd_Sm(const u32 code, const std::string&instruction, const settings& settings) {
    const bool M = (llarm::util::bit_fetch(code, 5));
   
    const std::string Sm = util::vfp_reg_string_bits(code, 0, 3, M, settings);
    const std::string Dd = util::reg_string(code, 12, 15, settings, util::prefix::D);

    return util::make_string(
        instruction, util::cond(code, settings),  " ", Dd, ", ", Sm
    );
}


std::string patterns::vfp_Rd_Dn(const u32 code, const std::string&instruction, const settings& settings) {
    const std::string Rd = util::reg_string(code, 12, 15, settings, util::prefix::R);
    const std::string Dn = util::reg_string(code, 16, 19, settings, util::prefix::D);

    return util::make_string(
        instruction, util::cond(code, settings),  " ", Rd, ", ", Dn
    );
}


std::string patterns::vfp_Dn_Rd(const u32 code, const std::string&instruction, const settings& settings) {
    const std::string Rd = util::reg_string(code, 12, 15, settings, util::prefix::R);
    const std::string Dn = util::reg_string(code, 16, 19, settings, util::prefix::D);

    return util::make_string(
        instruction, util::cond(code, settings), " ", Dn, ", ", Rd
    );
}


std::string patterns::vfp_Sd(const u32 code, const std::string&instruction, const settings& settings) {
    const bool D = (llarm::util::bit_fetch(code, 22));

    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D, settings);

    return util::make_string(
        instruction, util::cond(code, settings), " ", Sd
    ); 
}


std::string patterns::vfp_Dd(const u32 code, const std::string&instruction, const settings& settings) {
    const std::string Dd = util::reg_string(code, 12, 15, settings, util::prefix::D);

    return util::make_string(
        instruction, util::cond(code, settings), " ", Dd
    ); 
}