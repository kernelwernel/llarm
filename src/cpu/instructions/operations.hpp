#include "types.hpp"
#include <vector>

namespace operation {
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

    bool signed_overflow_sub(const u32, const u32);
    bool signed_overflow_add(const u32, const u32);

    u16 sign_extend(const u16 value) {}


    [[nodiscard]] bool arithmetic_shift_right(u32 num, const u8 shift); // why is this not a reference? research more...

    std::vector<id::reg> register_list(const u8 reg_list);

    id::coprocessor fetch_cp_id(const u8 raw_cp_num);
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

// TODO: doube check if all of these work as intended, hella important