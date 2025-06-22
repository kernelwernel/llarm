#pragma once

#include "../instruction_id.hpp"

#include "shared/types.hpp"

namespace internal::identifiers {
    id::arm misc_instructions(const u32 code);

    id::arm multiply_extra_load_store(const u32 code) {
        const u8 second_half = shared::util::bit_range(code, 20, 24);
        const u8 first_half = shared::util::bit_range(code, 4, 7);

        switch (first_half) {
            // multiplies
            case 0b1001:
                switch (second_half) {
                    case 0b00000:
                    case 0b00001: return id::arm::MUL;
                    case 0b00010:
                    case 0b00011: return id::arm::MLA;
                    // this normally wouldn't be necessary but i'm designing it for 
                    // each possible case as a contiguous condition so that the 
                    // compiler can take advantage of page table lookup optimisations
                    case 0b00100: 
                    case 0b00101:
                    case 0b00110:
                    case 0b00111: return id::arm::UNDEFINED;
                    case 0b01000:
                    case 0b01001: return id::arm::UMULL;
                    case 0b01010:
                    case 0b01011: return id::arm::UMLAL;
                    case 0b01100: 
                    case 0b01101: return id::arm::SMULL;
                    case 0b01110:
                    case 0b01111: return id::arm::SMLAL;
                    case 0b10000: return id::arm::SWP;
                    case 0b10100: return id::arm::SWPB;
                }

                return id::arm::UNDEFINED;

            // halfwords
            case 0b1011:
                if (shared::util::bit_fetch(code, 20) == true) {
                    return id::arm::LDRH;
                } else {
                    return id::arm::STRH;
                }




            case 0b1101:
                if (shared::util::bit_fetch(code, 20) == true) {
                    return id::arm::LDRSB;
                } else {
                }




            case 0b1111:
                if (shared::util::bit_fetch(code, 20) == true) {
                    return id::arm::LDRSH;
                } else {
                }
                
        }

    }

    id::arm arm(const arm_code_t &code);
    id::arm arm(const u32 code);
    id::arm arm(const std::string string_code);

    id::thumb thumb(const thumb_code_t &code);
    id::thumb thumb(const u16 code);
    id::thumb thumb(const std::string code);
}