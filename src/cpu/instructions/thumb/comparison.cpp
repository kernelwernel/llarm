#include "types.hpp"
#include "utility.hpp"
#include "cpu/instructions/instructions.hpp"
#include "cpu/core/registers.hpp"

/*
 * alu_out = Rn + Rm
 * N Flag = alu_out[31]
 * Z Flag = if alu_out == 0 then 1 else 0
 * C Flag = NOT BorrowFrom(Rn + Rm)
 * V Flag = OverflowFrom(Rn + Rm)
 */
void instructions::thumb::compare::CMN(const thumb_code_t &code, REGISTERS &reg) {
    const u32 Rn = reg.read(code, 0, 2);
    const u32 Rm = reg.read(code, 3, 5);
    const i32 alu_out = Rn + Rm;

    reg.write(id::cpsr::N, (alu_out & (1 << 31)));
    reg.write(id::cpsr::Z, (alu_out == 0));
    reg.write(id::cpsr::C, !util::borrow_add(Rn, Rm));
    reg.write(id::cpsr::V, util::overflow_add(Rn, Rm));

    reg.thumb_increment_PC();
}


/*
 * alu_out = Rn - immed_8
 * N Flag = alu_out[31]
 * Z Flag = if alu_out == 0 then 1 else 0
 * C Flag = NOT BorrowFrom(Rn - immed_8)
 * V Flag = OverflowFrom(Rn - immed_8)
 */
void instructions::thumb::compare::CMP1(const thumb_code_t &code, REGISTERS &reg) {
    const u32 Rn = reg.read(code, 8, 10);
    const u8 immed_8 = util::bit_fetcher<u8>(code, 0, 7);

    const i32 alu_out = Rn - immed_8;

    reg.write(id::cpsr::N, (alu_out & (1 << 31)));
    reg.write(id::cpsr::Z, (alu_out == 0));
    reg.write(id::cpsr::C, !util::borrow_sub(Rn, immed_8));
    reg.write(id::cpsr::V, util::overflow_sub(Rn, immed_8));

    reg.thumb_increment_PC();
}


/*
 * alu_out = Rn - Rm
 * N Flag = alu_out[31]
 * Z Flag = if alu_out == 0 then 1 else 0
 * C Flag = NOT BorrowFrom(Rn - Rm)
 * V Flag = OverflowFrom(Rn - Rm)
 */
void instructions::thumb::compare::CMP2(const thumb_code_t &code, REGISTERS &reg) {
    const u32 Rn = reg.read(code, 0, 2);
    const u32 Rm = reg.read(code, 3, 5);

    const i32 alu_out = Rn - Rm;

    reg.write(id::cpsr::N, (alu_out & (1 << 31)));
    reg.write(id::cpsr::Z, (alu_out == 0));
    reg.write(id::cpsr::C, !util::borrow_sub(Rn, Rm));
    reg.write(id::cpsr::V, util::overflow_sub(Rn, Rm));

    reg.thumb_increment_PC();
}


/*
 * alu_out = Rn - Rm
 * N Flag = alu_out[31]
 * Z Flag = if alu_out == 0 then 1 else 0
 * C Flag = NOT BorrowFrom(Rn - Rm)
 * V Flag = OverflowFrom(Rn - Rm)
 */
void instructions::thumb::compare::CMP3(const thumb_code_t &code, REGISTERS &reg) {
    u8 Rn_bits = util::bit_fetcher<u8>(code, 0, 2);
    u8 Rm_bits = util::bit_fetcher<u8>(code, 3, 5);

    const bool H2 = code.test(6);
    const bool H1 = code.test(7);

    Rn_bits += (8 * H1);
    Rm_bits += (8 * H2);

    const id::reg Rn_id = reg.fetch_reg_id(Rn_bits);
    const id::reg Rm_id = reg.fetch_reg_id(Rm_bits);

    const u32 Rn = reg.read(Rn_id);
    const u32 Rm = reg.read(Rm_id);

    const i32 alu_out = Rn - Rm;

    reg.write(id::cpsr::N, (alu_out & (1 << 31)));
    reg.write(id::cpsr::Z, (alu_out == 0));
    reg.write(id::cpsr::C, !util::borrow_sub(Rn, Rm));
    reg.write(id::cpsr::V, util::overflow_sub(Rn, Rm));

    reg.thumb_increment_PC();
}
