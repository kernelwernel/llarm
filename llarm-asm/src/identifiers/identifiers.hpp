#pragma once

#include "../instruction_id.hpp"
#include "../settings.hpp"

#include "shared/types.hpp"

namespace internal::identifiers {
    id::arm misc_instructions(const u32 code);
    id::arm multiply_extra_load_store(const u32 code);
    id::arm unconditional(const u32 code, const settings &settings);
    id::arm data_processing(const u32 code);
    id::arm load_store(const u32 code);
    id::arm vfp_single(const u32 code);
    id::arm vfp_double(const u32 code);

    id::arm arm(const arm_code_t &code, const settings &settings = default_settings());
    id::arm arm(const u32 code, const settings &settings = default_settings());
    //id::arm arm(const std::string string_code);

    id::thumb thumb(const thumb_code_t &code);
    id::thumb thumb(const u16 code);
    //id::thumb thumb(const std::string code);
}