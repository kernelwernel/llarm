#include "../../../../id.hpp"

#include "addressing_modes.hpp"

#include "llarm-asm/llarm-asm.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"
#include "shared/out.hpp"

u32 ADDRESSING_MODE::load_store(const u32 code) {
    using namespace llarm::util;

    const shifter_enum shifter_id = llarm::as::identify::shifter(shift_category::LS, code);

    switch (shifter_id) {
        case shifter_enum::LS_IMM: return ls_imm(code);
        case shifter_enum::LS_IMM_PRE: return ls_imm_pre(code);
        case shifter_enum::LS_IMM_POST: return ls_imm_post(code);
        case shifter_enum::LS_REG: return ls_reg(code); 
        case shifter_enum::LS_REG_PRE: return ls_reg_pre(code); 
        case shifter_enum::LS_REG_POST: return ls_reg_post(code); 
        case shifter_enum::LS_SCALED_LSL:
        case shifter_enum::LS_SCALED_LSR:
        case shifter_enum::LS_SCALED_ASR:
        case shifter_enum::LS_SCALED_ROR:
        case shifter_enum::LS_SCALED_RRX: return ls_scaled_reg(code);
        case shifter_enum::LS_SCALED_PRE_LSL:
        case shifter_enum::LS_SCALED_PRE_LSR:
        case shifter_enum::LS_SCALED_PRE_ASR:
        case shifter_enum::LS_SCALED_PRE_ROR:
        case shifter_enum::LS_SCALED_PRE_RRX: return ls_scaled_reg_pre(code);
        case shifter_enum::LS_SCALED_POST_LSL:
        case shifter_enum::LS_SCALED_POST_LSR:
        case shifter_enum::LS_SCALED_POST_ASR:
        case shifter_enum::LS_SCALED_POST_ROR:
        case shifter_enum::LS_SCALED_POST_RRX: return ls_scaled_reg_post(code);
        default: llarm::out::error("Impossible identification of ARM load store shifter");
    }
}


/**
 * if U == 1 then
 *     address = Rn + offset_12
 * else // U == 0
 *     address = Rn - offset_12
 */
u32 ADDRESSING_MODE::ls_imm(const u32 code) {
    const u32 Rn = reg.read(code, 16, 19);
    const u16 offset_12 = llarm::util::bit_range(code, 0, 11);
    
    if (llarm::util::bit_fetch(code, 23)) {
        return (Rn + offset_12);
    } else {
        return (Rn - offset_12);
    }
}


/**
 * if U == 1 then
 *     address = Rn + Rm
 * else // U == 0
 *     address = Rn - Rm
 */
u32 ADDRESSING_MODE::ls_reg(const u32 code) {
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    if (llarm::util::bit_fetch(code, 23)) {
        return (Rn + Rm);
    } else {
        return (Rn - Rm);
    }
}


/**
 * case shift of
 *   0b00 // LSL
 *     index = Rm Logical_Shift_Left shift_imm
 *   0b01 // LSR
 *     if shift_imm == 0 then // LSR #32
 *       index = 0
 *     else
 *       index = Rm Logical_Shift_Right shift_imm
 *   0b10 // ASR
 *     if shift_imm == 0 then // ASR #32
 *       if Rm[31] == 1 then
 *         index = 0xFFFFFFFF
 *       else
 *         index = 0
 *     else
 *       index = Rm Arithmetic_Shift_Right shift_imm
 *   0b11 // ROR or RRX
 *     if shift_imm == 0 then // RRX
 *       index = (C Flag Logical_Shift_Left 31) OR 
 *               (Rm Logical_Shift_Right 1)
 *     else // ROR
 *       index = Rm Rotate_Right shift_imm
 * endcase
 * 
 * if U == 1 then
 *   address = Rn + index
 * else // U == 0
 *   address = Rn - index
 */
