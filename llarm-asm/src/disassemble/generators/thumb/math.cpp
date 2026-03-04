#include "../generators.hpp"
#include "../util.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>

#include <string>

using namespace internal;

/** 
 * ADC <Rd>, <Rm>
 * where:
 * <Rd> Holds the first value for the addition, and is the destination register for the operation.
 * <Rm> Specifies the register that contains the second operand for the addition.
 * 
 * reference: A7-4
 */
std::string generators::thumb::math::ADC(const u32 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rm = util::reg_string(code, 3, 5, settings);

    return util::make_string(
        "ADC ", Rd, ", ", Rm
    );
}


/**
 * ADD <Rd>, <Rn>, #<immed_3>
 * where:
 * <Rd> Is the destination register for the completed operation.
 * <Rn> Specifies the register that contains the operand for the addition.
 * <immed_3> Specifies a 3-bit immediate value that is added to the value of <Rn>.
 * 
 * reference: A7-5
 */
std::string generators::thumb::math::ADD1(const u32 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rn = util::reg_string(code, 3, 5, settings);

    const u8 immed_3 = llarm::util::bit_range<u8>(code, 6, 8);

    return util::make_string(
        "ADD ", Rd, ", ", Rn, ", #", util::hex(immed_3, settings)
    );
}


/**
 * ADD <Rd>, #<immed_8>
 * where:
 * <Rd> Holds the first operand for the addition, and is the destination register for the completed operation.
 * <immed_8> Specifies an 8-bit immediate value that is added to the value of <Rd>.
 *
 * reference: A7-6
 */
std::string generators::thumb::math::ADD2(const u32 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 8, 10, settings);

    const u8 immed_8 = llarm::util::bit_range<u8>(code, 0, 7);

    return util::make_string(
        "ADD ", Rd, ", #", util::hex(immed_8, settings)
    );
}


/**
 * ADD <Rd>, <Rn>, <Rm>
 * where:
 * <Rd> Is the destination register for the completed operation.
 * <Rn> Specifies the register containing the first value for the addition.
 * <Rm> Specifies the register containing the second value for the addition.
 *
 * reference: A7-7
 */
std::string generators::thumb::math::ADD3(const u32 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rn = util::reg_string(code, 3, 5, settings);
    const std::string Rm = util::reg_string(code, 6, 8, settings);

    return util::make_string(
        "ADD ", Rd, ", ", Rn, ", ", Rm
    );
}


/**
 * ADD <Rd>, <Rm>
 * where:
 * <Rd> Specifies the register containing the first value, and is also the destination register. It can be
 *      any of R0 to R15. The register number is encoded in the instruction in H1 (most significant bit) 
 *      and Rd (remaining three bits).
 * <Rm> Specifies the register containing the second value. It can be any of R0 to R15. Its number is
 *      encoded in the instruction in H2 (most significant bit) and Rm (remaining three bits).
 *
 * reference: A7-8
 */
std::string generators::thumb::math::ADD4(const u32 code, const settings settings) {
    const bool H1 = (llarm::util::bit_fetch(code, 7));
    const bool H2 = (llarm::util::bit_fetch(code, 6));

    const std::string Rd = util::reg_string_bits(code, 0, 2, H1, settings);
    const std::string Rm = util::reg_string_bits(code, 3, 5, H2, settings);

    return util::make_string(
        "ADD4 ", Rd, ", ", Rm
    );
}
         

/**
 * ADD  <Rd>, PC, #<immed_8> * 4
 * where:
 * <Rd> Is the destination register for the completed operation.
 * PC Indicates PC-relative addressing.
 * <immed_8> Specifies an 8-bit immediate value that is quadrupled and added to the value of the PC.
 * 
 * reference: A7-10
 */
std::string generators::thumb::math::ADD5(const u32 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 8, 10, settings);

    const u8 immed_8 = llarm::util::bit_range<u8>(code, 0, 7);

    return util::make_string(
        "ADD ", Rd, ", PC, #", util::hex(immed_8, settings), " * 4"
    );
}


/**
 * ADD  <Rd>, SP, #<immed_8> * 4
 * where:
 * <Rd> Is the destination register for the completed operation.
 * SP Indicates SP-relative addressing.
 * <immed_8> Specifies an 8-bit immediate value that is quadrupled and added to the value of the SP.
 *
 * reference: A7-11
 */
