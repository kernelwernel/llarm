#include "../shifters.hpp"
#include "../../../util.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>

#include <string>

using namespace internal;


std::string shifters::ls_imm(const u32 code, const settings& settings) {
    const std::string Rn = util::reg_string(code, 16, 19, settings);
    const u16 offset_12 = llarm::util::bit_range<u16>(code, 0, 11);

    if ((offset_12 == 0) && settings.remove_nulls) {
        return util::make_string("[", Rn, "]");   
    }

    const char* op = ((llarm::util::bit_fetch(code, 23) == 0) ? "-" : "");

    return util::make_string("[", Rn, ", #", op, util::hex(offset_12, settings), "]");
}


std::string shifters::ls_imm_pre(const u32 code, const settings& settings) {
    return (ls_imm(code, settings) + "!");
}


std::string shifters::ls_imm_post(const u32 code, const settings& settings) {
    const std::string Rn = util::reg_string(code, 16, 19, settings);
    const u16 offset_12 = llarm::util::bit_range<u16>(code, 0, 11);
    
    if ((offset_12 == 0) && settings.remove_nulls) {
        return util::make_string("[", Rn, "]");
    }

    const char* op = ((llarm::util::bit_fetch(code, 23) == 0) ? "-" : "");

    return util::make_string("[", Rn, "], #", op, util::hex(offset_12, settings));
}


std::string shifters::ls_reg(const u32 code, const settings& settings) {
    const std::string Rn = util::reg_string(code, 16, 19, settings);
    const std::string Rm = util::reg_string(code, 0, 3, settings);

    const char* op = ((llarm::util::bit_fetch(code, 23) == 0) ? "-" : "");

    return util::make_string("[", Rn, ", ", op, Rm, "]");
}


std::string shifters::ls_reg_pre(const u32 code, const settings& settings) {
    return (ls_reg(code, settings) + "!");
}


std::string shifters::ls_reg_post(const u32 code, const settings& settings) {
    const std::string Rn = util::reg_string(code, 16, 19, settings);
    const std::string Rm = util::reg_string(code, 0, 3, settings);

    const char* op = ((llarm::util::bit_fetch(code, 23) == 0) ? "-" : "");

    return util::make_string("[", Rn, "], ", op, Rm);
}




std::string shifters::ls_reg_scaled(const u32 code, const std::string &mode, const settings& settings) {
    const std::string Rn = util::reg_string(code, 16, 19, settings);
    const std::string Rm = util::reg_string(code, 0, 3, settings);

    const u8 shift_imm = llarm::util::bit_range<u8>(code, 7, 11);

    const char* op = ((llarm::util::bit_fetch(code, 23) == 0) ? "-" : "");

    if ((shift_imm == 0) && settings.remove_nulls) {
        return util::make_string("[", Rn, ", ", op, Rm, "]");
    }

    return util::make_string("[", Rn, ", ", op, Rm, ", ", mode, " #", util::hex(shift_imm, settings), "]");
}


std::string shifters::ls_reg_scaled_pre(const u32 code, const std::string &mode, const settings& settings) {
    return (ls_reg_scaled(code, mode, settings) + "!");
}


std::string shifters::ls_reg_scaled_post(const u32 code, const std::string &mode, const settings& settings) {
    const std::string Rn = util::reg_string(code, 16, 19, settings);
    const std::string Rm = util::reg_string(code, 0, 3, settings);

    const u8 shift_imm = llarm::util::bit_range<u8>(code, 7, 11);

    const char* op = ((llarm::util::bit_fetch(code, 23) == 0) ? "-" : "");

    if ((shift_imm == 0) && settings.remove_nulls) {
        return util::make_string("[", Rn, "], ", op, Rm);
    }

    return util::make_string("[", Rn, "], ", op, Rm, ", ", mode, " #", util::hex(shift_imm, settings));
}


std::string shifters::ls_reg_scaled_rrx(const u32 code, const settings& settings) {
    const std::string Rn = util::reg_string(code, 16, 19, settings);
    const std::string Rm = util::reg_string(code, 0, 3, settings);

    const char* op = ((llarm::util::bit_fetch(code, 23) == 0) ? "-" : "");

    return util::make_string("[", Rn, ", ", op, Rm, ", RRX]");
}


std::string shifters::ls_reg_scaled_pre_rrx(const u32 code, const settings& settings) {
    return (ls_reg_scaled_rrx(code, settings) + "!");
}


std::string shifters::ls_reg_scaled_post_rrx(const u32 code, const settings& settings) {
        const std::string Rn = util::reg_string(code, 16, 19, settings);
    const std::string Rm = util::reg_string(code, 0, 3, settings);

    const char* op = ((llarm::util::bit_fetch(code, 23) == 0) ? "-" : "");

    return util::make_string("[", Rn, "], ", op, Rm, ", RRX");
}