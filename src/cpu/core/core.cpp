#include "types.hpp"
#include "settings.hpp"
#include "id.hpp"

#include "cpu/core/registers.hpp"
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
    REGISTERS reg;
    RAM ram;
    TLB tlb(ram);
    COPROCESSOR coprocessor(settings);
    MMU mmu(ram);
    MEMORY memory(binary, ram, coprocessor);
    INSTRUCTION_SET instruction_set(reg, memory, coprocessor);
    SYSTEM sys(reg, instruction_set, coprocessor);
    EXCEPTION exception(reg, coprocessor, instruction_set);
    FETCH fetch(instruction_set, reg, memory);
    DECODE decode(instruction_set, reg);
    EXECUTE execute(instruction_set, reg);


    // setup/boot
    sys.switch_mode(id::mode::SUPERVISOR);
    sys.switch_to_thumb();
    sys.disable_mmu();


    // instruction cycle 
    //for (;;) {
        switch (instruction_set.set) {
            case id::instruction_sets::ARM: {
                const code_t raw_code = fetch.fetch();
                const decoded_t code = decode.decode(raw_code);
                execute.execute(code);
                break;
            }

            case id::instruction_sets::THUMB: {
                const thumbcode_t raw_thumb_code = fetch.thumb_fetch();
                const thumb_decoded_t thumb_code = decode.thumb_decode(raw_thumb_code);
                execute.thumb_execute(thumb_code);
                break;
            }
        }
    //}

}