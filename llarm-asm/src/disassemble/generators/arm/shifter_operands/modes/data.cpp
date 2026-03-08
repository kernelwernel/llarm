#include "../shifters.hpp"
#include "../../../util.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>

#include <string>

using namespace internal;

// reference: A5-6
std::string shifters::data_imm(const u32 code, const settings& settings) {
    const u8 rotate_imm = llarm::util::bit_range<u8>(code, 8, 11);
    const u8 immed_8 = llarm::util::bit_range<u8>(code, 0, 7);

    const u8 rotate_count = rotate_imm * 2;
 
//    const std::string rotate_str = [&]() -> std::string {
//        if ((settings.remove_nulls && rotate_count == 0) || settings.explicit_rotation == false) {
//            return "";
//        }
//        return util::make_string(", #", rotate_count);
//    }();
//
//    return util::make_string(
//        "#", util::hex(llarm::util::rotr(immed_8, rotate_count), settings), rotate_str
//    );


    const u32 immed_32 = static_cast<u32>(immed_8);
    const u32 rotated  = rotate_count == 0 ? immed_32 : (immed_32 >> rotate_count) | (immed_32 << (32 - rotate_count));

    if (rotate_count == 0 || rotated <= 0xFF) {
        // fits in 8 bits, show raw fields
        if (rotate_count == 0) {
            return util::make_string("#", util::hex(immed_8, settings));
        }
        return util::make_string("#", immed_8, ", #", rotate_count);
    } else {
        // doesn't fit in 8 bits, show rotated value
        return util::make_string("#", util::hex(rotated, settings));
    }
}


// reference: A5-8
std::string shifters::data_reg(const u32 code, const settings& settings) {
    return util::reg_string(code, 0, 3, settings);
}


// reference: A5-17
std::string shifters::data_rrx(const u32 code, const settings& settings) {
    return util::make_string(util::reg_string(code, 0, 3, settings), ", RRX");
}


std::string shifters::data_reg_pattern(const u32 code, const std::string &mode, const settings& settings) {
    const std::string Rs = util::reg_string(code, 8, 11, settings);
    const std::string Rm = util::reg_string(code, 0, 3, settings);
    return util::make_string(Rm, ", ", mode, " ", Rs);
}


std::string shifters::data_imm_pattern(const u32 code, const std::string &mode, const settings& settings) {
    u8 shift_imm = llarm::util::bit_range<u8>(code, 7, 11);

    if (shift_imm == 0) {
        shift_imm = 32;
    }

    const std::string Rm = util::reg_string(code, 0, 3, settings);
    return util::make_string(Rm, ", ", mode, " #", shift_imm);
}