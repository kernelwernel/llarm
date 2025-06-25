#pragma once

#include "decode.hpp"
#include "../../instructions/instructions.hpp"

#include "llarm-emu/src/cpu/exception.hpp"

#include <llarm-asm/llarm-asm.hpp>

struct EXECUTE {
private:
    INSTRUCTIONS& instructions;
    EXCEPTION& exception;

public:
    void arm_execute(const arm_decode_struct &code);
    
    void thumb_execute(const thumb_decode_struct &code);

    EXECUTE(INSTRUCTIONS& instructions, EXCEPTION& exception);
};