#include "string_arm.hpp"
#include "../identifiers/string_arm.hpp"
#include "../identifiers/string_shifters.hpp"

#include "../interpreter/interpreter.hpp"
#include "llarm-asm/src/interpreter/tokens.hpp"

using namespace internal;

// binary arm instructions don't really have much of a way to "fail",
// even "faulty" arguments are encoded in ways where it can't be considered
// as an error. So the only real failure for a thumb instruction would
// be to identify an undefined or unknown instruction (me thinks)

bool validation::string_arm::is_arm_instruction_valid(const std::string &code) {
    const id::arm id = ident::string_arm::arm(code);
    const interpreter::lexemes_t lexemes = interpreter::analyze(code);

    return is_arm_instruction_valid(id, lexemes);
}


bool validation::string_arm::is_arm_instruction_valid(const id::arm id, const interpreter::lexemes_t &lexemes) {
    using namespace interpreter;
    
    // how this works is that some instructions using shifters are already validified 
    // just by checking whether the shifter is valid. The shifter identification already 
    // checks all the token placements already, so there's no need to do this again.
    // So basically, if the shifter is identified as a valid shifter, the instruction
    // is also valid by extension. That's the gist of why this design choice was made.  

    switch (id) {
        case id::arm::UNKNOWN: return false;
        case id::arm::UNDEFINED: return false;
        case id::arm::NOP: return false;

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
        case id::arm::LDC2: return (ident::string_shifters::identify_shifter(id, lexemes) != shifter_enum::UNKNOWN);

        case id::arm::B:
        case id::arm::BL: //return has_matching_pattern({ CONST }, lexemes);
        case id::arm::SWI: return has_matching_pattern({ IMMED_24 }, lexemes);

        case id::arm::MCR2: 
        case id::arm::MCR: 
        case id::arm::MRC2:
        case id::arm::MRC:
            return (
                (has_matching_pattern({ COPROCESSOR, IMMED, REG, CR_REG, CR_REG, IMMED }, lexemes)) || 
                (has_matching_pattern({ COPROCESSOR, IMMED, REG, CR_REG, CR_REG }, lexemes))
            );

        case id::arm::SWP:
        case id::arm::SWPB:
            return (
                (has_matching_pattern({ REG, REG, REG }, lexemes)) || 
                (has_matching_pattern({ REG, REG }, lexemes))
            );
            
        case id::arm::QADD:
        case id::arm::QDADD:
        case id::arm::QDSUB:
        case id::arm::QSUB:
        case id::arm::SMULXY:
        case id::arm::SMULWY:
        case id::arm::MUL: return has_matching_pattern({ REG, REG, REG }, lexemes);

        case id::arm::MLA:
        case id::arm::SMLAL:
        case id::arm::SMULL:
        case id::arm::UMLAL:
        case id::arm::SMLAXY:
        case id::arm::SMLALXY:
        case id::arm::SMLAWY:
        case id::arm::UMULL: return has_matching_pattern({ REG, REG, REG, REG }, lexemes);
        
        case id::arm::MRS: 
            return (
                (has_matching_pattern({ REG, CPSR_FIELD }, lexemes)) ||
                (has_matching_pattern({ REG, SPSR_FIELD }, lexemes))
            );
            
        case id::arm::MSR_IMM: // both these instructions are already verified in the identification process
        case id::arm::MSR_REG: return true; 
        case id::arm::BKPT: return has_matching_pattern({ IMMED_16 }, lexemes);
        case id::arm::BLX1:
        case id::arm::BX: return has_matching_pattern({ REG }, lexemes);
        case id::arm::BLX2: return has_matching_pattern({ REG }, lexemes);
        case id::arm::CLZ: return has_matching_pattern({ REG, REG }, lexemes);
        case id::arm::CDP: return has_matching_pattern({ COPROCESSOR, IMMED, CR_REG, CR_REG, CR_REG, IMMED }, lexemes);
        case id::arm::CDP2: return has_matching_pattern({ COPROCESSOR, IMMED, CR_REG, CR_REG, CR_REG, IMMED }, lexemes);
        
        case id::arm::MCRR:
        case id::arm::MRRC: return has_matching_pattern({ COPROCESSOR, IMMED, REG, REG, CR_REG }, lexemes);
        
        case id::arm::PLD: return (ident::string_shifters::identify_shifter(id, lexemes) != shifter_enum::UNKNOWN);

        case id::arm::FADDD: 
        case id::arm::FDIVD: 
        case id::arm::FMACD: 
        case id::arm::FMSCD: 
        case id::arm::FMULD: 
        case id::arm::FNMACD: 
        case id::arm::FNMSCD: 
        case id::arm::FNMULD: 
        case id::arm::FSUBD: return has_matching_pattern({ REG_DOUBLE, REG_DOUBLE, REG_DOUBLE }, lexemes);
        
        case id::arm::FTOSIS: 
        case id::arm::FTOUIS: 
        case id::arm::FUITOS: 
        case id::arm::FSITOS: 
        case id::arm::FSQRTS: 
        case id::arm::FNEGS: 
        case id::arm::FCPYS: 
        case id::arm::FCMPS: 
        case id::arm::FABSS: 
        case id::arm::FCMPES: return has_matching_pattern({ REG_SINGLE, REG_SINGLE }, lexemes);
        
        case id::arm::FABSD: 
        case id::arm::FCMPD: 
        case id::arm::FCMPED: 
        case id::arm::FCPYD: 
        case id::arm::FNEGD: 
        case id::arm::FSQRTD: return has_matching_pattern({ REG_DOUBLE, REG_DOUBLE }, lexemes);
        
        case id::arm::FADDS:
        case id::arm::FDIVS:
        case id::arm::FMACS:
        case id::arm::FMSCS:
        case id::arm::FMULS:
        case id::arm::FNMACS:
        case id::arm::FNMSCS:
        case id::arm::FNMULS:
        case id::arm::FSUBS: return has_matching_pattern({ REG_SINGLE, REG_SINGLE, REG_SINGLE }, lexemes);
        
        case id::arm::FTOSID:
        case id::arm::FCVTSD:
        case id::arm::FTOUID: return has_matching_pattern({ REG_SINGLE, REG_DOUBLE }, lexemes);
        
        case id::arm::FCVTDS:
        case id::arm::FUITOD:
        case id::arm::FSITOD: return has_matching_pattern({ REG_DOUBLE, REG_SINGLE }, lexemes);

        case id::arm::FCMPEZS:
        case id::arm::FCMPZS: return has_matching_pattern({ REG_SINGLE }, lexemes);

        case id::arm::FCMPEZD:
        case id::arm::FCMPZD: return has_matching_pattern({ REG_DOUBLE }, lexemes);

        case id::arm::FLDMS:
            return (
                (has_matching_pattern({ REG, PRE_INDEX, REG_LIST_SINGLE }, lexemes)) ||
                (has_matching_pattern({ REG, REG_LIST_SINGLE }, lexemes))
            );
        
        case id::arm::FLDMX:
            return (
                (has_matching_pattern({ REG, PRE_INDEX, REG_LIST_DOUBLE }, lexemes)) ||
                (has_matching_pattern({ REG, REG_LIST_DOUBLE }, lexemes))
            );
        
        case id::arm::FLDS: // TODO
        case id::arm::FMRS: return has_matching_pattern({ REG, REG_SINGLE }, lexemes);
        case id::arm::FMRX: return has_matching_pattern({ REG, VFP_REG_SPECIAL }, lexemes);
        case id::arm::FMSR: return has_matching_pattern({ REG_SINGLE, REG }, lexemes);
        case id::arm::FMSTAT: return true; // no arguments, so no room for errors
        case id::arm::FMXR: return has_matching_pattern({ VFP_REG_SPECIAL, REG }, lexemes);
        case id::arm::FSTMS:
            return (
                (has_matching_pattern({ REG, PRE_INDEX, REG_LIST_SINGLE }, lexemes)) ||
                (has_matching_pattern({ REG, REG_LIST_SINGLE }, lexemes))
            );
            
        case id::arm::FSTMX:
            return (
                (has_matching_pattern({ REG, PRE_INDEX, REG_LIST_DOUBLE }, lexemes)) ||
                (has_matching_pattern({ REG, REG_LIST_DOUBLE }, lexemes))
            );

        case id::arm::FSTS: 
            return (
                (has_matching_pattern({ REG_SINGLE, MEM_START, REG, MEM_END }, lexemes)) ||
                (has_matching_pattern({ REG_SINGLE, MEM_START, REG, HASHTAG, CONST_MUL_4, MEM_END }, lexemes))
            );

        case id::arm::FLDD: 
        //return (
            //    has_matching_pattern({ REG_DOUBLE, MEM_START, REG }, lexemes) ||
            //    has_matching_pattern({ REG_DOUBLE, MEM_START, REG, HASHTAG,  }, lexemes)
            //);
            // TODO

        case id::arm::FLDMD: 
            return (
                (has_matching_pattern({ REG, PRE_INDEX, REG_LIST_DOUBLE }, lexemes)) ||
                (has_matching_pattern({ REG, REG_LIST_DOUBLE }, lexemes))
            );
            
        case id::arm::FMDHR: return has_matching_pattern({ REG_DOUBLE, REG }, lexemes);
        case id::arm::FMDLR: return has_matching_pattern({ REG_DOUBLE, REG }, lexemes);
        case id::arm::FMRDL: return has_matching_pattern({ REG, REG_DOUBLE }, lexemes);
        case id::arm::FMRDH: return has_matching_pattern({ REG, REG_DOUBLE }, lexemes);
        case id::arm::FSTD: // TODO
        case id::arm::FSTMD: 
            return (
                (has_matching_pattern({ REG, PRE_INDEX, REG_LIST_DOUBLE }, lexemes)) ||
                (has_matching_pattern({ REG, REG_LIST_DOUBLE }, lexemes))
            );
       
    }
}