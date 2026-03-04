#include "../generators.hpp"
#include "../util.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>

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
std::string generators::thumb::comparison::CMN(const u32 code, const settings settings) {
    const std::string Rn = util::reg_string(code, 0, 2, settings);
    const std::string Rm = util::reg_string(code, 3, 5, settings);

    return util::make_string(
        "CMN ", Rn, ", ", Rm
    );
}


/** 
 * CMP  <Rn>, #<immed_8>
 * where:
 * <Rn> Is the register containing the first value for comparison.
 * <immed_8> Is the 8-bit second value for comparison
 * 
 * reference: A7-35
 */
std::string generators::thumb::comparison::CMP1(const u32 code, const settings settings) {
    const std::string Rn = util::reg_string(code, 8, 10, settings);

    const u8 immed_8 = llarm::util::bit_range<u8>(code, 0, 7);

    return util::make_string(
        "CMP ", Rn, ", #", util::hex(immed_8, settings)
    );
}


/** 
 * CMP  <Rn>, <Rm>
 * where:
 * <Rn> Is the register containing the first value for comparison.
 * <Rm> Is the register containing the second value for comparison
 * 
 * reference: A7-36
 */
std::string generators::thumb::comparison::CMP2(const u32 code, const settings settings) {
    const std::string Rn = util::reg_string(code, 0, 2, settings);
    const std::string Rm = util::reg_string(code, 3, 5, settings);

    return util::make_string(
        "CMP ", Rn, ", ", Rm
    );
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
std::string generators::thumb::comparison::CMP3(const u32 code, const settings settings) {
    const bool H1 = (llarm::util::bit_fetch(code, 7));
    const bool H2 = (llarm::util::bit_fetch(code, 6));

    const std::string Rn = util::reg_string_bits(code, 0, 2, H1, settings);
    const std::string Rm = util::reg_string_bits(code, 3, 5, H2, settings);

    return util::make_string(
        "CMP ", Rn, ", ", Rm
    );
}