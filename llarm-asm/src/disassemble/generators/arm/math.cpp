#include "../generators.hpp"
#include "../util.hpp"
#include "../patterns/patterns.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>

#include <string>

using namespace internal;

/**
 * ADC{<cond>}{S} <Rd>, <Rn>, <shifter_operand>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * S      Causes the S bit (bit[20]) in the instruction to be set to 1 and specifies that the instruction
 *        updates the CPSR. If S is omitted, the S bit is set to 0 and the CPSR is not changed by the
 *        instruction. Two types of CPSR update can occur when S is specified:
 *          •If <Rd> is not R15, the N and Z flags are set according to the result of the addition,
 *          and the C and V flags are set according to whether the addition generated a carry
 *          (unsigned overflow) and a signed overflow, respectively. The rest of the CPSR is
 *          unchanged.
 * 
 *          •If <Rd> is R15, the SPSR of the current mode is copied to the CPSR. This form of
 *          the instruction is UNPREDICTABLE if executed in User mode or System mode, because
 *          these modes do not have an SPSR.
 * 
 * <Rd>   Specifies the destination register of the instruction.
 * <Rn>   Specifies the register that contains the first operand for the addition.
 * <shifter_operand>
 *        Specifies the second operand for the addition. The options for this operand are described in
 *        Addressing Mode 1 - Data-processing operands on page A5-2, including how each option
 *        causes the I bit (bit[25]) and the shifter_operand bits (bits[11:0]) to be set in the instruction.
 *        
 *        If the I bit is 0 and both bit[7] and bit[4] of shifter_operand are 1, the instruction is not ADC.
 *        Instead, see Extending the instruction set on page A3-27 to determine which instruction it is.
 *
 * reference: A4-4
 */
std::string generators::arm::math::ADC(const u32 code, const settings& settings) {
    return patterns::S_Rd_Rn_data(code, "ADC", settings);
}


/**
 * ADD{<cond>}{S} <Rd>, <Rn>, <shifter_operand>
 * where:
 * <cond> Is the condition under which the instruction is executed. The condition field on page A3-5.
 *        If <cond> is omitted, the AL (always) condition is used.
 * S      Causes the S bit (bit[20]) in the instruction to be set to 1 and specifies that the instruction
 *        updates the CPSR. If S is omitted, the S bit is set to 0 and the CPSR is not changed by the
 *        instruction. Two types of CPSR update can occur when S is specified:
 *          •If <Rd> is not R15, the N and Z flags are set according to the result of the addition,
 *          and the C and V flags are set according to whether the addition generated a carry
 *          (unsigned overflow) and a signed overflow, respectively. The rest of the CPSR is
 *          unchanged.
 *          •If <Rd> is R15, the SPSR of the current mode is copied to the CPSR. This form of
 *          the instruction is UNPREDICTABLE if executed in User mode or System mode, because
 *          these modes do not have an SPSR.
 * 
 * <Rd>   Specifies the destination register of the instruction.
 * <Rn>   Specifies the register that contains the first operand for the addition.
 * 
 * <shifter_operand>
 *        Specifies the second operand for the addition. The options for this operand are described in
 *        Addressing Mode 1 - Data-processing operands on page A5-2, including how each option
 *        causes the I bit (bit[25]) and the shifter_operand bits (bits[11:0]) to be set in the instruction.
 *        If the I bit is 0 and both bit[7] and bit[4] of shifter_operand are 1, the instruction is not ADD.
 *        Instead, see Extending the instruction set on page A3-27 to determine which instruction it is.
 *
 * reference: A4-6
 */
std::string generators::arm::math::ADD(const u32 code, const settings& settings) {
    return patterns::S_Rd_Rn_data(code, "ADD", settings);
}


