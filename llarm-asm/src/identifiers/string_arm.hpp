#pragma once

#include "../id/instruction_id.hpp"

#include <string>

using namespace internal;

namespace internal::ident::string_arm {
    arm_id arm(const std::string &code, const u32 PC = 0);
}