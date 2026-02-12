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