#include "bin_thumb.hpp"

#include "../id/instruction_id.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>


using namespace internal;

thumb_id ident::bin_thumb::thumb(const u32 code) {
    const u8 bytecode = llarm::util::bit_range<u8>(code, 13, 15);

    switch (bytecode) {
        case 0b000: return bits_000(code);
        case 0b001: return bits_001(code);
        case 0b010: return bits_010(code);
        case 0b011: return bits_011(code);
        case 0b100: return bits_100(code);
        case 0b101: return bits_101(code);
        case 0b110: return bits_110(code);
        case 0b111: return bits_111(code);
    }

    return thumb_id::UNDEFINED;
}


// shift by immediate
// add/subtract register
// add/subtract immediate
thumb_id ident::bin_thumb::bits_000(const u32 code) {
    switch (llarm::util::bit_range(code, 11, 12)) { 
        case 0b00: return thumb_id::LSL1;
        case 0b01: return thumb_id::LSR1;
        case 0b10: return thumb_id::ASR1;
    }

    switch (llarm::util::bit_range(code, 9, 12)) {
        case 0b1110: return thumb_id::ADD1;
        case 0b1100: return thumb_id::ADD3;
        case 0b1111: return thumb_id::SUB1;
        case 0b1101: return thumb_id::SUB3;
    }

    if (llarm::util::bit_range(code, 6, 12) == 0b1110000) {
        return thumb_id::MOV2;
    }

    return thumb_id::UNDEFINED;
}


// add/subtract/compare/move immediate
thumb_id ident::bin_thumb::bits_001(const u32 code) {
    switch (llarm::util::bit_range(code, 11, 12)) {
        case 0b10: return thumb_id::ADD2;
        case 0b01: return thumb_id::CMP1;
        case 0b00: return thumb_id::MOV1;
        case 0b11: return thumb_id::SUB2;
    }

    return thumb_id::UNDEFINED;
}


// data-processing register
// special data processing
// branch/exchange instruction set
// load from literal pool
// load/store register offset
thumb_id ident::bin_thumb::bits_010(const u32 code) {
    if (llarm::util::bit_range(code, 11, 12) == 0b01) {
        return thumb_id::LDR3;
    }

    switch (llarm::util::bit_range(code, 9, 12)) {
        case 0b1000: return thumb_id::STR2;
        case 0b1001: return thumb_id::STRH2;
        case 0b1010: return thumb_id::STRB2;
        case 0b1011: return thumb_id::LDRSB;
        case 0b1100: return thumb_id::LDR2;
        case 0b1101: return thumb_id::LDRH2;
        case 0b1110: return thumb_id::LDRB2;
        case 0b1111: return thumb_id::LDRSH;
    }
    
    switch (llarm::util::bit_range(code, 6, 12)) {
        case 0b0000101: return thumb_id::ADC;
        case 0b0010000:
        case 0b0010001:
        case 0b0010010:
        case 0b0010011: return thumb_id::ADD4;
        case 0b0000000: return thumb_id::AND;
        case 0b0000100: return thumb_id::ASR2;
        case 0b0001110: return thumb_id::BIC;
        case 0b0011110:
        case 0b0011111: return thumb_id::BLX2;
        case 0b0011100:
        case 0b0011101: return thumb_id::BX;
        case 0b0001011: return thumb_id::CMN;
        case 0b0001010: return thumb_id::CMP2;
        case 0b0010100:
        case 0b0010101:
        case 0b0010110:
        case 0b0010111: return thumb_id::CMP3;
        case 0b0000001: return thumb_id::EOR;
        case 0b0000010: return thumb_id::LSL2;
        case 0b0000011: return thumb_id::LSR2;
        case 0b0011000:
        case 0b0011001:
        case 0b0011010:
        case 0b0011011: return thumb_id::MOV3;
        case 0b0001101: return thumb_id::MUL;
        case 0b0001111: return thumb_id::MVN;
        case 0b0001001: return thumb_id::NEG;
        case 0b0001100: return thumb_id::ORR;
        case 0b0000111: return thumb_id::ROR;
        case 0b0000110: return thumb_id::SBC;
        case 0b0001000: return thumb_id::TST;
    }

    return thumb_id::UNDEFINED;
}


// load/store word/byte immediate offset
thumb_id ident::bin_thumb::bits_011(const u32 code) {
    switch (llarm::util::bit_range(code, 11, 12)) {
        case 0b00: return thumb_id::STR1;
        case 0b01: return thumb_id::LDR1;
        case 0b10: return thumb_id::STRB1;
        case 0b11: return thumb_id::LDRB1;
    }
    
    return thumb_id::UNDEFINED;
}


// load/store halfword immediate offset
// load/store to/from stack
thumb_id ident::bin_thumb::bits_100(const u32 code) {
    switch (llarm::util::bit_range(code, 11, 12)) {
        case 0b00: return thumb_id::STRH1;
        case 0b01: return thumb_id::LDRH1;
        case 0b10: return thumb_id::STR3;
        case 0b11: return thumb_id::LDR4;
    }

    return thumb_id::UNDEFINED;
}


// add to SP or PC
// misc
thumb_id ident::bin_thumb::bits_101(const u32 code) {
    switch (llarm::util::bit_range(code, 11, 12)) {
        case 0b00: return thumb_id::ADD5;
        case 0b01: return thumb_id::ADD6;
        case 0b10: {
            const u8 tmp = llarm::util::bit_range<u8>(code, 7, 10);
            
            if (tmp == 0b0000) {
                return thumb_id::ADD7;
            }
            
            if (tmp == 0b0001) {
                return thumb_id::SUB4;
            }

            if (llarm::util::bit_range(code, 9, 10) == 0b10) {
                return thumb_id::PUSH;
            }
            break;
        }

        case 0b11: {
            const u8 tmp2 = llarm::util::bit_range<u8>(code, 8, 10);
            
            if (tmp2 == 0b110) {
                return thumb_id::BKPT;
            }

            if (tmp2 == 0b100 || tmp2 == 0b101) {
                return thumb_id::POP;
            }
        }
    }

    return thumb_id::UNDEFINED;
}


// load/store multiple
// conditional branch
// software interrupt
thumb_id ident::bin_thumb::bits_110(const u32 code) {
    switch (llarm::util::bit_range(code, 11, 12)) {
        case 0b00: return thumb_id::STMIA;
        case 0b01: return thumb_id::LDMIA;
        case 0b10:
        case 0b11:
            if (llarm::util::bit_range(code, 8, 12) == 0b11111) {
                return thumb_id::SWI;
            }

            return thumb_id::B1;
    }

    return thumb_id::UNDEFINED;
}


// unconditional branch
// BLX suffix
// BL/BLX prefix
// BL suffix
thumb_id ident::bin_thumb::bits_111(const u32 code) {
    switch (llarm::util::bit_range(code, 11, 12)) {
        case 0b00: return thumb_id::B2;
        case 0b01: return thumb_id::BLX1;
        case 0b10: return thumb_id::BL_BLX1_PREFIX;
        case 0b11: return thumb_id::BL;
    }

    return thumb_id::UNDEFINED;
}