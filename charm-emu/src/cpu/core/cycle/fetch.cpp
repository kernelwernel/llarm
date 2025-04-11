#include "shared/types.hpp"
#include "../globals.hpp"
#include "fetch.hpp"

FETCH::FETCH(
    REGISTERS& reg,
    MEMORY& memory,
    GLOBALS& globals
) : reg(reg), memory(memory), globals(globals) {

}


arm_fetch_struct FETCH::arm_fetch() {
    arm_fetch_struct tmp = {};

    memory_struct access = memory.read<u32>(reg.read(id::reg::PC), 4, id::access_type::INSTRUCTION_FETCH);
    
    if (globals.is_little_endian) {
        access.value = util::swap_endianness<u32>(access.value);
    }

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        tmp.has_failed = true;
        tmp.code = arm_code_t(0);
    } else {
        tmp.has_failed = false;
        tmp.code = arm_code_t(access.value);
    }

    return tmp;
}


thumb_fetch_struct FETCH::thumb_fetch() {
    thumb_fetch_struct tmp = {};

    std::cout << ">>>>> PC: 0x" << std::hex << reg.read(id::reg::PC) << std::dec << "\n\n";

    memory_struct access = memory.read<u16>(reg.read(id::reg::PC), 2, id::access_type::INSTRUCTION_FETCH);

    if (globals.is_little_endian) {
        access.value = util::swap_endianness<u16>(access.value);
    }

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        tmp.has_failed = true;
        tmp.code = thumb_code_t(0);
    } else {
        tmp.has_failed = false;
        tmp.code = thumb_code_t(access.value);
    }

    return tmp;
}


//jazelle_code_t FETCH::jazelle_fetch() const {
//    return memory.read(reg.read(id::reg::PC));
//}