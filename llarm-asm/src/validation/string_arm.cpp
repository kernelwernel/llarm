#include "string_arm.hpp"
#include "../identifiers/string_arm.hpp"
#include "../identifiers/string_shifters.hpp"

#include "../interpreter/interpreter.hpp"
#include "llarm-asm/src/interpreter/IR.hpp"
#include "llarm-asm/src/interpreter/tokens.hpp"

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

    switch (IR.mnemonic.id) {
        case arm_id::UNKNOWN: return false;
        case arm_id::UNDEFINED: return false;
        case arm_id::NOP: return false;

        // TODO COMPLETE ALL THE SHIFTERS

        // addressing mode 1: data processing
        case arm_id::ADC: 
        case arm_id::ADD:
        case arm_id::RSB:
        case arm_id::BIC:
        case arm_id::SUB:
        case arm_id::CMN: // TODO, FUCK THIS INSTRUCTION
        case arm_id::AND:
        case arm_id::CMP:
        case arm_id::RSC:
        case arm_id::SBC:
        case arm_id::EOR:
        case arm_id::ORR:
        case arm_id::TEQ:
        case arm_id::TST:
        case arm_id::MOV:
        case arm_id::MVN:
        case arm_id::CMNP:
        case arm_id::CMPP:
        case arm_id::TEQP:
        case arm_id::TSTP:

        // addressing mode 2: load store
        case arm_id::LDR:
        case arm_id::LDRB:
        case arm_id::LDRBT:
        case arm_id::LDRT:
        case arm_id::STR: 
        case arm_id::STRB: 
        case arm_id::STRBT:
        case arm_id::STRT:
        
        // addressing mode 3: load store misc
        case arm_id::STRH:
        case arm_id::LDRH:
        case arm_id::LDRSB:
        case arm_id::LDRSH:
        case arm_id::STRD:
        case arm_id::LDRD:

        // addressing mode 4: load store multiple
        case arm_id::LDM1:
        case arm_id::LDM2:
        case arm_id::LDM3:
        case arm_id::STM1: 
        case arm_id::STM2: 

        // addressing mode 5: load store coprocessor
        case arm_id::STC: 
        case arm_id::STC2: 
        case arm_id::LDC: 
        case arm_id::LDC2: return (ident::string_shifters::identify_shifter(IR) != shifter_id::UNKNOWN);

        case arm_id::B:
        case arm_id::BL: //return verify_tokens({ CONST }, lexemes);
        case arm_id::SWI: return verify_tokens({ IMMED_24 }, lexemes);
            return verify_tokens({  }, lexemes);

        case arm_id::MCR2: 
        case arm_id::MCR: 
        case arm_id::MRC2:
        case arm_id::MRC:
            return (
                (verify_tokens({ COPROCESSOR, IMMED, REG, CR_REG, CR_REG, IMMED }, lexemes)) || 
                (verify_tokens({ COPROCESSOR, IMMED, REG, CR_REG, CR_REG }, lexemes))
            );

        case arm_id::SWP:
        case arm_id::SWPB:
            return (
                (verify_tokens({ REG, REG, REG }, lexemes)) || 
                (verify_tokens({ REG, REG }, lexemes))
            );

        case arm_id::QADD:
        case arm_id::QDADD:
        case arm_id::QDSUB:
        case arm_id::QSUB:
        case arm_id::SMULXY:
        case arm_id::SMULWY:
        case arm_id::MUL: return verify_tokens({ REG, REG, REG }, lexemes);

        case arm_id::MLA:
        case arm_id::SMLAL:
        case arm_id::SMULL:
        case arm_id::UMLAL:
        case arm_id::SMLAXY:
        case arm_id::SMLALXY:
        case arm_id::SMLAWY:
        case arm_id::UMULL: return verify_tokens({ REG, REG, REG, REG }, lexemes);
        
        case arm_id::MRS: 
            return (
                (verify_tokens({ REG, CPSR_FIELD }, lexemes)) ||
                (verify_tokens({ REG, SPSR_FIELD }, lexemes))
            );
            
        case arm_id::MSR_IMM: // both these instructions are already verified in the identification process
        case arm_id::MSR_REG: return true; 
        case arm_id::BKPT: return verify_tokens({ IMMED_16 }, lexemes);
        case arm_id::BLX1:
        case arm_id::BX: return verify_tokens({ REG }, lexemes);
        case arm_id::BLX2: return verify_tokens({ REG }, lexemes);
        case arm_id::CLZ: return verify_tokens({ REG, REG }, lexemes);
        case arm_id::CDP: return verify_tokens({ COPROCESSOR, IMMED, CR_REG, CR_REG, CR_REG, IMMED }, lexemes);
        case arm_id::CDP2: return verify_tokens({ COPROCESSOR, IMMED, CR_REG, CR_REG, CR_REG, IMMED }, lexemes);
        
        case arm_id::MCRR:
        case arm_id::MRRC: return verify_tokens({ COPROCESSOR, IMMED, REG, REG, CR_REG }, lexemes);
        
        case arm_id::PLD: return (ident::string_shifters::identify_shifter(id, lexemes) != shifter_id::UNKNOWN);

        case arm_id::FADDD: 
        case arm_id::FDIVD: 
        case arm_id::FMACD: 
        case arm_id::FMSCD: 
        case arm_id::FMULD: 
        case arm_id::FNMACD: 
        case arm_id::FNMSCD: 
        case arm_id::FNMULD: 
        case arm_id::FSUBD: return verify_tokens({ REG_DOUBLE, REG_DOUBLE, REG_DOUBLE }, lexemes);
        
        case arm_id::FTOSIS: 
        case arm_id::FTOUIS: 
        case arm_id::FUITOS: 
        case arm_id::FSITOS: 
        case arm_id::FSQRTS: 
        case arm_id::FNEGS: 
        case arm_id::FCPYS: 
        case arm_id::FCMPS: 
        case arm_id::FABSS: 
        case arm_id::FCMPES: return verify_tokens({ REG_SINGLE, REG_SINGLE }, lexemes);
        
        case arm_id::FABSD: 
        case arm_id::FCMPD: 
        case arm_id::FCMPED: 
        case arm_id::FCPYD: 
        case arm_id::FNEGD: 
        case arm_id::FSQRTD: return verify_tokens({ REG_DOUBLE, REG_DOUBLE }, lexemes);
        
        case arm_id::FADDS:
        case arm_id::FDIVS:
        case arm_id::FMACS:
        case arm_id::FMSCS:
        case arm_id::FMULS:
        case arm_id::FNMACS:
        case arm_id::FNMSCS:
        case arm_id::FNMULS:
        case arm_id::FSUBS: return verify_tokens({ REG_SINGLE, REG_SINGLE, REG_SINGLE }, lexemes);
        
        case arm_id::FTOSID:
        case arm_id::FCVTSD:
        case arm_id::FTOUID: return verify_tokens({ REG_SINGLE, REG_DOUBLE }, lexemes);
        
        case arm_id::FCVTDS:
        case arm_id::FUITOD:
        case arm_id::FSITOD: return verify_tokens({ REG_DOUBLE, REG_SINGLE }, lexemes);

        case arm_id::FCMPEZS:
        case arm_id::FCMPZS: return verify_tokens({ REG_SINGLE }, lexemes);

        case arm_id::FCMPEZD:
        case arm_id::FCMPZD: return verify_tokens({ REG_DOUBLE }, lexemes);

        case arm_id::FLDMS:
            return (
                (verify_tokens({ REG, PRE_INDEX, REG_LIST_SINGLE }, lexemes)) ||
                (verify_tokens({ REG, REG_LIST_SINGLE }, lexemes))
            );
        
        case arm_id::FLDMX:
            return (
                (verify_tokens({ REG, PRE_INDEX, REG_LIST_DOUBLE }, lexemes)) ||
                (verify_tokens({ REG, REG_LIST_DOUBLE }, lexemes))
            );
        
        case arm_id::FLDS: // TODO
        case arm_id::FMRS: return verify_tokens({ REG, REG_SINGLE }, lexemes);
        case arm_id::FMRX: return verify_tokens({ REG, VFP_REG_SPECIAL }, lexemes);
        case arm_id::FMSR: return verify_tokens({ REG_SINGLE, REG }, lexemes);
        case arm_id::FMSTAT: return true; // no arguments, so no room for errors
        case arm_id::FMXR: return verify_tokens({ VFP_REG_SPECIAL, REG }, lexemes);
        case arm_id::FSTMS:
            return (
                (verify_tokens({ REG, PRE_INDEX, REG_LIST_SINGLE }, lexemes)) ||
                (verify_tokens({ REG, REG_LIST_SINGLE }, lexemes))
            );
            
        case arm_id::FSTMX:
            return (
                (verify_tokens({ REG, PRE_INDEX, REG_LIST_DOUBLE }, lexemes)) ||
                (verify_tokens({ REG, REG_LIST_DOUBLE }, lexemes))
            );

        case arm_id::FSTS: 
            return (
                (verify_tokens({ REG_SINGLE, MEM_START, REG, MEM_END }, lexemes)) ||
                (verify_tokens({ REG_SINGLE, MEM_START, REG, HASHTAG, CONST_MUL_4, MEM_END }, lexemes))
            );

        case arm_id::FLDD: 
        //return (
            //    verify_tokens({ REG_DOUBLE, MEM_START, REG }, lexemes) ||
            //    verify_tokens({ REG_DOUBLE, MEM_START, REG, HASHTAG,  }, lexemes)
            //);
            // TODO

        case arm_id::FLDMD: 
            return (
                (verify_tokens({ REG, PRE_INDEX, REG_LIST_DOUBLE }, lexemes)) ||
                (verify_tokens({ REG, REG_LIST_DOUBLE }, lexemes))
            );
            
        case arm_id::FMDHR: return verify_tokens({ REG_DOUBLE, REG }, lexemes);
        case arm_id::FMDLR: return verify_tokens({ REG_DOUBLE, REG }, lexemes);
        case arm_id::FMRDL: return verify_tokens({ REG, REG_DOUBLE }, lexemes);
        case arm_id::FMRDH: return verify_tokens({ REG, REG_DOUBLE }, lexemes);
        case arm_id::FSTD: // TODO
        case arm_id::FSTMD: 
            return (
                (verify_tokens({ REG, PRE_INDEX, REG_LIST_DOUBLE }, lexemes)) ||
                (verify_tokens({ REG, REG_LIST_DOUBLE }, lexemes))
            );
       
    }
}