#include "generators.hpp"

using namespace internal;

// format: <opcode>{<cond>}{S} <Rd>, <Rn>, <shifter_operand>
u32 generators::data_instruction(const id::arm instruction, const arguments &arg) {
    u32 binary = 0;

    shared::util::swap_bits(binary, 28, 31, arg.cond);

    if (arg.has_S) {
        shared::util::modify_bit(binary, 20, true);
    }

    bool Rd_present = true;
    bool Rn_present = true;
    u8 opcode = 0;

    // bits 26 and 27 are 0 for all instructions below, so they're ignored

    switch (instruction) {
        case id::arm::ADC: opcode = 0b0101; break;
        case id::arm::ADD: opcode = 0b0100; break;
        case id::arm::AND: opcode = 0b0000; break;
        case id::arm::BIC: opcode = 0b1110; break;
        case id::arm::EOR: opcode = 0b0001; break;
        case id::arm::ORR: opcode = 0b1100; break;
        case id::arm::RSB: opcode = 0b0011; break;
        case id::arm::SBC: opcode = 0b0110; break;
        case id::arm::RSC: opcode = 0b0111; break;
        case id::arm::SUB: opcode = 0b0010; break;

        case id::arm::TST: 
            opcode = 0b1000;
            Rd_present = false;
            break;

        case id::arm::TEQ: 
            opcode = 0b1001;
            Rd_present = false;
            break;

        case id::arm::CMP:
            opcode = 0b1010;
            Rd_present = false;
            break;

        case id::arm::CMN:
            opcode = 0b1011;
            Rd_present = false;
            break;

        case id::arm::MOV: 
            opcode = 0b1101;
            Rn_present = false;
            break;

        case id::arm::MVN: 
            opcode = 0b1111;
            Rn_present = false;
            break;

        default: shared::out::dev_error("Invalid configuration to data instruction pattern of instruction generation");
    }

    shared::util::swap_bits(binary, 21, 24, opcode);

    if (Rd_present) {
        shared::util::swap_bits(binary, 12, 15, arg.first_reg);
    }

    if (Rn_present) {
        shared::util::swap_bits(binary, 16, 19, arg.second_reg);
    }

    // TODO, continue this after finishing the shifter identification an fetcher

    return binary;
}


u32 generators::ls_instruction(const id::arm instruction, const arguments &arg) {

}







