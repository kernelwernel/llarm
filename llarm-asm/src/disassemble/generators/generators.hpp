#pragma once

#include "../../settings.hpp"

#include <llarm/shared/types.hpp>

#include <string>

// the generation mechanism was benchmarked here:
// https://quick-bench.com/q/No_nYrHbcGwK5JTFl-qJtJ0ncc0

namespace internal::generators {
    namespace arm {
        namespace math {
            std::string ADC(const u32 code, const settings& settings);
            std::string ADD(const u32 code, const settings& settings);
            std::string RSB(const u32 code, const settings& settings);
            std::string RSC(const u32 code, const settings& settings);
            std::string SBC(const u32 code, const settings& settings);
            std::string SUB(const u32 code, const settings& settings);
            std::string QADD16(const u32 code, const settings& settings);
            std::string QADD8(const u32 code, const settings& settings);
            std::string QADDSUBX(const u32 code, const settings& settings);
            std::string QSUB16(const u32 code, const settings& settings);
            std::string QSUB8(const u32 code, const settings& settings);
            std::string QSUBADDX(const u32 code, const settings& settings);
            std::string SADD16(const u32 code, const settings& settings);
            std::string SADD8(const u32 code, const settings& settings);
            std::string SADDSUBX(const u32 code, const settings& settings);
            std::string SEL(const u32 code, const settings& settings);
            std::string SHADD16(const u32 code, const settings& settings);
            std::string SHADD8(const u32 code, const settings& settings);
            std::string SHADDSUBX(const u32 code, const settings& settings);
            std::string SHSUB16(const u32 code, const settings& settings);
            std::string SHSUB8(const u32 code, const settings& settings);
            std::string SHSUBADDX(const u32 code, const settings& settings);
            std::string SSUB16(const u32 code, const settings& settings);
            std::string SSUB8(const u32 code, const settings& settings);
            std::string SSUBADDX(const u32 code, const settings& settings);
            std::string SXTAB(const u32 code, const settings& settings);
            std::string SXTAB16(const u32 code, const settings& settings);
            std::string SXTAH(const u32 code, const settings& settings);
            std::string SXTB(const u32 code, const settings& settings);
            std::string SXTB16(const u32 code, const settings& settings);
            std::string SXTH(const u32 code, const settings& settings);
            std::string UADD16(const u32 code, const settings& settings);
            std::string UADD8(const u32 code, const settings& settings);
            std::string UADDSUBX(const u32 code, const settings& settings);
            std::string UHADD16(const u32 code, const settings& settings);
            std::string UHADD8(const u32 code, const settings& settings);
            std::string UHADDSUBX(const u32 code, const settings& settings);
            std::string UHSUB16(const u32 code, const settings& settings);
            std::string UHSUB8(const u32 code, const settings& settings);
            std::string UHSUBADDX(const u32 code, const settings& settings);
            std::string UQADD16(const u32 code, const settings& settings);
            std::string UQADD8(const u32 code, const settings& settings);
            std::string UQADDSUBX(const u32 code, const settings& settings);
            std::string UQSUB16(const u32 code, const settings& settings);
            std::string UQSUB8(const u32 code, const settings& settings);
            std::string UQSUBADDX(const u32 code, const settings& settings);
            std::string USAD8(const u32 code, const settings& settings);
            std::string USADA8(const u32 code, const settings& settings);
            std::string USUB16(const u32 code, const settings& settings);
            std::string USUB8(const u32 code, const settings& settings);
            std::string USUBADDX(const u32 code, const settings& settings);
            std::string UXTAB(const u32 code, const settings& settings);
            std::string UXTAB16(const u32 code, const settings& settings);
            std::string UXTAH(const u32 code, const settings& settings);
            std::string UXTB(const u32 code, const settings& settings);
            std::string UXTB16(const u32 code, const settings& settings);
            std::string UXTH(const u32 code, const settings& settings);
        }
        
