#include "../generators.hpp"
#include "../util.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"
#include "shared/out.hpp"

#include <string>
#include <sstream>

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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const std::string Dd = util::reg_string(code, 12, 15, util::prefix::D);
    const std::string Dm = util::reg_string(code, 0, 3, util::prefix::D);

    return util::make_string("FABSD", util::fetch_cond(cond), " ", Dd, ", ", Dm); 
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const bool M = (code & (1 << 5));
    const bool D = (code & (1 << 22));

    const std::string Sm = util::vfp_reg_string_bits(code, 0, 3, M);
    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D);

    return util::make_string("FABSS", util::fetch_cond(cond), " ", Sd, ", ", Sm); 
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const std::string Dn = util::reg_string(code, 16, 19, util::prefix::D);
    const std::string Dd = util::reg_string(code, 12, 15, util::prefix::D);
    const std::string Dm = util::reg_string(code, 0, 3, util::prefix::D);

    return util::make_string("FADDD", util::fetch_cond(cond), " ", Dd, ", ", Dn, ", ", Dm); 
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const bool D = (code & (1 << 22));
    const bool N = (code & (1 << 7));
    const bool M = (code & (1 << 5));

    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D);
    const std::string Sn = util::vfp_reg_string_bits(code, 16, 19, N);
    const std::string Sm = util::vfp_reg_string_bits(code, 0, 3, M);

    return util::make_string("FADDS", util::fetch_cond(cond), " ", Sd, ", ", Sn, ", ", Sm); 
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const std::string Dd = util::reg_string(code, 12, 15, util::prefix::D);
    const std::string Dm = util::reg_string(code, 0, 3, util::prefix::D);

    return util::make_string("FCMPD", util::fetch_cond(cond), " ", Dd, ", ", Dm); 
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const std::string Dd = util::reg_string(code, 12, 15, util::prefix::D);
    const std::string Dm = util::reg_string(code, 0, 3, util::prefix::D);

    return util::make_string("FCMPED", util::fetch_cond(cond), " ", Dd, ", ", Dm); 
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const bool D = (code & (1 << 22));
    const bool M = (code & (1 << 5));

    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D);
    const std::string Sm = util::vfp_reg_string_bits(code, 0, 3, M);

    return util::make_string("FCMPES", util::fetch_cond(cond), " ", Sd, ", ", Sm); 


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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const std::string Dd = util::reg_string(code, 12, 15, util::prefix::D);

    return util::make_string("FCMPEZD", util::fetch_cond(cond), " ", Dd); 
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const bool D = (code & (1 << 22));

    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D);

    return util::make_string("FCMPEZS", util::fetch_cond(cond), " ", Sd); 
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const bool D = (code & (1 << 22));
    const bool M = (code & (1 << 5));

    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D);
    const std::string Sm = util::vfp_reg_string_bits(code, 0, 3, M);

    return util::make_string("FCMPS", util::fetch_cond(cond), " ", Sd, ", ", Sm); 
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const std::string Dd = util::reg_string(code, 12, 15, util::prefix::D);

    return util::make_string("FCMPZD", util::fetch_cond(cond), " ", Dd); 
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const bool D = (code & (1 << 22));

    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D);

    return util::make_string("FCMPZS", util::fetch_cond(cond), " ", Sd); 
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const std::string Dd = util::reg_string(code, 12, 15, util::prefix::D);
    const std::string Dm = util::reg_string(code, 0, 3, util::prefix::D);

    return util::make_string("FCPYD", util::fetch_cond(cond), " ", Dd, ", ", Dm); 
}


/**
 * FCPYS{<cond>} <Sd>, <Sm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Sd>   Specifies the destination register. The register number is encoded as Fd (top 4 bits) and D (bottom bit).
 * <Sm> Specifies the source register. The register number is encoded as Fm (top 4 bits) and M (bottom bit).
 * 
 * reference: C4-28
 */
