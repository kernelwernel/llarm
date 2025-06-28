#include "../../instructions/instructions.hpp"
#include "../../core/registers.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"

/*
 * alu_out = Rn + Rm
 * N Flag = alu_out[31]
 * Z Flag = if alu_out == 0 then 1 else 0
 * C Flag = NOT BorrowFrom(Rn + Rm)
 * V Flag = OverflowFrom(Rn + Rm)
 */
void INSTRUCTIONS::thumb::compare::CMN(const u16 code) {
    const u32 Rn = reg.read(code, 0, 2);
    const u32 Rm = reg.read(code, 3, 5);
    const i32 alu_out = Rn + Rm;

    reg.write(id::cpsr::N, (shared::util::bit_fetch(alu_out, 31)));
    reg.write(id::cpsr::Z, (alu_out == 0));
    reg.write(id::cpsr::C, !operation.borrow_add(Rn, Rm));
    reg.write(id::cpsr::V, operation.overflow_add(Rn, Rm));
}


/*
 * alu_out = Rn - immed_8
 * N Flag = alu_out[31]
 * Z Flag = if alu_out == 0 then 1 else 0
 * C Flag = NOT BorrowFrom(Rn - immed_8)
 * V Flag = OverflowFrom(Rn - immed_8)
 */
void INSTRUCTIONS::thumb::compare::CMP1(const u16 code) {
    const u32 Rn = reg.read(code, 8, 10);
    const u8 immed_8 = shared::util::bit_range<u8>(code, 0, 7);

    const i32 alu_out = Rn - immed_8;

    reg.write(id::cpsr::N, (shared::util::bit_fetch(alu_out, 31)));
    reg.write(id::cpsr::Z, (alu_out == 0));
    reg.write(id::cpsr::C, !operation.borrow_sub(Rn, immed_8));
    reg.write(id::cpsr::V, operation.overflow_sub(Rn, immed_8));
}


/*
 * alu_out = Rn - Rm
 * N Flag = alu_out[31]
 * Z Flag = if alu_out == 0 then 1 else 0
 * C Flag = NOT BorrowFrom(Rn - Rm)
 * V Flag = OverflowFrom(Rn - Rm)
 */
void INSTRUCTIONS::thumb::compare::CMP2(const u16 code) {
    const u32 Rn = reg.read(code, 0, 2);
    const u32 Rm = reg.read(code, 3, 5);

    const i32 alu_out = Rn - Rm;

    reg.write(id::cpsr::N, (shared::util::bit_fetch(alu_out, 31)));
    reg.write(id::cpsr::Z, (alu_out == 0));
    reg.write(id::cpsr::C, !operation.borrow_sub(Rn, Rm));
    reg.write(id::cpsr::V, operation.overflow_sub(Rn, Rm));
}


/*
 * alu_out = Rn - Rm
 * N Flag = alu_out[31]
 * Z Flag = if alu_out == 0 then 1 else 0
 * C Flag = NOT BorrowFrom(Rn - Rm)
 * V Flag = OverflowFrom(Rn - Rm)
 */
void INSTRUCTIONS::thumb::compare::CMP3(const u16 code) {
    u8 Rn_bits = shared::util::bit_range<u8>(code, 0, 2);
    u8 Rm_bits = shared::util::bit_range<u8>(code, 3, 5);

    const bool H2 = shared::util::bit_fetch(code, 6);
    const bool H1 = shared::util::bit_fetch(code, 7);

    Rn_bits += (8 * H1);
    Rm_bits += (8 * H2);

    const id::reg Rn_id = reg.fetch_reg_id(Rn_bits);
    const id::reg Rm_id = reg.fetch_reg_id(Rm_bits);

    const u32 Rn = reg.read(Rn_id);
    const u32 Rm = reg.read(Rm_id);

    const i32 alu_out = Rn - Rm;

    reg.write(id::cpsr::N, (shared::util::bit_fetch(alu_out, 31)));
    reg.write(id::cpsr::Z, (alu_out == 0));
    reg.write(id::cpsr::C, !operation.borrow_sub(Rn, Rm));
    reg.write(id::cpsr::V, operation.overflow_sub(Rn, Rm));
}
