#include "../../settings.hpp"
#include "../../id.hpp"
#include "../coprocessor/coprocessor.hpp"

#include "fcse.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"

bool FCSE::is_fcse_enabled() {
    return (settings.is_fcse_enabled);
}

u32 FCSE::modify_address(const u32 address) {
    if (shared::util::bit_range(address, 31, 25) != 0) {
        return address;
    }

    const u8 PID = coprocessor.read(id::cp15::R13_PID);
    return (address | PID << 25);
}