/**
 * RSB{<cond>}{S} <Rd>, <Rn>, <shifter_operand>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * S      Sets the S bit (bit[20]) in the instruction to 1 and specifies that the instruction updates the
 *        CPSR. If S is omitted, the S bit is set to 0 and the CPSR is not changed by the instruction.
 *        Two types of CPSR update can occur when S is specified:
 *          •If <Rd> is not R15, the N and Z flags are set according to the result of the subtraction,
 *          and the C and V flags are set according to whether the subtraction generated a borrow
 *          (unsigned underflow) and a signed overflow, respectively. The rest of the CPSR is
 *          unchanged.
 *          •If <Rd> is R15, the SPSR of the current mode is copied to the CPSR. This form of
 *          the instruction is UNPREDICTABLE if executed in User mode or System mode, because
 *          these modes do not have an SPSR.
 * 
 * <Rd>   Specifies the destination register of the instruction.
 * <Rn>   Specifies the register that contains the second operand for the subtraction.
 * <shifter_operand>
 *        Specifies the first operand for the subtraction. The options for this operand are described in
 *        Addressing Mode 1 - Data-processing operands on page A5-2, including how each option
 *        causes the I bit (bit[25]) and the shifter_operand bits (bits[11:0]) to be set in the instruction.
 *        If the I bit is 0 and both bit[7] and bit[4] of shifter_operand are 1, the instruction is not RSB.
 *        Instead, see Extending the instruction set on page A3-27 to determine which instruction it is.
 * 
 * reference: A4-72
 */
std::string generators::arm::math::RSB(const u32 code, const settings& settings) {
    return patterns::S_Rd_Rn_data(code, "RSB", settings);
}


/**
 * RSC{<cond>}{S} <Rd>, <Rn>, <shifter_operand>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * S      Sets the S bit (bit[20]) in the instruction to 1 and specifies that the instruction updates the
 *        CPSR. If S is omitted, the S bit is set to 0 and the CPSR is not changed by the instruction.
 *        Two types of CPSR update can occur when S is specified:
 *          •If <Rd> is not R15, the N and Z flags are set according to the result of the subtraction,
 *          and the C and V flags are set according to whether the subtraction generated a borrow
 *          (unsigned underflow) and a signed overflow, respectively. The rest of the CPSR is
 *          unchanged.
 *          •If <Rd> is R15, the SPSR of the current mode is copied to the CPSR. This form of
 *          the instruction is UNPREDICTABLE if executed in User mode or System mode, because
 *          these modes do not have an SPSR.
 * 
 * <Rd>   Specifies the destination register of the instruction.
 * <Rn>   Specifies the register that contains the second operand for the subtraction.
 * <shifter_operand>
 *        Specifies the first operand for the subtraction. The options for this operand are described in
 *        Addressing Mode 1 - Data-processing operands on page A5-2, including how each option
 *        causes the I bit (bit[25]) and the shifter_operand bits (bits[11:0]) to be set in the instruction.
 *        If the I bit is 0 and both bit[7] and bit[4] of shifter_operand are 1, the instruction is not RSC.
 *        Instead, see Extending the instruction set on page A3-27 to determine which instruction it is.
 * 
 * reference: A4-74
 */
std::string generators::arm::math::RSC(const u32 code, const settings& settings) {
    return patterns::S_Rd_Rn_data(code, "RSC", settings);
}


/**
 * SBC{<cond>}{S} <Rd>, <Rn>, <shifter_operand>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * S      Sets the S bit (bit[20]) in the instruction to 1 and specifies that the instruction updates the
 *        CPSR. If S is omitted, the S bit is set to 0 and the CPSR is not changed by the instruction.
 *        Two types of CPSR update can occur when S is specified:
 *          •If <Rd> is not R15, the N and Z flags are set according to the result of the subtraction,
 *          and the C and V flags are set according to whether the subtraction generated a borrow
 *          (unsigned underflow) and a signed overflow, respectively. The rest of the CPSR is
 *          unchanged.
 *          •If <Rd> is R15, the SPSR of the current mode is copied to the CPSR. This form of
 *          the instruction is UNPREDICTABLE if executed in User mode or System mode, because
 *          these modes do not have an SPSR.
 * 
 * <Rd>  Specifies the destination register of the instruction.
 * <Rn>  Specifies the register that contains the first operand for the subtraction.
 * 
 * <shifter_operand>
 *       Specifies the second operand for the subtraction. The options for this operand are described
 *       in Addressing Mode 1 - Data-processing operands on page A5-2, including how each
 *       option causes the I bit (bit[25]) and the shifter_operand bits (bits[11:0]) to be set in the
 *       instruction.
 *       If the I bit is 0 and both bit[7] and bit[4] of shifter_operand are 1, the instruction is not SBC.
 *       Instead, see Extending the instruction set on page A3-27 to determine which instruction it is.
 *
 * reference: A4-76
 */
