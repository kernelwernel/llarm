#include "types.hpp"
#include "utility.hpp"
#include "cpu/instructions/instructions.hpp"
#include "cpu/core/registers.hpp"

            void MOV1(const thumb_code_t&, REGISTERS&);
            void MOV2(const thumb_code_t&, REGISTERS&);
            void MOV3(const thumb_code_t&, REGISTERS&);
            void MVN(const thumb_code_t&, REGISTERS&);



/**
 * Rd = immed_8
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * C Flag = unaffected
 * V Flag = unaffected
 */
void instructions::thumb::movement::MOV1(const thumb_code_t &code, REGISTERS& reg) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 8, 10);
    const u8 immed_8 = util::bit_fetcher<u8>(code, 0, 7);

    reg.write(Rd_id, immed_8);

    const u32 Rd = reg.read(Rd_id);

    reg.write_cpsr(id::cpsr::N, (Rd & (1 << 31)));
    reg.write_cpsr(id::cpsr::Z, (Rd == 0));

    reg.thumb_increment_PC();
}


/**
 * Rd = Rn
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * C Flag = 0
 * V Flag = 0
 */
void instructions::thumb::movement::MOV2(const thumb_code_t &code, REGISTERS& reg) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);
    const u32 Rn = reg.read(code, 3, 5);

    reg.write(Rd_id, Rn);

    const u32 Rd = reg.read(Rd_id);

    reg.write_cpsr(id::cpsr::N, (Rd & (1 << 31)));
    reg.write_cpsr(id::cpsr::Z, (Rd == 0));
    reg.write_cpsr(id::cpsr::C, false);
    reg.write_cpsr(id::cpsr::V, false);

    reg.thumb_increment_PC();
}


/**
 * Rd = Rm
 */
void instructions::thumb::movement::MOV3(const thumb_code_t &code, REGISTERS& reg) {
    u8 Rd_id = reg.fetch_reg_id(code, 0, 2);
    const u32 Rm = reg.read(code, 3, 6);
    const bool H1 = code.test(7);
    // const bool H2 = code.test(6); H2 isn't really needed

    Rd_id += (H1 * 8);

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
void instructions::thumb::movement::MVN(const thumb_code_t &code, REGISTERS& reg) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);
    const u32 Rm = reg.read(code, 3, 5);

    reg.write(Rd_id, ~Rm);

    const u32 Rd = reg.read(Rd_id);

    reg.write_cpsr(id::cpsr::N, (Rd & (1 << 31)));
    reg.write_cpsr(id::cpsr::Z, (Rd == 0));

    reg.thumb_increment_PC();
}
