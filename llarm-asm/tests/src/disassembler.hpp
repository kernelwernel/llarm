#pragma once

#include "constants.hpp"
#include <llarm/shared/types.hpp>
#include <capstone/capstone.h>
#include <string>


inline std::string capstone_arm_disassembler(const u32 binary) {
    csh handle;
    cs_open(CS_ARCH_ARM, CS_MODE_ARM, &handle);  // plain ARM, no thumb, no v5+

    const u8 bytes[4] = {
        static_cast<u8>(binary & 0xFF),
        static_cast<u8>((binary >> 8) & 0xFF),
        static_cast<u8>((binary >> 16) & 0xFF),
        static_cast<u8>((binary >> 24) & 0xFF)
    };

    cs_insn* insn;
    const size_t count = cs_disasm(handle, bytes, sizeof(bytes), PC, 1, &insn);

    std::string result = "error";
    if (count > 0) {
        result = std::string(insn[0].mnemonic) + " " + std::string(insn[0].op_str);
        cs_free(insn, count);
    }

    cs_close(&handle);
    return result;
}
