#include "../../types_extra.hpp"
#include "../../settings.hpp"
#include "../../id.hpp"
#include "../globals.hpp"
#include "../instruction_set.hpp"
#include "../exception.hpp"
#include "../core/core.hpp"
#include "../memory/memory.hpp"
#include "../memory/mmu.hpp"
#include "../memory/mpu.hpp"
#include "../memory/ram.hpp"
#include "../memory/fcse.hpp"
#include "../coprocessor/coprocessor.hpp"
#include "../instructions/instructions.hpp"
#include "cycle/fetch.hpp"
#include "cycle/decode.hpp"
#include "cycle/execute.hpp"
#include "registers.hpp"

#include <vector>

#include "core.hpp"

#include "shared/types.hpp"

#include <llarm-asm/llarm-asm.hpp>


void core::initialise(const std::vector<u8> &binary) {
    // essential settings
    SETTINGS settings;

    settings = settings.default_settings();

    // initialisations
    GLOBALS globals;
    CP15 cp15(settings, globals); // SEGFAULT HERE in release version for some reason
    COPROCESSOR coprocessor(settings, globals, cp15);
    RAM ram(globals);
    ARCH_26 arch_26(coprocessor, settings);
    MMU mmu(globals, ram, coprocessor, settings);
    MPU mpu(globals, coprocessor, settings);
    FCSE fcse(coprocessor, settings);
    REGISTERS reg(coprocessor, globals, arch_26, settings);
    //VFP vfp(reg);
    EXCEPTION exception(reg, coprocessor);
    MEMORY memory(ram, mmu, mpu, fcse, arch_26, exception);
    OPERATION operation;
    ADDRESSING_MODE address_mode(reg, operation);
    INSTRUCTIONS instructions(reg, address_mode, operation, coprocessor, settings, memory);
    INSTRUCTION_SET instruction_set(instructions);
    FETCH fetch(reg, memory, globals);
    DECODE decode(instruction_set, reg, settings);
    EXECUTE execute(instruction_set);


    // core reset, setup, and boot
    reg.reset();
    coprocessor.write(id::cp15::R1_M, false, id::cp::CP15, FORCED); // disable MMU/MPU
    coprocessor.write(id::cp15::R1_P, true, id::cp::CP15, FORCED); // set to 32-bit mode (maybe temporary idk)
    coprocessor.write(id::cp15::R1_D, true, id::cp::CP15, FORCED); // set to 32-bit mode (maybe temporary idk)
    // reg.switch_mode(id::mode::SUPERVISOR); only enable for system mode
    reg.switch_mode(id::mode::USER); // only for user programs, temporary
    //reg.write(id::cpsr::T, 1); // switch to thumb  // TODO: double check if it actually starts in thumb mode
    reg.write(id::cpsr::T, 0); // start in ARM mode, temporary
    memory.reset();
    ram.write(binary, 0);

    if (!settings.fresh_system) {
        reg.write(id::reg::SP, util::get_kb(16));
    }

    const llarm::as::settings tmp = { false, true, false, true, true };

    // instruction cycle 
    for (;;) {
        switch (globals.instruction_set) {
            case id::instruction_sets::ARM: {
                std::cout << ">>>>> PC: 0x" << std::hex << reg.read(id::reg::PC) << std::dec << "\n";

                const arm_fetch_struct arm_code_access = fetch.arm_fetch();

                if (arm_code_access.has_failed) {
                    continue;
                }

                std::cout << "0x" << std::hex << arm_code_access.code.to_ulong() << std::dec << "\n";
                
                const arm_decode_struct instruction = decode.arm_decode(arm_code_access.code);

                std::cout << llarm::as::arm_id_to_string(instruction.id) << "\n";
                std::cout << llarm::as::disassemble::arm(instruction.code, reg.read_PC(), tmp) << "\n";

                execute.arm_execute(instruction);

                reg.arm_increment_PC();

                util::dev::pause();
                continue;
            }

            case id::instruction_sets::THUMB: {
                const thumb_fetch_struct thumb_code_access = fetch.thumb_fetch();

                if (thumb_code_access.has_failed) {
                    continue;
                }

                const thumb_decode_struct instruction = decode.thumb_decode(thumb_code_access.code);

                execute.thumb_execute(instruction);

                reg.thumb_increment_PC();
                continue;
                // TODO benchmark by having the object allocations before the for (;;) loop
            }

            case id::instruction_sets::JAZELLE: {
                // this might look strange, but the fetch and decode stages are switched 
                // because Java bytecode can have varying instruction sizes unlike ARM 
                // (32-bit) or Thumb (16-bit). Only the opcode is known to have 1 byte 
                // while the operands take up space depending on which instruction it's 
                // being run. So basically this code will DECODE which instruction this 
                // is, FETCH the appropriate operands based on the identified instruction's 
                // operand size, then EXECUTE that instruction. It's weird, but whatever.

                // fetch
                //const u8 jazelle_code = fetch.jazelle_fetch();
                // decode

                // execute


                continue;
            }
        }
    }
}