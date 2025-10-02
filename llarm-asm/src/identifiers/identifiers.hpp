#pragma once

#include "../instruction_id.hpp"

#include "shared/types.hpp"

namespace internal::identifiers {
    id::arm arm(const std::string &code);
    id::arm arm(const u32 code);
    
    id::thumb thumb(const std::string &code);
    id::thumb thumb(const u16 code);
}