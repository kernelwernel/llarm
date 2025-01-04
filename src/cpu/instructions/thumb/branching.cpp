#include "types.hpp"
#include "utility.hpp"
#include "cpu/instructions/instructions.hpp"
#include "cpu/core/registers.hpp"

/*
 * if ConditionPassed(cond) then
 *   PC = PC + (SignExtend(signed_immed_8) << 1)
 */
void instructions::thumb::branching::B1(const thumb_code_t &code, REGISTERS &reg) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);

    const i8 signed_immed_8 = util::bit_fetcher<i8>(code, 0, 7);

    const id::cond cond = reg.fetch_cond_id(util::bit_fetcher<u8>(code, 8, 11));

    if (reg.check_cond(cond)) {
        reg.write(id::reg::PC, (reg.PC + ((static_cast<i32>(signed_immed_8)) << 1)));
    }
}


/*
 * PC = PC + (SignExtend(signed_immed_11) << 1)
 */
void instructions::thumb::branching::B2(const thumb_code_t &code, REGISTERS &reg) {
    const i16 signed_immed_10 = util::bit_fetcher<i16>(code, 0, 10);

    reg.write(id::reg::PC, (reg.PC + ((static_cast<i32>(signed_immed_10)) << 1)));
}


/*
 * if H == 10 then
 *   LR = PC + (SignExtend(offset_11) << 12)
 * else if H == 11 then
 *   PC = LR + (offset_11 << 1)
 *   LR = (address of next instruction) | 1
 * else if H == 01 then
 *   PC = (LR + (offset_11 << 1)) AND 0xFFFFFFFC
 *   LR = (address of next instruction) | 1
 *   T Flag = 0
 */
void instructions::thumb::branching::BL(const thumb_code_t &code, REGISTERS &reg) {
    const u16 offset_11 = util::bit_fetcher<u16>(code, 0, 10);
    const u8 H = util::bit_fetcher<u8>(code, 11, 12);

    //const u32 PC = reg.read(id::reg::PC);

    // CONTINUE
}


/*
 * if H == 10 then
 *   LR = PC + (SignExtend(offset_11) << 12)
 * else if H == 11 then
 *   PC = LR + (offset_11 << 1)
 *   LR = (address of next instruction) | 1
 * else if H == 01 then
 *   PC = (LR + (offset_11 << 1)) AND 0xFFFFFFFC
 *   LR = (address of next instruction) | 1
 *   T Flag = 0
 */
void instructions::thumb::branching::BLX1(const thumb_code_t &code, REGISTERS &reg) {
    const u16 offset_11 = util::bit_fetcher<u16>(code, 0, 10);
    const u8 H = util::bit_fetcher<u8>(code, 11, 12);

    const u32 PC = reg.read(id::reg::PC);

    // CONTINUE
}


/*
 * LR = (address of the instruction after this BLX) | 1
 * T Flag = Rm[0]
 * PC = Rm[31:1] << 1
 */
void instructions::thumb::branching::BLX2(const thumb_code_t &code, REGISTERS &reg) {
    u8 Rm_bits = reg.fetch_reg_id(code, 3, 5);
    const bool H2 = code.test(6);

    Rm_bits += (8 * H2);

    const id::reg Rm_id = reg.fetch_reg_id(Rm_bits);

    //reg.write(id::reg::LR)
    // CONTINUE
}


/*
 * T Flag = Rm[0]
 * PC = Rm[31:1] << 1
 */
void instructions::thumb::branching::BX(const thumb_code_t &code, REGISTERS &reg) {
    u8 Rm_bits = reg.fetch_reg_id(code, 3, 5);
    const bool H2 = code.test(6);

    Rm_bits += (8 * H2);

    const u32 Rm = reg.read(Rm_bits);

    reg.write_cpsr(id::cpsr::T, (Rm & 1));
    reg.write(id::reg::PC, ((Rm & 0xFFFFFFFE) << 1));
}
