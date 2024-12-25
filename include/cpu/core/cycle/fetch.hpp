#pragma once

#include "types.hpp"

#include "cpu/instruction_set.hpp"
#include "cpu/memory.hpp"

struct FETCH {
private:
    INSTRUCTION_SET& inst_set;
    REGISTERS& reg;
    MEMORY& memory;

    [[nodiscard]] code_t converter(const std::vector<u8> &raw_code) const;
    
    [[nodiscard]] thumbcode_t thumb_converter(const std::vector<u8> &raw_code) const;

public:
    FETCH(
        INSTRUCTION_SET& inst_set, 
        REGISTERS& reg,
        MEMORY& memory
    );

    [[nodiscard]] code_t fetch() const;

    [[nodiscard]] thumbcode_t thumb_fetch() const;
};