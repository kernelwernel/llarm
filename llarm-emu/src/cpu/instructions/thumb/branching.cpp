#include "../../instructions/instructions.hpp"
#include "../../core/registers.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>

/*
 * if ConditionPassed(cond) then
 *   PC = PC + (SignExtend(signed_immed_8) << 1)
 */
void INSTRUCTIONS::thumb::branching::B1(const u16 code) {
    const u8 signed_immed_8 = llarm::util::bit_range<u8>(code, 0, 7);

    const id::cond cond = reg.fetch_cond_id(llarm::util::bit_range<u8>(code, 8, 11));

    if (reg.is_cond_valid(cond)) {
        reg.write(id::reg::PC, (reg.read(id::reg::PC) + u32(operation.sign_extend(signed_immed_8, 7) << 1)));
    }
}


/*
 * PC = PC + (SignExtend(signed_immed_11) << 1)
 */
void INSTRUCTIONS::thumb::branching::B2(const u16 code) {
    const u16 signed_immed_10 = llarm::util::bit_range<u16>(code, 0, 10);

    reg.write(id::reg::PC, reg.read(id::reg::PC) + u32((signed_immed_10) << 1));
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
void INSTRUCTIONS::thumb::branching::BL(const u16 code) {
    const u16 offset_11 = llarm::util::bit_range<u16>(code, 0, 10);
    const u8 H = llarm::util::bit_range<u8>(code, 11, 12);

    const u32 next_instruction_address = reg.read(id::reg::PC) + 2;

    if (H == 0b10) {
        reg.write(id::reg::LR, (reg.read(id::reg::PC) + u32(operation.sign_extend(offset_11, 10) << 12)));
    } else if (H == 0b11) {
        reg.write(id::reg::PC, (reg.read(id::reg::LR) + u32(offset_11 << 1)));
        reg.write(id::reg::LR, ((next_instruction_address + 2) | 1));
    } else if (H == 0b01) {
        reg.write(id::reg::PC, ((reg.read(id::reg::LR) + u32(offset_11 << 1)) & 0xFFFFFFFC));
        reg.write(id::reg::LR, (next_instruction_address | 1));
        reg.write(id::cpsr::T, false);
    }
}


/*
 * LR = PC + (SignExtend(offset_11) << 12)
 *
 * NOTE: this is not a real instruction. It's more as a functional layer
 *       to make the whole BL/BLX1 instruction work since they're divided
 *       into 2 u16 operations instead of a single one. This manages the
 *       first halfword of the operation.
 */
void INSTRUCTIONS::thumb::branching::BL_BLX1_PREFIX(const u16 code) {
    const u16 offset_11 = llarm::util::bit_range<u16>(code, 0, 10);

    reg.write(id::reg::LR, (reg.read(id::reg::PC) + u32(operation.sign_extend(offset_11, 10) << 12)));
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
void INSTRUCTIONS::thumb::branching::BLX1(const u16 code) {
    const u16 offset_11 = llarm::util::bit_range<u16>(code, 0, 10);
    const u8 H = llarm::util::bit_range<u8>(code, 11, 12);

    const u32 next_instruction_address = reg.read(id::reg::PC) + 2;

    if (H == 0b10) {
        reg.write(id::reg::LR, (reg.read(id::reg::PC) + u32(operation.sign_extend(offset_11, 10) << 12)));
    } else if (H == 0b11) {
        reg.write(id::reg::PC, (reg.read(id::reg::LR) + u32(offset_11 << 1)));
        reg.write(id::reg::LR, ((next_instruction_address + 2) | 1));
    } else if (H == 0b01) {
        reg.write(id::reg::PC, ((reg.read(id::reg::LR) + u32(offset_11 << 1)) & 0xFFFFFFFC));
        reg.write(id::reg::LR, (next_instruction_address | 1));
        reg.write(id::cpsr::T, false);
    }
}


/*
 * LR = (address of the instruction after this BLX) | 1
 * T Flag = Rm[0]
 * PC = Rm[31:1] << 1
 */
void INSTRUCTIONS::thumb::branching::BLX2(const u16 code) {
    const u32 Rm = reg.read(code, 3, 6);

    const u32 next_instruction_address = reg.read(id::reg::PC) + 2;

    reg.write(id::reg::LR, (next_instruction_address | 1));
    reg.write(id::cpsr::T, (Rm & 1));
    reg.write(id::reg::PC, (llarm::util::bit_range(Rm, 1, 31) << 1));
}


/*
 * T Flag = Rm[0]
 * PC = Rm[31:1] << 1
 */
void INSTRUCTIONS::thumb::branching::BX(const u16 code) {
    const u32 Rm = reg.read(code, 3, 6);

    reg.write(id::cpsr::T, (Rm & 1));
    reg.write(id::reg::PC, (llarm::util::bit_range(Rm, 1, 31) << 1));
}