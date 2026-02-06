#include "core.hpp"

#include <llarm/shared/types.hpp>

#include <vector>

#include <llarm-asm/llarm-asm.hpp>


inline void CORE::arm_cycle(const llarm::as::settings &settings) {
    std::cout << ">>>>> PC: 0x" << std::hex << reg.read(id::reg::PC) << std::dec << "\n";

    const arm_fetch_struct arm_code_access = fetch.arm_fetch();

    if (arm_code_access.has_failed) {
        return;
    }

    std::cout << "0x" << std::hex << arm_code_access.code << std::dec << "\n";
    
    const arm_decode_struct instruction = decode.arm_decode(arm_code_access.code);

    std::cout << llarm::as::arm_id_to_string(instruction.id) << "\n";
    std::cout << llarm::as::disassemble::arm(instruction.code, reg.read_PC(), settings) << "\n";

    execute.arm_execute(instruction);

    reg.arm_increment_PC();

    util::dev::pause();
}


inline void CORE::thumb_cycle() {
    const thumb_fetch_struct thumb_code_access = fetch.thumb_fetch();

    if (thumb_code_access.has_failed) {
        return;
    }

    const thumb_decode_struct instruction = decode.thumb_decode(thumb_code_access.code);

    execute.thumb_execute(instruction);

    reg.thumb_increment_PC();
}


void CORE::initialise(const std::vector<u8> &binary) {

    // core reset, setup, and boot
    reg.reset();
    coprocessor.force_write(id::cp15::R1_M, false); // disable MMU/MPU
    coprocessor.force_write(id::cp15::R1_P, true); // set to 32-bit mode (maybe temporary idk)
    coprocessor.force_write(id::cp15::R1_D, true); // set to 32-bit mode (maybe temporary idk)
    // reg.switch_mode(id::mode::SUPERVISOR); only enable for system mode
    reg.switch_mode(id::mode::USER); // only for user programs, temporary
    //reg.write(id::cpsr::T, 1); // switch to thumb  // TODO: double check if it actually starts in thumb mode
    reg.write(id::cpsr::T, 0); // start in ARM mode, temporary
    memory.reset();
    ram.write(binary, 0);

    if (!settings.fresh_system) {
        reg.write(id::reg::SP, util::get_kb(16));
    }

    // temporary, for development purposes
    const llarm::as::settings settings = { false, true, false, true, true };

    // instruction cycle 
    for (;;) {
        switch (globals.instruction_set) {
            case id::instruction_sets::ARM: arm_cycle(settings); continue;
            case id::instruction_sets::THUMB: thumb_cycle(); continue;
        }
    }
}