#include "addressing_modes.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>
#include <llarm/shared/out.hpp>

#include <llarm/llarm-asm.hpp>


address_struct ADDRESSING_MODE::load_store_coprocessor(const u32 code) {
    using namespace llarm::as;
    
    const shifter_id shifter_id = llarm::as::identify_shifter(shifter_category::LS_COPROC, code);

    switch (shifter_id) {
        case shifter_id::LS_COPROC_IMM: return ls_coproc_imm(code);
        case shifter_id::LS_COPROC_IMM_PRE: return ls_coproc_imm_pre(code);
        case shifter_id::LS_COPROC_IMM_POST: return ls_coproc_imm_post(/* code */); // TODO uncomment these when they are implemented
        case shifter_id::LS_COPROC_UNINDEXED: return ls_coproc_unindexed(/* code */); // TODO uncomment these when they are implemented
        default: llarm::out::error("Impossible identification of ARM load store coprocessor shifter");
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
    using namespace llarm::util;

    u32 address = 0;

    const u8 offset_8 = llarm::util::bit_range<u8>(code, 0, 7);
    const u32 Rn = reg.read(code, 16, 19);
    
    if (bit_fetch(code, 23)) {
        address = Rn + (offset_8 * 4);
    } else {
        address = Rn - (offset_8 * 4);
    }

    const u32 start_address = address;
    //const u8 cp_num = llarm::util::bit_range<u8>(code, 8, 11);

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
    const bool U = llarm::util::bit_fetch(code, 23);
    const u8 offset_8 = llarm::util::bit_range<u8>(code, 0, 7);
    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);

    if (U == true) {
        reg.write(Rn_id, (reg.read(Rn_id) + (offset_8 * 4)));
    } else {
        reg.write(Rn_id, (reg.read(Rn_id) - (offset_8 * 4)));
    }

    const u32 start_address = reg.read(Rn_id);
    //u32 address = start_address;

    // TODO

    // temporary
    return address_struct {
        start_address,
        0
    };    
}


address_struct ADDRESSING_MODE::ls_coproc_imm_post(/*const u32 code*/) {
// TODO


    // temporary
    return address_struct {
        0,
        0
    };
}


address_struct ADDRESSING_MODE::ls_coproc_unindexed(/*const u32 code*/) {
// TODO

    // temporary
    return address_struct {
        0,
        0
    };
}