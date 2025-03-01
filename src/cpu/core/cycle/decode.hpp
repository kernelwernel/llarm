#pragma once

#include "../../../types.hpp"
#include "../../../id.hpp"
#include "../../../constants.hpp"
#include "../../../settings.hpp"
#include "../../instruction_set.hpp"
#include "../registers.hpp"

#include <bitset>
#include <tuple>
#include <functional>

struct DECODE {
private:
    INSTRUCTION_SET& inst_set;
    REGISTERS& reg;
    MEMORY& memory;
    SETTINGS& settings;

private:
    struct arm_scan {
        id::arm_instruction instruction_id;
        std::function<bool(const arm_code_t&)> opcode_function;
    };

    struct thumb_scan {
        id::thumb_instruction instruction_id;
        std::function<bool(const thumb_code_t&)> opcode_function;
    };

    struct jazelle_scan {
        id::jazelle_instruction instruction_id;
        std::function<bool(const jazelle_code_t)> opcode_function;
    };

    std::vector<arm_scan> arm_vector;
    std::vector<thumb_scan> thumb_vector;
    std::vector<jazelle_scan> jazelle_vector;


    id::arm_instruction arm_identifier(const arm_code_t &raw_code) const;

    // TODO: benchmark with maybe a std::execution iterator
    id::thumb_instruction thumb_identifier(const thumb_code_t &raw_code) const;

    id::jazelle_instruction jazelle_identifier(const jazelle_code_t raw_code) const;

    bool condition_match(const id::cond cond) const;

    void loader();

public:
    DECODE(
        INSTRUCTION_SET& inst_set,
        REGISTERS& reg,
        MEMORY& memory,
        SETTINGS& settings
    ) : inst_set(inst_set),
        reg(reg),
        memory(memory),
        settings(settings)
    {
        
    }

    arm_decoded_t arm_decode(const arm_code_t &raw_code) const;

    thumb_decoded_t thumb_decode(const thumb_code_t &raw_code) const;

    jazelle_decoded_t jazelle_decode(const jazelle_code_t raw_code) const;
};