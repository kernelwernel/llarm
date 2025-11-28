#include "addressing_modes.hpp"

#include "llarm-asm/llarm-asm.hpp"
#include "shared/types.hpp"
#include "shared/util.hpp"
#include "shared/out.hpp"

/**
 * ===== 32-bit immediate mode =====
 * 
 * shifter_operand = immed_8 Rotate_Right (rotate_imm * 2)
 * if rotate_imm == 0 then
 *   shifter_carry_out = C flag
 * else // rotate_imm != 0
 *   shifter_carry_out = shifter_operand[31]
 * 
 * (A5-6)
 */
data_struct ADDRESSING_MODE::data_process_immediate_mode(const u32 code) {
    data_struct data = {};

    const u8 rotate_imm = llarm::util::bit_range<u8>(code, 8, 11);
    const u8 immed_8 = llarm::util::bit_range<u8>(code, 0, 7);

    data.value = std::rotr(immed_8, (rotate_imm * 2));

    if (rotate_imm == 0) {
        data.carry = reg.read(id::cpsr::C);
    } else {
        data.carry = llarm::util::bit_fetch(data.value, 31);
    }

    return data;
}


/**
 * ===== register =====
 * 
 * shifter_operand = Rm
 * shifter_carry_out = C Flag
 * 
 * (A5-8)
 */
data_struct ADDRESSING_MODE::data_process_register(const u32 code) {
    data_struct data = {};

    const u32 Rm = reg.read(code, 0, 3);

    data.value = Rm;
    data.carry = reg.read(id::cpsr::C);

    return data;
}


/**
 * ===== logical shift left by immediate =====
 * 
 * if shift_imm == 0 then // Register Operand
 *   shifter_operand = Rm
 *   shifter_carry_out = C Flag
 * else // shift_imm > 0
 *   shifter_operand = Rm Logical_Shift_Left shift_imm
 *   shifter_carry_out = Rm[32 - shift_imm]
 * 
 * (A5-9)
 */
data_struct ADDRESSING_MODE::data_process_logical_shift_left_immediate(const u32 code) {
    data_struct data = {};

    const u8 shift_imm = llarm::util::bit_range<u8>(code, 7, 11);
    const u32 Rm = reg.read(code, 0, 3);

    if (shift_imm == 0) {
        data.value = Rm;
        data.carry = reg.read(id::cpsr::C);
    } else {
        data.value = (Rm << shift_imm);
        data.carry = (llarm::util::bit_fetch(Rm, (32 - shift_imm)));
    }

    return data;
}


/**
 * ===== logical shift right by immediate =====
 * 
 * if shift_imm == 0 then
 *   shifter_operand = 0
 *   shifter_carry_out = Rm[31]
 * else // shift_imm > 0
 *   shifter_operand = Rm Logical_Shift_Right shift_imm
 *   shifter_carry_out = Rm[shift_imm - 1]
 * 
 * (A5-11)
 */
data_struct ADDRESSING_MODE::data_process_logical_shift_right_immediate(const u32 code) {
    data_struct data = {};

    const u8 shift_imm = llarm::util::bit_range<u8>(code, 7, 11);
    const u32 Rm = reg.read(code, 0, 3);

    if (shift_imm == 0) {
        data.value = 0;
        data.carry = (llarm::util::bit_fetch(Rm, 31));
    } else {
        data.value = (Rm >> shift_imm);
        data.carry = (llarm::util::bit_fetch(Rm, (shift_imm - 1)));
    }

    return data;
}


/**
 * ===== arithmetic shift right by immediate
 * 
 * if shift_imm == 0 then
 *   if Rm[31] == 0 then
 *     shifter_operand = 0
 *     shifter_carry_out = Rm[31]
 *   else // Rm[31] == 1
 *     shifter_operand = 0xFFFFFFFF
 *     shifter_carry_out = Rm[31]
 * else // shift_imm > 0
 *   shifter_operand = Rm Arithmetic_Shift_Right <shift_imm>
 *   shifter_carry_out = Rm[shift_imm - 1]
 * 
 * (A5-13)
 */
data_struct ADDRESSING_MODE::data_process_arithmetic_shift_right_immediate(const u32 code) {
    data_struct data = {};

    const u8 shift_imm = llarm::util::bit_range<u8>(code, 7, 11);
    const u32 Rm = reg.read(code, 0, 3);

    if (shift_imm == 0) {
        if ((llarm::util::bit_fetch(Rm, 31)) == 0) {
            data.value = 0;
            data.carry = (llarm::util::bit_fetch(Rm, 31));
        } else {
            data.value = 0xFFFFFFFF;
            data.carry = (llarm::util::bit_fetch(Rm, 31));
        }
    } else {
        data.value = operation.arithmetic_shift_right(Rm, shift_imm);
        data.carry = (llarm::util::bit_fetch(Rm, (shift_imm - 1))); 
    }

    return data;
}


