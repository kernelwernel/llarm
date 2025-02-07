#include "types.hpp"
#include "utility.hpp"
#include "cpu/instructions/instructions.hpp"
#include "cpu/core/registers.hpp"

/**
 * start_address = Rn
 * end_address = Rn + (Number_Of_Set_Bits_In(register_list) * 4) - 4
 * address = start_address
 * for i = 0 to 7
 *    if register_list[i] == 1
 *       Ri = Memory[address,4]
 *       address = address + 4
 * assert end_address == address - 4
 * Rn = Rn + (Number_Of_Set_Bits_In(register_list) * 4)
 */
void instructions::thumb::load::LDMIA(const thumb_code_t &code, REGISTERS &reg) {

}


/**
 * address = Rn + (immed_5 * 4)
 * if address[1:0] == 0b00
 *    data = Memory[address,4]
 * else
 *    data = UNPREDICTABLE
 * Rd = data
 */
void instructions::thumb::load::LDR1(const thumb_code_t &code, REGISTERS &reg) {
    const u8 immed_5 = util::bit_fetcher<u8>(code, 6, 10);
    const id::reg Rn_id = reg.fetch_reg_id(code, 3, 5);
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);

    const u32 address = (reg.read(Rn_id) + (immed_5 * 4));

    if ((address & 0b11) == 0b00) {
        reg.write(Rd_id, memory.read())
    }
}


/**
 * 
 */
void instructions::thumb::load::LDR2(const thumb_code_t &code, REGISTERS &reg) {

}


/**
 * 
 */
void instructions::thumb::load::LDR3(const thumb_code_t &code, REGISTERS &reg) {

}


/**
 * 
 */
void instructions::thumb::load::LDR4(const thumb_code_t &code, REGISTERS &reg) {

}


/**
 * 
 */
void instructions::thumb::load::LDRB1(const thumb_code_t &code, REGISTERS &reg) {

}


/**
 * 
 */
void instructions::thumb::load::LDRB2(const thumb_code_t &code, REGISTERS &reg) {

}


/**
 * 
 */
void instructions::thumb::load::LDRH1(const thumb_code_t &code, REGISTERS &reg) {

}


/**
 * 
 */
void instructions::thumb::load::LDRH2(const thumb_code_t &code, REGISTERS &reg) {

}


/**
 * 
 */
void instructions::thumb::load::LDRSB(const thumb_code_t &code, REGISTERS &reg) {

}


/**
 * 
 */
void instructions::thumb::load::LDRSH(const thumb_code_t &code, REGISTERS &reg) {

}


/**
 * 
 */
void instructions::thumb::load::POP(const thumb_code_t &code, REGISTERS &reg) {

}
