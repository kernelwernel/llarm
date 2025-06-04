#include "../../core/registers.hpp"
#include "../instructions.hpp"

#include "shared/types.hpp"

// NOTE: MSR is still available in backwards compatible 26-bit mode

// TODO: THIS SHOULD BE DISABLED BEFORE V2, COPROCESSORS DIDN'T EXIST IN V1
void INSTRUCTIONS::arm::coprocessor_inst::CDP(const arm_code_t &code) {

}
// TODO: THIS SHOULD BE DISABLED BEFORE V2, COPROCESSORS DIDN'T EXIST IN V1
void INSTRUCTIONS::arm::coprocessor_inst::LDC(const arm_code_t &code) {

}


/*
 * if ConditionPassed(cond) then
 *   send Rd value to Coprocessor[cp_num]
 */
// TODO: THIS SHOULD BE DISABLED BEFORE V2, COPROCESSORS DIDN'T EXIST IN V1
void INSTRUCTIONS::arm::coprocessor_inst::MCR(const arm_code_t &code) {
    if (reg.is_privileged() == false) {
        // TODO: UNDEFINED INSTRUCTION EXCEPTION
    }


    const u8 opcode_1 = shared::util::bit_range<u8>(code, 21, 23);
    const u8 opcode_2 = shared::util::bit_range<u8>(code, 5, 7);
    const u8 CRm = shared::util::bit_range<u8>(code, 0, 3);
    const u8 CRn = shared::util::bit_range<u8>(code, 16, 19);
    const u8 cp_num = shared::util::bit_range<u8>(code, 8, 11);
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);


    // write-only special case for R8_MMU register in CP15 (B3-26)
    if (cp_num == 15 && CRn == 8) {
        const u8 bytecode = ((opcode_2 << 4) | CRm);

        switch (bytecode) {
            // Invalidate entire unified TLB or both instruction and data TLBs
            case 0b0000111:

            // Invalidate unified single entry
            case 0b0010111: 

            // Invalidate entire instruction TLB
            case 0b0000101: 

            // Invalidate instruction single entry
            case 0b0010101: 

            // Invalidate entire data TLB
            case 0b0000110: 

            // Invalidate data single entry
            case 0b0010110: 

            default: shared::out::error("TODO, idk maybe there's just an undefined exception here, research more");
        }

        return;
    }



    // TODO: implement the cache invalidator
    /*.
    Function<opcode2><CRm>DataInstruction
    Invalidate entire unified TLB
    or both instruction and data
    TLBs0b0000b0111SBZMCR p15, 0, Rd, c8, c7, 0
    Invalidate unified single entry0b0010b0111Virtual
    addressMCR p15, 0, Rd, c8, c7, 1
    Invalidate entire instruction
    TLB0b0000b0101SBZMCR p15, 0, Rd, c8, c5, 0
    Invalidate instruction single
    entry0b0010b0101Virtual
    addressMCR p15, 0, Rd, c8, c5, 1
    Invalidate entire data TLB0b0000b0110SBZMCR p15, 0, Rd, c8, c6, 0
    Invalidate data single entry0b0010b0110Virtual
    addressMCR p15, 0, Rd, c8, c6, 1
    */



}


/**
 * if ConditionPassed(cond) then
 *   data = value from Coprocessor[cp_num]
 *   if Rd is R15 then
 *     N flag = data[31]
 *     Z flag = data[30]
 *     C flag = data[29]
 *     V flag = data[28]
 *   else // Rd is not R15
 *     Rd = data
 */
// TODO: THIS SHOULD BE DISABLED BEFORE V2, COPROCESSORS DIDN'T EXIST IN V1
void INSTRUCTIONS::arm::coprocessor_inst::MRC(const arm_code_t &code) {
    if (reg.is_privileged() == false) {
        // TODO: UNDEFINED INSTRUCTION EXCEPTION
    }

    [[maybe_unused]] /* TODO, REMOVE */ const u8 CRm = shared::util::bit_range<u8>(code, 0, 3); // cp register type
    [[maybe_unused]] /* TODO, REMOVE */ const u8 opcode_2 = shared::util::bit_range<u8>(code, 5, 7); // extra
    [[maybe_unused]] /* TODO, REMOVE */ const u8 cp_num = shared::util::bit_range<u8>(code, 8, 11); // cp id
    [[maybe_unused]] /* TODO, REMOVE */ const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15); // transfer arm register
    [[maybe_unused]] /* TODO, REMOVE */ const u8 CRn = shared::util::bit_range<u8>(code, 16, 19); // cp register
    [[maybe_unused]] /* TODO, REMOVE */ const u8 opcode_1 = shared::util::bit_range<u8>(code, 21, 23); // cp opcode (?)

    [[maybe_unused]] /* TODO, REMOVE */ const id::cp cp_id = coprocessor.fetch_cp_id(cp_num);

    // TODO
    //const u32 data = coprocessor.read();
//
    //if (Rd_id == id::reg::R15) {
    //    reg.write(id::cpsr::N, shared::util::bit_fetch(data, 31));
    //    reg.write(id::cpsr::Z, shared::util::bit_fetch(data, 30));
    //    reg.write(id::cpsr::C, shared::util::bit_fetch(data, 29));
    //    reg.write(id::cpsr::V, shared::util::bit_fetch(data, 28));
    //} else {
    //    reg.write(Rd_id, data);
    //}


}

// TODO: THIS SHOULD BE DISABLED BEFORE V2, COPROCESSORS DIDN'T EXIST IN V1
void INSTRUCTIONS::arm::coprocessor_inst::STC(const arm_code_t &code) {

}