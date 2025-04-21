#include "../generators.hpp"
#include "../util.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"

#include <string>

using namespace internal;


/** 
 * MOV  <Rd>, #<immed_8>
 * where: 
 * <Rd> Is the destination register for the operation.
 * <immed_8> Is an 8-bit immediate value, in the range 0 to 255, to move into <Rd>.
 * 
 * reference: A7-66
 */
std::string generators::thumb::movement::MOV1(const u16 code) {
    const std::string Rd = util::reg_string(code, 8, 10);

    const u8 immed_8 = shared::util::bit_fetcher(code, 0, 7);

    return util::make_instruction("MOV ", Rd, ", #", immed_8);
}


/** 
 * MOV  <Rd>, <Rn>
 * where: 
 * <Rd> Is the destination register for the operation.
 * <Rn> Is the register containing the value to be copied.
 * 
 * reference: A7-67
 */
std::string generators::thumb::movement::MOV2(const u16 code) {
    const std::string Rd = util::reg_string(code, 0, 2);
    const std::string Rn = util::reg_string(code, 3, 5);

    return util::make_instruction("MOV ", Rd, ", ", Rn);
}


/** 
 * MOV  <Rd>, <Rm>
 * where: 
 * <Rd> Is the destination register for the operation. It can be any of R0 to R15, and its number is 
 *      encoded in the instruction in H1 (most significant bit) and Rd (remaining three bits).
 * <Rm> Is the register containing the value to be copied. It can be any of R0 to R15, and its number 
 *      is encoded in the instruction in H2 (most significant bit) and Rm (remaining three bits).
 * 
 * reference: A7-68
 */
std::string generators::thumb::movement::MOV3(const u16 code) {
    u8 Rd_bits = shared::util::bit_fetcher<u8>(code, 0, 2);
    u8 Rm_bits = shared::util::bit_fetcher<u8>(code, 3, 5);

    const bool H1 = (code & (1 << 7));
    const bool H2 = (code & (1 << 6));

    // branchless version of "if H1/H2 is true, add 8" 
    Rd_bits += (8 * H1);
    Rm_bits += (8 * H2);

    const util::reg_id Rd_id = util::identify_reg(Rd_bits);
    const util::reg_id Rm_id = util::identify_reg(Rm_bits);

    const std::string Rd = util::reg_to_string(Rd_id, false);
    const std::string Rm = util::reg_to_string(Rm_id, false);

    return util::make_instruction("MOV ", Rd, ", ", Rm);
}


/** 
 * MVN  <Rd>, <Rm>
 * where: 
 * <Rd> Is the destination register for the operation.
 * <Rm> Is the register containing the value whose one’s complement is written to <Rd>.
 * 
 * reference: A7-68
 */
std::string generators::thumb::movement::MVN(const u16 code) {
    const std::string Rd = util::reg_string(code, 0, 2);
    const std::string Rm = util::reg_string(code, 3, 5);

    return util::make_instruction("MVN ", Rd, ", ", Rm);
}