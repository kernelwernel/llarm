#include "identifiers.hpp"
#include "../instruction_id.hpp"
#include "../instruction_table.hpp"

#include "shared/types.hpp"

using namespace internal;


id::thumb identifiers::thumb(const thumb_code_t &raw_code) {
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

id::thumb identifiers::thumb(const u16 raw_code) {
    return thumb(thumb_code_t(raw_code));
}


//id::thumb thumb(const std::string string_code) {}