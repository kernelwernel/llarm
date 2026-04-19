#pragma once

#include "decode.hpp"
#include "../../instructions/instructions.hpp"
#include "../exception.hpp"

struct EXECUTE {
    INSTRUCTIONS& instructions;
    EXCEPTION& exception;

    void arm_execute(const arm_decode_struct &instruction);
    
    void thumb_execute(const thumb_decode_struct &instruction);

    EXECUTE(
        INSTRUCTIONS& instructions, 
        EXCEPTION& exception
    ) : instructions(instructions), 
        exception(exception) 
    {

    }
};