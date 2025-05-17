#include "addressing_modes.hpp"
#include "shared/util.hpp"

u32 ADDRESSING_MODE::load_store_misc(const arm_code_t &code) {
    if (
        (code.test(27) != false) || 
        (code.test(26) != false) ||
        (code.test(25) != false) ||
        (code.test(7) != true) ||
        (code.test(4) != true)
    ) {
        shared::out::error("TODO");
    }
    
    const u8 shift_type = ((code.test(24) << 2) | (code.test(22) << 1) | code.test(21));

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
u32 ADDRESSING_MODE::ls_misc_imm(const arm_code_t &code) {
    const u8 immedH = shared::util::bit_range<u8>(code, 8, 11);
    const u8 immedL = shared::util::bit_range<u8>(code, 0, 3);

    const u8 offset_8 = (immedH << 4) | immedL;

    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);

    if (code.test(23)) {
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
u32 ADDRESSING_MODE::ls_misc_reg(const arm_code_t &code) {
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    if (code.test(23)) {
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
u32 ADDRESSING_MODE::ls_misc_imm_pre(const arm_code_t &code) {
    const u8 immedH = shared::util::bit_range<u8>(code, 8, 11);
    const u8 immedL = shared::util::bit_range<u8>(code, 0, 3);

    const u8 offset_8 = (immedH << 4) | immedL;

    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);

    u32 address = 0;

    if (code.test(23)) {
        address = reg.read(Rn_id) + offset_8;
    } else {
        address = reg.read(Rn_id) - offset_8;
    }

    if (reg.check_cond(code)) {
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
u32 ADDRESSING_MODE::ls_misc_reg_pre(const arm_code_t &code) {
    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);

    const u32 Rn = reg.read(Rn_id);
    const u32 Rm = reg.read(code, 0, 3);

    u32 address = 0;

    if (code.test(23)) {
        address = (Rn + Rm);
    } else {
        address = (Rn - Rm);
    }

    if (reg.check_cond(code)) {
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
u32 ADDRESSING_MODE::ls_misc_imm_post(const arm_code_t &code) {
    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);

    const u32 Rn = reg.read(Rn_id);
    
    const u32 address = Rn;
    
    if (reg.check_cond(code)) {
        const u8 immedH = shared::util::bit_range<u8>(code, 8, 11);
        const u8 immedL = shared::util::bit_range<u8>(code, 0, 3);
        
        const u8 offset_8 = (immedH << 4) | immedL;

        if (code.test(23)) {
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
u32 ADDRESSING_MODE::ls_misc_reg_post(const arm_code_t &code) {
    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);

    const u32 Rn = reg.read(Rn_id);
    
    const u32 address = Rn;
    
    if (reg.check_cond(code)) {
        const u32 Rm = reg.read(code, 0, 3);

        if (code.test(23)) {
            reg.write(Rn_id, (Rn + Rm));
        } else {
            reg.write(Rn_id, (Rn - Rm));
        }
    }

    return address;
}