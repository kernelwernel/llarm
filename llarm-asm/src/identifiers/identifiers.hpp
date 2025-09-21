#pragma once

#include "interpreter.hpp"
#include "../instruction_id.hpp"
#include "../settings.hpp"

#include "shared/types.hpp"

namespace internal::identifiers {


    // defined in u32_arm.cpp
    id::arm misc_instructions(const u32 code);
    id::arm multiply_extra_load_store(const u32 code);
    id::arm unconditional(const u32 code, const settings &settings);
    id::arm data_processing(const u32 code);
    id::arm load_store(const u32 code);
    id::arm vfp_single(const u32 code);
    id::arm vfp_double(const u32 code);
    id::arm arm(const u32 code, const settings &settings = default_settings());

    // defined in string_arm.cpp
    id::arm arm(const std::string &code);

    // defined in string_thumb.cpp
    id::thumb ADD(const std::string &code);
    id::thumb SUB(const std::string &code);
    id::thumb thumb(std::string code);

    // defined in u16_thumb.cpp
    id::thumb thumb(const u16 code);
}