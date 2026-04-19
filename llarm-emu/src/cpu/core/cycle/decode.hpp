#pragma once

#include "../../../id.hpp"
#include "../../../settings.hpp"
#include "../registers.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/llarm-asm.hpp>

struct arm_decode_struct {
    llarm::as::arm_id id;
    u32 code;
};

struct thumb_decode_struct {
    llarm::as::thumb_id id;
    u16 code;
};


struct DECODE {
    REGISTERS& reg;
    SETTINGS& settings;

    bool has_condition_failed(const id::cond cond) const;

    bool is_arm_instruction_unsupported(const llarm::as::arm_id id) const;
    bool is_thumb_instruction_unsupported(const llarm::as::thumb_id id) const;

    arm_decode_struct arm_decode(const u32 raw_code) const;
    thumb_decode_struct thumb_decode(const u16 raw_code) const;

    DECODE(
        REGISTERS& reg,
        SETTINGS& settings
    );
};