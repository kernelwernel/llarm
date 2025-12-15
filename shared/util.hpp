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

    inline u32 bit_range(const u32 input, const u8 start, const u8 end) {
        if (start >= end) [[unlikely]] {
            // TODO: think of an error
        }

        u32 copy = input;

        copy <<= (31 - end);
        copy >>= (31 - end + start);

        return copy;
    }

    template <typename T, std::size_t N>
    inline T bit_range(const std::bitset<N> &input, const u8 start, const u8 end) {
        const u32 range = input.to_ulong();
        return bit_range<T>(range, start, end);
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


    inline u8 get_lsb_index(u32 integer) {
        if (integer == 0) { 
            return 255;
        }

        u8 index = 0;
    
        while ((integer & 1) == 0) {
            integer >>= 1;
            ++index;
        }

        return index;
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

    inline void swap_bits(u32 &original, const u8 start, const u8 end, const u32 value) {
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

    inline void to_lower(std::string& str) {
        for (char& c : str) {
            c = (c >= 'A' && c <= 'Z') ? (c | 0x20) : c;
        }
    }

    inline std::string to_upper(const std::string& str) {
        std::string tmp = str;

        for (char& c : tmp) {
            c = (c >= 'a' && c <= 'z') ? (c & ~0x20) : c;
        }

        return tmp;
    }

    // this assumes the str has already been checked beforehand
    inline u32 str_to_u32(const llarm::string_view str) {
        u32 num = 0;

        for (const unsigned char c : str) {
            // convert to int
            if (c >= '0' && c <= '9') {
                num = num * 10 + (c - '0');
            }
        }

        return num;
    }

    inline i64 hex_to_i64(const llarm::string_view str) {
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