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

bool validation::string_arm::is_arm_instruction_valid(const std::string &code) {
    return is_arm_instruction_valid(IR::generate(code));
}


bool validation::string_arm::is_arm_instruction_valid(const IR_arm_struct &IR) {
    using namespace interpreter;

    switch (IR.id) {
        case id::arm::UNKNOWN: return false;
        case id::arm::UNDEFINED: return false;
        case id::arm::NOP: return false;

        // TODO COMPLETE ALL THE SHIFTERS

        // addressing mode 1: data processing
        case id::arm::ADC: 
        case id::arm::ADD:
        case id::arm::RSB:
        case id::arm::BIC:
        case id::arm::SUB:
        case id::arm::CMN: // TODO, FUCK THIS INSTRUCTION
        case id::arm::AND:
        case id::arm::CMP:
        case id::arm::RSC:
        case id::arm::SBC:
        case id::arm::EOR:
        case id::arm::ORR:
        case id::arm::TEQ:
        case id::arm::TST:
        case id::arm::MOV:
        case id::arm::MVN:
        case id::arm::CMNP:
        case id::arm::CMPP:
        case id::arm::TEQP:
        case id::arm::TSTP:

        // addressing mode 2: load store
        case id::arm::LDR:
        case id::arm::LDRB:
        case id::arm::LDRBT:
        case id::arm::LDRT:
        case id::arm::STR: 
        case id::arm::STRB: 
        case id::arm::STRBT:
        case id::arm::STRT:
        
        // addressing mode 3: load store misc
        case id::arm::STRH:
        case id::arm::LDRH:
        case id::arm::LDRSB:
        case id::arm::LDRSH:
        case id::arm::STRD:
        case id::arm::LDRD:

        // addressing mode 4: load store multiple
        case id::arm::LDM1:
        case id::arm::LDM2:
        case id::arm::LDM3:
        case id::arm::STM1: 
        case id::arm::STM2: 

        // addressing mode 5: load store coprocessor
        case id::arm::STC:  
        case id::arm::STC2: 
        case id::arm::LDC:  
        case id::arm::LDC2: return (ident::string_shifters::identify_shifter(IR) != shifter_enum::UNKNOWN);

        case id::arm::B:
        case id::arm::BL: //return verify_tokens({ CONST }, lexemes);
        case id::arm::SWI: return verify_tokens({ IMMED_24 }, lexemes);
            return verify_tokens({  }, lexemes);

        case id::arm::MCR2: 
        case id::arm::MCR: 
        case id::arm::MRC2:
        case id::arm::MRC:
            return (
                (verify_tokens({ COPROCESSOR, IMMED, REG, CR_REG, CR_REG, IMMED }, lexemes)) || 
                (verify_tokens({ COPROCESSOR, IMMED, REG, CR_REG, CR_REG }, lexemes))
            );

        case id::arm::SWP:
        case id::arm::SWPB:
            return (
                (verify_tokens({ REG, REG, REG }, lexemes)) || 
                (verify_tokens({ REG, REG }, lexemes))
            );

        case id::arm::QADD:
        case id::arm::QDADD:
        case id::arm::QDSUB:
        case id::arm::QSUB:
        case id::arm::SMULXY:
        case id::arm::SMULWY:
        case id::arm::MUL: return verify_tokens({ REG, REG, REG }, lexemes);

        case id::arm::MLA:
        case id::arm::SMLAL:
        case id::arm::SMULL:
        case id::arm::UMLAL:
        case id::arm::SMLAXY:
        case id::arm::SMLALXY:
        case id::arm::SMLAWY:
        case id::arm::UMULL: return verify_tokens({ REG, REG, REG, REG }, lexemes);
        
        case id::arm::MRS: 
            return (
                (verify_tokens({ REG, CPSR_FIELD }, lexemes)) ||
                (verify_tokens({ REG, SPSR_FIELD }, lexemes))
            );
            
        case id::arm::MSR_IMM: // both these instructions are already verified in the identification process
        case id::arm::MSR_REG: return true; 
        case id::arm::BKPT: return verify_tokens({ IMMED_16 }, lexemes);
        case id::arm::BLX1:
        case id::arm::BX: return verify_tokens({ REG }, lexemes);
        case id::arm::BLX2: return verify_tokens({ REG }, lexemes);
        case id::arm::CLZ: return verify_tokens({ REG, REG }, lexemes);
        case id::arm::CDP: return verify_tokens({ COPROCESSOR, IMMED, CR_REG, CR_REG, CR_REG, IMMED }, lexemes);
        case id::arm::CDP2: return verify_tokens({ COPROCESSOR, IMMED, CR_REG, CR_REG, CR_REG, IMMED }, lexemes);
        
        case id::arm::MCRR:
        case id::arm::MRRC: return verify_tokens({ COPROCESSOR, IMMED, REG, REG, CR_REG }, lexemes);
        
        case id::arm::PLD: return (ident::string_shifters::identify_shifter(id, lexemes) != shifter_enum::UNKNOWN);

        case id::arm::FADDD: 
        case id::arm::FDIVD: 
        case id::arm::FMACD: 
        case id::arm::FMSCD: 
        case id::arm::FMULD: 
        case id::arm::FNMACD: 
        case id::arm::FNMSCD: 
        case id::arm::FNMULD: 
        case id::arm::FSUBD: return verify_tokens({ REG_DOUBLE, REG_DOUBLE, REG_DOUBLE }, lexemes);
        
        case id::arm::FTOSIS: 
        case id::arm::FTOUIS: 
        case id::arm::FUITOS: 
        case id::arm::FSITOS: 
        case id::arm::FSQRTS: 
        case id::arm::FNEGS: 
        case id::arm::FCPYS: 
        case id::arm::FCMPS: 
        case id::arm::FABSS: 
        case id::arm::FCMPES: return verify_tokens({ REG_SINGLE, REG_SINGLE }, lexemes);
        
        case id::arm::FABSD: 
        case id::arm::FCMPD: 
        case id::arm::FCMPED: 
        case id::arm::FCPYD: 
        case id::arm::FNEGD: 
        case id::arm::FSQRTD: return verify_tokens({ REG_DOUBLE, REG_DOUBLE }, lexemes);
        
        case id::arm::FADDS:
        case id::arm::FDIVS:
        case id::arm::FMACS:
        case id::arm::FMSCS:
        case id::arm::FMULS:
        case id::arm::FNMACS:
        case id::arm::FNMSCS:
        case id::arm::FNMULS:
        case id::arm::FSUBS: return verify_tokens({ REG_SINGLE, REG_SINGLE, REG_SINGLE }, lexemes);
        
        case id::arm::FTOSID:
        case id::arm::FCVTSD:
        case id::arm::FTOUID: return verify_tokens({ REG_SINGLE, REG_DOUBLE }, lexemes);
        
        case id::arm::FCVTDS:
        case id::arm::FUITOD:
        case id::arm::FSITOD: return verify_tokens({ REG_DOUBLE, REG_SINGLE }, lexemes);

        case id::arm::FCMPEZS:
        case id::arm::FCMPZS: return verify_tokens({ REG_SINGLE }, lexemes);

        case id::arm::FCMPEZD:
        case id::arm::FCMPZD: return verify_tokens({ REG_DOUBLE }, lexemes);

        case id::arm::FLDMS:
            return (
                (verify_tokens({ REG, PRE_INDEX, REG_LIST_SINGLE }, lexemes)) ||
                (verify_tokens({ REG, REG_LIST_SINGLE }, lexemes))
            );
        
        case id::arm::FLDMX:
            return (
                (verify_tokens({ REG, PRE_INDEX, REG_LIST_DOUBLE }, lexemes)) ||
                (verify_tokens({ REG, REG_LIST_DOUBLE }, lexemes))
            );
        
        case id::arm::FLDS: // TODO
        case id::arm::FMRS: return verify_tokens({ REG, REG_SINGLE }, lexemes);
        case id::arm::FMRX: return verify_tokens({ REG, VFP_REG_SPECIAL }, lexemes);
        case id::arm::FMSR: return verify_tokens({ REG_SINGLE, REG }, lexemes);
        case id::arm::FMSTAT: return true; // no arguments, so no room for errors
        case id::arm::FMXR: return verify_tokens({ VFP_REG_SPECIAL, REG }, lexemes);
        case id::arm::FSTMS:
            return (
                (verify_tokens({ REG, PRE_INDEX, REG_LIST_SINGLE }, lexemes)) ||
                (verify_tokens({ REG, REG_LIST_SINGLE }, lexemes))
            );
            
        case id::arm::FSTMX:
            return (
                (verify_tokens({ REG, PRE_INDEX, REG_LIST_DOUBLE }, lexemes)) ||
                (verify_tokens({ REG, REG_LIST_DOUBLE }, lexemes))
            );

        case id::arm::FSTS: 
            return (
                (verify_tokens({ REG_SINGLE, MEM_START, REG, MEM_END }, lexemes)) ||
                (verify_tokens({ REG_SINGLE, MEM_START, REG, HASHTAG, CONST_MUL_4, MEM_END }, lexemes))
            );

        case id::arm::FLDD: 
        //return (
            //    verify_tokens({ REG_DOUBLE, MEM_START, REG }, lexemes) ||
            //    verify_tokens({ REG_DOUBLE, MEM_START, REG, HASHTAG,  }, lexemes)
            //);
            // TODO

        case id::arm::FLDMD: 
            return (
                (verify_tokens({ REG, PRE_INDEX, REG_LIST_DOUBLE }, lexemes)) ||
                (verify_tokens({ REG, REG_LIST_DOUBLE }, lexemes))
            );
            
        case id::arm::FMDHR: return verify_tokens({ REG_DOUBLE, REG }, lexemes);
        case id::arm::FMDLR: return verify_tokens({ REG_DOUBLE, REG }, lexemes);
        case id::arm::FMRDL: return verify_tokens({ REG, REG_DOUBLE }, lexemes);
        case id::arm::FMRDH: return verify_tokens({ REG, REG_DOUBLE }, lexemes);
        case id::arm::FSTD: // TODO
        case id::arm::FSTMD: 
            return (
                (verify_tokens({ REG, PRE_INDEX, REG_LIST_DOUBLE }, lexemes)) ||
                (verify_tokens({ REG, REG_LIST_DOUBLE }, lexemes))
            );
       
    }
}