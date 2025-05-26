#include "../generators.hpp"
#include "../util.hpp"

#include "llarm-asm/src/disassemble/generators/arm/shifter_operands/shifters.hpp"
#include "shared/types.hpp"
#include "shared/util.hpp"

#include <string>

using namespace internal;

/**
 * CDP{<cond>} <coproc>, <opcode_1>, <CRd>, <CRn>, <CRm>, <opcode_2>
 * CDP2 <coproc>, <opcode_1>, <CRd>, <CRn>, <CRm>, <opcode_2>
 * where:
 * <cond>     Is the condition under which the instruction is executed. The conditions are defined
 *            in The condition field on page A3-5. If <cond> is omitted, the AL (always)
 *            condition is used.
 * 
 * CDP2       Causes the condition field of the instruction to be set to 0b1111. This provides
 *            additional opcode space for coprocessor designers. The resulting instructions can
 *            only be executed unconditionally.
 *
 * <coproc>   Specifies the name of the coprocessor, and causes the corresponding coprocessor
 *            number to be placed in the cp_num field of the instruction. The standard generic
 *            coprocessor names are p0, p1, ..., p15.
 *
 * <opcode_1> Specifies (in a coprocessor-specific manner) which coprocessor operation is to be
 *            performed.
 * <CRd>      Specifies the destination coprocessor register for the instruction.
 * <CRn>      Specifies the coprocessor register that contains the first operand for the instruction.
 * <CRm>      Specifies the coprocessor register that contains the second operand for the
 *            instruction.
 *
 * <opcode_2> Specifies (in a coprocessor-specific manner) which coprocessor operation is to be
 *            performed.
 * 
 * reference: A4-20
 */
std::string generators::arm::coprocessor::CDP(const u32 code, const settings settings) {
    const u8 cond = shared::util::bit_range<u8>(code, 28, 31);
    const std::string suffix = ((cond == 0b1111) ? "2" : util::raw_cond(cond, settings));

    const std::string coproc = util::reg_string(code, 8, 11, settings, util::prefix::P);

    const u8 opcode_1 = shared::util::bit_range<u8>(code, 20, 23);
    const u8 opcode_2 = shared::util::bit_range<u8>(code, 5, 7);

    const std::string CRd = util::reg_string(code, 12, 15, settings, util::prefix::C);
    const std::string CRn = util::reg_string(code, 16, 19, settings, util::prefix::C);
    const std::string CRm = util::reg_string(code, 0, 3, settings, util::prefix::C);

    return util::make_string("CDP", suffix, " ", coproc, ", #", opcode_1, ", ", CRd, ", ", CRn, ", ", CRm, ", #", opcode_2);
}


/**
 * LDC{<cond>}{L} <coproc>, <CRd>, <addressing_mode>
 * LDC2{L} <coproc>, <CRd>, <addressing_mode>
 * where:
 * <cond>   Is the condition under which the instruction is executed. The conditions are defined in The
 *          condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * LDC2     Causes the condition field of the instruction to be set to 0b1111. This provides additional
 *          opcode space for coprocessor designers. The resulting instructions can only be executed
 *          unconditionally.
 * L        Sets the N bit (bit[22]) in the instruction to 1 and specifies a long load (for example,
 *          double-precision instead of single-precision data transfer). If L is omitted, the N bit is 0 and
 *          the instruction specifies a short load.
 * <coproc> Specifies the name of the coprocessor, and causes the corresponding coprocessor number to
 *          be placed in the cp_num field of the instruction. The standard generic coprocessor names
 *          are p0, p1, ..., p15.
 * <CRd>    Specifies the coprocessor destination register of the instruction.
 * <addressing_mode>
 *          Is described in Addressing Mode 5 - Load and Store Coprocessor on page A5-56. It
 *          determines the P, U, Rn, W and 8_bit_word_offset bits of the instruction.
 *          The syntax of all forms of <addressing_mode> includes a base register <Rn>. Some
 *          forms also specify that the instruction modifies the base register value (this is known as base
 *          register writeback).
 * 
 * reference: A4-28
 */
std::string generators::arm::coprocessor::LDC(const u32 code, const settings settings) {
    const u8 cond = shared::util::bit_range<u8>(code, 28, 31);
    const std::string suffix = ((cond == 0b1111) ? "2" : util::raw_cond(cond, settings));

    const char* L = (shared::util::bit_fetch(code, 22) ? "L" : "");

    const std::string coproc = util::reg_string(code, 8, 11, settings, util::prefix::P);

    const std::string CRd = util::reg_string(code, 12, 15, settings, util::prefix::C);

    const std::string addressing_mode = shifters::ls_coproc(code, settings);

    return util::make_string("LDC", suffix, L, " ", coproc, ", ", CRd, ", ", addressing_mode);
}


/**
 * MCR{<cond>} <coproc>, <opcode_1>, <Rd>, <CRn>, <CRm>{, <opcode_2>}
 * MCR2 <coproc>, <opcode_1>, <Rd>, <CRn>, <CRm>{, <opcode_2>}
 * where:
 * <cond>     Is the condition under which the instruction is executed. The conditions are defined in The
 *            condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * MCR2       Causes the condition field of the instruction to be set to 0b1111. This provides additional
 *            opcode space for coprocessor designers. The resulting instructions can only be executed
 *            unconditionally.
 * <coproc>   Specifies the name of the coprocessor, and causes the corresponding coprocessor number to
 *            be placed in the cp_num field of the instruction. The standard generic coprocessor names
 *            are p0, p1, ..., p15.
 * <opcode_1> Is a coprocessor-specific opcode.
 * <Rd>       Is the ARM register whose value is transferred to the coprocessor. If R15 is specified for
 *            <Rd>, the result is UNPREDICTABLE.
 * <CRn>      Is the destination coprocessor register.
 * <CRm>      Is an additional destination or source coprocessor register.
 * <opcode_2> Is a coprocessor-specific opcode. If it is omitted, <opcode_2> is assumed to be 0.
 * 
 * reference: A4-52
 */