std::string generators::arm::math::SBC(const u32 code, const settings& settings) {
    return patterns::S_Rd_Rn_data(code, "SBC", settings);
}


/**
 * SUB{<cond>}{S} <Rd>, <Rn>, <shifter_operand>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 *        condition field on page A3-5. If <cond> is omitted, the AL (always) condition is used.
 * S      Sets the S bit (bit[20]) in the instruction to 1 and specifies that the instruction updates the
 *        CPSR. If S is omitted, the S bit is set to 0 and the CPSR is not changed by the instruction.
 *        Two types of CPSR update can occur when S is specified:
 *          •If <Rd> is not R15, the N and Z flags are set according to the result of the subtraction,
 *          and the C and V flags are set according to whether the subtraction generated a borrow
 *          (unsigned underflow) and a signed overflow, respectively. The rest of the CPSR is
 *          unchanged.
 * 
 *          •If <Rd> is R15, the SPSR of the current mode is copied to the CPSR. This form of
 *          the instruction is UNPREDICTABLE if executed in User mode or System mode, because
 *          these modes do not have an SPSR.
 * 
 * <Rd>   Specifies the destination register of the instruction.
 * <Rn>   Specifies the register that contains the first operand for the subtraction.
 * 
 * <shifter_operand>
 *        Specifies the second operand for the subtraction. The options for this operand are described
 *        in Addressing Mode 1 - Data-processing operands on page A5-2, including how each
 *        option causes the I bit (bit[25]) and the shifter_operand bits (bits[11:0]) to be set in the
 *        instruction.
 *        If the I bit is 0 and both bit[7] and bit[4] of shifter_operand are 1, the instruction is not SUB.
 *        Instead, see Extending the instruction set on page A3-27 to determine which instruction it is.
 *
 * reference: A4-98
 */
std::string generators::arm::math::SUB(const u32 code, const settings& settings) {
    return patterns::S_Rd_Rn_data(code, "SUB", settings);
}


/**
 * QADD16{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand.
 */
std::string generators::arm::math::QADD16(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "QADD16", settings);
}


/**
 * QADD8{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand
 */
std::string generators::arm::math::QADD8(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "QADD8", settings);
}


/**
 * QADDSUBX{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand
 */
std::string generators::arm::math::QADDSUBX(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "QADDSUBX", settings);
}


/**
 * QSUB16{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand
 */
std::string generators::arm::math::QSUB16(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "QSUB16", settings);
}


/**
 * QSUB8{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand
 */
std::string generators::arm::math::QSUB8(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "QSUB8", settings);
}


/**
 * QSUBADDX{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand
 */
std::string generators::arm::math::QSUBADDX(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "QSUBADDX", settings);
}


/**
 * SADD16{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond>Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>Specifies the destination register.
 * <Rn>Specifies the register that contains the first operand.
 * <Rm>Specifies the register that contains the second operand.
 */
std::string generators::arm::math::SADD16(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "SADD16", settings);
}


/**
 * SADD8{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond>Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>Specifies the destination register.
 * <Rn>Specifies the register that contains the first operand.
 * <Rm>Specifies the register that contains the second operand.
 */
std::string generators::arm::math::SADD8(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "SADD8", settings);
}


/**
 * SADDSUBX{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond>Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>Specifies the destination register.
 * <Rn>Specifies the register that contains the first operand.
 * <Rm>Specifies the register that contains the second operand.
 */
std::string generators::arm::math::SADDSUBX(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "SADDSUBX", settings);
}


/**
 * SEL{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond>Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>Specifies the destination register.
 * <Rn>Specifies the register that contains the first operand.
 * <Rm>Specifies the register that contains the second operand.
 */
std::string generators::arm::math::SEL(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "SEL", settings);
}


/**
 * SHADD16{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond>Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>Specifies the destination register.
 * <Rn>Specifies the register that contains the first operand.
 * <Rm>Specifies the register that contains the second operand.
 */
std::string generators::arm::math::SHADD16(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "SHADD16", settings);
}


/**
 * SHADD8{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond>Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>Specifies the destination register.
 * <Rn>Specifies the register that contains the first operand.
 * <Rm>Specifies the register that contains the second operand.
 */
