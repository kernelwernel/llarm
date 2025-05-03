#include "../generators.hpp"
#include "../util.hpp"
#include "../patterns/patterns.hpp"
#include "shifter_operands/shifters.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"
#include "shared/out.hpp"

#include <string>

using namespace internal;


/**
 * FABSD{<cond>} <Dd>, <Dm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Dd>   Specifies the destination register.
 * <Dm>   Specifies the source register.
 * 
 * reference: C4-2
 */
std::string generators::arm::vfp::FABSD(const u32 code) {
    return patterns::vfp_Dd_Dm(code, "FABSD");
}


/**
 * FABSS{<cond>} <Sd>, <Sm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Sd>   Specifies the destination register. Its number is encoded as Fd (top 4 bits) and D (bottom bit).
 * <Sm>   Specifies the source register. Its number is encoded as Fm (top 4 bits) and M (bottom bit).

 * reference: C4-4
 */
std::string generators::arm::vfp::FABSS(const u32 code) {
    return patterns::vfp_Sd_Sm(code, "FABSS");
}


/**
 * FADDD{<cond>} <Dd>, <Dn>, <Dm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Dd>   Specifies the destination register.
 * <Dn>   Specifies the register that contains the first operand for the addition.
 * <Dm>   Specifies the register that contains the second operand for the addition.
 * 
 * reference: C4-6
 */
std::string generators::arm::vfp::FADDD(const u32 code) {
    return patterns::vfp_Dd_Dn_Dm(code, "FADDD");
}


/**
 * FADDS{<cond>} <Sd>, <Sn>, <Sm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Sd>   Specifies the destination register. Its number is encoded as Fd (top 4 bits) and D (bottom bit).
 * <Sn>   Specifies the register that contains the first operand for the addition. Its number is encoded
 *        as Fn (top 4 bits) and N (bottom bit).
 * <Sm>   Specifies the register that contains the second operand for the addition. Its number is
 *        encoded as Fm (top 4 bits) and M (bottom bit).
 * 
 * reference: C4-8
 */
std::string generators::arm::vfp::FADDS(const u32 code) {
    return patterns::vfp_Sd_Sn_Sm(code, "FADDS");
}


/**
 * FCMPD{<cond>} <Dd>, <Dm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Dd>   Specifies the register which contains the first operand for the comparison.
 * <Dm>   Specifies the register which contains the second operand for the comparison.
 *
 * reference: C4-10
 */
std::string generators::arm::vfp::FCMPD(const u32 code) {
    return patterns::vfp_Dd_Dm(code, "FCMPD");
}


/**
 * FCMPED{<cond>} <Dd>, <Dm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Dd>   Specifies the register which contains the first operand for the comparison.
 * <Dm>   Specifies the register which contains the second operand for the comparison.
 *
 * reference: C4-12
 */
std::string generators::arm::vfp::FCMPED(const u32 code) {
    return patterns::vfp_Dd_Dm(code, "FCMPED");
}


/**
 * FCMPES{<cond>} <Sd>, <Sm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Sd>   Specifies the register which contains the first operand for the comparison. The register
 *        number is encoded as Fd (top 4 bits) and D (bottom bit).
 * <Sm>   Specifies the register which contains the second operand for the comparison. The register
 *        number is encoded as Fm (top 4 bits) and M (bottom bit).

 * reference: C4-14
 */
std::string generators::arm::vfp::FCMPES(const u32 code) {
    return patterns::vfp_Sd_Sm(code, "FCMPES");
}


/**
 * FCMPEZD{<cond>} <Dd>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Dd>   Specifies the register which contains the first operand for the comparison.
 *
 * reference: C4-16
 */
std::string generators::arm::vfp::FCMPEZD(const u32 code) {
    return patterns::vfp_Dd(code, "FCMPEZD");
}


/**
 * FCMPEZS{<cond>} <Sd>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Sd>   Specifies the register which contains the first operand for the comparison. The register
 *        number is encoded as Fd (top 4 bits) and D (bottom bit).
 * 
 * reference: C4-18
 */
std::string generators::arm::vfp::FCMPEZS(const u32 code) {
    return patterns::vfp_Sd(code, "FCMPEZS"); 
}


/**
 * FCMPS{<cond>} <Sd>, <Sm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Sd>   Specifies the register which contains the first operand for the comparison. The register
 *        number is encoded as Fd (top 4 bits) and D (bottom bit).
 * <Sm>   Specifies the register which contains the second operand for the comparison. The register
 *        number is encoded as Fm (top 4 bits) and M (bottom bit).
 * 
 * reference: C4-20
 */
std::string generators::arm::vfp::FCMPS(const u32 code) {
    return patterns::vfp_Sd_Sm(code, "FCMPS");
}


/**
 * FCMPZD{<cond>} <Dd>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Dd>   Specifies the register which contains the first operand for the comparison.
 *
 * reference: C4-22
 */
std::string generators::arm::vfp::FCMPZD(const u32 code) {
    return patterns::vfp_Dd(code, "FCMPZD");
}


/**
 * FCMPZS{<cond>} <Sd>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Sd>   Specifies the register which contains the first operand for the comparison. The register
 *        number is encoded as Fd (top 4 bits) and D (bottom bit).
 * 
 * reference: C4-24
 */
std::string generators::arm::vfp::FCMPZS(const u32 code) {
    return patterns::vfp_Sd(code, "FCMPZS");
}


/**
 * FCPYD{<cond>} <Dd>, <Dm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Dd> Specifies the destination register.
 * <Dm> Specifies the source register.
 * 
 * reference: C4-26
 */
std::string generators::arm::vfp::FCPYD(const u32 code) {
    return patterns::vfp_Dd_Dm(code, "FCPYD");
}


