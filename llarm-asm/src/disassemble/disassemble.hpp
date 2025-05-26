#pragma once

#include "../settings.hpp"

#include "shared/types.hpp"

#include <string>

namespace internal::disassemble {
    std::string thumb_generate(const u16 code, const u32 PC, const settings settings);
    std::string arm_generate(const u32 code, const u32 PC, const settings settings);

    std::string thumb(const u16 code, const u32 PC = 0, const settings settings = default_settings());
    std::string arm(const u32 code, const u32 PC = 0, const settings settings = default_settings());
}