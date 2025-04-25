#include "../generators.hpp"
#include "../util.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"

#include <string>

using namespace internal;

/** 
 * CMN  <Rn>, <Rm>
 * where:
 * <Rn> Is the register containing the first value for comparison.
 * <Rm> Is the register containing the second value for comparison.
 * 
 * reference: A7-34
 */
std::string generators::thumb::comparison::CMN(const u16 code) {
    const std::string Rn = util::reg_string(code, 0, 2);
    const std::string Rm = util::reg_string(code, 3, 5);

    return util::make_string("CMN ", Rn, ", ", Rm);
}


/** 
 * CMP  <Rn>, #<immed_8>
 * where:
 * <Rn> Is the register containing the first value for comparison.
 * <immed_8> Is the 8-bit second value for comparison
 * 
 * reference: A7-35
 */
std::string generators::thumb::comparison::CMP1(const u16 code) {
    const std::string Rn = util::reg_string(code, 8, 10);

    const u8 immed_8 = shared::util::bit_fetcher<u8>(code, 0, 7);

    return util::make_string("CMP ", Rn, ", #", immed_8);
}


/** 
 * CMP  <Rn>, <Rm>
 * where:
 * <Rn> Is the register containing the first value for comparison.
 * <Rm> Is the register containing the second value for comparison
 * 
 * reference: A7-36
 */
std::string generators::thumb::comparison::CMP2(const u16 code) {
    const std::string Rn = util::reg_string(code, 0, 2);
    const std::string Rm = util::reg_string(code, 3, 5);

    return util::make_string("CMP ", Rn, ", ", Rm);
}


/** 
 * CMP  <Rn>, <Rm>
 * where:
 * <Rn> Is the register containing the first value. It can be any of R0 to R15. Its number is encoded 
 *      in the instruction in H1 (most significant bit) and Rn (remaining three bits).
 * <Rm> Is the register containing the second value. It can be any of R0 to R15. Its number is encoded 
 *      in the instruction in H2 (most significant bit) and Rm (remaining three bits).
 * 
 * reference: A7-37
 */
std::string generators::thumb::comparison::CMP3(const u16 code) {
    const bool H1 = (code & (1 << 7));
    const bool H2 = (code & (1 << 6));

    const std::string Rn = util::reg_string_bits(code, 0, 2, H1);
    const std::string Rm = util::reg_string_bits(code, 3, 5, H2);

    return util::make_string("CMP ", Rn, ", ", Rm);
}