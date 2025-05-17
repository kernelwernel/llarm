//#include "addressing_modes.hpp"
//#include "shared/types.hpp"
//#include "shared/util.hpp"
//
//
//ADDRESSING_MODE::address_struct ADDRESSING_MODE::load_store_coprocessor(const arm_code_t &code) {
//    if (
//        (code.test(27) != true) || 
//        (code.test(26) != true) ||
//        (code.test(25) != false)
//    ) {
//        shared::out::error("TODO");
//    }
//   
//    const u8 shift_type = ((code.test(24) << 1) | (code.test(22)));
//
//    switch (shift_type) {
//        case 0b10: return ls_coproc_imm(code);
//        case 0b11: return ls_coproc_imm_pre(code);
//        case 0b01: return ls_coproc_imm_post(code);
//        case 0b00: return ls_coproc_unindexed(code);
//    }
//
//    shared::out::error("TODO");    
//}
//
//
///**
// * if ConditionPassed(cond) then
// *     if U == 1 then
// *         address = Rn + offset_8 * 4
// *     else // U == 0
// *         address = Rn - offset_8 * 4
// *     start_address = address
// *     while (NotFinished(coprocessor[cp_num]))
// *         address = address + 4
// *     end_address = address
// */
//ADDRESSING_MODE::address_struct ADDRESSING_MODE::ls_coproc_imm(const arm_code_t &code) {
//    u32 address = 0;
//
//    const u8 offset_8 = shared::util::bit_range<u8>(code, 0, 7);
//    const u32 Rn = reg.read(code, 16, 19);
//    
//    if (code.test(23)) {
//        address = Rn + (offset_8 * 4);
//    } else {
//        address = Rn - (offset_8 * 4);
//    }
//
//    const u32 start_address = address;
//
//    
//}
//
//
//ADDRESSING_MODE::address_struct ADDRESSING_MODE::ls_coproc_imm_pre(const arm_code_t &code) {
//
//}
//
//
//ADDRESSING_MODE::address_struct ADDRESSING_MODE::ls_coproc_imm_post(const arm_code_t &code) {
//
//}
//
//
//ADDRESSING_MODE::address_struct ADDRESSING_MODE::ls_coproc_unindexed(const arm_code_t &code) {
//
//}