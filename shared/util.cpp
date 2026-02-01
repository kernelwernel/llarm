#include "util.hpp"
#include "types.hpp"
#include "string_view.hpp"

using namespace llarm;

u32 util::bit_range(const u32 input, const u8 start, const u8 end) {
    if (start >= end) [[unlikely]] {
        // TODO: think of an error
    }

    u32 copy = input;

    copy <<= (31 - end);
    copy >>= (31 - end + start);

    return copy;
}


std::string util::to_upper(const std::string& str) {
    std::string tmp = str;

    for (char& c : tmp) {
        c = (c >= 'a' && c <= 'z') ? (c & ~0x20) : c;
    }

    return tmp;
}


void util::to_lower(std::string& str) {
    for (char& c : str) {
        c = (c >= 'A' && c <= 'Z') ? (c | 0x20) : c;
    }
}

// https://quick-bench.com/q/JqnAzdyhgQ9yuc4WflaEe_3tciE