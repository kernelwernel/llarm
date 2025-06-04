#pragma once

#include "../id.hpp"

struct GLOBALS {
    id::instruction_sets instruction_set;
    bool is_privileged;
    bool is_little_endian;
    bool mpu_address_change;
    bool mpu_inst_address_change;
    bool mpu_data_address_change;
};