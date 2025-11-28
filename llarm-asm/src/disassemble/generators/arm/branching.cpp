#include "../generators.hpp"
#include "../util.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"

#include <string>

using namespace internal;


/**
 * B{L}{<cond>} <target_address>
 * where:
 * L      Causes the L bit (bit 24) in the instruction to be set to 1. The resulting instruction stores a
 *        return address in the link register (R14). If L is omitted, the L bit is 0 and the instruction
 *        simply branches without storing a return address.
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <target_address>
 *        Specifies the address to branch to. The branch target address is calculated by:
 *        
 *        1.Sign-extending the 24-bit signed (two’s complement) immediate to 32 bits.
 *        2.Shifting the result left two bits.
 *        3.Adding this to the contents of the PC, which contains the address of the branch
 *        instruction plus 8.
 *        
 *        The instruction can therefore specify a branch of approximately ±32MB.
 *
 * reference: A4-10
 */
std::string generators::arm::branching::B(const u32 code, const u32 PC, const settings settings) {
    const u32 signed_immed_24 = llarm::util::bit_range(code, 0, 23);

    const u32 target_address = util::thumb_sign_extend(signed_immed_24, 23, PC);

    return util::make_string("B", util::cond(code, settings), " #", util::hex(target_address, settings));
}


// basically the same as B above
std::string generators::arm::branching::BL(const u32 code, const u32 PC, const settings settings) {
    const u32 signed_immed_24 = llarm::util::bit_range(code, 0, 23);

    const u32 target_address = util::thumb_sign_extend(signed_immed_24, 23, PC);

    return util::make_string("BL", util::cond(code, settings), " ", util::hex(target_address, settings));
}


/**
 * BX{<cond>} <Rm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Rm>   Holds the value of the branch target address. Bit[0] of Rm is 0 to select a target ARM
 *        instruction, or 1 to select a target Thumb instruction.
 * 
 * reference: A4-19
 */
std::string generators::arm::branching::BX(const u32 code, const settings settings) {
    const std::string Rm = util::reg_string(code, 0, 3, settings);

    return util::make_string("BX", util::cond(code, settings), " ", Rm);
}


/**
 * BLX <target_addr>
 * where:
 * <target_addr> 
 *        Specifies the address of the Thumb instruction to branch to. The branch target
 *        address is calculated by:
 *        1. Sign-extending the 24-bit signed (two’s complement) immediate to 32 bits
 *        2. Shifting the result left two bits
 *        3. Setting bit[1] of the result of step 2 to the H bit
 *        4. Adding the result of step 3 to the contents of the PC, which contains the
 *           address of the branch instruction plus 8.
 *
 * The instruction can therefore specify a branch of approximately ±32MB.
 *
 * reference: A4-16
 */
std::string generators::arm::branching::BLX1(const u32 code, const u32 PC, const settings settings) {
    const u32 signed_immed_24 = llarm::util::bit_range(code, 0, 23);

    const u32 target_address = util::thumb_sign_extend(signed_immed_24, 23, PC);

    return util::make_string("BLX ", util::hex(target_address, settings));
}


/**
 * BLX{<cond>} <Rm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Rm>   Is the register containing the address of the target instruction. Bit[0] of Rm is 0 to select a
 *        target ARM instruction, or 1 to select a target Thumb instruction. If R15 is specified for
 *        <Rm>, the results are UNPREDICTABLE.
 * 
 * reference: A4-18
 */
std::string generators::arm::branching::BLX2(const u32 code, const settings settings) {
    const std::string Rm = util::reg_string(code, 0, 3, settings);
    return util::make_string("BLX", util::cond(code, settings), " ", Rm);
}