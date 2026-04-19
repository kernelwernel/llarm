#include "string_thumb.hpp"
#include "../interpreter/interpreter.hpp"
#include "../interpreter/IR.hpp"
#include "../interpreter/tokens.hpp"

using namespace internal;
using namespace interpreter;
using enum token_enum;
using enum special_reg;

bool validation::string_thumb::is_B1_valid(const u32 PC, const lexemes_t& lexemes) {
    if (lexemes.front().token_type != token_enum::IMMED) {
        return false;
    }

    const u32 target_address = static_cast<u32>(lexemes.front().data.imm.number);
    const i64 offset = static_cast<i64>(target_address) - (static_cast<i64>(PC) + 4);
    return !(offset & 0x1) && offset >= -256 && offset <= 254;
}


bool validation::string_thumb::is_B2_valid(const u32 PC, const lexemes_t& lexemes) {
    if (lexemes.front().token_type != token_enum::IMMED) {
        return false;
    }

    const u32 target_address = static_cast<u32>(lexemes.front().data.imm.number);
    const i64 offset = static_cast<i64>(target_address) - (static_cast<i64>(PC) + 4);
    return !(offset & 0x1) && offset >= -2048 && offset <= 2046;
}


bool validation::string_thumb::is_bl_blx_target_valid(const u32 PC, const lexemes_t& lexemes, const bool is_blx) {
    if (lexemes.front().token_type != token_enum::IMMED) {
        return false;
    }

    const u32 target_address = static_cast<u32>(lexemes.front().data.imm.number);

    // BLX target must be word-aligned (ARM mode), BL just halfword-aligned
    if (is_blx && (target_address & 0x3)) {
        return false;
    }

    if (!is_blx && (target_address & 0x1)) {
        return false;
    }

    const i64 offset = static_cast<i64>(target_address) - (static_cast<i64>(PC) + 4);
    return offset >= -4194304 && offset <= 4194302;
}

bool validation::string_thumb::is_thumb_instruction_valid(const std::string& code) {
    return is_thumb_instruction_valid(IR::generate_thumb(code));
}


