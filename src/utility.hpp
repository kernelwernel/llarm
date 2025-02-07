#pragma once

#include "types.hpp"
#include "id.hpp"
#include "constants.hpp"

#include <bitset>

namespace util {

    // TODO: maybe replace this with the 0-shifter strategy

    // 0-based counting btw
    template <typename T>
    T bit_fetcher(const arm_code_t &input, const u8 start, const u8 end) {
        if (start >= end) [[unlikely]] {
            // TODO: think of an error
        }

        const u32 mask = ((1U << (end - start + 1)) - 1);
        return static_cast<T>((input.to_ulong() >> start) & mask);
    }

    template <typename T>
    T bit_fetcher(const thumb_code_t &input, const u8 start, const u8 end) {
        if (start >= end) [[unlikely]] {
            // TODO: think of an error
        }

        const u32 mask = ((1U << (end - start + 1)) - 1);
        return static_cast<T>((input.to_ulong() >> start) & mask);
    }

    template <typename T>
    T bit_fetcher(const u32 input, const u8 start, const u8 end) {
        if (start >= end) [[unlikely]] {
            // TODO: think of an error
        }

        const u32 mask = ((1U << (end - start + 1)) - 1);
        return static_cast<T>((input >> start) & mask);
    }

    u32 bit_fetcher(const u32 input, const u8 start, const u8 end) {
        if (start >= end) [[unlikely]] {
            // TODO: think of an error
        }

        u32 copy = input;

        copy <<= (31 - end);
        copy >>= (31 - end + start);

        return copy;
    }



    void modify_bit_range(u32 &original, const u16 start, const u16 end, const u32 value) {
        if (start > end || start > 31 || end > 31) {
            throw std::invalid_argument("Invalid bit range");
        }

        // create the mask, this looks wonky as hell ngl
        const u32 mask = ((1U << (end - start + 1)) - 1) << start;

        u32 original_copy = original;

        original_copy &= ~mask;

        const u32 masked_value = (1U << (end - start + 1)) - 1;

        if (value & ~masked_value) {
            throw std::invalid_argument("Value does not fit in the specified bit range");
        }

        original_copy |= (value << start) & mask;

        original = original_copy;
    }


    void modify_bit(u32 &original, const u8 index const bool value) {
        if (index > 31) {
            throw std::out_of_range("Index must be between 0 and 31.");
        }

        if (value) {
            original |= (1U << index);
        } else {
            original &= ~(1U << index);
        }
    }

    // 1-based counting
    constexpr u32 trim(const u32 original, const u8 lhs, const u8 rhs) noexcept {
        if (lhs + rhs >= 32) {
            // TODO thing of a dev warning message here
            return 0;
        }

        u32 original_copy = original;

        original_copy >>= rhs;
        original_copy <<= rhs + lhs;
        original_copy >>= lhs;

        return original_copy;
    }


    void swap_bits(u32 &original, const u8 index, const u8 width, const u32 value) {
        const u32 mask = ((1u << width) - 1) << index;
        original &= ~mask;
        original |= (value << index) & mask;
    };

    void swap_bits(u32 &original, const u8 index, const u32 value) {
        swap_bits(original, index, (31 - index), value);
    };






