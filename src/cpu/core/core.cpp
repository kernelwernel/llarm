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
#include "../memory/ram.hpp"
#include "../memory/fcse.hpp"
#include "../coprocessor/coprocessor.hpp"
//#include "cpu/mpu.hpp"

#include "cycle/fetch.hpp"
#include "cycle/decode.hpp"
#include "cycle/execute.hpp"
#include "vfp.hpp"

#include <vector>

void core::initialise(const std::vector<u8> &binary/*, input_args &args*/) {

    // initialisations
    GLOBALS globals;
    RAM ram;
    SETTINGS settings;
    COPROCESSOR coprocessor(settings, globals);
    ARCH_26_BIT arch_26(coprocessor);
    MMU mmu(globals, ram, coprocessor);
    FCSE fcse(coprocessor, settings);
    //MPU mpu(globals, coprocessor);
    REGISTERS reg(coprocessor, globals);
    //VFP vfp(reg);
    EXCEPTION exception(reg, coprocessor);
    MEMORY memory(binary, coprocessor, ram, mmu, fcse, settings);
    INSTRUCTION_SET instruction_set(reg, memory, coprocessor, settings);
    FETCH fetch(instruction_set, reg, memory);
    DECODE decode(instruction_set, reg, memory, settings);
    EXECUTE execute(instruction_set, reg);


    // core setup and boot
    reg.switch_mode(id::mode::SUPERVISOR);
    reg.write(id::cpsr::T, 1); // switch to thumb  // TODO: double check if it actually starts in thumb mode
    coprocessor.write(id::cp::CP15_R1_M, false); // disable MMU/MPU
    memory.reset();


    // instruction cycle 
    //for (;;) {
        switch (globals.instruction_set) {
            case id::instruction_sets::ARM: {
                const arm_code_t raw_arm_code = fetch.arm_fetch();
                const arm_decoded_t code = decode.arm_decode(raw_arm_code);
                execute.arm_execute(code);
                break;
            }

            case id::instruction_sets::THUMB: {
                const thumb_code_t raw_thumb_code = fetch.thumb_fetch();
                const thumb_decoded_t thumb_code = decode.thumb_decode(raw_thumb_code);
                execute.thumb_execute(thumb_code);
                break;
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
    //}

}