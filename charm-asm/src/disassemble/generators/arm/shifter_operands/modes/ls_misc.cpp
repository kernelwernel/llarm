#include "../shifters.hpp"
#include "../../../util.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"

#include <string>

using namespace internal;


std::string shifters::ls_misc_imm(const u32 code) {
    const std::string Rn = util::reg_string(code, 16, 19);
    const u8 immedH = shared::util::bit_fetcher(code, 8, 11);
    const u8 immedL = shared::util::bit_fetcher(code, 0, 3);
    const u8 offset_8 = ((immedH << 4) | immedL);

    const char* op = (((code & (1 << 23)) == 0) ? "-" : "");

    return util::make_string("[", Rn, ", #", op, util::hex(offset_8), "]");
}


std::string shifters::ls_misc_imm_pre(const u32 code) {
    return (ls_misc_imm(code) + "!");
}


std::string shifters::ls_misc_imm_post(const u32 code) {
    const std::string Rn = util::reg_string(code, 16, 19);
    const u8 immedH = shared::util::bit_fetcher(code, 8, 11);
    const u8 immedL = shared::util::bit_fetcher(code, 0, 3);
    const u8 offset_8 = ((immedH << 4) | immedL);

    const char* op = (((code & (1 << 23)) == 0) ? "-" : "");

    return util::make_string("[", Rn, "], #", op, util::hex(offset_8));
}


std::string shifters::ls_misc_reg(const u32 code) {
    const std::string Rn = util::reg_string(code, 16, 19);
    const std::string Rm = util::reg_string(code, 0, 3);

    const char* op = (((code & (1 << 23)) == 0) ? "-" : "");

    return util::make_string("[", Rn, ", ", op, Rm, "]");
}


std::string shifters::ls_misc_reg_pre(const u32 code) {
    return (ls_misc_reg(code) + "!");
}


std::string shifters::ls_misc_reg_post(const u32 code) {
    const std::string Rn = util::reg_string(code, 16, 19);
    const std::string Rm = util::reg_string(code, 0, 3);

    const char* op = (((code & (1 << 23)) == 0) ? "-" : "");

    return util::make_string("[", Rn, "], ", op, Rm);
}

