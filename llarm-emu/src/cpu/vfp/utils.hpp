#pragma once

#include "shared/types.hpp"

namespace vfp_utils {
    double u64_to_double(const u64 value);
    float u32_to_single(const u32 value);

    u64 double_to_u64(const double value);
    u32 single_to_u32(const float value);

    bool is_signaling_nan(const float value);
    bool is_quiet_nan(const float value);
};