        namespace logic {
            std::string CMN(const u32 code, const settings& settings);
            std::string AND(const u32 code, const settings& settings);
            std::string BIC(const u32 code, const settings& settings);
            std::string CMP(const u32 code, const settings& settings);
            std::string CLZ(const u32 code, const settings& settings);
            std::string EOR(const u32 code, const settings& settings);
            std::string ORR(const u32 code, const settings& settings);
            std::string TEQ(const u32 code, const settings& settings);
            std::string TST(const u32 code, const settings& settings);
            std::string PKHBT(const u32 code, const settings& settings);
            std::string PKHTB(const u32 code, const settings& settings);
            std::string REV(const u32 code, const settings& settings);
            std::string REV16(const u32 code, const settings& settings);
            std::string REVSH(const u32 code, const settings& settings);
            std::string SSAT(const u32 code, const settings& settings);
            std::string SSAT16(const u32 code, const settings& settings);
            std::string USAT(const u32 code, const settings& settings);
            std::string USAT16(const u32 code, const settings& settings);
        }
        
        namespace movement {
            std::string MOV(const u32 code, const settings& settings);
            std::string MVN(const u32 code, const settings& settings);
            std::string MRS(const u32 code, const settings& settings);
            std::string MSR_IMM(const u32 code, const settings& settings);
            std::string MSR_REG(const u32 code, const settings& settings);
            std::string CPY(const u32 code, const settings& settings);
        }

        namespace multiply {
            std::string MLA(const u32 code, const settings& settings);
            std::string MUL(const u32 code, const settings& settings);
            std::string SMLAL(const u32 code, const settings& settings);
            std::string SMULL(const u32 code, const settings& settings);
            std::string UMLAL(const u32 code, const settings& settings);
            std::string UMULL(const u32 code, const settings& settings);
            std::string SMLAD(const u32 code, const settings& settings);
            std::string SMLALD(const u32 code, const settings& settings);
            std::string SMLSD(const u32 code, const settings& settings);
            std::string SMLSLD(const u32 code, const settings& settings);
            std::string SMMLA(const u32 code, const settings& settings);
            std::string SMMLS(const u32 code, const settings& settings);
            std::string SMMUL(const u32 code, const settings& settings);
            std::string SMUAD(const u32 code, const settings& settings);
            std::string SMUSD(const u32 code, const settings& settings);
            std::string UMAAL(const u32 code, const settings& settings);
        }

        namespace branching {
            std::string B(const u32 code, const u32 PC, const settings& settings);
            std::string BL(const u32 code, const u32 PC, const settings& settings);
            std::string BX(const u32 code, const settings& settings);
            std::string BLX1(const u32 code, const u32 PC, const settings& settings);
            std::string BLX2(const u32 code, const settings& settings);
        }

        namespace coprocessor {
            std::string CDP(const u32 code, const settings& settings);
            std::string LDC(const u32 code, const settings& settings);
            std::string MCR(const u32 code, const settings& settings);
            std::string MRC(const u32 code, const settings& settings);
            std::string STC(const u32 code, const settings& settings);
        }

        namespace misc {
            std::string NOP();
            std::string CMNP(const u32 code, const settings& settings);
            std::string CMPP(const u32 code, const settings& settings);
            std::string TEQP(const u32 code, const settings& settings);
            std::string TSTP(const u32 code, const settings& settings);
            std::string SWI(const u32 code, const settings& settings);
            std::string BKPT(const u32 code, const settings& settings);
            std::string PSR(const u32 code, const settings& settings);
            std::string CPS(const u32 code, const settings& settings);
            std::string SETEND(const u32 code);
        }

        namespace load {
            std::string LDM1(const u32 code, const settings& settings);
            std::string LDM2(const u32 code, const settings& settings);
            std::string LDM3(const u32 code, const settings& settings);
            std::string LDR(const u32 code, const settings& settings);
            std::string LDRB(const u32 code, const settings& settings);
            std::string LDRBT(const u32 code, const settings& settings);
            std::string LDRH(const u32 code, const settings& settings);
            std::string LDRSB(const u32 code, const settings& settings);
            std::string LDRSH(const u32 code, const settings& settings);
            std::string LDRT(const u32 code, const settings& settings);
            std::string LDREX(const u32 code, const settings& settings);
            std::string RFE(const u32 code, const settings& settings);
        }

        namespace store {
            std::string STM1(const u32 code, const settings& settings);
            std::string STM2(const u32 code, const settings& settings);
            std::string STR(const u32 code, const settings& settings);
            std::string STRB(const u32 code, const settings& settings);
            std::string STRBT(const u32 code, const settings& settings);
            std::string STRH(const u32 code, const settings& settings);
            std::string STRT(const u32 code, const settings& settings);
            std::string SWP(const u32 code, const settings& settings);
            std::string SWPB(const u32 code, const settings& settings);
            std::string SRS(const u32 code, const settings& settings);
            std::string STREX(const u32 code, const settings& settings);
        }

