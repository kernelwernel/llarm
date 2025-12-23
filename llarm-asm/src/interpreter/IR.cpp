#include "IR.hpp"

#include "../identifiers/string_arm.hpp"
#include "../identifiers/string_thumb.hpp"

IR_arm_struct IR::generate(const std::string &code) {
    return IR_arm_struct {
        ident::string_arm::arm(code), // id
        interpreter::analyze(code), // lexemes
        interpreter::fetch_instruction(code) // mnemonic
    };
}

IR_thumb_struct IR::generate_thumb(const std::string &code) {
    return IR_thumb_struct {
        ident::string_thumb::thumb(code), // id
        interpreter::analyze(code), // lexemes
        interpreter::fetch_instruction(code) // mnemonic
    };
}