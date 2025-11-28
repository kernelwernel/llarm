#include "../generators.hpp"
#include "../util.hpp"
#include "shifter_operands/shifters.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"
#include "shared/out.hpp"

#include <string>

using namespace internal;


/**
 * STM{<cond>}<addressing_mode> <Rn>{!}, <registers>
 * where:
 * <cond>      Is the condition under which the instruction is executed. The conditions are defined
 *             in The condition field on page A3-5. If <cond> is omitted, the AL (always)
 *             condition is used.
 * <addressing_mode>
 *             Is described in Addressing Mode 4 - Load and Store Multiple on page A5-48. It
 *             determines the P, U, and W bits of the instruction.
 * <Rn>        Specifies the base register used by <addressing_mode>. If R15 is specified as
 *             <Rn>, the result is UNPREDICTABLE.
 * !           Sets the W bit, causing the instruction to write a modified value back to its base
 *             register Rn as specified in Addressing Mode 4 - Load and Store Multiple on
 *             page A5-48. If ! is omitted, the W bit is 0 and the instruction does not change its
 *             base register in this way.
 * <registers> Is a list of registers, separated by commas and surrounded by { and }. It specifies
 *             the set of registers to be stored by the STM instruction.
 *             The registers are stored in sequence, the lowest-numbered register to the lowest
 *             memory address (start_address), through to the highest-numbered register to
 *             the highest memory address (end_address).
 *             For each of i=0 to 15, bit[i] in the register_list field of the instruction is 1 if Ri is in
 *             the list and 0 otherwise. If bits[15:0] are all zero, the result is UNPREDICTABLE.
 *             If R15 is specified in <registers>, the value stored is IMPLEMENTATION
 *             DEFINED. For more details, see Reading the program counter on page A2-7.
 *
 * reference: A4-84
 */
std::string generators::arm::store::STM1(const u32 code, const settings settings) {
    const u16 register_list = llarm::util::bit_range<u16>(code, 0, 15);
    
    const std::string Rn = util::reg_string(code, 16, 19, settings);
    
    const std::string addressing_mode = shifters::ls_mul(code, settings);

    const char* W = (llarm::util::bit_fetch(code, 21) ? "!" : "");

    return util::make_string("STM", util::cond(code, settings), addressing_mode, " ", Rn, W, ", ", util::reg_list(register_list, settings));
}


/**
 * STM{<cond>}<addressing_mode> <Rn>, <registers>^
 * where:
 * <cond>      Is the condition under which the instruction is executed. The conditions are defined
 *             in The condition field on page A3-5. If <cond> is omitted, the AL (always)
 *             condition is used.
 * <addressing_mode>
 *             Is described in Addressing Mode 4 - Load and Store Multiple on page A5-48. It
 *             determines the P and U bits of the instruction. Only the forms of this addressing
 *             mode with W == 0 are available for this form of the STM instruction.
 * <Rn>        Specifies the base register used by <addressing_mode>. If R15 is specified as
 *             the base register <Rn>, the result is UNPREDICTABLE.
 * <registers> Is a list of registers, separated by commas and surrounded by { and }. It specifies
 *             the set of registers to be stored by the STM instruction.
 *             The registers are stored in sequence, the lowest-numbered register to the lowest
 *             memory address (start_address), through to the highest-numbered register to
 *             the highest memory address (end_address).
 *             For each of i=0 to 15, bit[i] in the register_list field of the instruction is 1 if Ri is in
 *             the list and 0 otherwise. If bits[15:0] are all zero, the result is UNPREDICTABLE.
 *             If R15 is specified in <registers> the value stored is IMPLEMENTATION
 *             DEFINED. For more details, see Reading the program counter on page A2-7.
 * ^           For an STM instruction, indicates that User mode registers are to be stored.
 */
std::string generators::arm::store::STM2(const u32 code, const settings settings) {
    return STM1(code, settings) + "^";
}