/**
 * FCPYS{<cond>} <Sd>, <Sm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Sd>   Specifies the destination register. The register number is encoded as Fd (top 4 bits) and D (bottom bit).
 * <Sm>   Specifies the source register. The register number is encoded as Fm (top 4 bits) and M (bottom bit).
 * 
 * reference: C4-28
 */
std::string generators::arm::vfp::FCPYS(const u32 code) {
    return patterns::vfp_Sd_Sm(code, "FCPYS");
}


/**
 * FCVTDS{<cond>} <Dd>, <Sm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Dd>   Specifies the destination register.
 * <Sm>   Specifies the source register. The register number is encoded as Fm (top 4 bits) and M (bottom bit).
 * 
 * reference: C4-30
 */
std::string generators::arm::vfp::FCVTDS(const u32 code) {
    return patterns::vfp_Dd_Sm(code, "FCVTDS");
}


/**
 * FCVTSD{<cond>} <Sd>, <Dm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Sd>   Specifies the destination register. The register number is encoded as Fd (top 4 bits) and D (bottom bit).
 * <Dm>   Specifies the source register
 * 
 * reference: C4-31
 */
std::string generators::arm::vfp::FCVTSD(const u32 code) {
    const bool D = (code & (1 << 22));

    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D);
    const std::string Dm = util::reg_string(code, 0, 3, util::prefix::D);

    return util::make_string("FCVTSD", util::cond(code), " ", Sd, ", ", Dm);
}


/**
 * FDIVD{<cond>} <Dd>, <Dn>, <Dm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Dd>   Specifies the destination register.
 * <Dn>   Specifies the register that contains the first operand for the division.
 * <Dm>   Specifies the register that contains the second operand for the division.
 * 
 * reference: C4-32
 */
std::string generators::arm::vfp::FDIVD(const u32 code) {
    return patterns::vfp_Dd_Dn_Dm(code, "FDIVD");
}


/**
 * FDIVS{<cond>} <Sd>, <Sn>, <Sm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Sd>   Specifies the destination register. The register number is encoded as Fd (top 4 bits) and D (bottom bit).
 * <Sn>   Specifies the register that contains the first operand for the division. The register number is
 *        encoded as Fn (top 4 bits) and N (bottom bit).
 * <Sm>   Specifies the register that contains the second operand for the division. The register number
 *        is encoded as Fm (top 4 bits) and M (bottom bit).
 *
 * reference: C4-34
 */
std::string generators::arm::vfp::FDIVS(const u32 code) {
    return patterns::vfp_Sd_Sn_Sm(code, "FDIVS");
}


/**
 * FLDD{<cond>} <Dd>, [<Rn>{, #+/-(<offset>*4)}]
 * where:
 * <cond>   Is the condition under which the instruction is executed. The conditions are defined in The
 *          condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Dd>     Specifies the destination register.
 * <Rn>     Specifies the register holding the base address for the transfer.
 * <offset> Specifies an offset to be multiplied by 4, then added to the base address (if U == 1) or
 *          subtracted from it (if U == 0) in order to form the actual address of the transfer. If this offset
 *          is omitted, it defaults to +0.
 * 
 * reference: C4-36
 */
std::string generators::arm::vfp::FLDD(const u32 code) {
    const std::string Dd = util::reg_string(code, 12, 15, util::prefix::D);
    const std::string Rn = util::reg_string(code, 16, 19);

    const u16 offset = shared::util::bit_fetcher<u16>(code, 0, 7) * 4;

    const char* op = ((code & (1 << 23)) ? "" : "-");

    return util::make_string("FLDD", util::cond(code), " ", Dd, ", [", Rn, ", #", op, util::hex(offset), "]");
}


/**
 * FLDM<addressing_mode>D{<cond>} <Rn>{!}, <registers>
 * where:
 * <addressing_mode>
 *             Specifies the addressing mode, which determines the values of start_address and
 *             end_address used by the instruction. See Addressing Mode 5 - VFP load/store
 *             multiple on page C5-24.
 * <cond>      Is the condition under which the instruction is executed. The conditions are defined
 *             in The condition field on page A3-5. If <cond> is omitted, the AL (always)
 *             condition is used.
 * <Rn>        Specifies the base register used by <addressing_mode>.
 * !           Sets the W bit of the instruction to 1, specifying that the base register <Rn> is to be
 *             updated by the instruction. If it is omitted, the W bit of the instruction is set to 0 and
 *             the base register <Rn> is left unchanged. Some combinations of
 *             <addressing_mode> and the presence or absence of ! are not allowed. For
 *             details, see Addressing Mode 5 - VFP load/store multiple on page C5-24.
 * <registers> Specifies which registers are to be loaded, as a list of consecutively numbered
 *             double-precision registers, separated by commas and surrounded by brackets. It is
 *             encoded in the instruction by setting Dd to the number of the first register in the list,
 *             and offset to twice the number of registers in the list. At least one register must
 *             be specified in the list.
 *             For example, if <registers> is {D2,D3,D4}, the Dd field of the instruction is
 *             2 and the offset field is 6.
 *
 * reference: C4-38
 */
std::string generators::arm::vfp::FLDMD(const u32 code) {
    const std::string addressing_mode = shifters::vfp_ls_mul(code);

    const std::string Rn = util::reg_string(code, 16, 19);

    const char* W = ((code & (1 << 21)) ? "!" : "");

    const u8 Dd = shared::util::bit_fetcher<u8>(code, 12, 15);
    const u8 offset = shared::util::bit_fetcher<u8>(code, 0, 7);

    const std::string registers = util::vfp_register_list(Dd, offset, util::prefix::D);

    return util::make_string("FLDM", addressing_mode, 'D', util::cond(code), " ", Rn, W, ", ", registers);
}


