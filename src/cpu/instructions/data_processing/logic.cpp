#include "types.hpp"
#include "utility.hpp"
#include "cpu/instructions.hpp"
#include "cpu/core/registers.hpp"

#include <bit>

/*
 * Rd = Rd AND Rm
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * C Flag = unaffected
 * V Flag = unaffected
 */
void instructions::thumb::logic::AND(const thumbcode_t &code, REGISTERS &reg) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);

    const u32 Rm = reg.read(code, 3, 5);

    reg.write(Rd_id, reg.read(Rd_id) & Rm);

    const u32 Rd = reg.read(Rd_id);

    reg.write_cpsr(id::cpsr::N, (Rd & (1 << 31)));
    reg.write_cpsr(id::cpsr::Z, (Rd == 0));

    reg.thumb_increment_PC();
}


/*
 * if immed_5 == 0
 *   C Flag = Rm[31]
 *   if Rm[31] == 0 then
 *     Rd = 0
 *   else /Rm[31] == 1/ ]
 *     Rd = 0xFFFFFFFF
 * else /immed_5 > 0/
 *   C Flag = Rm[immed_5 - 1]
 *   Rd = Rm Arithmetic_Shift_Right immed_5
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * V Flag = unaffected
 */
void instructions::thumb::logic::ASR1(const thumbcode_t &code, REGISTERS &reg) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);

    const u32 Rm = reg.read(code, 3, 5);
    const u8 immed_5 = util::bit_fetcher<u8>(code, 6, 10);

    if (immed_5 == 0) {
        const bool carry_bit = (Rm & (1 << 31));
        reg.write_cpsr(id::cpsr::C, carry_bit);

        reg.write(Rd_id, 0xFFFFFFFF * carry_bit);
    } else {
        //C Flag = Rm[immed_5 - 1]
        reg.write_cpsr(id::cpsr::C, (Rm & (1 << (immed_5 - 1))));
        reg.write(Rd_id, util::arithmetic_shift_right(Rm, immed_5));
    }

    const u32 Rd = reg.read(Rd_id);

    reg.write_cpsr(id::cpsr::N, (Rd & (1 << 31)));
    reg.write_cpsr(id::cpsr::Z, (Rd == 0));

    reg.thumb_increment_PC();
}


/*
 * if Rs[7:0] == 0 then
 *   C Flag = unaffected
 *   Rd = unaffected
 * else if Rs[7:0] < 32 then
 *   C Flag = Rd[Rs[7:0] - 1]
 *   Rd = Rd Arithmetic_Shift_Right Rs[7:0]
 * else /Rs[7:0] >= 32/
 *   C Flag = Rd[31]
 *   if Rd[31] == 0 then
 *     Rd = 0
 *   else /Rd[31] == 1/
 *     Rd = 0xFFFFFFFF
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * V Flag = unaffected
 */
void instructions::thumb::logic::ASR2(const thumbcode_t &code, REGISTERS &reg) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);
    const id::reg Rs_id = reg.fetch_reg_id(code, 3, 5);

    const u32 Rd = reg.read(Rd_id);
    const u32 Rs = reg.read(Rs_id);

    const u8 Rs_0_7 = util::bit_fetcher<u8>(Rs, 0, 7);

    if (Rs_0_7 == 0) {

    } else if (Rs_0_7 < 32) {
        reg.write_cpsr(id::cpsr::C, (Rd & (1 << (Rs_0_7 - 1))));
        reg.write(Rd_id, util::arithmetic_shift_right(Rd, Rs_0_7));
    } else {
        reg.write_cpsr(id::cpsr::C, (Rd & (1 << 31)));

        const bool carry_bit = (Rd & (1 << 31));

        reg.write(Rd_id, 0xFFFFFFFF * carry_bit);
    }

    reg.write_cpsr(id::cpsr::N, (Rd & (1 << 31)));
    reg.write_cpsr(id::cpsr::Z, (Rd == 0));

    reg.thumb_increment_PC();
}


/*
 * Rd = Rd AND NOT Rm
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * C Flag = unaffected
 * V Flag = unaffected
 */