std::string generators::arm::math::SHADD8(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "SHADD8", settings);
}


/**
 * SHADDSUBX{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond>Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>Specifies the destination register.
 * <Rn>Specifies the register that contains the first operand.
 * <Rm>Specifies the register that contains the second operand.
 */
std::string generators::arm::math::SHADDSUBX(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "SHADDSUBX", settings);
}


/**
 * SHSUB16{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond>Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>Specifies the destination register.
 * <Rn>Specifies the register that contains the first operand.
 * <Rm>Specifies the register that contains the second operand.
 */
std::string generators::arm::math::SHSUB16(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "SHSUB16", settings);
}


/**
 * SHSUB16{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond>Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>Specifies the destination register.
 * <Rn>Specifies the register that contains the first operand.
 * <Rm>Specifies the register that contains the second operand.
 */
std::string generators::arm::math::SHSUB8(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "SHSUB8", settings);
}


/**
 * SHSUBADDX{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond>Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd>Specifies the destination register.
 * <Rn>Specifies the register that contains the first operand.
 * <Rm>Specifies the register that contains the second operand.
 */
std::string generators::arm::math::SHSUBADDX(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "SHSUBADDX", settings);
}


/**
 * SSUB16{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand.
 */
std::string generators::arm::math::SSUB16(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "SSUB16", settings);
}


/**
 * SSUB8{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand.
 */
std::string generators::arm::math::SSUB8(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "SSUB8", settings);
}


/**
 * SSUB8{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand.
 */
std::string generators::arm::math::SSUBADDX(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "SSUBADDX", settings);
}


/**
 * SXTAB{<cond>} <Rd>, <Rn>, <Rm>{, <rotation>}
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined
 * in The condition field on page A3-3. If <cond> is omitted, the AL (always) condition
 * is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand.
 * <rotation> This can be any one of:
 * • ROR #8. This is encoded as 0b01 in the rotate field.
 * • ROR #16. This is encoded as 0b10 in the rotate field.
 * • ROR #24. This is encoded as 0b11 in the rotate field.
 * • Omitted. This is encoded as 0b00 in the rotate field.
 * Note
 * If your assembler accepts shifts by #0 and treats them as equivalent to no shift
 * or LSL #0, then it must accept ROR #0 here. It is equivalent to omitting
 * <rotation>
 */
std::string generators::arm::math::SXTAB(const u32 code, const settings& settings) {
    return patterns::Rd_Rn_Rm_rotate(code, "SXTAB", settings);
}


/**
 * SXTAB16{<cond>} <Rd>, <Rn>, <Rm>{, <rotation>}
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined
 * in The condition field on page A3-3. If <cond> is omitted, the AL (always) condition
 * is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand.
 * <rotation> This can be any one of:
 * • ROR #8. This is encoded as 0b01 in the rotate field.
 * • ROR #16. This is encoded as 0b10 in the rotate field.
 * • ROR #24. This is encoded as 0b11 in the rotate field.
 * • Omitted. This is encoded as 0b00 in the rotate field.
 * Note
 * If your assembler accepts shifts by #0 and treats them as equivalent to no shift
 * or LSL #0, then it must accept ROR #0 here. It is equivalent to omitting
 * <rotation>
 */
std::string generators::arm::math::SXTAB16(const u32 code, const settings& settings) {
    return patterns::Rd_Rn_Rm_rotate(code, "SXTAB16", settings);
} 


/**
 * SXTAH{<cond>} <Rd>, <Rn>, <Rm>{, <rotation>}
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined
 * in The condition field on page A3-3. If <cond> is omitted, the AL (always) condition
 * is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand.
 * <rotation> This can be any one of:
 * • ROR #8. This is encoded as 0b01 in the rotate field.
 * • ROR #16. This is encoded as 0b10 in the rotate field.
 * • ROR #24. This is encoded as 0b11 in the rotate field.
 * • Omitted. This is encoded as 0b00 in the rotate field.
 * Note
 * If your assembler accepts shifts by #0 and treats them as equivalent to no shift
 * or LSL #0, then it must accept ROR #0 here. It is equivalent to omitting
 * <rotation>
 */
std::string generators::arm::math::SXTAH(const u32 code, const settings& settings) {
    return patterns::Rd_Rn_Rm_rotate(code, "SXTAH", settings);
}


