#include "shared/types.hpp"
#include "../../../utility.hpp"
#include "../../instructions/instructions.hpp"
#include "../../core/registers.hpp"



/**
 * Rd = immed_8
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * C Flag = unaffected
 * V Flag = unaffected
 */
void INSTRUCTIONS::thumb::movement::MOV1(const thumb_code_t &code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 8, 10);
    const u8 immed_8 = shared::util::bit_range<u8>(code, 0, 7);

    reg.write(Rd_id, immed_8);

    const u32 Rd = reg.read(Rd_id);

    reg.write(id::cpsr::N, (Rd & (1 << 31)));
    reg.write(id::cpsr::Z, (Rd == 0));

    reg.thumb_increment_PC();
}


/**
 * Rd = Rn
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * C Flag = 0
 * V Flag = 0
 */
void INSTRUCTIONS::thumb::movement::MOV2(const thumb_code_t &code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);
    const u32 Rn = reg.read(code, 3, 5);

    reg.write(Rd_id, Rn);

    const u32 Rd = reg.read(Rd_id);

    reg.write(id::cpsr::N, (Rd & (1 << 31)));
    reg.write(id::cpsr::Z, (Rd == 0));
    reg.write(id::cpsr::C, false);
    reg.write(id::cpsr::V, false);

    reg.thumb_increment_PC();
}


/**
 * Rd = Rm
 */
void INSTRUCTIONS::thumb::movement::MOV3(const thumb_code_t &code) {
    u8 Rd_id_bits = shared::util::bit_range<u8>(code, 0, 2);
    const u32 Rm = reg.read(code, 3, 6);
    const bool H1 = code.test(7);
    // const bool H2 = code.test(6); H2 isn't really needed

    Rd_id_bits += (H1 * 8);
    const id::reg Rd_id = reg.fetch_reg_id(Rd_id_bits);

    reg.write(Rd_id, Rm);

    reg.thumb_increment_PC();
}


/**
 * Rd = NOT Rm
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * C Flag = unaffected
 * V Flag = unaffected
 */
void INSTRUCTIONS::thumb::movement::MVN(const thumb_code_t &code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);
    const u32 Rm = reg.read(code, 3, 5);

    reg.write(Rd_id, ~Rm);

    const u32 Rd = reg.read(Rd_id);

    reg.write(id::cpsr::N, (Rd & (1 << 31)));
    reg.write(id::cpsr::Z, (Rd == 0));

    reg.thumb_increment_PC();
}
