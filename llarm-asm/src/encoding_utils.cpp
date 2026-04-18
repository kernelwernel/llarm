#include "encoding_utils.hpp"
#include <llarm/shared/util.hpp>

bool encoders::is_imm_encodable(const u32 imm) {
    // 1 byte immeds are always encodable
    if ((imm & 0xFFFFFF00) == 0) {
        return true;
    }

    // try every possible rotation
    for (u8 rot = 0; rot < 32; rot += 2) {
        const u32 rotated = llarm::util::rotr(imm, rot);

        if ((rotated & 0xFFFFFF00) == 0) {
            return true;
        }
    }

    return false;
}


void encoders::encode_imm(u32 &binary, const u32 immed) {
    for (u8 rot = 0; rot < 16; ++rot) {
        u32 rotated = llarm::util::rotr(immed, rot * 2);
        if ((rotated & 0xFFFFFF00) == 0) {
            llarm::util::swap_bits(binary, 8, 11, rotated);
            llarm::util::swap_bits(binary, 0, 7, immed);
            break;
        }
    }
}


bool encoders::is_branch_target_valid(const u32 PC, const u32 target_address) {
    const i64 offset = static_cast<i64>(target_address) - (static_cast<i64>(PC) + 8);
    return !(offset & 0x3) && offset >= -33554432 && offset <= 33554428;
}