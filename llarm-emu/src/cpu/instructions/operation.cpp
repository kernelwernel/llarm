#include "../../id.hpp"

#include "operation.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>
#include <llarm/shared/out.hpp>


bool operation::carry_add(const u64 sum) {
    constexpr u64 max = ((1ULL << 32) - 1);
    return (sum > max);
}

bool operation::carry_add(const u32 a, const u32 b) {
    constexpr u64 max = ((1ULL << 32) - 1);
    return ((static_cast<u64>(a) + b) > max);
}

bool operation::carry_add(const u32 a, const u32 b, const u32 c) {
    constexpr u64 max = ((1ULL << 32) - 1);
    return ((static_cast<u64>(a) + b + c) > max);
}

bool operation::borrow_add(const u32 a, const u32 b) {
    return !operation::carry_add(a, b);
}

bool operation::borrow_sub(const u32 a, const u32 b) {
    return (a < b);
}

bool operation::borrow_sub(const u32 a, const u32 b, const u32 c) {
    return (a < b) || (a - b < c);
}

bool operation::overflow_add(const u32 a, const u32 b) {
    const u32 result = a + b;
    return static_cast<bool>(((a ^ result) & (b ^ result)) >> 31);
}


bool operation::overflow_add(const u32 a, const u32 b, const u32 c) {
    const u32 result = a + b + c;
    return static_cast<bool>(((a ^ result) & (b ^ result)) >> 31);
}


bool operation::overflow_sub(const u32 a, const u32 b) {
    const u32 result = a - b;
    return static_cast<bool>(((a ^ b) & (a ^ result)) >> 31);
}


bool operation::overflow_sub(const u32 a, const u32 b, const u32 c) {
    const u32 result = a - b - c;
    return static_cast<bool>(((a ^ b) & (a ^ result)) >> 31);
}


bool operation::signed_overflow_sub(const i32 a, const i32 b) {
    return operation::overflow_sub(static_cast<u32>(a), static_cast<u32>(b));
}


bool operation::signed_overflow_add(const i32 a, const i32 b) {
    return operation::overflow_add(static_cast<u32>(a), static_cast<u32>(b));
}


u32 operation::arithmetic_shift_right(u32 num, const u8 shift) {
    return static_cast<u32>(static_cast<i32>(num) >> shift);
}


i32 operation::sign_extend(const u32 value, const u8 sign_index) {
    const u32 mask = (1 << sign_index);

    if (value & mask) {
        const u32 extension = ~((mask << 1) - 1);
        return static_cast<i32>(value | extension);
    }

    return static_cast<i32>(value);
}


// source: Glossary-XII
i32 operation::signed_sat(const u32 x, const u32 n) {
    const i32 x_sign = static_cast<i32>(x);

    const i32 neg_range = -static_cast<i32>(1ULL << (n - 1)); // basically -2^(n - 1)
    const i32 pos_range = static_cast<i32>(1ULL << (n - 1)) - 1; // 2^(n - 1) - 1

    if (x_sign < neg_range) {
        return neg_range;
    }
    
    if (neg_range <= x_sign && x_sign <= pos_range) {
        return x_sign;
    }
    
    if (x_sign > pos_range) {
        return pos_range;
    }

    llarm::out::dev_error("Invalid value for signed saturation operation");
}


// source: Glossary-XII
bool operation::signed_does_sat(const u32 x, const u32 n) {
    const i32 x_sign = static_cast<i32>(x);

    const i32 neg_range = -static_cast<i32>(1ULL << (n - 1)); // basically -2^(n - 1)
    const i32 pos_range = static_cast<i32>(1ULL << (n - 1)) - 1; // 2^(n - 1) - 1

    return (!(neg_range <= x_sign && x_sign <= pos_range));
}


// source: Glossary-16
u32 operation::unsigned_sat(const u32 x, const u32 n) {
    const i32 x_sign = static_cast<i32>(x);

    if (x_sign < 0) {
        return 0;
    }

    const i64 pos_range = static_cast<i64>((1ULL << n) - 1); // 2^n - 1

    if (x_sign > pos_range) {
        return static_cast<u32>(pos_range);
    }

    return static_cast<u32>(x_sign);
}


// source: Glossary-16
bool operation::unsigned_does_sat(const u32 x, const u32 n) {
    const i32 x_sign = static_cast<i32>(x);

    const i64 pos_range = static_cast<i64>((1ULL << n) - 1); // 2^n - 1

    return (!(x_sign >= 0 && x_sign <= pos_range));
}



std::vector<id::reg> operation::register_list(const u16 reg_list) {
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