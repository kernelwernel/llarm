#include "string_arm.hpp"
#include "../identifiers/string_shifters.hpp"
#include "../interpreter/interpreter.hpp"
#include "../interpreter/IR.hpp"
#include "../interpreter/tokens.hpp"

using namespace internal;

// binary arm instructions don't really have much of a way to "fail",
// even "faulty" arguments are encoded in ways where it can't be considered
// as an error. So the only real failure for a thumb instruction would
// be to identify an undefined or unknown instruction (me thinks)

bool validation::string_arm::is_arm_instruction_valid(const std::string &code, const u32 PC) {
    return is_arm_instruction_valid(IR::generate(code, PC));
}


bool validation::string_arm::is_arm_instruction_valid(const IR_arm_struct &IR) {
    using namespace interpreter;
    using enum token_enum;
    using enum reg_type;

    const lexemes_t &lexemes = IR.lexemes;

    switch (IR.mnemonic.id) {
        case arm_id::UNKNOWN: return false;
/* TODO */        case arm_id::UNDEFINED: return false;
/* TODO */        case arm_id::NOP: return false;
/* TODO */
/* TODO */        // TODO COMPLETE ALL THE SHIFTERS
/* TODO */
/* TODO */        // addressing mode 1: data processing
/* TODO */        case arm_id::ADC: 
/* TODO */        case arm_id::ADD:
/* TODO */        case arm_id::RSB:
/* TODO */        case arm_id::BIC:
/* TODO */        case arm_id::SUB:
/* TODO */        case arm_id::CMN: // TODO, FUCK THIS INSTRUCTION
/* TODO */        case arm_id::AND:
/* TODO */        case arm_id::CMP:
/* TODO */        case arm_id::RSC:
/* TODO */        case arm_id::SBC:
/* TODO */        case arm_id::EOR:
/* TODO */        case arm_id::ORR:
/* TODO */        case arm_id::TEQ:
/* TODO */        case arm_id::TST:
/* TODO */        case arm_id::MOV:
/* TODO */        case arm_id::MVN:
/* TODO */        case arm_id::CMNP:
/* TODO */        case arm_id::CMPP:
/* TODO */        case arm_id::TEQP:
/* TODO */        case arm_id::TSTP:
/* TODO */
/* TODO */        // addressing mode 2: load store
/* TODO */        case arm_id::LDR:
/* TODO */        case arm_id::LDRB:
/* TODO */        case arm_id::LDRBT:
/* TODO */        case arm_id::LDRT:
/* TODO */        case arm_id::STR: 
/* TODO */        case arm_id::STRB: 
/* TODO */        case arm_id::STRBT:
/* TODO */        case arm_id::STRT:
/* TODO */        
/* TODO */        // addressing mode 3: load store misc
/* TODO */        case arm_id::STRH:
/* TODO */        case arm_id::LDRH:
/* TODO */        case arm_id::LDRSB:
/* TODO */        case arm_id::LDRSH:
/* TODO */        case arm_id::STRD:
/* TODO */        case arm_id::LDRD:
/* TODO */
/* TODO */        // addressing mode 4: load store multiple
/* TODO */        case arm_id::LDM1:
/* TODO */        case arm_id::LDM2:
/* TODO */        case arm_id::LDM3:
/* TODO */        case arm_id::STM1: 
/* TODO */        case arm_id::STM2: 
/* TODO */
/* TODO */        // addressing mode 5: load store coprocessor
/* TODO */        case arm_id::STC: 
/* TODO */        case arm_id::STC2: 
/* TODO */        case arm_id::LDC: 
/* TODO */        case arm_id::LDC2: return (ident::string_shifters::identify_shifter(IR) != shifter_id::UNKNOWN);

        case arm_id::B:
        case arm_id::BL: //return verify_lexemes({ CONST }, lexemes);
        case arm_id::SWI: return verify_lexemes({ immed(24) }, lexemes);

        case arm_id::MCR2: 
        case arm_id::MCR: 
        case arm_id::MRC2:
        case arm_id::MRC:
            return (
                (verify_lexemes({ reg(COPROC), immed(2), reg(), reg(CR), reg(CR), immed(2) }, lexemes)) || 
                (verify_lexemes({ reg(COPROC), immed(2), reg(), reg(CR), reg(CR) }, lexemes))
            );

        case arm_id::SWP:
        case arm_id::SWPB:
            return ((verify_lexemes({ reg(), reg(), token(MEM_START), reg(), token(MEM_END) }, lexemes)));

        case arm_id::QADD:
        case arm_id::QDADD:
        case arm_id::QDSUB:
        case arm_id::QSUB:
        case arm_id::SMULXY:
        case arm_id::SMULWY:
        case arm_id::MUL: return verify_lexemes({ reg(), reg(), reg() }, lexemes);

        case arm_id::MLA:
        case arm_id::SMLAL:
        case arm_id::SMULL:
        case arm_id::UMLAL:
        case arm_id::SMLAXY:
        case arm_id::SMLALXY:
        case arm_id::SMLAWY:
        case arm_id::UMULL: return verify_lexemes({ reg(), reg(), reg(), reg() }, lexemes);
        
        case arm_id::MRS: 
            return (
                (verify_lexemes({ reg(), psr(CPSR) }, lexemes)) ||
                (verify_lexemes({ reg(), psr(SPSR) }, lexemes))
            );
            
        case arm_id::MSR_IMM: // both these instructions are already verified in the identification process
        case arm_id::MSR_REG: return true; 
        case arm_id::BKPT: return verify_lexemes({ immed(16) }, lexemes);
        case arm_id::BLX1:
        case arm_id::BX: return verify_lexemes({ reg() }, lexemes);
        case arm_id::BLX2: return verify_lexemes({ reg() }, lexemes);
        case arm_id::CLZ: return verify_lexemes({ reg(), reg() }, lexemes);
        case arm_id::CDP2:
        case arm_id::CDP: return verify_lexemes({ reg(COPROC), immed(2), reg(CR), reg(CR), reg(CR), immed(2) }, lexemes);
        case arm_id::MCRR:
        case arm_id::MRRC: return verify_lexemes({ reg(COPROC), immed(3), reg(), reg(), reg(CR) }, lexemes);
        
        case arm_id::PLD: return (ident::string_shifters::identify_shifter(lexemes, IR.mnemonic) != shifter_id::UNKNOWN);

        case arm_id::FADDD: 
        case arm_id::FDIVD: 
        case arm_id::FMACD: 
        case arm_id::FMSCD: 
        case arm_id::FMULD: 
        case arm_id::FNMACD: 
        case arm_id::FNMSCD: 
        case arm_id::FNMULD: 
        case arm_id::FSUBD: return verify_lexemes({ reg(DOUBLE), reg(DOUBLE), reg(DOUBLE) }, lexemes);
        
        case arm_id::FTOSIS: 
        case arm_id::FTOUIS: 
        case arm_id::FUITOS: 
        case arm_id::FSITOS: 
        case arm_id::FSQRTS: 
        case arm_id::FNEGS: 
        case arm_id::FCPYS: 
        case arm_id::FCMPS: 
        case arm_id::FABSS: 
        case arm_id::FCMPES: return verify_lexemes({ reg(SINGLE), reg(SINGLE) }, lexemes);
        
        case arm_id::FABSD: 
        case arm_id::FCMPD: 
        case arm_id::FCMPED: 
        case arm_id::FCPYD: 
        case arm_id::FNEGD: 
        case arm_id::FSQRTD: return verify_lexemes({ reg(DOUBLE), reg(DOUBLE) }, lexemes);
        
        case arm_id::FADDS:
        case arm_id::FDIVS:
        case arm_id::FMACS:
        case arm_id::FMSCS:
        case arm_id::FMULS:
        case arm_id::FNMACS:
        case arm_id::FNMSCS:
        case arm_id::FNMULS:
        case arm_id::FSUBS: return verify_lexemes({ reg(SINGLE), reg(SINGLE), reg(SINGLE) }, lexemes);
        
        case arm_id::FTOSID:
        case arm_id::FCVTSD:
        case arm_id::FTOUID: return verify_lexemes({ reg(SINGLE), reg(DOUBLE) }, lexemes);
        
        case arm_id::FCVTDS:
        case arm_id::FUITOD:
        case arm_id::FSITOD: return verify_lexemes({ reg(DOUBLE), reg(SINGLE) }, lexemes);

        case arm_id::FCMPEZS:
        case arm_id::FCMPZS: return verify_lexemes({ reg(SINGLE) }, lexemes);

        case arm_id::FCMPEZD:
        case arm_id::FCMPZD: return verify_lexemes({ reg(DOUBLE) }, lexemes);

        case arm_id::FLDMS:
            return (
                (verify_lexemes({ reg(), token(PRE_INDEX), reg_list_single() }, lexemes)) ||
                (verify_lexemes({ reg(), reg_list_single() }, lexemes))
            );
        
        case arm_id::FMRS: return verify_lexemes({ reg(), reg(SINGLE) }, lexemes);
        case arm_id::FMRX: return verify_lexemes({ reg(), reg(FP_WILDCARD) }, lexemes);
        case arm_id::FMSR: return verify_lexemes({ reg(SINGLE), reg() }, lexemes);
        case arm_id::FMSTAT: return true; // no arguments, so no room for errors
        case arm_id::FMXR: return verify_lexemes({ reg(FP_WILDCARD), reg() }, lexemes);
        case arm_id::FSTMS:
            return (
                (verify_lexemes({ reg(), token(PRE_INDEX), reg_list_single() }, lexemes)) ||
                (verify_lexemes({ reg(), reg_list_single() }, lexemes))
            );

        case arm_id::FLDS:
        case arm_id::FSTS: 
            return (
                (verify_lexemes({ reg(SINGLE), token(MEM_START), reg(), token(MEM_END) }, lexemes)) ||
                (verify_lexemes({ reg(SINGLE), token(MEM_START), reg(), token(HASHTAG), immed(7, 4), token(MEM_END) }, lexemes))
            );

        case arm_id::FLDMD: 
        case arm_id::FSTMX:
        case arm_id::FLDMX:
        case arm_id::FSTMD: 
            return (
                (verify_lexemes({ reg(), token(PRE_INDEX), reg_list_double() }, lexemes)) ||
                (verify_lexemes({ reg(), reg_list_double() }, lexemes))
            );
            
        case arm_id::FMDHR: return verify_lexemes({ reg(DOUBLE), reg() }, lexemes);
        case arm_id::FMDLR: return verify_lexemes({ reg(DOUBLE), reg() }, lexemes);
        case arm_id::FMRDL: return verify_lexemes({ reg(), reg(DOUBLE) }, lexemes);
        case arm_id::FMRDH: return verify_lexemes({ reg(), reg(DOUBLE) }, lexemes);
        case arm_id::FSTD: 
        case arm_id::FLDD: 
            return (
                (verify_lexemes({ reg(DOUBLE), token(MEM_START), reg(), token(MEM_END) }, lexemes)) ||
                (verify_lexemes({ reg(DOUBLE), token(MEM_START), reg(), token(HASHTAG), immed(7, 4), token(MEM_END) }, lexemes))
            );
    }
}