#pragma once

#include "../../../id.hpp"
#include "../../../settings.hpp"
#include "../../instruction_set.hpp"
#include "../registers.hpp"

#include "shared/types.hpp"

#include <llarm-asm/llarm-asm.hpp>

struct arm_decode_struct {
    llarm::as::id::arm id;
    arm_code_t code;
};

struct thumb_decode_struct {
    llarm::as::id::thumb id;
    thumb_code_t code;
};


struct DECODE {
private:
    INSTRUCTION_SET& inst_set;
    REGISTERS& reg;
    SETTINGS& settings;

private:
    bool condition_match(const id::cond cond) const;

public:
    arm_decode_struct arm_decode(const arm_code_t &raw_code) const;
    thumb_decode_struct thumb_decode(const thumb_code_t &raw_code) const;
    llarm::as::id::jazelle jazelle_decode(const u8 raw_code) const;

    DECODE(
        INSTRUCTION_SET& inst_set,
        REGISTERS& reg,
        SETTINGS& settings
    );
};