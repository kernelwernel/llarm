#pragma once

#include <string>
#include "shared/types.hpp"

namespace internal::assemble {
    u32 arm(const std::string &code);
    u16 thumb(const std::string &code);
}