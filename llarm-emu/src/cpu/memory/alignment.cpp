#include "../../id.hpp"
#include "../../settings.hpp"
#include "../coprocessor/coprocessor.hpp"

#include "alignment.hpp"

#include "shared/out.hpp"


bool ALIGNMENT::is_enabled() {
    return (
        (settings.has_alignment_fault_checking) &&
        (coprocessor.read(id::cp15::R1_A))
    );
}


// this might look stupid, but i'd much rather do this than have "!alignment.is_enabled()"
// throughout the code, which is a common enough occurrence that this is kinda warranted
// for the sake of having a natural readability style which i prefer. 
bool ALIGNMENT::is_disabled() {
    return (!is_enabled());
}


bool ALIGNMENT::is_aligned(const u32 value, const u8 access_size) {
    switch (access_size) {
        // byte
        case 1: return true; // there are no alignment faults for byte accesses

        // halfword 
        case 2: return ((value & 1) == 0);

        // word
        case 4: return ((value & 0b11) == 0b00);

        // dword
        case 8: return ((value & 0b111) == 0b000);

        default: llarm::out::error(); // TODO
    }
}