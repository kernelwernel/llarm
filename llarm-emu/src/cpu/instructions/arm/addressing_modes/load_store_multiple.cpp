#include "addressing_modes.hpp"

#include <llarm/shared/util.hpp>
#include <llarm/shared/out.hpp>

#include <llarm/llarm-asm.hpp>

address_struct ADDRESSING_MODE::load_store_multiple(const u32 code) {
    using namespace llarm::as;

    const shifter_id shifter_id = identify_shifter(shifter_category::LS_MUL, code);

    switch (shifter_id) {
        case shifter_id::LS_MUL_INC_AFTER: return ls_mul_inc_after(code);
        case shifter_id::LS_MUL_INC_BEFORE: return ls_mul_inc_before(code);
        case shifter_id::LS_MUL_DEC_AFTER: return ls_mul_dec_after(code);
        case shifter_id::LS_MUL_DEC_BEFORE: return ls_mul_dec_before(code);
        default: llarm::out::error("Impossible identification of ARM load store multiple shifter");
    }
}


/**
 * start_address = Rn
 * end_address = Rn + (Number_Of_Set_Bits_In(register_list) * 4) - 4
 * if ConditionPassed(cond) and W == 1 then
 *     Rn = Rn + (Number_Of_Set_Bits_In(register_list) * 4)
 */
address_struct ADDRESSING_MODE::ls_mul_inc_after(const u32 code) {
    const u16 list = llarm::util::bit_range<u16>(code, 0, 15);

    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);

    const u32 start_address = reg.read(Rn_id);
    const u32 end_address = static_cast<u32>((llarm::util::popcount(list) * 4) - 4);

    if (reg.is_cond_valid(code) && llarm::util::bit_fetch(code, 21)) {
        reg.write(Rn_id, (reg.read(Rn_id) + (llarm::util::popcount(list) * 4)));
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
    const u16 list = llarm::util::bit_range<u16>(code, 0, 15);

    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);

    const u32 start_address = reg.read(Rn_id) + 4;
    const u32 end_address = reg.read(Rn_id) + (llarm::util::popcount(list) * 4);

    if (reg.is_cond_valid(code) && llarm::util::bit_fetch(code, 21)) {
        reg.write(Rn_id, (reg.read(Rn_id) + (llarm::util::popcount(list) * 4)));
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
    const u16 list = llarm::util::bit_range<u16>(code, 0, 15);

    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);

    const u32 start_address = reg.read(Rn_id) - static_cast<u32>((llarm::util::popcount(list) * 4) + 4);
    const u32 end_address = reg.read(Rn_id);

    if (reg.is_cond_valid(code) && llarm::util::bit_fetch(code, 21)) {
        reg.write(Rn_id, (reg.read(Rn_id) - (llarm::util::popcount(list) * 4)));
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
    const u16 list = llarm::util::bit_range<u16>(code, 0, 15);

    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);

    const u32 start_address = reg.read(Rn_id) - (llarm::util::popcount(list) * 4);
    const u32 end_address = reg.read(Rn_id) - 4;

    if (reg.is_cond_valid(code) && llarm::util::bit_fetch(code, 21)) {
        reg.write(Rn_id, (reg.read(Rn_id) - (llarm::util::popcount(list) * 4)));
    }

    return address_struct { 
        start_address, 
        end_address 
    };
}