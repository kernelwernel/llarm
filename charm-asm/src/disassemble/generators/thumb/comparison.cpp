#include "../generators.hpp"
#include "../util.hpp"

#include <charm/internal/shared/types.hpp>
#include <charm/internal/shared/util.hpp>

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
    const util::reg_id Rn_id = util::identify_reg(code, 0, 2);
    const util::reg_id Rm_id = util::identify_reg(code, 3, 5);

    const std::string Rn = util::reg_to_string(Rn_id, false);
    const std::string Rm = util::reg_to_string(Rm_id, false);

    return util::make_instruction("CMN ", Rn, ", ", Rm);
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
    const util::reg_id Rn_id = util::identify_reg(code, 8, 10);

    const std::string Rn = util::reg_to_string(Rn_id, false);

    const u8 immed_8 = shared::util::bit_fetcher(code, 0, 7);

    return util::make_instruction("CMP ", Rn, ", #", immed_8);
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
    const util::reg_id Rn_id = util::identify_reg(code, 0, 2);
    const util::reg_id Rm_id = util::identify_reg(code, 3, 5);

    const std::string Rn = util::reg_to_string(Rn_id, false);
    const std::string Rm = util::reg_to_string(Rm_id, false);

    return util::make_instruction("CMP ", Rn, ", ", Rm);
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
    u8 Rn_bits = shared::util::bit_fetcher<u8>(code, 0, 2);
    u8 Rm_bits = shared::util::bit_fetcher<u8>(code, 3, 5);

    const bool H1 = (code & (1 << 7));
    const bool H2 = (code & (1 << 6));

    // branchless version of "if H1/H2 is true, add 8" 
    Rn_bits += (8 * H1);
    Rm_bits += (8 * H2);

    const util::reg_id Rn_id = util::identify_reg(Rn_bits);
    const util::reg_id Rm_id = util::identify_reg(Rm_bits);

    const std::string Rn = util::reg_to_string(Rn_id, false);
    const std::string Rm = util::reg_to_string(Rm_id, false);

    return util::make_instruction("CMP ", Rn, ", ", Rm);
}