void instructions::thumb::logic::BIC(const thumbcode_t &code, REGISTERS &reg) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);
    const id::reg Rm_id = reg.fetch_reg_id(code, 3, 5);

    reg.write(Rd_id, (reg.read(Rd_id) & ~reg.read(Rm_id)));

    const u32 Rd = reg.read(Rd_id);

    reg.write_cpsr(id::cpsr::N, (Rd & (1 << 31)));
    reg.write_cpsr(id::cpsr::Z, (Rd == 0));

    reg.thumb_increment_PC();
}


/*
 * Rd = Rd EOR Rm
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * C Flag = unaffected
 * V Flag = unaffected
 */
void instructions::thumb::logic::EOR(const thumbcode_t &code, REGISTERS &reg) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);

    const u32 Rm = reg.read(code, 3, 5);

    reg.write(Rd_id, reg.read(Rd_id) ^ Rm);

    const u32 Rd = reg.read(Rd_id);

    reg.write_cpsr(id::cpsr::N, (Rd & (1 << 31)));
    reg.write_cpsr(id::cpsr::Z, (Rd == 0));

    reg.thumb_increment_PC();
}


/*
 * if immed_5 == 0
 *   C Flag = unaffected
 *   Rd = Rm
 * else /immed_5 > 0/
 *   C Flag = Rm[32 - immed_5]
 *   Rd = Rm Logical_Shift_Left immed_5
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * V Flag = unaffected
 */
void instructions::thumb::logic::LSL1(const thumbcode_t &code, REGISTERS &reg) {
    const u8 immed_5 = util::bit_fetcher<u8>(code, 6, 10);
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);

    const u32 Rm = reg.read(code, 3, 5);

    if (immed_5 == 0) {
        reg.write(Rd_id, Rm);
    } else {
        reg.write_cpsr(id::cpsr::C, (Rm & (1 << (32 - immed_5))));
        reg.write(Rd_id, (Rm << immed_5));
    }

    const u32 Rd = reg.read(Rd_id);

    reg.write_cpsr(id::cpsr::N, (Rd & (1 << 31)));
    reg.write_cpsr(id::cpsr::Z, (Rd == 0));

    reg.thumb_increment_PC();
}


/*
 * if Rs[7:0] == 0
 *   C Flag = unaffected
 *   Rd = unaffected
 * else if Rs[7:0] < 32 then
 *   C Flag = Rd[32 - Rs[7:0]]
 *   Rd = Rd Logical_Shift_Left Rs[7:0]
 * else if Rs[7:0] == 32 then
 *   C Flag = Rd[0]
 *   Rd = 0
 * else /Rs[7:0] > 32/
 *   C Flag = 0
 *   Rd = 0
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * V Flag = unaffected
 */
void instructions::thumb::logic::LSL2(const thumbcode_t &code, REGISTERS &reg) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);

    const u32 Rs = reg.read(code, 3, 5);

    if ((Rs & 0xFF) == 0) {

    } else if ((Rs & 0xFF) < 32) {
        reg.write_cpsr(id::cpsr::C, (reg.read(Rd_id) & (1 << (32 - (Rs & 0xFF)))));
        reg.write(Rd_id, (reg.read(Rd_id) << (Rs & 0xFF)));
    } else if ((Rs & 0xFF) == 32) {
        reg.write_cpsr(id::cpsr::C, (reg.read(Rd_id) & 1));
        reg.write(Rd_id, 0);
    } else {
        reg.write_cpsr(id::cpsr::C, 0);
        reg.write(Rd_id, 0);
    }

    const u32 Rd = reg.read(Rd_id);

    reg.write_cpsr(id::cpsr::N, (Rd & (1 << 31)));
    reg.write_cpsr(id::cpsr::Z, (Rd == 0));

    reg.thumb_increment_PC();
}


/*
 * if immed_5 == 0
 *   C Flag = Rd[31]
 *   Rd = 0
 * else /immed_5 > 0/
 *   C Flag = Rd[immed_5 - 1]
 *   Rd = Rm Logical_Shift_Right immed_5
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * V Flag = unaffected
 */
