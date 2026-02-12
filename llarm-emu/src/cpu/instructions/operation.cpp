#include "../../id.hpp"

#include "operation.hpp"

#include <cmath>

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>
#include <llarm/shared/out.hpp>


bool OPERATION::carry_add(const u64 sum) {
    constexpr u64 max = ((1ULL << 32) - 1);
    return (sum > max);
}

bool OPERATION::carry_add(const u32 sum1, const u32 sum2) {
    constexpr u64 max = ((1ULL << 32) - 1);
    return ((sum1 + sum2) > max);
}

// CHECK IF THIS WORKS TODO
bool OPERATION::carry_add(const u32 sum1, const u32 sum2, const u32 sum3) {
    constexpr u64 max = ((1ULL << 32) - 1);
    return ((sum1 + sum2 + sum3) > max);
}

// TODO: COMPLETE
bool OPERATION::borrow_add(const u32 p1, const u32 p2) {
    return true; // TODO: COMPLETE THIS SHIT
}

bool OPERATION::borrow_sub(const u32 p1, const u32 p2) {
    return (p1 < p2);
}

// CHECK IF THIS WORKS
bool OPERATION::borrow_sub(const u32 p1, const u32 p2, const u32 p3) {
    return (((p1 - p2) - p3) < 0);
}

bool OPERATION::overflow_add(const i32 a, const i32 b) {
    const i32 result = a + b;
    return (a > 0 && b > 0 && result < 0);
}

bool OPERATION::overflow_add(const i32 a, const i32 b, const i32 c) {
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
bool OPERATION::overflow_sub(const i32 a, const i32 b) {
    const bool sign = (a & (1 << 31)) ^ (b & (1 << 31));
    const i32 result = a - b;
    return (sign && (a & (1 << 31)) ^ (result & (1 << 31)));
}


// Subtraction causes an overflow if the operands have different signs, 
// and the first operand and the result have different signs.
// TODO: double check if this works manually
bool OPERATION::overflow_sub(const i32 a, const i32 b, const i32 c) {
    const bool sign = ((a & (1 << 31)) ^ (b & (1 << 31))) ^ (c & (1 << 31));
    const i32 result = a - b - c;
    return (sign && (a & (1 << 31)) ^ (result & (1 << 31)));
}


bool OPERATION::signed_overflow_sub(const u32 a, const u32 b) {
    return false; // TODO
}

bool OPERATION::signed_overflow_add(const u32 a, const u32 b) {
    return false; // TODO
}


bool OPERATION::arithmetic_shift_right(u32 num, const u8 shift) {
    const u32 sign = num & (1 << 31);
    num >>= shift;
    num |= sign;
    return num;
}


i32 OPERATION::sign_extend(const u32 value, const u8 sign_index) {
    const u32 mask = (1 << sign_index);

    if (value & mask) {
        u32 extension = ~((mask << 1) - 1);
        return static_cast<i32>(value | extension);
    }

    return static_cast<i32>(value);
}


// source: Glossary-XII
i32 OPERATION::signed_sat(const u32 x, const u32 n) {
    const i32 neg_range = std::pow(-2, n - 1);
    const i32 pos_range = std::pow(2, n - 1) - 1;

    if (x < neg_range) {
        return neg_range;
    } else if (neg_range <= x && x <= pos_range) {
        return x;
    } else if (x > pos_range) {
        return pos_range;
    }

    llarm::out::dev_error("Invalid value for signed saturation operation");
}


// source: Glossary-XII
bool OPERATION::signed_does_sat(const u32 x, const u32 n) {
    const i32 neg_range = std::pow(-2, n - 1);
    const i32 pos_range = std::pow(2, n - 1) - 1;

    return (!(neg_range <= x && x <= pos_range));
}



std::vector<id::reg> OPERATION::register_list(const u16 reg_list) {
    std::vector<id::reg> tmp = {};

    for (u8 i = 0; i < (sizeof(reg_list) * 8); i++) {
        if (llarm::util::bit_fetch(reg_list, i)) {
            switch (i) {
                case 0: tmp.push_back(id::reg::R0); continue;
                case 1: tmp.push_back(id::reg::R1); continue;
                case 2: tmp.push_back(id::reg::R2); continue;
                case 3: tmp.push_back(id::reg::R3); continue;
                case 4: tmp.push_back(id::reg::R4); continue;
                case 5: tmp.push_back(id::reg::R5); continue;
                case 6: tmp.push_back(id::reg::R6); continue;
                case 7: tmp.push_back(id::reg::R7); continue;
                case 8: tmp.push_back(id::reg::R8); continue;
                case 9: tmp.push_back(id::reg::R9); continue;
                case 10: tmp.push_back(id::reg::R10); continue;
                case 11: tmp.push_back(id::reg::R11); continue;
                case 12: tmp.push_back(id::reg::R12); continue;
                case 13: tmp.push_back(id::reg::R13); continue;
                case 14: tmp.push_back(id::reg::R14); continue;
                case 15: tmp.push_back(id::reg::R15); continue;
            }
        }
    }

    return tmp;
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

    bool overflow_sub(const u64 sum) {
    
    }
*/