/**
 * FLDM<addressing_mode>S{<cond>} <Rn>{!}, <registers>
 * where:
 * <addressing_mode>
 *             Specifies the addressing mode, which determines the values of start_address and
 *             end_address used by the instruction. See Addressing Mode 5 - VFP load/store
 *             multiple on page C5-24 for details.
 * <cond>      Is the condition under which the instruction is executed. The conditions are defined
 *             in The condition field on page A3-5. If <cond> is omitted, the AL (always)
 *             condition is used.
 * <Rn>        Specifies the base register used by <addressing_mode>.
 * !           Sets the W bit of the instruction to 1, specifying that the base register <Rn> is to be
 *             updated by the instruction. If it is omitted, the W bit of the instruction is set to 0 and
 *             the base register <Rn> is left unchanged. Some combinations of
 *             <addressing_mode> and the presence or absence of ! are not allowed. For
 *             details, see Addressing Mode 5 - VFP load/store multiple on page C5-24.
 * <registers> Specifies which registers are to be loaded, as a list of consecutively numbered
 *             single-precision registers, separated by commas and surrounded by brackets. If d is
 *             the number of the first register in the list, the list is encoded in the instruction by
 *             setting Fd and D to the top 4 bits and the bottom bit respectively of d, and offset
 *             to the number of registers in the list. At least one register must be specified in the
 *             list.
 *             For example, if <registers> is {S5,S6,S7}, the Fd field of the instruction is
 *             0b0010, the D bit is 1 and the offset field is 3.
 * 
 * reference: C4-40
 */
std::string generators::arm::vfp::FLDMS(const u32 code) {
    const std::string addressing_mode = shifters::vfp_ls_mul(code);

    const std::string Rn = util::reg_string(code, 16, 19);

    const char* W = ((code & (1 << 21)) ? "!" : "");

    const bool D = (code & (1 << 22));
    const u8 Fd = shared::util::bit_fetcher<u8>(code, 12, 15);
    const u8 offset = shared::util::bit_fetcher<u8>(code, 0, 7);

    const u8 Fd_bits = static_cast<u8>((Fd << 1) | D);

    const std::string registers = util::vfp_register_list(Fd_bits, offset, util::prefix::S);

    return util::make_string("FLDM", addressing_mode, 'S', util::cond(code), " ", Rn, W, ", ", registers);
}


/**
 * FLDM<addressing_mode>X{<cond>} <Rn>{!}, <registers>
 * where:
 * <addressing_mode>
 *             Specifies the addressing mode, which determines the values of start_address and
 *             end_address used by the instruction. See Addressing Mode 5 - VFP load/store
 *             multiple on page C5-24 for details.
 * <cond>      Is the condition under which the instruction is executed. The conditions are defined
 *             in The condition field on page A3-5. If <cond> is omitted, the AL (always)
 *             condition is used.
 * <Rn>        Specifies the base register used by <addressing_mode>.
 * !           Sets the W bit of the instruction to 1, specifying that the base register <Rn> is to be
 *             updated by the instruction. If it is omitted, the W bit of the instruction is set to 0 and
 *             the base register <Rn> is left unchanged. Some combinations of
 *             <addressing_mode> and the presence or absence of ! are not allowed. For
 *             details, see Addressing Mode 5 - VFP load/store multiple on page C5-24.
 * <registers> Specifies which registers are to be loaded, as a list of consecutively numbered
 *             double-precision registers, separated by commas and surrounded by brackets. It is
 *             encoded in the instruction by setting Dd to the number of the first register in the list,
 *             and offset to twice the number of registers in the list, plus 1. At least one register
 *             must be specified in the list.
 *             For example, if <registers> is {D2,D3,D4}, the Dd field of the instruction is
 *             2 and the offset field is 7.
 * 
 * reference: C4-42
 */
std::string generators::arm::vfp::FLDMX(const u32 code) {
    const std::string addressing_mode = shifters::vfp_ls_mul(code);

    const std::string Rn = util::reg_string(code, 16, 19);

    const char* W = ((code & (1 << 21)) ? "!" : "");

    const u8 Dd = shared::util::bit_fetcher<u8>(code, 12, 15);
    const u8 offset = shared::util::bit_fetcher<u8>(code, 0, 7) - 1;

    const std::string registers = util::vfp_register_list(Dd, offset, util::prefix::D);

    return util::make_string("FLDM", addressing_mode, 'X', util::cond(code), " ", Rn, W, ", ", registers);
}


/**
 * FLDS{<cond>} <Sd>, [<Rn>{, #+/-(<offset>*4)}]
 * where:
 * <cond>   Is the condition under which the instruction is executed. The conditions are defined in The
 *          condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Sd>     Specifies the destination register. Its number is encoded as Fd (top 4 bits) and D (bottom
 *          bit).
 * <Rn>     Specifies the register holding the base address for the transfer.
 * <offset> Specifies an offset to be multiplied by 4, then added to the base address (if U == 1) or
 *          subtracted from it (if U == 0) in order to form the actual address of the transfer. If this offset
 *          is omitted, it defaults to +0.
 * 
 * reference: C4-44
 */
std::string generators::arm::vfp::FLDS(const u32 code) {
    const bool D = (code & (1 << 22));
    
    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D);
    const std::string Rn = util::reg_string(code, 16, 19);

    const u16 offset = shared::util::bit_fetcher<u16>(code, 0, 7) * 4;

    const char* op = ((code & (1 << 23)) ? "" : "-");

    return util::make_string("FLDS", util::cond(code), " ", Sd, ", [", Rn, ", #", op, util::hex(offset), "]");
}


