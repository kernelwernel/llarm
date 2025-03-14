#include "../../types.hpp"
#include "../../settings.hpp"
#include "../../id.hpp"

#include "registers.hpp"
#include "globals.hpp"
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
//#include "cpu/mpu.hpp"

#include "cycle/fetch.hpp"
#include "cycle/decode.hpp"
#include "cycle/execute.hpp"
#include "vfp.hpp"

#include <vector>

void core::initialise(const std::vector<u8> &binary/*, input_args &args*/) {

    // initialisations
    GLOBALS globals;
    SETTINGS settings;
    CP15 cp15(settings, globals);
    COPROCESSOR coprocessor(cp15);
    RAM ram;
    ARCH_26_BIT arch_26(coprocessor, settings);
    MMU mmu(globals, ram, coprocessor, settings);
    MPU mpu(globals, coprocessor, settings);
    FCSE fcse(coprocessor, settings);
    REGISTERS reg(coprocessor, globals, arch_26, settings);
    //VFP vfp(reg);
    EXCEPTION exception(reg, coprocessor);
    MEMORY memory(binary, ram, mmu, mpu, fcse, arch_26, exception);
    OPERATION operation;
    ADDRESSING_MODE address_mode(reg, operation);
    INSTRUCTIONS instructions(reg, address_mode, operation, coprocessor, settings, memory);
    INSTRUCTION_SET instruction_set(instructions);
    FETCH fetch(reg, memory);
    DECODE decode(instruction_set, reg, settings);
    EXECUTE execute(instruction_set);


    // core setup and boot
    reg.switch_mode(id::mode::SUPERVISOR);
    reg.write(id::cpsr::T, 1); // switch to thumb  // TODO: double check if it actually starts in thumb mode
    coprocessor.write(id::cp::CP15_R1_M, false); // disable MMU/MPU
    memory.reset();


    std::cout << "hello charm\n";

    // instruction cycle 
    for (;;) {
        switch (globals.instruction_set) {
            case id::instruction_sets::ARM: {
                const FETCH::arm_fetch_struct arm_code_access = fetch.arm_fetch();

                if (arm_code_access.has_failed) {
                    continue;
                }

                const arm_decoded_t code = decode.arm_decode(arm_code_access.code);

                execute.arm_execute(code);
                continue;
            }

            case id::instruction_sets::THUMB: {
                const FETCH::thumb_fetch_struct thumb_code_access = fetch.thumb_fetch();

                if (thumb_code_access.has_failed) {
                    continue;
                }
        
                const thumb_decoded_t thumb_code = decode.thumb_decode(thumb_code_access.code);

                execute.thumb_execute(thumb_code);
                continue;
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
                //const jazelle_code_t raw_jazelle_code = fetch.jazelle_fetch();
                // decode

                // execute


                break;
            }
        }
    }

}