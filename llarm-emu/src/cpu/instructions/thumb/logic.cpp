#include "../../core/registers.hpp"
#include "../instructions.hpp"

#include <bit>

#include "shared/types.hpp"
#include "shared/util.hpp"


/*
 * Rd = Rd AND Rm
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * C Flag = unaffected
 * V Flag = unaffected
 */
void INSTRUCTIONS::thumb::logic::AND(const thumb_code_t &code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);

    const u32 Rm = reg.read(code, 3, 5);

    reg.write(Rd_id, reg.read(Rd_id) & Rm);

    const u32 Rd = reg.read(Rd_id);

    reg.write(id::cpsr::N, (shared::util::bit_fetch(Rd, 31)));
    reg.write(id::cpsr::Z, (Rd == 0));
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
void INSTRUCTIONS::thumb::logic::ASR1(const thumb_code_t &code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);

    const u32 Rm = reg.read(code, 3, 5);
    const u8 immed_5 = shared::util::bit_range<u8>(code, 6, 10);

    if (immed_5 == 0) {
        const bool carry_bit = (shared::util::bit_fetch(Rm, 31));
        reg.write(id::cpsr::C, carry_bit);

        reg.write(Rd_id, 0xFFFFFFFF * carry_bit);
    } else {
        //C Flag = Rm[immed_5 - 1]
        reg.write(id::cpsr::C, (shared::util::bit_fetch(Rm, (immed_5 - 1))));
        reg.write(Rd_id, operation.arithmetic_shift_right(Rm, immed_5));
    }

    const u32 Rd = reg.read(Rd_id);

    reg.write(id::cpsr::N, (shared::util::bit_fetch(Rd, 31)));
    reg.write(id::cpsr::Z, (Rd == 0));
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
void INSTRUCTIONS::thumb::logic::ASR2(const thumb_code_t &code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);
    const id::reg Rs_id = reg.fetch_reg_id(code, 3, 5);

    const u32 Rd = reg.read(Rd_id);
    const u32 Rs = reg.read(Rs_id);

    const u8 Rs_0_7 = shared::util::bit_range<u8, u32>(Rs, 0, 7);

    if (Rs_0_7 == 0) {

    } else if (Rs_0_7 < 32) {
        reg.write(id::cpsr::C, shared::util::bit_fetch(Rd, (Rs_0_7 - 1)));
        reg.write(Rd_id, operation.arithmetic_shift_right(Rd, Rs_0_7));
    } else {
        reg.write(id::cpsr::C, (shared::util::bit_fetch(Rd, 31)));

        const bool carry_bit = shared::util::bit_fetch(Rd, 31);

        reg.write(Rd_id, 0xFFFFFFFF * carry_bit);
    }

    reg.write(id::cpsr::N, (shared::util::bit_fetch(Rd, 31)));
    reg.write(id::cpsr::Z, (Rd == 0));
}


/*
 * Rd = Rd AND NOT Rm
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * C Flag = unaffected
 * V Flag = unaffected
 */
void INSTRUCTIONS::thumb::logic::BIC(const thumb_code_t &code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);
    const id::reg Rm_id = reg.fetch_reg_id(code, 3, 5);

    reg.write(Rd_id, (reg.read(Rd_id) & ~reg.read(Rm_id)));

    const u32 Rd = reg.read(Rd_id);

    reg.write(id::cpsr::N, (shared::util::bit_fetch(Rd, 31)));
    reg.write(id::cpsr::Z, (Rd == 0));
}


/*
 * Rd = Rd EOR Rm
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * C Flag = unaffected
 * V Flag = unaffected
 */
