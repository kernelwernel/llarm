#include "../generators.hpp"
#include "../patterns/patterns.hpp"

#include "shared/types.hpp"

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
std::string generators::arm::math::ADC(const u32 code, const settings settings) {
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
std::string generators::arm::math::ADD(const u32 code, const settings settings) {
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
std::string generators::arm::math::RSB(const u32 code, const settings settings) {
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
std::string generators::arm::math::RSC(const u32 code, const settings settings) {
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
std::string generators::arm::math::SBC(const u32 code, const settings settings) {
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
std::string generators::arm::math::SUB(const u32 code, const settings settings) {
    return patterns::S_Rd_Rn_data(code, "SUB", settings);
}