        namespace dsp {
            std::string LDRD(const u32 code, const settings& settings);
            std::string MCRR(const u32 code, const settings& settings);
            std::string MRRC(const u32 code, const settings& settings);
            std::string PLD(const u32 code, const settings& settings);
            std::string QADD(const u32 code, const settings& settings);
            std::string QDADD(const u32 code, const settings& settings);
            std::string QDSUB(const u32 code, const settings& settings);
            std::string QSUB(const u32 code, const settings& settings);
            std::string SMLAXY(const u32 code, const settings& settings);
            std::string SMLALXY(const u32 code, const settings& settings);
            std::string SMLAWY(const u32 code, const settings& settings);
            std::string SMULXY(const u32 code, const settings& settings);
            std::string SMULWY(const u32 code, const settings& settings);
            std::string STRD(const u32 code, const settings& settings);
        }

        namespace vfp {
            std::string FABSD(const u32 code, const settings& settings);
            std::string FABSS(const u32 code, const settings& settings);
            std::string FADDD(const u32 code, const settings& settings);
            std::string FADDS(const u32 code, const settings& settings);
            std::string FCMPD(const u32 code, const settings& settings);
            std::string FCMPED(const u32 code, const settings& settings);
            std::string FCMPES(const u32 code, const settings& settings);
            std::string FCMPEZD(const u32 code, const settings& settings);
            std::string FCMPEZS(const u32 code, const settings& settings);
            std::string FCMPS(const u32 code, const settings& settings);
            std::string FCMPZD(const u32 code, const settings& settings);
            std::string FCMPZS(const u32 code, const settings& settings);
            std::string FCPYD(const u32 code, const settings& settings);
            std::string FCPYS(const u32 code, const settings& settings);
            std::string FCVTDS(const u32 code, const settings& settings);
            std::string FCVTSD(const u32 code, const settings& settings);
            std::string FDIVD(const u32 code, const settings& settings);
            std::string FDIVS(const u32 code, const settings& settings);
            std::string FLDD(const u32 code, const settings& settings);
            std::string FLDMD(const u32 code, const settings& settings);
            std::string FLDMS(const u32 code, const settings& settings);
            std::string FLDMX(const u32 code, const settings& settings);
            std::string FLDS(const u32 code, const settings& settings);
            std::string FMACD(const u32 code, const settings& settings);
            std::string FMACS(const u32 code, const settings& settings);
            std::string FMDHR(const u32 code, const settings& settings);
            std::string FMDLR(const u32 code, const settings& settings);
            std::string FMRDH(const u32 code, const settings& settings);
            std::string FMRDL(const u32 code, const settings& settings);
            std::string FMRS(const u32 code, const settings& settings);
            std::string FMRX(const u32 code, const settings& settings);
            std::string FMSCD(const u32 code, const settings& settings);
            std::string FMSCS(const u32 code, const settings& settings);
            std::string FMSR(const u32 code, const settings& settings);
            std::string FMSTAT(const u32 code, const settings& settings);
            std::string FMULD(const u32 code, const settings& settings);
            std::string FMULS(const u32 code, const settings& settings);
            std::string FMXR(const u32 code, const settings& settings);
            std::string FNEGD(const u32 code, const settings& settings);
            std::string FNEGS(const u32 code, const settings& settings);
            std::string FNMACD(const u32 code, const settings& settings);
            std::string FNMACS(const u32 code, const settings& settings);
            std::string FNMSCD(const u32 code, const settings& settings);
            std::string FNMSCS(const u32 code, const settings& settings);
            std::string FNMULD(const u32 code, const settings& settings);
            std::string FNMULS(const u32 code, const settings& settings);
            std::string FSITOD(const u32 code, const settings& settings);
            std::string FSITOS(const u32 code, const settings& settings);
            std::string FSQRTD(const u32 code, const settings& settings);
            std::string FSQRTS(const u32 code, const settings& settings);
            std::string FSTD(const u32 code, const settings& settings);
            std::string FSTMD(const u32 code, const settings& settings);
            std::string FSTMS(const u32 code, const settings& settings);
            std::string FSTMX(const u32 code, const settings& settings);
            std::string FSTS(const u32 code, const settings& settings);
            std::string FSUBD(const u32 code, const settings& settings);
            std::string FSUBS(const u32 code, const settings& settings);
            std::string FTOSID(const u32 code, const settings& settings);
            std::string FTOSIS(const u32 code, const settings& settings);
            std::string FTOUID(const u32 code, const settings& settings);
            std::string FTOUIS(const u32 code, const settings& settings);
            std::string FUITOD(const u32 code, const settings& settings);
            std::string FUITOS(const u32 code, const settings& settings);
        }
    }


