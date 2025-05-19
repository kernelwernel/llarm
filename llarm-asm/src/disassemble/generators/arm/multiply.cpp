#include "../generators.hpp"
#include "../util.hpp"
#include "../patterns/patterns.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"

#include <string>

using namespace internal;


/**
 * MLA{<cond>}{S} <Rd>, <Rm>, <Rs>, <Rn>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * S      Causes the S bit (bit[20]) in the instruction to be set to 1 and specifies that the instruction
 *        updates the CPSR by setting the N and Z flags according to the result of the
 *        multiply-accumulate. If S is omitted, the S bit of the instruction is set to 0 and the entire
 *        CPSR is unaffected by the instruction.
 * <Rd>   Specifies the destination register of the instruction.
 * <Rm>   Holds the value to be multiplied with the value of <Rs>.
 * <Rs>   Holds the value to be multiplied with the value of <Rm>.
 * <Rn>   Contains the value that is added to the product of <Rs> and <Rm>.

 * reference: A4-54
 */
std::string generators::arm::multiply::MLA(const u32 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 16, 19, settings);
    const std::string Rm = util::reg_string(code, 0, 3, settings);
    const std::string Rs = util::reg_string(code, 8, 11, settings);
    const std::string Rn = util::reg_string(code, 12, 15, settings);

    const char* S = (shared::util::bit_fetch(code, 20) ? "S" : "");

    return util::make_string("MLA", util::cond(code), S, " ", Rd, ", ", Rm, ", ", Rs, ", ", Rn);
}


/**
 * MUL{<cond>}{S} <Rd>, <Rm>, <Rs>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * S      Causes the S bit (bit[20]) in the instruction to be set to 1 and specifies that the instruction
 *        updates the CPSR by setting the N and Z flags according to the result of the multiplication.
 *        If S is omitted, the S bit of the instruction is set to 0 and the entire CPSR is unaffected by
 *        the instruction.
 * <Rd>   Specifies the destination register for the instruction.
 * <Rm>   Specifies the register that contains the first value to be multiplied.
 * <Rs>   Holds the value to be multiplied with the value of <Rm>.
 *
 * reference: A4-66
 */
std::string generators::arm::multiply::MUL(const u32 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 16, 19, settings);
    const std::string Rm = util::reg_string(code, 0, 3, settings);
    const std::string Rs = util::reg_string(code, 8, 11, settings);

    const char* S = (shared::util::bit_fetch(code, 20) ? "S" : "");

    return util::make_string("MUL", util::cond(code), S, " ", Rd, ", ", Rm, ", ", Rs);
}


/**
 * SMLAL{<cond>}{S} <RdLo>, <RdHi>, <Rm>, <Rs>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * S      Causes the S bit (bit[20]) in the instruction to be set to 1 and specifies that the instruction
 *        updates the CPSR by setting the N and Z flags according to the result of the
 *        multiply-accumulate. If S is omitted, the S bit of the instruction is set to 0 and the entire
 *        CPSR is unaffected by the instruction.
 * <RdLo> Supplies the lower 32 bits of the value to be added to the product of <Rm> and <Rs>, and
 *        is the destination register for the lower 32 bits of the result.
 * <RdHi> Supplies the upper 32 bits of the value to be added to the product of <Rm> and <Rs>, and
 *        is the destination register for the upper 32 bits of the result.
 * <Rm>   Holds the signed value to be multiplied with the value of <Rs>.
 * <Rs>   Holds the signed value to be multiplied with the value of <Rm>.
 * 
 * reference: A4-78
 */
std::string generators::arm::multiply::SMLAL(const u32 code, const settings settings) {
    return patterns::mul_Hi_Lo(code, "SMLAL", settings);
}


/**
 * SMULL{<cond>}{S}
 * <RdLo>, <RdHi>, <Rm>, <Rs>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * S      Causes the S bit (bit[20]) in the instruction to be set to 1 and specifies that the instruction
 *        updates the CPSR by setting the N and Z flags according to the result of the multiplication.
 *        If S is omitted, the S bit of the instruction is set to 0 and the entire CPSR is unaffected by
 *        the instruction.
 * <RdLo> Stores the lower 32 bits of the result.
 * <RdHi> Stores the upper 32 bits of the result.
 * <Rm>   Holds the signed value to be multiplied with the value of <Rs>.
 * <Rs>   Holds the signed value to be multiplied with the value of <Rm>.
 *
 * reference: A4-80
 */
std::string generators::arm::multiply::SMULL(const u32 code, const settings settings) {
    return patterns::mul_Hi_Lo(code, "SMULL", settings);
}


/**
 * UMLAL{<cond>}{S} <RdLo>, <RdHi>, <Rm>, <Rs>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * S      Causes the S bit (bit[20]) in the instruction to be set to 1 and specifies that the instruction
 *        updates the CPSR by setting the N and Z flags according to the result of the
 *        multiply-accumulate. If S is omitted, the S bit of the instruction is set to 0 and the entire
 *        CPSR is unaffected by the instruction.
 * <RdLo> Supplies the lower 32 bits of the value to be added to the product of <Rm> and <Rs>, and
 *        is the destination register for the lower 32 bits of the result.
 * <RdHi> Supplies the upper 32 bits of the value to be added to the product of <Rm> and <Rs>, and
 *        is the destination register for the upper 32 bits of the result.
 * <Rm>   Holds the signed value to be multiplied with the value of <Rs>.
 * <Rs>   Holds the signed value to be multiplied with the value of <Rm>.
 * 
 * reference: A4-109
 */
std::string generators::arm::multiply::UMLAL(const u32 code, const settings settings) {
    return patterns::mul_Hi_Lo(code, "UMLAL", settings);
}


/**
 * UMULL{<cond>}{S} <RdLo>, <RdHi>, <Rm>, <Rs>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * S      Causes the S bit (bit[20]) in the instruction to be set to 1 and specifies that the instruction
 *        updates the CPSR by setting the N and Z flags according to the result of the multiplication.
 *        If S is omitted, the S bit of the instruction is set to 0 and the entire CPSR is unaffected by
 *        the instruction.
 * <RdLo> Stores the lower 32 bits of the result.
 * <RdHi> Stores the upper 32 bits of the result.
 * <Rm>   Holds the signed value to be multiplied with the value of <Rs>.
 * <Rs>   Holds the signed value to be multiplied with the value of <Rm>.
 *
 * reference: A4-111
 */
std::string generators::arm::multiply::UMULL(const u32 code, const settings settings) {
    return patterns::mul_Hi_Lo(code, "UMULL", settings);
}