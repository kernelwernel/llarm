#pragma once

#include "types.hpp"

namespace shared::util {
    // 0-based counting btw
    template <typename T>
    inline T bit_range(const arm_code_t &input, const u8 start, const u8 end) {
        if (start >= end) [[unlikely]] {
            // TODO: think of an error
        }

        const u32 mask = ((1U << (end - start + 1)) - 1);
        return static_cast<T>((input.to_ulong() >> start) & mask);
    }

    template <typename T>
    inline T bit_range(const thumb_code_t &input, const u8 start, const u8 end) {
        if (start >= end) [[unlikely]] {
            // TODO: think of an error
        }

        const u32 mask = ((1U << (end - start + 1)) - 1);
        return static_cast<T>((input.to_ulong() >> start) & mask);
    }

    template <typename T, typename M>
    inline T bit_range(const M input, const u8 start, const u8 end) {
        if (start >= end) [[unlikely]] {
            // TODO: think of an error
        }

        const M mask = static_cast<M>((1U << (end - start + 1)) - 1);
        return static_cast<T>((input >> start) & mask);
    }

    inline u32 bit_range(const u32 input, const u8 start, const u8 end) {
        if (start >= end) [[unlikely]] {
            // TODO: think of an error
        }

        u32 copy = input;

        copy <<= (31 - end);
        copy >>= (31 - end + start);

        return copy;
    }

    inline u32 bit_range(const arm_code_t &input, const u8 start, const u8 end) {
        return bit_range(static_cast<u32>(input.to_ulong()), start, end);
    }

    inline bool bit_fetch(const u32 input, const u8 index) {
        return ((input >> index) & 1);
    }

    // util::popcount only works for C++20, while
    // built-in functions are compiler-specific,
    // so to simplify all of this compatibility 
    // mess, i'm just going to use the std::bitset
    // version of it. The compiler should be able
    // to optimise this away with at least -O1:
    // https://godbolt.org/z/qEjaEz9zq
    inline u8 popcount(const u32 integer) {
        return static_cast<u8>(std::bitset<32>(integer).count());
    }
}

// https://quick-bench.com/q/JqnAzdyhgQ9yuc4WflaEe_3tciE