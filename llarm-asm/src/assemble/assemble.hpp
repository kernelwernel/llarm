#pragma once

#include "../interpreter/IR_struct.hpp"
#include "shared/types.hpp"
#include <string>

namespace internal::assemble {
    u32 arm(const std::string &code, const u32 PC = 0);
    u16 thumb(const std::string &code);

    u32 arm(const IR_arm_struct &IR);
    //u16 thumb(const IR_thumb_struct &IR);
}