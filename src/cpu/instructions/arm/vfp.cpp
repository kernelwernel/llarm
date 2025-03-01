
#include "types.hpp"
#include "../instructions.hpp"



void instructions::arm::VFP::FABSD(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FABSS(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FADDD(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FADDS(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FCMPD(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FCMPED(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FCMPES(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FCMPEZD(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FCMPEZS(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FCMPS(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FCMPZD(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FCMPZS(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FCPYD(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FCPYS(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FCVTDS(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FCVTSD(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FDIVD(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FDIVS(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FDIVS(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FLDD(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FLDMD(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FLDMS(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FLDMX(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FLDS(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FMACD(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FMACS(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FMDHR(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FMDLR(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FMRDH(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FMRDL(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FMRS(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FMRX(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
} 

void instructions::arm::VFP::FMSCD(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FMSCS(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

/**
 * if ConditionPassed(cond) then
 *     Sn = Rd
 */
void instructions::arm::VFP::FMSR(const arm_code_t& code, REGISTERS& reg) {
    const id::reg Rn_id = reg.fetch_reg_id(code, 12, 15);
    reg.arm_increment_PC();
}

void instructions::arm::VFP::FMSTAT(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FMULD(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FMULS(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FMXR(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FNEGD(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FNEGS(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FNMACD(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FNMACS(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FNMSCD(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FNMSCS(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FNMULD(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FNMULS(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FSITOD(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FSITOS(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FSQRTD(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FSQRTS(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FSTD(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FSTMD(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FSTMS(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FSTMX(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FSTS(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FSUBD(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FSUBS(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FTOSID(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FTOSIS(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FTOUID(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FTOUIS(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FUITOD(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}

void instructions::arm::VFP::FUITOS(const arm_code_t& code, REGISTERS& reg) {

    reg.arm_increment_PC();
}