/**
 * SXTB{<cond>} <Rd>, <Rm>{, <rotation>}
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined
 * in The condition field on page A3-3. If <cond> is omitted, the AL (always) condition
 * is used.
 * <Rd> Specifies the destination register.
 * <Rm> Specifies the register that contains the operand.
 * <rotation> This can be any one of:
 * • ROR #8. This is encoded as 0b01 in the rotate field.
 * • ROR #16. This is encoded as 0b10 in the rotate field.
 * • ROR #24. This is encoded as 0b11 in the rotate field.
 * • Omitted. This is encoded as 0b00 in the rotate field.
 * Note
 * If your assembler accepts shifts by #0 and treats them as equivalent to no shift
 * or LSL #0, then it must accept ROR #0 here. It is equivalent to omitting
 * <rotation>
 */
std::string generators::arm::math::SXTB(const u32 code, const settings& settings) {
    return patterns::Rd_Rm_rotate(code, "SXTB", settings);
}


/**
 * SXTB16{<cond>} <Rd>, <Rm>{, <rotation>}
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined
 * in The condition field on page A3-3. If <cond> is omitted, the AL (always) condition
 * is used.
 * <Rd> Specifies the destination register.
 * <Rm> Specifies the register that contains the operand.
 * <rotation> This can be any one of:
 * • ROR #8. This is encoded as 0b01 in the rotate field.
 * • ROR #16. This is encoded as 0b10 in the rotate field.
 * • ROR #24. This is encoded as 0b11 in the rotate field.
 * • Omitted. This is encoded as 0b00 in the rotate field.
 * Note
 * If your assembler accepts shifts by #0 and treats them as equivalent to no shift
 * or LSL #0, then it must accept ROR #0 here. It is equivalent to omitting
 * <rotation>
 */
std::string generators::arm::math::SXTB16(const u32 code, const settings& settings) {
    return patterns::Rd_Rm_rotate(code, "SXTB16", settings);
}


/**
 * SXTH{<cond>} <Rd>, <Rm>{, <rotation>}
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined
 * in The condition field on page A3-3. If <cond> is omitted, the AL (always) condition
 * is used.
 * <Rd> Specifies the destination register.
 * <Rm> Specifies the register that contains the operand.
 * <rotation> This can be any one of:
 * • ROR #8. This is encoded as 0b01 in the rotate field.
 * • ROR #16. This is encoded as 0b10 in the rotate field.
 * • ROR #24. This is encoded as 0b11 in the rotate field.
 * • Omitted. This is encoded as 0b00 in the rotate field.
 * Note
 * If your assembler accepts shifts by #0 and treats them as equivalent to no shift
 * or LSL #0, then it must accept ROR #0 here. It is equivalent to omitting
 * <rotation>
 */
std::string generators::arm::math::SXTH(const u32 code, const settings& settings) {
    return patterns::Rd_Rm_rotate(code, "SXTH", settings);
}


/**
 * UADD16{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand
 */
std::string generators::arm::math::UADD16(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "UADD16", settings);
}


/**
 * UADD8{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand
 */
std::string generators::arm::math::UADD8(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "UADD8", settings);
}


/**
 * UADDSUBX{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand.
 */
std::string generators::arm::math::UADDSUBX(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "UADDSUBX", settings);
}


/**
 * UHADD16{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand.
 */
std::string generators::arm::math::UHADD16(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "UHADD16", settings);
}


/**
 * UHADD8{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand
 */
std::string generators::arm::math::UHADD8(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "UHADD8", settings);
}


/**
 * UHADDSUBX{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand
 */
std::string generators::arm::math::UHADDSUBX(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "UHADDSUBX", settings);
}


/**
 * UHSUB16{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand
 */
std::string generators::arm::math::UHSUB16(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "UHSUB16", settings);
}


/**
 * UHSUB8{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand
 */
std::string generators::arm::math::UHSUB8(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "UHSUB8", settings);
}


/**
 * UHSUBADDX{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand.
 */
std::string generators::arm::math::UHSUBADDX(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "UHSUBADDX", settings);
}


/**
 * UQADD16{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand
 */
std::string generators::arm::math::UQADD16(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "UQADD16", settings);
}


/**
 * UQADD8{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand
 */
