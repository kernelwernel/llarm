#include "string_thumb.hpp"
#include "../interpreter/interpreter.hpp"
#include "../interpreter/IR.hpp"
#include "../interpreter/tokens.hpp"

using namespace internal;
using namespace interpreter;
using enum token_enum;
using enum special_reg;

// binary arm instructions don't really have much of a way to "fail",
// even "faulty" arguments are encoded in ways where it can't be considered
// as an error. So the only real failure for a thumb instruction would
// be to identify an undefined or unknown instruction (me thinks)

bool validation::string_thumb::is_thumb_instruction_valid(const std::string &code) {
    return is_thumb_instruction_valid(IR::generate_thumb(code));
}


bool validation::string_thumb::is_thumb_instruction_valid(const IR_thumb_struct &IR) {
    const lexemes_t &lexemes = IR.lexemes;

    switch (IR.id) {
        /* ✅ */ case thumb_id::UNKNOWN: return false;
        /* ✅ */ case thumb_id::UNDEFINED: return false;
        /* ✅ */ case thumb_id::NOP: return false;    
        /* ✅ */ case thumb_id::ADD3: return verify_lexemes({ reg_thumb(), reg_thumb(), reg_thumb() }, lexemes);
        /* ✅ */ case thumb_id::LDRH2: return verify_lexemes({ reg_thumb(), reg_thumb(), reg_thumb() }, lexemes);
        /* ✅ */ case thumb_id::SUB3: return verify_lexemes({ reg_thumb(), reg_thumb(), reg_thumb() }, lexemes);
        /* ✅ */ case thumb_id::ADD4: return verify_lexemes({ reg(), reg() }, lexemes);
        /* ✅ */ case thumb_id::CMP3: return verify_lexemes({ reg(), reg() }, lexemes);
        /* ✅ */ case thumb_id::MOV3: return verify_lexemes({ reg(), reg() }, lexemes);
        /* ✅ */ case thumb_id::ADD5: return verify_lexemes({ reg_thumb(), reg(PC), token(HASHTAG), immed(8, 4) }, lexemes);
        /* ✅ */ case thumb_id::ADD6: return verify_lexemes({ reg_thumb(), reg(SP), token(HASHTAG), immed(8, 4) }, lexemes);
        /* ✅ */ case thumb_id::ADD7: return verify_lexemes({ reg(SP), token(HASHTAG), immed(7, 4) }, lexemes);
        /* ✅ */ case thumb_id::ADD1: return verify_lexemes({ reg_thumb(), reg_thumb(), token(HASHTAG), immed(3)}, lexemes);
        /* ✅ */ case thumb_id::SUB1: return verify_lexemes({ reg_thumb(), reg_thumb(), token(HASHTAG), immed(3)}, lexemes);
        /* ✅ */ case thumb_id::SUB2: return verify_lexemes({ reg_thumb(), token(HASHTAG), immed(8) }, lexemes);
        /* ✅ */ case thumb_id::SUB4: return verify_lexemes({ reg(SP), token(HASHTAG), immed(7, 4) }, lexemes);
        /* ✅ */ case thumb_id::ADC: return verify_lexemes({ reg_thumb(), reg_thumb() }, lexemes);
        /* ✅ */ case thumb_id::SBC: return verify_lexemes({ reg_thumb(), reg_thumb() }, lexemes);
        /* ✅ */ case thumb_id::MUL: return verify_lexemes({ reg_thumb(), reg_thumb() }, lexemes);
        /* ✅ */ case thumb_id::AND: return verify_lexemes({ reg_thumb(), reg_thumb() }, lexemes);
        /* ✅ */ case thumb_id::BIC: return verify_lexemes({ reg_thumb(), reg_thumb() }, lexemes);
        /* ✅ */ case thumb_id::EOR: return verify_lexemes({ reg_thumb(), reg_thumb() }, lexemes);
        /* ✅ */ case thumb_id::NEG: return verify_lexemes({ reg_thumb(), reg_thumb() }, lexemes);
        /* ✅ */ case thumb_id::ORR: return verify_lexemes({ reg_thumb(), reg_thumb() }, lexemes);
        /* ✅ */ case thumb_id::ROR: return verify_lexemes({ reg_thumb(), reg_thumb() }, lexemes);
        /* ✅ */ case thumb_id::TST: return verify_lexemes({ reg_thumb(), reg_thumb() }, lexemes);
        /* ✅ */ case thumb_id::CMN: return verify_lexemes({ reg_thumb(), reg_thumb() }, lexemes);
        /* ✅ */ case thumb_id::MVN: return verify_lexemes({ reg_thumb(), reg_thumb() }, lexemes);
        /* ✅ */ case thumb_id::ASR2: return verify_lexemes({ reg_thumb(), reg_thumb() }, lexemes);
        /* ✅ */ case thumb_id::CMP2: return verify_lexemes({ reg_thumb(), reg_thumb() }, lexemes);
        /* ✅ */ case thumb_id::LSL2: return verify_lexemes({ reg_thumb(), reg_thumb() }, lexemes);
        /* ✅ */ case thumb_id::LSR2: return verify_lexemes({ reg_thumb(), reg_thumb() }, lexemes);
        /* ✅ */ case thumb_id::MOV2: return verify_lexemes({ reg_thumb(), reg_thumb() }, lexemes);
        /* ✅ */ case thumb_id::ASR1: return verify_lexemes({ reg_thumb(), reg_thumb(), token(HASHTAG), immed(5) }, lexemes);
        /* ✅ */ case thumb_id::LSR1: return verify_lexemes({ reg_thumb(), reg_thumb(), token(HASHTAG), immed(5) }, lexemes);
        /* ✅ */ case thumb_id::LSL1: return verify_lexemes({ reg_thumb(), reg_thumb(), token(HASHTAG), immed(5) }, lexemes);
        /* ✅ */ case thumb_id::ADD2: return verify_lexemes({ reg_thumb(), token(HASHTAG), immed(8) }, lexemes);
        /* ✅ */ case thumb_id::CMP1: return verify_lexemes({ reg_thumb(), token(HASHTAG), immed(8) }, lexemes);
        /* ✅ */ case thumb_id::MOV1: return verify_lexemes({ reg_thumb(), token(HASHTAG), immed(8) }, lexemes);
        case thumb_id::B1:
        case thumb_id::B2:
        case thumb_id::BLX1:
        case thumb_id::BLX2:
        /* ✅ */ case thumb_id::LDR1: return verify_lexemes({ reg_thumb(), token(MEM_START), reg_thumb(), token(HASHTAG), immed(5, 4), token(MEM_END) }, lexemes); 
        /* ✅ */ case thumb_id::LDR3: return verify_lexemes({ reg_thumb(), token(MEM_START), reg(PC), token(HASHTAG), immed(8, 4), token(MEM_END) }, lexemes);
        /* ✅ */ case thumb_id::LDR4: return verify_lexemes({ reg_thumb(), token(MEM_START), reg(SP), token(HASHTAG), immed(8, 4), token(MEM_END) }, lexemes); 
        /* ✅ */ case thumb_id::STRB1: return verify_lexemes({ reg_thumb(), token(MEM_START), reg_thumb(), token(HASHTAG), immed(5), token(MEM_END) }, lexemes);
        /* ✅ */ case thumb_id::LDRB1: return verify_lexemes({ reg_thumb(), token(MEM_START), reg_thumb(), token(HASHTAG), immed(5), token(MEM_END) }, lexemes);
        /* ✅ */ case thumb_id::LDRSB: return verify_lexemes({ reg_thumb(), token(MEM_START), reg_thumb(), reg_thumb(), token(MEM_END) }, lexemes);
        /* ✅ */ case thumb_id::LDRSH: return verify_lexemes({ reg_thumb(), token(MEM_START), reg_thumb(), reg_thumb(), token(MEM_END) }, lexemes);
        /* ✅ */ case thumb_id::LDRB2: return verify_lexemes({ reg_thumb(), token(MEM_START), reg_thumb(), reg_thumb(), token(MEM_END) }, lexemes);
        /* ✅ */ case thumb_id::STR2: return verify_lexemes({ reg_thumb(), token(MEM_START), reg_thumb(), reg_thumb(), token(MEM_END) }, lexemes);
        /* ✅ */ case thumb_id::STRB2: return verify_lexemes({ reg_thumb(), token(MEM_START), reg_thumb(), reg_thumb(), token(MEM_END) }, lexemes);
        /* ✅ */ case thumb_id::STRH2: return verify_lexemes({ reg_thumb(), token(MEM_START), reg_thumb(), reg_thumb(), token(MEM_END) }, lexemes);
        /* ✅ */ case thumb_id::LDR2: return verify_lexemes({ reg_thumb(), token(MEM_START), reg_thumb(), reg_thumb(), token(MEM_END) }, lexemes);
        /* ✅ */ case thumb_id::LDRH1: return verify_lexemes({ reg_thumb(), token(MEM_START), reg_thumb(), token(HASHTAG), immed(5, 2), token(MEM_END) }, lexemes); 
        /* ✅ */ case thumb_id::STR1: return verify_lexemes({ reg_thumb(), token(MEM_START), reg_thumb(), token(HASHTAG), immed(5, 4), token(MEM_END) }, lexemes); 
        /* ✅ */ case thumb_id::STR3: return verify_lexemes({ reg_thumb(), token(MEM_START), reg(SP), token(HASHTAG), immed(8, 4), token(MEM_END) }, lexemes); 
        /* ✅ */ case thumb_id::STRH1: return verify_lexemes({ reg_thumb(), token(MEM_START), reg_thumb(), token(HASHTAG), immed(5, 2), token(MEM_END) }, lexemes); 
        /* ✅ */ case thumb_id::BKPT: return verify_lexemes({ immed(8) }, lexemes);
        /* ✅ */ case thumb_id::SWI: return verify_lexemes({ immed(8) }, lexemes); // no hashtag for both BKPT and SWI
        case thumb_id::LDMIA: 
        case thumb_id::STMIA: return verify_lexemes({ reg_thumb(), token(PRE_INDEX), reg_list_thumb() }, lexemes);
        case thumb_id::BL: return verify_lexemes({ immed(16) }, lexemes); // TODO TEMPORARY
        /* ✅ */ case thumb_id::BX: return verify_lexemes({ reg() }, lexemes); // R0~R15 is only supported here 
        /* ✅ */ case thumb_id::POP: return verify_lexemes({ reg_list_thumb_optional_PC() }, lexemes);
        /* ✅ */ case thumb_id::PUSH: return verify_lexemes({ reg_list_thumb_optional_LR() }, lexemes);
    }
}