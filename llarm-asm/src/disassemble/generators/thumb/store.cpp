#include "../generators.hpp"
#include "../util.hpp"
#include "../../disassemble.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>

#include <string>

using namespace internal;


/** 
 * STMIA <Rn>!, <registers>
 * where:
 * <Rn>Is the register containing the start address for the instruction.
 * 
 * !Causes base register writeback, and is not optional.
 * 
 * <registers> Is a list of registers to be stored, separated by commas and surrounded by { and }.
 *             The list is encoded in the register_list field of the instruction, by setting bit[i] to 1 if
 *             register Ri is included in the list and to 0 otherwise, for each of i=0 to 7.
 *             
 *             At least one register must be stored. If bits[7:0] are all zero, the result is
 *             UNPREDICTABLE.
 *             
 *             The registers are stored in sequence, the lowest-numbered register to the lowest
 *             memory address (start_address), through to the highest-numbered register to
 *             the highest memory address (end_address).
 *             
 *             The start_address is the value of the base register <Rn>. Subsequent
 *             addresses are formed by incrementing the previous address by four. One address is
 *             produced for each register that is specified in <registers>.
 *             
 *             The end_address value is four less than the sum of the value of the base register
 *             and four times the number of registers specified in <registers>.
 *            
 *             Finally, the base register <Rn> is incremented by 4 times the numbers of registers
 *             in <registers>.
 * 
 * reference: A7-84
 */
std::string generators::thumb::store::STMIA(const u32 code, const settings& settings) {
    const u8 list = llarm::util::bit_range<u8>(code, 0, 7);

    if (list == 0) {
        return ERROR;
    }

    const std::string Rn = util::reg_string(code, 8, 10, settings);

    return util::make_string(
        "STMIA ", Rn, "!, ", util::reg_list(list, settings)
    );
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
std::string generators::thumb::store::STR1(const u32 code, const settings& settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rn = util::reg_string(code, 3, 5, settings);

    const u8 immed_5 = llarm::util::bit_range<u8>(code, 6, 10);

    return util::make_string(
        "STR ", Rd, ", [", Rn, ", #", util::hex(immed_5, settings), "]"
    );
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
std::string generators::thumb::store::STR2(const u32 code, const settings& settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rn = util::reg_string(code, 3, 5, settings);
    const std::string Rm = util::reg_string(code, 6, 8, settings);

    return util::make_string(
        "STR ", Rd, ", [", Rn, ", ", Rm, "]"
    );
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
std::string generators::thumb::store::STR3(const u32 code, const settings& settings) {
    const std::string Rd = util::reg_string(code, 8, 10, settings);

    const u8 immed_8 = llarm::util::bit_range<u8>(code, 0, 7);

    return util::make_string(
        "STR ", Rd, ", [SP, #", util::hex(immed_8 * 4, settings), "]"
    );
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
std::string generators::thumb::store::STRB1(const u32 code, const settings& settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rn = util::reg_string(code, 3, 5, settings);

    const u8 immed_5 = llarm::util::bit_range<u8>(code, 6, 10);

    return util::make_string(
        "STRB ", Rd, ", [", Rn, ", #", util::hex(immed_5, settings), "]"
    );
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
std::string generators::thumb::store::STRB2(const u32 code, const settings& settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rn = util::reg_string(code, 3, 5, settings);
    const std::string Rm = util::reg_string(code, 6, 8, settings);

    return util::make_string(
        "STRB ", Rd, ", [", Rn, ", ", Rm, "]"
    );
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
std::string generators::thumb::store::STRH1(const u32 code, const settings& settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rn = util::reg_string(code, 3, 5, settings);

    const u8 immed_5 = llarm::util::bit_range<u8>(code, 6, 10);

    return util::make_string(
        "STRH ", Rd, ", [", Rn, ", #", util::hex(immed_5 * 2, settings), "]"
    );
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
std::string generators::thumb::store::STRH2(const u32 code, const settings& settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rn = util::reg_string(code, 3, 5, settings);
    const std::string Rm = util::reg_string(code, 6, 8, settings);

    return util::make_string(
        "STRH ", Rd, ", [", Rn, ", ", Rm, "]"
    );
}


/** 
 * PUSH <registers>
 * where:
 * <registers> Is the list of registers to be stored, separated by commas and surrounded by { and }.
 *             The list is encoded in the register_list field of the instruction, by setting bit[i] to 1 if
 *             register Ri is included in the list and to 0 otherwise, for each of i=0 to 7. The R bit
 *             (bit[8]) is set to 1 if the LR is in the list and to 0 otherwise.
 * 
 *             At least one register must be stored. If bits[8:0] are all zero, the result is UNPREDICTABLE.
 *             
 *             The registers are stored in sequence, the lowest-numbered register to the lowest
 *             memory address (start_address), through to the highest-numbered register to
 *             the highest memory address (end_address)
 *             
 *             The start_address is the value of the SP minus 4 times the number of registers
 *             to be stored.
 *             
 *             Subsequent addresses are formed by incrementing the previous address by four.
 *             One address is produced for each register that is specified in <registers>.
 *             
 *             The end_address value is four less than the original value of SP.
 *             
 *             The SP register is decremented by four times the numbers of registers in <registers>.
 * 
 * reference: A7-78
 */
std::string generators::thumb::store::PUSH(const u32 code, const settings& settings) {
    const u8 list = llarm::util::bit_range<u8>(code, 0, 7);

    const bool R = (llarm::util::bit_fetch(code, 8));

    if (list == 0 && R == false) {
        return ERROR;
    }

    const util::reg_id extra_reg = (R ? util::reg_id::R14 : util::reg_id::NULL_REG);

    return util::make_string(
        "PUSH ", util::reg_list(list, settings, extra_reg)
    );
}