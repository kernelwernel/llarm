#pragma once

#include "../../types.hpp"
#include "../../types_extra.hpp"

#include <bitset>

namespace opcodes {
    namespace arm {
        bool ADC(const arm_code_t &raw_code) noexcept;
        bool ADD(const arm_code_t &raw_code) noexcept;
        bool AND(const arm_code_t &raw_code) noexcept;
        bool UNDEFINED(const arm_code_t &raw_code) noexcept;
        bool NOP(const arm_code_t &raw_code) noexcept;
        bool B(const arm_code_t &raw_code) noexcept;
        bool BL(const arm_code_t &raw_code) noexcept;
        bool BIC(const arm_code_t &raw_code) noexcept;
        bool CDP(const arm_code_t &raw_code) noexcept;
        bool CMN(const arm_code_t &raw_code) noexcept;
        bool CMP(const arm_code_t &raw_code) noexcept;
        bool EOR(const arm_code_t &raw_code) noexcept;
        bool LDC(const arm_code_t &raw_code) noexcept;
        bool LDM1(const arm_code_t &raw_code) noexcept;
        bool LDM2(const arm_code_t &raw_code) noexcept;
        bool LDM3(const arm_code_t &raw_code) noexcept;
        bool LDR(const arm_code_t &raw_code) noexcept;
        bool LDRB(const arm_code_t &raw_code) noexcept;
        bool LDRBT(const arm_code_t &raw_code) noexcept;
        bool LDRT(const arm_code_t &raw_code) noexcept;
        bool MCR(const arm_code_t &raw_code) noexcept;
        bool MLA(const arm_code_t &raw_code) noexcept;
        bool MOV(const arm_code_t &raw_code) noexcept;
        bool MRC(const arm_code_t &raw_code) noexcept;
        bool MRS(const arm_code_t &raw_code) noexcept;
        bool MSR_IMM(const arm_code_t &raw_code) noexcept;
        bool MSR_REG(const arm_code_t &raw_code) noexcept;
        bool MUL(const arm_code_t &raw_code) noexcept;
        bool MVN(const arm_code_t &raw_code) noexcept;
        bool ORR(const arm_code_t &raw_code) noexcept;
        bool RSB(const arm_code_t &raw_code) noexcept;
        bool RSC(const arm_code_t &raw_code) noexcept;
        bool SBC(const arm_code_t &raw_code) noexcept;
        bool STC(const arm_code_t &raw_code) noexcept;
        bool STM1(const arm_code_t &raw_code) noexcept;
        bool STM2(const arm_code_t &raw_code) noexcept;
        bool STR(const arm_code_t &raw_code) noexcept;
        bool STRB(const arm_code_t &raw_code) noexcept;
        bool STRBT(const arm_code_t &raw_code) noexcept;
        bool STRT(const arm_code_t &raw_code) noexcept;
        bool SUB(const arm_code_t &raw_code) noexcept;
        bool SWI(const arm_code_t &raw_code) noexcept;
        bool SWP(const arm_code_t &raw_code) noexcept;
        bool SWPB(const arm_code_t &raw_code) noexcept;
        bool TEQ(const arm_code_t &raw_code) noexcept;
        bool TST(const arm_code_t &raw_code) noexcept;
        bool PSR(const arm_code_t &raw_code) noexcept;
        bool STRH(const arm_code_t &raw_code) noexcept; // v4
        bool LDRH(const arm_code_t &raw_code) noexcept; // v4
        bool LDRSB(const arm_code_t &raw_code) noexcept; // v4
        bool LDRSH(const arm_code_t &raw_code) noexcept; // v4
        bool BKPT(const arm_code_t &raw_code) noexcept; // v5
        bool BLX1(const arm_code_t &raw_code) noexcept; // v5
        bool BLX2(const arm_code_t &raw_code) noexcept; // v5
        bool CLZ(const arm_code_t &raw_code) noexcept; // v5
        bool BX(const arm_code_t &raw_code) noexcept; // VERSION 5 BUT SUPPORTS VERSION 4 T VARIANT
        bool SMLAL(const arm_code_t &raw_code) noexcept; // M variants
        bool SMULL(const arm_code_t &raw_code) noexcept; // M variants
        bool UMLAL(const arm_code_t &raw_code) noexcept; // M variants
        bool UMULL(const arm_code_t &raw_code) noexcept; // M variants
        bool LDRD(const arm_code_t &raw_code) noexcept; // dsp
        bool MCRR(const arm_code_t &raw_code) noexcept; // dsp
        bool MRRC(const arm_code_t &raw_code) noexcept; // dsp
        bool PLD(const arm_code_t &raw_code) noexcept; // dsp
        bool QADD(const arm_code_t &raw_code) noexcept; // dsp
        bool QDADD(const arm_code_t &raw_code) noexcept; // dsp
        bool QDSUB(const arm_code_t &raw_code) noexcept; // dsp
        bool QSUB(const arm_code_t &raw_code) noexcept; // dsp
        bool SMLA(const arm_code_t &raw_code) noexcept; // dsp
        bool SMLAL(const arm_code_t &raw_code) noexcept; // dsp
        bool SMLAW(const arm_code_t &raw_code) noexcept; // dsp
        bool SMUL(const arm_code_t &raw_code) noexcept; // dsp
        bool SMULW(const arm_code_t &raw_code) noexcept; // dsp
        bool STRD(const arm_code_t &raw_code) noexcept; // dsp
        bool FABSD(const arm_code_t &raw_code) noexcept; // vfp
        bool FABSS(const arm_code_t &raw_code) noexcept; // vfp
        bool FADDD(const arm_code_t &raw_code) noexcept; // vfp
        bool FADDS(const arm_code_t &raw_code) noexcept; // vfp
        bool FCMPD(const arm_code_t &raw_code) noexcept; // vfp
        bool FCMPED(const arm_code_t &raw_code) noexcept; // vfp
        bool FCMPES(const arm_code_t &raw_code) noexcept; // vfp
        bool FCMPEZD(const arm_code_t &raw_code) noexcept; // vfp
        bool FCMPEZS(const arm_code_t &raw_code) noexcept; // vfp
        bool FCMPS(const arm_code_t &raw_code) noexcept; // vfp
        bool FCMPZD(const arm_code_t &raw_code) noexcept; // vfp
        bool FCMPZS(const arm_code_t &raw_code) noexcept; // vfp
        bool FCPYD(const arm_code_t &raw_code) noexcept; // vfp
        bool FCPYS(const arm_code_t &raw_code) noexcept; // vfp
        bool FCVTDS(const arm_code_t &raw_code) noexcept; // vfp
        bool FCVTSD(const arm_code_t &raw_code) noexcept; // vfp
        bool FDIVD(const arm_code_t &raw_code) noexcept; // vfp
        bool FDIVS(const arm_code_t &raw_code) noexcept; // vfp
        bool FDIVS(const arm_code_t &raw_code) noexcept; // vfp
        bool FLDD(const arm_code_t &raw_code) noexcept; // vfp
        bool FLDMD(const arm_code_t &raw_code) noexcept; // vfp
        bool FLDMS(const arm_code_t &raw_code) noexcept; // vfp
        bool FLDMX(const arm_code_t &raw_code) noexcept; // vfp
        bool FLDS(const arm_code_t &raw_code) noexcept; // vfp
        bool FMACD(const arm_code_t &raw_code) noexcept; // vfp
        bool FMACS(const arm_code_t &raw_code) noexcept; // vfp
        bool FMDHR(const arm_code_t &raw_code) noexcept; // vfp
        bool FMDLR(const arm_code_t &raw_code) noexcept; // vfp
        bool FMRDH(const arm_code_t &raw_code) noexcept; // vfp
        bool FMRDL(const arm_code_t &raw_code) noexcept; // vfp
        bool FMRS(const arm_code_t &raw_code) noexcept; // vfp
        bool FMRX(const arm_code_t &raw_code) noexcept; // vfp 
        bool FMSCD(const arm_code_t &raw_code) noexcept; // vfp
        bool FMSCS(const arm_code_t &raw_code) noexcept; // vfp
        bool FMSR(const arm_code_t &raw_code) noexcept; // vfp
        bool FMSTAT(const arm_code_t &raw_code) noexcept; // vfp
        bool FMULD(const arm_code_t &raw_code) noexcept; // vfp
        bool FMULS(const arm_code_t &raw_code) noexcept; // vfp
        bool FMXR(const arm_code_t &raw_code) noexcept; // vfp
        bool FNEGD(const arm_code_t &raw_code) noexcept; // vfp
        bool FNEGS(const arm_code_t &raw_code) noexcept; // vfp
        bool FNMACD(const arm_code_t &raw_code) noexcept; // vfp
        bool FNMACS(const arm_code_t &raw_code) noexcept; // vfp
        bool FNMSCD(const arm_code_t &raw_code) noexcept; // vfp
        bool FNMSCS(const arm_code_t &raw_code) noexcept; // vfp
        bool FNMULD(const arm_code_t &raw_code) noexcept; // vfp
        bool FNMULS(const arm_code_t &raw_code) noexcept; // vfp
        bool FSITOD(const arm_code_t &raw_code) noexcept; // vfp
        bool FSITOS(const arm_code_t &raw_code) noexcept; // vfp
        bool FSQRTD(const arm_code_t &raw_code) noexcept; // vfp
        bool FSQRTS(const arm_code_t &raw_code) noexcept; // vfp
        bool FSTD(const arm_code_t &raw_code) noexcept; // vfp
        bool FSTMD(const arm_code_t &raw_code) noexcept; // vfp
        bool FSTMS(const arm_code_t &raw_code) noexcept; // vfp
        bool FSTMX(const arm_code_t &raw_code) noexcept; // vfp
        bool FSTS(const arm_code_t &raw_code) noexcept; // vfp
        bool FSUBD(const arm_code_t &raw_code) noexcept; // vfp
        bool FSUBS(const arm_code_t &raw_code) noexcept; // vfp
        bool FTOSID(const arm_code_t &raw_code) noexcept; // vfp
        bool FTOSIS(const arm_code_t &raw_code) noexcept; // vfp
        bool FTOUID(const arm_code_t &raw_code) noexcept; // vfp
        bool FTOUIS(const arm_code_t &raw_code) noexcept; // vfp
        bool FUITOD(const arm_code_t &raw_code) noexcept; // vfp
        bool FUITOS(const arm_code_t &raw_code) noexcept; // vfp
    }

