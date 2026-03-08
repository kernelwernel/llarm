#pragma once

#include "../interpreter/IR_struct.hpp"
#include <llarm/shared/types.hpp>
#include <string>

namespace internal::assemble {
    constexpr u32 ARM_UNDEFINED = 0xE7F000F0;
    constexpr u16 THUMB_UNDEFINED = 0xDE00; 

    u32 arm(const std::string &code, const u32 PC = 0);
    u32 thumb(const std::string &code, const u32 PC = 0);

    u32 arm(const IR_arm_struct &IR);
    u32 thumb(const IR_thumb_struct &IR);
}