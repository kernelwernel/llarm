#include "types.hpp"
#include "utility.hpp"
#include "cpu/instructions/instructions.hpp"
#include "cpu/core/registers.hpp"



/**
 * 
 */
void instructions::thumb::store::STMIA(const thumb_code_t& code, REGISTERS& reg) { // TODO

    reg.thumb_increment_PC();
}


/**
 * address = Rn + (immed_5 * 4)
 * if address[1:0] == 0b00
 *    Memory[address,4] = Rd
 * else
 *    Memory[address,4] = UNPREDICTABLE
 */
void instructions::thumb::store::STR1(const thumb_code_t& code, REGISTERS& reg) { // TODO

    reg.thumb_increment_PC();
}


/**
 * 
 */
void instructions::thumb::store::STR2(const thumb_code_t& code, REGISTERS& reg) { // TODO

    reg.thumb_increment_PC();
}


/**
 * address = SP + (immed_8 * 4)
 * if address[1:0] == 0b00
 *    Memory[address,4] = Rd
 * else
 *    Memory[address,4] = UNPREDICTABLE
 */
void instructions::thumb::store::STR3(const thumb_code_t& code, REGISTERS& reg) { // TODO
    const u8 immed_8 = utill::bit_fetcher<u8>(code, 0, 7);
    const id::reg Rd_id = reg.fetch_reg_id(code, 8, 10);

    const u32 address = (reg.read(id::reg::SP) + (immed_8 * 4));

    if ((address & 0b11) == 0b00) {
        memory.write(reg.read(Rd_id), address, 4);
    } else {
        // TODO
    }

    reg.thumb_increment_PC();
}


/**
 * address = Rn + immed_5
 * Memory[address,1] = Rd[7:0]
 */
void instructions::thumb::store::STRB1(const thumb_code_t& code, REGISTERS& reg) { // TODO
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);
    const id::reg Rn_id = reg.fetch_reg_id(code, 3, 5);
    const u8 immed_5 = util::bit_fetcher(code, 6, 10);

    const u32 address = (reg.read(Rn_id) + immed_5);
    memory.write(util::bit_fetcher<u8>(reg.read(Rd_id), 0, 7), address , 1);

    reg.thumb_increment_PC();
}


/**
 * address = Rn + Rm
 * Memory[address,1] = Rd[7:0]
 */
void instructions::thumb::store::STRB2(const thumb_code_t& code, REGISTERS& reg) { // TODO
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);
    const id::reg Rn_id = reg.fetch_reg_id(code, 3, 5);
    const id::reg Rm_id = reg.fetch_reg_id(code, 6, 8);

    const u32 address = (reg.read(Rn_id) + reg.read(Rm_id));
    memory.write(util::bit_fetcher(reg.read(Rd_id), 0, 7), address, 1);

    reg.thumb_increment_PC();
}


/**
 * 
 */
void instructions::thumb::store::STRH1(const thumb_code_t& code, REGISTERS& reg) { // TODO

    reg.thumb_increment_PC();
}


/**
 * address = Rn + Rm
 * if address[1:0] == 0
 *    Memory[address,2] = Rd[15:0]
 * else
 *    Memory[address,2] = UNPREDICTABLE
 */
void instructions::thumb::store::STRH2(const thumb_code_t& code, REGISTERS& reg) { // TODO
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);
    const id::reg Rn_id = reg.fetch_reg_id(code, 3, 5);
    const id::reg Rm_id = reg.fetch_reg_id(code, 6, 8);

    const u32 address = (reg.read(Rn_id) + reg.read(Rm_id));

    if ((address & 0b11) == 0) {
        memory.write((util::bit_fetcher(reg.read(Rd_id), 0, 15)), address, 2);
    } else {
        // TODO
    }

    reg.thumb_increment_PC();
}


/**
 * 
 */
void instructions::thumb::store::PUSH(const thumb_code_t& code, REGISTERS& reg) { // TODO

    reg.thumb_increment_PC();
}


