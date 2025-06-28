#include "addressing_modes.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"
#include "shared/out.hpp"


address_struct ADDRESSING_MODE::load_store_coprocessor(const u32 code) {
    using namespace shared::util;

    if (
        (bit_fetch(code, 27) != true) || 
        (bit_fetch(code, 26) != true) ||
        (bit_fetch(code, 25) != false)
    ) {
        shared::out::error("TODO");
    }
   
    const u8 shift_type = ((bit_fetch(code, 24) << 1) | (bit_fetch(code, 22)));

    switch (shift_type) {
        case 0b10: return ls_coproc_imm(code);
        case 0b11: return ls_coproc_imm_pre(code);
        case 0b01: return ls_coproc_imm_post(code);
        case 0b00: return ls_coproc_unindexed(code);
        default: shared::out::dev_error("Invalid coprocessor addressing mode shift type bits");
    }
}


/**
 * if ConditionPassed(cond) then
 *     if U == 1 then
 *         address = Rn + offset_8 * 4
 *     else // U == 0
 *         address = Rn - offset_8 * 4
 *     start_address = address
 *     while (NotFinished(coprocessor[cp_num]))
 *         address = address + 4
 *     end_address = address
 */
address_struct ADDRESSING_MODE::ls_coproc_imm(const u32 code) {
    using namespace shared::util;

    u32 address = 0;

    const u8 offset_8 = shared::util::bit_range<u8>(code, 0, 7);
    const u32 Rn = reg.read(code, 16, 19);
    
    if (bit_fetch(code, 23)) {
        address = Rn + (offset_8 * 4);
    } else {
        address = Rn - (offset_8 * 4);
    }

    const u32 start_address = address;
    const u8 cp_num = shared::util::bit_range(code, 8, 11);

    // ???? TODO

    // temporary
    return address_struct {
        start_address,
        0
    };
}


/**
 * if ConditionPassed(cond) then
 *     if U == 1 then
 *         Rn = Rn + offset_8 * 4
 *     else // U == 0
 *         Rn = Rn - offset_8 * 4
 *     start_address = Rn
 *     address = start_address
 *     while (NotFinished(coprocessor[cp_num]))
 *         address = address + 4
 *     end_address = address
 */
address_struct ADDRESSING_MODE::ls_coproc_imm_pre(const u32 code) {
    const bool U = shared::util::bit_fetch(code, 23);
    const u8 offset_8 = shared::util::bit_range(code, 0, 7);
    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);

    if (U == true) {
        reg.write(Rn_id, (reg.read(Rn_id) + offset_8 * 4));
    } else {
        reg.write(Rn_id, (reg.read(Rn_id) - offset_8 * 4));
    }

    const u32 start_address = reg.read(Rn_id);
    u32 address = start_address;

    
}


address_struct ADDRESSING_MODE::ls_coproc_imm_post(const u32 code) {
// TODO
}


address_struct ADDRESSING_MODE::ls_coproc_unindexed(const u32 code) {
// TODO
}