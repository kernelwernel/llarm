#include "types.hpp"
#include "utility.hpp"
#include "cpu/instructions.hpp"
#include "cpu/core/registers.hpp"

/*
 * Rd = immed_8
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * C Flag = unaffected
 * V Flag = unaffected
 */
void instructions::thumb::movement::MOV1(const thumbcode_t &code, REGISTERS &reg) {
    const u8 immed_8 = util::bit_fetcher<u8>(code, 0, 7);

    const id::reg Rd_id = reg.fetch_reg_id(code, 8, 10);

    reg.write(Rd_id, immed_8);

    const u32 Rd = reg.read(Rd_id);

    reg.write_cpsr(id::cpsr::N, Rd & (1 << 31));
    reg.write_cpsr(id::cpsr::Z, (Rd == 0));

    reg.thumb_increment_PC();
}


/*
 * Rd = Rn
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * C Flag = 0
 * V Flag = 0
 */
void instructions::thumb::movement::MOV2(const thumbcode_t &code, REGISTERS &reg) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);
    const u32 Rn = reg.read(code, 3, 5);

    reg.write(Rd_id, Rn);

    const u32 Rd = reg.read(Rd_id);
    
    reg.write_cpsr(id::cpsr::N, (Rd & (1 << 31)));
    reg.write_cpsr(id::cpsr::Z, (Rd == 0));
    reg.write_cpsr(id::cpsr::C, 0);
    reg.write_cpsr(id::cpsr::V, 0);

    reg.thumb_increment_PC();
}


/*
 * Rd = Rm
 */
void instructions::thumb::movement::MOV3(const thumbcode_t &code, REGISTERS &reg) {
    u8 Rd_bits = util::bit_fetcher<u8>(code, 0, 2);
    u8 Rm_bits = util::bit_fetcher<u8>(code, 3, 5);

    const bool H2 = code.test(6);
    const bool H1 = code.test(7);

    Rd_bits += (8 * H1);
    Rm_bits += (8 * H2);

    const id::reg Rd_id = reg.fetch_reg_id(Rd_bits); 
    const id::reg Rm_id = reg.fetch_reg_id(Rm_bits); 

    reg.write(Rd_id, reg.read(Rm_id));

    reg.thumb_increment_PC();
}


/*
 * Rd = NOT Rm
 * N Flag = Rd[31]
 * Z Flag = if Rd == 0 then 1 else 0
 * C Flag = unaffected
 * V Flag = unaffected
 */
void instructions::thumb::movement::MVN(const thumbcode_t &code, REGISTERS &reg) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);

    const u32 Rm = reg.read(code, 3, 5);

    reg.write(Rd_id, ~Rm);

    const u32 Rd = reg.read(Rd_id);

    reg.write_cpsr(id::cpsr::N, (Rd & (1 << 31)));
    reg.write_cpsr(id::cpsr::Z, (Rd == 0));

    reg.thumb_increment_PC();
}