void instructions::thumb::logic::LSR1(const thumbcode_t &code, REGISTERS &reg) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);

    const u8 immed_5 = util::bit_fetcher<u8>(code, 6, 10);
    const u32 Rm = reg.read(code, 3, 5);

    if (immed_5 == 0) {
        reg.write_cpsr(id::cpsr::C, (reg.read(Rd_id) & (1 << 31)));
        reg.write(Rd_id, 0);
    } else {
        reg.write_cpsr(id::cpsr::C, (reg.read(Rd_id) & (1 << (immed_5 - 1))));
        reg.write(Rd_id, (Rm >> immed_5));
    }

    const u32 Rd = reg.read(Rd_id);

    reg.write_cpsr(id::cpsr::N, (Rd & (1 << 31)));
    reg.write_cpsr(id::cpsr::Z, (Rd == 0));

    reg.thumb_increment_PC();
}


/*
 * if Rs[7:0] == 0 then
 *   C Flag = unaffected
 *   Rd = unaffected
 * else if Rs[7:0] < 32 then
 *   C Flag = Rd[Rs[7:0] - 1]
 *   Rd = Rd Logical_Shift_Right Rs[7:0]
 * else if Rs[7:0] == 32 then
 *   C Flag = Rd[31]
 *   Rd = 0
 * else /Rs[7:0] > 32/
 *   C Flag = 0
 *   Rd = 0
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * V Flag = unaffected
 */
void instructions::thumb::logic::LSR2(const thumbcode_t &code, REGISTERS &reg) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);

    const u32 Rs = reg.read(code, 3, 5);

    if ((Rs & 0xFF) == 0) {

    } else if ((Rs & 0xFF) < 32) {
        reg.write_cpsr(id::cpsr::C, (reg.read(Rd_id) & (1 << ((Rs & 0xFF) - 1))));
        reg.write(Rd_id, (reg.read(Rd_id) >> (Rs & 0xFF)));
    } else if ((Rs & 0xFF) == 32) {
        reg.write_cpsr(id::cpsr::C, (reg.read(Rd_id) & (1 << 31)));
        reg.write(Rd_id, 0);
    } else {
        reg.write_cpsr(id::cpsr::C, 0);
        reg.write(Rd_id, 0);
    }

    const u32 Rd = reg.read(Rd_id);

    reg.write_cpsr(id::cpsr::N, (Rd & (1 << 31)));
    reg.write_cpsr(id::cpsr::Z, (Rd == 0));

    reg.thumb_increment_PC();
}


/*
 * Rd = 0 - Rm
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * C Flag = NOT BorrowFrom(0 - Rm)
 * V Flag = OverflowFrom(0 - Rm)
 */
void instructions::thumb::logic::NEG(const thumbcode_t &code, REGISTERS &reg) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);

    const u32 Rm = reg.read(code, 3, 5);

    reg.write(Rd_id, 0 - Rm);

    const u32 Rd = reg.read(Rd_id);

    reg.write_cpsr(id::cpsr::N, (Rd & (1 << 31)));
    reg.write_cpsr(id::cpsr::Z, (Rd == 0));
    reg.write_cpsr(id::cpsr::C, !util::borrow_sub(0, Rm));
    reg.write_cpsr(id::cpsr::V, util::overflow_sub(0, Rm));

    reg.thumb_increment_PC();
}


/*
 * Rd = Rd OR Rm
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * C Flag = unaffected
 * V Flag = unaffected
 */
void instructions::thumb::logic::ORR(const thumbcode_t &code, REGISTERS &reg) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);

    const u32 Rm = reg.read(code, 3, 5);

    reg.write(Rd_id, (reg.read(Rd_id) | Rm));

    const u32 Rd = reg.read(Rd_id);

    reg.write_cpsr(id::cpsr::N, (Rd & (1 << 31)));
    reg.write_cpsr(id::cpsr::Z, (Rd == 0));

    reg.thumb_increment_PC();
}


