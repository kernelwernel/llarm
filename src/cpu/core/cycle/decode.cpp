#include "types.hpp"
#include "id.hpp"
#include "constants.hpp"
#include "cpu/instruction_set.hpp"
#include "cpu/core/cycle/decode.hpp"

#include <bitset>
#include <tuple>

// to whoever is reading this, i'm deeply sorry for the awful code below.

[[nodiscard]] id::arm_instruction DECODE::arm_identifier(const arm_code_t &raw_code) const {
    for (const auto &scan : arm_vector) {
        if (std::invoke(scan.opcode_function, raw_code)) {
            return scan.instruction_id;
        }
    }

    return id::arm_instruction::UNKNOWN;
}

// TODO: benchmark with maybe a std::execution iterator
[[nodiscard]] id::thumb_instruction DECODE::thumb_identifier(const thumb_code_t &raw_code) const {
    for (const auto &scan : thumb_vector) {
        if (std::invoke(scan.opcode_function, raw_code)) {
            return scan.instruction_id;
        }
    }

    return id::thumb_instruction::UNKNOWN;
}

// TODO: benchmark with maybe a std::execution iterator
[[nodiscard]] id::jazelle_instruction DECODE::jazelle_identifier(const u8 raw_code) const {
    for (const auto &scan : jazelle_vector) {
        if (scan.opcode == raw_code) {
            return scan.instruction_id;
        }
    }

    return id::jazelle_instruction::UNKNOWN;
}

[[nodiscard]] bool DECODE::condition_match(const id::cond cond) const {
    return (cond == reg.check_cond(cond));
}

void DECODE::loader() {
    // TODO: benchmark with maybe a std::execution iterator (for all 3)
    for (const auto &inst : inst_set.arm_table) {
        INSTRUCTION_SET::arm_struct data = inst.second;
        arm_vector.push_back({ inst.first, data.opcode });
    }

    if (settings.is_thumb_enabled) {
        for (const auto &inst : inst_set.thumb_table) {
            INSTRUCTION_SET::thumb_struct data = inst.second;
            thumb_vector.push_back({ inst.first, data.opcode });
        }
    }

    if (settings.is_jazelle_enabled) {
        for (const auto &inst : inst_set.jazelle_table) {
            INSTRUCTION_SET::jazelle_struct data = inst.second;
            jazelle_vector.push_back({ inst.first, data.opcode });
        }
    }
}

[[nodiscard]] arm_decoded_t DECODE::arm_decode(const arm_code_t &raw_code) const {
    id::cond cond = reg.fetch_cond_id(raw_code);

    if (!condition_match(cond)) {
        return (std::make_pair(id::arm_instruction::NOP, raw_code));
    }

    id::arm_instruction inst_id = identifier(raw_code);

    return (std::make_pair(inst_id, raw_code));
}

[[nodiscard]] thumb_decoded_t DECODE::thumb_decode(const thumb_code_t &raw_code) const {
    id::thumb_instruction inst_id = thumb_identifier(raw_code);
    return (std::make_pair(inst_id, raw_code));
}

[[nodiscard]] jazelle_decoded_t DECODE::jazelle_decode(const jazelle_code_t raw_code) const {
    id::jazelle_instruction inst_id = jazelle_identifier(raw_code);
    return inst_id;
}

DECODE::DECODE(
    INSTRUCTION_SET& inst_set,
    REGISTERS& reg,
    MEMORY& memory,
    SETTINGS& settings,
) : inst_set(inst_set), reg(reg), memory(memory), settings(settings) {
    loader();
}