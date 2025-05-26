#include "addressing_modes.hpp"

#include "shared/util.hpp"

address_struct ADDRESSING_MODE::load_store_multiple(const arm_code_t &code) {
    if (
        (code.test(27) != true) || 
        (code.test(26) != false) ||
        (code.test(25) != false)
    ) {
        shared::out::error("TODO");
    }
    
    const u8 shift_type = shared::util::bit_range<u8>(code, 23, 24);

    switch (shift_type) {
        case 0b01: return ls_mul_inc_after(code);
        case 0b11: return ls_mul_inc_before(code);
        case 0b00: return ls_mul_dec_after(code);
        case 0b10: return ls_mul_dec_before(code);
    }

    shared::out::error("TODO");
}


/**
 * start_address = Rn
 * end_address = Rn + (Number_Of_Set_Bits_In(register_list) * 4) - 4
 * if ConditionPassed(cond) and W == 1 then
 *     Rn = Rn + (Number_Of_Set_Bits_In(register_list) * 4)
 */
address_struct ADDRESSING_MODE::ls_mul_inc_after(const arm_code_t &code) {
    const u16 list = shared::util::bit_range<u16>(code, 0, 15);

    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);

    const u32 start_address = reg.read(Rn_id);
    const u32 end_address = ((shared::util::popcount(list) * 4) - 4);

    if (reg.check_cond(code) && code.test(21)) {
        reg.write(Rn_id, (reg.read(Rn_id) + (shared::util::popcount(list) * 4)));
    }

    return address_struct { 
        start_address, 
        end_address 
    };
}


/**
 * start_address = Rn + 4
 * end_address = Rn + (Number_Of_Set_Bits_In(register_list) * 4)
 * if ConditionPassed(cond) and W == 1 then
 *     Rn = Rn + (Number_Of_Set_Bits_In(register_list) * 4)
 */
address_struct ADDRESSING_MODE::ls_mul_inc_before(const arm_code_t &code) {
    const u16 list = shared::util::bit_range<u16>(code, 0, 15);

    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);

    const u32 start_address = reg.read(Rn_id) + 4;
    const u32 end_address = reg.read(Rn_id) + (shared::util::popcount(list) * 4);

    if (reg.check_cond(code) && code.test(21)) {
        reg.write(Rn_id, (reg.read(Rn_id) + (shared::util::popcount(list) * 4)));
    }

    return address_struct { 
        start_address, 
        end_address 
    };
}


/**
 * start_address = Rn - (Number_Of_Set_Bits_In(register_list) * 4) + 4
 * end_address = Rn
 * if ConditionPassed(cond) and W == 1 then
 *     Rn = Rn - (Number_Of_Set_Bits_In(register_list) * 4)
 */
address_struct ADDRESSING_MODE::ls_mul_dec_after(const arm_code_t &code) {
    const u16 list = shared::util::bit_range<u16>(code, 0, 15);

    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);

    const u32 start_address = reg.read(Rn_id) - ((shared::util::popcount(list) * 4) + 4);
    const u32 end_address = reg.read(Rn_id);

    if (reg.check_cond(code) && code.test(21)) {
        reg.write(Rn_id, (reg.read(Rn_id) - (shared::util::popcount(list) * 4)));
    }

    return address_struct { 
        start_address, 
        end_address 
    };
}


/**
 * start_address = Rn - (Number_Of_Set_Bits_In(register_list) * 4)
 * end_address = Rn - 4
 * if ConditionPassed(cond) and W == 1 then
 *     Rn = Rn - (Number_Of_Set_Bits_In(register_list) * 4)
 */
address_struct ADDRESSING_MODE::ls_mul_dec_before(const arm_code_t &code) {
    const u16 list = shared::util::bit_range<u16>(code, 0, 15);

    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);

    const u32 start_address = reg.read(Rn_id) - (shared::util::popcount(list) * 4);
    const u32 end_address = reg.read(Rn_id) - 4;

    if (reg.check_cond(code) && code.test(21)) {
        reg.write(Rn_id, (reg.read(Rn_id) - (shared::util::popcount(list) * 4)));
    }

    return address_struct { 
        start_address, 
        end_address 
    };
}