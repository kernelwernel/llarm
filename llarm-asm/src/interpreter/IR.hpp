#pragma once

#include "lexer.hpp"
#include "mnemonic.hpp"
#include "../id/instruction_id.hpp"

// this file is meant for IR (Intermediate Representation) of instructions.
// It's not exactly the same concept as what you'd hear like in compilers,
// because this is intended more as a caching mechanism for the sake of
// eliminating a duplication (or triplication) of effort. 

using namespace internal;

struct IR_arm_struct {
    arm_id id;
    lexemes_t lexemes;
    mnemonic_struct mnemonic;
    u32 PC;
};

//struct IR_thumb_struct {
//    thumb_id id;
//    lexemes_t lexemes;
//    sv mnemonic;
//};

namespace IR {
    IR_arm_struct generate(const std::string &code, const u32 PC = 0);
    //IR_thumb_struct generate_thumb(const std::string &code);
}