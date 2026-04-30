#include "../generators.hpp"
#include "../util.hpp"
#include "../patterns/patterns.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>

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
std::string generators::arm::multiply::MLA(const u32 code, const settings& settings) {
    const std::string Rd = util::reg_string(code, 16, 19, settings);
    const std::string Rm = util::reg_string(code, 0, 3, settings);
    const std::string Rs = util::reg_string(code, 8, 11, settings);
    const std::string Rn = util::reg_string(code, 12, 15, settings);

    const char* S = (llarm::util::bit_fetch(code, 20) ? "S" : "");

    const bool suf = settings.cond_always_suffix;

    return util::make_string("MLA", (suf ? S : ""), util::cond(code, settings), (suf ? "" : S), " ", Rd, ", ", Rm, ", ", Rs, ", ", Rn);
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
std::string generators::arm::multiply::MUL(const u32 code, const settings& settings) {
    const std::string Rd = util::reg_string(code, 16, 19, settings);
    const std::string Rm = util::reg_string(code, 0, 3, settings);
    const std::string Rs = util::reg_string(code, 8, 11, settings);

    const char* S = (llarm::util::bit_fetch(code, 20) ? "S" : "");

    const bool suf = settings.cond_always_suffix;

    return util::make_string("MUL", (suf ? S : ""), util::cond(code, settings), (suf ? "" : S), " ", Rd, ", ", Rm, ", ", Rs);
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
std::string generators::arm::multiply::SMLAL(const u32 code, const settings& settings) {
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
std::string generators::arm::multiply::SMULL(const u32 code, const settings& settings) {
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
std::string generators::arm::multiply::UMLAL(const u32 code, const settings& settings) {
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
std::string generators::arm::multiply::UMULL(const u32 code, const settings& settings) {
    return patterns::mul_Hi_Lo(code, "UMULL", settings);
}


/**
 * SMLAD{X}{<cond>} <Rd>, <Rm>, <Rs>, <Rn>
 * where:
 * Sets the X bit of the instruction to 1, and the multiplications are bottom x top and top x
 * bottom.
 * X
 * If the X is omitted, sets the X bit to 0, and the multiplications are bottom x bottom and top
 * x top.
 * <cond>Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>Specifies the destination register.
 * <Rm>Specifies the register that contains the first operand.
 * <Rs>Specifies the register that contains the second operand.
 * <Rn>Specifies the register that contains the accumulate operand.
 */
std::string generators::arm::multiply::SMLAD(const u32 code, const settings& settings) {
    return patterns::mul_Rd_Rm_Rs_Rn(code, "SMLAD", "X", settings);
}


/**
 * SMLALD{X}{<cond>} <RdLo>, <RdHi>, <Rm>, <Rs>
 * where:
 * Sets the X bit of the instruction to 1, and the multiplications are bottom x top and top x
 * bottom.
 * X If the X is omitted, sets the X bit to 0, and the multiplications are bottom x bottom and top
 * x top.
 * <cond>Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <RdLo>Supplies the lower 32 bits of the 64-bit accumulate value to be added to the product, and is
 * the destination register for the lower 32 bits of the 64-bit result.
 * <RdHi>Supplies the upper 32 bits of the 64-bit accumulate value to be added to the product, and is
 * the destination register for the upper 32 bits of the 64-bit result.
 * <Rm>Specifies the register that contains the first multiply operand.
 * <Rs>Specifies the register that contains the second multiply operand.
 */
std::string generators::arm::multiply::SMLALD(const u32 code, const settings& settings) {
    return patterns::mul_RdLo_RdHi_Rm_Rs_X(code, "SMLALD", settings);
}


/**
 * SMLSD{X}{<cond>} <Rd>, <Rm>, <Rs>, <Rn>
 * where:
 * Sets the X bit of the instruction to 1, and the multiplications are bottom x top and top x
 * bottom.
 * X
 * If the X is omitted, sets the X bit to 0, and the multiplications are bottom x bottom and top
 * x top.
 * <cond>Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>Specifies the destination register.
 * <Rm>Specifies the register that contains the first multiply operand.
 * <Rs>Specifies the register that contains the second multiply operand.
 * <Rn>Specifies the register that contains the accumulate operand.
 */
std::string generators::arm::multiply::SMLSD(const u32 code, const settings& settings) {
    return patterns::mul_Rd_Rm_Rs_Rn(code, "SMLSD", "X", settings);
}


/**
 * SMLSD{X}{<cond>} <Rd>, <Rm>, <Rs>, <Rn>
 * where:
 * Sets the X bit of the instruction to 1, and the multiplications are bottom x top and top x
 * bottom.
 * X
 * If the X is omitted, sets the X bit to 0, and the multiplications are bottom x bottom and top
 * x top.
 * <cond>Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>Specifies the destination register.
 * <Rm>Specifies the register that contains the first multiply operand.
 * <Rs>Specifies the register that contains the second multiply operand.
 * <Rn>Specifies the register that contains the accumulate operand.
 */
std::string generators::arm::multiply::SMLSLD(const u32 code, const settings& settings) {
    return patterns::mul_RdLo_RdHi_Rm_Rs_X(code, "SMLSLD", settings);
}


/**
 * SMMLA{R}{<cond>} <Rd>, <Rm>, <Rs>, <Rn>
 * where:
 * Sets the R bit of the instruction to 1. The multiplication is rounded.
 * R
 * If the R is omitted, sets the R bit to 0. The multiplication is truncated.
 * <cond>Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>Specifies the destination register.
 * <Rm>Specifies the register that contains the first multiply operand.
 * <Rs>Specifies the register that contains the second multiply operand.
 * <Rn>Specifies the register that contains the accumulate operand.
 */
std::string generators::arm::multiply::SMMLA(const u32 code, const settings& settings) {
    return patterns::mul_Rd_Rm_Rs_Rn(code, "SMMLA", "R", settings);
}


/**
 * SMMLS{R}{<cond>} <Rd>, <Rm>, <Rs>, <Rn>
 * where:
 * Sets the R bit of the instruction to 1. The multiplication is rounded.
 * R
 * If the R is omitted, sets the R bit to 0. The multiplication is truncated.
 * <cond>Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>Specifies the destination register.
 * <Rm>Specifies the register that contains the first multiply operand.
 * <Rs>Specifies the register that contains the second multiply operand.
 * <Rn>Specifies the register that contains the accumulate operand.
 */
std::string generators::arm::multiply::SMMLS(const u32 code, const settings& settings) {
    return patterns::mul_Rd_Rm_Rs_Rn(code, "SMMLS", "R", settings);
}


/**
 * SMMUL{R}{<cond>} <Rd>, <Rm>, <Rs>
 * where:
 * Sets the R bit of the instruction to 1. The multiplication is rounded.
 * R If the R is omitted, sets the R bit to 0. The multiplication is truncated.
 * <cond>Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>Specifies the destination register.
 * <Rm>Specifies the register that contains the first multiply operand.
 * <Rs>Specifies the register that contains the second multiply operand.
 */
std::string generators::arm::multiply::SMMUL(const u32 code, const settings& settings) {
    return patterns::mul_Rd_Rm_Rs_X(code, "SMMUL", "R", settings);
}


/**
 * SMUAD{X}{<cond>} <Rd>, <Rm>, <Rs>
 * where:
 * Sets the X bit of the instruction to 1, and the multiplications are bottom x top and top x
 * bottom.
 * X
 * If the X is omitted, sets the X bit to 0, and the multiplications are bottom x bottom and top
 * x top.
 * <cond>Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>Specifies the destination register.
 * <Rm>Specifies the register that contains the first operand.
 * <Rs>Specifies the register that contains the second operand.
 */
std::string generators::arm::multiply::SMUAD(const u32 code, const settings& settings) {
    return patterns::mul_Rd_Rm_Rs_X(code, "SMUAD", "X", settings);
}



/**
 * SMUSD{X}{<cond>} <Rd>, <Rm>, <Rs>
 * where:
 * Sets the X bit of the instruction to 1. The multiplications are bottom x top and top x bottom.
 * X
 * If the X is omitted, sets the X bit to 0. The multiplications are bottom x bottom and top x top.
 * <cond>Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>Specifies the destination register.
 * <Rm>Specifies the register that contains the first multiply operand.
 * <Rs>Specifies the register that contains the second multiply operand.
 */
std::string generators::arm::multiply::SMUSD(const u32 code, const settings& settings) {
    return patterns::mul_Rd_Rm_Rs_X(code, "SMUSD", "X", settings);
}


/**
 * UMAAL{<cond>} <RdLo>, <RdHi>, <Rm>, <Rs>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <RdLo> Supplies one of the 32-bit values to be added to the product of <Rm> and <Rs>, and is the
 * destination register for the lower 32 bits of the result.
 * <RdHi> Supplies the other 32-bit value to be added to the product of <Rm> and <Rs>, and is the
 * destination register for the upper 32 bits of the result.
 * <Rm> Holds the unsigned value to be multiplied with the value of <Rs>.
 * <Rs> Holds the unsigned value to be multiplied with the value of <Rm>.
 */
std::string generators::arm::multiply::UMAAL(const u32 code, const settings& settings) {
    return patterns::mul_RdLo_RdHi_Rm_Rs(code, "UMAAL", settings);
}