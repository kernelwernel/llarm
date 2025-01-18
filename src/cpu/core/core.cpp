#include "types.hpp"
#include "settings.hpp"
#include "id.hpp"

#include "cpu/core/registers.hpp"
#include "cpu/core/globals.hpp"
#include "cpu/instruction_set.hpp"
//#include "cpu/clock.hpp"
#include "cpu/exception.hpp"
#include "cpu/core/core.hpp"
#include "cpu/ram.hpp"
#include "cpu/mmu.hpp"
#include "cpu/tlb.hpp"
#include "cpu/memory.hpp"
#include "cpu/coprocessor.hpp"

#include "cpu/core/cycle/fetch.hpp"
#include "cpu/core/cycle/decode.hpp"
#include "cpu/core/cycle/execute.hpp"

#include <vector>

void core::initialise(const std::vector<u8> &binary, input_args &args) {

    // initialisations
    SETTINGS settings(args);
    GLOBALS globals;
    COPROCESSOR coprocessor(settings);
    REGISTERS reg(coprocessor, globals);
    RAM ram;
    MMU mmu(ram);
    MEMORY memory(binary, ram, coprocessor, mmu);
    INSTRUCTION_SET instruction_set(reg, memory, coprocessor);
    SYSTEM sys(reg, instruction_set, coprocessor);
    EXCEPTION exception(reg, coprocessor, instruction_set);
    FETCH fetch(instruction_set, reg, memory);
    DECODE decode(instruction_set, reg, memory);
    EXECUTE execute(instruction_set, reg);


    // setup/boot
    reg.switch_mode(id::mode::SUPERVISOR);
    reg.write_cpsr(id::cpsr::T, 1); // switch to thumb  // TODO: double check if it actually starts in thumb mode
    coprocessor.write_control(id::cp::CP15_R1_M, false); // disable MMU


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
                const jazelle_code_t raw_jazelle_code = fetch.jazelle_fetch();
                // decode

                // execute


                break;
            }
        }
    //}

}