#include "../generators.hpp"
#include "../util.hpp"
#include "shifter_operands/shifters.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"
#include "shared/out.hpp"

#include <string>

using namespace internal;

std::string generators::arm::misc::PSR(const u32 code, const settings settings) {
    const u8 opc  = shared::util::bit_range<u8>(code, 21, 22);

    const std::string Rn = util::reg_string(code, 16, 19, settings);

    std::string instruction;

    switch (opc) {
        case 0b11: instruction = "CMN"; break; 
        case 0b10: instruction = "CMP"; break; 
        case 0b01: instruction = "TEQ"; break; 
        case 0b00: instruction = "TST"; break;
        default: shared::out::error("Unknown opcode for PSR instruction");
    }

    const std::string addressing_mode = shifters::data(code, settings);

    return util::make_string(instruction, util::cond(code), "P ", Rn, ", ", addressing_mode);
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
std::string generators::arm::misc::SWI(const u32 code, const settings settings) {
    const u32 immed_24 = shared::util::bit_range(code, 0, 23);
    return util::make_string("SWI", util::cond(code), " ", util::hex(immed_24, settings));
}


/**
 * BKPT <immediate>
 * where:
 * <immediate>
 *         Is a 16-bit immediate value, the top 12 bits of which are placed in bits[19:8] of the
 *         instruction, and the bottom 4 bits of which are placed in bits[3:0] of the instruction.
 *         This value is ignored by the ARM hardware, but can be used by a debugger to store
 *         additional information about the breakpoint.
 * 
 * reference: A4-14
 */
 std::string generators::arm::misc::BKPT(const u32 code, const settings settings) {
    const u16 immed_top = shared::util::bit_range<u16>(code, 8, 19);
    const u16 immed_bottom = shared::util::bit_range<u16>(code, 0, 3);

    const u16 immediate = static_cast<u16>((immed_top << 4) | immed_bottom);

    return util::make_string("BKPT ", util::hex(immediate, settings));
}


/**
 * This isn't a real instruction documentated in the ARM docs, 
 * but i'm still adding this here for the sake of convenience
 */
std::string generators::arm::misc::NOP() {
    return "NOP";
}