std::string generators::thumb::math::ADD6(const u32 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 8, 10, settings);

    const u8 immed_8 = llarm::util::bit_range<u8>(code, 0, 7);

    return util::make_string(
        "ADD ", Rd, ", SP, #", util::hex(immed_8, settings), " * 4"
    );
}


/**
 * ADD SP, #<immed_7> * 4
 * where:
 * SP Contains the first operand for the addition. SP is also the destination register for the operation.
 * <immed_7> Specifies the immediate value that is quadrupled and added to the value of the SP.
 *
 * reference: A7-12
 */
std::string generators::thumb::math::ADD7(const u32 code, const settings settings) {
    const u8 immed_7 = llarm::util::bit_range<u8>(code, 0, 6);

    return util::make_string(
        "ADD SP, #", util::hex(immed_7, settings), " * 4"
    );
}


/**
 * SBC  <Rd>, <Rm>
 * where: 
 * <Rd> Contains the first operand for the subtraction, and is also the destination register for the operation.
 * <Rm> Contains the value to be subtracted from <Rd>
 *
 * reference: A7-82
 */
std::string generators::thumb::math::SBC(const u32 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rm = util::reg_string(code, 3, 5, settings);

    return util::make_string(
        "SBC ", Rd, ", ", Rm
    );
}


/*
 * SUB  <Rd>, <Rn>, #<immed_3>
 * where: 
 * <Rd> Is the destination register for the operation. 
 * <Rn> Is the register containing the first operand for the subtraction.
 * <immed_3> Is a 3-bit immediate value (values 0 to 7) that is subtracted from <Rn>
 * 
 * reference: A7-98
 */
std::string generators::thumb::math::SUB1(const u32 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rn = util::reg_string(code, 3, 5, settings);

    const u8 immed_3 = llarm::util::bit_range<u8>(code, 6, 8);

    return util::make_string(
        "SUB ", Rd, ", ", Rn, ", #", util::hex(immed_3, settings)
    );
}


/*
 * SUB  <Rd>, #<immed_8>
 * where: 
 * <Rd> Is the register containing the first operand for the subtraction, and is also the destination register for the operation. 
 * <immed_8> Is an 8-bit immediate value (values 0 to 255) that is subtracted from <Rd>
 * 
 * reference: A7-99
 */
std::string generators::thumb::math::SUB2(const u32 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 8, 10, settings);

    const u8 immed_8 = llarm::util::bit_range<u8>(code, 0, 7);

    return util::make_string(
        "SUB ", Rd, ", #", util::hex(immed_8, settings)
    );
}


/*
 * SUB  <Rd>, <Rn>, <Rm>
 * where: 
 * <Rd> Is the destination register for the operation. 
 * <Rn> Is the register containing the first operand for the subtraction.
 * <Rm> Is the register whose value is subtracted from <Rn>.
 * 
 * reference: A7-100
 */
std::string generators::thumb::math::SUB3(const u32 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rn = util::reg_string(code, 3, 5, settings);
    const std::string Rm = util::reg_string(code, 6, 8, settings);

    return util::make_string(
        "SUB ", Rd, ", ", Rn, ", ", Rm
    );
}


/*
 * SUB  SP, #<immed_7> * 4
 * where: 
 * SP Indicates the stack pointer. The result of the operation is also stored in the SP.
 * <immed_7> Is a 7-bit immediate value that is multiplied by 4 and then subtracted from the value of the stack pointer.
 * 
 * reference: A7-101
 */
std::string generators::thumb::math::SUB4(const u32 code, const settings settings) {
    const u8 immed_7 = llarm::util::bit_range<u8>(code, 0, 6);

    return util::make_string(
        "SUB SP, #", util::hex(immed_7, settings), " * 4"
    );
}


/**
 * MUL  <Rd>, <Rm>
 * where: 
 * <Rd> Contains the value to be multiplied with the value of <Rm>, and is also the destination register for the operation.
 * <Rm> Is the register containing the value to be multiplied with the value of <Rd>
 *
 * reference: A7-70 
 */
std::string generators::thumb::math::MUL(const u32 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 0, 2, settings);
    const std::string Rm = util::reg_string(code, 3, 5, settings);

    return util::make_string(
        "MUL ", Rd, ", ", Rm
    );
}