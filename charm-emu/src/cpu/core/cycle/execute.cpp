#include "shared/types.hpp"
#include "../../instruction_set.hpp"
#include "execute.hpp"
#include "decode.hpp"

void EXECUTE::loader() {
    for (const auto &inst : inst_set.arm_table) {
        arm_map[inst.first] = inst.second;
    }

    for (const auto &inst : inst_set.thumb_table) {
        thumb_map[inst.first] = inst.second;
    }

    //for (const auto &inst : inst_set.jazelle_table) {
    //    INSTRUCTION_SET::jazelle_struct data = inst.second;
    //    jazelle_map[inst.first] = data.function;
    //}
}

void EXECUTE::arm_execute(const arm_decode_struct &instruction) const {
    arm_map.at(instruction.id)(instruction.code);
    /**
     * ADC
     * ADD
     * AND
     * UNDEFINED
     * NOP
     * B
     * BL
     * BIC
     * CDP
     * CMN
     * CMP
     * EOR
     * LDC
     * LDM1
     * LDM2
     * LDM3
     * LDR
     * LDRB
     * LDRBT
     * LDRT
     * MCR
     * MLA
     * MOV
     * MRC
     * MRS
     * MSR_IMM
     * MSR_REG
     * MUL
     * MVN
     * ORR
     * RSB
     * RSC
     * SBC
     * STC
     * STM1
     * STM2
     * STR
     * STRB
     * STRBT
     * STRT
     * SUB
     * SWI
     * SWP
     * SWPB
     * TEQ
     * TST
     * PSR
     * STRH
     * LDRH
     * LDRSB
     * LDRSH
     * BKPT
     * BLX1
     * BLX2
     * CLZ
     * BX
     * SMLAL
     * SMULL
     * UMLAL
     * UMULL
     * LDRD
     * MCRR
     * MRRC
     * PLD
     * QADD
     * QDADD
     * QDSUB
     * QSUB
     * SMLA
     * SMLAW
     * SMUL
     * SMULW
     * STRD
     * FABSD
     * FABSS
     * FADDD
     * FADDS
     * FCMPD
     * FCMPED
     * FCMPES
     * FCMPEZD
     * FCMPEZS
     * FCMPS
     * FCMPZD
     * FCMPZS
     * FCPYD
     * FCPYS
     * FCVTDS
     * FCVTSD
     * FDIVD
     * FDIVS
     * FLDD
     * FLDMD
     * FLDMS
     * FLDMX
     * FLDS
     * FMACD
     * FMACS
     * FMDHR
     * FMDLR
     * FMRDH
     * FMRDL
     * FMRS
     * FMRX
     * FMSCD
     * FMSCS
     * FMSR
     * FMSTAT
     * FMULD
     * FMULS
     * FMXR
     * FNEGD
     * FNEGS
     * FNMACD
     * FNMACS
     * FNMSCD
     * FNMSCS
     * FNMULD
     * FNMULS
     * FSITOD
     * FSITOS
     * FSQRTD
     * FSQRTS
     * FSTD
     * FSTMD
     * FSTMS
     * FSTMX
     * FSTS
     * FSUBD
     * FSUBS
     * FTOSID
     * FTOSIS
     * FTOUID
     * FTOUIS
     * FUITOD
     * FUITOS
     * 
     * =========================================================================
     */


    //.function(code.second, reg);
}

void EXECUTE::thumb_execute(const thumb_decode_struct &instruction) const {
    thumb_map.at(instruction.id)(instruction.code);
}

//void EXECUTE::jazelle_execute(const jazelle_decoded_t &code) const {
//    jazelle_map.at(code.first)(code.second, reg);
//}

EXECUTE::EXECUTE(INSTRUCTION_SET& inst_set) : inst_set(inst_set) {
    loader();
}