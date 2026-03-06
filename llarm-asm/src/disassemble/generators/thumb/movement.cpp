#include "../generators.hpp"
#include "../util.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>

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
std::string generators::thumb::movement::MOV1(const u32 code, const settings& settings) {
    const std::string Rd = util::reg_string(code, 8, 10, settings);

    const u8 immed_8 = llarm::util::bit_range<u8>(code, 0, 7);

    return util::make_string(
        "MOV ", Rd, ", #", util::hex(immed_8, settings)
    );
}


/** 
 * MOV  <Rd>, <Rn>
 * where: 
 * <Rd> Is the destination register for the operation.
 * <Rn> Is the register containing the value to be copied.
 * 
 * reference: A7-67
 */
std::string generators::thumb::movement::MOV2(const u32 code, const settings& settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rn = util::reg_string(code, 3, 5, settings);

    return util::make_string(
        "MOV ", Rd, ", ", Rn
    );
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
std::string generators::thumb::movement::MOV3(const u32 code, const settings& settings) {
    const bool H1 = (llarm::util::bit_fetch(code, 7));
    const bool H2 = (llarm::util::bit_fetch(code, 6));

    const std::string Rd = util::reg_string_bits(code, 0, 2, H1, settings);
    const std::string Rm = util::reg_string_bits(code, 3, 5, H2, settings);

    return util::make_string(
        "MOV ", Rd, ", ", Rm
    );
}


/** 
 * MVN  <Rd>, <Rm>
 * where: 
 * <Rd> Is the destination register for the operation.
 * <Rm> Is the register containing the value whose one’s complement is written to <Rd>.
 * 
 * reference: A7-68
 */
std::string generators::thumb::movement::MVN(const u32 code, const settings& settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rm = util::reg_string(code, 3, 5, settings);

    return util::make_string(
        "MVN ", Rd, ", ", Rm
    );
}