#pragma once

#include "cpu/core/registers.hpp"
#include "cpu/memory.hpp"

#include <map>
#include <variant>

class INSTRUCTION_SET {
public:
    struct arm_struct {
        std::function<bool(const code_t&)> opcode;
        std::function<void(const code_t&, [[maybe_unused]] REGISTERS&)> function;
    };

    struct thumb_struct {
        std::function<bool(const thumbcode_t&)> opcode;
        std::function<void(const thumbcode_t&, [[maybe_unused]] REGISTERS&)> function;
    };

    REGISTERS& reg;
    MEMORY& memory;

private:
    using table_t = std::map<id::instruction, arm_struct>;
    using thumbtable_t = std::map<id::instruction, thumb_struct>;

public:
    table_t arm_table;
    thumbtable_t thumb_table;

    id::instruction_sets set;

    INSTRUCTION_SET(REGISTERS& reg, MEMORY& memory);
};