    namespace thumb {
        bool ADC(const thumb_code_t &raw_code) noexcept;
        bool ADD1(const thumb_code_t &raw_code) noexcept;
        bool ADD2(const thumb_code_t &raw_code) noexcept;
        bool ADD3(const thumb_code_t &raw_code) noexcept;
        bool ADD4(const thumb_code_t &raw_code) noexcept;
        bool ADD5(const thumb_code_t &raw_code) noexcept;
        bool ADD6(const thumb_code_t &raw_code) noexcept;
        bool ADD7(const thumb_code_t &raw_code) noexcept;
        bool AND(const thumb_code_t &raw_code) noexcept;
        bool ASR1(const thumb_code_t &raw_code) noexcept;
        bool ASR2(const thumb_code_t &raw_code) noexcept;
        bool B1(const thumb_code_t &raw_code) noexcept;
        bool B2(const thumb_code_t &raw_code) noexcept;
        bool BIC(const thumb_code_t &raw_code) noexcept;
        bool BL(const thumb_code_t &raw_code) noexcept;
        bool BX(const thumb_code_t &raw_code) noexcept;
        bool CMN(const thumb_code_t &raw_code) noexcept;
        bool CMP1(const thumb_code_t &raw_code) noexcept;
        bool CMP2(const thumb_code_t &raw_code) noexcept;
        bool CMP3(const thumb_code_t &raw_code) noexcept;
        bool EOR(const thumb_code_t &raw_code) noexcept;
        bool LDMIA(const thumb_code_t &raw_code) noexcept;
        bool LDR1(const thumb_code_t &raw_code) noexcept;
        bool LDR2(const thumb_code_t &raw_code) noexcept;
        bool LDR3(const thumb_code_t &raw_code) noexcept;
        bool LDR4(const thumb_code_t &raw_code) noexcept;
        bool LDRB1(const thumb_code_t &raw_code) noexcept;
        bool LDRB2(const thumb_code_t &raw_code) noexcept;
        bool LDRH1(const thumb_code_t &raw_code) noexcept;
        bool LDRH2(const thumb_code_t &raw_code) noexcept;
        bool LDRSB(const thumb_code_t &raw_code) noexcept;
        bool LDRSH(const thumb_code_t &raw_code) noexcept;
        bool LSL1(const thumb_code_t &raw_code) noexcept;
        bool LSL2(const thumb_code_t &raw_code) noexcept;
        bool LSR1(const thumb_code_t &raw_code) noexcept;
        bool LSR2(const thumb_code_t &raw_code) noexcept;
        bool MOV1(const thumb_code_t &raw_code) noexcept;
        bool MOV2(const thumb_code_t &raw_code) noexcept;
        bool MOV3(const thumb_code_t &raw_code) noexcept;
        bool MUL(const thumb_code_t &raw_code) noexcept;
        bool MVN(const thumb_code_t &raw_code) noexcept;
        bool NOP(const thumb_code_t &raw_code) noexcept;
        bool NEG(const thumb_code_t &raw_code) noexcept;
        bool ORR(const thumb_code_t &raw_code) noexcept;
        bool POP(const thumb_code_t &raw_code) noexcept;
        bool PUSH(const thumb_code_t &raw_code) noexcept;
        bool ROR(const thumb_code_t &raw_code) noexcept;
        bool SBC(const thumb_code_t &raw_code) noexcept;
        bool STMIA(const thumb_code_t &raw_code) noexcept;
        bool STR1(const thumb_code_t &raw_code) noexcept;
        bool STR2(const thumb_code_t &raw_code) noexcept;
        bool STR3(const thumb_code_t &raw_code) noexcept;
        bool STRB1(const thumb_code_t &raw_code) noexcept;
        bool STRB2(const thumb_code_t &raw_code) noexcept;
        bool STRH1(const thumb_code_t &raw_code) noexcept;
        bool STRH2(const thumb_code_t &raw_code) noexcept;
        bool SUB1(const thumb_code_t &raw_code) noexcept;
        bool SUB2(const thumb_code_t &raw_code) noexcept;
        bool SUB3(const thumb_code_t &raw_code) noexcept;
        bool SUB4(const thumb_code_t &raw_code) noexcept;
        bool SWI(const thumb_code_t &raw_code) noexcept;
        bool TST(const thumb_code_t &raw_code) noexcept;
        bool BKPT(const thumb_code_t &raw_code) noexcept; // v5
        bool BLX1(const thumb_code_t &raw_code) noexcept; // v5
        bool BLX2(const thumb_code_t &raw_code) noexcept; // v5
    }
}










