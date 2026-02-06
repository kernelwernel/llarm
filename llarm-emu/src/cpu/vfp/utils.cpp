#include "utils.hpp"

#include <cmath>
#include <cstring>

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>


double vfp_utils::u64_to_double(const u64 value) {
    double d;
    std::memcpy(&d, &value, sizeof(d));
    return d;
}

float vfp_utils::u32_to_single(const u32 value) {
    float d;
    std::memcpy(&d, &value, sizeof(d));
    return d;
}

u64 vfp_utils::double_to_u64(const double value) {
    u64 ret = 0;
    std::memcpy(&ret, &value, sizeof(ret));
    return ret;
}

u32 vfp_utils::single_to_u32(const float value) {
    u32 ret = 0;
    std::memcpy(&ret, &value, sizeof(ret));
    return ret;
}

bool vfp_utils::is_signaling_nan(const float value) {
    if (std::isnan(value) == false) {
        return false;
    }

    return (llarm::util::bit_fetch(value, 22) == false); // is not quiet
}

bool vfp_utils::is_quiet_nan(const float value) {
    if (std::isnan(value) == false) {
        return false;
    }

    return llarm::util::bit_fetch(value, 22); // is quiet
}