    // for example, ARMv5TEJ will be simplified to ARMv5
    id::arch conv_specific_arch_to_arch(const id::specific_arch arch) {
        switch (arch) {
            case id::specific_arch::ARMv1: return id::arch::ARMv1;
            case id::specific_arch::ARMv2: 
            case id::specific_arch::ARMv2a: return id::arch::ARMv2;
            case id::specific_arch::ARMv3: return id::arch::ARMv3;
            case id::specific_arch::ARMv4: 
            case id::specific_arch::ARMv4T: return id::arch::ARMv4;
            case id::specific_arch::ARMv5: 
            case id::specific_arch::ARMv5T: 
            case id::specific_arch::ARMv5TE: 
            case id::specific_arch::ARMv5TEJ: return id::arch::ARMv5;
            case id::specific_arch::ARMv6: 
            case id::specific_arch::ARMv6T2: 
            case id::specific_arch::ARMv6Z: 
            case id::specific_arch::ARMv6K: 
            case id::specific_arch::ARMv6_M: return id::arch::ARMv6;
            case id::specific_arch::ARMv7_A: 
            case id::specific_arch::ARMv7_M: 
            case id::specific_arch::ARMv7_R: 
            case id::specific_arch::ARMv7E_M: return id::arch::ARMv7;
            case id::specific_arch::ARMv8_A: 
            case id::specific_arch::ARMv8_R: 
            case id::specific_arch::ARMv8_M_BASELINE: 
            case id::specific_arch::ARMv8_M_MAINLINE: 
            case id::specific_arch::ARMv8_1_M_MAINLINE: 
            case id::specific_arch::ARMv8_2_A: 
            case id::specific_arch::ARMv8_3_A: 
            case id::specific_arch::ARMv8_4_A: 
            case id::specific_arch::ARMv8_5_A: 
            case id::specific_arch::ARMv8_6_A: return id::arch::ARMv8;
            case id::specific_arch::ARMv9_A: 
            case id::specific_arch::ARMv9_2_A: return id::arch::ARMv9;
        }
    }



    consteval u32 get_kb(const u16 kb) {
        switch (kb) {
            case 1:   return std::pow(2, 10); // 1KB
            case 2:   return std::pow(2, 11); // 2KB
            case 4:   return std::pow(2, 12); // 4KB
            case 8:   return std::pow(2, 13); // 8KB
            case 16:  return std::pow(2, 14); // 16KB
            case 32:  return std::pow(2, 15); // 32KB
            case 64:  return std::pow(2, 16); // 64KB
            case 128: return std::pow(2, 17); // 128KB
            case 256: return std::pow(2, 18); // 256KB
            case 512: return std::pow(2, 19); // 512KB
            default: static_assert(false, "get_kb: invalid argument (must be either 1 or a power of 2)");
        }
    }

    consteval u32 get_mb(const u16 mb) {
        switch(mb) {
            case 1:   return std::pow(2, 20); // 1MB
            case 2:   return std::pow(2, 21); // 2MB
            case 4:   return std::pow(2, 22); // 4MB
            case 8:   return std::pow(2, 23); // 8MB
            case 16:  return std::pow(2, 24); // 16MB
            case 32:  return std::pow(2, 25); // 32MB
            case 64:  return std::pow(2, 26); // 64MB
            case 128: return std::pow(2, 27); // 128MB
            case 256: return std::pow(2, 28); // 256MB
            case 512: return std::pow(2, 29); // 512MB
            default: static_assert(false, "get_mb: invalid argument (must be either 1 or a power of 2)");
        }
    }
    
    consteval u64 get_gb(const u16 gb) {
        switch (gb) {
            case 1:   return std::pow(2, 30); // 1GB
            case 2:   return std::pow(2, 31); // 2GB
            case 4:   return std::pow(2, 32); // 4GB
            case 8:   return std::pow(2, 33); // 8GB
            case 16:  return std::pow(2, 34); // 16GB
            case 32:  return std::pow(2, 35); // 32GB
            case 64:  return std::pow(2, 36); // 64GB
            case 128: return std::pow(2, 37); // 128GB
            case 256: return std::pow(2, 38); // 256GB
            case 512: return std::pow(2, 39); // 512GB
            default: static_assert(false, "get_gb: invalid argument (must be either 1 or a power of 2)");
        }
    }


/*
    overflow:
    Returns 1 if the addition or subtraction specified as 
    its parameter caused a 32-bit signed overflow. 

    Addition generates an overflow if both operands have the same sign 
    (bit[31]), and the sign of the result is different to
    the sign of both operands. 
    
    Subtraction causes an overflow
     if the operands have different signs, and the first
    operand and the result have different signs.
    This delivers further information about an addition or 
    subtraction which occurred earlier in the pseudo-code.
    The addition or subtraction is not repeated

    bool overflow_sub(const u64 &sum) {
    
    }
*/
}