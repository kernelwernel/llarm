#pragma once

#include "../../instruction_id.hpp"

#include "shared/types.hpp"

#include <functional>
#include <string>
#include <map>

// the generation mechanism was benchmarked here:
// https://quick-bench.com/q/No_nYrHbcGwK5JTFl-qJtJ0ncc0

namespace internal::generators {
    namespace arm {
        namespace math {
            std::string ADC(const u32);
            std::string ADD(const u32);
            std::string RSB(const u32);
            std::string RSC(const u32);
            std::string SBC(const u32);
            std::string SUB(const u32);
        }

        namespace logic {
            std::string CMN(const u32);
            std::string AND(const u32);
            std::string CMP(const u32);
            std::string CLZ(const u32);
            std::string EOR(const u32);
            std::string ORR(const u32);
            std::string TEQ(const u32);
            std::string TST(const u32);
        }

        namespace movement {
            std::string MOV(const u32);
            std::string MVN(const u32);
            std::string MRS(const u32);
            std::string MSR_IMM(const u32);
            std::string MSR_REG(const u32);
        }

        namespace multiply {
            std::string MLA(const u32);
            std::string MUL(const u32);
            std::string SMLAL(const u32);
            std::string SMULL(const u32);
            std::string UMLAL(const u32);
            std::string UMULL(const u32);
        }

        namespace branching {
            std::string B(const u32);
            std::string BL(const u32);
            std::string BX(const u32);
        }

        namespace coprocessor {
            std::string CDP(const u32);
            std::string LDC(const u32);
            std::string MCR(const u32);
            std::string MRC(const u32);
            std::string STC(const u32);
        }

        namespace misc {
            std::string NOP(const u32);
            std::string PSR(const u32);
            std::string SWI(const u32);
        }

        namespace load {
            std::string LDM1(const u32);
            std::string LDM2(const u32);
            std::string LDM3(const u32);
            std::string LDR(const u32);
            std::string LDRB(const u32);
            std::string LDRBT(const u32);
            std::string LDRH(const u32);
            std::string LDRSB(const u32);
            std::string LDRSH(const u32);
            std::string LDRT(const u32);
        }

        namespace store {
            std::string STM1(const u32);
            std::string STM2(const u32);
            std::string STR(const u32);
            std::string STRB(const u32);
            std::string STRBT(const u32);
            std::string STRH(const u32);
            std::string STRT(const u32);
            std::string SWP(const u32);
            std::string SWPB(const u32);
        }

        namespace dsp {
            std::string LDRD(const u32);
            std::string MCRR(const u32);
            std::string MRRC(const u32);
            std::string PLD(const u32);
            std::string QADD(const u32);
            std::string QDADD(const u32);
            std::string QDSUB(const u32);
            std::string QSUB(const u32);
            std::string SMLA(const u32);
            std::string SMLAL(const u32);
            std::string SMLAW(const u32);
            std::string SMUL(const u32);
            std::string SMULW(const u32);
            std::string STRD(const u32);
        }

