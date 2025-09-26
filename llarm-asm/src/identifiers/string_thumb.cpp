#include "string_thumb.hpp"
#include "interpreter.hpp"
#include "../instruction_id.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"

using namespace internal;

id::thumb string_thumb::thumb(const std::string &code) {
    const std::string instruction = shared::util::to_upper(code);
    
    const std::string mnemonic = interpreter::fetch_instruction(instruction);

    for (const auto &e : pure_thumb_instructions) {
        if (mnemonic == e.str) {
            return e.id;
        }
    }

    // this is the point where the instruction could either
    // be a variant (i.e ADD1, ADD2, etc) or it is an invalid
    // string. Categorisation happens after this stage.

    const std::vector<std::string> tokens = interpreter::tokenize(instruction);
    const lexemes_t lexemes = interpreter::lexer(tokens);

    for (const auto &inst : thumb_subinstructions) {
        if (mnemonic == inst.str) {
            switch (inst.id) {
                case sub_inst::ADD: return ADD(lexemes);
                case sub_inst::SUB: return SUB(lexemes);
                case sub_inst::ASR: return ASR(lexemes);
                case sub_inst::LSL: return LSL(lexemes);
                case sub_inst::LSR: return LSR(lexemes);
                case sub_inst::CMP: return CMP(lexemes);
                case sub_inst::MOV: return MOV(lexemes);
                case sub_inst::BLX: return BLX(lexemes);
                case sub_inst::LDR: return LDR(lexemes);
                case sub_inst::LDRB: return LDRB(lexemes);
                case sub_inst::LDRH: return LDRH(lexemes);
                case sub_inst::STR: return STR(lexemes);
                case sub_inst::STRB: return STRB(lexemes);
                case sub_inst::STRH: return STRH(lexemes);
                default: break;
            }
        }
    }

    // this is the stage where further identification happens 
    // due to edgecases, it's basically the last line of defence 
    // before an unknown instruction will be returned

    // B1
    if (mnemonic.front() == 'B' && mnemonic.size() == 3) { // +1 for B, +2 for cond
        const u16 cond_key = (mnemonic.at(1) << 8) | (mnemonic.at(2));

        if (interpreter::cond_match(cond_key)) {
            return id::thumb::B1;
        }
    }

    return id::thumb::UNDEFINED;
}


id::thumb string_thumb::ADD(const lexemes_t &lexemes) {
    using namespace interpreter;

    // ADD1
    if (has_matching_pattern({ REG_THUMB, REG_THUMB, IMMED_3 }, lexemes)) {
        return id::thumb::ADD1;
    }

    // ADD2
    if (has_matching_pattern({ REG_THUMB, IMMED_8 }, lexemes)) {
        return id::thumb::ADD2;
    }

    // ADD3
    if (has_matching_pattern({ REG_THUMB, REG_THUMB, REG_THUMB }, lexemes)) {
        return id::thumb::ADD3;
    }

    // ADD4
    if (has_matching_pattern({ REG, REG }, lexemes)) {
        return id::thumb::ADD4;
    }

    // ADD5
    if (has_matching_pattern({ REG_THUMB, REG_PC, IMMED_8, MUL_OP, INTEGER_4 }, lexemes)) {
        return id::thumb::ADD5;
    }

    // ADD6
    if (has_matching_pattern({ REG_THUMB, REG_SP, IMMED_8, MUL_OP, INTEGER_4 }, lexemes)) {
        return id::thumb::ADD6;
    }

    // ADD7
    if (has_matching_pattern({ REG_SP, IMMED_7, MUL_OP, INTEGER_4 }, lexemes)) {
        return id::thumb::ADD7;
    }

    shared::out::error("Unknown ADD thumb instruction variant, cannot be identified");
}


