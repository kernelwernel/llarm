#include "../generators.hpp"
#include "../util.hpp"
#include "shifter_operands/shifters.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"
#include "shared/out.hpp"

#include <string>

using namespace internal;

/**
 * LDM{<cond>}<addressing_mode> <Rn>{!}, <registers>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <addressing_mode>
 *        Is described in Addressing Mode 4 - Load and Store Multiple on page A5-48. It determines
 *        the P, U, and W bits of the instruction.
 * 
 * <Rn>   Specifies the base register used by <addressing_mode>. Using R15 as the base register
 *        <Rn> gives an UNPREDICTABLE result.
 * 
 * !      Sets the W bit, causing the instruction to write a modified value back to its base register Rn
 *        as specified in Addressing Mode 4 - Load and Store Multiple on page A5-48. If ! is omitted,
 *        the W bit is 0 and the instruction does not change its base register in this way. (However, if
 *        the base register is included in <registers>, it changes when a value is loaded into it.)
 * 
 * <registers>
 *        Is a list of registers, separated by commas and surrounded by { and }. It specifies the set of
 *        registers to be loaded by the LDM instruction.
 *        The registers are loaded in sequence, the lowest-numbered register from the lowest memory
 *        address (start_address), through to the highest-numbered register from the highest
 *        memory address (end_address). If the PC is specified in the register list (opcode bit[15]
 *        is set), the instruction causes a branch to the address (data) loaded into the PC.
 *        For each of i=0 to 15, bit[i] in the register_list field of the instruction is 1 if Ri is in the list
 *        and 0 otherwise. If bits[15:0] are all zero, the result is UNPREDICTABLE
 * 
 * reference: A4-30
 */
std::string generators::arm::load::LDM1(const u32 code, const settings settings) {
    const u16 register_list = shared::util::bit_range<u16>(code, 0, 15);

    const std::string Rn = util::reg_string(code, 16, 19, settings); 

    const std::string addressing_mode = shifters::ls_mul(code, settings);

    const std::string W = (shared::util::bit_fetch(code, 21) ? "!" : "");

    const std::string registers = util::reg_list(register_list, settings);

    return util::make_string("LDM", util::cond(code, settings), addressing_mode, " ", Rn, W, ", ", registers);
}


/**
 * LDM{<cond>}<addressing_mode> <Rn>, <registers_without_pc>^
 * where:
 * <cond>  Is the condition under which the instruction is executed. The conditions are defined in The
 *         condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * 
 * <addressing_mode>
 *         Is described in Addressing Mode 4 - Load and Store Multiple on page A5-48. It determines
 *         the P and U bits of the instruction. Only the forms of this addressing mode with W == 0 are
 *         available for this form of the LDM instruction.
 * 
 * <Rn>    Specifies the base register used by <addressing_mode>. Using R15 as <Rn> gives an
 *         UNPREDICTABLE result.
 * 
 * <registers_without_pc>
 *         Is a list of registers, separated by commas and surrounded by { and }. This list must not
 *         include the PC, and specifies the set of registers to be loaded by the LDM instruction.
 *         The registers are loaded in sequence, the lowest-numbered register from the lowest memory
 *         address (start_address), through to the highest-numbered register from the highest
 *         memory address (end_address).
 *         For each of i=0 to 15, bit[i] in the register_list field of the instruction is 1 if Ri is in the list
 *         and 0 otherwise. If bits[15:0] are all zero, the result is UNPREDICTABLE.
 * 
 * ^       For an LDM instruction that does not load the PC, this indicates that User mode registers are
 *         to be loaded.
 * 
 * reference: A4-32
 */
std::string generators::arm::load::LDM2(const u32 code, const settings settings) {
    const u16 register_list = shared::util::bit_range<u16>(code, 0, 14);
    
    const std::string Rn = util::reg_string(code, 16, 19, settings);

    const std::string addressing_mode = shifters::ls_mul(code, settings);

    const std::string registers_without_pc = util::reg_list(register_list, settings);

    return util::make_string("LDM", util::cond(code, settings), addressing_mode, " ", Rn, ", ", registers_without_pc, "^");
}


/**
 * LDM{<cond>}<addressing_mode> <Rn>{!}, <registers_and_pc>^
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * 
 * <addressing_mode> 
 *        Is described in Addressing Mode 4 - Load and Store Multiple on page A5-48. It determines
 *        the P, U, and W bits of the instruction.
 * 
 * <Rn>   Specifies the base register used by <addressing_mode>. Using R15 as <Rn> gives an
 *        UNPREDICTABLE result.
 * 
 * !      Sets the W bit, and the instruction writes a modified value back to its base register Rn (see
 *        Addressing Mode 4 - Load and Store Multiple on page A5-48). If ! is omitted, the W bit is
 *        0 and the instruction does not change its base register in this way. (However, if the base
 *        register is included in <registers>, it changes when a value is loaded into it.)
 * 
 * <registers_and_pc>
 *        Is a list of registers, separated by commas and surrounded by { and }. This list must include
 *        the PC, and specifies the set of registers to be loaded by the LDM instruction.
 *        The registers are loaded in sequence, the lowest-numbered register from the lowest memory
 *        address (start_address), through to the highest-numbered register from the highest
 *        memory address (end_address).
 * 
 * ^      For each of i=0 to 15, bit[i] in the register_list field of the instruction is 1 if Ri is in the list
 *        and 0 otherwise.
 *        For an LDM instruction that loads the PC, this indicates that the SPSR of the current mode
 *        is copied to the CPSR.
 * 
 * reference: A4-34
 */
