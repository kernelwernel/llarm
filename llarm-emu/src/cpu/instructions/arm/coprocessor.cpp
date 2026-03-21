#include "../../core/registers.hpp"
#include "../instructions.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>

/**
 * if ConditionPassed(cond) then
 *     Coprocessor[cp_num]-dependent operation
 */
void INSTRUCTIONS::arm::coproc::CDP(/* const u32 code */) {
// TODO
}


/**
 * if ConditionPassed(cond) then
 *     address = start_address
 *     load Memory[address,4] for Coprocessor[cp_num]
 *     while (NotFinished(Coprocessor[cp_num]))
 *         address = address + 4
 *         load Memory[address,4] for Coprocessor[cp_num]
 *     assert address == end_address
 */
void INSTRUCTIONS::arm::coproc::LDC(/*const u32 code*/) {
    // const address_struct addresses = address_mode.load_store_coprocessor(code);
// 
    // u32 address = addresses.start;

    // TODO
}


/*
 * if ConditionPassed(cond) then
 *   send Rd value to Coprocessor[cp_num]
 */
void INSTRUCTIONS::arm::coproc::MCR(const u32 code) {
    if (reg.is_privileged() == false) {
        // TODO: UNDEFINED INSTRUCTION EXCEPTION
    }

    //const u8 opcode_1 = llarm::util::bit_range<u8>(code, 21, 23);
    const u8 opcode_2 = llarm::util::bit_range<u8>(code, 5, 7);
    const u8 CRm = llarm::util::bit_range<u8>(code, 0, 3);
    const u8 CRn = llarm::util::bit_range<u8>(code, 16, 19);
    const u8 cp_num = llarm::util::bit_range<u8>(code, 8, 11);
    const u32 Rd = reg.read(code, 12, 15);

    coprocessor.write(cp_num, CRn, CRm, /*opcode_1,*/ opcode_2, Rd); // TODO
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
void INSTRUCTIONS::arm::coproc::MRC(const u32 code) {
    if (reg.is_privileged() == false) {
        // TODO: UNDEFINED INSTRUCTION EXCEPTION
    }

    const u8 CRm = llarm::util::bit_range<u8>(code, 0, 3); // cp register type
    const u8 opcode_2 = llarm::util::bit_range<u8>(code, 5, 7); // extra
    const u8 cp_num = llarm::util::bit_range<u8>(code, 8, 11); // cp id
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15); // transfer arm register
    const u8 CRn = llarm::util::bit_range<u8>(code, 16, 19); // cp register
    //const u8 opcode_1 = llarm::util::bit_range<u8>(code, 21, 23); // cp opcode (?)

    const u32 data = coprocessor.read(cp_num, CRn, CRm, /*opcode_1,*/ opcode_2); // TODO UNCOMMENT

    if (Rd_id == id::reg::R15) {
        reg.write(id::cpsr::N, llarm::util::bit_fetch(data, 31));
        reg.write(id::cpsr::Z, llarm::util::bit_fetch(data, 30));
        reg.write(id::cpsr::C, llarm::util::bit_fetch(data, 29));
        reg.write(id::cpsr::V, llarm::util::bit_fetch(data, 28));
    } else {
        reg.write(Rd_id, data);
    }
}


/**
 * if ConditionPassed(cond) then
 *     address = start_address
 *     Memory[address,4] = value from Coprocessor[cp_num]
 *     while (NotFinished(coprocessor[cp_num]))
 *         address = address + 4
 *         Memory[address,4] = value from Coprocessor[cp_num]
 *     assert address == end_address
 */
void INSTRUCTIONS::arm::coproc::STC(/* const u32 code */) { // TODO
    //const address_struct addresses = address_mode.load_store_coprocessor(code);
    // TODO
}


void INSTRUCTIONS::arm::coproc::CDP2(/* const u32 code */) { // TODO 
    CDP(/*code*/); // TODO 
}


void INSTRUCTIONS::arm::coproc::LDC2(/* const u32 code */) { // TODO 
    LDC(/*code*/); // TODO
}


void INSTRUCTIONS::arm::coproc::MCR2(const u32 code) { 
    MCR(code); 
}


void INSTRUCTIONS::arm::coproc::MRC2(const u32 code) { 
    MRC(code);
}


void INSTRUCTIONS::arm::coproc::STC2(/*const u32 code*/) { 
    STC(/*code*/); 
}