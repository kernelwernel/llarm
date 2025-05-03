
#include "shared/types.hpp"
#include "../instructions.hpp"



void INSTRUCTIONS::arm::vfp::FABSD(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FABSS(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FADDD(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FADDS(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FCMPD(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FCMPED(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FCMPES(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FCMPEZD(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FCMPEZS(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FCMPS(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FCMPZD(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FCMPZS(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FCPYD(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FCPYS(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FCVTDS(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FCVTSD(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FDIVD(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FDIVS(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FLDD(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FLDMD(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FLDMS(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FLDMX(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FLDS(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FMACD(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FMACS(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FMDHR(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FMDLR(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FMRDH(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FMRDL(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FMRS(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FMRX(const arm_code_t& code) {

    reg.arm_increment_PC();
} 

void INSTRUCTIONS::arm::vfp::FMSCD(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FMSCS(const arm_code_t& code) {

    reg.arm_increment_PC();
}

/**
 * if ConditionPassed(cond) then
 *     Sn = Rd
 */
void INSTRUCTIONS::arm::vfp::FMSR(const arm_code_t& code) {
    //const id::reg Rn_id = reg.fetch_reg_id(code, 12, 15);
    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FMSTAT(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FMULD(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FMULS(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FMXR(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FNEGD(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FNEGS(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FNMACD(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FNMACS(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FNMSCD(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FNMSCS(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FNMULD(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FNMULS(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FSITOD(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FSITOS(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FSQRTD(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FSQRTS(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FSTD(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FSTMD(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FSTMS(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FSTMX(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FSTS(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FSUBD(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FSUBS(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FTOSID(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FTOSIS(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FTOUID(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FTOUIS(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FUITOD(const arm_code_t& code) {

    reg.arm_increment_PC();
}

void INSTRUCTIONS::arm::vfp::FUITOS(const arm_code_t& code) {

    reg.arm_increment_PC();
}