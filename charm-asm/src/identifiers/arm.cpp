#include "identifiers.hpp"
#include "../instruction_id.hpp"
#include "../instruction_table.hpp"
#include "../../../shared/types.hpp"

using namespace internal;


static id::arm identifiers::arm_identifier(const arm_code_t &raw_code) {
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

static id::arm identifiers::arm_identifier(const u32 &raw_code) {
    return arm_identifier(arm_code_t(raw_code));
}