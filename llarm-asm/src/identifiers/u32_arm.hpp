#pragma once

#include "../instruction_id.hpp"

#include "shared/types.hpp"

namespace internal::ident::u32_arm {
    id::arm misc_instructions(const u32 code);
    id::arm multiply_extra_load_store(const u32 code);
    id::arm unconditional(const u32 code);
    id::arm data_processing(const u32 code);
    id::arm load_store(const u32 code);
    id::arm vfp_single(const u32 code);
    id::arm vfp_double(const u32 code);

    id::arm arm(const u32 code);
}