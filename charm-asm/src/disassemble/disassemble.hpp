#pragma once

#include <charm/internal/shared/types.hpp>

#include <string>

namespace internal::disassemble {
    std::string thumb(const u16 code);

    //std::string arm(const u32 code);
}