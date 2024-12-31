#pragma once

#include "types.hpp"
#include "types_extra.hpp"
#include "id.hpp"
#include "constants.hpp"
#include "cpu/instruction_set.hpp"
#include "cpu/core/registers.hpp"

#include <bitset>
#include <tuple>
#include <functional>

struct DECODE {
private:
    struct arm_scan {
        id::instruction instruction_id;
        std::function<bool(const code_t&)> opcode_function;
    };

    struct thumb_scan {
        id::instruction instruction_id;
        std::function<bool(const thumbcode_t&)> opcode_function;
    };

    INSTRUCTION_SET& inst_set;
    REGISTERS& reg;

    std::vector<arm_scan> arm_vector;
    std::vector<thumb_scan> thumb_vector;


    [[nodiscard]] id::instruction identifier(const code_t &raw_code) const;

    // TODO: benchmark with maybe a std::execution iterator
    [[nodiscard]] id::instruction thumb_identifier(const thumbcode_t &raw_code) const;

    [[nodiscard]] bool condition_match(const id::cond cond) const;

    void loader();

public:
    DECODE(
        INSTRUCTION_SET& inst_set,
        REGISTERS& reg
    );

    [[nodiscard]] decoded_t decode(const code_t &raw_code) const;

    [[nodiscard]] thumb_decoded_t thumb_decode(const thumbcode_t &raw_code) const;
};