    namespace thumb {
        namespace math {
            std::string ADC(const u32 code, const settings& settings);
            std::string ADD1(const u32 code, const settings& settings);
            std::string ADD2(const u32 code, const settings& settings);
            std::string ADD3(const u32 code, const settings& settings);
            std::string ADD4(const u32 code, const settings& settings);
            std::string ADD5(const u32 code, const settings& settings);
            std::string ADD6(const u32 code, const settings& settings);
            std::string ADD7(const u32 code, const settings& settings);
            std::string SBC(const u32 code, const settings& settings);
            std::string SUB1(const u32 code, const settings& settings);
            std::string SUB2(const u32 code, const settings& settings);
            std::string SUB3(const u32 code, const settings& settings);
            std::string SUB4(const u32 code, const settings& settings);
            std::string MUL(const u32 code, const settings& settings);
        }

        namespace logic {
            std::string AND(const u32 code, const settings& settings);
            std::string ASR1(const u32 code, const settings& settings);
            std::string ASR2(const u32 code, const settings& settings);
            std::string BIC(const u32 code, const settings& settings);
            std::string EOR(const u32 code, const settings& settings);
            std::string LSL1(const u32 code, const settings& settings);
            std::string LSL2(const u32 code, const settings& settings);
            std::string LSR1(const u32 code, const settings& settings);
            std::string LSR2(const u32 code, const settings& settings);
            std::string NEG(const u32 code, const settings& settings);
            std::string ORR(const u32 code, const settings& settings);
            std::string ROR(const u32 code, const settings& settings);
            std::string TST(const u32 code, const settings& settings);
        }

        namespace comparison {
            std::string CMN(const u32 code, const settings& settings);
            std::string CMP1(const u32 code, const settings& settings);
            std::string CMP2(const u32 code, const settings& settings);
            std::string CMP3(const u32 code, const settings& settings);
        }

        namespace movement {
            std::string MOV1(const u32 code, const settings& settings);
            std::string MOV2(const u32 code, const settings& settings);
            std::string MOV3(const u32 code, const settings& settings);
            std::string MVN(const u32 code, const settings& settings);
        }

        namespace branching {
            std::string B1(const u32 code, const u32 PC, const settings& settings);
            std::string B2(const u32 code, const u32 PC, const settings& settings);
            std::string BX(const u32 code, const settings& settings);
            std::string BL_BLX1(const u32 code, const u32 PC, const settings& settings);
            std::string BLX2(const u32 code, const settings& settings);
        }

        namespace misc {
            std::string SWI(const u32 code, const settings& settings);
            std::string BKPT(const u32 code, const settings& settings);
        }

        namespace load {
            std::string LDMIA(const u32 code, const settings& settings);
            std::string LDR1(const u32 code, const settings& settings);
            std::string LDR2(const u32 code, const settings& settings);
            std::string LDR3(const u32 code, const settings& settings);
            std::string LDR4(const u32 code, const settings& settings);
            std::string LDRB1(const u32 code, const settings& settings);
            std::string LDRB2(const u32 code, const settings& settings);
            std::string LDRH1(const u32 code, const settings& settings);
            std::string LDRH2(const u32 code, const settings& settings);
            std::string LDRSB(const u32 code, const settings& settings);
            std::string LDRSH(const u32 code, const settings& settings);
            std::string POP(const u32 code, const settings& settings);
        }

        namespace store {
            std::string STMIA(const u32 code, const settings& settings);
            std::string STR1(const u32 code, const settings& settings);
            std::string STR2(const u32 code, const settings& settings);
            std::string STR3(const u32 code, const settings& settings);
            std::string STRB1(const u32 code, const settings& settings);
            std::string STRB2(const u32 code, const settings& settings);
            std::string STRH1(const u32 code, const settings& settings);
            std::string STRH2(const u32 code, const settings& settings);
            std::string PUSH(const u32 code, const settings& settings);
        }
    }
}