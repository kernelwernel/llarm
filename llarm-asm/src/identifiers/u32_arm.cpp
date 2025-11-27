#include "u32_arm.hpp"
#include "../instruction_id.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"

using namespace internal;

id::arm ident::u32_arm::misc_instructions(const u32 code) {
    const u8 second_half = shared::util::bit_range<u8>(code, 20, 24);
    const u8 first_half = shared::util::bit_range<u8>(code, 4, 7);

    switch (first_half) {
        case 0b0000:
            switch (second_half) {
                case 0b10000: 
                case 0b10100: return id::arm::MRS; 
                case 0b10010:
                case 0b10110: return id::arm::MSR_REG;
            }
            break;

        case 0b0001:
            if (second_half == 0b10110) {
                return id::arm::CLZ;
            } else if (second_half == 0b10010) {
                return id::arm::BX;
            }
            break;
            

        case 0b0011:
            if (second_half == 0b10010) {
                return id::arm::BLX2;
            }
            break;

        case 0b0101:
            switch (second_half) {
                case 0b10000: return id::arm::QADD;
                case 0b10010: return id::arm::QSUB;
                case 0b10100: return id::arm::QDADD;
                case 0b10110: return id::arm::QDSUB;
            }
            break;


        case 0b0111: 
            if (
                (second_half == 0b10010) && 
                (shared::util::bit_range(code, 28, 31) == 0b1110)
            ) {
                return id::arm::BKPT;
            }
            break;
        
        case 0b1000:
        case 0b1010:
        case 0b1100:
        case 0b1110:
            const u16 bytecode = static_cast<u16>(shared::util::bit_range<u8>(code, 20, 27) << 4) | shared::util::bit_range<u8>(code, 4, 7);
            
            switch (bytecode) {
                case 0b000100001000:
                case 0b000100001010:
                case 0b000100001100:
                case 0b000100001110:
                    return id::arm::SMLAXY;
                
                case 0b000101001000:
                case 0b000101001010:
                case 0b000101001100:
                case 0b000101001110:
                    return id::arm::SMLALXY;
                
                case 0b000100101000:
                case 0b000100101100:
                    return id::arm::SMLAWY;
                
                case 0b000101101000:
                case 0b000101101010:
                case 0b000101101100:
                case 0b000101101110:
                    return id::arm::SMULXY;
                
                case 0b000100101010:
                case 0b000100101110:
                    return id::arm::SMULWY;
            }
    }

    return id::arm::UNDEFINED;
}





id::arm ident::u32_arm::multiply_extra_load_store(const u32 code) {
    const u8 second_half = shared::util::bit_range<u8>(code, 20, 24);
    const u8 first_half = shared::util::bit_range<u8>(code, 4, 7);

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
            break;

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
                return id::arm::LDRD;
            }

        case 0b1111:
            if (shared::util::bit_fetch(code, 20) == true) {
                return id::arm::LDRSH;
            }
    }

    return id::arm::UNDEFINED;
}

id::arm ident::u32_arm::unconditional(const u32 code) {
    if (shared::util::bit_fetch(code, 27) == false) {
        if (
            (shared::util::bit_fetch(code, 26) == 1) &&
            (shared::util::bit_fetch(code, 24) == 1) &&
            (shared::util::bit_fetch(code, 22) == 1) &&
            (shared::util::bit_fetch(code, 21) == 0) &&
            (shared::util::bit_fetch(code, 20) == 1) &&
            (shared::util::bit_range(code, 12, 15) == 0b1111)
        ) {
            return id::arm::PLD;
        } else {
            return id::arm::UNDEFINED;
        }
    }

    switch (shared::util::bit_range(code, 25, 26)) {
        case 0b01: return id::arm::BLX1;
        case 0b10: 
            if (shared::util::bit_fetch(code, 20) == 1) {
                return id::arm::LDC2;
            } else {
                return id::arm::STC2;
            }
        
        case 0b11:
            if (shared::util::bit_fetch(code, 24) == 1) {
                return id::arm::UNDEFINED;
            }

            if (shared::util::bit_fetch(code, 4) == 0) {
                return id::arm::CDP2;
            } 

            if (shared::util::bit_fetch(code, 20) == 1) {
                return id::arm::MRC2;
            } else {
                return id::arm::MCR2;
            }
    }

    return id::arm::UNDEFINED;
}