/**
 * FMACD{<cond>} <Dd>, <Dn>, <Dm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Dd>   Specifies the destination register, which is also used as the second operand for the addition.
 * <Dn>   Specifies the register that contains the first operand for the multiplication.
 * <Dm>   Specifies the register that contains the second operand for the multiplication.
 * 
 * reference: C4-46
 */
std::string generators::arm::vfp::FMACD(const u32 code) {
    return patterns::vfp_Dd_Dn_Dm(code, "FMACD");
}


/**
 * FMACS{<cond>} <Sd>, <Sn>, <Sm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Sd>   Specifies the destination register, which is also used as the second operand for the addition.
 *        The register number is encoded as Fd (top 4 bits) and D (bottom bit).
 * <Sn>   Specifies the register that contains the first operand for the multiplication. The register
 *        number is encoded as Fn (top 4 bits) and N (bottom bit).
 * <Sm>   Specifies the register that contains the second operand for the multiplication. The register
 *        number is encoded as Fm (top 4 bits) and M (bottom bit).
 * 
 * reference: C4-48
 */
std::string generators::arm::vfp::FMACS(const u32 code) {
    return patterns::vfp_Sd_Sn_Sm(code, "FMACS");
}


/**
 * FMDHR{<cond>} <Dn>, <Rd>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Dn>   Specifies the destination register.
 * <Rd>   Specifies the source ARM register.
 * 
 * reference: C4-50
 */
std::string generators::arm::vfp::FMDHR(const u32 code) {
    return patterns::vfp_Dn_Rd(code, "FMDHR");
}

//1111 11100010 0001 0010 101100010000

/**
 * FMDLR{<cond>} <Dn>, <Rd>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Dn>   Specifies the destination register.
 * <Rd>   Specifies the source ARM register.
 * 
 * reference: C4-52
 */
std::string generators::arm::vfp::FMDLR(const u32 code) {
    return patterns::vfp_Dn_Rd(code, "FMDLR");
}


/**
 * FMRDH{<cond>} <Rd>, <Dn>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>   Specifies the destination ARM register.
 * <Dn>   Specifies the source register.
 * 
 * reference: C4-54
 */
std::string generators::arm::vfp::FMRDH(const u32 code) {
    return patterns::vfp_Rd_Dn(code, "FMRDH");
}


/**
 * FMRDL{<cond>} <Rd>, <Dn>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>   Specifies the destination ARM register.
 * <Dn>   Specifies the source register.
 * 
 * reference: C4-55
 */
std::string generators::arm::vfp::FMRDL(const u32 code) {
    return patterns::vfp_Rd_Dn(code, "FMRDL");
}


/**
 * FMRS{<cond>} <Rd>, <Sn>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>   Specifies the destination ARM register.
 * <Sn>   Specifies the source register. Its number is encoded as Fn (top 4 bits) and N (bottom bit).
 * 
 * reference: C4-56
 */
std::string generators::arm::vfp::FMRS(const u32 code) {
    const bool N = (code & (1 << 7));

    const std::string Sn = util::vfp_reg_string_bits(code, 16, 19, N);
    const std::string Rd = util::reg_string(code, 12, 15, util::prefix::R);

    return util::make_string("FMRS", util::cond(code), " ", Rd, ", ", Sn);
}


/**
 * FMRX{<cond>} <Rd>, <reg>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>   Specifies the destination ARM register.
 * <reg>  Specifies the source system register as follows:
 * 
 *        <reg> = 0b0000: FPSID
 *        <reg> = 0b0001: FPSCR
 *        <reg> = 0b1000: FPEXC
 * 
 *        Other values of <reg> can be used by individual VFP implementations for
 *        IMPLEMENTATION DEFINED purposes. Typically, they are used to transfer data from a
 *        hardware coprocessor to the support code for that coprocessor.
 *        
 *        All other code must treat such values of <reg> as UNPREDICTABLE.
 * 
 * reference: C4-58
 */
std::string generators::arm::vfp::FMRX(const u32 code) {
    const std::string Rd = util::reg_string(code, 12, 15, util::prefix::R);

    std::string vfp_sys_reg;
    vfp_sys_reg.reserve(5); // all system registers are only 5 characters long

    const u8 reg_bits = shared::util::bit_fetcher<u8>(code, 16, 19);

    switch (reg_bits) {
        case 0b0000: vfp_sys_reg = "FPSID"; break;
        case 0b0001: vfp_sys_reg = "FPSCR"; break;
        case 0b1000: vfp_sys_reg = "FPEXC"; break;
        default: shared::out::error("Unrecognised VFP system register for FMRX"); // unpredictable todo
    }

    return util::make_string("FMRX", util::cond(code), " ", Rd, ", ", vfp_sys_reg);
}


/**
 * FMSCD{<cond>} <Dd>, <Dn>, <Dm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Dd>   Specifies the destination register, which is also the second operand for the subtraction.
 * <Dn>   Specifies the register that contains the first operand for the multiplication.
 * <Dm>   Specifies the register that contains the second operand for the multiplication.
 * 
 * reference: C4-60
 */
std::string generators::arm::vfp::FMSCD(const u32 code) {
    return patterns::vfp_Dd_Dn_Dm(code, "FMSCD");
}


/**
 * FMSCS{<cond>} <Sd>, <Sn>, <Sm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Sd>   Specifies the destination register, which is also used as the second operand for the
 *        subtraction. The register number is encoded as Fd (top 4 bits) and D (bottom bit).
 * <Sn>   Specifies the register that contains the first operand for the multiplication. The register
 *        number is encoded as Fn (top 4 bits) and N (bottom bit).
 * <Sm>   Specifies the register that contains the second operand for the multiplication. The register
 *        number is encoded as Fm (top 4 bits) and M (bottom bit).
 * 
 * reference: C4-62
 */