u32 ADDRESSING_MODE::ls_scaled_reg(const u32 code) {
    const u8 shift = llarm::util::bit_range(code, 5, 6);
    const u8 shift_imm = llarm::util::bit_range(code, 7, 11);
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rn = reg.read(code, 16, 19);

    u32 index = 0;
    u32 address = 0;

    switch (shift) {
        case 0b00: // LSL
            index = (Rm << shift_imm);
            break;

        case 0b01: // LSR
            if (shift_imm == 0) {
                index = 0;
            } else {
                index = (Rm >> shift_imm);
            }
            break;

        case 0b10: // ASR
            if (shift_imm == 0) {
                if (llarm::util::bit_fetch(Rm, 31) == 1) {
                    index = 0xFFFFFFFF;
                } else {
                    index = 0;
                }
            } else {
                index = operation.arithmetic_shift_right(Rm, shift_imm);
            }
            break;

        case 0b11: // ROR or RRX
            if (shift_imm == 0) { // RRX
                index = ((reg.read(id::cpsr::C) << 31) | (Rm >> 1));
            } else { // ROR
                index = std::rotr(Rm, shift_imm);
            }
            break;
    }

    if (llarm::util::bit_fetch(code, 23)) {
        address = (Rn + index);
    } else {
        address = (Rn - index);
    }

    return address;
}


/**
 * if U == 1 then
 *   address = Rn + offset_12
 * else // if U == 0
 *   address = Rn - offset_12
 * if ConditionPassed(cond) then
 *   Rn = address
 */
u32 ADDRESSING_MODE::ls_imm_pre(const u32 code) {
    const u16 offset_12 = llarm::util::bit_range(code, 0, 11);

    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);
    const u32 Rn = reg.read(Rn_id);

    u32 address = 0;

    if (llarm::util::bit_fetch(code, 23)) {
        address = (Rn + offset_12);
    } else {
        address = (Rn - offset_12);
    }

    if (reg.is_cond_valid(code)) {
        reg.write(Rn_id, address);
    }

    return address;
}


/**
 * ===== register pre-indexed =====
 * 
 * if U == 1 then
 *   address = Rn + Rm
 * else // U == 0
 *   address = Rn - Rm
 * if ConditionPassed(cond) then
 *   Rn = address
 */
u32 ADDRESSING_MODE::ls_reg_pre(const u32 code) {
    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);
    const u32 Rn = reg.read(Rn_id);
    const u32 Rm = reg.read(code, 0, 3);
    
    u32 address = 0;

    if (llarm::util::bit_fetch(code, 23)) {
        address = (Rn + Rm);
    } else {
        address = (Rn - Rm);
    }

    if (reg.is_cond_valid(code)) {
        reg.write(Rn_id, address);
    }

    return address;
}


/**
 * ===== scaled register pre-indexed =====
 * 
 * case shift of
 *   0b00 // LSL
 *     index = Rm Logical_Shift_Left shift_imm
 *   0b01 // LSR
 *     if shift_imm == 0 then // LSR #32
 *       index = 0
 *     else
 *       index = Rm Logical_Shift_Right shift_imm
 *   0b10 // ASR
 *     if shift_imm == 0 then // ASR #32 
 *       if Rm[31] == 1 then
 *         index = 0xFFFFFFFF
 *       else
 *         index = 0
 *     else
 *       index = Rm Arithmetic_Shift_Right shift_imm
 *   0b11 // ROR or RRX
 *     if shift_imm == 0 then // RRX
 *       index = (C Flag Logical_Shift_Left 31) OR
 *               (Rm Logical_Shift_Right 1)
 *     else // ROR
 *       index = Rm Rotate_Right shift_imm
 * endcase
 * 
 * if U == 1 then
 *   address = Rn + index
 * else // U == 0
 *   address = Rn - index
 * if ConditionPassed(cond) then
 *   Rn = address
 */
u32 ADDRESSING_MODE::ls_scaled_reg_pre(const u32 code) {
    const u8 shift = llarm::util::bit_range(code, 5, 6);
    const u8 shift_imm = llarm::util::bit_range(code, 7, 11);
    const u32 Rm = reg.read(code, 0, 3);
    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);
    const u32 Rn = reg.read(Rn_id);
    
    u32 index = 0;
    u32 address = 0;

    switch (shift) {
        case 0b00: // LSL
            index = (Rm << shift_imm);
            break;

        case 0b01: // LSR
            if (shift_imm == 0) {
                index = 0;
            } else {
                index = (Rm >> shift_imm);
            }
            break;

        case 0b10: // ASR
            if (shift_imm == 0) {
                if (llarm::util::bit_fetch(Rm, 31) == 1) {
                    index = 0xFFFFFFFF;
                } else {
                    index = 0;
                }
            } else {
                index = operation.arithmetic_shift_right(Rm, shift_imm);
            }
            break;

        case 0b11: // ROR or RRX
            if (shift_imm == 0) { // RRX
                index = ((reg.read(id::cpsr::C) << 31) | (Rm >> 1));
            } else { // ROR
                index = std::rotr(Rm, shift_imm);
            }
            break;
    }

    if (llarm::util::bit_fetch(code, 23)) {
        address = (Rn + index);
    } else {
        address = (Rn - index);
    }

    if (reg.is_cond_valid(code)) {
        reg.write(Rn_id, address);
    }

    return address;
}


