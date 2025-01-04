#pragma once

#include "types.hpp"

#include "cpu/instruction_set.hpp"
#include "cpu/memory.hpp"

struct FETCH {
private:
    INSTRUCTION_SET& inst_set;
    REGISTERS& reg;
    MEMORY& memory;

    arm_code_t arm_converter(const std::vector<u8> &raw_code) const;
    
    thumb_code_t thumb_converter(const std::vector<u8> &raw_code) const;

public:
    FETCH(
        INSTRUCTION_SET& inst_set, 
        REGISTERS& reg,
        MEMORY& memory
    );

    arm_code_t arm_fetch() const;

    thumb_code_t thumb_fetch() const;

    jazelle_code_t jazelle_fetch() const;
};