id::arm ident::u32_arm::data_processing(const u32 code) {
    switch (shared::util::bit_range(code, 21, 24)) {
        case 0b0000: return id::arm::AND; 
        case 0b0001: return id::arm::EOR;
        case 0b0010: return id::arm::SUB;
        case 0b0011: return id::arm::RSB;
        case 0b0100: return id::arm::ADD; 
        case 0b0101: return id::arm::ADC; 
        case 0b0110: return id::arm::SBC;
        case 0b0111: return id::arm::RSC;
        case 0b1000: 
            if (shared::util::bit_fetch(code, 20)) {
                return id::arm::TST;
            } else if (shared::util::bit_range(code, 12, 15) == 0b1111) {
                return id::arm::TSTP;
            }
            return id::arm::UNDEFINED;

        case 0b1001: 
            if (shared::util::bit_fetch(code, 20)) {
                return id::arm::TEQ;
            } else if (shared::util::bit_range(code, 12, 15) == 0b1111) {
                return id::arm::TEQP;
            }
            return id::arm::UNDEFINED;

        case 0b1010: 
            if (shared::util::bit_fetch(code, 20)) {
                return id::arm::CMP;
            } else if (shared::util::bit_range(code, 12, 15) == 0b1111) {
                return id::arm::CMPP;
            }
            return id::arm::UNDEFINED;
        
        case 0b1011: 
            if (shared::util::bit_fetch(code, 20)) {
                return id::arm::CMN;
            } else if (shared::util::bit_range(code, 12, 15) == 0b1111) {
                return id::arm::CMNP;
            }
            return id::arm::UNDEFINED;

        case 0b1100: return id::arm::ORR;
        case 0b1101: return id::arm::MOV; 
        case 0b1110: return id::arm::BIC;
        case 0b1111: return id::arm::MVN;
        default: return id::arm::UNDEFINED;
    }
}


id::arm ident::u32_arm::load_store(const u32 code) {
    const bool bit_22 = shared::util::bit_fetch(code, 22);
    const bool bit_20 = shared::util::bit_fetch(code, 20);

    const u8 bytecode = (static_cast<u8>(bit_22 << 1) | bit_20);

    switch (bytecode) {
        case 0b00: return id::arm::STR;
        case 0b01: return id::arm::LDR;
        case 0b10: return id::arm::STRB;
        case 0b11: return id::arm::LDRB;
    }

    const bool bit_24 = shared::util::bit_fetch(code, 24);
    const bool bit_21 = shared::util::bit_fetch(code, 21);

    const u8 bytecode2 = static_cast<u8>((bit_24 << 3) | (bit_22 << 2) | (bit_21 << 1) | bit_20);

    switch (bytecode2) {
        case 0b0010: return id::arm::STRT;
        case 0b0011: return id::arm::LDRT;
        case 0b0110: return id::arm::STRBT;
        case 0b0111: return id::arm::LDRBT;
    }

    return id::arm::UNDEFINED;
}



