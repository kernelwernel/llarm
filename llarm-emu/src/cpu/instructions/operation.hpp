#pragma once

#include "../../id.hpp"

#include <vector>

#include <llarm/shared/types.hpp>

namespace operation {
    bool carry_add(const u64 sum);
    bool carry_add(const u32 a, const u32 b);
    bool carry_add(const u32 a, const u32 b, const u32 c);

    bool borrow_add(const u32 a, const u32 b);
    bool borrow_sub(const u32 a, const u32 b);
    bool borrow_sub(const u32 a, const u32 b, const u32 c);

    bool overflow_add(const u32 a, const u32 b, const u32 c);
    bool overflow_add(const u32 a, const u32 b);
    bool overflow_sub(const u32 a, const u32 b);
    bool overflow_sub(const u32 a, const u32 b, const u32 c);

    bool signed_overflow_sub(const i32 a, const i32 b);
    bool signed_overflow_add(const i32 a, const i32 b);

    i32 sign_extend(const u32 value, const u8 sign_index = 31);
    i32 signed_sat(const u32 x, const u32 n);
    bool signed_does_sat(const u32 x, const u32 n);

    bool arithmetic_shift_right(u32 num, const u8 shift); // why is this not a reference? research more...

    std::vector<id::reg> register_list(const u16 reg_list);
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

    bool overflow_sub(const u64 sum) {
    
    }
*/

// TODO: doube check if all of these work as intended, hella important