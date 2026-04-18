#pragma once

#include <llarm/shared/types.hpp>

namespace encoders {
    bool is_branch_target_valid(const u32 PC, const u32 target_address);
    bool is_imm_encodable(const u32 imm);
    void encode_imm(u32 &binary, const u32 immed);
}