id::arm ident::u32_arm::vfp_single(const u32 code) {
    const bool bit_24 = shared::util::bit_fetch(code, 24);
    const bool bit_23 = shared::util::bit_fetch(code, 23);
    const bool bit_21 = shared::util::bit_fetch(code, 21);
    const bool bit_20 = shared::util::bit_fetch(code, 20);

    const u8 bytecode = static_cast<u8>(
        (bit_24 << 7) |
        (bit_23 << 6) |
        (bit_21 << 5) |
        (bit_20 << 4) |
        shared::util::bit_range<u8>(code, 4, 7)
    );

    const u8 middle_zone = shared::util::bit_range<u8>(code, 16, 19);
    switch (bytecode) {
        case 0b01111100:
            if (middle_zone == 0b0101) {
                return id::arm::FCMPEZS;
            }

            [[fallthrough]]; // no break on purpose
        case 0b01111110: 
            switch (middle_zone) {
                case 0b0100: return id::arm::FCMPES;
                case 0b0000: return id::arm::FABSS;
                case 0b1000: return id::arm::FSITOS;
                case 0b1101: return id::arm::FTOSIS;
                case 0b0001: return id::arm::FSQRTS;
                case 0b1100: return id::arm::FTOUIS;
            }
            break;
        case 0b00110000:
        case 0b00110010:
        case 0b00111000:
        case 0b00111010: return id::arm::FADDS;
        case 0b01110100:
        case 0b01110110: 
            switch (middle_zone) {
                case 0b0100: return id::arm::FCMPS;
                case 0b1000: return id::arm::FUITOS;
                case 0b0101: return id::arm::FCMPZS;
                case 0b1101: return id::arm::FTOSIS;
                case 0b0000: return id::arm::FCPYS;
                case 0b0001: return id::arm::FNEGS;
                case 0b1100: return id::arm::FTOUIS;
            }
            break;

        case 0b01000000:
        case 0b01000010:
        case 0b01001000:
        case 0b01001010:
            return id::arm::FDIVS;
        
        case 0b00000000:
        case 0b00000010:
        case 0b00001000:
        case 0b00001010:
            return id::arm::FMACS;
        
        case 0b00000100:
        case 0b00000110:
        case 0b00001100:
        case 0b00001110:
            return id::arm::FNMACS;

        case 0b00010100:
        case 0b00010110:
        case 0b00011100:
        case 0b00011110:
            return id::arm::FNMSCS;

        case 0b00100100:
        case 0b00100110:
        case 0b00101100:
        case 0b00101110:
            return id::arm::FNMULS;

        case 0b00010001:
        case 0b00011001:
            if (shared::util::bit_fetch(code, 22) == false) {
                return id::arm::FMRS;
            }
            break;
        
        case 0b01110001:
            if (shared::util::bit_fetch(code, 22) == true) {
                if (
                    (shared::util::bit_range(code, 12, 19) == 0b00011111) &&
                    (shared::util::bit_fetch(code, 4))
                ) {
                    return id::arm::FMSTAT;
                } else {
                    return id::arm::FMRX;
                }
            }
            break;
        
        case 0b00010000:
        case 0b00010010:
        case 0b00011000:
        case 0b00011010:
            return id::arm::FMSCS;
        
        case 0b00000001:
        case 0b00001001:
            if (shared::util::bit_fetch(code, 22) == true) {
                return id::arm::FMSR;
            }
            break;

        case 0b00100000:
        case 0b00100010:
        case 0b00101000:
        case 0b00101010:
            return id::arm::FMULS;

        case 0b01100001:
            if (shared::util::bit_fetch(code, 22) == true) {
                return id::arm::FMXR;
            }
            break;
    
        case 0b00110100:
        case 0b00110110:
        case 0b00111100:
        case 0b00111110:
            return id::arm::FSUBS;
    
    }

    return id::arm::UNDEFINED;
}