/**
 * ===== rotate right by immediate =====
 * 
 * if shift_imm == 0 then
 *   See “Data-processing operands - Rotate right with extend” on page A5-17
 * else // shift_imm > 0
 *   shifter_operand = Rm Rotate_Right shift_imm
 *   shifter_carry_out = Rm[shift_imm - 1]
 * 
 * (A5-15)
 */
data_struct ADDRESSING_MODE::data_process_rotate_right_immediate(const u32 code) {
    data_struct data = {};

    const u8 shift_imm = llarm::util::bit_range<u8>(code, 7, 11);
    const u32 Rm = reg.read(code, 0, 3);

    if (shift_imm == 0) {
        // TODO
    } else {
        data.value = std::rotr(Rm, shift_imm);
        data.carry = (llarm::util::bit_fetch(Rm, (shift_imm - 1)));
    }

    return data;
}


/**
 * ===== logical shift left by register =====
 * 
 * if Rs[7:0] == 0 then
 *   shifter_operand = Rm
 *   shifter_carry_out = C Flag
 * else if Rs[7:0] < 32 then
 *   shifter_operand = Rm Logical_Shift_Left Rs[7:0]
 *   shifter_carry_out = Rm[32 - Rs[7:0]]
 * else if Rs[7:0] == 32 then
 *   shifter_operand = 0
 *   shifter_carry_out = Rm[0]
 * else // Rs[7:0] > 32
 *   shifter_operand = 0
 *   shifter_carry_out = 0
 * 
 * (A5-10)
 */
data_struct ADDRESSING_MODE::data_process_logical_shift_left_register(const u32 code) {
    data_struct data = {};

    const u32 Rs = reg.read(code, 8, 11);
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rs_bits = llarm::util::bit_range(Rs, 0, 7);

    if (Rs_bits == 0) {
        data.value = Rm;
        data.carry = reg.read(id::cpsr::C);
    } else if (Rs_bits < 32) {
        data.value = (Rm << Rs_bits);
        data.carry = (llarm::util::bit_fetch(Rm, (32 - Rs_bits))); // what the fuck?
    } else if (Rs_bits == 32) {
        data.value = 0;
        data.carry = (Rm & 1);
    } else {
        data.value = 0;
        data.carry = false;
    }
            
    return data;
}


/**
 * ===== logical shift right by register =====
 * 
 * if Rs[7:0] == 0 then
 *   shifter_operand = Rm
 *   shifter_carry_out = C Flag
 * else if Rs[7:0] < 32 then
 *   shifter_operand = Rm Logical_Shift_Right Rs[7:0]
 *   shifter_carry_out = Rm[Rs[7:0] - 1]
 * else if Rs[7:0] == 32 then
 *   shifter_operand = 0
 *   shifter_carry_out = Rm[31]
 * else // Rs[7:0] > 32
 *   shifter_operand = 0
 *   shifter_carry_out = 0
 */
data_struct ADDRESSING_MODE::data_process_logical_shift_right_register(const u32 code) {
    data_struct data = {};

    const u32 Rs = reg.read(code, 8, 11);
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rs_bits = llarm::util::bit_range(Rs, 0, 7);

    if (Rs_bits == 0) {
        data.value = Rm;
        data.carry = reg.read(id::cpsr::C);
    } else if (Rs_bits < 32) {
        data.value = (Rm >> Rs_bits);
        data.carry = (llarm::util::bit_fetch(Rm, (Rs_bits - 1)));
    } else if (Rs_bits == 32) {
        data.value = 0;
        data.carry = (llarm::util::bit_fetch(Rm, 31));
    } else {
        data.value = 0;
        data.carry = false;
    }
            
    return data;
}





/**
 * ===== arithmetic shift right by register =====
 * 
 * if Rs[7:0] == 0 then
 *   shifter_operand = Rm
 *   shifter_carry_out = C Flag
 * else if Rs[7:0] < 32 then
 *   shifter_operand = Rm Arithmetic_Shift_Right Rs[7:0]
 *   shifter_carry_out = Rm[Rs[7:0] - 1]
 * else // Rs[7:0] >= 32
 *   if Rm[31] == 0 then
 *     shifter_operand = 0
 *     shifter_carry_out = Rm[31]
 *   else // Rm[31] == 1
 *     shifter_operand = 0xFFFFFFFF
 *     shifter_carry_out = Rm[31]
 * 
 * (A5-14)
 */
