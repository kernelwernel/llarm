#include "addressing_modes.hpp"

#include "shared/util.hpp"
#include "shared/out.hpp"

u32 ADDRESSING_MODE::load_store_misc(const u32 code) {
    using namespace shared::util;

    if (
        (bit_fetch(code, 27) != false) || 
        (bit_fetch(code, 26) != false) ||
        (bit_fetch(code, 25) != false) ||
        (bit_fetch(code, 7) != true) ||
        (bit_fetch(code, 4) != true)
    ) {
        shared::out::error("TODO");
    }
    
    const u8 shift_type = ((bit_fetch(code, 24) << 2) | (bit_fetch(code, 22) << 1) | bit_fetch(code, 21));

    switch (shift_type) {
        case 0b110: return ls_misc_imm(code);
        case 0b100: return ls_misc_reg(code);
        case 0b111: return ls_misc_imm_pre(code);
        case 0b101: return ls_misc_reg_pre(code);
        case 0b010: return ls_misc_imm_post(code);
        case 0b000: return ls_misc_reg_post(code);
    }

    shared::out::error("TODO");
}


/**
 * offset_8 = (immedH << 4) OR immedL
 * if U == 1 then
 *     address = Rn + offset_8
 * else // U == 0
 *     address = Rn - offset_8
 */
u32 ADDRESSING_MODE::ls_misc_imm(const u32 code) {
    const u8 immedH = shared::util::bit_range<u8>(code, 8, 11);
    const u8 immedL = shared::util::bit_range<u8>(code, 0, 3);

    const u8 offset_8 = (immedH << 4) | immedL;

    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);

    if (shared::util::bit_fetch(code, 23)) {
        return (reg.read(Rn_id) + offset_8);
    } else {
        return (reg.read(Rn_id) - offset_8);
    }
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

    if (shared::util::bit_fetch(code, 23)) {
        return Rn + Rm;
    } else {
        return Rn - Rm;
    }
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
    const u8 immedH = shared::util::bit_range<u8>(code, 8, 11);
    const u8 immedL = shared::util::bit_range<u8>(code, 0, 3);

    const u8 offset_8 = (immedH << 4) | immedL;

    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);

    u32 address = 0;

    if (shared::util::bit_fetch(code, 23)) {
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

    if (shared::util::bit_fetch(code, 23)) {
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
        const u8 immedH = shared::util::bit_range<u8>(code, 8, 11);
        const u8 immedL = shared::util::bit_range<u8>(code, 0, 3);
        
        const u8 offset_8 = (immedH << 4) | immedL;

        if (shared::util::bit_fetch(code, 23)) {
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

        if (shared::util::bit_fetch(code, 23)) {
            reg.write(Rn_id, (Rn + Rm));
        } else {
            reg.write(Rn_id, (Rn - Rm));
        }
    }

    return address;
}