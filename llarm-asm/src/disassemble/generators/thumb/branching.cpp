#include "../generators.hpp"
#include "../util.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>
#include <llarm/shared/out.hpp>

#include <string>

using namespace internal;

/** 
 * B<cond> <target_address>
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
std::string generators::thumb::branching::B1(const u32 code, const u32 PC, const settings& settings) {
    const u8 cond = llarm::util::bit_range<u8>(code, 8, 11);

    const u8 signed_immed_8 = llarm::util::bit_range<u8>(code, 0, 7);

    const u32 sign_extend = static_cast<u32>(signed_immed_8 << 1);
    const u32 target_address = (sign_extend + 4 + PC);

    return util::make_string(
        "B", util::raw_cond(cond, settings), " #", util::hex(target_address, settings)
    );
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
std::string generators::thumb::branching::B2(const u32 code, const u32 PC, const settings& settings) {
    const u16 signed_immed_11 = llarm::util::bit_range<u16>(code, 0, 10);

    const u32 sign_extend = static_cast<u32>(signed_immed_11 << 1);
    const u32 target_address = (sign_extend + 4 + PC);

    return util::make_string(
        "B2 #", util::hex(target_address, settings)
    );
}


/** 
 * BL  <target_addr>
 * BLX  <target_addr>
 * where:
 * <target_addr> Specifies the address to branch to. The branch target address is calculated by:
 *               
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
std::string generators::thumb::branching::BL_BLX1(const u32 code, const u32 PC, const settings& settings) {
    const u16 first  = static_cast<u16>(code >> 16);
    const u16 second = static_cast<u16>(code & 0xFFFF);

    const u8 H_first  = llarm::util::bit_range<u8>(first,  11, 12);
    const u8 H_second = llarm::util::bit_range<u8>(second, 11, 12);

    // validate we have the correct pair
    if (H_first != 0b10) {
        llarm::out::error("H value of first halfword of BL/BLX1 must be valid");
    }

    const bool is_BLX1 = (H_second == 0b01);
    const bool is_BL   = (H_second == 0b11);

    if (!is_BL && !is_BLX1) {
        llarm::out::error("H value of second halfword of BL/BLX1 must hve a valid value");
    }

    // extract both offset_11 fields
    const u32 offset_high = llarm::util::bit_range<u32>(first,  0, 10);  // offset[22:12]
    const u32 offset_low  = llarm::util::bit_range<u32>(second, 0, 10);  // offset[11:1]

    // reconstruct the full offset
    const u32 raw_offset = (offset_high << 12) | (offset_low << 1);

    // sign extend from bit 22
    const i32 offset = (raw_offset & (1 << 22))
        ? static_cast<i32>(raw_offset | 0xFF800000)
        : static_cast<i32>(raw_offset);

    // base address is PC of first instruction + 4
    const u32 base_address = PC + 4;
    const u32 target_address = static_cast<u32>(static_cast<i32>(base_address) + offset);

    return util::make_string((is_BLX1 ? "BLX" : "BL"), " #", util::hex(target_address, settings));
}


/** 
 * BX  <Rm>
 * where:
 * <Rm> Is the register that contains the branch target address. It can be any of R0 to R15. The register 
 *      number is encoded in the instruction in H2 (most significant bit) and Rm (remaining three bits).
 * 
 * reference: A7-32
 */
std::string generators::thumb::branching::BX(const u32 code, const settings& settings) {
    const std::string Rm = util::reg_string(code, 3, 6, settings); // H2 included

    return util::make_string(
        "BX ", Rm
    );
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
std::string generators::thumb::branching::BLX2(const u32 code, const settings& settings) {
    const std::string Rm = util::reg_string(code, 3, 6, settings); // H2 included

    return util::make_string(
        "BLX2 ", Rm
    );
}