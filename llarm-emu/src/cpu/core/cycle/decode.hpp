#pragma once

#include "../../../id.hpp"
#include "../../../settings.hpp"
#include "../registers.hpp"

#include <llarm/shared/types.hpp>

#include <llarm-asm/llarm-asm.hpp>

struct arm_decode_struct {
    llarm::as::id::arm id;
    u32 code;
};

struct thumb_decode_struct {
    llarm::as::id::thumb id;
    u16 code;
};


struct DECODE {
private:
    REGISTERS& reg;
    SETTINGS& settings;

private:
    bool has_condition_failed(const id::cond cond);

    bool is_arm_instruction_unsupported(const llarm::as::id::arm id);
    bool is_thumb_instruction_unsupported(const llarm::as::id::thumb id);

public:
    arm_decode_struct arm_decode(const u32 raw_code);
    thumb_decode_struct thumb_decode(const u16 raw_code);

    DECODE(
        REGISTERS& reg,
        SETTINGS& settings
    );
};