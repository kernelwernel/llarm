#include "../shifters.hpp"
#include "../../../util.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"

#include <string>

using namespace internal;


std::string shifters::ls_imm(const u32 code) {
    const std::string Rn = util::reg_string(code, 16, 19);
    const u16 offset_12 = shared::util::bit_fetcher(code, 0, 11);

    const char* op = (((code & (1 << 23)) == 0) ? "-" : "");

    return util::make_string("[", Rn, ", #", op, util::hex(offset_12), "]");
}




std::string shifters::ls_imm_pre(const u32 code) {
    return (ls_imm(code) + "!");
}


std::string shifters::ls_imm_post(const u32 code) {
    const std::string Rn = util::reg_string(code, 16, 19);
    const u16 offset_12 = shared::util::bit_fetcher(code, 0, 11);

    const char* op = (((code & (1 << 23)) == 0) ? "-" : "");

    return util::make_string("[", Rn, "], #", op, util::hex(offset_12));
}


std::string shifters::ls_reg(const u32 code) {
    const std::string Rn = util::reg_string(code, 16, 19);
    const std::string Rm = util::reg_string(code, 0, 3);

    const char* op = (((code & (1 << 23)) == 0) ? "-" : "");

    return util::make_string("[", Rn, ", ", op, Rm, "]");
}


std::string shifters::ls_reg_pre(const u32 code) {
    return (ls_reg(code) + "!");
}


std::string shifters::ls_reg_post(const u32 code) {
    const std::string Rn = util::reg_string(code, 16, 19);
    const std::string Rm = util::reg_string(code, 0, 3);

    const char* op = (((code & (1 << 23)) == 0) ? "-" : "");

    return util::make_string("[", Rn, "], ", op, Rm);
}




std::string shifters::ls_reg_scaled(const u32 code, const sv mode) {
    const std::string Rn = util::reg_string(code, 16, 19);
    const std::string Rm = util::reg_string(code, 0, 3);

    const u8 shift_imm = shared::util::bit_fetcher(code, 7, 11);

    const char* op = (((code & (1 << 23)) == 0) ? "-" : "");

    return util::make_string("[", Rn, ", ", op, Rm, ", ", mode, " #", util::hex(shift_imm), "]");
}


std::string shifters::ls_reg_scaled_pre(const u32 code, const sv mode) {
    return (ls_reg_scaled(code, mode) + "!");
}


std::string shifters::ls_reg_scaled_post(const u32 code, const sv mode) {
    const std::string Rn = util::reg_string(code, 16, 19);
    const std::string Rm = util::reg_string(code, 0, 3);

    const u8 shift_imm = shared::util::bit_fetcher(code, 7, 11);

    const char* op = (((code & (1 << 23)) == 0) ? "-" : "");

    return util::make_string("[", Rn, "], ", op, Rm, ", ", mode, " #", util::hex(shift_imm));
}


std::string shifters::ls_reg_scaled_rrx(const u32 code) {
    const std::string Rn = util::reg_string(code, 16, 19);
    const std::string Rm = util::reg_string(code, 0, 3);

    const u8 shift_imm = shared::util::bit_fetcher(code, 7, 11);

    const char* op = (((code & (1 << 23)) == 0) ? "-" : "");

    return util::make_string("[", Rn, ", ", op, Rm, ", RRX]");
}


std::string shifters::ls_reg_scaled_pre_rrx(const u32 code) {
    return (ls_reg_scaled_rrx(code) + "!");
}


std::string shifters::ls_reg_scaled_post_rrx(const u32 code) {
        const std::string Rn = util::reg_string(code, 16, 19);
    const std::string Rm = util::reg_string(code, 0, 3);

    const u8 shift_imm = shared::util::bit_fetcher(code, 7, 11);

    const char* op = (((code & (1 << 23)) == 0) ? "-" : "");

    return util::make_string("[", Rn, "], ", op, Rm, ", RRX");
}