id::thumb string_thumb::SUB(const lexemes_t &lexemes) {
    using namespace interpreter;

    // SUB1
    if (has_matching_pattern({ REG_THUMB, REG_THUMB, IMMED_3 }, lexemes)) {
        return id::thumb::SUB1;
    }

    // SUB2
    if (has_matching_pattern({ REG_THUMB, IMMED_8 }, lexemes)) {
        return id::thumb::SUB2;
    }

    // SUB3
    if (has_matching_pattern({ REG_THUMB, REG_THUMB, REG_THUMB }, lexemes)) {
        return id::thumb::SUB3;
    }

    // SUB4
    if (has_matching_pattern({ REG_SP, IMMED_7, MUL_OP, INTEGER_4 }, lexemes)) {
        return id::thumb::SUB4;
    }

    shared::out::error("Unknown SUB thumb instruction variant, cannot be identified");
}


id::thumb string_thumb::ASR(const lexemes_t &lexemes) {
    using namespace interpreter;

    // ASR1
    if (has_matching_pattern({ REG_THUMB, REG_THUMB, IMMED_5 }, lexemes)) {
        return id::thumb::ASR1;
    }

    // ASR2
    if (has_matching_pattern({ REG_THUMB, REG_THUMB }, lexemes)) {
        return id::thumb::ASR2;
    }

    shared::out::error("Unknown ASR thumb instruction variant, cannot be identified");
}


id::thumb string_thumb::LSL(const lexemes_t &lexemes) {
    using namespace interpreter;

    // LSL1
    if (has_matching_pattern({ REG_THUMB, REG_THUMB, IMMED_5 }, lexemes)) {
        return id::thumb::LSL1;
    }

    // LSL2
    if (has_matching_pattern({ REG_THUMB, REG_THUMB }, lexemes)) {
        return id::thumb::LSL2;
    }

    shared::out::error("Unknown LSL thumb instruction variant, cannot be identified");
}


id::thumb string_thumb::LSR(const lexemes_t &lexemes) {
    using namespace interpreter;

    // LSR1
    if (has_matching_pattern({ REG_THUMB, REG_THUMB, IMMED_5 }, lexemes)) {
        return id::thumb::LSR1;
    }

    // LSR2
    if (has_matching_pattern({ REG_THUMB, REG_THUMB }, lexemes)) {
        return id::thumb::LSR2;
    }

    shared::out::error("Unknown LSR thumb instruction variant, cannot be identified");
}


id::thumb string_thumb::CMP(const lexemes_t &lexemes) {
    using namespace interpreter;

    // CMP1
    if (has_matching_pattern({ REG_THUMB, IMMED_8 }, lexemes)) {
        return id::thumb::CMP1;
    }

    // CMP2
    if (has_matching_pattern({ REG_THUMB, REG_THUMB }, lexemes)) {
        return id::thumb::CMP2;
    }

    // CMP3
    if (has_matching_pattern({ REG, REG }, lexemes)) {
        return id::thumb::CMP3;
    }

    shared::out::error("Unknown CMP thumb instruction variant, cannot be identified");
}


id::thumb string_thumb::MOV(const lexemes_t &lexemes) {
    using namespace interpreter;

    // MOV1
    if (has_matching_pattern({ REG_THUMB, IMMED_8 }, lexemes)) {
        return id::thumb::MOV1;
    }

    // MOV2
    if (has_matching_pattern({ REG_THUMB, REG_THUMB }, lexemes)) {
        return id::thumb::MOV2;
    }

    // MOV3
    if (has_matching_pattern({ REG, REG }, lexemes)) {
        return id::thumb::MOV3;
    }

    shared::out::error("Unknown MOV thumb instruction variant, cannot be identified");
}


id::thumb string_thumb::BLX(const lexemes_t &lexemes) {
    using namespace interpreter;

    // BLX1
    if (has_matching_pattern({ INTEGER }, lexemes)) {
        return id::thumb::BLX1;
    }

    // BLX2
    if (has_matching_pattern({ REG }, lexemes)) {
        return id::thumb::BLX2;
    }

    shared::out::error("Unknown BLX thumb instruction variant, cannot be identified");
}


