#include "types.hpp"
#include "id.hpp"
#include "constants.hpp"
#include "cpu/instruction_set.hpp"
#include "cpu/core/cycle/decode.hpp"

#include <bitset>
#include <tuple>
#include <iostream> //tmp

[[nodiscard]] id::instruction DECODE::identifier(const code_t &raw_code) const {
    for (const auto &scan : arm_vector) {
        if (std::invoke(scan.opcode_function, raw_code)) {
            return scan.instruction_id;
        }
    }

    return id::instruction::UNKNOWN;
}

// TODO: benchmark with maybe a std::execution iterator
[[nodiscard]] id::instruction DECODE::thumb_identifier(const thumbcode_t &raw_code) const {
    for (const auto &scan : thumb_vector) {
        if (std::invoke(scan.opcode_function, raw_code)) {
            return scan.instruction_id;
        }
    }

    return id::instruction::T_UNKNOWN;
}

[[nodiscard]] bool DECODE::condition_match(const id::cond cond) const {
    return (cond == inst_set.reg.check_cond(cond));
}

void DECODE::loader() {
    // TODO: benchmark with maybe a std::execution iterator
    for (const auto &inst : inst_set.arm_table) {
        INSTRUCTION_SET::arm_struct data = inst.second;
        arm_vector.push_back({ inst.first, data.opcode });
    }

    // same here
    for (const auto &inst : inst_set.thumb_table) {
        INSTRUCTION_SET::thumb_struct data = inst.second;
        thumb_vector.push_back({ inst.first, data.opcode });
    }
}

[[nodiscard]] decoded_t DECODE::decode(const code_t &raw_code) const {
    id::cond cond = reg.fetch_cond_id(raw_code);

    if (!condition_match(cond)) {
        return (std::make_pair(id::instruction::NOP, raw_code));
    }

    id::instruction inst_id = identifier(raw_code);

    return (std::make_pair(inst_id, raw_code));
}

[[nodiscard]] thumb_decoded_t DECODE::thumb_decode(const thumbcode_t &raw_code) const {
    id::instruction inst_id = thumb_identifier(raw_code);
    return (std::make_pair(inst_id, raw_code));
}

DECODE::DECODE(
    INSTRUCTION_SET& inst_set,
    REGISTERS& reg
) : inst_set(inst_set), reg(reg) {
    loader();
}