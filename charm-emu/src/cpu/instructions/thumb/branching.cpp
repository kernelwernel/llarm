#include "shared/types.hpp"
#include "../../../utility.hpp"
#include "../../instructions/instructions.hpp"
#include "../../core/registers.hpp"


/*
 * if ConditionPassed(cond) then
 *   PC = PC + (SignExtend(signed_immed_8) << 1)
 */
void INSTRUCTIONS::thumb::branching::B1(const thumb_code_t &code) {
    const i8 signed_immed_8 = util::bit_fetcher<i8>(code, 0, 7);

    const id::cond cond = reg.fetch_cond_id(util::bit_fetcher<u8>(code, 8, 11));

    std::cout << "B1 PC before: 0x" << std::hex << reg.read(id::reg::PC) << std::dec << "\n";

    if (reg.check_cond(cond)) {
        //reg.write(id::reg::PC, (reg.read(id::reg::PC) + (operation.sign_extend<u8>(signed_immed_8) << 1)));
        reg.write(id::reg::PC, (reg.read(id::reg::PC) + (signed_immed_8 << 1) + 4));
    }

    std::cout << "B1 PC after: 0x" << std::hex << reg.read(id::reg::PC) << std::dec << "\n";

    reg.thumb_increment_PC();
}


/*
 * PC = PC + (SignExtend(signed_immed_11) << 1)
 */
void INSTRUCTIONS::thumb::branching::B2(const thumb_code_t &code) {
    const i16 signed_immed_10 = util::bit_fetcher<i16>(code, 0, 10);

    std::cout << "before: " << reg.read(id::reg::PC) << "\n";

    reg.write(id::reg::PC, (reg.read(id::reg::PC) + ((static_cast<i32>(signed_immed_10)) << 1)));

    reg.thumb_increment_PC();

    std::cout << "after: " << reg.read(id::reg::PC) << "\n";
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
void INSTRUCTIONS::thumb::branching::BL(const thumb_code_t &code) {
    std::cout << "\n\n\n\nbefore: " << reg.read(id::reg::PC) << "\n\n\n";

    const u16 offset_11 = util::bit_fetcher<u16>(code, 0, 10);
    const u8 H = util::bit_fetcher<u8>(code, 11, 12);

    const u32 next_instruction_address = reg.read(id::reg::PC) + 2;

    if (H == 0b10) {
        reg.write(id::reg::LR, (reg.read(id::reg::PC) + (operation.sign_extend(offset_11) << 12)));
    } else if (H == 0b11) {
        reg.write(id::reg::PC, (reg.read(id::reg::LR) + (offset_11 << 1)));
        reg.write(id::reg::LR, ((next_instruction_address + 2) | 1));
    } else if (H == 0b01) {
        reg.write(id::reg::PC, ((reg.read(id::reg::LR) + (offset_11 << 1)) & 0xFFFFFFFC));
        reg.write(id::reg::LR, (next_instruction_address | 1));
        reg.write(id::cpsr::T, false);
    }

    reg.thumb_increment_PC();
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
void INSTRUCTIONS::thumb::branching::BLX1(const thumb_code_t &code) {
    const u16 offset_11 = util::bit_fetcher<u16>(code, 0, 10);
    const u8 H = util::bit_fetcher<u8>(code, 11, 12);

    const u32 next_instruction_address = reg.read(id::reg::PC) + 2;

    if (H == 0b10) {
        reg.write(id::reg::LR, (reg.read(id::reg::PC) + (operation.sign_extend(offset_11) << 12)));
    } else if (H == 0b11) {
        reg.write(id::reg::PC, (reg.read(id::reg::LR) + (offset_11 << 1)));
        reg.write(id::reg::LR, ((next_instruction_address + 2) | 1));
    } else if (H == 0b01) { // TODO: v5 specific
        reg.write(id::reg::PC, ((reg.read(id::reg::LR) + (offset_11 << 1)) & 0xFFFFFFFC));
        reg.write(id::reg::LR, (next_instruction_address | 1));
        reg.write(id::cpsr::T, false);
    }

    reg.thumb_increment_PC();
}


/*
 * LR = (address of the instruction after this BLX) | 1
 * T Flag = Rm[0]
 * PC = Rm[31:1] << 1
 */
void INSTRUCTIONS::thumb::branching::BLX2(const thumb_code_t &code) {
    const u32 Rm = reg.read(code, 3, 6);

    const u32 next_instruction_address = reg.read(id::reg::PC) + 2;

    reg.write(id::reg::LR, (next_instruction_address | 1));
    reg.write(id::cpsr::T, (Rm & 1));
    reg.write(id::reg::PC, (util::bit_fetcher(Rm, 1, 31) << 1));

    reg.thumb_increment_PC();
}


/*
 * T Flag = Rm[0]
 * PC = Rm[31:1] << 1
 */
void INSTRUCTIONS::thumb::branching::BX(const thumb_code_t &code) {
    const u32 Rm = reg.read(code, 3, 6);

    reg.write(id::cpsr::T, (Rm & 1));
    reg.write(id::reg::PC, (util::bit_fetcher(Rm, 1, 31) << 1));

    reg.thumb_increment_PC();
}
