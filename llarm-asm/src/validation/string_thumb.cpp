#include "string_thumb.hpp"
#include "../identifiers/string_thumb.hpp"

#include "../interpreter/interpreter.hpp"
#include "llarm-asm/src/interpreter/IR.hpp"

using namespace internal;

// binary arm instructions don't really have much of a way to "fail",
// even "faulty" arguments are encoded in ways where it can't be considered
// as an error. So the only real failure for a thumb instruction would
// be to identify an undefined or unknown instruction (me thinks)

bool validation::string_thumb::is_thumb_instruction_valid(const std::string &code) {
    return is_thumb_instruction_valid(IR::generate_thumb(code));
}


bool validation::string_thumb::is_thumb_instruction_valid(const IR_thumb_struct &IR) {
    using namespace interpreter;
    
    switch (id) {
        case id::thumb::UNKNOWN: return false;
        case id::thumb::UNDEFINED: return false;
        case id::thumb::NOP: return false;
        case id::thumb::ADD1:
        case id::thumb::ADD2:
        case id::thumb::ADD3:
        case id::thumb::ADD4:
        case id::thumb::ADD5:
        case id::thumb::ADD6:
        case id::thumb::ADD7:
        case id::thumb::SUB1:
        case id::thumb::SUB2:
        case id::thumb::SUB3:
        case id::thumb::SUB4:
        case id::thumb::ASR1:
        case id::thumb::ASR2:
        case id::thumb::LSL1:
        case id::thumb::LSL2:
        case id::thumb::LSR1:
        case id::thumb::LSR2:
        case id::thumb::CMP1:
        case id::thumb::CMP2:
        case id::thumb::CMP3:
        case id::thumb::MOV1:
        case id::thumb::MOV2:
        case id::thumb::MOV3:
        case id::thumb::B1:
        case id::thumb::B2:
        case id::thumb::BLX1:
        case id::thumb::BLX2:
        case id::thumb::LDR1:
        case id::thumb::LDR2:
        case id::thumb::LDR3:
        case id::thumb::LDR4:
        case id::thumb::LDRB1:
        case id::thumb::LDRB2:
        case id::thumb::LDRH1:
        case id::thumb::LDRH2:
        case id::thumb::STR1:
        case id::thumb::STR2:
        case id::thumb::STR3:
        case id::thumb::STRB1:
        case id::thumb::STRB2:
        case id::thumb::STRH1:
        case id::thumb::STRH2: 
            // all variant instruction are already checked beforehand
            // if they're valid, otherwise it would return unknown.
            // So basically, a shortcut can be taken here since we 
            // know they're valid during the identification process.
            return true;

        case id::thumb::ADC: 
        case id::thumb::SBC: 
        case id::thumb::MUL: 
        case id::thumb::AND: 
        case id::thumb::BIC: 
        case id::thumb::EOR: 
        case id::thumb::NEG: 
        case id::thumb::ORR: 
        case id::thumb::ROR: 
        case id::thumb::TST: 
        case id::thumb::CMN: 
        case id::thumb::MVN: return verify_tokens({ REG_THUMB, REG_THUMB }, lexemes);
        case id::thumb::BKPT: 
        case id::thumb::SWI: return verify_tokens({ IMMED_8 }, lexemes); // no hashtag
        case id::thumb::LDRSB: 
        case id::thumb::LDRSH: return verify_tokens({ REG_THUMB, MEM_START, REG_THUMB, REG_THUMB, MEM_END }, lexemes);
        case id::thumb::LDMIA: 
        case id::thumb::STMIA: return verify_tokens({ REG_THUMB, PRE_INDEX, REG_LIST_THUMB }, lexemes);
        case id::thumb::BL: return verify_tokens({ CONST }, lexemes);
        case id::thumb::BX: return verify_tokens({ REG }, lexemes);
        case id::thumb::POP: return verify_tokens({ REG_LIST_THUMB_OPTIONAL_PC }, lexemes);
        case id::thumb::PUSH: return verify_tokens({ REG_LIST_THUMB_OPTIONAL_LR }, lexemes);
    }
}