std::string generators::arm::vfp::FCPYS(const u32 code) {
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const bool D = (code & (1 << 22));
    const bool M = (code & (1 << 5));

    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D);
    const std::string Sm = util::vfp_reg_string_bits(code, 0, 3, M);

    return util::make_string("FCPYS", util::fetch_cond(cond), " ", Sd, ", ", Sm); 
}


/**
 * FCVTDS{<cond>} <Dd>, <Sm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <Dd> Specifies the destination register.
 * <Sm> Specifies the source register. The register number is encoded as Fm (top 4 bits) and M (bottom bit).
 * 
 * reference: C4-30
 */
std::string generators::arm::vfp::FCVTDS(const u32 code) {
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const bool M = (code & (1 << 5));

    const std::string Sm = util::vfp_reg_string_bits(code, 12, 15, M);
    const std::string Dd = util::reg_string(code, 12, 15, util::prefix::D);

    return util::make_string("FCVTDS", util::fetch_cond(cond), " ", Dd, ", ", Sm);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const bool D = (code & (1 << 22));

    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D);
    const std::string Dm = util::reg_string(code, 0, 3, util::prefix::D);

    return util::make_string("FCVTSD", util::fetch_cond(cond), " ", Sd, ", ", Dm);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const std::string Dd = util::reg_string(code, 12, 15, util::prefix::D);
    const std::string Dn = util::reg_string(code, 16, 19, util::prefix::D);
    const std::string Dm = util::reg_string(code, 0, 3, util::prefix::D);

    return util::make_string("FDIVD", util::fetch_cond(cond), " ", Dd, ", ", Dn, ", ", Dm);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const bool D = (code & (1 << 22));
    const bool N = (code & (1 << 7));
    const bool M = (code & (1 << 5));

    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D);
    const std::string Sn = util::vfp_reg_string_bits(code, 16, 19, N);
    const std::string Sm = util::vfp_reg_string_bits(code, 0, 3, M);

    return util::make_string("FDIVS", util::fetch_cond(cond), " ", Sd, ", ", Sn, ", ", Sm);
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
    // TODO
}


/**
 * 
 * reference: C4-
 */
std::string generators::arm::vfp::FLDMD(const u32 code) {
    // TODO
}


/**
 * 
 * reference: C4-
 */
std::string generators::arm::vfp::FLDMS(const u32 code) {
    // TODO
}


/**
 * 
 * reference: C4-
 */
std::string generators::arm::vfp::FLDMX(const u32 code) {
    // TODO
}


/**
 * 
 * reference: C4-
 */
