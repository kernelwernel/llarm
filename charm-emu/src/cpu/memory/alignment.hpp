#pragma once

#include "../../id.hpp"
#include "../coprocessor/coprocessor.hpp"


struct ALIGNMENT {
private:
    COPROCESSOR& coprocessor;

    bool is_alignment_enabled() {
        return (
            (settings.has_alignment_fault_checking) &&
            (coprocessor.read(id::cp::CP15_R1_A))
        );
    }


    if (
        (coprocessor.read(id::cp::CP15_R1_A)) && // check if allignment fault is enabled
        (access_type != id::access_type::INSTRUCTION_FETCH)
    ) {
        switch (access_byte_size) {
            case 1: // byte
                break; // there are no alignment faults for byte accesses

            case 2: // halfword 
                if ((address & 1) != 0) {
                    ret.status = id::aborts::ALIGNMENT;
                    return ret;
                }
                break;

            case 4: // word
                if ((address & 0b11) != 0b00) {
                    ret.status = id::aborts::ALIGNMENT;
                    return ret;
                }
                break;

            default: shared::out::error(); // TODO
        }
    }
};
        