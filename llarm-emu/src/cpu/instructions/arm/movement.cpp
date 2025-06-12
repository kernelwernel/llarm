#include "../../core/registers.hpp"
#include "../instructions.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"

/**
 * if ConditionPassed(cond) then
 *   Rd = shifter_operand
 *   if S == 1 and Rd == R15 then
 *     CPSR = SPSR
 *   else if S == 1 then
 *     N Flag = Rd[31]
 *     Z Flag = if Rd == 0 then 1 else 0
 *     C Flag = shifter_carry_out
 *     V Flag = unaffected
 */
void INSTRUCTIONS::arm::movement::MOV(const arm_code_t &code) {
    const data_struct shifter_operand = address_mode.data_processing(code);
    
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);

    const bool S = code.test(20);

    reg.write(Rd_id, shifter_operand.value);

    const u32 Rd = reg.read(Rd_id);

    if ((S == 1) && (Rd_id == id::reg::R15)) {
        reg.write(id::reg::CPSR, id::reg::SPSR);
    } else {
        reg.write(id::cpsr::N, (shared::util::bit_fetch(Rd, 31)));
        reg.write(id::cpsr::Z, (Rd == 0));
        reg.write(id::cpsr::C, (shifter_operand.carry));
    }
} 


/**
 * if ConditionPassed(cond) then
 *   Rd = NOT shifter_operand
 *   if S == 1 and Rd == R15 then
 *     CPSR = SPSR
 *   else if S == 1 then
 *     N Flag = Rd[31]
 *     Z Flag = if Rd == 0 then 1 else 0
 *     C Flag = shifter_carry_out
 *     V Flag = unaffected
 */
void INSTRUCTIONS::arm::movement::MVN(const arm_code_t &code) {
    const data_struct shifter_operand = address_mode.data_processing(code);

    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);

    const bool S = code.test(20);

    reg.write(Rd_id, ~shifter_operand.value);

    const u32 Rd = reg.read(Rd_id);

    if ((S == 1) && (Rd_id == id::reg::R15)) {
        reg.write(id::reg::CPSR, id::reg::SPSR);
    } else {
        reg.write(id::cpsr::N, (shared::util::bit_fetch(Rd, 31)));
        reg.write(id::cpsr::Z, (Rd == 0));
        reg.write(id::cpsr::C, (shifter_operand.carry));
    }
}


void INSTRUCTIONS::arm::movement::MRS(const arm_code_t&) {};// TODO




/**
 * if ConditionPassed(cond) then
 *   if opcode[25] == 1
 *     operand = 8_bit_immediate Rotate_Right (rotate_imm * 2)
 *   else // opcode[25] == 0
 *     operand = Rm
 *   if R == 0 then
 *     if field_mask[0] == 1 and InAPrivilegedMode() then
 *       CPSR[7:0] = operand[7:0]
 *     if field_mask[1] == 1 and InAPrivilegedMode() then
 *       CPSR[15:8] = operand[15:8]
 *     if field_mask[2] == 1 and InAPrivilegedMode() then
 *       CPSR[23:16] = operand[23:16]
 *     if field_mask[3] == 1 then
 *       CPSR[31:24] = operand[31:24]
 *   else // R == 1
 *     if field_mask[0] == 1 and CurrentModeHasSPSR() then
 *       SPSR[7:0] = operand[7:0]
 *     if field_mask[1] == 1 and CurrentModeHasSPSR() then
 *       SPSR[15:8] = operand[15:8]
 *     if field_mask[2] == 1 and CurrentModeHasSPSR() then
 *       SPSR[23:16] = operand[23:16]
 *     if field_mask[3] == 1 and CurrentModeHasSPSR() then
 *       SPSR[31:24] = operand[31:24]
 */
