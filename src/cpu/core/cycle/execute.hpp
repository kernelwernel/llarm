#pragma once

#include "types.hpp"
#include "cpu/instruction_set.hpp"
#include "cpu/core/registers.hpp"
#include "cpu/core/cycle/decode.hpp"

struct EXECUTE {
private:
    INSTRUCTION_SET& inst_set;
    REGISTERS& reg;

    std::map<id::arm_instruction, std::function<void(const arm_code_t&, [[maybe_unused]] REGISTERS&)>> arm_map;
    std::map<id::thumb_instruction, std::function<void(const thumb_code_t&, [[maybe_unused]] REGISTERS&)>> thumb_map;
    std::map<id::jazelle_instruction, std::function<void(const jazelle_code_t&, [[maybe_unused]] REGISTERS&)>> jazelle_map;

public:
    void loader();

    void arm_execute(const arm_decoded_t &code) const;
    
    void thumb_execute(const thumb_decoded_t &code) const;

    void jazelle_execute(const jazelle_decoded_t &code) const;

    EXECUTE(
        INSTRUCTION_SET& inst_set,
        REGISTERS& reg
    );
};