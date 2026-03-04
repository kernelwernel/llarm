#pragma once

#include "IR_struct.hpp"

// this file is meant for IR (Intermediate Representation) of instructions.
// It's not exactly the same concept as what you'd hear like in compilers,
// because this is intended more as a caching structure for the sake of
// eliminating a duplication (or triplication) of effort. 

using namespace internal;

namespace IR {
    IR_arm_struct generate(const std::string &code, const u32 PC = 0);
    IR_thumb_struct generate_thumb(const std::string &code, const u32 PC = 0);
}