std::string generators::arm::load::LDM3(const u32 code, const settings settings) {
    const u16 register_list = shared::util::bit_range<u16>(code, 0, 14);

    const std::string Rn = util::reg_string(code, 16, 19, settings);

    const std::string addressing_mode = shifters::ls_mul(code, settings);

    const std::string W = (shared::util::bit_fetch(code, 21) ? "!" : "");

    const std::string registers_and_pc = util::reg_list(register_list, settings, util::reg_id::R15);

    return util::make_string("LDM", util::cond(code, settings), addressing_mode, " ", Rn, W, ", ", registers_and_pc, "^");
}


/**
 * LDR{<cond>} <Rd>, <addressing_mode>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>   Specifies the destination register for the loaded value.
 * <addressing_mode>
 *        Is described in Addressing Mode 2 - Load and Store Word or Unsigned Byte on page A5-18.
 *        It determines the I, P, U, W, Rn and addr_mode bits of the instruction.
 *        The syntax of all forms of <addressing_mode> includes a base register <Rn>. Some
 *        forms also specify that the instruction modifies the base register value (this is known as base
 *        register writeback).
 * 
 * reference: A4-37
 */
std::string generators::arm::load::LDR(const u32 code, const settings settings) {
    const std::string addressing_mode = shifters::ls(code, settings);

    const std::string Rd = util::reg_string(code, 12, 15, settings);

    return util::make_string("LDR", util::cond(code, settings), " ", Rd, ", ", addressing_mode);
}


/**
 * LDR{<cond>}B <Rd>, <addressing_mode>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>   Specifies the destination register for the loaded value. If register 15 is specified for <Rd>,
 *        the result is UNPREDICTABLE.
 * <addressing_mode>
 *        Is described in Addressing Mode 2 - Load and Store Word or Unsigned Byte on page A5-18.
 *        It determines the I, P, U, W, Rn and addr_mode bits of the instruction.
 *        The syntax of all forms of <addressing_mode> includes a base register <Rn>. Some
 *        forms also specify that the instruction modifies the base register value (this is known as base
 *        register writeback).
 *
 * reference: A4-40
 */
std::string generators::arm::load::LDRB(const u32 code, const settings settings) {
    const std::string addressing_mode = shifters::ls(code, settings);

    const std::string Rd = util::reg_string(code, 12, 15, settings);

    return util::make_string("LDR", util::cond(code, settings), "B ", Rd, ", ", addressing_mode);
}


/**
 * LDR{<cond>}BT <Rd>, <post_indexed_addressing_mode>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>   Specifies the destination register for the loaded value. If R15 is specified for <Rd>, the
 *        result is UNPREDICTABLE.
 * <post_indexed_addressing_mode>
 *        Is described in Addressing Mode 2 - Load and Store Word or Unsigned Byte on page A5-18.
 *        It determines the I, U, Rn and addr_mode bits of the instruction. Only post-indexed forms
 *        of Addressing Mode 2 are available for this instruction. These forms have P == 0 and W ==
 *        0, where P and W are bit[24] and bit[21] respectively. This instruction uses P == 0 and W
 *        == 1 instead, but the addressing mode is the same in all other respects.
 * 
 *        The syntax of all forms of <post_indexed_addressing_mode> includes a base
 *        register <Rn>. All forms also specify that the instruction modifies the base register value
 *        (this is known as base register writeback).
 * 
 * reference: A4-42
 */
std::string generators::arm::load::LDRBT(const u32 code, const settings settings) {
    const shifters::mode mode_id = shifters::identify_ls_shifter(code);
    
    switch (mode_id) {
        case shifters::mode::LS_IMM_POST:
        case shifters::mode::LS_REG_POST:
        case shifters::mode::LS_REG_SCALED_POST_LSL:
        case shifters::mode::LS_REG_SCALED_POST_LSR:
        case shifters::mode::LS_REG_SCALED_POST_ASR:
        case shifters::mode::LS_REG_SCALED_POST_ROR:
        case shifters::mode::LS_REG_SCALED_POST_RRX: break;
        default: shared::out::error("Only post-indexed addressing modes are allowed for LDRBT");
    }

    const std::string Rd = util::reg_string(code, 12, 15, settings);

    const std::string post_indexed_addressing_mode = shifters::shifter_to_string(mode_id, code, settings);

    return util::make_string("LDR", util::cond(code, settings), "BT ", Rd, ", ", post_indexed_addressing_mode);
}