bool validation::string_thumb::is_thumb_instruction_valid(const IR_thumb_struct& IR) {
    const lexemes_t& lexemes = IR.lexemes;

    switch (IR.mnemonic.id) {
        case thumb_id::UNKNOWN: return false;
        case thumb_id::UNDEFINED: return false;
        case thumb_id::NOP: return false;    
        case thumb_id::ADD3: return verify_lexemes(make_lexemes(reg_thumb(), reg_thumb(), reg_thumb()), lexemes);
        case thumb_id::LDRH2: return verify_lexemes(make_lexemes(reg_thumb(), reg_thumb(), reg_thumb()), lexemes);
        case thumb_id::SUB3: return verify_lexemes(make_lexemes(reg_thumb(), reg_thumb(), reg_thumb()), lexemes);
        case thumb_id::ADD4: return verify_lexemes(make_lexemes(reg(), reg()), lexemes);
        case thumb_id::CMP3: return verify_lexemes(make_lexemes(reg(), reg()), lexemes);
        case thumb_id::MOV3: return verify_lexemes(make_lexemes(reg(), reg()), lexemes);
        case thumb_id::ADD5: return verify_lexemes(make_lexemes(reg_thumb(), reg(PC), token(HASHTAG), immed(8, 4)), lexemes);
        case thumb_id::ADD6: return verify_lexemes(make_lexemes(reg_thumb(), reg(SP), token(HASHTAG), immed(8, 4)), lexemes);
        case thumb_id::ADD7: return verify_lexemes(make_lexemes(reg(SP), token(HASHTAG), immed(7, 4)), lexemes);
        case thumb_id::ADD1: return verify_lexemes(make_lexemes(reg_thumb(), reg_thumb(), token(HASHTAG), immed(3)), lexemes);
        case thumb_id::SUB1: return verify_lexemes(make_lexemes(reg_thumb(), reg_thumb(), token(HASHTAG), immed(3)), lexemes);
        case thumb_id::SUB2: return verify_lexemes(make_lexemes(reg_thumb(), token(HASHTAG), immed(8)), lexemes);
        case thumb_id::SUB4: return verify_lexemes(make_lexemes(reg(SP), token(HASHTAG), immed(7, 4)), lexemes);
        case thumb_id::ADC: return verify_lexemes(make_lexemes(reg_thumb(), reg_thumb()), lexemes);
        case thumb_id::SBC: return verify_lexemes(make_lexemes(reg_thumb(), reg_thumb()), lexemes);
        case thumb_id::MUL: return verify_lexemes(make_lexemes(reg_thumb(), reg_thumb()), lexemes);
        case thumb_id::AND: return verify_lexemes(make_lexemes(reg_thumb(), reg_thumb()), lexemes);
        case thumb_id::BIC: return verify_lexemes(make_lexemes(reg_thumb(), reg_thumb()), lexemes);
        case thumb_id::EOR: return verify_lexemes(make_lexemes(reg_thumb(), reg_thumb()), lexemes);
        case thumb_id::NEG: return verify_lexemes(make_lexemes(reg_thumb(), reg_thumb()), lexemes);
        case thumb_id::ORR: return verify_lexemes(make_lexemes(reg_thumb(), reg_thumb()), lexemes);
        case thumb_id::ROR: return verify_lexemes(make_lexemes(reg_thumb(), reg_thumb()), lexemes);
        case thumb_id::TST: return verify_lexemes(make_lexemes(reg_thumb(), reg_thumb()), lexemes);
        case thumb_id::CMN: return verify_lexemes(make_lexemes(reg_thumb(), reg_thumb()), lexemes);
        case thumb_id::MVN: return verify_lexemes(make_lexemes(reg_thumb(), reg_thumb()), lexemes);
        case thumb_id::ASR2: return verify_lexemes(make_lexemes(reg_thumb(), reg_thumb()), lexemes);
        case thumb_id::CMP2: return verify_lexemes(make_lexemes(reg_thumb(), reg_thumb()), lexemes);
        case thumb_id::LSL2: return verify_lexemes(make_lexemes(reg_thumb(), reg_thumb()), lexemes);
        case thumb_id::LSR2: return verify_lexemes(make_lexemes(reg_thumb(), reg_thumb()), lexemes);
        case thumb_id::MOV2: return verify_lexemes(make_lexemes(reg_thumb(), reg_thumb()), lexemes);
        case thumb_id::ASR1: return verify_lexemes(make_lexemes(reg_thumb(), reg_thumb(), token(HASHTAG), immed(5)), lexemes);
        case thumb_id::LSR1: return verify_lexemes(make_lexemes(reg_thumb(), reg_thumb(), token(HASHTAG), immed(5)), lexemes);
        case thumb_id::LSL1: return verify_lexemes(make_lexemes(reg_thumb(), reg_thumb(), token(HASHTAG), immed(5)), lexemes);
        case thumb_id::ADD2: return verify_lexemes(make_lexemes(reg_thumb(), token(HASHTAG), immed(8)), lexemes);
        case thumb_id::CMP1: return verify_lexemes(make_lexemes(reg_thumb(), token(HASHTAG), immed(8)), lexemes);
        case thumb_id::MOV1: return verify_lexemes(make_lexemes(reg_thumb(), token(HASHTAG), immed(8)), lexemes);
        case thumb_id::B1: return is_B1_valid(IR.PC, lexemes);
        case thumb_id::B2: return is_B2_valid(IR.PC, lexemes);
        case thumb_id::BLX1: return is_bl_blx_target_valid(IR.PC, lexemes, true);
        case thumb_id::BL_BLX1_PREFIX: return false; // this should not be identified as an instruction in the thumb string instruction, it's only valid in binary
        case thumb_id::BL: return is_bl_blx_target_valid(IR.PC, lexemes, false);
        case thumb_id::BLX2: return verify_lexemes(make_lexemes(reg()), lexemes); 
        case thumb_id::LDR1: return verify_lexemes(make_lexemes(reg_thumb(), token(MEM_START), reg_thumb(), token(HASHTAG), immed(5, 4), token(MEM_END)), lexemes); 
        case thumb_id::LDR3: return verify_lexemes(make_lexemes(reg_thumb(), token(MEM_START), reg(PC), token(HASHTAG), immed(8, 4), token(MEM_END)), lexemes);
        case thumb_id::LDR4: return verify_lexemes(make_lexemes(reg_thumb(), token(MEM_START), reg(SP), token(HASHTAG), immed(8, 4), token(MEM_END)), lexemes); 
        case thumb_id::STRB1: return verify_lexemes(make_lexemes(reg_thumb(), token(MEM_START), reg_thumb(), token(HASHTAG), immed(5), token(MEM_END)), lexemes);
        case thumb_id::LDRB1: return verify_lexemes(make_lexemes(reg_thumb(), token(MEM_START), reg_thumb(), token(HASHTAG), immed(5), token(MEM_END)), lexemes);
        case thumb_id::LDRSB: return verify_lexemes(make_lexemes(reg_thumb(), token(MEM_START), reg_thumb(), reg_thumb(), token(MEM_END)), lexemes);
        case thumb_id::LDRSH: return verify_lexemes(make_lexemes(reg_thumb(), token(MEM_START), reg_thumb(), reg_thumb(), token(MEM_END)), lexemes);
        case thumb_id::LDRB2: return verify_lexemes(make_lexemes(reg_thumb(), token(MEM_START), reg_thumb(), reg_thumb(), token(MEM_END)), lexemes);
        case thumb_id::STR2: return verify_lexemes(make_lexemes(reg_thumb(), token(MEM_START), reg_thumb(), reg_thumb(), token(MEM_END)), lexemes);
        case thumb_id::STRB2: return verify_lexemes(make_lexemes(reg_thumb(), token(MEM_START), reg_thumb(), reg_thumb(), token(MEM_END)), lexemes);
        case thumb_id::STRH2: return verify_lexemes(make_lexemes(reg_thumb(), token(MEM_START), reg_thumb(), reg_thumb(), token(MEM_END)), lexemes);
        case thumb_id::LDR2: return verify_lexemes(make_lexemes(reg_thumb(), token(MEM_START), reg_thumb(), reg_thumb(), token(MEM_END)), lexemes);
        case thumb_id::LDRH1: return verify_lexemes(make_lexemes(reg_thumb(), token(MEM_START), reg_thumb(), token(HASHTAG), immed(5, 2), token(MEM_END)), lexemes); 
        case thumb_id::STR1: return verify_lexemes(make_lexemes(reg_thumb(), token(MEM_START), reg_thumb(), token(HASHTAG), immed(5, 4), token(MEM_END)), lexemes); 
        case thumb_id::STR3: return verify_lexemes(make_lexemes(reg_thumb(), token(MEM_START), reg(SP), token(HASHTAG), immed(8, 4), token(MEM_END)), lexemes); 
        case thumb_id::STRH1: return verify_lexemes(make_lexemes(reg_thumb(), token(MEM_START), reg_thumb(), token(HASHTAG), immed(5, 2), token(MEM_END)), lexemes); 
        case thumb_id::BKPT: return verify_lexemes(make_lexemes(immed(8)), lexemes);
        case thumb_id::SWI: return verify_lexemes(make_lexemes(immed(8)), lexemes); // no hashtag for both BKPT and SWI
        case thumb_id::LDMIA: return verify_lexemes(make_lexemes(reg_thumb(), token(PRE_INDEX), reg_list_thumb()), lexemes);
        case thumb_id::STMIA: return verify_lexemes(make_lexemes(reg_thumb(), token(PRE_INDEX), reg_list_thumb()), lexemes);
        case thumb_id::BX: return verify_lexemes(make_lexemes(reg()), lexemes); // R0~R15 is only supported here 
        case thumb_id::POP: return verify_lexemes(make_lexemes(reg_list_thumb_optional_PC()), lexemes);
        case thumb_id::PUSH: return verify_lexemes(make_lexemes(reg_list_thumb_optional_LR()), lexemes);
    }
}