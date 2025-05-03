#include "patterns.hpp"
#include "../arm/shifter_operands/shifters.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"

#include <string>

#include "../util.hpp"

using namespace internal;


std::string patterns::S_Rd_Rn_data(const u32 code, const sv instruction) {
    const std::string shifter_operand = shifters::data_shifter(code);

    const std::string Rd = util::reg_string(code, 12, 15);
    const std::string Rn = util::reg_string(code, 16, 19);

    const char* S = ((code & (1 << 20)) ? "S" : "");

    return util::make_string(instruction, util::cond(code), S, " ", Rd, ", ", Rn, ", ", shifter_operand);
}


std::string patterns::Rn_data(const u32 code, const sv instruction) {
    const std::string shifter_operand = shifters::data_shifter(code);

    const std::string Rn = util::reg_string(code, 16, 19);

    return util::make_string(instruction, util::cond(code), " ", Rn, ", ", shifter_operand);
}


std::string patterns::S_Rd_data(const u32 code, const sv instruction) {
    const std::string shifter_operand = shifters::data_shifter(code);

    const std::string Rd = util::reg_string(code, 12, 15);

    const char* S = ((code & (1 << 20)) ? "S" : "");

    return util::make_string(instruction, util::cond(code), S, " ", Rd, ", ", shifter_operand);
}


std::string patterns::psr_fields(const u32 code) {
    const bool R = (code & (1 << 22));

    const char* PSR = (R ? "SPSR" : "CPSR");

    std::string fields(5, '\0');

    const u8 field_mask = shared::util::bit_fetcher<u8>(code, 16, 19);

    if (field_mask != 0) {
        fields += '_';

        // capstone does it in this order, so i'm replicating it
        if (field_mask & (1 << 3)) { fields += 'f'; }
        if (field_mask & (1 << 2)) { fields += 's'; }
        if (field_mask & (1 << 1)) { fields += 'x'; }
        if (field_mask & 1) { fields += 'c'; }
    }

    return fields;
}




std::string patterns::mul_Hi_Lo(const u32 code, const sv instruction) {
    const std::string Rm = util::reg_string(code, 0, 3);
    const std::string Rs = util::reg_string(code, 8, 11);
    const std::string RdHi = util::reg_string(code, 16, 19);
    const std::string RdLo = util::reg_string(code, 12, 15);

    const char* S = ((code & (1 << 20)) ? "S" : "");

    return util::make_string(instruction, util::cond(code), S, " ", RdLo, ", ", RdHi, ", ", Rm, ", ", Rs);
}




std::string patterns::dsp_Rd_Rm_Rn(const u32 code, const sv instruction) {
    const std::string Rd = util::reg_string(code, 12, 15);
    const std::string Rm = util::reg_string(code, 0, 3);
    const std::string Rn = util::reg_string(code, 16, 19);

    return util::make_string(instruction, util::cond(code), " ", Rd, ", ", Rm, ", ", Rn);
}

std::string patterns::vfp_Dd_Dm(const u32 code, const sv instruction) {
    const std::string Dd = util::reg_string(code, 12, 15, util::prefix::D);
    const std::string Dm = util::reg_string(code, 0, 3, util::prefix::D);

    return util::make_string(instruction, util::cond(code), " ", Dd, ", ", Dm); 
}


std::string patterns::vfp_Dd_Dn_Dm(const u32 code, const sv instruction) {
    const std::string Dd = util::reg_string(code, 12, 15, util::prefix::D);
    const std::string Dn = util::reg_string(code, 16, 19, util::prefix::D);
    const std::string Dm = util::reg_string(code, 0, 3, util::prefix::D);

    return util::make_string(instruction, util::cond(code), " ", Dd, ", ", Dn, ", ", Dm); 
}


std::string patterns::vfp_Sd_Sm(const u32 code, const sv instruction) {
    const bool D = (code & (1 << 22));
    const bool M = (code & (1 << 5));

    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D);
    const std::string Sm = util::vfp_reg_string_bits(code, 0, 3, M);

    return util::make_string(instruction, util::cond(code), " ", Sd, ", ", Sm); 
}


std::string patterns::vfp_Sd_Sm_Z(const u32 code, const sv semi_instruction) {
    const bool D = (code & (1 << 22));
    const bool M = (code & (1 << 5));

    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D);
    const std::string Sm = util::vfp_reg_string_bits(code, 0, 3, M);

    const char* Z = ((code & (1 << 7)) ? "ZS" : "S");

    return util::make_string(semi_instruction, Z, util::cond(code), " ", Sd, ", ", Sm);
}


std::string patterns::vfp_Sd_Dm_Z(const u32 code, const sv semi_instruction) {
    const bool D = (code & (1 << 22));
   
    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D);
    const std::string Dm = util::reg_string(code, 0, 3, util::prefix::D);

    const char* Z = ((code & (1 << 7)) ? "ZD" : "D");

    return util::make_string(semi_instruction, Z, util::cond(code), " ", Sd, ", ", Dm);
}


std::string patterns::vfp_Sd_Sn_Sm(const u32 code, const sv instruction) {
    const bool D = (code & (1 << 22));
    const bool N = (code & (1 << 7));
    const bool M = (code & (1 << 5));
   
    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D); 
    const std::string Sn = util::vfp_reg_string_bits(code, 16, 19, N); 
    const std::string Sm = util::vfp_reg_string_bits(code, 0, 3, M); 

    return util::make_string(instruction, util::cond(code), " ", Sd, ", ", Sn, ", ", Sm);
}


std::string patterns::vfp_Dd_Sm(const u32 code, const sv instruction) {
    const bool M = (code & (1 << 5));
   
    const std::string Sm = util::vfp_reg_string_bits(code, 0, 3, M); 
    const std::string Dd = util::reg_string(code, 12, 15, util::prefix::D);

    return util::make_string(instruction, util::cond(code), " ", Dd, ", ", Sm);
}


std::string patterns::vfp_Rd_Dn(const u32 code, const sv instruction) {
    const std::string Rd = util::reg_string(code, 12, 15, util::prefix::R);
    const std::string Dn = util::reg_string(code, 16, 19, util::prefix::D);

    return util::make_string(instruction, util::cond(code), " ", Rd, ", ", Dn);
}


std::string patterns::vfp_Dn_Rd(const u32 code, const sv instruction) {
    const std::string Rd = util::reg_string(code, 12, 15, util::prefix::R);
    const std::string Dn = util::reg_string(code, 16, 19, util::prefix::D);

    return util::make_string(instruction, util::cond(code), " ", Dn, ", ", Rd);
}


std::string patterns::vfp_Sd(const u32 code, const sv instruction) {
    const bool D = (code & (1 << 22));

    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D);

    return util::make_string(instruction, util::cond(code), " ", Sd); 
}


std::string patterns::vfp_Dd(const u32 code, const sv instruction) {
    const std::string Dd = util::reg_string(code, 12, 15, util::prefix::D);

    return util::make_string(instruction, util::cond(code), " ", Dd); 
}