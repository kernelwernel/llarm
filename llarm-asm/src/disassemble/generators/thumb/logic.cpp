#include "../generators.hpp"
#include "../util.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"

#include <string>

using namespace internal;


/** 
 * AND  <Rd>, <Rm>
 * where:
 * <Rd> Specifies the register containing the first operand, and is also the destination register.
 * <Rm> Specifies the register containing the second operand.
 * 
 * reference: A7-13
 */
std::string generators::thumb::logic::AND(const u16 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rm = util::reg_string(code, 3, 5, settings);

    return util::make_string(
        "AND ", Rd, ", ", Rm
    );
}


/** 
 * ASR  <Rd>, <Rm>, #<immed_5>
 * where:
 * <Rd> Is the destination register for the completed operation.
 * <Rm> Specifies the register that contains the value to be shifted.
 * <immed_5> Specifies the shift amount, in the range 1 to 32. Shifts by 1 to 31 are encoded directly 
 *           in immed_5. A shift by 32 is encoded as immed_5 == 0.
 * 
 * reference: A7-14
 */
std::string generators::thumb::logic::ASR1(const u16 code, const settings settings) {
    const u8 immed_5 = shared::util::bit_range<u8>(code, 6, 10);

    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rm = util::reg_string(code, 3, 5, settings);

    return util::make_string(
        "ASR ", Rd, ", ", Rm, ", #", util::hex(immed_5, settings)
    );
}


/** 
 * ASR <Rd>, <Rs>
 * where:
 * <Rd> Contains the value to be shifted, and is also the destination register for the completed operation.
 * <Rs> Specifies the register that contains the value of the shift
 * 
 * reference: A7-16
 */
std::string generators::thumb::logic::ASR2(const u16 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rs = util::reg_string(code, 3, 5, settings);

    return util::make_string(
        "ASR ", Rd, ", ", Rs
    );
}


/** 
 * BIC  <Rd>, <Rm>
 * where:
 * <Rd> Is the register containing the value to be ANDed, and is also the destination register for the completed operation.
 * <Rm> Specifies the register that contains the value whose complement is ANDed with the value in <Rd>.
 * 
 * reference: A7-22
 */
std::string generators::thumb::logic::BIC(const u16 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rm = util::reg_string(code, 3, 5, settings);

    return util::make_string(
        "BIC ", Rd, ", ", Rm
    );
}


/** 
 * EOR  <Rd>, <Rm>
 * where:
 * <Rd> Specifies the register containing the first operand, and is also the destination register.
 * <Rm> Specifies the register containing the second operand.
 * 
 * reference: A7-39
 */
std::string generators::thumb::logic::EOR(const u16 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rm = util::reg_string(code, 3, 5, settings);

    return util::make_string(
        "EOR ", Rd, ", ", Rm
    );
}


/**
 * LSL  <Rd>, <Rm>, #<immed_5>
 * where: 
 * <Rd> Is the register that stores the result of the operation.
 * <Rm> Is the register containing the value to be shifted.
 * <immed_5> Specifies the shift amount, in the range 0 to 31
 * 
 * reference: A7-59
 */
std::string generators::thumb::logic::LSL1(const u16 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rm = util::reg_string(code, 3, 5, settings);

    const u8 immed_5 = shared::util::bit_range<u8>(code, 6, 10);

    return util::make_string(
        "LSL ", Rd, ", ", Rm, ", #", util::hex(immed_5, settings)
    );
}
 
 
/**
 * LSL  <Rd>, <Rs>
 * where: 
 * <Rd> Contains the value to be shifted, and is the destination register for the result of the operation.
 * <Rs> Is the register containing the shift value. The value is held in the least significant byte
 *  
 * 
 * reference: A7-60
 */
std::string generators::thumb::logic::LSL2(const u16 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rs = util::reg_string(code, 3, 5, settings);

    return util::make_string(
        "LSL ", Rd, ", ", Rs
    );
}
 

/**
 * LSR  <Rd>, <Rm>, #<immed_5>
 * where: 
 * <Rd> Is the destination register for the operation.
 * <Rm> Is the register containing the value to be shifted.
 * <immed_5> Specifies the shift amount, in the range 1 to 32. Shifts by 1 to 31 are encoded directly 
 *           in immed_5. A shift by 32 is encoded as immed_5 == 0.
 * 
 * reference: A7-62
 */
std::string generators::thumb::logic::LSR1(const u16 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rm = util::reg_string(code, 3, 5, settings);

    const u8 immed_5 = shared::util::bit_range<u8>(code, 6, 10);

    return util::make_string(
        "LSR ", Rd, ", ", Rm, ", #", util::hex(immed_5, settings)
    );
} 
 
 
/**
 * LSR  <Rd>, <Rs>
 * where: 
 * <Rd> Contains the value to be shifted, and is the destination register for the result of the operation.
 * <Rs> Is the register containing the shift value. The value is held in the least significant byte
 *
 * reference: A7-64
 */
std::string generators::thumb::logic::LSR2(const u16 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rs = util::reg_string(code, 3, 5, settings);

    return util::make_string(
        "LSR ", Rd, ", ", Rs
    );
}
 

/**
 * NEG  <Rd>, <Rm>
 * where: 
 * <Rd> Is the destination register for the operation.
 * <Rm> Is the register containing the value that is subtracted from zero
 *
 * reference: A7-73
 */
std::string generators::thumb::logic::NEG(const u16 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rm = util::reg_string(code, 3, 5, settings);

    return util::make_string(
        "NEG ", Rd, ", ", Rm
    );
}


/**
 * ORR  <Rd>, <Rm>
 * where: 
 * <Rd> Is the destination register for the operation.
 * <Rm> Is the register containing the value that is ORed with the value of <Rd>. The operation is a 
 *      bitwise inclusive OR.
 *
 * reference: A7-74
 */
std::string generators::thumb::logic::ORR(const u16 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rm = util::reg_string(code, 3, 5, settings);

    return util::make_string(
        "ORR ", Rd, ", ", Rm
    );
}


/**
 * ROR  <Rd>, <Rs>
 * where: 
 * <Rd> Contains the value to be rotated, and is also the destination register for the operation.
 * <Rs> Is the register containing the rotation applied to the value of <Rd>. The value of the rotation 
 *      is stored in the least significant byte
 *
 * reference: A7-80
 */
std::string generators::thumb::logic::ROR(const u16 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rs = util::reg_string(code, 3, 5, settings);

    return util::make_string(
        "ROR ", Rd, ", ", Rs
    );
}


/**
 * TST  <Rn>, <Rm>
 * where: 
 * <Rn> Is the register containing the first operand for the instruction.
 * <Rm> Is the register whose value is logically ANDed with the value of <Rn>
 *
 * reference: A7-103
 */
std::string generators::thumb::logic::TST(const u16 code, const settings settings) {
    const std::string Rn = util::reg_string(code, 0, 2, settings);
    const std::string Rm = util::reg_string(code, 3, 5, settings);

    return util::make_string(
        "TST ", Rn, ", ", Rm
    );
}