std::string generators::arm::vfp::FMSCS(const u32 code) {
    return patterns::vfp_Sd_Sn_Sm(code, "FMSCS");
}


/**
 * FMSR{<cond>} <Sn>, <Rd>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Sn>   Is the destination register. Its number is encoded as Fn (top 4 bits) and N (bottom bit).
 * <Rd>   Is the source ARM register.
 * 
 * reference: C4-64
 */
std::string generators::arm::vfp::FMSR(const u32 code) {
    const bool N = (code & (1 << 7));

    const std::string Sn = util::vfp_reg_string_bits(code, 16, 19, N);
    const std::string Rd = util::reg_string(code, 12, 15);

    return util::make_string("FMSR", util::cond(code), " ", Sn, ", ", Rd);
}


/**
 * FMSTAT{<cond>}
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * 
 * reference: C4-66
 */
std::string generators::arm::vfp::FMSTAT(const u32 code) {
    return util::make_string("FMSTAT", util::cond(code));
}


/**
 * FMULD{<cond>} <Dd>, <Dn>, <Dm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Dd>   Specifies the destination register.
 * <Dn>   Specifies the register that contains the first operand for the multiplication.
 * <Dm>   Specifies the register that contains the second operand for the multiplication.
 * 
 * reference: C4-67
 */
std::string generators::arm::vfp::FMULD(const u32 code) {
    return patterns::vfp_Dd_Dn_Dm(code, "FMULD");
}


/**
 * FMULS{<cond>} <Sd>, <Sn>, <Sm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Sd>   Specifies the destination register. Its number is encoded as Fd (top 4 bits) and D (bottom bit).
 * <Sn>   Specifies the register that contains the first operand for the multiplication. Its number is
 *        encoded as Fn (top 4 bits) and N (bottom bit).
 * <Sm>   Specifies the register that contains the second operand for the multiplication. Its number is
 *        encoded as Fm (top 4 bits) and M (bottom bit).
 * 
 * reference: C4-68
 */
std::string generators::arm::vfp::FMULS(const u32 code) {
    return patterns::vfp_Sd_Sn_Sm(code, "FMULS");
}


/**
 * FMXR{<cond>} <reg>, <Rd>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <reg>  Specifies the destination system register as follows:
 * 
 *        <reg> = 0b0000: FPSID
 *        <reg> = 0b0001: FPSCR
 *        <reg> = 0b1000: FPEXC
 * 
 *        Other values of <reg> can be used by individual VFP implementations for
 *        IMPLEMENTATION DEFINED purposes. Typically, they are used to transfer data to a hardware
 *        coprocessor from the support code for that coprocessor.
 *        
 *        All other code must treat such values of <reg> as UNPREDICTABLE and not to be relied
 *        upon.
 * 
 * <Rd>   Specifies the source ARM register.
 * 
 * reference: C4-70
 */
std::string generators::arm::vfp::FMXR(const u32 code) {
    const std::string Rd = util::reg_string(code, 12, 15);

    std::string vfp_sys_reg;
    vfp_sys_reg.reserve(5); // all system registers are only 5 characters long

    const u8 reg_bits = shared::util::bit_fetcher<u8>(code, 16, 19);

    switch (reg_bits) {
        case 0b0000: vfp_sys_reg = "FPSID"; break;
        case 0b0001: vfp_sys_reg = "FPSCR"; break;
        case 0b1000: vfp_sys_reg = "FPEXC"; break;
        default: shared::out::error("Unrecognised VFP system register for FMXR"); // unpredictable todo
    }

    return util::make_string("FMXR", util::cond(code), " ", vfp_sys_reg, ", ", Rd);
}


/**
 * FNEGD{<cond>} <Dd>, <Dm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Dd>   Specifies the destination register.
 * <Dm>   Specifies the source register.
 * 
 * reference: C4-72
 */
std::string generators::arm::vfp::FNEGD(const u32 code) {
    return patterns::vfp_Dd_Dm(code, "FNEGD");
}


/**
 * FNEGS{<cond>} <Sd>, <Sm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Sd>   Specifies the destination register. Its number is encoded as Fd (top 4 bits) and D (bottom bit).
 * <Sm>   Specifies the source register. Its number is encoded as Fm (top 4 bits) and M (bottom bit).
 * 
 * reference: C4-74
 */
std::string generators::arm::vfp::FNEGS(const u32 code) {
    return patterns::vfp_Sd_Sm(code, "FNEGS");
}


/**
 * FNMACD{<cond>} <Dd>, <Dn>, <Dm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Dd>   Specifies the destination register, which is also used as the second operand for the addition.
 * <Dn>   Specifies the register that contains the first operand for the multiplication.
 * <Dm>   Specifies the register that contains the second operand for the multiplication.
 * 
 * reference: C4-76
 */
std::string generators::arm::vfp::FNMACD(const u32 code) {
    return patterns::vfp_Dd_Dn_Dm(code, "FNMACD");
}


/**
 * FNMACS{<cond>} <Sd>, <Sn>, <Sm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Sd>   Specifies the destination register, which is also used as the second operand for the addition.
 *        Its number is encoded as Fd (top 4 bits) and D (bottom bit).
 * <Sn>   Specifies the register that contains the first operand for the multiplication. Its number is
 *        encoded as Fn (top 4 bits) and N (bottom bit).
 * <Sm>   Specifies the register that contains the second operand for the multiplication. Its number is
 *        encoded as Fm (top 4 bits) and M (bottom bit).
 * 
 * reference: C4-78
 */
