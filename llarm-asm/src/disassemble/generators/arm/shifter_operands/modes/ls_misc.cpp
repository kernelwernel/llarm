#include "../shifters.hpp"
#include "../../../util.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"

#include <string>

using namespace internal;


std::string shifters::ls_misc_imm(const u32 code, const settings settings) {
    const u8 immedH = shared::util::bit_range<u8>(code, 8, 11);
    const u8 immedL = shared::util::bit_range<u8>(code, 0, 3);
    const u8 offset_8 = static_cast<u8>((immedH << 4) | immedL);
    const std::string Rn = util::reg_string(code, 16, 19, settings);
    
    if ((offset_8 == 0) && settings.remove_nulls) {
        return util::make_string("[", Rn, "]");
    }
    
    const char* op = ((shared::util::bit_fetch(code, 23) == 0) ? "-" : "");

    return util::make_string("[", Rn, ", #", op, util::hex(offset_8, settings), "]");
}


std::string shifters::ls_misc_imm_pre(const u32 code, const settings settings) {
    return (ls_misc_imm(code, settings) + "!");
}


std::string shifters::ls_misc_imm_post(const u32 code, const settings settings) {
    const std::string Rn = util::reg_string(code, 16, 19, settings);
    const u8 immedH = shared::util::bit_range<u8>(code, 8, 11);
    const u8 immedL = shared::util::bit_range<u8>(code, 0, 3);
    const u8 offset_8 = static_cast<u8>((immedH << 4) | immedL);

    if ((offset_8 == 0) && settings.remove_nulls) {
        return util::make_string("[", Rn, "]");
    }

    const char* op = ((shared::util::bit_fetch(code, 23) == 0) ? "-" : "");

    return util::make_string("[", Rn, "], #", op, util::hex(offset_8, settings));
}


std::string shifters::ls_misc_reg(const u32 code, const settings settings) {
    const std::string Rn = util::reg_string(code, 16, 19, settings);
    const std::string Rm = util::reg_string(code, 0, 3, settings);

    const char* op = ((shared::util::bit_fetch(code, 23) == 0) ? "-" : "");

    return util::make_string("[", Rn, ", ", op, Rm, "]");
}


std::string shifters::ls_misc_reg_pre(const u32 code, const settings settings) {
    return (ls_misc_reg(code, settings) + "!");
}


std::string shifters::ls_misc_reg_post(const u32 code, const settings settings) {
    const std::string Rn = util::reg_string(code, 16, 19, settings);
    const std::string Rm = util::reg_string(code, 0, 3, settings);

    const char* op = ((shared::util::bit_fetch(code, 23) == 0) ? "-" : "");

    return util::make_string("[", Rn, "], ", op, Rm);
}