/**
 * STR{<cond>} <Rd>, <addressing_mode>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>   Specifies the source register for the operation. If R15 is specified for <Rd>, the value stored
 *        is IMPLEMENTATION DEFINED. For more details, see Reading the program counter on
 *        page A2-7.
 * <addressing_mode>
 *        Is described in Addressing Mode 2 - Load and Store Word or Unsigned Byte on page A5-18.
 *        It determines the I, P, U, W, Rn and addr_mode bits of the instruction.
 *        The syntax of all forms of <addressing_mode> includes a base register <Rn>. Some
 *        forms also specify that the instruction modifies the base register value (this is known as base
 *        register writeback).
 * 
 * reference: A4-88
 */
std::string generators::arm::store::STR(const u32 code, const settings settings) {
    const u16 register_list = llarm::util::bit_range<u16>(code, 0, 15);

    const std::string Rd = util::reg_string(code, 12, 15, settings);

    const std::string addressing_mode = shifters::ls(code, settings);

    return util::make_string("STR", util::cond(code, settings), " ", Rd, ", ", addressing_mode);
}


/**
 * STR{<cond>}B <Rd>, <addressing_mode>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>   Specifies the source register for the operation. If R15 is specified for <Rd>, the result is
 *        UNPREDICTABLE.
 * <addressing_mode>
 *        Is described in Addressing Mode 2 - Load and Store Word or Unsigned Byte on page A5-18.
 *        It determines the I, P, U, W, Rn and addr_mode bits of the instruction.
 *        The syntax of all forms of <addressing_mode> includes a base register <Rn>. Some
 *        forms also specify that the instruction modifies the base register value (this is known as base
 *        register writeback).
 *
 * reference: A4-90
 */
std::string generators::arm::store::STRB(const u32 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 12, 15, settings);

    const std::string addressing_mode = shifters::ls(code, settings);

    return util::make_string("STR", util::cond(code, settings), "B ", Rd, ", ", addressing_mode);
}


/**
 * STR{<cond>}BT <Rd>, <post_indexed_addressing_mode>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>   Specifies the source register for the operation. If R15 is specified for <Rd>, the result is
 *        UNPREDICTABLE.
 * <post_indexed_addressing_mode>
 *        Is described in Addressing Mode 2 - Load and Store Word or Unsigned Byte on page A5-18.
 *        It determines the I, U, Rn and addr_mode bits of the instruction. Only post-indexed forms
 *        of Addressing Mode 2 are available for this instruction. These forms have P == 0 and W ==
 *        0, where P and W are bit[24] and bit[21] respectively. This instruction uses P == 0 and W
 *        == 1 instead, but the addressing mode is the same in all other respects.
 *        The syntax of all forms of <post_indexed_addressing_mode> includes a base
 *        register <Rn>. All forms also specify that the instruction modifies the base register value
 *        (this is known as base register writeback).
 *
 * reference: A4-92
*/
std::string generators::arm::store::STRBT(const u32 code, const settings settings) {
    const shifter_enum mode_id = shifters::identify_ls_shifter(code);
    
    switch (mode_id) {
        case shifter_enum::LS_IMM_POST:
        case shifter_enum::LS_REG_POST:
        case shifter_enum::LS_SCALED_POST_LSL:
        case shifter_enum::LS_SCALED_POST_LSR:
        case shifter_enum::LS_SCALED_POST_ASR:
        case shifter_enum::LS_SCALED_POST_ROR:
        case shifter_enum::LS_SCALED_POST_RRX: break;
        default: llarm::out::error("Only post-indexed addressing modes are allowed for STRBT");
    }

    const std::string Rd = util::reg_string(code, 12, 15, settings);

    const std::string post_indexed_addressing_mode = shifters::shifter_to_string(mode_id, code, settings);

    return util::make_string("STR", util::cond(code, settings), "BT ", Rd, post_indexed_addressing_mode);
}