data_struct ADDRESSING_MODE::data_process_arithmetic_shift_right_register(const u32 code) {
    data_struct data = {};

    const u32 Rs = reg.read(code, 8, 11);
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rs_bits = llarm::util::bit_range(Rs, 0, 7);
    
    if (Rs_bits == 0) {
        data.value = Rm;
        data.carry = reg.read(id::cpsr::C);
    } else if (Rs_bits < 32) {
        data.value = operation.arithmetic_shift_right(Rm, Rs_bits);
        data.carry = (llarm::util::bit_fetch(Rm, (Rs_bits - 1)));
    } else {
        if ((llarm::util::bit_fetch(Rm, 31)) == 0) {
            data.value = 0;
            data.carry = (llarm::util::bit_fetch(Rm, (31)));
        } else {
            data.value = 0xFFFFFFFF;
            data.carry = (llarm::util::bit_fetch(Rm, (31)));
        }
    }

    return data;
}


/**
 * ===== rotate right by register =====
 * 
 * if Rs[7:0] == 0 then
 *   shifter_operand = Rm
 *   shifter_carry_out = C Flag
 * else if Rs[4:0] == 0 then
 *   shifter_operand = Rm
 *   shifter_carry_out = Rm[31]
 * else // Rs[4:0] > 0
 *   shifter_operand = Rm Rotate_Right Rs[4:0]
 *   shifter_carry_out = Rm[Rs[4:0] - 1]
 * 
 * (A5-16)
 */
data_struct ADDRESSING_MODE::data_process_rotate_right_register(const u32 code) {
    data_struct data = {};
    
    const u32 Rs = reg.read(code, 8, 11);
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rs_bits = llarm::util::bit_range(Rs, 0, 7);
    const u32 Rs_bits_4 = llarm::util::bit_range(Rs, 0, 4);

    if (Rs_bits == 0) {
        data.value = Rm;
        data.carry = reg.read(id::cpsr::C);
    } else if (Rs_bits_4 == 0) {
        data.value = Rm;
        data.carry = (llarm::util::bit_fetch(Rm, 31));
    } else {
        data.value = std::rotr(Rm, Rs_bits_4);
        data.carry = (llarm::util::bit_fetch(Rm, (Rs_bits_4 - 1)));
    }

    return data;
}


/**
 * ===== rotate right with extend =====
 * 
 * shifter_operand = (C Flag Logical_Shift_Left 31) OR (Rm Logical_Shift_Right 1)
 * shifter_carry_out = Rm[0]
 * 
 * (A5-17)
 */
data_struct ADDRESSING_MODE::data_process_rotate_right_extend(const u32 code) {
    data_struct data = {};

    const u32 Rm = reg.read(code, 0, 3);

    data.value = ((reg.read(id::cpsr::C) << 31) | (Rm >> 1));
    data.carry = (Rm & 1);

    return data;
}


data_struct ADDRESSING_MODE::data_processing(const u32 code) {
    using namespace llarm::util;

    const shifter_enum shifter_id = llarm::as::identify::shifter(shifter_category::DATA, code);

    switch (shifter_id) {
        case shifter_enum::DATA_IMM: return data_process_immediate_mode(code);
        case shifter_enum::DATA_RRX: return data_process_rotate_right_extend(code);
        case shifter_enum::DATA_REG: return data_process_register(code);
        case shifter_enum::DATA_IMM_LSL: return data_process_logical_shift_left_immediate(code);
        case shifter_enum::DATA_IMM_LSR: return data_process_logical_shift_right_immediate(code);
        case shifter_enum::DATA_IMM_ASR: return data_process_arithmetic_shift_right_immediate(code);
        case shifter_enum::DATA_IMM_ROR: return data_process_rotate_right_immediate(code);
        case shifter_enum::DATA_REG_LSL: return data_process_logical_shift_left_register(code);
        case shifter_enum::DATA_REG_LSR: return data_process_logical_shift_right_register(code);
        case shifter_enum::DATA_REG_ASR: return data_process_arithmetic_shift_right_register(code);
        case shifter_enum::DATA_REG_ROR: return data_process_rotate_right_register(code);
        default: llarm::out::error("Impossible identification of ARM data processing shifter");
    }
}