u32 generators::arm(const id::arm id, const arguments &args) {
    switch (id) {
        case id::arm::UNKNOWN: return 0;
        case id::arm::UNDEFINED:  return 0;
        case id::arm::NOP: return 0;
        case id::arm::ADC: return data_instruction(id, args);
        case id::arm::ADD: return data_instruction(id, args);
        case id::arm::AND: return data_instruction(id, args);
        case id::arm::BIC: return data_instruction(id, args);
        case id::arm::CMN: return data_instruction(id, args);
        case id::arm::CMP: return data_instruction(id, args);
        case id::arm::EOR: return data_instruction(id, args);
        case id::arm::MOV: return data_instruction(id, args);
        case id::arm::MVN: return data_instruction(id, args);
        case id::arm::ORR: return data_instruction(id, args);
        case id::arm::RSB: return data_instruction(id, args);
        case id::arm::RSC: return data_instruction(id, args);
        case id::arm::SBC: return data_instruction(id, args);
        case id::arm::SUB: return data_instruction(id, args);
        case id::arm::TEQ: return data_instruction(id, args);
        case id::arm::TST: return data_instruction(id, args);
        case id::arm::LDR: return ls_instruction(id, args);
        case id::arm::LDRB: return ls_instruction(id, args);
        case id::arm::LDRBT: return ls_instruction(id, args);
        case id::arm::LDRT: return ls_instruction(id, args);
        case id::arm::STR: return ls_instruction(id, args);
        case id::arm::STRB: return ls_instruction(id, args);
        case id::arm::STRBT: return ls_instruction(id, args);
        case id::arm::STRT: return ls_instruction(id, args);
        case id::arm::B: 
        case id::arm::BL:
        case id::arm::CDP: coproc
        case id::arm::LDC: coproc
        case id::arm::LDM1:
        case id::arm::LDM2:
        case id::arm::LDM3:
        case id::arm::MCR: coproc 
        case id::arm::MLA: S R R R R
        case id::arm::MRC: coproc
        case id::arm::MRS: R PSR
        case id::arm::MSR_IMM:  TODO
        case id::arm::MSR_REG:  TODO
        case id::arm::MUL: S R R R 
        case id::arm::STC:  
        case id::arm::STM1:  
        case id::arm::STM2:  
        case id::arm::SWI: 
        case id::arm::SWP: R R M R M
        case id::arm::SWPB: R R M R M
        case id::arm::PSR:  
        case id::arm::STRH: R 3
        case id::arm::LDRH: R 3
        case id::arm::LDRSB: R 3
        case id::arm::LDRSH: R 3
        case id::arm::BKPT:  
        case id::arm::BLX1:  
        case id::arm::BLX2: R
        case id::arm::CLZ: R R
        case id::arm::BX: R
        case id::arm::SMLAL:  
        case id::arm::SMULL:  
        case id::arm::UMLAL:  
        case id::arm::UMULL:  
        case id::arm::LDRD: R 3
        case id::arm::MCRR: 
        case id::arm::MRRC:  
        case id::arm::PLD: 2
        case id::arm::QADD: R R R
        case id::arm::QDADD: R R R
        case id::arm::QDSUB: R R R
        case id::arm::QSUB: R R R
        case id::arm::SMLAXY: XY R R R R
        case id::arm::SMLALXY:
        case id::arm::SMLAWY: Y R R R R
        case id::arm::SMULXY: XY R R R
        case id::arm::SMULWY: Y R R R
        case id::arm::STRD: R 3
        case id::arm::FABSD: D D
        case id::arm::FABSS: S S
        case id::arm::FADDD: D D D
        case id::arm::FADDS: S S S
        case id::arm::FCMPD: D D
        case id::arm::FCMPED: D D
        case id::arm::FCMPES: S S
        case id::arm::FCMPEZD: D
        case id::arm::FCMPEZS: S
        case id::arm::FCMPS: S S
        case id::arm::FCMPZD: D
        case id::arm::FCMPZS: S
        case id::arm::FCPYD: D D
        case id::arm::FCPYS: S S
        case id::arm::FCVTDS: D S
        case id::arm::FCVTSD: S D
        case id::arm::FDIVD: D D D
        case id::arm::FDIVS: S S S 
        case id::arm::FLDD:  
        case id::arm::FLDMD:  
        case id::arm::FLDMS:  
        case id::arm::FLDMX:  
        case id::arm::FLDS:  
        case id::arm::FMACD:  
        case id::arm::FMACS:  
        case id::arm::FMDHR:  
        case id::arm::FMDLR:  
        case id::arm::FMRDH:  
        case id::arm::FMRDL:  
        case id::arm::FMRS:  
        case id::arm::FMRX:  
        case id::arm::FMSCD:  
        case id::arm::FMSCS:  
        case id::arm::FMSR:  
        case id::arm::FMSTAT:  
        case id::arm::FMULD:  
        case id::arm::FMULS:  
        case id::arm::FMXR:  
        case id::arm::FNEGD:  
        case id::arm::FNEGS:  
        case id::arm::FNMACD:  
        case id::arm::FNMACS:  
        case id::arm::FNMSCD:  
        case id::arm::FNMSCS:  
        case id::arm::FNMULD:  
        case id::arm::FNMULS:  
        case id::arm::FSITOD:  
        case id::arm::FSITOS:  
        case id::arm::FSQRTD:  
        case id::arm::FSQRTS:  
        case id::arm::FSTD:  
        case id::arm::FSTMD:  
        case id::arm::FSTMS:  
        case id::arm::FSTMX:  
        case id::arm::FSTS:  
        case id::arm::FSUBD:  
        case id::arm::FSUBS:  
        case id::arm::FTOSID:  
        case id::arm::FTOSIS:  
        case id::arm::FTOUID:  
        case id::arm::FTOUIS:  
        case id::arm::FUITOD:  
        case id::arm::FUITOS: 
        case id::arm::CDP2: 
        case id::arm::LDC2: 
        case id::arm::MCR2: 
        case id::arm::MRC2: 
        case id::arm::STC2: 
    }
}