/**
 * STR{<cond>}H <Rd>, <addressing_mode>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>   Specifies the source register for the operation. If R15 is specified for <Rd>, the result is
 *        UNPREDICTABLE.
 * <addressing_mode>
 *        Is described in Addressing Mode 3 - Miscellaneous Loads and Stores on page A5-34. It
 *        determines the P, U, I, W, Rn and addr_mode bits of the instruction.
 *        The syntax of all forms of <addressing_mode> includes a base register <Rn>. Some
 *        forms also specify that the instruction modifies the base register value (this is known as base
 *        register writeback).
 * 
 * reference: A4-94
 */
std::string generators::arm::store::STRH(const u32 code, const settings settings) {
    const std::string addressing_mode = shifters::ls_misc(code, settings);

    const std::string Rd = util::reg_string(code, 12, 15, settings);

    return util::make_string("STR", util::cond(code, settings), "H ", Rd, ", ", addressing_mode);
}


/**
 * STR{<cond>}T <Rd>, <post_indexed_addressing_mode>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>   Specifies the source register for the operation. If R15 is specified for <Rd>, the value stored
 *        is IMPLEMENTATION DEFINED. For more details, see Reading the program counter on
 *        page A2-7.
 * <post_indexed_addressing_mode>
 *        Is described in Addressing Mode 2 - Load and Store Word or Unsigned Byte on page A5-18.
 *        It determines the I, U, Rn and addr_mode bits of the instruction. Only post-indexed forms
 *        of Addressing Mode 2 are available for this instruction. These forms have P == 0 and W ==
 *        0, where P and W are bit[24] and bit[21] respectively. This instruction uses P == 0 and W
 *        == 1 instead, but the addressing mode is the same in all other respects.
 *        The syntax of all forms of <post_indexed_addressing_mode> includes a base
 *        register <Rn>. All forms also specify that the instruction modifies the base register value
 *        (this is known as base register writeback).
 *
 * reference: A4-96
 */
std::string generators::arm::store::STRT(const u32 code, const settings settings) {
    const shifter_enum mode_id = shifters::identify_ls_shifter(code);

    switch (mode_id) {
        case shifter_enum::LS_IMM_POST:
        case shifter_enum::LS_REG_POST:
        case shifter_enum::LS_SCALED_POST_LSL:
        case shifter_enum::LS_SCALED_POST_LSR:
        case shifter_enum::LS_SCALED_POST_ASR:
        case shifter_enum::LS_SCALED_POST_ROR:
        case shifter_enum::LS_SCALED_POST_RRX: break;
        default: llarm::out::error("Only post-indexed addressing modes are allowed for STRBT");
    }

    const std::string Rd = util::reg_string(code, 12, 15, settings);

    const std::string post_indexed_addressing_mode = shifters::shifter_to_string(mode_id, code, settings);

    return util::make_string("STR", util::cond(code, settings), "T ", Rd, ", ", post_indexed_addressing_mode);
}


/**
 * SWP{<cond>} <Rd>, <Rm>, [<Rn>]
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>   Specifies the destination register for the instruction.
 * <Rm>   Contains the value that is stored to memory.
 * <Rn>   Contains the memory address to load from.
 * 
 * reference: A4-102
 */
std::string generators::arm::store::SWP(const u32 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 12, 15, settings);
    const std::string Rm = util::reg_string(code, 0, 3, settings);
    const std::string Rn = util::reg_string(code, 16, 19, settings);

    return util::make_string("SWP", util::cond(code, settings), " ", Rd, ", ", Rm, ", [", Rn, "]");
}


/**
 * SWP{<cond>}B <Rd>, <Rm>, [<Rn>]
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>   Specifies the destination register for the instruction.
 * <Rm>   Contains the value that is stored to memory.
 * <Rn>   Contains the memory address to load from.
 *
 * reference: A4-104
 */
std::string generators::arm::store::SWPB(const u32 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 12, 15, settings);
    const std::string Rm = util::reg_string(code, 0, 3, settings);
    const std::string Rn = util::reg_string(code, 16, 19, settings);

    return util::make_string("SWP", util::cond(code, settings), "B ", Rd, ", ", Rm, ", [", Rn, "]");
}