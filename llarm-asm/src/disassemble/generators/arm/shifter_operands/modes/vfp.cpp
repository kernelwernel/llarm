#include "../shifters.hpp"

#include <string>

using namespace internal;


std::string shifters::vfp_ls_mul_unindexed(const settings settings) {
    if (settings.capitals) {
        return "IA";
    } else {
        return "ia";
    }
}


std::string shifters::vfp_ls_mul_inc(const settings settings) {
    if (settings.capitals) {
        return "IA";
    } else {
        return "ia";
    }
}

std::string shifters::vfp_ls_mul_dec(const settings settings) {
    if (settings.capitals) {
        return "DB";
    } else {
        return "db";
    }
}