#include "IR.hpp"
#include "IR_struct.hpp"
#include "operands.hpp"
#include "mnemonic.hpp"

using namespace internal;

IR_arm_struct IR::generate(const std::string &code, const u32 PC) {
    const lexemes_t& lexemes = interpreter::analyze(code);
    const mnemonic_struct& mnemonic = mnemonic::arm(code);
    const operand_struct& operands = operands::lex_to_operands(lexemes, mnemonic);

    return IR_arm_struct {
        lexemes,
        mnemonic,
        operands,
        PC
    };
}

//IR_thumb_struct IR::generate_thumb(const std::string &code) {
//    return IR_thumb_struct {
//        ident::string_thumb::thumb(code), // id
//        interpreter::analyze(code), // lexemes
//        interpreter::fetch_instruction(code) // mnemonic
//    };
//}