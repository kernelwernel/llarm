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

    inline bool bit_fetch(const u32 input, const u8 index) {
        return ((input >> index) & 1);
    }
}

// https://quick-bench.com/q/JqnAzdyhgQ9yuc4WflaEe_3tciE