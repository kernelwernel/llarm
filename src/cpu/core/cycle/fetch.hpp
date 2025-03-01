#pragma once

#include "../../../types.hpp"

#include "../../instruction_set.hpp"
#include "../../memory/memory.hpp"

struct FETCH {
private:
    INSTRUCTION_SET& inst_set;
    REGISTERS& reg;
    MEMORY& memory;

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