std::string generators::arm::vfp::FLDS(const u32 code) {
    // TODO
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const std::string Dd = util::reg_string(code, 12, 15, util::prefix::D);
    const std::string Dn = util::reg_string(code, 16, 19, util::prefix::D);
    const std::string Dm = util::reg_string(code, 0, 3, util::prefix::D);

    return util::make_string("FMACD", util::fetch_cond(cond), " ", Dd, ", ", Dn, ", ", Dm);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const bool D = (code & (1 << 22));
    const bool N = (code & (1 << 7));
    const bool M = (code & (1 << 5));

    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D);
    const std::string Sn = util::vfp_reg_string_bits(code, 16, 19, N);
    const std::string Sm = util::vfp_reg_string_bits(code, 0, 3, M);

    return util::make_string("FMACS", util::fetch_cond(cond), " ", Sd, ", ", Sn, ", ", Sm);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const std::string Rd = util::reg_string(code, 12, 15, util::prefix::R);
    const std::string Dn = util::reg_string(code, 16, 19, util::prefix::D);

    return util::make_string("FMDHR", util::fetch_cond(cond), " ", Dn, ", ", Rd);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const std::string Rd = util::reg_string(code, 12, 15, util::prefix::R);
    const std::string Dn = util::reg_string(code, 16, 19, util::prefix::D);

    return util::make_string("FMDLR", util::fetch_cond(cond), " ", Dn, ", ", Rd);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const std::string Rd = util::reg_string(code, 12, 15, util::prefix::R);
    const std::string Dn = util::reg_string(code, 16, 19, util::prefix::D);

    return util::make_string("FMRDH", util::fetch_cond(cond), " ", Rd, ", ", Dn);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const std::string Rd = util::reg_string(code, 12, 15, util::prefix::R);
    const std::string Dn = util::reg_string(code, 16, 19, util::prefix::D);

    return util::make_string("FMRDL", util::fetch_cond(cond), " ", Rd, ", ", Dn);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const bool N = (code & (1 << 7));

    const std::string Sn = util::vfp_reg_string_bits(code, 16, 19, N);
    const std::string Rd = util::reg_string(code, 12, 15, util::prefix::R);

    return util::make_string("FMRS", util::fetch_cond(cond), " ", Rd, ", ", Sn);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const std::string Rd = util::reg_string(code, 12, 15, util::prefix::R);

    std::string vfp_sys_reg = "";
    vfp_sys_reg.reserve(5); // all system registers are only 5 characters long

    const u8 reg_bits = shared::util::bit_fetcher(code, 16, 19);

    switch (reg_bits) {
        case 0b0000: vfp_sys_reg = "FPSID"; break;
        case 0b0001: vfp_sys_reg = "FPSCR"; break;
        case 0b1000: vfp_sys_reg = "FPEXC"; break;
        default: shared::out::error("Unrecognised VFP system register for FMRX"); // unpredictable todo
    }

    return util::make_string("FMRX", util::fetch_cond(cond), " ", Rd, ", ", vfp_sys_reg);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const std::string Dd = util::reg_string(code, 12, 15, util::prefix::D);
    const std::string Dn = util::reg_string(code, 16, 19, util::prefix::D);
    const std::string Dm = util::reg_string(code, 0, 3, util::prefix::D);

    return util::make_string("FMSCD", util::fetch_cond(cond), " ", Dd, ", ", Dn, ", ", Dm);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const bool D = (code & (1 << 22));
    const bool N = (code & (1 << 7));
    const bool M = (code & (1 << 5));
   
    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D); 
    const std::string Sn = util::vfp_reg_string_bits(code, 16, 19, N); 
    const std::string Sm = util::vfp_reg_string_bits(code, 0, 3, M); 

    return util::make_string("FMSCS", util::fetch_cond(cond), " ", Sd, ", ", Sn, ", ", Sm);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const bool N = (code & (1 << 7));

    const std::string Sn = util::vfp_reg_string_bits(code, 16, 19, N);
    const std::string Rd = util::reg_string(code, 12, 15);

    return util::make_string("FMSR", util::fetch_cond(cond), " ", Sn, ", ", Rd);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);
    return util::make_string("FMSTAT", util::fetch_cond(cond));
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const std::string Dd = util::reg_string(code, 12, 15, util::prefix::D);
    const std::string Dn = util::reg_string(code, 16, 19, util::prefix::D);
    const std::string Dm = util::reg_string(code, 0, 3, util::prefix::D);

    return util::make_string("FMULD", util::fetch_cond(cond), " ", Dd, ", ", Dn, ", ", Dm);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const bool D = (code & (1 << 22));
    const bool N = (code & (1 << 7));
    const bool M = (code & (1 << 5));
   
    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D); 
    const std::string Sn = util::vfp_reg_string_bits(code, 16, 19, N); 
    const std::string Sm = util::vfp_reg_string_bits(code, 0, 3, M); 

    return util::make_string("FMULS", util::fetch_cond(cond), " ", Sd, ", ", Sn, ", ", Sm);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const std::string Rd = util::reg_string(code, 12, 15);

    std::string vfp_sys_reg = "";
    vfp_sys_reg.reserve(5); // all system registers are only 5 characters long

    const u8 reg_bits = shared::util::bit_fetcher(code, 16, 19);

    switch (reg_bits) {
        case 0b0000: vfp_sys_reg = "FPSID"; break;
        case 0b0001: vfp_sys_reg = "FPSCR"; break;
        case 0b1000: vfp_sys_reg = "FPEXC"; break;
        default: shared::out::error("Unrecognised VFP system register for FMXR"); // unpredictable todo
    }

    return util::make_string("FMXR", util::fetch_cond(cond), " ", vfp_sys_reg, ", ", Rd);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const std::string Dd = util::reg_string(code, 12, 15, util::prefix::D);
    const std::string Dm = util::reg_string(code, 0, 3, util::prefix::D);

    return util::make_string("FNEGD", util::fetch_cond(cond), " ", Dd, ", ", Dm);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const bool D = (code & (1 << 22));
    const bool M = (code & (1 << 5));
   
    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D); 
    const std::string Sm = util::vfp_reg_string_bits(code, 0, 3, M); 

    return util::make_string("FNEGS", util::fetch_cond(cond), " ", Sd, ", ", Sm);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const std::string Dd = util::reg_string(code, 12, 15, util::prefix::D);
    const std::string Dn = util::reg_string(code, 16, 19, util::prefix::D);
    const std::string Dm = util::reg_string(code, 0, 3, util::prefix::D);

    return util::make_string("FNMACD", util::fetch_cond(cond), " ", Dd, ", ", Dn, ", ", Dm);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const bool D = (code & (1 << 22));
    const bool N = (code & (1 << 7));
    const bool M = (code & (1 << 5));
   
    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D); 
    const std::string Sn = util::vfp_reg_string_bits(code, 16, 19, N); 
    const std::string Sm = util::vfp_reg_string_bits(code, 0, 3, M); 

    return util::make_string("FNMACS", util::fetch_cond(cond), " ", Sd, ", ", Sn, ", ", Sm);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const std::string Dd = util::reg_string(code, 12, 15, util::prefix::D);
    const std::string Dn = util::reg_string(code, 16, 19, util::prefix::D);
    const std::string Dm = util::reg_string(code, 0, 3, util::prefix::D);

    return util::make_string("FNMSCD", util::fetch_cond(cond), " ", Dd, ", ", Dn, ", ", Dm);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const bool D = (code & (1 << 22));
    const bool N = (code & (1 << 7));
    const bool M = (code & (1 << 5));
   
    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D); 
    const std::string Sn = util::vfp_reg_string_bits(code, 16, 19, N); 
    const std::string Sm = util::vfp_reg_string_bits(code, 0, 3, M); 

    return util::make_string("FNMSCS", util::fetch_cond(cond), " ", Sd, ", ", Sn, ", ", Sm);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const std::string Dd = util::reg_string(code, 12, 15, util::prefix::D);
    const std::string Dn = util::reg_string(code, 16, 19, util::prefix::D);
    const std::string Dm = util::reg_string(code, 0, 3, util::prefix::D);

    return util::make_string("FNMULD", util::fetch_cond(cond), " ", Dd, ", ", Dn, ", ", Dm);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const bool D = (code & (1 << 22));
    const bool N = (code & (1 << 7));
    const bool M = (code & (1 << 5));
   
    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D); 
    const std::string Sn = util::vfp_reg_string_bits(code, 16, 19, N); 
    const std::string Sm = util::vfp_reg_string_bits(code, 0, 3, M); 

    return util::make_string("FNMULS", util::fetch_cond(cond), " ", Sd, ", ", Sn, ", ", Sm);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const bool M = (code & (1 << 5));
   
    const std::string Sm = util::vfp_reg_string_bits(code, 0, 3, M); 
    const std::string Dd = util::reg_string(code, 12, 15, util::prefix::D);

    return util::make_string("FSITOD", util::fetch_cond(cond), " ", Dd, ", ", Sm);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const bool D = (code & (1 << 22));
    const bool M = (code & (1 << 5));
   
    const std::string Sm = util::vfp_reg_string_bits(code, 0, 3, M); 
    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D); 

    return util::make_string("FSITOS", util::fetch_cond(cond), " ", Sd, ", ", Sm);   
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const std::string Dd = util::reg_string(code, 12, 15, util::prefix::D);
    const std::string Dm = util::reg_string(code, 0, 3, util::prefix::D);

    return util::make_string("FSQRTD", util::fetch_cond(cond), " ", Dd, ", ", Dm);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const bool D = (code & (1 << 22));
    const bool M = (code & (1 << 5));
   
    const std::string Sm = util::vfp_reg_string_bits(code, 0, 3, M); 
    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D); 

    return util::make_string("FSQRTS", util::fetch_cond(cond), " ", Sd, ", ", Sm);   
}


