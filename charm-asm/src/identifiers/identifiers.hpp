#pragma once

#include "../instruction_id.hpp"

#include "shared/types.hpp"
#include "shared/out.hpp"

#include <bitset>

namespace internal::identifiers {
    id::arm arm(const arm_code_t &raw_code);
    id::arm arm(const u32 raw_code);
    id::arm arm(const std::string string_code);

    id::thumb thumb(const thumb_code_t &raw_code);
    id::thumb thumb(const u16 raw_code);
    id::thumb thumb(const std::string string_code);

    id::jazelle jazelle(const u8 opcode);
}