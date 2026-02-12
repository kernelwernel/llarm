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
private:
    REGISTERS& reg;
    SETTINGS& settings;

private:
    bool has_condition_failed(const id::cond cond);

    bool is_arm_instruction_unsupported(const llarm::as::arm_id id);
    bool is_thumb_instruction_unsupported(const llarm::as::thumb_id id);

public:
    arm_decode_struct arm_decode(const u32 raw_code);
    thumb_decode_struct thumb_decode(const u16 raw_code);

    DECODE(
        REGISTERS& reg,
        SETTINGS& settings
    );
};