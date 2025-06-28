#include "addressing_modes.hpp"

#include "shared/util.hpp"
#include "shared/out.hpp"

address_struct ADDRESSING_MODE::load_store_multiple(const u32 code) {
    using namespace shared::util;

    if (
        (bit_fetch(code, 27) != true) || 
        (bit_fetch(code, 26) != false) ||
        (bit_fetch(code, 25) != false)
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
address_struct ADDRESSING_MODE::ls_mul_inc_after(const u32 code) {
    const u16 list = shared::util::bit_range<u16>(code, 0, 15);

    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);

    const u32 start_address = reg.read(Rn_id);
    const u32 end_address = ((shared::util::popcount(list) * 4) - 4);

    if (reg.is_cond_valid(code) && shared::util::bit_fetch(code, 21)) {
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
address_struct ADDRESSING_MODE::ls_mul_inc_before(const u32 code) {
    const u16 list = shared::util::bit_range<u16>(code, 0, 15);

    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);

    const u32 start_address = reg.read(Rn_id) + 4;
    const u32 end_address = reg.read(Rn_id) + (shared::util::popcount(list) * 4);

    if (reg.is_cond_valid(code) && shared::util::bit_fetch(code, 21)) {
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
address_struct ADDRESSING_MODE::ls_mul_dec_after(const u32 code) {
    const u16 list = shared::util::bit_range<u16>(code, 0, 15);

    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);

    const u32 start_address = reg.read(Rn_id) - ((shared::util::popcount(list) * 4) + 4);
    const u32 end_address = reg.read(Rn_id);

    if (reg.is_cond_valid(code) && shared::util::bit_fetch(code, 21)) {
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
address_struct ADDRESSING_MODE::ls_mul_dec_before(const u32 code) {
    const u16 list = shared::util::bit_range<u16>(code, 0, 15);

    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);

    const u32 start_address = reg.read(Rn_id) - (shared::util::popcount(list) * 4);
    const u32 end_address = reg.read(Rn_id) - 4;

    if (reg.is_cond_valid(code) && shared::util::bit_fetch(code, 21)) {
        reg.write(Rn_id, (reg.read(Rn_id) - (shared::util::popcount(list) * 4)));
    }

    return address_struct { 
        start_address, 
        end_address 
    };
}