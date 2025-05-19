#include "../generators.hpp"
#include "../util.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"

#include <string>

using namespace internal;


/** 
 * LDMIA  <Rn>!, <registers>
 * where:
 * <Rn> Is the register containing the start address for the instruction.
 * ! Causes base register writeback, and is not optional.
 * <registers> Is a list of registers to be loaded, separated by commas and surrounded by { and }. 
 *             The list is encoded in the register_list field of the instruction, by setting bit[i] to 1 if 
 *             register Ri is included in the list and to 0 otherwise, for each of i=0 to 7.
 *             At least one register must be loaded. If bits[7:0] are all zero, the result is UNPREDICTABLE.
 * 
 *             The registers are loaded in sequence, the lowest-numbered register from the lowest 
 *             memory address (start_address), through to the highest-numbered register 
 *             from the highest memory address (end_address).
 * 
 *             The start_address is the value of the base register <Rn>. Subsequent 
 *             addresses are formed by incrementing the previous address by four. One address is 
 *             produced for each register that is specified in <registers>. 
 * 
 *             The end_address value is four less than the sum of the value of the base register 
 *             and four times the number of registers specified in <registers>. 
 * 
 *             Finally, the base register <Rn> is incremented by four times the numbers of 
 *             registers in <registers>.
 * 
 * reference: A7-40
 */
std::string generators::thumb::load::LDMIA(const u16 code, const settings settings) {
    const std::string Rn = util::reg_string(code, 8, 10, settings);

    const u8 list = shared::util::bit_range<u8>(code, 0, 7);

    return util::make_string(
        "LDMIA ", Rn, "!, ", util::reg_list(list, settings)
    );
}


/**
 * LDR  <Rd>, [<Rn>, #<immed_5> * 4]
 * where: 
 * <Rd> Is the destination register for the word loaded from memory.
 * <Rn> Is the register containing the base address for the instruction.
 * <immed_5> Is a 5-bit value that is multiplied by 4 and added to the value of <Rn> to form the memory address.
 *
 * reference: A7-42
 */
std::string generators::thumb::load::LDR1(const u16 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rn = util::reg_string(code, 3, 5, settings);

    const u8 immed_5 = shared::util::bit_range<u8>(code, 6, 10);

    return util::make_string(
        "LDR ", Rd, ", [", Rn, ", #", util::hex(immed_5, settings), " * 4]"
    );
}



/**
 * LDR  <Rd>, [<Rn>, <Rm>]
 * where:
 * <Rd> Is the destination register for the word loaded from memory.
 * <Rn> Is the register containing the first value used in forming the memory address.
 * <Rm> Is the register containing the second value used in forming the memory addressto form the memory address.
 *
 * reference: A7-44
 */
std::string generators::thumb::load::LDR2(const u16 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rn = util::reg_string(code, 3, 5, settings);
    const std::string Rm = util::reg_string(code, 6, 8, settings);

    return util::make_string(
        "LDR ", Rd, ", [", Rn, ", ", Rm, "]"
    );
}


/**
 * LDR  <Rd>, [PC, #<immed_8> * 4]
 * where: 
 * <Rd> Is the destination register for the word loaded from memory.
 * PC Is the program counter. Its value is used to calculate the memory address. Bit 1 of the PC 
 *    value is forced to zero for the purpose of this calculation, so the address is always word-aligned.
 * <immed_8> Is an 8-bit value that is multiplied by 4 and added to the value of the PC to form the memory address.
 *
 * reference: A7-46
 */
std::string generators::thumb::load::LDR3(const u16 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 8, 10, settings);

    const u8 immed_8 = shared::util::bit_range<u8>(code, 0, 7);

    return util::make_string(
        "LDR ", Rd, ", [PC, #", util::hex(immed_8, settings), " * 4]"
    );
}


/**
 * LDR  <Rd>, [SP, #<immed_8> * 4]
 * where: 
 * <Rd> Is the destination register for the word loaded from memory.
 * SP Is the stack pointer. Its value is used to calculate the memory address.
 * <immed_8> Is an 8-bit value that is multiplied by 4 and added to the value of the SP to form the memory address
 *
 * reference: A7-46
 */
std::string generators::thumb::load::LDR4(const u16 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 8, 10, settings);

    const u8 immed_8 = shared::util::bit_range<u8>(code, 0, 7);

    return util::make_string(
        "LDR ", Rd, ", [SP, #", util::hex(immed_8, settings), " * 4]"
    );
}


/**
 * LDRB  <Rd>, [<Rn>, #<immed_5>]
 * where: 
 * <Rd> Is the destination register for the byte loaded from memory.
 * <Rn> Is the register containing the base address for the instruction.
 * <immed_5> Is a 5-bit value that is added to the value of <Rn> to form the memory address
 *
 * reference: A7-50
 */
std::string generators::thumb::load::LDRB1(const u16 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rn = util::reg_string(code, 3, 5, settings);

    const u8 immed_5 = shared::util::bit_range<u8>(code, 6, 10);

    return util::make_string(
        "LDRB ", Rd, ", [", Rn, ", #", util::hex(immed_5, settings), "]"
    );
}