/**
 * address = Rn
 * if ConditionPassed(cond) then
 *   if U == 1 then
 *     Rn = Rn + offset_12
 *   else // U == 0
 *     Rn = Rn - offset_12
 */
u32 ADDRESSING_MODE::ls_imm_post(const u32 code) {
    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);
    const u16 offset_12 = llarm::util::bit_range(code, 0, 11);
    const u32 Rn = reg.read(Rn_id);

    const u32 address = Rn;

    if (reg.is_cond_valid(code)) {
        if (llarm::util::bit_fetch(code, 23)) {
            reg.write(Rn_id, (Rn + offset_12));
        } else {
            reg.write(Rn_id, (Rn - offset_12));
        }
    }

    return address;
}


/**
 * address = Rn
 * if ConditionPassed(cond) then
 *   if U == 1 then
 *     Rn = Rn + Rm
 *   else // U == 0
 *     Rn = Rn - Rm
 */
u32 ADDRESSING_MODE::ls_reg_post(const u32 code) {
    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);
    const u32 Rn = reg.read(Rn_id);
    const u32 Rm = reg.read(code, 0, 3);

    const u32 address = Rn;

    if (reg.is_cond_valid(code)) {
        if (llarm::util::bit_fetch(code, 23)) {
            reg.write(Rn_id, (Rn + Rm));
        } else {
            reg.write(Rn_id, (Rn - Rm));
        }
    }

    return address;
}


/**
 * ===== scaled register post-indexed =====
 * 
 * address = Rn
 * case shift of
 *   0b00 // LSL
 *     index = Rm Logical_Shift_Left shift_imm
 *   0b01 // LSR
 *     if shift_imm == 0 then // LSR #32
 *       index = 0
 *     else
 *       index = Rm Logical_Shift_Right shift_imm
 *   0b10 // ASR
 *     if shift_imm == 0 then // ASR #32 
 *       if Rm[31] == 1 then
 *         index = 0xFFFFFFFF
 *       else
 *         index = 0
 *     else
 *       index = Rm Arithmetic_Shift_Right shift_imm
 *   0b11 // ROR or RRX
 *     if shift_imm == 0 then // RRX
 *       index = (C Flag Logical_Shift_Left 31) OR
 *               (Rm Logical_Shift_Right 1)
 *     else // ROR
 *       index = Rm Rotate_Right shift_imm
 * endcase
 * 
 * if ConditionPassed(cond) then
 *   if U == 1 then
 *     Rn = Rn + index
 *   else // U == 0
 *     Rn = Rn - index
 */
u32 ADDRESSING_MODE::ls_scaled_reg_post(const u32 code) {
    const u8 shift = llarm::util::bit_range(code, 5, 6);
    const u8 shift_imm = llarm::util::bit_range(code, 7, 11);
    const u32 Rm = reg.read(code, 0, 3);
    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);
    const u32 Rn = reg.read(Rn_id);

    u32 index = 0;
    u32 address = Rn;

    switch (shift) {
        case 0b00: // LSL
            index = (Rm << shift_imm);
            break;

        case 0b01: // LSR
            if (shift_imm == 0) {
                index = 0;
            } else {
                index = (Rm >> shift_imm);
            }
            break;

        case 0b10: // ASR
            if (shift_imm == 0) {
                if (llarm::util::bit_fetch(Rm, 31) == 1) {
                    index = 0xFFFFFFFF;
                } else {
                    index = 0;
                }
            } else {
                index = operation.arithmetic_shift_right(Rm, shift_imm);
            }
            break;

        case 0b11: // ROR or RRX
            if (shift_imm == 0) { // RRX
                index = ((reg.read(id::cpsr::C) << 31) | (Rm >> 1));
            } else { // ROR
                index = std::rotr(Rm, shift_imm);
            }
            break;
    }

    if (reg.is_cond_valid(code)) {
        if (llarm::util::bit_fetch(code, 23)) {
            reg.write(Rn_id, Rn + index);
        } else {
            reg.write(Rn_id, Rn - index);
        }
    }

    return address;
}