std::string generators::arm::math::UQADD8(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "UQADD8", settings);
}

/**
 * UQADDSUBX{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand.
 */
std::string generators::arm::math::UQADDSUBX(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "UQADDSUBX", settings);
}


/**
 * UQSUB16{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand.
 */
std::string generators::arm::math::UQSUB16(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "UQSUB16", settings);
}


/**
 * UQSUB8{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand
 */
std::string generators::arm::math::UQSUB8(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "UQSUB8", settings);
}


/**
 * UQSUBADDX{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand.
 */
std::string generators::arm::math::UQSUBADDX(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "UQSUBADDX", settings);
}


/**
 * USAD8{<cond>} <Rd>, <Rm>, <Rs>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd> Specifies the destination register.
 * <Rm> Specifies the register that contains the first operand.
 * <Rs> Specifies the register that contains the second operand.
 */
std::string generators::arm::math::USAD8(const u32 code, const settings& settings) {
    const std::string Rd = util::reg_string(code, 16, 19, settings);
    const std::string Rs = util::reg_string(code, 8, 11, settings);
    const std::string Rm = util::reg_string(code, 0, 3, settings);

    return util::make_string("USAD8", util::cond(code, settings), " ", Rd, ", ", Rm, ", ", Rs);
}


/**
 * USADA8{<cond>} <Rd>, <Rm>, <Rs>, <Rn>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd> Specifies the destination register.
 * <Rm> Specifies the register that contains the first main operand.
 * <Rs> Specifies the register that contains the second main operand.
 * <Rn> Specifies the register that contains the accumulate operand.
 */
std::string generators::arm::math::USADA8(const u32 code, const settings& settings) {
    const std::string Rd = util::reg_string(code, 16, 19, settings);
    const std::string Rm = util::reg_string(code, 0, 3, settings);
    const std::string Rs = util::reg_string(code, 8, 11, settings);
    const std::string Rn = util::reg_string(code, 12, 15, settings);

    return util::make_string("USADA8", util::cond(code, settings), " ", Rd, ", ", Rm, ", ", Rs, ", ", Rn);
}


/**
 * USUB16{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand.
 */
std::string generators::arm::math::USUB16(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "USUB16", settings);
}


/**
 * USUB8{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand
 */
std::string generators::arm::math::USUB8(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "USUB8", settings);
}


/**
 * USUBADDX{<cond>} <Rd>, <Rn>, <Rm>
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined in The
 * condition field on page A3-3. If <cond> is omitted, the AL (always) condition is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand
 */
std::string generators::arm::math::USUBADDX(const u32 code, const settings& settings) {
    return patterns::sat_Rd_Rn_Rm(code, "USUBADDX", settings);
}


/**
 * UXTAB{<cond>} <Rd>, <Rn>, <Rm>{, <rotation>}
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined
 * in The condition field on page A3-3. If <cond> is omitted, the AL (always) condition
 * is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand.
 * <rotation> This can be any one of:
 * • ROR #8. This is encoded as 0b01 in the rotate field.
 * • ROR #16. This is encoded as 0b10 in the rotate field.
 * • ROR #24. This is encoded as 0b11 in the rotate field.
 * • Omitted. This is encoded as 0b00 in the rotate field.
 * Note
 * If your assembler accepts shifts by #0 and treats them as equivalent to no shift
 * or LSL #0, then it must accept ROR #0 here. It is equivalent to omitting
 * <rotation>.
 */
std::string generators::arm::math::UXTAB(const u32 code, const settings& settings) {
    return patterns::Rd_Rn_Rm_rotate(code, "UXTAB", settings);
}


/**
 * UXTAB16{<cond>} <Rd>, <Rn>, <Rm>{, <rotation>}
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined
 * in The condition field on page A3-3. If <cond> is omitted, the AL (always) condition
 * is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand.
 * <rotation> This can be any one of:
 * • ROR #8. This is encoded as 0b01 in the rotate field.
 * • ROR #16. This is encoded as 0b10 in the rotate field.
 * • ROR #24. This is encoded as 0b11 in the rotate field.
 * • Omitted. This is encoded as 0b00 in the rotate field.
 * Note
 * If your assembler accepts shifts by #0 and treats them as equivalent to no shift
 * or LSL #0, then it must accept ROR #0 here. It is equivalent to omitting
 * <rotation>
 */
