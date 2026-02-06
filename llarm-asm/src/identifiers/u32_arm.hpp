#pragma once

#include "../id/instruction_id.hpp"

#include <llarm/shared/types.hpp>

namespace internal::ident::u32_arm {
    arm_id misc_instructions(const u32 code);
    arm_id multiply_extra_load_store(const u32 code);
    arm_id unconditional(const u32 code);
    arm_id data_processing(const u32 code);
    arm_id load_store(const u32 code);
    arm_id vfp_single(const u32 code);
    arm_id vfp_double(const u32 code);

    arm_id arm(const u32 code);
}