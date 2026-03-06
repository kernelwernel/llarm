#include "../shifters.hpp"

#include <string>

using namespace internal;


std::string shifters::ls_mul_inc_after(const settings& settings) {
    if (settings.simplify) {
        return "";
    }

    if (settings.capitals) {
        return "IA";
    } else {
        return "ia";
    }
}


std::string shifters::ls_mul_inc_before(const settings& settings) {
    if (settings.simplify) {
        return "";
    }

    if (settings.capitals) {
        return "IB";
    } else {
        return "ib";
    }
}


std::string shifters::ls_mul_dec_after(const settings& settings) {
    if (settings.simplify) {
        return "";
    }

    if (settings.capitals) {
        return "DA";
    } else {
        return "da";
    }
}


std::string shifters::ls_mul_dec_before(const settings& settings) {
    if (settings.simplify) {
        return "";
    }

    if (settings.capitals) {
        return "DB";
    } else {
        return "db";
    }
}