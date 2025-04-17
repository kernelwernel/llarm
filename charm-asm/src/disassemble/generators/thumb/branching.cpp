#include "../generators.hpp"
#include "../util.hpp"

#include <charm/internal/shared/types.hpp>
#include <charm/internal/shared/util.hpp>

#include <string>
#include <sstream>

using namespace internal;

/** 
 * B <cond> <target_address>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The 
 *        condition field on page A3-5.
 * <target_address>
 *        Specifies the address to branch to. The branch target address is calculated by:
 *
 *        1. Shifting the 8-bit signed offset field of the instruction left by one bit.
 *        2. Sign-extending the result to 32 bits.
 *        3. Adding this to the contents of the PC (which contains the address of the branch instruction plus 4).
 * 
 *        The instruction can therefore specify a branch of approximately ±256 bytes
 * 
 * reference: A7-18
 */
std::string generators::thumb::branching::B1(const u16 code, const u32 PC) {
    const u8 cond = shared::util::bit_fetcher(code, 8, 11);

    const u8 signed_immed_8 = shared::util::bit_fetcher(code, 0, 7);

    const std::string cond_string = util::fetch_cond(cond);

    const u32 sign_extend = (signed_immed_8 << 1);
    const u32 target_address = (sign_extend + 4 + PC);

    if (target_address > 8) {
        std::stringstream ss;
        ss << std::hex << target_address;
        const std::string hex_address = ss.str();
        return util::make_instruction("B", cond_string, " #0x", hex_address);
    } else {
        return util::make_instruction("B", cond_string, " #", target_address);
    }
}


/** 
 * B  <target_address>
 * where:
 * <target_address>  
 *            Specifies the address to branch to. The branch target address is calculated by:
 *            
 *            1. Shifting the 11-bit signed offset of the instruction left one bit.
 *            2. Sign-extending the result to 32 bits.
 *            3. Adding this to the contents of the PC (which contains the address of the branch instruction plus 4). 
 * 
 *            The instruction can therefore specify a branch of approximately ±2048 bytes.
 * 
 * reference: A7-20
 */
std::string generators::thumb::branching::B2(const u16 code, const u32 PC) {
    const u16 signed_immed_11 = shared::util::bit_fetcher(code, 0, 10);

    const u32 sign_extend = (signed_immed_11 << 1);
    const u32 target_address = (sign_extend + 4 + PC);

    if (target_address > 8) {
        std::stringstream ss;
        ss << std::hex << target_address;
        const std::string hex_address = ss.str();
        return util::make_instruction("B #0x", hex_address);
    } else {
        return util::make_instruction("B #", target_address);
    }
}



/** 
 * NOTE: BL is functionally the same as BLX1, so it's referring back to that instruction for this case
 */
std::string generators::thumb::branching::BL(const u16 code, const u32 PC) {
    return BLX1(code, PC);
}





// https://stackoverflow.com/questions/70749497/how-arm-thumb-instruction-sets-blx-instruction-support-4mb-range





/** 
 * BL  <target_addr>
 * BLX  <target_addr>
 * where:
 * <target_addr> Specifies the address to branch to. The branch target address is calculated by:
 *               1. Shifting the offset_11 field of the first instruction left twelve bits.
 *               2. Sign-extending the result to 32 bits.
 *               3. Adding this to the contents of the PC (which contains the address of the first instruction plus 4).
 *               4. Adding twice the offset_11 field of the second instruction. For BLX, the 
 *                  resulting address is forced to be word-aligned by clearing bit[1]. 
 *               
 *               The instruction can therefore specify a branch of approximately ±4MB.
 * 
 * reference: A7-26
 */
std::string generators::thumb::branching::BLX1(const u16 code, const u32 PC) {
    const u16 offset_11 = shared::util::bit_fetcher(code, 0, 10);

    const u8 H = shared::util::bit_fetcher(code, 11, 12);

    u32 tmp = offset_11 << 12;

    tmp = tmp + 4 + PC;

// TODO


    return "";
}


/** 
 * BX  <Rm>
 * where:
 * <Rm> Is the register that contains the branch target address. It can be any of R0 to R15. The register 
 *      number is encoded in the instruction in H2 (most significant bit) and Rm (remaining three bits).
 * 
 * reference: A7-32
 */
std::string generators::thumb::branching::BX(const u16 code) {
    const util::reg_id Rm_id = util::identify_reg(code, 3, 6); // H2 included

    const std::string Rm = util::reg_to_string(Rm_id, false);

    return util::make_instruction("BX ", Rm);
}


/** 
 * BLX  <Rm>
 * where:
 * <Rm> Is the register that contains the branch target address. It can be any of R0 to R14. The register 
 *      number is encoded in the instruction in H2 (most significant bit) and Rm (remaining three bits). 
 *      If R15 is specified for <Rm>, the results are UNPREDICTABLE.
 * 
 * reference: A7-30
 */
std::string generators::thumb::branching::BLX2(const u16 code) {
    const util::reg_id Rm_id = util::identify_reg(code, 3, 6); // H2 included

    const std::string Rm = util::reg_to_string(Rm_id, false);

    return util::make_instruction("BLX ", Rm);
}