/*
 * if Rs[7:0] == 0 then
 *   C Flag = unaffected
 *   Rd = unaffected
 * else if Rs[4:0] == 0 then
 *   C Flag = Rd[31]
 *   Rd = unaffected
 * else /Rs[4:0] > 0/
 *   C Flag = Rd[Rs[4:0] - 1]
 *   Rd = Rd Rotate_Right Rs[4:0]
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * V Flag = unaffected
 */
void instructions::thumb::logic::ROR(const thumbcode_t &code, REGISTERS &reg) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);

    const u32 Rs = reg.read(code, 3, 5);

    const u8 Rs_4_0 = (Rs & 0b11111);

    if ((Rs & 0xFF) == 0) {

    } else if (Rs_4_0 == 0) {
        reg.write_cpsr(id::cpsr::C, (reg.read(Rd_id) & (1 << 31)));
    } else {
        reg.write_cpsr(id::cpsr::C, (reg.read(Rd_id) & (1 << (Rs_4_0 - 1))));
        reg.write(Rd_id, std::rotr(reg.read(Rd_id), Rs_4_0));
    }

    const u32 Rd = reg.read(Rd_id);

    reg.write_cpsr(id::cpsr::N, (Rd & (1 << 31)));
    reg.write_cpsr(id::cpsr::Z, (Rd == 0));

    reg.thumb_increment_PC();
}


/*
 * alu_out = Rn AND Rm
 * N Flag = alu_out[31]
 * Z Flag = if alu_out == 0 then 1 else 0
 * C Flag = unaffected
 * V Flag = unaffected
 */
void instructions::thumb::logic::TST(const thumbcode_t &code, REGISTERS &reg) {
    const u32 Rn = reg.read(code, 0, 2);
    const u32 Rm = reg.read(code, 3, 5);

    const u32 alu_out = Rn & Rm;

    reg.write_cpsr(id::cpsr::N, (alu_out & (1 << 31)));
    reg.write_cpsr(id::cpsr::Z, (alu_out == 0));

    reg.thumb_increment_PC();
}



















































/*
 * if ConditionPassed(cond) then
 *   Rd = Rn AND shifter_operand
 *   if S == 1 and Rd == R15 then
 *     CPSR = SPSR
 *   else if S == 1 then
 *     N Flag = Rd[31]
 *     Z Flag = if Rd == 0 then 1 else 0
 *     C Flag = shifter_carry_out
 *     V Flag = unaffected
 */
void instructions::logic::AND(const code_t &code, REGISTERS &reg) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);

    const u16 shifter_operand = util::bit_fetcher<u16>(code, 0, 11);
    const u32 Rn = reg.read(code, 16, 19);

    const bool S = code.test(20);
    const bool I = code.test(25);

    reg.write(Rd_id, Rn & shifter_operand);

    if ((S == 1) && (Rd_id == id::reg::R15)) {
        reg.write_cpsr(id::reg::CURRENT_SPSR);
    } else if (S == 1) {
        const u32 Rd = reg.read(Rd_id);
        reg.write_cpsr(id::cpsr::N, (Rd & (1 << 31)));
        reg.write_cpsr(id::cpsr::Z, (Rd == 0));
        //TODO:
        //reg.write_cpsr(id::cpsr::C, ());
    }

    reg.increment_PC();
}


/*
 * if Rm == 0
 *   Rd = 32
 * else
 *   Rd = 31 - (bit position of most significant ’1’ in Rm)
 */
void instructions::logic::CLZ(const code_t &code, REGISTERS &reg) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);

    const u32 Rm = reg.read(code, 0, 3);

    if (Rm == 0) {
        reg.write(Rd_id, 32);
    } else {
        reg.write(Rd_id, 31 - (std::bit_width(Rm) - 1));
    }

    reg.increment_PC();
}





/*
 * if ConditionPassed(cond) then
 *   Rd = Rn EOR shifter_operand
 *   if S == 1 and Rd == R15 then
 *     CPSR = SPSR
 *   else if S == 1 then
 *     N Flag = Rd[31]
 *     Z Flag = if Rd == 0 then 1 else 0
 *     C Flag = shifter_carry_out
 *     V Flag = unaffected
 */
void instructions::logic::EOR(const code_t &code, REGISTERS &reg) {
    
}