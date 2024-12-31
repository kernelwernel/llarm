#pragma once

#include "types.hpp"
#include "id.hpp"

#include <tuple>

using decoded_t = std::pair<id::instruction, code_t>;
using thumb_decoded_t = std::pair<id::instruction, thumbcode_t>;