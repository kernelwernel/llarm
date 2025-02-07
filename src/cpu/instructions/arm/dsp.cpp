#include "types.hpp"
#include "id.hpp"
#include "cpu/instructions/instructions.hpp"
#include "cpu/core/registers.hpp"


/**
 * 
 */
void instructions::arm::DSP::LDRD(const arm_code_t& code, REGISTERS& reg) {
    reg.arm_increment_PC();
}


/**
 * 
 */
void instructions::arm::DSP::MCRR(const arm_code_t& code, REGISTERS& reg) {
    reg.arm_increment_PC();
}


/**
 * 
 */
void instructions::arm::DSP::MRRC(const arm_code_t& code, REGISTERS& reg) {
    reg.arm_increment_PC();
}


/**
 * 
 */
void instructions::arm::DSP::PLD(const arm_code_t& code, REGISTERS& reg) {
    reg.arm_increment_PC();
}


/**
 * 
 */
void instructions::arm::DSP::QADD(const arm_code_t& code, REGISTERS& reg) {
    reg.arm_increment_PC();
}


/**
 * 
 */
void instructions::arm::DSP::QDADD(const arm_code_t& code, REGISTERS& reg) {
    reg.arm_increment_PC();
}


/**
 *
 */
void instructions::arm::DSP::QDSUB(const arm_code_t& code, REGISTERS& reg) {
    reg.arm_increment_PC();
}


/**
 * if ConditionPassed(cond) then
 *    Rd = SignedSat(Rm - Rn, 32)
 *    if SignedDoesSat(Rm - Rn, 32) then
 *       Q Flag = 1
 */
void instructions::arm::DSP::QSUB(const arm_code_t& code, REGISTERS& reg) {
    reg.arm_increment_PC();
}


/**
 * 
 */
void instructions::arm::DSP::SMLA(const arm_code_t& code, REGISTERS& reg) {
    reg.arm_increment_PC();
}


/**
 * 
 */
void instructions::arm::DSP::SMLAL(const arm_code_t& code, REGISTERS& reg) {
    reg.arm_increment_PC();
}


/**
 * 
 */
void instructions::arm::DSP::SMLAW(const arm_code_t& code, REGISTERS& reg) {
    reg.arm_increment_PC();
}


/**
 * 
 */
void instructions::arm::DSP::SMUL(const arm_code_t& code, REGISTERS& reg) {
    reg.arm_increment_PC();
}


/**
 * 
 */
void instructions::arm::DSP::SMULW(const arm_code_t& code, REGISTERS& reg) {
    reg.arm_increment_PC();
}


/**
 * 
 */
void instructions::arm::DSP::STRD(const arm_code_t& code, REGISTERS& reg) {
    reg.arm_increment_PC();
}