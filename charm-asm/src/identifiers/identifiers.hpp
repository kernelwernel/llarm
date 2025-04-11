#pragma once

#include "../instruction_id.hpp"
#include "../../../shared/types.hpp"
#include "../../../shared/out.hpp"

#include <bitset>

namespace internal::identifiers {
    static id::arm arm_identifier(const arm_code_t &raw_code);
    static id::arm arm_identifier(const u32 &raw_code);

    static id::thumb thumb_identifier(const thumb_code_t &raw_code);
    static id::thumb thumb_identifier(const u16 &raw_code);

    static id::jazelle jazelle_identifier(const u8 raw_code);
}