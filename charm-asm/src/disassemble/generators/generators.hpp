#pragma once

#include "shared/types.hpp"

#include <string>

// the generation mechanism was benchmarked here:
// https://quick-bench.com/q/No_nYrHbcGwK5JTFl-qJtJ0ncc0

namespace internal::generators {
    namespace arm {
        namespace math {
            std::string ADC(u32);
            std::string ADD(u32);
            std::string RSB(u32);
            std::string RSC(u32);
            std::string SBC(u32);
            std::string SUB(u32);
        }

        namespace logic {
            std::string CMN(u32);
            std::string AND(u32);
            std::string BIC(u32);
            std::string CMP(u32);
            std::string CLZ(u32);
            std::string EOR(u32);
            std::string ORR(u32);
            std::string TEQ(u32);
            std::string TST(u32);
        }

        namespace movement {
            std::string MOV(u32);
            std::string MVN(u32);
            std::string MRS(u32);
            std::string MSR_IMM(u32);
            std::string MSR_REG(u32);
        }

        namespace multiply {
            std::string MLA(u32);
            std::string MUL(u32);
            std::string SMLAL(u32);
            std::string SMULL(u32);
            std::string UMLAL(u32);
            std::string UMULL(u32);
        }

        namespace branching {
            std::string B(u32, u32 PC);
            std::string BL(u32, u32 PC);
            std::string BX(u32);
            std::string BLX1(u32, u32 PC);
            std::string BLX2(u32);
        }

        namespace coprocessor {
            std::string CDP(u32);
            std::string LDC(u32);
            std::string MCR(u32);
            std::string MRC(u32);
            std::string STC(u32);
        }

        namespace misc {
            std::string NOP(u32);
            std::string PSR(u32);
            std::string SWI(u32);
            std::string BKPT(u32);
        }

        namespace load {
            std::string LDM1(u32);
            std::string LDM2(u32);
            std::string LDM3(u32);
            std::string LDR(u32);
            std::string LDRB(u32);
            std::string LDRBT(u32);
            std::string LDRH(u32);
            std::string LDRSB(u32);
            std::string LDRSH(u32);
            std::string LDRT(u32);
        }

        namespace store {
            std::string STM1(u32);
            std::string STM2(u32);
            std::string STR(u32);
            std::string STRB(u32);
            std::string STRBT(u32);
            std::string STRH(u32);
            std::string STRT(u32);
            std::string SWP(u32);
            std::string SWPB(u32);
        }

        namespace dsp {
            std::string LDRD(u32);
            std::string MCRR(u32);
            std::string MRRC(u32);
            std::string PLD(u32);
            std::string QADD(u32);
            std::string QDADD(u32);
            std::string QDSUB(u32);
            std::string QSUB(u32);
            std::string SMLA(u32);
            std::string SMLAL(u32);
            std::string SMLAW(u32);
            std::string SMUL(u32);
            std::string SMULW(u32);
            std::string STRD(u32);
        }

        namespace vfp {
            std::string FABSD(u32);
            std::string FABSS(u32);
            std::string FADDD(u32);
            std::string FADDS(u32);
            std::string FCMPD(u32);
            std::string FCMPED(u32);
            std::string FCMPES(u32);
            std::string FCMPEZD(u32);
            std::string FCMPEZS(u32);
            std::string FCMPS(u32);
            std::string FCMPZD(u32);
            std::string FCMPZS(u32);
            std::string FCPYD(u32);
            std::string FCPYS(u32);
            std::string FCVTDS(u32);
            std::string FCVTSD(u32);
            std::string FDIVD(u32);
            std::string FDIVS(u32);
            std::string FLDD(u32);
            std::string FLDMD(u32);
            std::string FLDMS(u32);
            std::string FLDMX(u32);
            std::string FLDS(u32);
            std::string FMACD(u32);
            std::string FMACS(u32);
            std::string FMDHR(u32);
            std::string FMDLR(u32);
            std::string FMRDH(u32);
            std::string FMRDL(u32);
            std::string FMRS(u32);
            std::string FMRX(u32);
            std::string FMSCD(u32);
            std::string FMSCS(u32);
            std::string FMSR(u32);
            std::string FMSTAT(u32);
            std::string FMULD(u32);
            std::string FMULS(u32);
            std::string FMXR(u32);
            std::string FNEGD(u32);
            std::string FNEGS(u32);
            std::string FNMACD(u32);
            std::string FNMACS(u32);
            std::string FNMSCD(u32);
            std::string FNMSCS(u32);
            std::string FNMULD(u32);
            std::string FNMULS(u32);
            std::string FSITOD(u32);
            std::string FSITOS(u32);
            std::string FSQRTD(u32);
            std::string FSQRTS(u32);
            std::string FSTD(u32);
            std::string FSTMD(u32);
            std::string FSTMS(u32);
            std::string FSTMX(u32);
            std::string FSTS(u32);
            std::string FSUBD(u32);
            std::string FSUBS(u32);
            std::string FTOSID(u32);
            std::string FTOSIS(u32);
            std::string FTOUID(u32);
            std::string FTOUIS(u32);
            std::string FUITOD(u32);
            std::string FUITOS(u32);
        }
    }


    namespace thumb {
        namespace math {
            std::string ADC(u16); 
            std::string ADD1(u16);
            std::string ADD2(u16);
            std::string ADD3(u16);
            std::string ADD4(u16);
            std::string ADD5(u16);
            std::string ADD6(u16);
            std::string ADD7(u16);
            std::string SBC(u16);
            std::string SUB1(u16);
            std::string SUB2(u16);
            std::string SUB3(u16);
            std::string SUB4(u16);
            std::string MUL(u16);
        }

        namespace logic {
            std::string AND(u16);
            std::string ASR1(u16);
            std::string ASR2(u16);
            std::string BIC(u16);
            std::string EOR(u16);
            std::string LSL1(u16);
            std::string LSL2(u16);
            std::string LSR1(u16);
            std::string LSR2(u16);
            std::string NEG(u16);
            std::string ORR(u16);
            std::string ROR(u16);
            std::string TST(u16);
        }

        namespace comparison {
            std::string CMN(u16);
            std::string CMP1(u16);
            std::string CMP2(u16);
            std::string CMP3(u16);
        }

        namespace movement {
            std::string MOV1(u16);
            std::string MOV2(u16);
            std::string MOV3(u16);
            std::string MVN(u16);
        }

        namespace branching {
            std::string B1(u16, u32 PC);
            std::string B2(u16, u32 PC);
            std::string BX(u16);
            std::string BL_BLX1(u16, u32 PC);
            std::string BLX2(u16);
        }

        namespace misc {
            std::string SWI(u16);
            std::string BKPT(u16);
        }

        namespace load {
            std::string LDMIA(u16);
            std::string LDR1(u16);
            std::string LDR2(u16);
            std::string LDR3(u16);
            std::string LDR4(u16);
            std::string LDRB1(u16);
            std::string LDRB2(u16);
            std::string LDRH1(u16);
            std::string LDRH2(u16);
            std::string LDRSB(u16);
            std::string LDRSH(u16);
            std::string POP(u16);
        }

        namespace store {
            std::string STMIA(u16);
            std::string STR1(u16);
            std::string STR2(u16);
            std::string STR3(u16);
            std::string STRB1(u16);
            std::string STRB2(u16);
            std::string STRH1(u16);
            std::string STRH2(u16);
            std::string PUSH(u16);
        }
    }
}