#pragma once

#include "shared/types.hpp"
#include "../core/registers.hpp"
#include <vector>
#include <bit>

struct OPERATION {
public:
    bool carry_add(const u64&);
    bool carry_add(const u32, const u32);
    bool carry_add(const u32, const u32, const u32);

    bool borrow_add(const u32, const u32);
    bool borrow_sub(const u32, const u32);
    bool borrow_sub(const u32, const u32, const u32);

    bool overflow_add(const i32, const i32);
    bool overflow_add(const i32, const i32, const i32);
    bool overflow_sub(const i32, const i32);
    bool overflow_sub(const i32, const i32, const i32);

    bool signed_overflow_sub(const u32, const u32);
    bool signed_overflow_add(const u32, const u32);

    template <is_integral T>
    i32 sign_extend(const T value) {
        if constexpr (std::is_same_v<T, u8>) {
            return static_cast<i32>(static_cast<i8>(value));
        } else if constexpr (std::is_same_v<T, u16>) {
            return static_cast<i32>(static_cast<i16>(value));
        } else if constexpr (std::is_same_v<T, u32>) {
            return static_cast<i32>(static_cast<i32>(value));
        } else {
            out::error("TODO (not valid type)");
        }
    }

    bool arithmetic_shift_right(u32 num, const u8 shift); // why is this not a reference? research more...

    std::vector<id::reg> register_list(const u8 reg_list);
};

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

// TODO: doube check if all of these work as intended, hella important