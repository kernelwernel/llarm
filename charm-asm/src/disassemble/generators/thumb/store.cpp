#include "../generators.hpp"
#include "../util.hpp"

#include <charm/internal/shared/types.hpp>
#include <charm/internal/shared/util.hpp>

#include <string>

using namespace internal;


/** 

 * 
 * TODO
 */
std::string generators::thumb::store::STMIA(const u16 code) {
    //const (code, 0, 7);
//
    //const util::reg_id Rn_id = util::identify_reg(code, 8, 10);
//
    //const std::string Rn = util::reg_to_string(Rn_id, false);
//
    //return util::make_instruction("LDMIA ", Rn, "!, ", util::reg_list(list));
    return "todo";
}




/** 
 * STR  <Rd>, [<Rn>, #<immed_5> * 4]
 * where: 
 * <Rd> Is the register that contains the word to be stored to memory.
 * <Rn> Is the register containing the base address for the instruction.
 * <immed_5> Is a 5-bit value that is multiplied by 4 and added to the value of <Rn> to form the memory address
 * 
 * reference: A7-86
 */
std::string generators::thumb::store::STR1(const u16 code) {
    const util::reg_id Rd_id = util::identify_reg(code, 0, 2);
    const util::reg_id Rn_id = util::identify_reg(code, 3, 5);

    const std::string Rd = util::reg_to_string(Rd_id, false);
    const std::string Rn = util::reg_to_string(Rn_id, false);

    const u8 immed_5 = shared::util::bit_fetcher(code, 6, 10);

    return util::make_instruction("STR ", Rd, ", [", Rn, ", #", immed_5, " * 4]");
}


/** 
 * STR  <Rd>, [<Rn>, <Rm>]
 * where:
 * <Rd> Is the register that contains the word to be stored to memory.
 * <Rn> Is the register containing the first value used in forming the memory address.
 * <Rm> Is the register containing the second value used in forming the memory address
 * 
 * reference: A7-88
 */
std::string generators::thumb::store::STR2(const u16 code) {
    const util::reg_id Rd_id = util::identify_reg(code, 0, 2);
    const util::reg_id Rn_id = util::identify_reg(code, 3, 5);
    const util::reg_id Rm_id = util::identify_reg(code, 6, 8);

    const std::string Rd = util::reg_to_string(Rd_id, false);
    const std::string Rn = util::reg_to_string(Rn_id, false);
    const std::string Rm = util::reg_to_string(Rm_id, false);

    return util::make_instruction("STR ", Rd, ", [", Rn, ", ", Rm, "]");
}


/** 
 * STR  <Rd>, [SP, #<immed_8> * 4]
 * where: 
 * <Rd> Is the register that contains the word to be stored to memory.
 * SP Is the stack pointer. Its value is used to calculate the memory address.
 * <immed_8> Is an 8-bit value that is multiplied by 4 and added to the value of the SP to form the memory address.
 * 
 * reference: A7-90
 */
std::string generators::thumb::store::STR3(const u16 code) {
    const util::reg_id Rd_id = util::identify_reg(code, 8, 10);

    const std::string Rd = util::reg_to_string(Rd_id, false);

    const u8 immed_8 = shared::util::bit_fetcher(code, 0, 7);

    return util::make_instruction("STR ", Rd, ", [SP, #", immed_8, " * 4]");
}


/** 
 * STRB  <Rd>, [<Rn>, #<immed_5>]
 * where: 
 * <Rd> Is the register whose least significant byte is stored to memory. 
 * <Rn> Is the register containing the base address for the instruction.
 * <immed_5> Is a 5-bit immediate value that is added to the value of <Rn> to form the memory address.
 * 
 * reference: A7-92
 */
std::string generators::thumb::store::STRB1(const u16 code) {
    const util::reg_id Rd_id = util::identify_reg(code, 0, 2);
    const util::reg_id Rn_id = util::identify_reg(code, 3, 5);

    const std::string Rd = util::reg_to_string(Rd_id, false);
    const std::string Rn = util::reg_to_string(Rn_id, false);

    const u8 immed_5 = shared::util::bit_fetcher(code, 6, 10);

    return util::make_instruction("STRB ", Rd, ", [", Rn, ", #", immed_5, "]");
}


/** 
 * STRB  <Rd>, [<Rn>, <Rm>]
 * where:
 * <Rd> Is the register whose least significant byte is stored to memory.
 * <Rn> Is the register containing the first value used in forming the memory address.
 * <Rm> Is the register whose value is added to <Rn> to form the memory address.
 * 
 * reference: A7-93
 */
std::string generators::thumb::store::STRB2(const u16 code) {
    const util::reg_id Rd_id = util::identify_reg(code, 0, 2);
    const util::reg_id Rn_id = util::identify_reg(code, 3, 5);
    const util::reg_id Rm_id = util::identify_reg(code, 6, 8);

    const std::string Rd = util::reg_to_string(Rd_id, false);
    const std::string Rn = util::reg_to_string(Rn_id, false);
    const std::string Rm = util::reg_to_string(Rm_id, false);

    return util::make_instruction("STRB ", Rd, ", [", Rn, ", ", Rm, "]");
}


/** 
 * STRH  <Rd>, [<Rn>, #<immed_5> * 2]
 * where: 
 * <Rd> Is the register whose least significant halfword is stored to memory. 
 * <Rn> Is the register containing the base address for the instruction.
 * <immed_5> Is a 5-bit immediate value that is multiplied by two and added to the value of <Rn> to form the memory address.
 * 
 * reference: A7-94
 */
std::string generators::thumb::store::STRH1(const u16 code) {
    const util::reg_id Rd_id = util::identify_reg(code, 0, 2);
    const util::reg_id Rn_id = util::identify_reg(code, 3, 5);

    const std::string Rd = util::reg_to_string(Rd_id, false);
    const std::string Rn = util::reg_to_string(Rn_id, false);

    const u8 immed_5 = shared::util::bit_fetcher(code, 6, 10);

    return util::make_instruction("STRH ", Rd, ", [", Rn, ", #", immed_5, " * 2]");
}


/** 
 * STRH  <Rd>, [<Rn>, <Rm>]
 * where:
 * <Rd> Is the register whose least significant halfword is stored to memory.
 * <Rn> Is the register containing the first value used in forming the memory address.
 * <Rm> Is the register whose value is added to <Rn> to form the memory address.
 * 
 * reference: A7-95
 */
std::string generators::thumb::store::STRH2(const u16 code) {
    const util::reg_id Rd_id = util::identify_reg(code, 0, 2);
    const util::reg_id Rn_id = util::identify_reg(code, 3, 5);
    const util::reg_id Rm_id = util::identify_reg(code, 6, 8);

    const std::string Rd = util::reg_to_string(Rd_id, false);
    const std::string Rn = util::reg_to_string(Rn_id, false);
    const std::string Rm = util::reg_to_string(Rm_id, false);

    return util::make_instruction("STRH ", Rd, ", [", Rn, ", ", Rm, "]");
}


/** 
 * TODO
 * 
 * reference: A7-78
 */
std::string generators::thumb::store::PUSH(const u16 code) {
    return "todo";
}


