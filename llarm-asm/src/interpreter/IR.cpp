#include "IR.hpp"
#include "IR_struct.hpp"
#include "interpreter.hpp"
#include "../id/shifter_id.hpp"
#include "operands.hpp"
#include "mnemonic_arm.hpp"
#include "mnemonic_thumb.hpp"
#include "../identifiers/string_shifters.hpp"

using namespace internal;

IR_arm_struct IR::generate(const std::string &code, const u32 PC) {
    const lexemes_t& lexemes = interpreter::analyze(code);
    const mnemonic_struct_arm& mnemonic = mnemonic_arm::arm(code);
    const operand_struct& operands = operands::lex_to_operands_arm(lexemes, mnemonic);
    const shifter_id shifter_id = ident::string_shifters::identify_shifter(lexemes, mnemonic);

    return IR_arm_struct {
        lexemes,
        mnemonic,
        operands,
        PC,
        shifter_id
    };
}

IR_thumb_struct IR::generate_thumb(const std::string &code, const u32 PC) {
    const mnemonic_struct_thumb& mnemonic = mnemonic_thumb::thumb(code);
    const lexemes_t& lexemes = interpreter::analyze(code);
    const operand_struct& operands = operands::lex_to_operands_thumb(lexemes, mnemonic);

    return IR_thumb_struct {
        lexemes,
        mnemonic,
        operands,
        PC
    };
}