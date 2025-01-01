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



    void modify_bits(u32 &original, const u32 start, const u32 end, const u32 value) {
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


    // for example, ARMv5TEJ will be simplified to ARMv5
    id::base_arch conv_specific_arch_to_base_arch(const id::specific_arch arch) {
        switch (arch) {
            case id::specific_arch::ARMv1: return id::base_arch::ARMv1;
            case id::specific_arch::ARMv2: 
            case id::specific_arch::ARMv2a: return id::base_arch::ARMv2;
            case id::specific_arch::ARMv3: return id::base_arch::ARMv3;
            case id::specific_arch::ARMv4: 
            case id::specific_arch::ARMv4T: return id::base_arch::ARMv4;
            case id::specific_arch::ARMv5: 
            case id::specific_arch::ARMv5T: 
            case id::specific_arch::ARMv5TE: 
            case id::specific_arch::ARMv5TEJ: return id::base_arch::ARMv5;
            case id::specific_arch::ARMv6: 
            case id::specific_arch::ARMv6T2: 
            case id::specific_arch::ARMv6Z: 
            case id::specific_arch::ARMv6K: 
            case id::specific_arch::ARMv6_M: return id::base_arch::ARMv6;
            case id::specific_arch::ARMv7_A: 
            case id::specific_arch::ARMv7_M: 
            case id::specific_arch::ARMv7_R: 
            case id::specific_arch::ARMv7E_M: return id::base_arch::ARMv7;
            case id::specific_arch::ARMv8_A: 
            case id::specific_arch::ARMv8_R: 
            case id::specific_arch::ARMv8_M_BASELINE: 
            case id::specific_arch::ARMv8_M_MAINLINE: 
            case id::specific_arch::ARMv8_1_M_MAINLINE: 
            case id::specific_arch::ARMv8_2_A: 
            case id::specific_arch::ARMv8_3_A: 
            case id::specific_arch::ARMv8_4_A: 
            case id::specific_arch::ARMv8_5_A: 
            case id::specific_arch::ARMv8_6_A: return id::base_arch::ARMv8;
            case id::specific_arch::ARMv9_A: 
            case id::specific_arch::ARMv9_2_A: return id::base_arch::ARMv9;
        }
    }




    id::coprocessor fetch_cp_id(const u8 raw_cp_num) {
        switch(raw_cp_num) {
            case 0b0000: return id::coprocessor::CP0;
            case 0b0001: return id::coprocessor::CP1;
            case 0b0010: return id::coprocessor::CP2;
            case 0b0011: return id::coprocessor::CP3;
            case 0b0100: return id::coprocessor::CP4;
            case 0b0101: return id::coprocessor::CP5;
            case 0b0110: return id::coprocessor::CP6;
            case 0b0111: return id::coprocessor::CP7;
            case 0b1000: return id::coprocessor::CP8;
            case 0b1001: return id::coprocessor::CP9;
            case 0b1010: return id::coprocessor::CP10;
            case 0b1011: return id::coprocessor::CP11;
            case 0b1100: return id::coprocessor::CP12;
            case 0b1101: return id::coprocessor::CP13;
            case 0b1110: return id::coprocessor::CP14;
            case 0b1111: return id::coprocessor::CP15;
            default: // TODO: throw undefined exception
        }
    }


    id::cp15 fetch_cp15_reg_id(const u8 raw_cp15_num) {
        switch(raw_cp15_num) {
            case 0b0000: return id::cp15::R0;
            case 0b0001: return id::cp15::R1;
            case 0b0010: return id::cp15::R2;
            case 0b0011: return id::cp15::R3;
            case 0b0100: return id::cp15::R4;
            case 0b0101: return id::cp15::R5;
            case 0b0110: return id::cp15::R6;
            case 0b0111: return id::cp15::R7;
            case 0b1000: return id::cp15::R8;
            case 0b1001: return id::cp15::R9;
            case 0b1010: return id::cp15::R10;
            case 0b1011: return id::cp15::R11;
            case 0b1100: return id::cp15::R12;
            case 0b1101: return id::cp15::R13;
            case 0b1110: return id::cp15::R14;
            case 0b1111: return id::cp15::R15;
            default: // TODO: throw undefined exception
        }
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