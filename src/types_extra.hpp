#pragma once

#include "types.hpp"
#include "id.hpp"

#include <tuple>

using arm_decoded_t = std::pair<id::arm_instruction, arm_code_t>;
using thumb_decoded_t = std::pair<id::thumb_instruction, thumb_code_t>;