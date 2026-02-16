#include "../../settings.hpp"
#include "../../id.hpp"
#include "../coprocessor/coprocessor.hpp"

#include "fcse.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>

bool FCSE::is_fcse_enabled() {
    return (settings.is_fcse_enabled);
}

u32 FCSE::modify_address(const u32 address) {
    if (llarm::util::bit_range(address, 31, 25) != 0) {
        return address;
    }

    const u8 PID = static_cast<u8>(coprocessor.read(id::cp15::R13_PID));
    return (address | u32(PID << 25));
}

// TODO ctrl+f for "FCSE" in the arm docs once all the MMU, cache, and write buffer stuff are complete