std::string generators::arm::math::UXTAB16(const u32 code, const settings& settings) {
    return patterns::Rd_Rn_Rm_rotate(code, "UXTAB16", settings);
}


/**
 * UXTAH{<cond>} <Rd>, <Rn>, <Rm>{, <rotation>}
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined
 * in The condition field on page A3-3. If <cond> is omitted, the AL (always) condition
 * is used.
 * <Rd> Specifies the destination register.
 * <Rn> Specifies the register that contains the first operand.
 * <Rm> Specifies the register that contains the second operand.
 * <rotation> This can be any one of:
 * • ROR #8. This is encoded as 0b01 in the rotate field.
 * • ROR #16. This is encoded as 0b10 in the rotate field.
 * • ROR #24. This is encoded as 0b11 in the rotate field.
 * • Omitted. This is encoded as 0b00 in the rotate field.
 * Note
 * If your assembler accepts shifts by #0 and treats them as equivalent to no shift
 * or LSL #0, then it must accept ROR #0 here. It is equivalent to omitting
 * <rotation>
 */
std::string generators::arm::math::UXTAH(const u32 code, const settings& settings) {
    return patterns::Rd_Rn_Rm_rotate(code, "UXTAH", settings);
}


/**
 * UXTB{<cond>} <Rd>, <Rm>{, <rotation>}
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined
 * in The condition field on page A3-3. If <cond> is omitted, the AL (always) condition
 * is used.
 * <Rd> Specifies the destination register.
 * <Rm> Specifies the register that contains the operand.
 * <rotation> This can be any one of:
 * • ROR #8. This is encoded as 0b01 in the rotate field.
 * • ROR #16. This is encoded as 0b10 in the rotate field.
 * • ROR #24. This is encoded as 0b11 in the rotate field.
 * • Omitted. This is encoded as 0b00 in the rotate field.
 * Note
 * If your assembler accepts shifts by #0 and treats them as equivalent to no shift
 * or LSL #0, then it must accept ROR #0 here. It is equivalent to omitting
 * <rotation>
 */
std::string generators::arm::math::UXTB(const u32 code, const settings& settings) {
    return patterns::Rd_Rm_rotate(code, "UXTB", settings);
}


/**
 * UXTB16{<cond>} <Rd>, <Rm>{, <rotation>}
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined
 * in The condition field on page A3-3. If <cond> is omitted, the AL (always) condition
 * is used.
 * <Rd> Specifies the destination register.
 * <Rm> Specifies the register that contains the operand.
 * <rotation> This can be any one of:
 * • ROR #8. This is encoded as 0b01 in the rotate field.
 * • ROR #16. This is encoded as 0b10 in the rotate field.
 * • ROR #24. This is encoded as 0b11 in the rotate field.
 * • Omitted. This is encoded as 0b00 in the rotate field.
 * Note
 * If your assembler accepts shifts by #0 and treats them as equivalent to no shift
 * or LSL #0, then it must accept ROR #0 here. It is equivalent to omitting
 * <rotation>.
 */
std::string generators::arm::math::UXTB16(const u32 code, const settings& settings) {
    return patterns::Rd_Rm_rotate(code, "UXTB16", settings);
}


/**
 * UXTH{<cond>} <Rd>, <Rm>{, <rotation>}
 * where:
 * <cond> Is the condition under which the instruction is executed. The conditions are defined
 * in The condition field on page A3-3. If <cond> is omitted, the AL (always) condition
 * is used.
 * <Rd> Specifies the destination register.
 * <Rm> Specifies the register that contains the operand.
 * <rotation> This can be any one of:
 * • ROR #8. This is encoded as 0b01 in the rotate field.
 * • ROR #16. This is encoded as 0b10 in the rotate field.
 * • ROR #24. This is encoded as 0b11 in the rotate field.
 * • Omitted. This is encoded as 0b00 in the rotate field.
 * Note
 * If your assembler accepts shifts by #0 and treats them as equivalent to no shift
 * or LSL #0, then it must accept ROR #0 here. It is equivalent to omitting
 * <rotation>.
 */
std::string generators::arm::math::UXTH(const u32 code, const settings& settings) {
    return patterns::Rd_Rm_rotate(code, "UXTH", settings);
}