void INSTRUCTIONS::thumb::logic::EOR(const thumb_code_t &code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);

    const u32 Rm = reg.read(code, 3, 5);

    reg.write(Rd_id, reg.read(Rd_id) ^ Rm);

    const u32 Rd = reg.read(Rd_id);

    reg.write(id::cpsr::N, (shared::util::bit_fetch(Rd, 31)));
    reg.write(id::cpsr::Z, (Rd == 0));
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
void INSTRUCTIONS::thumb::logic::LSL1(const thumb_code_t &code) {
    const u8 immed_5 = shared::util::bit_range<u8>(code, 6, 10);
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);

    const u32 Rm = reg.read(code, 3, 5);

    if (immed_5 == 0) {
        reg.write(Rd_id, Rm);
    } else {
        reg.write(id::cpsr::C, (shared::util::bit_fetch(Rm, (32 - immed_5))));
        reg.write(Rd_id, (Rm << immed_5));
    }

    const u32 Rd = reg.read(Rd_id);

    reg.write(id::cpsr::N, (shared::util::bit_fetch(Rd, 31)));
    reg.write(id::cpsr::Z, (Rd == 0));
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
void INSTRUCTIONS::thumb::logic::LSL2(const thumb_code_t &code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);

    const u32 Rs = reg.read(code, 3, 5);

    if ((Rs & 0xFF) == 0) {

    } else if ((Rs & 0xFF) < 32) {
        reg.write(id::cpsr::C, shared::util::bit_fetch(reg.read(Rd_id), (32 - (Rs & 0xFF))));
        reg.write(Rd_id, (reg.read(Rd_id) << (Rs & 0xFF)));
    } else if ((Rs & 0xFF) == 32) {
        reg.write(id::cpsr::C, (reg.read(Rd_id) & 1));
        reg.write(Rd_id, 0);
    } else {
        reg.write(id::cpsr::C, 0);
        reg.write(Rd_id, 0);
    }

    const u32 Rd = reg.read(Rd_id);

    reg.write(id::cpsr::N, (shared::util::bit_fetch(Rd, 31)));
    reg.write(id::cpsr::Z, (Rd == 0));
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
void INSTRUCTIONS::thumb::logic::LSR1(const thumb_code_t &code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);

    const u8 immed_5 = shared::util::bit_range<u8>(code, 6, 10);
    const u32 Rm = reg.read(code, 3, 5);

    if (immed_5 == 0) {
        reg.write(id::cpsr::C, shared::util::bit_fetch(reg.read(Rd_id), 31));
        reg.write(Rd_id, 0);
    } else {
        reg.write(id::cpsr::C, shared::util::bit_fetch(reg.read(Rd_id), (immed_5 - 1)));
        reg.write(Rd_id, (Rm >> immed_5));
    }

    const u32 Rd = reg.read(Rd_id);

    reg.write(id::cpsr::N, (shared::util::bit_fetch(Rd, 31)));
    reg.write(id::cpsr::Z, (Rd == 0));
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
void INSTRUCTIONS::thumb::logic::LSR2(const thumb_code_t &code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);

    const u32 Rs = reg.read(code, 3, 5);

    if ((Rs & 0xFF) == 0) {

    } else if ((Rs & 0xFF) < 32) {
        reg.write(id::cpsr::C, shared::util::bit_fetch(reg.read(Rd_id), ((Rs & 0xFF) - 1)));
        reg.write(Rd_id, (reg.read(Rd_id) >> (Rs & 0xFF)));
    } else if ((Rs & 0xFF) == 32) {
        reg.write(id::cpsr::C, shared::util::bit_fetch(reg.read(Rd_id), 31));
        reg.write(Rd_id, 0);
    } else {
        reg.write(id::cpsr::C, 0);
        reg.write(Rd_id, 0);
    }

    const u32 Rd = reg.read(Rd_id);

    reg.write(id::cpsr::N, (shared::util::bit_fetch(Rd, 31)));
    reg.write(id::cpsr::Z, (Rd == 0));
}


/*
 * Rd = 0 - Rm
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * C Flag = NOT BorrowFrom(0 - Rm)
 * V Flag = OverflowFrom(0 - Rm)
 */
void INSTRUCTIONS::thumb::logic::NEG(const thumb_code_t &code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);

    const u32 Rm = reg.read(code, 3, 5);

    reg.write(Rd_id, 0 - Rm);

    const u32 Rd = reg.read(Rd_id);

    reg.write(id::cpsr::N, (shared::util::bit_fetch(Rd, 31)));
    reg.write(id::cpsr::Z, (Rd == 0));
    reg.write(id::cpsr::C, !operation.borrow_sub(0, Rm));
    reg.write(id::cpsr::V, operation.overflow_sub(0, Rm));
}


/*
 * Rd = Rd OR Rm
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * C Flag = unaffected
 * V Flag = unaffected
 */
void INSTRUCTIONS::thumb::logic::ORR(const thumb_code_t &code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);

    const u32 Rm = reg.read(code, 3, 5);

    reg.write(Rd_id, (reg.read(Rd_id) | Rm));

    const u32 Rd = reg.read(Rd_id);

    reg.write(id::cpsr::N, (shared::util::bit_fetch(Rd, 31)));
    reg.write(id::cpsr::Z, (Rd == 0));
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
void INSTRUCTIONS::thumb::logic::ROR(const thumb_code_t &code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);

    const u32 Rs = reg.read(code, 3, 5);

    const u8 Rs_4_0 = (Rs & 0b11111);

    if ((Rs & 0xFF) == 0) {

    } else if (Rs_4_0 == 0) {
        reg.write(id::cpsr::C, shared::util::bit_fetch(reg.read(Rd_id), 31));
    } else {
        reg.write(id::cpsr::C, shared::util::bit_fetch(reg.read(Rd_id), (Rs_4_0 - 1)));
        reg.write(Rd_id, std::rotr(reg.read(Rd_id), Rs_4_0));
    }

    const u32 Rd = reg.read(Rd_id);

    reg.write(id::cpsr::N, (shared::util::bit_fetch(Rd, 31)));
    reg.write(id::cpsr::Z, (Rd == 0));
}


/*
 * alu_out = Rn AND Rm
 * N Flag = alu_out[31]
 * Z Flag = if alu_out == 0 then 1 else 0
 * C Flag = unaffected
 * V Flag = unaffected
 */
void INSTRUCTIONS::thumb::logic::TST(const thumb_code_t &code) {
    const u32 Rn = reg.read(code, 0, 2);
    const u32 Rm = reg.read(code, 3, 5);

    const u32 alu_out = Rn & Rm;

    reg.write(id::cpsr::N, (shared::util::bit_fetch(alu_out, 31)));
    reg.write(id::cpsr::Z, (alu_out == 0));
}