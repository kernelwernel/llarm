#include "identifiers.hpp"
#include "../instruction_id.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"


using namespace internal;


id::thumb identifiers::thumb(const thumb_code_t &code) {
    return thumb(static_cast<u16>(code.to_ulong()));
}

id::thumb identifiers::thumb(const u16 code) {
    const u8 bytecode = shared::util::bit_range(code, 13, 15);

    switch (bytecode) {
        // shift by immediate
        // add/subtract register
        // add/subtract immediate
        case 0b000: 
            switch (shared::util::bit_range(code, 11, 12)) { 
                case 0b00: return id::thumb::LSL1;
                case 0b01: return id::thumb::LSR1;
                case 0b10: return id::thumb::ASR1;
            }

            switch (shared::util::bit_range(code, 9, 12)) {
                case 0b1110: return id::thumb::ADD1;
                case 0b1100: return id::thumb::ADD3;
                case 0b1111: return id::thumb::SUB1;
                case 0b1101: return id::thumb::SUB3;
            }

            if (shared::util::bit_range(code, 6, 12) == 0b1110000) {
                return id::thumb::MOV2;
            }
            break;
   
        // add/subtract/compare/move immediate
        case 0b001:
            switch (shared::util::bit_range(code, 11, 12)) {
                case 0b10: return id::thumb::ADD2;
                case 0b01: return id::thumb::CMP1;
                case 0b00: return id::thumb::MOV1;
                case 0b11: return id::thumb::SUB2;
            }
            break;
        
        // data-processing register
        // special data processing
        // branch/exchange instruction set
        // load from literal pool
        // load/store register offset
        case 0b010:
            if (shared::util::bit_range(code, 11, 12) == 0b01) {
                return id::thumb::LDR3;
            }

            switch (shared::util::bit_range(code, 9, 12)) {
                case 0b1000: return id::thumb::STR2;
                case 0b1001: return id::thumb::STRH2;
                case 0b1010: return id::thumb::STRB2;
                case 0b1011: return id::thumb::LDRSB;
                case 0b1100: return id::thumb::LDR2;
                case 0b1101: return id::thumb::LDRH2;
                case 0b1110: return id::thumb::LDRB2;
                case 0b1111: return id::thumb::LDRSH;
            }
            
            switch (shared::util::bit_range(code, 6, 12)) {
                case 0b0000101: return id::thumb::ADC;
                case 0b0010000:
                case 0b0010001:
                case 0b0010010:
                case 0b0010011: return id::thumb::ADD4;
                case 0b0000000: return id::thumb::AND;
                case 0b0000100: return id::thumb::ASR2;
                case 0b0001110: return id::thumb::BIC;
                case 0b0011110:
                case 0b0011111: return id::thumb::BLX2;
                case 0b0011100:
                case 0b0011101: return id::thumb::BX;
                case 0b0001011: return id::thumb::CMN;
                case 0b0001010: return id::thumb::CMP2;
                case 0b0010100:
                case 0b0010101:
                case 0b0010110:
                case 0b0010111: return id::thumb::CMP3;
                case 0b0000001: return id::thumb::EOR;
                case 0b0000010: return id::thumb::LSL2;
                case 0b0000011: return id::thumb::LSR2;
                case 0b0011000:
                case 0b0011001:
                case 0b0011010:
                case 0b0011011: return id::thumb::MOV3;
                case 0b0001101: return id::thumb::MUL;
                case 0b0001111: return id::thumb::MVN;
                case 0b0001001: return id::thumb::NEG;
                case 0b0001100: return id::thumb::ORR;
                case 0b0000111: return id::thumb::ROR;
                case 0b0000110: return id::thumb::SBC;
                case 0b0001000: return id::thumb::TST;
            }
            break;
            
        // load/store word/byte immediate offset
        case 0b011:
            switch (shared::util::bit_range(code, 11, 12)) {
                case 0b00: return id::thumb::STR1;
                case 0b01: return id::thumb::LDR1;
                case 0b10: return id::thumb::STRB1;
                case 0b11: return id::thumb::LDRB1;
            }
            break;
        
        // load/store halfword immediate offset
        // load/store to/from stack
        case 0b100: 
            switch (shared::util::bit_range(code, 11, 12)) {
                case 0b00: return id::thumb::STRH1;
                case 0b01: return id::thumb::LDRH1;
                case 0b10: return id::thumb::STR3;
                case 0b11: return id::thumb::LDR4;
            }
            break;
        
        // add to SP or PC
        // misc
        case 0b101: 
            switch (shared::util::bit_range(code, 11, 12)) {
                case 0b00: return id::thumb::ADD5;
                case 0b01: return id::thumb::ADD6;
                case 0b10: {
                    const u8 tmp = shared::util::bit_range(code, 7, 10);
                    if (tmp == 0b0000) {
                        return id::thumb::ADD7;
                    } else if (tmp == 0b0001) {
                        return id::thumb::SUB4;
                    }

                    if (shared::util::bit_range(code, 9, 10) == 0b10) {
                        return id::thumb::PUSH;
                    }
                    break;
                }

                case 0b11: {
                    const u8 tmp2 = shared::util::bit_range(code, 8, 10);
                    if (tmp2 == 0b110) {
                        return id::thumb::BKPT;
                    }

                    if (tmp2 == 0b100 || tmp2 == 0b101) {
                        return id::thumb::POP;
                    }
                }
            } 
            break;
        
        // load/store multiple
        // conditional branch
        // undefined
        // software interrupt
        case 0b110:
            switch (shared::util::bit_range(code, 11, 12)) {
                case 0b00: return id::thumb::STMIA;
                case 0b01: return id::thumb::LDMIA;
                case 0b10:
                case 0b11:
                    if (shared::util::bit_range(code, 8, 12) == 0b11111) {
                        return id::thumb::SWI;
                    }

                    return id::thumb::B1;
            }
            break;

        // unconditional branch
        // BLX suffix
        // undefined
        // BL/BLX prefix
        // BL suffix
        case 0b111:
            switch (shared::util::bit_range(code, 11, 12)) {
                case 0b00: return id::thumb::B2;
                case 0b01: return id::thumb::BLX1;
                case 0b10: // TODO IDK WHAT THE FUCK THIS IS SUPPOSED TO MEAN (A7-26)
                case 0b11: return id::thumb::BL;
            }
            break;

    }

    return id::thumb::UNDEFINED;
}