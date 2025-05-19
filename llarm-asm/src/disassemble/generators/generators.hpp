#pragma once

#include "../../settings.hpp"

#include "shared/types.hpp"

#include <string>

// the generation mechanism was benchmarked here:
// https://quick-bench.com/q/No_nYrHbcGwK5JTFl-qJtJ0ncc0

namespace internal::generators {
    namespace arm {
        namespace math {
            std::string ADC(u32, settings);
            std::string ADD(u32, settings);
            std::string RSB(u32, settings);
            std::string RSC(u32, settings);
            std::string SBC(u32, settings);
            std::string SUB(u32, settings);
        }

        namespace logic {
            std::string CMN(u32, settings);
            std::string AND(u32, settings);
            std::string BIC(u32, settings);
            std::string CMP(u32, settings);
            std::string CLZ(u32, settings);
            std::string EOR(u32, settings);
            std::string ORR(u32, settings);
            std::string TEQ(u32, settings);
            std::string TST(u32, settings);
        }

        namespace movement {
            std::string MOV(u32, settings);
            std::string MVN(u32, settings);
            std::string MRS(u32, settings);
            std::string MSR_IMM(u32, settings);
            std::string MSR_REG(u32, settings);
        }

        namespace multiply {
            std::string MLA(u32, settings);
            std::string MUL(u32, settings);
            std::string SMLAL(u32, settings);
            std::string SMULL(u32, settings);
            std::string UMLAL(u32, settings);
            std::string UMULL(u32, settings);
        }

        namespace branching {
            std::string B(u32, u32 PC, settings);
            std::string BL(u32, u32 PC, settings);
            std::string BX(u32, settings);
            std::string BLX1(u32, u32 PC, settings);
            std::string BLX2(u32, settings);
        }

        namespace coprocessor {
            std::string CDP(u32, settings);
            std::string LDC(u32, settings);
            std::string MCR(u32, settings);
            std::string MRC(u32, settings);
            std::string STC(u32, settings);
        }

        namespace misc {
            std::string NOP();
            std::string PSR(u32, settings);
            std::string SWI(u32, settings);
            std::string BKPT(u32, settings);
        }

        namespace load {
            std::string LDM1(u32, settings);
            std::string LDM2(u32, settings);
            std::string LDM3(u32, settings);
            std::string LDR(u32, settings);
            std::string LDRB(u32, settings);
            std::string LDRBT(u32, settings);
            std::string LDRH(u32, settings);
            std::string LDRSB(u32, settings);
            std::string LDRSH(u32, settings);
            std::string LDRT(u32, settings);
        }

        namespace store {
            std::string STM1(u32, settings);
            std::string STM2(u32, settings);
            std::string STR(u32, settings);
            std::string STRB(u32, settings);
            std::string STRBT(u32, settings);
            std::string STRH(u32, settings);
            std::string STRT(u32, settings);
            std::string SWP(u32, settings);
            std::string SWPB(u32, settings);
        }

        namespace dsp {
            std::string LDRD(u32, settings);
            std::string MCRR(u32, settings);
            std::string MRRC(u32, settings);
            std::string PLD(u32, settings);
            std::string QADD(u32, settings);
            std::string QDADD(u32, settings);
            std::string QDSUB(u32, settings);
            std::string QSUB(u32, settings);
            std::string SMLA(u32, settings);
            std::string SMLAL(u32, settings);
            std::string SMLAW(u32, settings);
            std::string SMUL(u32, settings);
            std::string SMULW(u32, settings);
            std::string STRD(u32, settings);
        }

