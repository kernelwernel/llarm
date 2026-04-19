#include "addressing_modes.hpp"

#include <llarm/shared/util.hpp>
#include <llarm/shared/out.hpp>

#include <llarm/llarm-asm.hpp>

u32 ADDRESSING_MODE::load_store_misc(const u32 code) {
    using namespace llarm::as;

    const shifter_id shifter_id = llarm::as::identify_shifter(shifter_category::LS_MISC, code);

    switch (shifter_id) {
        case shifter_id::LS_MISC_IMM: return ls_misc_imm(code);
        case shifter_id::LS_MISC_REG: return ls_misc_reg(code);
        case shifter_id::LS_MISC_IMM_PRE: return ls_misc_imm_pre(code);
        case shifter_id::LS_MISC_IMM_POST: return ls_misc_imm_post(code);
        case shifter_id::LS_MISC_REG_PRE: return ls_misc_reg_pre(code);
        case shifter_id::LS_MISC_REG_POST: return ls_misc_reg_post(code);
        default: llarm::out::error("Impossible identification of ARM load store misc shifter");
    }
}


/**
 * offset_8 = (immedH << 4) OR immedL
 * if U == 1 then
 *     address = Rn + offset_8
 * else // U == 0
 *     address = Rn - offset_8
 */
u32 ADDRESSING_MODE::ls_misc_imm(const u32 code) {
    const u8 immedH = llarm::util::bit_range<u8>(code, 8, 11);
    const u8 immedL = llarm::util::bit_range<u8>(code, 0, 3);

    const u8 offset_8 = static_cast<u8>((immedH << 4) | immedL);

    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);

    if (llarm::util::bit_fetch(code, 23)) {
        return (reg.read(Rn_id) + offset_8);
    }

    return (reg.read(Rn_id) - offset_8);
}


/**
 * if U == 1 then
 *     address = Rn + Rm
 * else // U == 0
 *     address = Rn - Rm
 */
u32 ADDRESSING_MODE::ls_misc_reg(const u32 code) {
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    if (llarm::util::bit_fetch(code, 23)) {
        return Rn + Rm;
    }
    
    return Rn - Rm;
}


/**
 * offset_8 = (immedH << 4) OR immedL
 * if U == 1 then
 *     address = Rn + offset_8
 * else // U == 0
 *     address = Rn - offset_8
 * if ConditionPassed(cond) then
 *     Rn = address
 */
u32 ADDRESSING_MODE::ls_misc_imm_pre(const u32 code) {
    const u8 immedH = llarm::util::bit_range<u8>(code, 8, 11);
    const u8 immedL = llarm::util::bit_range<u8>(code, 0, 3);

    const u8 offset_8 = static_cast<u8>((immedH << 4) | immedL);

    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);

    u32 address = 0;

    if (llarm::util::bit_fetch(code, 23)) {
        address = reg.read(Rn_id) + offset_8;
    } else {
        address = reg.read(Rn_id) - offset_8;
    }

    if (reg.is_cond_valid(code)) {
        reg.write(Rn_id, address);
    }

    return address;
}


/**
 * if U == 1 then
 *     address = Rn + Rm
 * else // U == 0
 *     address = Rn - Rm
 * if ConditionPassed(cond) then
 *     Rn = address
 */
u32 ADDRESSING_MODE::ls_misc_reg_pre(const u32 code) {
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
 * address = Rn
 * offset_8 = (immedH << 4) OR immedL
 * if ConditionPassed(cond) then
 *     if U == 1 then
 *         Rn = Rn + offset_8
 *     else // U == 0
 *         Rn = Rn - offset_8
 */
u32 ADDRESSING_MODE::ls_misc_imm_post(const u32 code) {
    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);

    const u32 Rn = reg.read(Rn_id);
    
    const u32 address = Rn;
    
    if (reg.is_cond_valid(code)) {
        const u8 immedH = llarm::util::bit_range<u8>(code, 8, 11);
        const u8 immedL = llarm::util::bit_range<u8>(code, 0, 3);
        
        const u8 offset_8 = static_cast<u8>((immedH << 4) | immedL);

        if (llarm::util::bit_fetch(code, 23)) {
            reg.write(Rn_id, (Rn + offset_8));
        } else {
            reg.write(Rn_id, (Rn - offset_8));
        }
    }

    return address;
}


/**
 * address = Rn
 * if ConditionPassed(cond) then
 *     if U == 1 then
 *         Rn = Rn + Rm
 *     else // U == 0
 *         Rn = Rn - Rm
 */
u32 ADDRESSING_MODE::ls_misc_reg_post(const u32 code) {
    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);

    const u32 Rn = reg.read(Rn_id);
    
    const u32 address = Rn;
    
    if (reg.is_cond_valid(code)) {
        const u32 Rm = reg.read(code, 0, 3);

        if (llarm::util::bit_fetch(code, 23)) {
            reg.write(Rn_id, (Rn + Rm));
        } else {
            reg.write(Rn_id, (Rn - Rm));
        }
    }

    return address;
}