std::string generators::arm::vfp::FNMACS(const u32 code) {
    return patterns::vfp_Sd_Sn_Sm(code, "FNMACS");
}


/**
 * FNMSCD{<cond>} <Dd>, <Dn>, <Dm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Dd>   Specifies the destination register, and is also used as the second operand for the subtraction.
 * <Dn>   Specifies the register that contains the first operand for the multiplication.
 * <Dm>   Specifies the register that contains the second operand for the multiplication.
 * 
 * reference: C4-80
 */
std::string generators::arm::vfp::FNMSCD(const u32 code) {
    return patterns::vfp_Dd_Dn_Dm(code, "FNMSCD");
}


/**
 * FNMSCS{<cond>} <Sd>, <Sn>, <Sm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Sd>   Specifies the destination register, which is also used as the second operand for the
 *        subtraction. The register number is encoded as Fd (top 4 bits) and D (bottom bit).
 * <Sn>   Specifies the register that contains the first operand for the multiplication. The register
 *        number is encoded as Fn (top 4 bits) and N (bottom bit).
 * <Sm>   Specifies the register that contains the second operand for the multiplication. The register
 *        number is encoded as Fm (top 4 bits) and M (bottom bit).
 * 
 * reference: C4-82
 */
std::string generators::arm::vfp::FNMSCS(const u32 code) {
    return patterns::vfp_Sd_Sn_Sm(code, "FNMSCS");
}


/**
 * FNMULD{<cond>} <Dd>, <Dn>, <Dm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Dd>   Specifies the destination register.
 * <Dn>   Specifies the register that contains the first operand for the multiplication.
 * <Dm>   Specifies the register that contains the second operand for the multiplication.
 * 
 * reference: C4-84
 */
std::string generators::arm::vfp::FNMULD(const u32 code) {
    return patterns::vfp_Dd_Dn_Dm(code, "FNMULD");
}


/**
 * FNMULS{<cond>} <Sd>, <Sn>, <Sm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Sd>   Specifies the destination register. The register number is encoded as Fd (top 4 bits) and D (bottom bit).
 * <Sn>   Specifies the register that contains the first operand for the multiplication. The register
 *        number is encoded as Fn (top 4 bits) and N (bottom bit).
 * <Sm>   Specifies the register that contains the second operand for the multiplication. The register
 *        number is encoded as Fm (top 4 bits) and M (bottom bit).
 * 
 * reference: C4-86
 */
std::string generators::arm::vfp::FNMULS(const u32 code) {
    return patterns::vfp_Sd_Sn_Sm(code, "FNMULS");
}


/**
 * FSITOD{<cond>} <Dd>, <Sm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Dd>   Specifies the destination register.
 * <Sm>   Specifies the source register. The register number is encoded as Fm (top 4 bits) and M (bottom bit).
 * 
 * reference: C4-88
 */
std::string generators::arm::vfp::FSITOD(const u32 code) {
    return patterns::vfp_Dd_Sm(code, "FSITOD");
}


/**
 * FSITOS{<cond>} <Sd>, <Sm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Sd>   Specifies the destination register. The register number is encoded as Fd (top 4 bits) and D (bottom bit).
 * <Sm>   Specifies the source register. The register number is encoded as Fm (top 4 bits) and M (bottom bit).
 * 
 * reference: C4-89
 */
std::string generators::arm::vfp::FSITOS(const u32 code) {
    return patterns::vfp_Sd_Sm(code, "FSITOS");
}


/**
 * FSQRTD{<cond>} <Dd>, <Dm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Dd>   Specifies the destination register.
 * <Dm>   Specifies the source register.
 * 
 * reference: C4-90
 */
std::string generators::arm::vfp::FSQRTD(const u32 code) {
    return patterns::vfp_Dd_Dm(code, "FSQRTD");
}


/**
 * FSQRTS{<cond>} <Sd>, <Sm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Sd>   Specifies the destination register. The register number is encoded as Fd (top 4 bits) and D (bottom bit).
 * <Sm>   Specifies the source register. The register number is encoded as Fm (top 4 bits) and M (bottom bit).
 * 
 * reference: C4-92
 */
std::string generators::arm::vfp::FSQRTS(const u32 code) {
    return patterns::vfp_Sd_Sm(code, "FSQRTS"); 
}


/**
 * FSTD{<cond>} <Dd>, [<Rn>{, #+/-(<offset>*4)}]
 * where:
 * <cond>   Is the condition under which the instruction is executed. The conditions are defined in The
 *          condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Dd>     Specifies the source register.
 * <Rn>     Specifies the register holding the base address for the transfer.
 * <offset> Specifies an offset to be multiplied by 4, then added to the base address (if U == 1) or
 *          subtracted from it (if U == 0) to form the actual address of the transfer. If offset is
 *          omitted, it defaults to +0.
 * 
 * reference: C4-94
 */
std::string generators::arm::vfp::FSTD(const u32 code) {
    const std::string Dd = util::reg_string(code, 12, 15, util::prefix::D);
    const std::string Rn = util::reg_string(code, 16, 19);

    const u16 offset = (shared::util::bit_fetcher<u16>(code, 0, 7) * 4);

    const char* op = ((code & (1 << 23)) ? "" : "-");

    return util::make_string("FSTD", util::cond(code), " ", Dd, ", [", Rn, ", #", op, util::hex(offset), "]");
}


