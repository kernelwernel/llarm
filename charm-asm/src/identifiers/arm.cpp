#include "identifiers.hpp"
#include "../instruction_id.hpp"
#include "../instruction_table.hpp"

#include <charm/internal/shared/types.hpp>

using namespace internal;


id::arm identifiers::arm(const arm_code_t &raw_code) {
    if (instructions::arm_table.empty()) [[unlikely]] {
        instructions::arm_load();
    }

    for (const auto &opcode : instructions::arm_table) {
        if (std::invoke(opcode.test, raw_code)) {
            return opcode.instruction_id;
        }
    }

    return id::arm::UNKNOWN;
}

id::arm identifiers::arm(const u32 raw_code) {
    return arm(arm_code_t(raw_code));
}