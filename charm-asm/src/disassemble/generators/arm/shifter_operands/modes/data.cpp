#include "../shifters.hpp"
#include "../../../util.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"

#include <string>

using namespace internal;

// reference: A5-6
std::string shifters::data_imm(const u32 code) {
    const u8 rotate_imm = shared::util::bit_fetcher<u8>(code, 8, 11);
    const u8 immed_8 = shared::util::bit_fetcher<u8>(code, 0, 7);
    return util::make_string("#", std::rotr(immed_8, (rotate_imm * 2)));
}


// reference: A5-8
std::string shifters::data_reg(const u32 code) {
    return util::reg_string(code, 0, 3);
}


// reference: A5-17
std::string shifters::data_rrx(const u32 code) {
    return util::make_string(util::reg_string(code, 0, 3), ", RRX");
}


std::string shifters::data_reg_pattern(const u32 code, const sv mode) {
    const std::string Rs = util::reg_string(code, 8, 11);
    const std::string Rm = util::reg_string(code, 0, 3);
    return util::make_string(Rm, ", ", mode, " ", Rs);
}


std::string shifters::data_imm_pattern(const u32 code, const sv mode) {
    const u8 shift_imm = shared::util::bit_fetcher<u8>(code, 7, 11);
    const std::string Rm = util::reg_string(code, 0, 3);
    return util::make_string(Rm, ", ", mode, " #", shift_imm);
}