void INSTRUCTIONS::arm::movement::MSR_IMM(const arm_code_t &code) {
    const bool R = code.test(22);

    const bool field_mask_c = code.test(16);
    const bool field_mask_x = code.test(17);
    const bool field_mask_s = code.test(18);
    const bool field_mask_f = code.test(19);

    u32 operand = 0;

    const u8 imm_8 = shared::util::bit_range<u8>(code, 0, 7);
    const u8 rotate_imm = shared::util::bit_range<u8>(code, 8, 11);
    operand = std::rotr(imm_8, (rotate_imm * 2)); 

    if (R == false) {
        const bool is_privileged = reg.is_privileged();

        u32 new_CPSR = reg.read(id::reg::CPSR);

        if (field_mask_c && is_privileged) {
            util::swap_bits(new_CPSR, 0, 7, shared::util::bit_range<u8>(operand, 0, 7));
        }

        if (field_mask_x && is_privileged) {
            util::swap_bits(new_CPSR, 8, 15, shared::util::bit_range<u8>(operand, 8, 15));
        }

        if (field_mask_s && is_privileged) {
            util::swap_bits(new_CPSR, 16, 23, shared::util::bit_range<u8>(operand, 16, 23));
        }

        if (field_mask_f) {
            util::swap_bits(new_CPSR, 24, 31, shared::util::bit_range<u8>(operand, 24, 31));
        }

        reg.write(id::reg::CPSR, new_CPSR);
    } else {
        const bool has_SPSR = reg.current_mode_has_SPSR();

        if (has_SPSR) {
            u32 new_SPSR = reg.read(id::reg::SPSR);
            
            if (field_mask_c) {
                util::swap_bits(new_SPSR, 0, 7, shared::util::bit_range<u8>(operand, 0, 7));
            }

            if (field_mask_x) {
                util::swap_bits(new_SPSR, 8, 15, shared::util::bit_range<u8>(operand, 8, 15));
            }

            if (field_mask_s) {
                util::swap_bits(new_SPSR, 16, 23, shared::util::bit_range<u8>(operand, 16, 23));
            }

            if (field_mask_f) {
                util::swap_bits(new_SPSR, 24, 31, shared::util::bit_range<u8>(operand, 24, 31));
            }

            reg.write(id::reg::SPSR, new_SPSR);
        }
    }
};


/**
 * if ConditionPassed(cond) then
 *   if opcode[25] == 1
 *     operand = 8_bit_immediate Rotate_Right (rotate_imm * 2)
 *   else // opcode[25] == 0
 *     operand = Rm
 *   if R == 0 then
 *     if field_mask[0] == 1 and InAPrivilegedMode() then
 *       CPSR[7:0] = operand[7:0]
 *     if field_mask[1] == 1 and InAPrivilegedMode() then
 *       CPSR[15:8] = operand[15:8]
 *     if field_mask[2] == 1 and InAPrivilegedMode() then
 *       CPSR[23:16] = operand[23:16]
 *     if field_mask[3] == 1 then
 *       CPSR[31:24] = operand[31:24]
 *   else // R == 1
 *     if field_mask[0] == 1 and CurrentModeHasSPSR() then
 *       SPSR[7:0] = operand[7:0]
 *     if field_mask[1] == 1 and CurrentModeHasSPSR() then
 *       SPSR[15:8] = operand[15:8]
 *     if field_mask[2] == 1 and CurrentModeHasSPSR() then
 *       SPSR[23:16] = operand[23:16]
 *     if field_mask[3] == 1 and CurrentModeHasSPSR() then
 *       SPSR[31:24] = operand[31:24]
 */
void INSTRUCTIONS::arm::movement::MSR_REG(const arm_code_t &code) {
    const bool R = code.test(22);

    const bool field_mask_c = code.test(16);
    const bool field_mask_x = code.test(17);
    const bool field_mask_s = code.test(18);
    const bool field_mask_f = code.test(19);

    u32 operand = 0;

    const u32 Rm = reg.read(code, 0, 3);
    operand = Rm;

    if (R == false) {
        const bool is_privileged = reg.is_privileged();

        u32 new_CPSR = reg.read(id::reg::CPSR);

        if (field_mask_c && is_privileged) {
            util::swap_bits(new_CPSR, 0, 7, shared::util::bit_range<u8>(operand, 0, 7));
        }

        if (field_mask_x && is_privileged) {
            util::swap_bits(new_CPSR, 8, 15, shared::util::bit_range<u8>(operand, 8, 15));
        }

        if (field_mask_s && is_privileged) {
            util::swap_bits(new_CPSR, 16, 23, shared::util::bit_range<u8>(operand, 16, 23));
        }

        if (field_mask_f) {
            util::swap_bits(new_CPSR, 24, 31, shared::util::bit_range<u8>(operand, 24, 31));
        }

        reg.write(id::reg::CPSR, new_CPSR);
    } else {
        const bool has_SPSR = reg.current_mode_has_SPSR();

        if (has_SPSR) {
            u32 new_SPSR = reg.read(id::reg::SPSR);
            
            if (field_mask_c) {
                util::swap_bits(new_SPSR, 0, 7, shared::util::bit_range<u8>(operand, 0, 7));
            }

            if (field_mask_x) {
                util::swap_bits(new_SPSR, 8, 15, shared::util::bit_range<u8>(operand, 8, 15));
            }

            if (field_mask_s) {
                util::swap_bits(new_SPSR, 16, 23, shared::util::bit_range<u8>(operand, 16, 23));
            }

            if (field_mask_f) {
                util::swap_bits(new_SPSR, 24, 31, shared::util::bit_range<u8>(operand, 24, 31));
            }

            reg.write(id::reg::SPSR, new_SPSR);
        }
    }
};