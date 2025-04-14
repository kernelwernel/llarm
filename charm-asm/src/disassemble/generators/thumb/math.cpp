#include "../generators.hpp"
#include "../util.hpp"

#include <charm/internal/shared/types.hpp>
#include <charm/internal/shared/util.hpp>

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
std::string generators::thumb::math::ADC(const u16 code) {
    const util::reg_id Rd_id = util::identify_reg(code, 0, 2);
    const util::reg_id Rm_id = util::identify_reg(code, 3, 5);

    const std::string Rd = util::reg_to_string(Rd_id, false);
    const std::string Rm = util::reg_to_string(Rm_id, false);

    return util::make_instruction("ADC ", Rd, ", ", Rm);
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
std::string generators::thumb::math::ADD1(const u16 code) {
    const util::reg_id Rd_id = util::identify_reg(code, 0, 2);
    const util::reg_id Rn_id = util::identify_reg(code, 3, 5);

    const std::string Rd = util::reg_to_string(Rd_id, false);
    const std::string Rn = util::reg_to_string(Rn_id, false);

    const u8 immed_3 = shared::util::bit_fetcher(code, 6, 8);

    return util::make_instruction("ADD ", Rd, ", ", Rn, ", #", immed_3);
}


/**
 * ADD <Rd>, #<immed_8>
 * where:
 * <Rd> Holds the first operand for the addition, and is the destination register for the completed operation.
 * <immed_8> Specifies an 8-bit immediate value that is added to the value of <Rd>.
 *
 * reference: A7-6
 */
std::string generators::thumb::math::ADD2(const u16 code) {
    const util::reg_id Rd_id = util::identify_reg(code, 8, 10);

    const std::string Rd = util::reg_to_string(Rd_id, false);

    const u8 immed_8 = shared::util::bit_fetcher(code, 0, 7);

    return util::make_instruction("ADD ", Rd, ", #", immed_8);
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
std::string generators::thumb::math::ADD3(const u16 code) {
    const util::reg_id Rd_id = util::identify_reg(code, 0, 2);
    const util::reg_id Rn_id = util::identify_reg(code, 3, 5);
    const util::reg_id Rm_id = util::identify_reg(code, 6, 8);

    const std::string Rd = util::reg_to_string(Rd_id, false);
    const std::string Rn = util::reg_to_string(Rn_id, false);
    const std::string Rm = util::reg_to_string(Rm_id, false);

    return util::make_instruction("ADD ", Rd, ", ", Rn, ", ", Rm);
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
std::string generators::thumb::math::ADD4(const u16 code) {
    u8 Rd_bits = shared::util::bit_fetcher<u8>(code, 0, 2);
    u8 Rm_bits = shared::util::bit_fetcher<u8>(code, 3, 5);

    const bool H1 = (code & (1 << 7));
    const bool H2 = (code & (1 << 6));

    // branchless version of "if H1/H2 is true, add 8" 
    Rd_bits += (8 * H1);
    Rm_bits += (8 * H2);

    const util::reg_id Rd_id = util::identify_reg(Rd_bits);
    const util::reg_id Rm_id = util::identify_reg(Rm_bits);

    const std::string Rd = util::reg_to_string(Rd_id, false);
    const std::string Rm = util::reg_to_string(Rm_id, false);

    return util::make_instruction("ADD ", Rd, ", ", Rm);
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
std::string generators::thumb::math::ADD5(const u16 code) {
    const util::reg_id Rd_id = util::identify_reg(code, 8, 10);

    const std::string Rd = util::reg_to_string(Rd_id, false);

    const u8 immed_8 = shared::util::bit_fetcher<u8>(code, 0, 7);

    return util::make_instruction("ADD ", Rd, ", PC, #", immed_8, " * 4");
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
std::string generators::thumb::math::ADD6(const u16 code) {
    const util::reg_id Rd_id = util::identify_reg(code, 8, 10);

    const std::string Rd = util::reg_to_string(Rd_id, false);

    const u8 immed_8 = shared::util::bit_fetcher<u8>(code, 0, 7);

    return util::make_instruction("ADD ", Rd, ", SP, #", immed_8, " * 4");
}


/**
 * ADD  SP, #<immed_7> * 4
 * where:
 * SP Contains the first operand for the addition. SP is also the destination register for the operation.
 * <immed_7> Specifies the immediate value that is quadrupled and added to the value of the SP.
 *
 * reference: A7-12
 */
std::string generators::thumb::math::ADD7(const u16 code) {
    const u8 immed_7 = shared::util::bit_fetcher<u8>(code, 0, 6);

    return util::make_instruction("ADD SP, #", immed_7, " * 4");
}


/**
 * SBC  <Rd>, <Rm>
 * where: 
 * <Rd> Contains the first operand for the subtraction, and is also the destination register for the operation.
 * <Rm> Contains the value to be subtracted from <Rd>
 *
 * reference: A7-82
 */
std::string generators::thumb::math::SBC(const u16 code) {
    const util::reg_id Rd_id = util::identify_reg(code, 0, 2);
    const util::reg_id Rm_id = util::identify_reg(code, 3, 5);

    const std::string Rd = util::reg_to_string(Rd_id, false);
    const std::string Rm = util::reg_to_string(Rm_id, false);

    return util::make_instruction("SBC ", Rd, ", ", Rm);
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
std::string generators::thumb::math::SUB1(const u16 code) {
    const util::reg_id Rd_id = util::identify_reg(code, 0, 2);
    const util::reg_id Rn_id = util::identify_reg(code, 3, 5);

    const std::string Rd = util::reg_to_string(Rd_id, false);
    const std::string Rn = util::reg_to_string(Rn_id, false);

    const u8 immed_3 = shared::util::bit_fetcher<u8>(code, 6, 8);

    return util::make_instruction("SUB ", Rd, ", ", Rn, ", #", immed_3);
}


/*
 * SUB  <Rd>, #<immed_8>
 * where: 
 * <Rd> Is the register containing the first operand for the subtraction, and is also the destination register for the operation. 
 * <immed_8> Is an 8-bit immediate value (values 0 to 255) that is subtracted from <Rd>
 * 
 * reference: A7-99
 */
std::string generators::thumb::math::SUB2(const u16 code) {
    const util::reg_id Rd_id = util::identify_reg(code, 8, 10);

    const std::string Rd = util::reg_to_string(Rd_id, false);

    const u8 immed_8 = shared::util::bit_fetcher<u8>(code, 0, 7);

    return util::make_instruction("SUB ", Rd, ", #", immed_8);
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
std::string generators::thumb::math::SUB3(const u16 code) {
    const util::reg_id Rd_id = util::identify_reg(code, 0, 2);
    const util::reg_id Rn_id = util::identify_reg(code, 3, 5);
    const util::reg_id Rm_id = util::identify_reg(code, 6, 8);

    const std::string Rd = util::reg_to_string(Rd_id, false);
    const std::string Rn = util::reg_to_string(Rn_id, false);
    const std::string Rm = util::reg_to_string(Rm_id, false);

    return util::make_instruction("SUB ", Rd, ", ", Rn, ", ", Rm);
}


/*
 * SUB  SP, #<immed_7> * 4
 * where: 
 * SP Indicates the stack pointer. The result of the operation is also stored in the SP.
 * <immed_7> Is a 7-bit immediate value that is multiplied by 4 and then subtracted from the value of the stack pointer.
 * 
 * reference: A7-101
 */
std::string generators::thumb::math::SUB4(const u16 code) {
    const u8 immed_7 = shared::util::bit_fetcher<u8>(code, 0, 6);

    return util::make_instruction("SUB SP, #", immed_7, " * 4");
}


/**
 * MUL  <Rd>, <Rm>
 * where: 
 * <Rd> Contains the value to be multiplied with the value of <Rm>, and is also the destination register for the operation.
 * <Rm> Is the register containing the value to be multiplied with the value of <Rd>
 *
 * reference: A7-70 
 */
std::string generators::thumb::math::MUL(const u16 code) {
    const util::reg_id Rd_id = util::identify_reg(code, 0, 2);
    const util::reg_id Rm_id = util::identify_reg(code, 3, 5);

    const std::string Rd = util::reg_to_string(Rd_id, false);
    const std::string Rm = util::reg_to_string(Rm_id, false);

    return util::make_instruction("MUL ", Rd, ", ", Rm);
}