#include "../../instructions/instructions.hpp"
#include "../../core/registers.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"

#include <limits>

/*
 * Rd = Rd + Rm + C Flag
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * C Flag = CarryFrom(Rd + Rm + C Flag)
 * V Flag = OverflowFrom(Rd + Rm + C Flag)
 */
void INSTRUCTIONS::thumb::math::ADC(const u16 code) {
    const id::reg Rd_id = reg.thumb_fetch_reg_id(code, 0, 2);

    const u32 Rd = reg.read(Rd_id);
    const u32 Rm = reg.read(code, 3, 5);
    const bool c_flag = reg.read(id::cpsr::C);

    const u64 result = (Rd + Rm + c_flag);

    reg.write(Rd_id, (result & (std::numeric_limits<u32>::max()))); // basically the same as static_cast<u32>

    reg.write(id::cpsr::N, llarm::util::bit_fetch(reg.read(Rd_id), 31));
    reg.write(id::cpsr::Z, (reg.read(Rd_id) == 0));
    reg.write(id::cpsr::C, operation.carry_add(result));
    reg.write(id::cpsr::V, operation.overflow_add(Rd, Rm, c_flag));
}


/*
 * Rd = Rn + immed_3
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * C Flag = CarryFrom(Rn + immed_3)
 * V Flag = OverflowFrom(Rn + immed_3)
 */
void INSTRUCTIONS::thumb::math::ADD1(const u16 code) {
    const id::reg Rd_id = reg.thumb_fetch_reg_id(code, 0, 2);
    const u8 immed_3 = llarm::util::bit_range<u8>(code, 6, 8);

    const u32 Rn = reg.read(code, 3, 5);

    reg.write(Rd_id, Rn + immed_3);

    const u32 Rd = reg.read(Rd_id);

    reg.write(id::cpsr::N, (llarm::util::bit_fetch(Rd, 31)));
    reg.write(id::cpsr::Z, (Rd == 0));
    reg.write(id::cpsr::C, operation.carry_add(Rn, immed_3));
    reg.write(id::cpsr::V, operation.overflow_add(Rn, immed_3));
}


/*
 * Rd = Rd + immed_8
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * C Flag = CarryFrom(Rd + immed_8)
 * V Flag = OverflowFrom(Rd + immed_8)
 */
void INSTRUCTIONS::thumb::math::ADD2(const u16 code) {
    const id::reg Rd_id = reg.thumb_fetch_reg_id(code, 8, 10);
    const u8 immed_8 = llarm::util::bit_range<u8>(code, 0, 7);

    reg.write(Rd_id, reg.read(Rd_id) + immed_8);

    const u32 Rd = reg.read(Rd_id);

    reg.write(id::cpsr::N, (llarm::util::bit_fetch(Rd, 31)));
    reg.write(id::cpsr::Z, (Rd == 0));
    reg.write(id::cpsr::C, operation.carry_add(Rd, immed_8));
    reg.write(id::cpsr::V, operation.overflow_add(Rd, immed_8));
}


/*
 * Rd = Rn + Rm
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * C Flag = CarryFrom(Rn + Rm)
 * V Flag = OverflowFrom(Rn + Rm)
 */
void INSTRUCTIONS::thumb::math::ADD3(const u16 code) {
    const id::reg Rd_id = reg.thumb_fetch_reg_id(code, 0, 2);

    const u32 Rn = reg.read(code, 3, 5);
    const u32 Rm = reg.read(code, 6, 8);

    reg.write(Rd_id, Rn + Rm);

    const u32 Rd = reg.read(Rd_id);

    reg.write(id::cpsr::N, (llarm::util::bit_fetch(Rd, 31)));
    reg.write(id::cpsr::Z, (Rd == 0));
    reg.write(id::cpsr::C, operation.carry_add(Rn, Rm));
    reg.write(id::cpsr::V, operation.overflow_add(Rn, Rm));
}


/*
 * Rd = Rd + Rm
 */
void INSTRUCTIONS::thumb::math::ADD4(const u16 code) {
    u8 Rd_bits = llarm::util::bit_range<u8>(code, 0, 2);
    u8 Rm_bits = llarm::util::bit_range<u8>(code, 3, 5);
    const bool H1 = llarm::util::bit_fetch(code, 7);
    const bool H2 = llarm::util::bit_fetch(code, 6);

    // branchless version of "if H1/H2 is true, add 8" 
    Rd_bits = Rd_bits + (8 * H1);
    Rm_bits = Rm_bits + (8 * H2);

    const id::reg Rd_id = reg.fetch_reg_id(Rd_bits);
    const id::reg Rm_id = reg.fetch_reg_id(Rm_bits);

    const u32 Rd = reg.read(Rd_id);
    const u32 Rm = reg.read(Rm_id);

    reg.write(Rd_id, Rd + Rm);
}


/*
 * Rd = (PC AND 0xFFFFFFFC) + (immed_8 << 2)
 */
void INSTRUCTIONS::thumb::math::ADD5(const u16 code) {
    const u8 immed_8 = llarm::util::bit_range<u8>(code, 0, 7);

    const id::reg Rd_id = reg.thumb_fetch_reg_id(code, 8, 10);

    reg.write(Rd_id, (reg.read(id::reg::PC) & 0xFFFFFFFC) + (immed_8 << 2));
}


/*
 * Rd = SP + (immed_8 << 2)
 */
void INSTRUCTIONS::thumb::math::ADD6(const u16 code) {
    const u8 immed_8 = llarm::util::bit_range<u8>(code, 0, 7);
    const id::reg Rd_id = reg.thumb_fetch_reg_id(code, 8, 10);

    reg.write(Rd_id, (reg.read(id::reg::SP) + (immed_8 << 2)));
}