id::arm ident::u32_arm::vfp_double(const u32 code) {
    const u8 left = shared::util::bit_range<u8>(code, 20, 23);
    const u8 right = shared::util::bit_range<u8>(code, 4, 7);

    switch (left) {
        case 0b0000:
            if (right == 0b0000) {
                return id::arm::FMACD;
            } else if (right == 0b0001) {
                return id::arm::FMDLR;
            } else if (right == 0b0100) {
                return id::arm::FNMACD;
            }
            break;

        case 0b1000:
            if (right == 0b0000) {
                return id::arm::FDIVD;
            }
            break;
        
        case 0b0010:
            if (right == 0b0000) {
                return id::arm::FMULD;
            } else if (right == 0b0001) {
                return id::arm::FMDHR;
            } else if (right == 0b0100) {
                return id::arm::FNMULD;
            }
            break;
        
        case 0b0001:
            if (right == 0b0000) {
                return id::arm::FMSCD;
            } else if (right == 0b0001) {
                return id::arm::FMRDL;
            } else if (right == 0b0100) {
                return id::arm::FNMSCD;
            }

            [[fallthrough]]; // no break on purpose

        case 0b1001:
            if (shared::util::bit_range(code, 8, 11) == 0b1011) {
                return id::arm::FLDD;
            }
            break;

        case 0b1011: {
            const u8 middle = shared::util::bit_range<u8>(code, 16, 19);

            if (right == 0b1100) {
                switch (middle) {
                    case 0b0000: return id::arm::FABSD;
                    case 0b0001: return id::arm::FSQRTD;
                    case 0b0100: return id::arm::FCMPED;
                    case 0b0101: return id::arm::FCMPEZD;
                    case 0b0111: 
                        if (shared::util::bit_range(code, 8, 11) == 0b1011) {
                            return id::arm::FCVTSD;
                        } else if (shared::util::bit_range(code, 8, 11) == 0b1010) {
                            return id::arm::FCVTDS;
                        }
                        break;
                    case 0b1000: return id::arm::FSITOD;
                    case 0b1100: return id::arm::FTOUID;
                    case 0b1101: return id::arm::FTOSID;
                }
                break;
            }
            
            if (right == 0b1110) {
                if (middle == 0b0111) {
                    return id::arm::FCVTDS;
                } else if (middle == 0b1000) {
                    return id::arm::FSITOD;
                }
            }

            if (right == 0b0100) {
                switch (middle) {
                    case 0b0100: return id::arm::FCMPD;
                    case 0b0101: return id::arm::FCMPZD;
                    case 0b0000: return id::arm::FCPYD;
                    case 0b0001: return id::arm::FNEGD;
                    case 0b1101: return id::arm::FTOSID;
                    case 0b1100: return id::arm::FTOUID;
                    case 0b1000: return id::arm::FUITOD;
                }
                break;
            }

            if (right == 0b0110) {
                if (middle == 0b1000) {
                    return id::arm::FUITOD;
                }
            }
            break;
        }
        
        case 0b0011:
        if (right == 0b0000) {
            return id::arm::FADDD;
            } else if (right == 0b0001) {
                return id::arm::FMRDH;
            } else if (right == 0b0100) {
                return id::arm::FSUBD;
            }
            break;
        
        case 0b1111:
            const u8 middle = shared::util::bit_range<u8>(code, 16, 19);

            if (right == 0b1100) {
                if (middle == 0b0111) {
                    return id::arm::FCVTSD;
                } else if (middle == 0b1101) {
                    return id::arm::FTOSID;
                } else if (middle == 0b1100) {
                    return id::arm::FTOUID;
                }
            } else if (right == 0b0100) {
                if (middle == 0b1101) {
                    return id::arm::FTOSID;
                } else if (middle == 0b1100) {
                    return id::arm::FTOUID;
                }
            }
    }

    return id::arm::UNDEFINED;
}


