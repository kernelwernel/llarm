#include "../../core/globals.hpp"

#include "fetch.hpp"

#include <llarm/shared/types.hpp>

FETCH::FETCH(
    REGISTERS& reg,
    MEMORY& memory,
    GLOBALS& globals
) : reg(reg), memory(memory), globals(globals) {

}


arm_fetch_struct FETCH::arm_fetch() {
    mem_read_struct access = memory.read(reg.read(id::reg::PC), 4, id::access_type::INSTRUCTION_FETCH);

    if (globals.is_little_endian) {
        access.value = util::swap_endianness(static_cast<u32>(access.value));
    }

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return arm_fetch_struct {
            0, // code
            true // has_failed
        };
    }

    return arm_fetch_struct {
        static_cast<u32>(access.value), // code
        false // has_failed
    };
}


thumb_fetch_struct FETCH::thumb_fetch() {
    mem_read_struct access = memory.read(reg.read(id::reg::PC), 2, id::access_type::INSTRUCTION_FETCH);

    if (globals.is_little_endian) {
        access.value = util::swap_endianness(static_cast<u16>(access.value));
    }

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return thumb_fetch_struct {
            0, // code
            true // has_failed
        };
    }

    return thumb_fetch_struct {
        static_cast<u16>(access.value), // code
        false // has_failed
    };
}