/**
 * 
 * reference: C4-
 */
std::string generators::arm::vfp::FSTD(const u32 code) {
    // TODO
}


/**
 * 
 * reference: C4-
 */
std::string generators::arm::vfp::FSTMD(const u32 code) {
    // TODO
}


/**
 * 
 * reference: C4-
 */
std::string generators::arm::vfp::FSTMS(const u32 code) {
    // TODO
}


/**
 * 
 * reference: C4-
 */
std::string generators::arm::vfp::FSTMX(const u32 code) {
    // TODO
}


/**
 * 
 * reference: C4-
 */
std::string generators::arm::vfp::FSTS(const u32 code) {
    // TODO
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const std::string Dd = util::reg_string(code, 12, 15, util::prefix::D);
    const std::string Dn = util::reg_string(code, 16, 19, util::prefix::D);
    const std::string Dm = util::reg_string(code, 0, 3, util::prefix::D);

    return util::make_string("FSUBD", util::fetch_cond(cond), " ", Dd, ", ", Dn, ", ", Dm);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const bool D = (code & (1 << 22));
    const bool N = (code & (1 << 7));
    const bool M = (code & (1 << 5));
   
    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D); 
    const std::string Sn = util::vfp_reg_string_bits(code, 16, 19, N); 
    const std::string Sm = util::vfp_reg_string_bits(code, 0, 3, M); 

    return util::make_string("FSUBS", util::fetch_cond(cond), " ", Sd, ", ", Sn, ", ", Sm);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const bool D = (code & (1 << 22));
   
    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D);
    const std::string Dm = util::reg_string(code, 0, 3, util::prefix::D);

    const char* Z = ((code & (1 << 7)) ? "ZD" : "D");

    return util::make_string("FTOSI", Z, util::fetch_cond(cond), " ", Sd, ", ", Dm);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const bool D = (code & (1 << 22));
    const bool M = (code & (1 << 5));
   
    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D);
    const std::string Sm = util::vfp_reg_string_bits(code, 0, 3, M);

    const char* Z = ((code & (1 << 7)) ? "ZS" : "S");

    return util::make_string("FTOSI", Z, util::fetch_cond(cond), " ", Sd, ", ", Sm);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const bool D = (code & (1 << 22));
   
    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D);
    const std::string Dm = util::reg_string(code, 0, 3, util::prefix::D);

    const char* Z = ((code & (1 << 7)) ? "ZD" : "D");

    return util::make_string("FTOUI", Z, util::fetch_cond(cond), " ", Sd, ", ", Dm);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const bool D = (code & (1 << 22));
    const bool M = (code & (1 << 5));
   
    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D);
    const std::string Sm = util::vfp_reg_string_bits(code, 0, 3, M);

    const char* Z = ((code & (1 << 7)) ? "ZS" : "S");

    return util::make_string("FTOUI", Z, util::fetch_cond(cond), " ", Sd, ", ", Sm);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const bool M = (code & (1 << 5));
   
    const std::string Sm = util::vfp_reg_string_bits(code, 0, 3, M);
    const std::string Dd = util::reg_string(code, 12, 15, util::prefix::D);

    return util::make_string("FUITOD", util::fetch_cond(cond), " ", Dd, ", ", Sm);
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
    const u8 cond = shared::util::bit_fetcher(code, 28, 31);

    const bool D = (code & (1 << 22));
    const bool M = (code & (1 << 5));
   
    const std::string Sd = util::vfp_reg_string_bits(code, 12, 15, D);
    const std::string Sm = util::vfp_reg_string_bits(code, 0, 3, M);

    return util::make_string("FUITOS", util::fetch_cond(cond), " ", Sd, ", ", Sm);
}