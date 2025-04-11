#pragma once

#include "shared/types.hpp"
#include "../../instruction_set.hpp"
#include "../registers.hpp"
#include "decode.hpp"

#include <charm-asm/charm-asm.hpp>

struct EXECUTE {
private:
    INSTRUCTION_SET& inst_set;

    std::map<charm::as::id::arm, std::function<void(const arm_code_t&)>> arm_map;
    
    std::map<charm::as::id::thumb, std::function<void(const thumb_code_t&)>> thumb_map;
    //std::map<id::jazelle_instruction, std::function<void(const jazelle_code_t&)>> jazelle_map;

public:
    void loader();

    void arm_execute(const arm_decode_struct &code) const;
    
    void thumb_execute(const thumb_decode_struct &code) const;

    //void jazelle_execute(const jazelle_decoded_t &code) const;

    EXECUTE(INSTRUCTION_SET& inst_set);
};