id::thumb string_thumb::LDR(const lexemes_t &lexemes) {
    using namespace interpreter;

    // LDR1
    if (has_matching_pattern({ REG_THUMB, MEM_START, REG_THUMB, IMMED_5, MUL_OP, INTEGER_4, MEM_END }, lexemes)) {
        return id::thumb::LDR1;
    }

    // LDR2
    if (has_matching_pattern({ REG_THUMB, MEM_START, REG_THUMB, REG_THUMB, MEM_END }, lexemes)) {
        return id::thumb::LDR2;
    }

    // LDR3
    if (has_matching_pattern({ REG_THUMB, MEM_START, REG_PC, IMMED_8, MUL_OP, INTEGER_4, MEM_END }, lexemes)) {
        return id::thumb::LDR3;
    }

    // LDR4
    if (has_matching_pattern({ REG_THUMB, MEM_START, REG_SP, IMMED_8, MUL_OP, INTEGER_4, MEM_END }, lexemes)) {
        return id::thumb::LDR4;
    }

    shared::out::error("Unknown LDR thumb instruction variant, cannot be identified");
}


id::thumb string_thumb::LDRB(const lexemes_t &lexemes) {
    using namespace interpreter;

    // LDRB1
    if (has_matching_pattern({ REG_THUMB, MEM_START, REG_THUMB, IMMED_5, MEM_END }, lexemes)) {
        return id::thumb::LDRB1;
    }

    // LDRB2
    if (has_matching_pattern({ REG_THUMB, MEM_START, REG_THUMB, REG_THUMB, MEM_END }, lexemes)) {
        return id::thumb::LDRB2;
    }

    shared::out::error("Unknown LDRB thumb instruction variant, cannot be identified");
}


id::thumb string_thumb::LDRH(const lexemes_t &lexemes) {
    using namespace interpreter;

    // LDRH1
    if (has_matching_pattern({ REG_THUMB, MEM_START, REG_THUMB, IMMED_5, MUL_OP, INTEGER_2, MEM_END }, lexemes)) {
        return id::thumb::LDRH1;
    }

    // LDRH2
    if (has_matching_pattern({ REG_THUMB, MEM_START, REG_THUMB, REG_THUMB, MEM_END }, lexemes)) {
        return id::thumb::LDRH2;
    }

    shared::out::error("Unknown LDRH thumb instruction variant, cannot be identified");
}


id::thumb string_thumb::STR(const lexemes_t &lexemes) {
    using namespace interpreter;

    // STR1
    if (has_matching_pattern({ REG_THUMB, MEM_START, REG_THUMB, IMMED_5, MUL_OP, INTEGER_4, MEM_END }, lexemes)) {
        return id::thumb::STR1;
    }

    // STR2
    if (has_matching_pattern({ REG_THUMB, MEM_START, REG_THUMB, REG_THUMB, MEM_END }, lexemes)) {
        return id::thumb::STR2;
    }

    // STR3
    if (has_matching_pattern({ REG_THUMB, MEM_START, REG_SP, IMMED_8, MUL_OP, INTEGER_4, MEM_END }, lexemes)) {
        return id::thumb::STR3;
    }

    shared::out::error("Unknown STR thumb instruction variant, cannot be identified");
}


id::thumb string_thumb::STRB(const lexemes_t &lexemes) {
    using namespace interpreter;

    // STRB1
    if (has_matching_pattern({ REG_THUMB, MEM_START, REG_THUMB, IMMED_5, MEM_END }, lexemes)) {
        return id::thumb::STRB1;
    }

    // STRB2
    if (has_matching_pattern({ REG_THUMB, MEM_START, REG_THUMB, REG_THUMB, MEM_END }, lexemes)) {
        return id::thumb::STRB2;
    }

    shared::out::error("Unknown STRB thumb instruction variant, cannot be identified");
}


id::thumb string_thumb::STRH(const lexemes_t &lexemes) {
    using namespace interpreter;

    // STRH1
    if (has_matching_pattern({ REG_THUMB, MEM_START, REG_THUMB, IMMED_5, MUL_OP, INTEGER_2, MEM_END }, lexemes)) {
        return id::thumb::STRB1;
    }

    // STRH2
    if (has_matching_pattern({ REG_THUMB, MEM_START, REG_THUMB, REG_THUMB, MEM_END }, lexemes)) {
        return id::thumb::STRB2;
    }

    shared::out::error("Unknown STRH thumb instruction variant, cannot be identified");
}