id::arm ident::u32_arm::arm(const u32 code) {
    // note: NOP is not handled because it's a pseudo 
    // instruction that's unique to this project. 
    
    if (shared::util::bit_range(code, 28, 31) == 0b1111) {
        const id::arm tmp = unconditional(code);

        if (tmp != id::arm::UNDEFINED) {
            return tmp;
        }
    }

    switch (shared::util::bit_range(code, 25, 27)) {
        // completed
        case 0b000: {
            const bool bit_4 = shared::util::bit_fetch(code, 4);
            const bool bit_20 = shared::util::bit_fetch(code, 20);
            const bool bit_23 = shared::util::bit_fetch(code, 23);
            const bool bit_24 = shared::util::bit_fetch(code, 24);

            if (bit_4) {
                const bool bit_7 = shared::util::bit_fetch(code, 7);

                if (bit_7) {
                    if (!bit_20 && shared::util::bit_range(code, 4, 7) == 0b1111) {
                        return id::arm::STRD;
                    }

                    // multiplies, extra load/stores
                    return multiply_extra_load_store(code);
                } else {
                    if (bit_24 && !bit_23 && !bit_20) {
                        return misc_instructions(code);
                    } else {
                        // data processing register shift [2]
                        return data_processing(code);
                    }
                }
            } else {
                if (bit_24 && !bit_23 && !bit_20) {
                    return misc_instructions(code);
                } else {
                    // data processing immediate shift
                    return data_processing(code);
                }
            }

            break;
        }

        // complete
        case 0b001: {
            const bool bit_20 = shared::util::bit_fetch(code, 20);
            const bool bit_21 = shared::util::bit_fetch(code, 21);
            const bool bit_23 = shared::util::bit_fetch(code, 23);
            const bool bit_24 = shared::util::bit_fetch(code, 24);

            const u8 bytecode = static_cast<u8>((bit_24 << 3) | (bit_23 << 2) | (bit_21 << 1) | bit_20);

            if (bytecode == 0b1000) {
                return id::arm::UNDEFINED;
            } else if (bytecode == 0b1010) {
                return id::arm::MSR_IMM;
            }

            return data_processing(code);
        }


        // complete
        case 0b010: return load_store(code); // load/store immediate
        

        // complete
        case 0b011:
            if (shared::util::bit_fetch(code, 4) == true) {
                return id::arm::UNDEFINED;
            }

            // load/store register offset
            return load_store(code);
        
        // complete
        case 0b100: {
            if (shared::util::bit_range(code, 31, 28) == 0b1111) {
                return id::arm::UNDEFINED;
            }

            // load/store multiple

            const bool bit_22 = shared::util::bit_fetch(code, 22);
            const bool bit_20 = shared::util::bit_fetch(code, 20);
            
            if (!bit_22 && bit_20) {
                return id::arm::LDM1;
            }

            if (!bit_22 && !bit_20) {
                return id::arm::STM1;
            }

            const bool bit_21 = shared::util::bit_fetch(code, 21);
            const bool bit_15 = shared::util::bit_fetch(code, 15);

            if (bit_22 && !bit_21 && !bit_20) {
                return id::arm::STM2;
            }

            if (bit_22 && !bit_21 && bit_20 && !bit_15) {
                return id::arm::LDM2;
            }

            if (bit_22 && bit_20 && bit_15) {
                return id::arm::LDM3;
            }

            break;
        }

        // complete
        case 0b101:
            // branch and branch with link
            if (shared::util::bit_fetch(code, 24)) {
                return id::arm::BL;
            } else {
                return id::arm::B;
            }
    
        // complete
        case 0b110: {
            // coprocessor load/store and double register transfers [6]
            const u8 bytecode = shared::util::bit_range<u8>(code, 20, 24);

            if (shared::util::bit_fetch(code, 20) == 0) {
                if (bytecode == 0b00100) {
                    return id::arm::MCRR;
                } 

                const u8 middle_right_zone = shared::util::bit_range<u8>(code, 8, 11);
                if (middle_right_zone == 0b1010) {
                    if (
                        (shared::util::bit_fetch(code, 24)) &&
                        (shared::util::bit_fetch(code, 21) == 0) &&
                        (shared::util::bit_fetch(code, 20) == 0)
                    ) {
                        return id::arm::FSTS;
                    }
                    return id::arm::FSTMS;
                } else if (middle_right_zone == 0b1011) {
                    if (shared::util::bit_fetch(code, 22) == 0) {
                        if (
                            (shared::util::bit_fetch(code, 24)) &&
                            (shared::util::bit_fetch(code, 21) == 0)
                        ) {
                            return id::arm::FSTD;
                        }

                        if (code & 1) {
                            return id::arm::FSTMX;
                        } else {
                            return id::arm::FSTMD;
                        }
                    }
                }

                return id::arm::STC;
            } else {
                switch (bytecode) {
                    case 0b00101: return id::arm::MRRC;
                    case 0b10001: 
                    case 0b10101: 
                    case 0b11001: 
                    case 0b11101: 
                        if (shared::util::bit_range(code, 8, 11) == 0b1010) {
                            return id::arm::FLDS;
                        }
                }

                const u8 middle_right_zone = shared::util::bit_range<u8>(code, 8, 11);
                if (middle_right_zone == 0b1010) {
                    return id::arm::FLDMS;
                } else if (
                    (middle_right_zone == 0b1011) && 
                    (shared::util::bit_fetch(code, 22) == false)
                ) {
                    // odd offset = FLDMX
                    // even offset = FLDMD 
                    if (code & 1) {
                        return id::arm::FLDMX;
                    } else {
                        return id::arm::FLDMD;
                    }

                }

                return id::arm::LDC;
            }
        }
        

        // complete
        case 0b111: {
            if (shared::util::bit_fetch(code, 24) == 1) {
                if (shared::util::bit_range(code, 31, 28) == 0b1111) {
                    return id::arm::UNDEFINED;
                } else {
                    return id::arm::SWI;
                }
            } else {
                if (shared::util::bit_fetch(code, 4) == 1) {
                    if (shared::util::bit_fetch(code, 20) == 1) {
                        return id::arm::MRC;
                    } else {
                        return id::arm::MCR;
                    }
                } else {
                    const u8 cp_num = shared::util::bit_range<u8>(code, 8, 11);
                    if (cp_num == 0b1010) {
                        return vfp_single(code);
                    } else if (cp_num == 0b1011) {
                        return vfp_double(code);
                    }
                
                    return id::arm::CDP;
                }
            }
        }
    }

    return id::arm::UNDEFINED;
}