#pragma once

#include "types.hpp"
#include "types_extra.hpp"
#include "cpu/instruction_set.hpp"
#include "cpu/core/registers.hpp"
#include "cpu/core/cycle/decode.hpp"

struct EXECUTE {
private:
    INSTRUCTION_SET& inst_set;
    REGISTERS& reg;

    std::map<id::instruction, std::function<void(const code_t&, [[maybe_unused]] REGISTERS&)>> arm_map;
    std::map<id::instruction, std::function<void(const thumbcode_t&, [[maybe_unused]] REGISTERS&)>> thumb_map;

public:
    void loader();

    void execute(const decoded_t &code) const;
    
    void thumb_execute(const thumb_decoded_t &code) const;

    EXECUTE(
        INSTRUCTION_SET& inst_set,
        REGISTERS& reg
    );
};