/**
 * FSTM<addressing_mode>D{<cond>} <Rn>{!}, <registers>
 * where:
 * <cond>      Is the condition under which the instruction is executed. The conditions are defined in The
 *             condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <addressing_mode>
 *             Specifies the addressing mode, which determines the values of start_address and
 *             end_address used by the instruction. See Addressing Mode 5 - VFP load/store multiple
 *             on page C5-24 for details.
 * <Rn>        Specifies the base register used by <addressing_mode>.
 * !           Sets the W bit of the instruction to 1, specifying that the base register <Rn> is to be updated
 *             by the instruction. If it is omitted, the W bit of the instruction is set to 0 and the base register
 *             <Rn> is left unchanged. Some combinations of <addressing_mode> and the presence
 *             or absence of ! are not allowed. For details, see Addressing Mode 5 - VFP load/store
 *             multiple on page C5-24.
 * <registers> Specifies which registers are to be stored, as a list of consecutively numbered
 *             double-precision registers, separated by commas and surrounded by brackets. It is encoded
 *             in the instruction by setting Dd to the number of the first register in the list, and offset to
 *             twice the number of registers in the list. At least one register must be specified in the list.
 *             For example, if <registers> is {D2,D3,D4}, the Dd field of the instruction is 2 and
 *             the offset field is 6.
 * 
 * reference: C4-96
 */
std::string generators::arm::vfp::FSTMD(const u32 code) {
    const std::string addressing_mode = shifters::vfp_ls_mul(code);

    const std::string Rn = util::reg_string(code, 16, 19);

    const char* W = ((code & (1 << 21)) ? "!" : "");

    const u8 Dd = shared::util::bit_fetcher<u8>(code, 12, 15);
    const u8 offset = shared::util::bit_fetcher<u8>(code, 0, 7);

    const std::string registers = util::vfp_register_list(Dd, offset, util::prefix::D);

    return util::make_string("FSTM", addressing_mode, 'D', util::cond(code), " ", Rn, W, ", ", registers);
}


/**
 * FSTM<addressing_mode>S{<cond>} <Rn>{!}, <registers>
 * where:
 * <cond>      Is the condition under which the instruction is executed. The conditions are defined in The
 *             condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <addressing_mode>
 *             Specifies the addressing mode, which determines the values of start_address and
 *             end_address used by the instruction. See Addressing Mode 5 - VFP load/store multiple
 *             on page C5-24.
 * <Rn>        Specifies the base register used by <addressing_mode>.
 * !           Sets the W bit of the instruction to 1, specifying that the base register <Rn> is to be updated
 *             by the instruction. If it is omitted, the W bit of the instruction is set to 0 and the base register
 *             <Rn> is left unchanged. Some combinations of <addressing_mode> and the presence
 *             or absence of ! are not allowed. For details, see Addressing Mode 5 - VFP load/store
 *             multiple on page C5-24.
 * <registers> Specifies which registers are to be stored, as a list of consecutively numbered
 *             single-precision registers, separated by commas and surrounded by brackets. If d is the
 *             number of the first register in the list, the list is encoded in the instruction by setting Fd and
 *             D to the top 4 bits and the bottom bit respectively of d, and offset to the number of
 *             registers in the list. At least one register must be specified in the list.
 *             For example, if <registers> is {S5,S6,S7}, the Fd field of the instruction is 0b0010,
 *             the D bit will be 1 and the offset field is 3.
 * 
 * reference: C4-98
 */
std::string generators::arm::vfp::FSTMS(const u32 code) {
    const std::string addressing_mode = shifters::vfp_ls_mul(code);

    const std::string Rn = util::reg_string(code, 16, 19);

    const char* W = ((code & (1 << 21)) ? "!" : "");

    const bool D = (code & (1 << 22));
    const u8 Fd = shared::util::bit_fetcher<u8>(code, 12, 15);
    const u8 offset = shared::util::bit_fetcher<u8>(code, 0, 7);

    const u8 Fd_bits = static_cast<u8>((Fd << 1) | D);

    const std::string registers = util::vfp_register_list(Fd_bits, offset, util::prefix::S);

    return util::make_string("FSTM", addressing_mode, 'S', util::cond(code), " ", Rn, W, ", ", registers);
}


/**
 * FSTM<addressing_mode>X{<cond>} <Rn>{!}, <registers>
 * where:
 * <cond>      Is the condition under which the instruction is executed. The conditions are defined in The
 *             condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <addressing_mode>
 *             Specifies the addressing mode, which determines the values of start_address and
 *             end_address used by the instruction. See Addressing Mode 5 - VFP load/store multiple
 *             on page C5-24 for details.
 * <Rn>        Specifies the base register used by <addressing_mode>.
 * !           Sets the W bit of the instruction to 1, specifying that the base register <Rn> is to be updated
 *             by the instruction. If it is omitted, the W bit of the instruction is set to 0 and the base register
 *             <Rn> is left unchanged. Some combinations of <addressing_mode> and the presence
 *             or absence of ! are not allowed. For details, see Addressing Mode 5 - VFP load/store
 *             multiple on page C5-24.
 * <registers> Specifies which registers are to be stored, as a list of consecutively numbered
 *             double-precision registers, separated by commas and surrounded by brackets. It is encoded
 *             in the instruction by setting Dd to the number of the first register in the list, and offset to
 *             twice the number of registers in the list plus 1. At least one register must be named in the list.
 *             For example, if <registers> is {D2,D3,D4}, the Dd field of the instruction is 2 and
 *             the offset field is 7.
 * 
 * reference: C4-100
 */
std::string generators::arm::vfp::FSTMX(const u32 code) {
    const std::string addressing_mode = shifters::vfp_ls_mul(code);

    const std::string Rn = util::reg_string(code, 16, 19);

    const char* W = ((code & (1 << 21)) ? "!" : "");

    const u8 Dd = shared::util::bit_fetcher<u8>(code, 12, 15);
    const u8 offset = shared::util::bit_fetcher<u8>(code, 0, 7) - 1;

    const std::string registers = util::vfp_register_list(Dd, offset, util::prefix::D);

    return util::make_string("FSTM", addressing_mode, 'X', util::cond(code), " ", Rn, W, ", ", registers);
}


