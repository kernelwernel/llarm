#pragma once

#include "cpu/core/registers.hpp"
#include "cpu/memory.hpp"

#include <map>
#include <variant>

class INSTRUCTION_SET {
public:
    struct arm_struct {
        std::function<bool(const arm_code_t&)> opcode;
        std::function<void(const arm_code_t&, [[maybe_unused]] REGISTERS&)> function;
    };

    struct thumb_struct {
        std::function<bool(const thumb_code_t&)> opcode;
        std::function<void(const thumb_code_t&, [[maybe_unused]] REGISTERS&)> function;
    };

    struct jazelle_struct {
        u8 opcode;
        std::function<void(const jazelle_code_t, [[maybe_unused]] REGISTERS&)> function;
    };

    REGISTERS& reg;
    MEMORY& memory;
    COPROCESSOR& coprocessor;

private:
    using arm_table_t = std::map<id::arm_instruction, arm_struct>;
    using thumb_table_t = std::map<id::thumb_instruction, thumb_struct>;
    using jazelle_table_t = std::map<id::jazelle_instruction, jazelle_struct>;

public:
    arm_table_t arm_table;
    thumb_table_t thumb_table;
    jazelle_table_t thumb_table;

    id::instruction_sets set;

    INSTRUCTION_SET(REGISTERS& reg, MEMORY& memory, COPROCESSOR& coprocessor);
};