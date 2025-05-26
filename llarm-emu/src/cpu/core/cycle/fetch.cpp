#include "../../globals.hpp"

#include "fetch.hpp"

#include "shared/types.hpp"

FETCH::FETCH(
    REGISTERS& reg,
    MEMORY& memory,
    GLOBALS& globals
) : reg(reg), memory(memory), globals(globals) {

}


arm_fetch_struct FETCH::arm_fetch() {
    memory_struct access = memory.read<u32>(reg.read(id::reg::PC), 4, id::access_type::INSTRUCTION_FETCH);
    
    if (globals.is_little_endian) {
        access.value = util::swap_endianness<u32>(access.value);
    }

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return arm_fetch_struct {
            arm_code_t(0), // code
            true // has_failed
        };
    } else {
        return arm_fetch_struct {
            arm_code_t(access.value), // code
            false // has_failed
        };
    }
}


thumb_fetch_struct FETCH::thumb_fetch() {
    memory_struct access = memory.read<u16>(reg.read(id::reg::PC), 2, id::access_type::INSTRUCTION_FETCH);

    if (globals.is_little_endian) {
        access.value = util::swap_endianness<u16>(access.value);
    }

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return thumb_fetch_struct {
            thumb_code_t(0), // code
            true // has_failed
        };
    } else {
        return thumb_fetch_struct {
            thumb_code_t(access.value), // code
            false // has_failed
        };
    }
}


//jazelle_code_t FETCH::jazelle_fetch() const {
//    return memory.read(reg.read(id::reg::PC));
//}