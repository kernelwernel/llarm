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
    const mem_read_struct access = memory.read(reg.force_read(id::reg::R15), 4, id::access_type::INSTRUCTION_FETCH);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code, id::access_type::INSTRUCTION_FETCH);
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
    const mem_read_struct access = memory.read(reg.force_read(id::reg::R15), 2, id::access_type::INSTRUCTION_FETCH);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code, id::access_type::INSTRUCTION_FETCH);
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