        namespace vfp {
            std::string FABSD(u32, settings);
            std::string FABSS(u32, settings);
            std::string FADDD(u32, settings);
            std::string FADDS(u32, settings);
            std::string FCMPD(u32, settings);
            std::string FCMPED(u32, settings);
            std::string FCMPES(u32, settings);
            std::string FCMPEZD(u32, settings);
            std::string FCMPEZS(u32, settings);
            std::string FCMPS(u32, settings);
            std::string FCMPZD(u32, settings);
            std::string FCMPZS(u32, settings);
            std::string FCPYD(u32, settings);
            std::string FCPYS(u32, settings);
            std::string FCVTDS(u32, settings);
            std::string FCVTSD(u32, settings);
            std::string FDIVD(u32, settings);
            std::string FDIVS(u32, settings);
            std::string FLDD(u32, settings);
            std::string FLDMD(u32, settings);
            std::string FLDMS(u32, settings);
            std::string FLDMX(u32, settings);
            std::string FLDS(u32, settings);
            std::string FMACD(u32, settings);
            std::string FMACS(u32, settings);
            std::string FMDHR(u32, settings);
            std::string FMDLR(u32, settings);
            std::string FMRDH(u32, settings);
            std::string FMRDL(u32, settings);
            std::string FMRS(u32, settings);
            std::string FMRX(u32, settings);
            std::string FMSCD(u32, settings);
            std::string FMSCS(u32, settings);
            std::string FMSR(u32, settings);
            std::string FMSTAT(u32, settings);
            std::string FMULD(u32, settings);
            std::string FMULS(u32, settings);
            std::string FMXR(u32, settings);
            std::string FNEGD(u32, settings);
            std::string FNEGS(u32, settings);
            std::string FNMACD(u32, settings);
            std::string FNMACS(u32, settings);
            std::string FNMSCD(u32, settings);
            std::string FNMSCS(u32, settings);
            std::string FNMULD(u32, settings);
            std::string FNMULS(u32, settings);
            std::string FSITOD(u32, settings);
            std::string FSITOS(u32, settings);
            std::string FSQRTD(u32, settings);
            std::string FSQRTS(u32, settings);
            std::string FSTD(u32, settings);
            std::string FSTMD(u32, settings);
            std::string FSTMS(u32, settings);
            std::string FSTMX(u32, settings);
            std::string FSTS(u32, settings);
            std::string FSUBD(u32, settings);
            std::string FSUBS(u32, settings);
            std::string FTOSID(u32, settings);
            std::string FTOSIS(u32, settings);
            std::string FTOUID(u32, settings);
            std::string FTOUIS(u32, settings);
            std::string FUITOD(u32, settings);
            std::string FUITOS(u32, settings);
        }
    }


    namespace thumb {
        namespace math {
            std::string ADC(u16, settings); 
            std::string ADD1(u16, settings);
            std::string ADD2(u16, settings);
            std::string ADD3(u16, settings);
            std::string ADD4(u16, settings);
            std::string ADD5(u16, settings);
            std::string ADD6(u16, settings);
            std::string ADD7(u16, settings);
            std::string SBC(u16, settings);
            std::string SUB1(u16, settings);
            std::string SUB2(u16, settings);
            std::string SUB3(u16, settings);
            std::string SUB4(u16, settings);
            std::string MUL(u16, settings);
        }

        namespace logic {
            std::string AND(u16, settings);
            std::string ASR1(u16, settings);
            std::string ASR2(u16, settings);
            std::string BIC(u16, settings);
            std::string EOR(u16, settings);
            std::string LSL1(u16, settings);
            std::string LSL2(u16, settings);
            std::string LSR1(u16, settings);
            std::string LSR2(u16, settings);
            std::string NEG(u16, settings);
            std::string ORR(u16, settings);
            std::string ROR(u16, settings);
            std::string TST(u16, settings);
        }

        namespace comparison {
            std::string CMN(u16, settings);
            std::string CMP1(u16, settings);
            std::string CMP2(u16, settings);
            std::string CMP3(u16, settings);
        }

        namespace movement {
            std::string MOV1(u16, settings);
            std::string MOV2(u16, settings);
            std::string MOV3(u16, settings);
            std::string MVN(u16, settings);
        }

        namespace branching {
            std::string B1(u16, u32 PC, settings);
            std::string B2(u16, u32 PC, settings);
            std::string BX(u16, settings);
            std::string BL_BLX1(u16, u32 PC, settings);
            std::string BLX2(u16, settings);
        }

        namespace misc {
            std::string SWI(u16, settings);
            std::string BKPT(u16, settings);
        }

        namespace load {
            std::string LDMIA(u16, settings);
            std::string LDR1(u16, settings);
            std::string LDR2(u16, settings);
            std::string LDR3(u16, settings);
            std::string LDR4(u16, settings);
            std::string LDRB1(u16, settings);
            std::string LDRB2(u16, settings);
            std::string LDRH1(u16, settings);
            std::string LDRH2(u16, settings);
            std::string LDRSB(u16, settings);
            std::string LDRSH(u16, settings);
            std::string POP(u16, settings);
        }

        namespace store {
            std::string STMIA(u16, settings);
            std::string STR1(u16, settings);
            std::string STR2(u16, settings);
            std::string STR3(u16, settings);
            std::string STRB1(u16, settings);
            std::string STRB2(u16, settings);
            std::string STRH1(u16, settings);
            std::string STRH2(u16, settings);
            std::string PUSH(u16, settings);
        }
    }
}