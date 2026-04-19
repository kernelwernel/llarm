#pragma once

#include "types.hpp"
#include "out.hpp"

#include <bitset>


namespace llarm::util {
    template <typename T = u32, typename M>
    T bit_range(const M input, const u8 start, const u8 end) {
        if (start > end) [[unlikely]] {
            llarm::out::error("Invalid range in llarm::util::bit_range function");
        }

        const M mask = static_cast<M>((static_cast<u64>(1) << (end - start + 1)) - 1);
        return static_cast<T>((input >> start) & mask);
    }

    template <typename T = u32, std::size_t N>
    T bit_range(const std::bitset<N> &input, const u8 start, const u8 end) {
        const u32 range = input.to_ulong();
        return bit_range<T>(range, start, end);
    }
    
    template<typename T = u32>
    constexpr void modify_bit(T &original, const u8 index, const bool value) {
        if (index > (sizeof(T) * 8) - 1) {
            //llarm::out::dev_error("Index for modify_bit() must be between 0 and 31");
            // TODO think of an error
        }

        if (value) {
            original |= (static_cast<u64>(1) << index);
        } else {
            original &= static_cast<T>(~(1U << index));
        }
    }


    inline std::string to_upper(const std::string& str) {
        std::string tmp = str;

        for (char& c : tmp) {
            c = (c >= 'a' && c <= 'z') ? static_cast<char>(c & ~0x20) : c;

        }

        return tmp;
    }


    inline void to_lower(std::string& str) {
        for (char& c : str) {
            c = (c >= 'A' && c <= 'Z') ? static_cast<char>(c | 0x20) : c;

        }
    }


    constexpr bool bit_fetch(const u64 input, const u8 index) {
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


    constexpr void swap_bits(u32 &original, const u8 start, const u8 end, const u32 value) {
        if (start >= 32 || end >= 32 || start >= end) {
            //llarm::out::dev_error("util::swap_bits has impossible arguments");
            // TODO think of an error 
            return;
        }

        const u8 num_bits = static_cast<u8>(end - start + 1);
        const u32 mask = static_cast<u32>(1 << num_bits) - 1;
        original &= ~(mask << start);
        original |= (value & mask) << start;
    }


    constexpr void swap_bits(u16 &original, const u8 start, const u8 end, const u32 value) {
        if (start >= 32 || end >= 32 || start >= end) {
            //llarm::out::dev_error("util::swap_bits has impossible arguments");
            // TODO think of an error 
            return;
        }

        const u8 num_bits = static_cast<u8>(end - start + 1);
        const u32 mask = static_cast<u32>(1 << num_bits) - 1;
        original &= static_cast<u16>(~(mask << start));
        original |= static_cast<u16>((value & mask) << start);
    }


    constexpr u32 rotr(const u32 num, u8 rotate) {
        rotate &= 31;

        if (rotate == 0) {
            return num;
        }

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

        while ((num & 1U) == 0) {
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
                num = (num * 10) + (static_cast<u32>(c) - '0');
            }
        }

        return num;
    }


    constexpr u64 hex_to_u64(const sv str) {
        u64 num = 0;

        // convert hex to i32
        for (const char c : str) {
            num <<= 4; // multiply by 16
        
            if (c >= '0' && c <= '9') {
                num += static_cast<u64>(c - '0');
            } else if (c >= 'A' && c <= 'F') {
                num += static_cast<u64>(c - 'A' + 10);
            }
        }

        return num;
    }
}

// https://quick-bench.com/q/JqnAzdyhgQ9yuc4WflaEe_3tciE