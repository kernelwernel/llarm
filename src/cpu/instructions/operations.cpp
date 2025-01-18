#include "types.hpp"
#include "id.hpp"
#include "constants.hpp"

#include "operations.hpp"

#include <bitset>


[[nodiscard]] bool operation::carry_add(const u64 &sum) {
    constexpr u64 max = ((1ULL << 32) - 1);
    return (sum > max);
}

[[nodiscard]] bool operation::carry_add(const u32 sum1, const u32 sum2) {
    constexpr u64 max = ((1ULL << 32) - 1);
    return ((sum1 + sum2) > max);
}

// CHECK IF THIS WORKS
[[nodiscard]] bool operation::carry_add(const u32 sum1, const u32 sum2, const u32 sum3) {
    constexpr u64 max = ((1ULL << 32) - 1);
    return ((sum1 + sum2 + sum3) > max);
}

// TODO: COMPLETE
[[nodiscard]] bool operation::borrow_add(const u32 p1, const u32 p2) {
    return true; // TODO: COMPLETE THIS SHIT
}

[[nodiscard]] bool operation::borrow_sub(const u32 p1, const u32 p2) {
    return (p1 < p2);
}

// CHECK IF THIS WORKS
[[nodiscard]] bool operation::borrow_sub(const u32 p1, const u32 p2, const u32 p3) {
    return (((p1 - p2) - p3) < 0);
}

[[nodiscard]] bool operation::overflow_add(const i32 a, const i32 b) {
    const i32 result = a + b;
    return (a > 0 && b > 0 && result < 0);
}

[[nodiscard]] bool operation::overflow_add(const i32 a, const i32 b, const i32 c) {
    const i32 intermediate_result = a + b;

    if (
        (a > 0 && b > 0 && intermediate_result < 0) || 
        (a < 0 && b < 0 && intermediate_result > 0)
    ) {
        return true;
    }

    const i32 final_result = intermediate_result + c;

    if (
        (intermediate_result > 0 && c > 0 && final_result < 0) || 
        (intermediate_result < 0 && c < 0 && final_result > 0)
    ) {
        return true;
    }

    return false;
}

// Subtraction causes an overflow if the operands have different signs, 
// and the first operand and the result have different signs.
// TODO: double check if this works manually
[[nodiscard]] bool operation::overflow_sub(const i32 a, const i32 b) {
    const bool sign = (a & (1 << 31)) ^ (b & (1 << 31));
    const i32 result = a - b;
    return (sign && (a & (1 << 31)) ^ (result & (1 << 31)));
}


// Subtraction causes an overflow if the operands have different signs, 
// and the first operand and the result have different signs.
// TODO: double check if this works manually
[[nodiscard]] bool operation::overflow_sub(const i32 a, const i32 b, const i32 c) {
    const bool sign = ((a & (1 << 31)) ^ (b & (1 << 31))) ^ (c & (1 << 31));
    const i32 result = a - b - c;
    return (sign && (a & (1 << 31)) ^ (result & (1 << 31)));
}


bool operation::signed_overflow_sub(const u32 a, const u32 b) {

}

bool operation::signed_overflow_add(const u32 a, const u32 b) {

}


[[nodiscard]] bool operation::arithmetic_shift_right(u32 num, const u8 shift) {
    const u32 sign = num & (1 << 31);
    num >>= shift;
    num |= sign;
    return num;
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