#include "identifiers.hpp"
#include "../instruction_id.hpp"
#include "../instruction_table.hpp"

#include "../../../shared/types.hpp"

using namespace internal;


static id::thumb identifiers::thumb_identifier(const thumb_code_t &raw_code) {
    if (instructions::thumb_table.empty()) [[unlikely]] {
        instructions::thumb_load();
    }

    for (const auto &opcode : instructions::thumb_table) {
        if (std::invoke(opcode.test, raw_code)) {
            return opcode.instruction_id;
        }
    }

    return id::thumb::UNKNOWN;
}

static id::thumb identifiers::thumb_identifier(const u16 &raw_code) {
    return thumb_identifier(thumb_code_t(raw_code));
}