/**
 * 
 * reference: C4-
 */
std::string generators::arm::vfp::FSTS(const u32 code) {
    const bool D = (code & (1 << 22));
    
    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D);
    const std::string Rn = util::reg_string(code, 16, 19);

    const u16 offset = shared::util::bit_fetcher<u16>(code, 0, 7) * 4;

    const char* op = ((code & (1 << 23)) ? "" : "-");

    return util::make_string("FSTS", util::cond(code), " ", Sd, ", [", Rn, ", #", op, util::hex(offset), "]");
}


/**
 * FSUBD{<cond>} <Dd>, <Dn>, <Dm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Dd>   Specifies the destination register.
 * <Dn>   Specifies the register that contains the first operand for the subtraction.
 * <Dm>   Specifies the register that contains the second operand for the subtraction.
 * 
 * reference: C4-104
 */
std::string generators::arm::vfp::FSUBD(const u32 code) {
    return patterns::vfp_Dd_Dn_Dm(code, "FSUBD");
}


/**
 * FSUBS{<cond>} <Sd>, <Sn>, <Sm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Sd>   Specifies the destination register. Its number is encoded as Fd (top 4 bits) and D (bottom bit).
 * <Sn>   Specifies the register that contains the first operand for the subtraction. The register number
 *        is encoded as Fn (top 4 bits) and N (bottom bit).
 * <Sm>   Specifies the register that contains the second operand for the subtraction. The register
 *        number is encoded as Fm (top 4 bits) and M (bottom bit).
 * 
 * reference: C4-106
 */
std::string generators::arm::vfp::FSUBS(const u32 code) {
    return patterns::vfp_Sd_Sn_Sm(code, "FSUBS");
}


/**
 * FTOSI{Z}D{<cond>} <Sd>, <Dm>
 * where:
 * Z      Sets the Z bit in the instruction to 1 and means that the operation uses the round towards
 *        zero rounding mode. If Z is not specified, the Z bit of the instruction is 0 and the operation
 *        uses the rounding mode specified by the FPSCR.
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Sd>   Specifies the destination register. Its number is encoded as Fd (top 4 bits) and D (bottom bit).
 * <Dm>   Specifies the source register.
 * 
 * reference: C4-108
 */
std::string generators::arm::vfp::FTOSID(const u32 code) {
    return patterns::vfp_Sd_Dm_Z(code, "FTOSI"); // D is appended at the end
}


/**
 * FTOSI{Z}S{<cond>} <Sd>, <Sm>
 * where:
 * Z      Sets the Z bit in the instruction to 1 and means that the operation uses the round towards
 *        zero rounding mode. If Z is not specified, the Z bit of the instruction is 0 and the operation
 *        uses the rounding mode specified by the FPSCR.
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Sd>   Specifies the destination register. Its number is encoded as Fd (top 4 bits) and D (bottom bit).
 * <Sm>   Specifies the source register. Its number is encoded as Fm (top 4 bits) and M (bottom bit).
 * 
 * reference: C4-110
 */
std::string generators::arm::vfp::FTOSIS(const u32 code) {
    return patterns::vfp_Sd_Sm_Z(code, "FTOSI"); // S is appended at the end
}


/**
 * FTOUI{Z}D{<cond>} <Sd>, <Dm>
 * where:
 * Z      Sets the Z bit in the instruction to 1 and means that the operation uses the round towards
 *        zero rounding mode. If Z is not specified, the Z bit of the instruction is 0 and the operation
 *        uses the rounding mode specified by the FPSCR.
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Sd>   Specifies the destination register. Its number is encoded as Fd (top 4 bits) and D (bottom bit).
 * <Dm>   Specifies the source register.
 * 
 * reference: C4-112
 */
std::string generators::arm::vfp::FTOUID(const u32 code) {
    return patterns::vfp_Sd_Dm_Z(code, "FTOUI"); // D is appended
}


/**
 * FTOUI{Z}S{<cond>} <Sd>, <Sm>
 * where:
 * Z      Sets the Z bit in the instruction to 1 and means that the operation uses the round towards
 *        zero rounding mode. If Z is not specified, the Z bit of the instruction is 0 and the operation
 *        uses the rounding mode specified by the FPSCR.
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Sd>   Specifies the destination register. Its number is encoded as Fd (top 4 bits) and D (bottom bit).
 * <Sm>   Specifies the source register. Its number is encoded as Fm (top 4 bits) and M (bottom bit).
 * 
 * reference: C4-114
 */
std::string generators::arm::vfp::FTOUIS(const u32 code) {
    return patterns::vfp_Sd_Sm_Z(code, "FTOUI"); // S is appended at the end
}


/**
 * FUITOD{<cond>} <Dd>, <Sm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Dd>   Specifies the destination register.
 * <Sm>   Specifies the source register. The register number is encoded as Fm (top 4 bits) and M (bottom bit).
 * 
 * reference: C4-116
 */
std::string generators::arm::vfp::FUITOD(const u32 code) {
    return patterns::vfp_Dd_Sm(code, "FUITOD");
}


/**
 * FUITOS{<cond>} <Sd>, <Sm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Sd>   Specifies the destination register. The register number is encoded as Fd (top 4 bits) and D (bottom bit).
 * <Sm>   Specifies the source register. The register number is encoded as Fm (top 4 bits) and M (bottom bit).
 * 
 * reference: C4-117
 */
std::string generators::arm::vfp::FUITOS(const u32 code) {
    return patterns::vfp_Sd_Sm(code, "FUITOS"); 
}