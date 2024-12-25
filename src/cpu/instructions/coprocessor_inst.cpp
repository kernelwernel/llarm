#include "types.hpp"
#include "utility.hpp"
#include "cpu/instructions.hpp"
#include "cpu/core/registers.hpp"


void instructions::coprocessor::CDP(const code_t &code, REGISTERS& reg) {

}

void instructions::coprocessor::LDC(const code_t &code, REGISTERS& reg) {

}


/*
 * if ConditionPassed(cond) then
 *   send Rd value to Coprocessor[cp_num]
 */
void instructions::coprocessor::MCR(const code_t &code, REGISTERS& reg) {
    const u8 CRm = util::bit_fetcher<u8>(code, 0, 3);
    const u8 opcode_2 = util::bit_fetcher<u8>(code, 5, 7);
    const u8 cp_num = util::bit_fetcher<u8>(code, 8, 11);
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u8 CRn = util::bit_fetcher<u8>(code, 16, 19);
    const u8 opcode_1 = util::bit_fetcher<u8>(code, 21, 23);


    // const u32 Rd = reg.read(Rd_id); idk if this is needed


    reg.increment_PC();
}




void instructions::coprocessor::MRC(const code_t &code, REGISTERS& reg) {
    u8 Rn_bits = util::bit_fetcher<u8>(code, 0, 2);
    u8 Rm_bits = util::bit_fetcher<u8>(code, 3, 5);

    const bool H2 = code.test(6);
    const bool H1 = code.test(7);

    Rn_bits += (8 * H1);
    Rm_bits += (8 * H2);

    const id::reg Rn_id = reg.fetch_reg_id(Rn_bits);
    const id::reg Rm_id = reg.fetch_reg_id(Rm_bits);

    const u32 Rn = reg.read(Rn_id);
    const u32 Rm = reg.read(Rm_id);



    reg.thumb_increment_PC();
}

void instructions::coprocessor::STC(const code_t &code, REGISTERS& reg) {

}