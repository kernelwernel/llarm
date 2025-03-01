#include "types.hpp"

    struct data_struct {
        u32 shifter_operand;
        bool shifter_carry_out;
    };


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
    data_struct data_process_immediate_mode(const arm_code_t &code) {
        data_struct data = {};

        const u8 rotate_imm = util::bit_fetcher<u8>(code, 8, 11);
        const u8 immed_8 = util::bit_fetcher<u8>(code, 0, 7);

        data.shifter_operand = std::rotr(immed_8, (rotate_imm * 2));

        if (rotate_imm == 0) {
            data.shifter_carry_out = reg.read(id::cpsr::C);
        } else {
            data.shifter_carry_out = (data.shifter_operand & (1 << 31));
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
    data_struct data_process_register(const arm_code_t &code) {
        data_struct data = {};

        const u32 Rm = reg.read(code, 0, 3);

        data.shifter_operand = Rm;
        data.shifter_carry_out = reg.read(id::cpsr::C);

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
    data_struct data_process_logical_shift_left_immediate(const arm_code_t &code) {
        data_struct data = {};

        const u8 shift_imm = util::bit_fetcher<u8>(code, 7, 11);
        const u32 Rm = reg.read(code, 0, 3);

        if (shift_imm == 0) {
            data.shifter_operand = Rm;
            data.shifter_carry_out = reg.read(id::cpsr::C);
        } else {
            data.shifter_operand = (Rm << shift_imm);
            data.shifter_carry_out = (Rm & (1 << (32 - shift_imm)));
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
    data_struct data_process_logical_shift_right_immediate(const arm_code_t &code) {
        data_struct data = {};

        const u8 shift_imm = util::bit_fetcher<u8>(code, 7, 11);
        const u32 Rm = reg.read(code, 0, 3);

        if (shift_imm == 0) {
            data.shifter_operand = 0;
            data.shifter_carry_out = (Rm & (1 << 31));
        } else {
            data.shifter_operand = (Rm >> shift_imm);
            data.shifter_carry_out = (Rm & (1 << (shift_imm - 1)));
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
    data_struct data_process_arithmetic_shift_right_immediate(const arm_code_t &code) {
        data_struct data = {};

        const u8 shift_imm = util::bit_fetcher<u8>(code, 7, 11);
        const u32 Rm = reg.read(code, 0, 3);

        if (shift_imm == 0) {
            if ((Rm & (1 << 31)) == 0) {
                data.shifter_operand = 0;
                data.shifter_carry_out = (Rm & (1 << 31));
            } else {
                data.shifter_operand = 0xFFFFFFFF;
                data.shifter_carry_out = (Rm & (1 << 31));
            }
        } else {
            data.shifter_operand = arithmetic_shift_right(Rm, shift_imm);
            data.shifter_carry_out = (Rm & (1 << (shift_imm - 1))); 
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
    data_struct data_process_rotate_right_immediate(const arm_code_t &code) {
        data_struct data = {};

        const u8 shift_imm = util::bit_fetcher<u8>(code, 7, 11);
        const u32 Rm = reg.read(code, 0, 3);

        if (shift_imm == 0) {
            // TODO
        } else {
            data.shifter_operand = std::rotr(Rm, shift_imm);
            data.shifter_carry_out = (Rm & (1 << (shift_imm - 1)));
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
    data_struct data_process_logical_shift_left_register(const arm_code_t &code) {
        data_struct data = {};

        const u32 Rs = reg.read(code, 8, 11);
        const u32 Rm = reg.read(code, 0, 3);
        const u32 Rs_bits = util::bit_fetcher(Rs, 0, 7);

        if (Rs_bits == 0) {
            data.shifter_operand = Rm;
            data.shifter_carry_out = reg.read(id::cpsr::C);
        } else if (Rs_bits < 32) {
            data.shifter_operand = (Rm << Rs_bits);
            data.shifter_carry_out = (Rm & (1 << (32 - Rs_bits))); // what the fuck?
        } else if (Rs_bits == 32) {
            data.shifter_operand = 0;
            data.shifter_carry_out = (Rm & 1);
        } else {
            data.shifter_operand = 0;
            data.shifter_carry_out = false;
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
    data_struct data_process_logical_shift_right_register(const arm_code_t &code) {
        data_struct data = {};

        const u32 Rs = reg.read(code, 8, 11);
        const u32 Rm = reg.read(code, 0, 3);
        const u32 Rs_bits = util::bit_fetcher(Rs, 0, 7);

        if (Rs_bits == 0) {
            data.shifter_operand = Rm;
            data.shifter_carry_out = reg.read(id::cpsr::C);
        } else if (Rs_bits < 32) {
            data.shifter_operand = (Rm >> Rs_bits);
            data.shifter_carry_out = (Rm & (1 << (Rs_bits - 1)));
        } else if (Rs_bits == 32) {
            data.shifter_operand = 0;
            data.shifter_carry_out = (Rm & (1 << 31));
        } else {
            data.shifter_operand = 0;
            data.shifter_carry_out = false;
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
    data_struct data_process_arithmetic_shift_right_register(const arm_code_t &code) {
        data_struct data = {};

        const u32 Rs = reg.read(code, 8, 11);
        const u32 Rm = reg.read(code, 0, 3);
        const u32 Rs_bits = util::bit_fetcher(Rs, 0, 7);
        
        if (Rs_bits == 0) {
            data.shifter_operand = Rm;
            data.shifter_carry_out = reg.read(id::cpsr::C);
        } else if (Rs_bits < 32) {
            data.shifter_operand = arithmetic_shift_right(Rm, Rs_bits);
            data.shifter_carry_out = (Rm & (1 << (Rs_bits - 1)));
        } else {
            if ((Rm & (1 << 31)) == 0) {
                data.shifter_operand = 0;
                data.shifter_carry_out = (Rm & (1 << (31)));
            } else {
                data.shifter_operand = 0xFFFFFFFF;
                data.shifter_carry_out = (Rm & (1 << (31)));
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
    data_struct data_process_rotate_right_register(const arm_code_t &code) {
        data_struct data = {};
        
        const u32 Rs = reg.read(code, 8, 11);
        const u32 Rm = reg.read(code, 0, 3);
        const u32 Rs_bits = util::bit_fetcher(Rs, 0, 7);
        const u32 Rs_bits_4 = util::bit_fetcher(Rs, 0, 4);

        if (Rs_bits == 0) {
            data.shifter_operand = Rm;
            data.shifter_carry_out = reg.read(id::cpsr::C);
        } else if (Rs_bits_4 == 0) {
            data.shifter_operand = Rm;
            data.shifter_carry_out = (Rm & (1 << 31));
        } else {
            data.shifter_operand = std::rotr(Rm, Rs_bits_4);
            data.shifter_carry_out = (Rm & (1 << (Rs_bits_4 - 1)));
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
    data_struct data_process_rotate_right_extend(const arm_code_t &code) {
        data_struct data = {};

        const u32 Rm = reg.read(code, 0, 3);

        data.shifter_operand = ((reg.read(id::cpsr::C) << 31) | (Rm >> 1));
        data.shifter_carry_out = (Rm & 1);

        return data;
    }


    data_struct data_process_addressing_mode(const arm_code_t &code) {
        if ((code.test(27) != false) || (code.test(26) != false)) {
            // TODO, error
        }

        const bool I = code.test(25);

        if (I) {
            return data_proccess_immediate_mode(code);
        }
        
        // immediate shift mode
        if (code.test(4) == false) {
            const u32 Rm = reg.read(code, 0, 3);
            const u8 shift_imm = util::bit_fetcher(code, 7, 11);

            if (
                (code.test(11) == false) &&
                (code.test(10) == false) &&
                (code.test(9) == false) &&
                (code.test(8) == false) &&
                (code.test(7) == false) &&
                (code.test(6) == false) &&
                (code.test(5) == false)
            ) {
                return data_process_register(code);
            }

            const u8 bytecode = ((code.test(6) << 1) | code.test(5));

            switch (bytecode) {
                case 0b00: return data_process_logical_shift_left_immediate(code);
                case 0b01: return data_process_logical_shift_right_immediate(code);
                case 0b10: return data_process_arithmetic_shift_right_immediate(code);
                case 0b11: return data_process_rotate_right_immediate(code);
            }
        }

        // register mode
        if (
            (code.test(7) == false) &&
            (code.test(4) == true)
        ) {
            const u8 bytecode = ((code.test(6) << 1) | code.test(5));

            switch (bytecode) {
                case 0b00: return data_process_logical_shift_left_register(code);
                case 0b01: return data_process_logical_shift_right_register(code);
                case 0b10: return data_process_arithmetic_shift_right_register(code);
                case 0b11: return data_process_rotate_right_register(code);
            }

            // TODO ERROR
        }


        if (
            (code.test(11) == false) &&
            (code.test(10) == false) &&
            (code.test(9) == false) &&
            (code.test(8) == false) &&
            (code.test(7) == false) &&
            (code.test(6) == true) &&
            (code.test(5) == true) &&
            (code.test(4) == false)
        ) {
            return data_process_rotate_right_extend(code);
        }

        // TODO: ERROR
    }