/*
 * SP = SP + (immed_7 << 2)
 */
void INSTRUCTIONS::thumb::math::ADD7(const u16 code) {
    const u8 immed_7 = llarm::util::bit_range<u8>(code, 0, 6);

    reg.write(id::reg::SP, (reg.read(id::reg::SP) + (immed_7 << 2)));
}


/*
 * Rd = Rd - Rm - NOT(C Flag)
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * C Flag = NOT BorrowFrom(Rd - Rm - NOT(C Flag))
 * V Flag = OverflowFrom(Rd - Rm - NOT(C Flag))
 */
void INSTRUCTIONS::thumb::math::SBC(const u16 code) {
    const id::reg Rd_id = reg.thumb_fetch_reg_id(code, 0, 2);

    const u32 Rm = reg.read(code, 3, 5);

    reg.write(Rd_id, (reg.read(Rd_id) - Rm - !reg.read(id::cpsr::C)));

    const u32 Rd = reg.read(Rd_id);

    reg.write(id::cpsr::N, (llarm::util::bit_fetch(Rd, 31)));
    reg.write(id::cpsr::Z, (Rd == 0));
    reg.write(id::cpsr::C, !operation.borrow_sub(Rd, Rm, !reg.read(id::cpsr::C)));
    reg.write(id::cpsr::V, operation.overflow_sub(Rd, Rm, !reg.read(id::cpsr::C)));
}


/**
 * Rd = Rn - immed_3
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * C Flag = NOT BorrowFrom(Rn - immed_3)
 * V Flag = OverflowFrom(Rn - immed_3)
 */
void INSTRUCTIONS::thumb::math::SUB1(const u16 code) {
    const u8 immed_3 = llarm::util::bit_range<u8>(code, 6, 8);
    const id::reg Rn_id = reg.thumb_fetch_reg_id(code, 3, 5);
    const id::reg Rd_id = reg.thumb_fetch_reg_id(code, 0, 2);

    const u32 Rn = reg.read(Rn_id);

    reg.write(Rd_id, (Rn - immed_3));

    const u32 Rd = reg.read(Rd_id);

    reg.write(id::cpsr::N, (llarm::util::bit_fetch(Rd, 31)));
    reg.write(id::cpsr::Z, (Rd == 0));
    reg.write(id::cpsr::C, !operation.borrow_sub(Rn, immed_3));
    reg.write(id::cpsr::V, operation.overflow_sub(Rn, immed_3));
}


/**
 * Rd = Rd - immed_8
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * C Flag = NOT BorrowFrom(Rd - immed_8)
 * V Flag = OverflowFrom(Rd - immed_8)
 */
void INSTRUCTIONS::thumb::math::SUB2(const u16 code) {
    const u8 immed_8 = llarm::util::bit_range<u8>(code, 0, 7);
    const id::reg Rd_id = reg.thumb_fetch_reg_id(code, 8, 10);

    reg.write(Rd_id, (reg.read(Rd_id) - immed_8));

    const u32 Rd = reg.read(Rd_id);

    reg.write(id::cpsr::N, (llarm::util::bit_fetch(Rd, 31)));
    reg.write(id::cpsr::Z, (Rd == 0));
    reg.write(id::cpsr::C, !operation.borrow_sub(Rd, immed_8));
    reg.write(id::cpsr::V, operation.overflow_sub(Rd, immed_8));
}


/**
 * Rd = Rn - Rm
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * C Flag = NOT BorrowFrom(Rn - Rm)
 * V Flag = OverflowFrom(Rn - Rm)
 */
void INSTRUCTIONS::thumb::math::SUB3(const u16 code) {
    const id::reg Rd_id = reg.thumb_fetch_reg_id(code, 0, 2);
    const id::reg Rn_id = reg.thumb_fetch_reg_id(code, 3, 5);
    const id::reg Rm_id = reg.thumb_fetch_reg_id(code, 6, 8);

    reg.write(Rd_id, (reg.read(Rn_id) - reg.read(Rm_id)));

    const u32 Rd = reg.read(Rd_id);
    const u32 Rn = reg.read(Rn_id);
    const u32 Rm = reg.read(Rm_id);

    reg.write(id::cpsr::N, (llarm::util::bit_fetch(Rd, 31)));
    reg.write(id::cpsr::Z, (Rd == 0));
    reg.write(id::cpsr::C, !operation.borrow_sub(Rn, Rm));
    reg.write(id::cpsr::V, operation.overflow_sub(Rn, Rm));
}

/**
 * SP = SP - (immed_7 << 2)
 */
void INSTRUCTIONS::thumb::math::SUB4(const u16 code) {
    const u8 immed_7 = llarm::util::bit_range<u8>(code, 0, 6);

    reg.write(id::reg::SP, (reg.read(id::reg::SP) - (immed_7 << 2)));
}


/*
 * Rd = (Rm * Rd)[31:0]
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * C Flag = unaffected
 * V Flag = unaffected
 */
void INSTRUCTIONS::thumb::math::MUL(const u16 code) {
    const id::reg Rd_id = reg.thumb_fetch_reg_id(code, 0, 2);

    const u32 Rm = reg.read(code, 3, 5);

    reg.write(Rd_id, ((Rm * reg.read(Rd_id)) & 0xFFFFFFFF));

    const u32 Rd = reg.read(Rd_id);

    reg.write(id::cpsr::N, (llarm::util::bit_fetch(Rd, 31)));
    reg.write(id::cpsr::Z, (Rd == 0));
}