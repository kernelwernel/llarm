#pragma once

#include "types.hpp"
#include "string_view.hpp"

#include <bitset>

namespace llarm::util {
    template <typename T, typename M>
    inline T bit_range(const M input, const u8 start, const u8 end) {
        if (start >= end) [[unlikely]] {
            // TODO: think of an error
        }

        const M mask = static_cast<M>((1U << (end - start + 1)) - 1);
        return static_cast<T>((input >> start) & mask);
    }

    template <typename T, std::size_t N>
    inline T bit_range(const std::bitset<N> &input, const u8 start, const u8 end) {
        const u32 range = input.to_ulong();
        return bit_range<T>(range, start, end);
    }
    
    template<typename T = u32>
    inline void modify_bit(T &original, const u8 index, const bool value) {
        if (index > (sizeof(T) * 8) - 1) {
            //llarm::out::dev_error("Index for modify_bit() must be between 0 and 31");
            // TODO think of an error
        }
        
        if (value) {
            original |= (1U << index);
        } else {
            original &= ~(1U << index);
        }
    }
    
    u32 bit_range(const u32 input, const u8 start, const u8 end);

    std::string to_upper(const std::string& str);

    void to_lower(std::string& str);

    constexpr bool bit_fetch(const u32 input, const u8 index) {
        return ((input >> index) & 1);
    }

    // util::popcount only works for C++20, while
    // built-in functions are compiler-specific,
    // so to simplify all of this compatibility 
    // mess, i'm just going to use the std::bitset
    // version of it. The compiler should be able
    // to optimise this away with at least -O1:
    // https://godbolt.org/z/qEjaEz9zq
    constexpr u8 popcount(const u32 integer) {
        return static_cast<u8>(std::bitset<32>(integer).count());
    }

    constexpr void swap_bits(u32 &original, const u8 start, const u8 end, const u32 value) {
        if (start >= 32 || end >= 32 || start >= end) {
            //llarm::out::dev_error("util::swap_bits has impossible arguments");
            // TODO think of an error 
            return;
        }

        const u8 num_bits = end - start + 1;
        const u32 mask = (1 << num_bits) - 1;
        original &= ~(mask << start);
        original |= (value & mask) << start;
    }

    constexpr u32 rotr(u32 num, u8 rotate) {
        rotate &= 31;
        return (num >> rotate) | (num << (32 - rotate));
    }

    // this will generate a bsr instruction in x86, so it's portable and optimisation-friendly for compilers (https://godbolt.org/z/MxY16Ev69)
    constexpr u8 get_msb(u32 num) {
        if (num == 0) {
            return 255;
        }

        u8 i = 0;

        while (num >>= 1) {
            ++i;
        }

        return i;
    }

    // same as above, but unlike above, i couldn't find a way to make it optimise the same way how __builtin_ctz(num) would
    constexpr u8 get_lsb(u32 num) {
        if (num == 0) {
            return 255;
        }

        u8 index = 0;

        while ((num & 1u) == 0) {
            num >>= 1;
            ++index;
        }

        return index;
    }


    // this assumes the str has already been checked beforehand
    constexpr u32 str_to_u32(const sv str) {
        u32 num = 0;

        for (const char c : str) {
            // convert to int
            if (c >= '0' && c <= '9') {
                num = num * 10 + (static_cast<u32>(c) - '0');
            }
        }

        return num;
    }


    constexpr i64 hex_to_i64(const sv str) {
        i64 num = 0;

        // convert hex to i32
        for (const char c : str) {
            num <<= 4; // multiply by 16
        
            if (c >= '0' && c <= '9') {
                num += c - '0';
            } else if (c >= 'A' && c <= 'F') {
                num += c - 'A' + 10;
            }
        }

        return num;
    }
}

// https://quick-bench.com/q/JqnAzdyhgQ9yuc4WflaEe_3tciE