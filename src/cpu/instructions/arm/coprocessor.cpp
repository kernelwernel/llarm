#include "types.hpp"
#include "utility.hpp"
#include "cpu/instructions/instructions.hpp"
#include "cpu/core/registers.hpp"

// NOTE: MSR is still available in backwards compatible 26-bit mode

// TODO: THIS SHOULD BE DISABLED BEFORE V2, COPROCESSORS DIDN'T EXIST IN V1
void instructions::arm::coprocessor::CDP(const arm_code_t &code, REGISTERS& reg) {

}
// TODO: THIS SHOULD BE DISABLED BEFORE V2, COPROCESSORS DIDN'T EXIST IN V1
void instructions::arm::coprocessor::LDC(const arm_code_t &code, REGISTERS& reg) {

}


/*
 * if ConditionPassed(cond) then
 *   send Rd value to Coprocessor[cp_num]
 */
// TODO: THIS SHOULD BE DISABLED BEFORE V2, COPROCESSORS DIDN'T EXIST IN V1
void instructions::arm::coprocessor::MCR(const arm_code_t &code, REGISTERS& reg) {
    if (reg.is_priviledged() == false) {
        // TODO: UNDEFINED INSTRUCTION EXCEPTION
    }

    const u8 CRm = util::bit_fetcher<u8>(code, 0, 3);
    const u8 opcode_2 = util::bit_fetcher<u8>(code, 5, 7);
    const u8 cp_num = util::bit_fetcher<u8>(code, 8, 11);
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u8 CRn = util::bit_fetcher<u8>(code, 16, 19);
    const u8 opcode_1 = util::bit_fetcher<u8>(code, 21, 23);


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
        }

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


    reg.arm_increment_PC();
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
void instructions::arm::coprocessor::MRC(const arm_code_t &code, REGISTERS& reg) {
    if (reg.is_priviledged() == false) {
        // TODO: UNDEFINED INSTRUCTION EXCEPTION
    }

    const u8 CRm = util::bit_fetcher<u8>(code, 0, 3); // cp register type
    const u8 opcode_2 = util::bit_fetcher<u8>(code, 5, 7); // extra
    const u8 cp_num = util::bit_fetcher<u8>(code, 8, 11); // cp id
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15); // transfer arm register
    const u8 CRn = util::bit_fetcher<u8>(code, 16, 19); // cp register
    const u8 opcode_1 = util::bit_fetcher<u8>(code, 21, 23); // cp opcode (?)

    const id::coprocessor cp_id = coprocessor.fetch_cp_id(cp_num);

    const u32 data = coprocessor.read();

    if (Rd_id == id::reg::R15) {
        reg.write(id::cpsr::N, (data & (1 << 31)));
        reg.write(id::cpsr::Z, (data & (1 << 30)));
        reg.write(id::cpsr::C, (data & (1 << 29)));
        reg.write(id::cpsr::V, (data & (1 << 28)));
    } else {
        reg.write(Rd_id, data);
    }

    reg.arm_increment_PC();
}

// TODO: THIS SHOULD BE DISABLED BEFORE V2, COPROCESSORS DIDN'T EXIST IN V1
void instructions::arm::coprocessor::STC(const arm_code_t &code, REGISTERS& reg) {

}