std::string generators::arm::coprocessor::MCR(const u32 code, const settings settings) {
    const u8 cond = shared::util::bit_range<u8>(code, 28, 31);
    const std::string suffix = ((cond == 0b1111) ? "2" : util::raw_cond(cond, settings));

    const std::string coproc = util::reg_string(code, 8, 11, settings, util::prefix::P);

    const u8 opcode_1 = shared::util::bit_range<u8>(code, 21, 23);
    const u8 opcode_2 = shared::util::bit_range<u8>(code, 5, 7);

    const std::string Rd = util::reg_string(code, 12, 15, settings);
    const std::string CRn = util::reg_string(code, 16, 19, settings, util::prefix::C);
    const std::string CRm = util::reg_string(code, 0, 3, settings, util::prefix::C);

    return util::make_string("MCR", suffix, " ", coproc, ", #", opcode_1, ", ", Rd, ", ", CRn, ", ", CRm, ", #", opcode_2);
}


/**
 * MRC{<cond>} <coproc>, <opcode_1>, <Rd>, <CRn>, <CRm>{, <opcode_2>}
 * MRC2 <coproc>, <opcode_1>, <Rd>, <CRn>, <CRm>{, <opcode_2>}
 * where:
 * <cond>     Is the condition under which the instruction is executed. The conditions are defined
 *            in The condition field on page A3-5. If <cond> is omitted, the AL (always)
 *            condition is used.
 * MRC2       Causes the condition field of the instruction to be set to 0b1111. This provides
 *            additional opcode space for coprocessor designers. The resulting instructions can
 *            only be executed unconditionally.
 * <coproc>   Specifies the name of the coprocessor, and causes the corresponding coprocessor
 *            number to be placed in the cp_num field of the instruction. The standard generic
 *            coprocessor names are p0, p1, ..., p15.
 * <opcode_1> Is a coprocessor-specific opcode.
 * <Rd>       Specifies the destination ARM register for the instruction. If R15 is specified for
 *            <Rd>, the condition code flags are updated instead of a general-purpose register.
 * <CRn>      Specifies the coprocessor register that contains the first operand for the instruction.
 * <CRm>      Is an additional coprocessor source or destination register.
 * <opcode_2> Is a coprocessor-specific opcode. If it is omitted, <opcode_2> is assumed to be 0.
 * 
 * reference: A4-58
 */
std::string generators::arm::coprocessor::MRC(const u32 code, const settings settings) {
    const u8 cond = shared::util::bit_range<u8>(code, 28, 31);
    const std::string suffix = ((cond == 0b1111) ? "2" : util::raw_cond(cond, settings));

    const std::string coproc = util::reg_string(code, 8, 11, settings, util::prefix::P);

    const u8 opcode_1 = shared::util::bit_range<u8>(code, 21, 23);
    const u8 opcode_2 = shared::util::bit_range<u8>(code, 5, 7);

    const std::string Rd = util::reg_string(code, 12, 15, settings);
    const std::string CRn = util::reg_string(code, 16, 19, settings, util::prefix::C);
    const std::string CRm = util::reg_string(code, 0, 3, settings, util::prefix::C);

    return util::make_string("MRC", suffix, " ", coproc, ", #", opcode_1, ", ", Rd, ", ", CRn, ", ", CRm, ", #", opcode_2);
}


/**
 * STC{<cond>}{L} <coproc>, <CRd>, <addressing_mode>
 * STC2{L} <coproc>, <CRd>, <addressing_mode>
 * where:
 * <cond>   Is the condition under which the instruction is executed. The conditions are defined in The
 *          condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * STC2     Causes the condition field of the instruction to be set to 0b1111. This provides additional
 *          opcode space for coprocessor designers. The resulting instructions can only be executed
 *          unconditionally.
 * L        Sets the N bit (bit[22]) in the instruction to 1 and specifies a long store (for example,
 *          double-precision instead of single-precision data transfer). If L is omitted, the N bit is 0 and
 *          the instruction specifies a short store.
 * <coproc> Specifies the name of the coprocessor, and causes the corresponding coprocessor number to
 *          be placed in the cp_num field of the instruction. The standard generic coprocessor names
 *          are p0, p1, ..., p15.
 * <CRd>    Specifies the coprocessor source register of the instruction.
 * <addressing_mode>
 *          Is described in Addressing Mode 5 - Load and Store Coprocessor on page A5-56. It
 *          determines the P, U, Rn, W and 8_bit_word_offset bits of the instruction.
 *          The syntax of all forms of <addressing_mode> includes a base register <Rn>. Some
 *          forms also specify that the instruction modifies the base register value (this is known as base
 *          register writeback).
 * 
 * reference: A4-82
 */
std::string generators::arm::coprocessor::STC(const u32 code, const settings settings) {
    const u8 cond = shared::util::bit_range<u8>(code, 28, 31);
    const std::string suffix = ((cond == 0b1111) ? "2" : util::raw_cond(cond, settings));

    const char* L = (shared::util::bit_fetch(code, 22) ? "L" : "");

    const std::string coproc = util::reg_string(code, 8, 11, settings, util::prefix::P);

    const std::string CRd = util::reg_string(code, 12, 15, settings, util::prefix::C);

    const std::string addressing_mode = shifters::ls_coproc(code, settings);

    return util::make_string("STC", suffix, L, " ", coproc, ", ", CRd, ", ", addressing_mode);
}