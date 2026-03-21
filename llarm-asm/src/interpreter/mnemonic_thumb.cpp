#include "interpreter.hpp"
#include "../id/instruction_id.hpp"
#include "mnemonic_thumb.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>
#include <llarm/shared/out.hpp>
#include <llarm/shared/string_view.hpp>

using namespace internal;
using enum token_enum;


//struct mnemonic_struct_thumb {
//    sv instruction = "";
//    thumb_id id = thumb_id::UNKNOWN;
//    cond_id cond_id = cond_id::UNKNOWN; // specifically for B1 instruction
//};


mnemonic_struct_thumb mnemonic_thumb::thumb(const std::string &code) {
    const std::string& assembly = llarm::util::to_upper(code);
    const sv mnemonic = interpreter::fetch_instruction(assembly);

    const thumb_id id = fetch_thumb_id(code, mnemonic);
    const cond_id cond_id = (id == thumb_id::B1 ? fetch_B1_cond_id(mnemonic) : cond_id::NONE);

    return mnemonic_struct_thumb {
        mnemonic,
        id, 
        cond_id
    };
}

thumb_id mnemonic_thumb::fetch_thumb_id(const sv code, const sv mnemonic) {
    for (const auto &inst : pure_thumb_instructions) {
        if (mnemonic == inst.str) {
            return inst.id;
        }
    }

    // this is the point where the instruction could either
    // be a variant (i.e ADD1, ADD2, etc) or it is an invalid
    // string. Categorisation happens after this stage.

    const lexemes_t lexemes = interpreter::analyze(code);

    for (const auto &inst : thumb_subinstructions) {
        if (mnemonic != inst.str) {
            continue;
        }

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

    // this is the stage where further identification happens 
    // due to edgecases, it's basically the last line of defence 
    // before an unknown instruction will be returned

    // B1
    if (mnemonic.front() == 'B' && mnemonic.size() == 3) { // +1 for B, +2 for cond
        const u16 cond_key = static_cast<u16>((mnemonic.at(1) << 8) | mnemonic.at(2));

        if (interpreter::cond_match(cond_key)) {
            return thumb_id::B1;
        }
    }

    return thumb_id::UNDEFINED;
}

cond_id mnemonic_thumb::fetch_B1_cond_id(sv mnemonic) {
    mnemonic.remove_prefix(1);
    return interpreter::fetch_cond_id(mnemonic);
}

thumb_id mnemonic_thumb::ADD(const lexemes_t &lexemes) {
    using namespace interpreter;

    // ADD1
    if (verify_tokens({ REG, REG, HASHTAG, IMMED }, lexemes)) {
        return thumb_id::ADD1;
    }

    // ADD2
    if (verify_tokens({ REG, HASHTAG, IMMED }, lexemes)) {
        return thumb_id::ADD2;
    }

    // ADD3
    if (verify_tokens({ REG, REG, REG }, lexemes)) {
        return thumb_id::ADD3;
    }

    // ADD4
    if (verify_tokens({ REG, REG }, lexemes)) {
        return thumb_id::ADD4;
    }

    // ADD5
    if (verify_tokens({ REG, IMMED, HASHTAG, IMMED, MUL_OP, IMMED }, lexemes)) {
        return thumb_id::ADD5;
    }

    // ADD6
    if (verify_tokens({ REG, IMMED, HASHTAG, IMMED, MUL_OP, IMMED }, lexemes)) {
        return thumb_id::ADD6;
    }

    // ADD7
    if (verify_tokens({ IMMED, HASHTAG, IMMED, MUL_OP, IMMED }, lexemes)) {
        return thumb_id::ADD7;
    }

    llarm::out::error("Unknown ADD thumb instruction variant, cannot be identified");
}


thumb_id mnemonic_thumb::SUB(const lexemes_t &lexemes) {
    using namespace interpreter;

    // SUB1
    if (verify_tokens({ REG, REG, HASHTAG, IMMED }, lexemes)) {
        return thumb_id::SUB1;
    }

    // SUB2
    if (verify_tokens({ REG, HASHTAG, IMMED }, lexemes)) {
        return thumb_id::SUB2;
    }

    // SUB3
    if (verify_tokens({ REG, REG, REG }, lexemes)) {
        return thumb_id::SUB3;
    }

    // SUB4
    if (verify_tokens({ IMMED, HASHTAG, IMMED, MUL_OP, IMMED }, lexemes)) {
        return thumb_id::SUB4;
    }

    llarm::out::error("Unknown SUB thumb instruction variant, cannot be identified");
}


thumb_id mnemonic_thumb::ASR(const lexemes_t &lexemes) {
    using namespace interpreter;

    // ASR1
    if (verify_tokens({ REG, REG, HASHTAG, IMMED }, lexemes)) {
        return thumb_id::ASR1;
    }

    // ASR2
    if (verify_tokens({ REG, REG }, lexemes)) {
        return thumb_id::ASR2;
    }

    llarm::out::error("Unknown ASR thumb instruction variant, cannot be identified");
}


thumb_id mnemonic_thumb::LSL(const lexemes_t &lexemes) {
    using namespace interpreter;

    // LSL1
    if (verify_tokens({ REG, REG, HASHTAG, IMMED }, lexemes)) {
        return thumb_id::LSL1;
    }

    // LSL2
    if (verify_tokens({ REG, REG }, lexemes)) {
        return thumb_id::LSL2;
    }

    llarm::out::error("Unknown LSL thumb instruction variant, cannot be identified");
}


thumb_id mnemonic_thumb::LSR(const lexemes_t &lexemes) {
    using namespace interpreter;

    // LSR1
    if (verify_tokens({ REG, REG, HASHTAG, IMMED }, lexemes)) {
        return thumb_id::LSR1;
    }

    // LSR2
    if (verify_tokens({ REG, REG }, lexemes)) {
        return thumb_id::LSR2;
    }

    llarm::out::error("Unknown LSR thumb instruction variant, cannot be identified");
}


thumb_id mnemonic_thumb::CMP(const lexemes_t &lexemes) {
    using namespace interpreter;

    // CMP1
    if (verify_tokens({ REG, HASHTAG, IMMED }, lexemes)) {
        return thumb_id::CMP1;
    }

    // CMP2
    if (verify_tokens({ REG, REG }, lexemes)) {
        return thumb_id::CMP2;
    }

    // CMP3
    if (verify_tokens({ REG, REG }, lexemes)) {
        return thumb_id::CMP3;
    }

    llarm::out::error("Unknown CMP thumb instruction variant, cannot be identified");
}


thumb_id mnemonic_thumb::MOV(const lexemes_t &lexemes) {
    using namespace interpreter;

    // MOV1
    if (verify_tokens({ REG, HASHTAG, IMMED }, lexemes)) {
        return thumb_id::MOV1;
    }

    // MOV2
    if (verify_tokens({ REG, REG }, lexemes)) {
        return thumb_id::MOV2;
    }

    // MOV3
    if (verify_tokens({ REG, REG }, lexemes)) {
        return thumb_id::MOV3;
    }

    llarm::out::error("Unknown MOV thumb instruction variant, cannot be identified");
}


thumb_id mnemonic_thumb::BLX(const lexemes_t &lexemes) {
    using namespace interpreter;

    // BLX1
    if (verify_tokens({ IMMED }, lexemes)) {
        return thumb_id::BLX1;
    }

    // BLX2
    if (verify_tokens({ REG }, lexemes)) {
        return thumb_id::BLX2;
    }

    llarm::out::error("Unknown BLX thumb instruction variant, cannot be identified");
}


thumb_id mnemonic_thumb::LDR(const lexemes_t &lexemes) {
    using namespace interpreter;

    // LDR1
    if (verify_tokens({ REG, MEM_START, REG, HASHTAG, IMMED, MUL_OP, IMMED, MEM_END }, lexemes)) {
        return thumb_id::LDR1;
    }

    // LDR2
    if (verify_tokens({ REG, MEM_START, REG, REG, MEM_END }, lexemes)) {
        return thumb_id::LDR2;
    }

    // LDR3
    if (verify_tokens({ REG, MEM_START, IMMED, HASHTAG, IMMED, MUL_OP, IMMED, MEM_END }, lexemes)) {
        return thumb_id::LDR3;
    }

    // LDR4
    if (verify_tokens({ REG, MEM_START, IMMED, HASHTAG, IMMED, MUL_OP, IMMED, MEM_END }, lexemes)) {
        return thumb_id::LDR4;
    }

    llarm::out::error("Unknown LDR thumb instruction variant, cannot be identified");
}


thumb_id mnemonic_thumb::LDRB(const lexemes_t &lexemes) {
    using namespace interpreter;

    // LDRB1
    if (verify_tokens({ REG, MEM_START, REG, HASHTAG, IMMED, MEM_END }, lexemes)) {
        return thumb_id::LDRB1;
    }

    // LDRB2
    if (verify_tokens({ REG, MEM_START, REG, REG, MEM_END }, lexemes)) {
        return thumb_id::LDRB2;
    }

    llarm::out::error("Unknown LDRB thumb instruction variant, cannot be identified");
}


thumb_id mnemonic_thumb::LDRH(const lexemes_t &lexemes) {
    using namespace interpreter;

    // LDRH1
    if (verify_tokens({ REG, MEM_START, REG, HASHTAG, IMMED, MUL_OP, IMMED, MEM_END }, lexemes)) {
        return thumb_id::LDRH1;
    }

    // LDRH2
    if (verify_tokens({ REG, MEM_START, REG, REG, MEM_END }, lexemes)) {
        return thumb_id::LDRH2;
    }

    llarm::out::error("Unknown LDRH thumb instruction variant, cannot be identified");
}


thumb_id mnemonic_thumb::STR(const lexemes_t &lexemes) {
    using namespace interpreter;

    // STR1
    if (verify_tokens({ REG, MEM_START, REG, HASHTAG, IMMED, MUL_OP, IMMED, MEM_END }, lexemes)) {
        return thumb_id::STR1;
    }

    // STR2
    if (verify_tokens({ REG, MEM_START, REG, REG, MEM_END }, lexemes)) {
        return thumb_id::STR2;
    }

    // STR3
    if (verify_tokens({ REG, MEM_START, IMMED, HASHTAG, IMMED, MUL_OP, IMMED, MEM_END }, lexemes)) {
        return thumb_id::STR3;
    }

    llarm::out::error("Unknown STR thumb instruction variant, cannot be identified");
}


thumb_id mnemonic_thumb::STRB(const lexemes_t &lexemes) {
    using namespace interpreter;

    // STRB1
    if (verify_tokens({ REG, MEM_START, REG, HASHTAG, IMMED, MEM_END }, lexemes)) {
        return thumb_id::STRB1;
    }

    // STRB2
    if (verify_tokens({ REG, MEM_START, REG, REG, MEM_END }, lexemes)) {
        return thumb_id::STRB2;
    }

    llarm::out::error("Unknown STRB thumb instruction variant, cannot be identified");
}


thumb_id mnemonic_thumb::STRH(const lexemes_t &lexemes) {
    using namespace interpreter;

    // STRH1
    if (verify_tokens({ REG, MEM_START, REG, HASHTAG, IMMED, MUL_OP, IMMED, MEM_END }, lexemes)) {
        return thumb_id::STRB1;
    }

    // STRH2
    if (verify_tokens({ REG, MEM_START, REG, REG, MEM_END }, lexemes)) {
        return thumb_id::STRB2;
    }

    llarm::out::error("Unknown STRH thumb instruction variant, cannot be identified");
}