/**
 * LDRB  <Rd>, [<Rn>, <Rm>]
 * where:
 * <Rd> Is the destination register for the byte loaded from memory.
 * <Rn> Is the register containing the first value used in forming the memory address.
 * <Rm> Is the register containing the second value used in forming the memory address
 *
 * reference: A7-51
 */
std::string generators::thumb::load::LDRB2(const u16 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rn = util::reg_string(code, 3, 5, settings);
    const std::string Rm = util::reg_string(code, 6, 8, settings);

    return util::make_string(
        "LDRB ", Rd, ", [", Rn, ", ", Rm, "]"
    );
}


/**
 * LDRH  <Rd>, [<Rn>, #<immed_5> * 2]
 * where: 
 * <Rd> Is the destination register for the halfword loaded from memory.
 * <Rn> Is the register containing the base address for the instruction.
 * <immed_5> Is a 5-bit value that is multiplied by 2, then added to the value of <Rn> to form the memory address.
 *
 * reference: A7-52
 */
std::string generators::thumb::load::LDRH1(const u16 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rn = util::reg_string(code, 3, 5, settings);

    const u8 immed_5 = shared::util::bit_range<u8>(code, 6, 10);

    return util::make_string(
        "LDRH ", Rd, ", [", Rn, ", #", util::hex(immed_5, settings), " * 2]"
    );
}



/**
 * LDRH  <Rd>, [<Rn>, <Rm>]
 * where:
 * <Rd> Is the destination register for the halfword loaded from memory.
 * <Rn> Is the register containing the first value used in forming the memory address.
 * <Rm> Is the register containing the second value used in forming the memory address
 *
 * reference: A7-54
 */
std::string generators::thumb::load::LDRH2(const u16 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rn = util::reg_string(code, 3, 5, settings);
    const std::string Rm = util::reg_string(code, 6, 8, settings);

    return util::make_string(
        "LDRH ", Rd, ", [", Rn, ", ", Rm, "]"
    );
}


/**
 * LDRSB  <Rd>, [<Rn>, <Rm>]
 * where:
 * <Rd> Is the destination register for the byte loaded from memory.
 * <Rn> Is the register containing the first value used in forming the memory address.
 * <Rm> Is the register containing the second value used in forming the memory address.
 *
 * reference: A7-56
 */
std::string generators::thumb::load::LDRSB(const u16 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rn = util::reg_string(code, 3, 5, settings);
    const std::string Rm = util::reg_string(code, 6, 8, settings);

    return util::make_string(
        "LDRSB ", Rd, ", [", Rn, ", ", Rm, "]"
    );
}


/**
 * LDRSH  <Rd>, [<Rn>, <Rm>]
 * where:
 * <Rd> Is the destination register for the halfword loaded from memory.
 * <Rn> Is the register containing the first value used in forming the memory address.
 * <Rm> Is the register containing the second value used in forming the memory address
 *
 * reference: A7-57
 */
std::string generators::thumb::load::LDRSH(const u16 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rn = util::reg_string(code, 3, 5, settings);
    const std::string Rm = util::reg_string(code, 6, 8, settings);

    return util::make_string(
        "LDRSH ", Rd, ", [", Rn, ", ", Rm, "]"
    );
}


/**
 * POP  <registers>
 * where: 
 * <registers> Is the list of registers, separated by commas and surrounded by { and }. The list is 
 *             encoded in the register_list field of the instruction, by setting bit[i] to 1 if register 
 *             Ri is included in the list and to 0 otherwise, for each of i=0 to 7. The R bit (bit[8]) 
 *             is set to 1 if the PC is in the list and to 0 otherwise.
 * 
 *             At least one register must be loaded. If bits[8:0] are all zero, the result is UNPREDICTABLE.
 *             
 *             The registers are loaded in sequence, the lowest-numbered register from the lowest 
 *             memory address (start_address), through to the highest-numbered register 
 *             from the highest memory address (end_address). If the PC is specified in the 
 *             register list (opcode bit[8] is set), the instruction causes a branch to the address 
 *             (data) loaded into the PC.
 * 
 *             The <start_address> is the value of the SP. 
 * 
 *             Subsequent addresses are formed by incrementing the previous address by four. 
 *             One address is produced for each register that is specified in <registers>. 
 *             
 *             The end_address value is four less than the sum of the value of the SP and four 
 *             times the number of registers specified in <registers>. 
 *             
 *             The SP register is incremented by four times the numbers of registers in 
 *             <registers>.
 *
 * reference: A7-75
 */
std::string generators::thumb::load::POP(const u16 code, const settings settings) {
    const u8 list = shared::util::bit_range<u8>(code, 0, 7);

    const bool R = (shared::util::bit_fetch(code, 8));

    const util::reg_id extra_reg = (R ? util::reg_id::R15 : util::reg_id::NULL_REG);

    return util::make_string(
        "POP ", util::reg_list(list, settings, extra_reg)
    );
}