        namespace vfp {
            std::string FABSD(const u32);
            std::string FABSS(const u32);
            std::string FADDD(const u32);
            std::string FADDS(const u32);
            std::string FCMPD(const u32);
            std::string FCMPED(const u32);
            std::string FCMPES(const u32);
            std::string FCMPEZD(const u32);
            std::string FCMPEZS(const u32);
            std::string FCMPS(const u32);
            std::string FCMPZD(const u32);
            std::string FCMPZS(const u32);
            std::string FCPYD(const u32);
            std::string FCPYS(const u32);
            std::string FCVTDS(const u32);
            std::string FCVTSD(const u32);
            std::string FDIVD(const u32);
            std::string FDIVS(const u32);
            std::string FLDD(const u32);
            std::string FLDMD(const u32);
            std::string FLDMS(const u32);
            std::string FLDMX(const u32);
            std::string FLDS(const u32);
            std::string FMACD(const u32);
            std::string FMACS(const u32);
            std::string FMDHR(const u32);
            std::string FMDLR(const u32);
            std::string FMRDH(const u32);
            std::string FMRDL(const u32);
            std::string FMRS(const u32);
            std::string FMRX(const u32);
            std::string FMSCD(const u32);
            std::string FMSCS(const u32);
            std::string FMSR(const u32);
            std::string FMSTAT(const u32);
            std::string FMULD(const u32);
            std::string FMULS(const u32);
            std::string FMXR(const u32);
            std::string FNEGD(const u32);
            std::string FNEGS(const u32);
            std::string FNMACD(const u32);
            std::string FNMACS(const u32);
            std::string FNMSCD(const u32);
            std::string FNMSCS(const u32);
            std::string FNMULD(const u32);
            std::string FNMULS(const u32);
            std::string FSITOD(const u32);
            std::string FSITOS(const u32);
            std::string FSQRTD(const u32);
            std::string FSQRTS(const u32);
            std::string FSTD(const u32);
            std::string FSTMD(const u32);
            std::string FSTMS(const u32);
            std::string FSTMX(const u32);
            std::string FSTS(const u32);
            std::string FSUBD(const u32);
            std::string FSUBS(const u32);
            std::string FTOSID(const u32);
            std::string FTOSIS(const u32);
            std::string FTOUID(const u32);
            std::string FTOUIS(const u32);
            std::string FUITOD(const u32);
            std::string FUITOS(const u32);
        }
    }


    namespace thumb {
        namespace math {
            std::string ADC(const u16); 
            std::string ADD1(const u16);
            std::string ADD2(const u16);
            std::string ADD3(const u16);
            std::string ADD4(const u16);
            std::string ADD5(const u16);
            std::string ADD6(const u16);
            std::string ADD7(const u16);
            std::string SBC(const u16);
            std::string SUB1(const u16);
            std::string SUB2(const u16);
            std::string SUB3(const u16);
            std::string SUB4(const u16);
            std::string MUL(const u16);
        }

        namespace logic {
            std::string AND(const u16);
            std::string ASR1(const u16);
            std::string ASR2(const u16);
            std::string BIC(const u16);
            std::string EOR(const u16);
            std::string LSL1(const u16);
            std::string LSL2(const u16);
            std::string LSR1(const u16);
            std::string LSR2(const u16);
            std::string NEG(const u16);
            std::string ORR(const u16);
            std::string ROR(const u16);
            std::string TST(const u16);
        }

        namespace comparison {
            std::string CMN(const u16);
            std::string CMP1(const u16);
            std::string CMP2(const u16);
            std::string CMP3(const u16);
        }

        namespace movement {
            std::string MOV1(const u16);
            std::string MOV2(const u16);
            std::string MOV3(const u16);
            std::string MVN(const u16);
        }

        namespace branching {
            std::string B1(const u16, const u32 PC);
            std::string B2(const u16, const u32 PC);
            std::string BX(const u16);
            std::string BL_BLX1(const u16, const u32 PC);
            std::string BLX2(const u16);
        }

        namespace misc {
            std::string SWI(const u16);
            std::string BKPT(const u16);
        }

        namespace load {
            std::string LDMIA(const u16);
            std::string LDR1(const u16);
            std::string LDR2(const u16);
            std::string LDR3(const u16);
            std::string LDR4(const u16);
            std::string LDRB1(const u16);
            std::string LDRB2(const u16);
            std::string LDRH1(const u16);
            std::string LDRH2(const u16);
            std::string LDRSB(const u16);
            std::string LDRSH(const u16);
            std::string POP(const u16);
        }

        namespace store {
            std::string STMIA(const u16);
            std::string STR1(const u16);
            std::string STR2(const u16);
            std::string STR3(const u16);
            std::string STRB1(const u16);
            std::string STRB2(const u16);
            std::string STRH1(const u16);
            std::string STRH2(const u16);
            std::string PUSH(const u16);
        }
    }
}