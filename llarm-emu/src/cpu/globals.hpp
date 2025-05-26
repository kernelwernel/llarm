#pragma once

#include "../id.hpp"

struct GLOBALS {
    id::instruction_sets instruction_set;
    bool is_privileged;
    bool mpu_address_change;
    bool is_little_endian;
};