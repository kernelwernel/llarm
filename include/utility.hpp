#pragma once

#include "types.hpp"
#include "id.hpp"
#include "constants.hpp"

#include <bitset>

namespace util {

    // 0-based counting btw
    template <typename T>
    T bit_fetcher(const code_t &input, const u8 start, const u8 end) {
        if (start >= end) [[unlikely]] {
            // TODO: think of an error
        }

        const u32 mask = ((1U << (end - start + 1)) - 1);
        return static_cast<T>((input.to_ulong() >> start) & mask);
    }

    template <typename T>
    T bit_fetcher(const thumbcode_t &input, const u8 start, const u8 end) {
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


    [[nodiscard]] bool carry_add(const u64&);
    [[nodiscard]] bool carry_add(const u32, const u32);
    [[nodiscard]] bool carry_add(const u32, const u32, const u32);

    [[nodiscard]] bool borrow_add(const u32, const u32);
    [[nodiscard]] bool borrow_sub(const u32, const u32);
    [[nodiscard]] bool borrow_sub(const u32, const u32, const u32);

    [[nodiscard]] bool overflow_add(const i32, const i32);
    [[nodiscard]] bool overflow_add(const i32, const i32, const i32);
    [[nodiscard]] bool overflow_sub(const i32, const i32);
    [[nodiscard]] bool overflow_sub(const i32, const i32, const i32);

    [[nodiscard]] bool arithmetic_shift_right(u32 num, const u8 shift);


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