/**
 * LDR{<cond>}H <Rd>, <addressing_mode>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>   Specifies the destination register for the loaded value. If R15 is specified for <Rd>, the
 *        result is UNPREDICTABLE.
 * <addressing_mode>
 *        Is described in Addressing Mode 3 - Miscellaneous Loads and Stores on page A5-34. It
 *        determines the P, U, I, W, Rn and addr_mode bits of the instruction.
 *        The syntax of all forms of <addressing_mode> includes a base register <Rn>. Some
 *        forms also specify that the instruction modifies the base register value (this is known as base
 *        register writeback).
 * 
 * reference: A4-44
 */
std::string generators::arm::load::LDRH(const u32 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 12, 15, settings);

    const std::string addressing_mode = shifters::ls_misc(code, settings);

    return util::make_string("LDR", util::cond(code, settings), "H ", Rd, ", ", addressing_mode);
}


/**
 * LDR{<cond>}SB <Rd>, <addressing_mode>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>   Specifies the destination register for the loaded value. If R15 is specified for <Rd>, the
 *        result is UNPREDICTABLE.
 * <addressing_mode>
 *        Is described in Addressing Mode 3 - Miscellaneous Loads and Stores on page A5-34. It
 *        determines the P, U, I, W, Rn and addr_mode bits of the instruction.
 *        The syntax of all forms of <addressing_mode> includes a base register <Rn>. Some
 *        forms also specify that the instruction modifies the base register value (this is known as base
 *        register writeback).
 *
 * reference: A4-46
 */
std::string generators::arm::load::LDRSB(const u32 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 12, 15, settings);

    const std::string addressing_mode = shifters::ls_misc(code, settings);

    return util::make_string("LDR", util::cond(code, settings), "SB ", Rd, ", ", addressing_mode);
}


/**
 * LDR{<cond>}SH <Rd>, <addressing_mode>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>   Specifies the destination register for the loaded value. If R15 is specified for <Rd>, the
 *        result is UNPREDICTABLE.
 * <addressing_mode>
 *        Is described in Addressing Mode 3 - Miscellaneous Loads and Stores on page A5-34. It
 *        determines the P, U, I, W, Rn and addr_mode bits of the instruction.
 *        The syntax of all forms of <addressing_mode> includes a base register <Rn>. Some
 *        forms also specify that the instruction modifies the base register value (this is known as base
 *        register writeback).
 * 
 * reference: A4-48
 */
std::string generators::arm::load::LDRSH(const u32 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 12, 15, settings);

    const std::string addressing_mode = shifters::ls_misc(code, settings);

    return util::make_string("LDR", util::cond(code, settings), "SH ", Rd, ", ", addressing_mode);
}


/**
 * LDR{<cond>}T <Rd>, <post_indexed_addressing_mode>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>   Specifies the destination register for the loaded value. If R15 is specified for <Rd>, the
 *        result is UNPREDICTABLE.
 * <post_indexed_addressing_mode>
 *        Is described in Addressing Mode 2 - Load and Store Word or Unsigned Byte on page A5-18.
 *        It determines the I, U, Rn and addr_mode bits of the instruction. Only post-indexed forms
 *        of Addressing Mode 2 are available for this instruction. These forms have P == 0 and W ==
 *        0, where P and W are bit[24] and bit[21] respectively. This instruction uses P == 0 and W
 *        == 1 instead, but the addressing mode is the same in all other respects.
 *        
 *        The syntax of all forms of <post_indexed_addressing_mode> includes a base
 *        register <Rn>. All forms also specify that the instruction modifies the base register value
 *        (this is known as base register writeback).
 * 
 * reference: A4-50
 */
std::string generators::arm::load::LDRT(const u32 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 12, 15, settings);

    const shifters::mode mode_id = shifters::identify_ls_shifter(code);
    
    switch (mode_id) {
        case shifters::mode::LS_IMM_POST:
        case shifters::mode::LS_REG_POST:
        case shifters::mode::LS_REG_SCALED_POST_LSL:
        case shifters::mode::LS_REG_SCALED_POST_LSR:
        case shifters::mode::LS_REG_SCALED_POST_ASR:
        case shifters::mode::LS_REG_SCALED_POST_ROR:
        case shifters::mode::LS_REG_SCALED_POST_RRX: break;
        default: shared::out::error("Only post-indexed addressing modes are allowed for LDRBT");
    }

    const std::string post_indexed_addressing_mode = shifters::shifter_to_string(mode_id, code, settings);

    return util::make_string("LDR", util::cond(code, settings), "T ", Rd, ", ", post_indexed_addressing_mode);
}

