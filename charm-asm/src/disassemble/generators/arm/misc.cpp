#include "../generators.hpp"
#include "../util.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"
#include "shared/out.hpp"

#include <string>
#include <sstream>

using namespace internal;

std::string generators::arm::misc::PSR(const u32 code) {

}


/**
 * SWI{<cond>} <immed_24>
 * where:
 * <cond>     Is the condition under which the instruction is executed. The conditions are defined in The
 *            condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * <immed_24> Is a 24-bit immediate value that is put into bits[23:0] of the instruction. This value is ignored
 *            by the ARM processor, but can be used by an operating system SWI exception handler to
 *            determine what operating system service is being requested (see Usage on page A4-101
 *            below for more details).
 * 
 * reference: A4-100
 */
std::string generators::arm::misc::SWI(const u32 code) {
    const u8 cond = shared::util::bit_fetcher<u8>(code, 28, 31);
    const u32 immed_24 = shared::util::bit_fetcher(code, 0, 23);

    return util::make_string("SWI", util::fetch_cond(cond), " ", immed_24);
}