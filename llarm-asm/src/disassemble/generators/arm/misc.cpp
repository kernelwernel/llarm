#include "../generators.hpp"
#include "../util.hpp"
#include "shifter_operands/shifters.hpp"
#include "../../../interpreter/mnemonic_arm.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>
#include <llarm/shared/out.hpp>

#include <string>

using namespace internal;

std::string generators::arm::misc::PSR(const u32 code, const settings& settings) {
    const u8 opc = llarm::util::bit_range<u8>(code, 21, 22);

    const std::string Rn = util::reg_string(code, 16, 19, settings);

    std::string instruction;

    switch (opc) {
        case 0b11: instruction = "CMN"; break; 
        case 0b10: instruction = "CMP"; break; 
        case 0b01: instruction = "TEQ"; break; 
        case 0b00: instruction = "TST"; break;
        default: llarm::out::error("Unknown opcode for PSR instruction");
    }

    const std::string addressing_mode = shifters::data(code, settings);

    return util::make_string(instruction, util::cond(code, settings), "P ", Rn, ", ", addressing_mode);
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
std::string generators::arm::misc::SWI(const u32 code, const settings& settings) {
    const u32 immed_24 = llarm::util::bit_range(code, 0, 23);
    return util::make_string("SWI", util::cond(code, settings), " ", util::hex(immed_24, settings));
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
 std::string generators::arm::misc::BKPT(const u32 code, const settings& settings) {
    const u16 immed_top = llarm::util::bit_range<u16>(code, 8, 19);
    const u16 immed_bottom = llarm::util::bit_range<u16>(code, 0, 3);

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


/**
 * CPS<effect> <iflags> {, #<mode>}
 * CPS #<mode>
 *
 * where:
 * <effect> Specifies what effect is wanted on the interrupt disable bits A, I, and F in the CPSR. This is
 * one of:
 * IE Interrupt Enable, encoded by imod == 0b10. This sets the specified bits to 0.
 * ID Interrupt Disable, encoded by imod == 0b11. This sets the specified bits to 1.
 * If <effect> is specified, the bits to be affected are specified by <iflags>. These are encoded
 * in the A, I, and F bits of the instruction. The mode can optionally be changed by specifying
 * a mode number as <mode>.
 * If <effect> is not specified, then:
 * • <iflags> is not specified and the A, I, and F mask settings are not changed
 * • the A, I, and F bits of the instruction are zero
 * • imod = 0b00
 * • mmod = 0b1
 * • <mode> specifies the new mode number.
 * <iflags> Is a sequence of one or more of the following, specifying which interrupt disable flags are
 * affected:
 * a Sets the A bit in the instruction, causing the specified effect on the CPSR A (imprecise data abort) bit.
 * i Sets the I bit in the instruction, causing the specified effect on the CPSR I (IRQ interrupt) bit.
 * f Sets the F bit in the instruction, causing the specified effect on the CPSR F (FIQ interrupt) bit
 * 
 * <mode>  * Specifies the number of the mode to change to. If it is present, then mmod == 1 and the mode
 * number is encoded in the mode field of the instruction. If it is omitted, then mmod == 0 and
 * the mode field of the instruction is zero. See The mode bits on page A2-14 for details.
 *
 * ARMv6 reference: A4-29
 */
std::string generators::arm::misc::CPS(const u32 code, const settings& settings) {
    const u8 imod = llarm::util::bit_range<u8>(code, 18, 19);
    const bool mmod = llarm::util::bit_fetch(code, 17);

    const bool A = llarm::util::bit_fetch(code, 8);
    const bool I = llarm::util::bit_fetch(code, 7);
    const bool F = llarm::util::bit_fetch(code, 6);

    const u8 mode_bits = llarm::util::bit_range<u8>(code, 0, 4);

    effect_id effect_id = effect_id::UNKNOWN;

    if (imod == 0b10) {
        effect_id = effect_id::IE;
    } else if (imod == 0b11) {
        effect_id = effect_id::ID;
    } else if (
        (imod == 0b00 && mmod == 0) ||
        (imod == 0b01 && mmod == 0) ||
        (imod == 0b01 && mmod == 1)
    ) {
        llarm::out::unpredictable("imod and mmod bits in CPS instruction during disassembly is unpredictable");
        effect_id = effect_id::NONE;
    } else if (imod == 0b00) {
        effect_id = effect_id::NONE;
    } else {
        llarm::out::unpredictable("CPS instruction effect field during disassembly is unpredictable");
        effect_id = effect_id::NONE;
    }

    if (effect_id == effect_id::NONE) {
        // format 2: CPS #<mode>
        return util::make_string("CPS #", util::hex(mode_bits, settings));
    }

    const std::string effect = [=]() -> std::string {
        if (effect_id == effect_id::IE) {
            return "IE";
        }

        if (effect_id == effect_id::ID) {
            return "ID";
        }

        return "";
    }();

    const std::string iflags = util::make_string(
        (A ? "a" : ""), (I ? "i" : ""), (F ? "f" : "")
    );

    const std::string mode = [=, &settings]() -> std::string {
        if (effect_id == effect_id::NONE) {
            return "";
        }

        return util::make_string(", #", util::hex(mode_bits, settings));
    }();
    
    // format 1: CPS<effect> <iflags> {, #<mode>}
    return util::make_string("CPS", effect, " ", iflags, mode);
}


/**
 * SETEND <endian_specifier>
 * where:
 * <endian_specifier>
 * Is one of:
 * BE Sets the E bit in the instruction. This sets the CPSR E bit.
 * LE Clears the E bit in the instruction. This clears the CPSR E bit.
 */
 std::string generators::arm::misc::SETEND(const u32 code) {
    const bool E = llarm::util::bit_fetch(code, 9);

    return util::make_string("SETEND ", (E ? "BE" : "LE"));
}
