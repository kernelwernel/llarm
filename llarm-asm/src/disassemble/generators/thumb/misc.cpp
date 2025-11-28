#include "../generators.hpp"
#include "../util.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"

#include <string>

using namespace internal;


/** 
 * BKPT  <immed_8>
 * where:
 * <immed_8> Is an 8-bit immediate value, which is placed in bits[7:0] of the instruction. This value is 
 *           ignored by the ARM hardware, but can be used by a debugger to store additional 
 *           information about the breakpoint
 * 
 * reference: A7-24
 */
std::string generators::thumb::misc::BKPT(const u16 code, const settings settings) {
    const u8 immed_8 = llarm::util::bit_range<u8>(code, 0, 7);

    return util::make_string(
        "BKPT ", util::hex(immed_8, settings)
    );
}


/** 
 * SWI  <immed_8>
 * where: 
 * <immed_8> Is an 8-bit immediate value that is put into bits[7:0] of the instruction. This value is 
 *           ignored by the processor, but can be used by an operating system’s SWI exception 
 *           handler to determine which operating system service is being requested
 * 
 * reference: A7-102
 */
std::string generators::thumb::misc::SWI(const u16 code, const settings settings) {
    const u8 immed_8 = llarm::util::bit_range<u8>(code, 0, 7);

    return util::make_string(
        "SWI ", util::hex(immed_8, settings)
    );
}