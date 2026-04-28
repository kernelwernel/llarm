#include "bin_arm.hpp"
#include "../id/instruction_id.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>

using namespace internal;

arm_id ident::bin_arm::misc_instructions(const u32 code) {
    const u8 second_half = llarm::util::bit_range<u8>(code, 20, 24);
    const u8 first_half = llarm::util::bit_range<u8>(code, 4, 7);

    switch (first_half) {
        case 0b0000:
            switch (second_half) {
                case 0b10000: 
                case 0b10100: return arm_id::MRS; 
                case 0b10010:
                case 0b10110: return arm_id::MSR_REG;
            }
            break;

        case 0b0001:
            if (second_half == 0b10110) {
                return arm_id::CLZ;
            } else if (second_half == 0b10010) {
                return arm_id::BX;
            }
            break;
            

        case 0b0011:
            if (second_half == 0b10010) {
                return arm_id::BLX2;
            }
            break;

        case 0b0101:
            switch (second_half) {
                case 0b10000: return arm_id::QADD;
                case 0b10010: return arm_id::QSUB;
                case 0b10100: return arm_id::QDADD;
                case 0b10110: return arm_id::QDSUB;
            }
            break;


        case 0b0111: 
            if (
                (second_half == 0b10010) && 
                (llarm::util::bit_range(code, 28, 31) == 0b1110)
            ) {
                return arm_id::BKPT;
            }
            break;
        
        case 0b1000:
        case 0b1010:
        case 0b1100:
        case 0b1110:
            const u16 bytecode = static_cast<u16>(llarm::util::bit_range<u8>(code, 20, 27) << 4) | llarm::util::bit_range<u8>(code, 4, 7);
            
            switch (bytecode) {
                case 0b000100001000:
                case 0b000100001010:
                case 0b000100001100:
                case 0b000100001110:
                    return arm_id::SMLAXY;
                
                case 0b000101001000:
                case 0b000101001010:
                case 0b000101001100:
                case 0b000101001110:
                    return arm_id::SMLALXY;
                
                case 0b000100101000:
                case 0b000100101100:
                    return arm_id::SMLAWY;
                
                case 0b000101101000:
                case 0b000101101010:
                case 0b000101101100:
                case 0b000101101110:
                    return arm_id::SMULXY;
                
                case 0b000100101010:
                case 0b000100101110:
                    return arm_id::SMULWY;
            }
    }

    return arm_id::UNDEFINED;
}





arm_id ident::bin_arm::multiply_extra_load_store(const u32 code) {
    const u8 first_half = llarm::util::bit_range<u8>(code, 4, 7);
    
    // edgecase, handled differently 
    if (
        (llarm::util::bit_fetch(code, 20) == false) && 
        (first_half == 0b1111)
    ) {
        return arm_id::STRD;
    }

    const u8 second_half = llarm::util::bit_range<u8>(code, 20, 24);
    
    switch (first_half) {
        // multiplies and exclusive memory access
        case 0b1001:
            switch (second_half) {
                case 0b00000:
                case 0b00001: return arm_id::MUL;
                case 0b00010:
                case 0b00011: return arm_id::MLA;
                case 0b00100: return arm_id::UMAAL;
                // this normally wouldn't be necessary but i'm designing it for 
                // each possible case as a contiguous condition so that the 
                // compiler can take advantage of optimisations (i think)
                case 0b00101:
                case 0b00110:
                case 0b00111: return arm_id::UNDEFINED;
                case 0b01000:
                case 0b01001: return arm_id::UMULL;
                case 0b01010:
                case 0b01011: return arm_id::UMLAL;
                case 0b01100: 
                case 0b01101: return arm_id::SMULL;
                case 0b01110:
                case 0b01111: return arm_id::SMLAL;
                case 0b10000: return arm_id::SWP;
                case 0b10100: return arm_id::SWPB;
                case 0b11001: return arm_id::LDREX;
                case 0b11000: return arm_id::STREX;
            }
            break;

        // halfwords
        case 0b1011:
            if (llarm::util::bit_fetch(code, 20) == true) {
                return arm_id::LDRH;
            } else {
                return arm_id::STRH;
            }

        case 0b1101:
            if (llarm::util::bit_fetch(code, 20) == true) {
                return arm_id::LDRSB;
            } else {
                return arm_id::LDRD;
            }

        case 0b1111:
            if (llarm::util::bit_fetch(code, 20) == true) {
                return arm_id::LDRSH;
            }
    }

    return arm_id::UNDEFINED;
}

arm_id ident::bin_arm::unconditional(const u32 code) {
    if (llarm::util::bit_fetch(code, 27) == false) {
        if (
            (llarm::util::bit_fetch(code, 26) == 1) &&
            (llarm::util::bit_fetch(code, 24) == 1) &&
            (llarm::util::bit_fetch(code, 22) == 1) &&
            (llarm::util::bit_fetch(code, 21) == 0) &&
            (llarm::util::bit_fetch(code, 20) == 1) &&
            (llarm::util::bit_range(code, 12, 15) == 0b1111)
        ) {
            return arm_id::PLD;
        }

        if (
            (llarm::util::bit_range(code, 20, 26) == 0010000) &&
            (llarm::util::bit_fetch(code, 16) == 0) &&
            (llarm::util::bit_fetch(code, 5) == 0)
        ) {
            return arm_id::CPS;
        }

        if (
            (llarm::util::bit_range(code, 16, 27) == 0b0001'0000'0001) &&
            (llarm::util::bit_range(code, 4, 7) == 0b0000)
        ) {

        }

        return arm_id::UNDEFINED;
    }

    switch (llarm::util::bit_range(code, 25, 26)) {
        case 0b00:
            if (
                (llarm::util::bit_fetch(code, 22) == false) &&
                (llarm::util::bit_fetch(code, 20) == true) &&
                (llarm::util::bit_range(code, 8, 11) == 0b1010)
            ) {
                return arm_id::RFE;
            }

            if (
                (llarm::util::bit_fetch(code, 22) == true) &&
                (llarm::util::bit_range(code, 8, 11) == 0b0101) &&
                (llarm::util::bit_range(code, 16, 20) == 0b01101)
            ) {
                return arm_id::SRS;
            }            

            return arm_id::UNDEFINED;

        case 0b01: return arm_id::BLX1;
        case 0b10: 
            if (llarm::util::bit_fetch(code, 20) == 1) {
                return arm_id::LDC2;
            } else {
                return arm_id::STC2;
            }
        
        case 0b11:
            if (llarm::util::bit_fetch(code, 24) == 1) {
                return arm_id::UNDEFINED;
            }

            if (llarm::util::bit_fetch(code, 4) == 0) {
                return arm_id::CDP2;
            } 

            if (llarm::util::bit_fetch(code, 20) == 1) {
                return arm_id::MRC2;
            }

            return arm_id::MCR2;
    }

    return arm_id::UNDEFINED;
}

arm_id ident::bin_arm::data_processing(const u32 code) {
    switch (llarm::util::bit_range(code, 21, 24)) {
        case 0b0000: return arm_id::AND; 
        case 0b0001: return arm_id::EOR;
        case 0b0010: return arm_id::SUB;
        case 0b0011: return arm_id::RSB;
        case 0b0100: return arm_id::ADD; 
        case 0b0101: return arm_id::ADC; 
        case 0b0110: return arm_id::SBC;
        case 0b0111: return arm_id::RSC;
        case 0b1000: 
            if (llarm::util::bit_fetch(code, 20)) {
                return arm_id::TST;
            } else if (llarm::util::bit_range(code, 12, 15) == 0b1111) {
                return arm_id::TSTP;
            }
            return arm_id::UNDEFINED;

        case 0b1001: 
            if (llarm::util::bit_fetch(code, 20)) {
                return arm_id::TEQ;
            } else if (llarm::util::bit_range(code, 12, 15) == 0b1111) {
                return arm_id::TEQP;
            }
            return arm_id::UNDEFINED;

        case 0b1010: 
            if (llarm::util::bit_fetch(code, 20)) {
                return arm_id::CMP;
            } else if (llarm::util::bit_range(code, 12, 15) == 0b1111) {
                return arm_id::CMPP;
            }
            return arm_id::UNDEFINED;
        
        case 0b1011: 
            if (llarm::util::bit_fetch(code, 20)) {
                return arm_id::CMN;
            } else if (llarm::util::bit_range(code, 12, 15) == 0b1111) {
                return arm_id::CMNP;
            }
            return arm_id::UNDEFINED;

        case 0b1100: return arm_id::ORR;
        case 0b1101: return arm_id::MOV; 
        case 0b1110: return arm_id::BIC;
        case 0b1111: return arm_id::MVN;
        default: return arm_id::UNDEFINED;
    }
}


arm_id ident::bin_arm::load_store(const u32 code) {
    const bool bit_22 = llarm::util::bit_fetch(code, 22);
    const bool bit_20 = llarm::util::bit_fetch(code, 20);

    const u8 bytecode = (static_cast<u8>(bit_22 << 1) | bit_20);

    switch (bytecode) {
        case 0b00: return arm_id::STR;
        case 0b01: return arm_id::LDR;
        case 0b10: return arm_id::STRB;
        case 0b11: return arm_id::LDRB;
    }

    const bool bit_24 = llarm::util::bit_fetch(code, 24);
    const bool bit_21 = llarm::util::bit_fetch(code, 21);

    const u8 bytecode2 = static_cast<u8>((bit_24 << 3) | (bit_22 << 2) | (bit_21 << 1) | bit_20);

    switch (bytecode2) {
        case 0b0010: return arm_id::STRT;
        case 0b0011: return arm_id::LDRT;
        case 0b0110: return arm_id::STRBT;
        case 0b0111: return arm_id::LDRBT;
    }

    return arm_id::UNDEFINED;
}



arm_id ident::bin_arm::vfp_single(const u32 code) {
    const bool bit_24 = llarm::util::bit_fetch(code, 24);
    const bool bit_23 = llarm::util::bit_fetch(code, 23);
    const bool bit_21 = llarm::util::bit_fetch(code, 21);
    const bool bit_20 = llarm::util::bit_fetch(code, 20);

    const u8 bytecode = static_cast<u8>(
        (bit_24 << 7) |
        (bit_23 << 6) |
        (bit_21 << 5) |
        (bit_20 << 4) |
        llarm::util::bit_range<u8>(code, 4, 7)
    );

    const u8 middle_zone = llarm::util::bit_range<u8>(code, 16, 19);
    switch (bytecode) {
        case 0b01111100:
            if (middle_zone == 0b0101) {
                return arm_id::FCMPEZS;
            }

            [[fallthrough]]; // no break on purpose
        case 0b01111110: 
            switch (middle_zone) {
                case 0b0100: return arm_id::FCMPES;
                case 0b0000: return arm_id::FABSS;
                case 0b1000: return arm_id::FSITOS;
                case 0b1101: return arm_id::FTOSIS;
                case 0b0001: return arm_id::FSQRTS;
                case 0b1100: return arm_id::FTOUIS;
            }
            break;
        case 0b00110000:
        case 0b00110010:
        case 0b00111000:
        case 0b00111010: return arm_id::FADDS;
        case 0b01110100:
        case 0b01110110: 
            switch (middle_zone) {
                case 0b0100: return arm_id::FCMPS;
                case 0b1000: return arm_id::FUITOS;
                case 0b0101: return arm_id::FCMPZS;
                case 0b1101: return arm_id::FTOSIS;
                case 0b0000: return arm_id::FCPYS;
                case 0b0001: return arm_id::FNEGS;
                case 0b1100: return arm_id::FTOUIS;
            }
            break;

        case 0b01000000:
        case 0b01000010:
        case 0b01001000:
        case 0b01001010:
            return arm_id::FDIVS;
        
        case 0b00000000:
        case 0b00000010:
        case 0b00001000:
        case 0b00001010:
            return arm_id::FMACS;
        
        case 0b00000100:
        case 0b00000110:
        case 0b00001100:
        case 0b00001110:
            return arm_id::FNMACS;

        case 0b00010100:
        case 0b00010110:
        case 0b00011100:
        case 0b00011110:
            return arm_id::FNMSCS;

        case 0b00100100:
        case 0b00100110:
        case 0b00101100:
        case 0b00101110:
            return arm_id::FNMULS;

        case 0b00010001:
        case 0b00011001:
            if (llarm::util::bit_fetch(code, 22) == false) {
                return arm_id::FMRS;
            }
            break;
        
        case 0b01110001:
            if (llarm::util::bit_fetch(code, 22) == true) {
                if (
                    (llarm::util::bit_range(code, 12, 19) == 0b00011111) &&
                    (llarm::util::bit_fetch(code, 4))
                ) {
                    return arm_id::FMSTAT;
                }

                return arm_id::FMRX;
            }
            break;
        
        case 0b00010000:
        case 0b00010010:
        case 0b00011000:
        case 0b00011010:
            return arm_id::FMSCS;
        
        case 0b00000001:
        case 0b00001001:
            if (llarm::util::bit_fetch(code, 22) == true) {
                return arm_id::FMSR;
            }
            break;

        case 0b00100000:
        case 0b00100010:
        case 0b00101000:
        case 0b00101010:
            return arm_id::FMULS;

        case 0b01100001:
            if (llarm::util::bit_fetch(code, 22) == true) {
                return arm_id::FMXR;
            }
            break;
    
        case 0b00110100:
        case 0b00110110:
        case 0b00111100:
        case 0b00111110:
            return arm_id::FSUBS;
    
    }

    return arm_id::UNDEFINED;
}


arm_id ident::bin_arm::vfp_double(const u32 code) {
    const u8 left = llarm::util::bit_range<u8>(code, 20, 23);
    const u8 right = llarm::util::bit_range<u8>(code, 4, 7);

    switch (left) {
        case 0b0000:
            if (right == 0b0000) {
                return arm_id::FMACD;
            } else if (right == 0b0001) {
                return arm_id::FMDLR;
            } else if (right == 0b0100) {
                return arm_id::FNMACD;
            }
            break;

        case 0b1000:
            if (right == 0b0000) {
                return arm_id::FDIVD;
            }
            break;
        
        case 0b0010:
            if (right == 0b0000) {
                return arm_id::FMULD;
            } else if (right == 0b0001) {
                return arm_id::FMDHR;
            } else if (right == 0b0100) {
                return arm_id::FNMULD;
            }
            break;
        
        case 0b0001:
            if (right == 0b0000) {
                return arm_id::FMSCD;
            } else if (right == 0b0001) {
                return arm_id::FMRDL;
            } else if (right == 0b0100) {
                return arm_id::FNMSCD;
            }

            [[fallthrough]]; // no break on purpose

        case 0b1001:
            if (llarm::util::bit_range(code, 8, 11) == 0b1011) {
                return arm_id::FLDD;
            }
            break;

        case 0b1011: {
            const u8 middle = llarm::util::bit_range<u8>(code, 16, 19);

            if (right == 0b1100) {
                switch (middle) {
                    case 0b0000: return arm_id::FABSD;
                    case 0b0001: return arm_id::FSQRTD;
                    case 0b0100: return arm_id::FCMPED;
                    case 0b0101: return arm_id::FCMPEZD;
                    case 0b0111: 
                        if (llarm::util::bit_range(code, 8, 11) == 0b1011) {
                            return arm_id::FCVTSD;
                        } else if (llarm::util::bit_range(code, 8, 11) == 0b1010) {
                            return arm_id::FCVTDS;
                        }
                        break;
                    case 0b1000: return arm_id::FSITOD;
                    case 0b1100: return arm_id::FTOUID;
                    case 0b1101: return arm_id::FTOSID;
                }
                break;
            }
            
            if (right == 0b1110) {
                if (middle == 0b0111) {
                    return arm_id::FCVTDS;
                }
                
                if (middle == 0b1000) {
                    return arm_id::FSITOD;
                }
            }

            if (right == 0b0100) {
                switch (middle) {
                    case 0b0100: return arm_id::FCMPD;
                    case 0b0101: return arm_id::FCMPZD;
                    case 0b0000: return arm_id::FCPYD;
                    case 0b0001: return arm_id::FNEGD;
                    case 0b1101: return arm_id::FTOSID;
                    case 0b1100: return arm_id::FTOUID;
                    case 0b1000: return arm_id::FUITOD;
                }
                break;
            }

            if (right == 0b0110) {
                if (middle == 0b1000) {
                    return arm_id::FUITOD;
                }
            }
            break;
        }
        
        case 0b0011:
        if (right == 0b0000) {
            return arm_id::FADDD;
            } else if (right == 0b0001) {
                return arm_id::FMRDH;
            } else if (right == 0b0100) {
                return arm_id::FSUBD;
            }
            break;
        
        case 0b1111:
            const u8 middle = llarm::util::bit_range<u8>(code, 16, 19);

            if (right == 0b1100) {
                if (middle == 0b0111) {
                    return arm_id::FCVTSD;
                }
                
                if (middle == 0b1101) {
                    return arm_id::FTOSID;
                }
                
                if (middle == 0b1100) {
                    return arm_id::FTOUID;
                }
            } else if (right == 0b0100) {
                if (middle == 0b1101) {
                    return arm_id::FTOSID;
                }
                
                if (middle == 0b1100) {
                    return arm_id::FTOUID;
                }
            }
    }

    return arm_id::UNDEFINED;
}


arm_id ident::bin_arm::pack_and_saturates(const u32 code) {
    {
        const u8 small_upper_part = llarm::util::bit_range<u8>(code, 21, 24);
        const u8 small_lower_part = llarm::util::bit_range<u8>(code, 5, 6);

        if ((small_upper_part == 0b0101) && (small_lower_part == 0b01)) {
            return arm_id::SSAT;
        }

        if ((small_upper_part == 0b0111) && (small_lower_part == 0b01)) {
            return arm_id::USAT;
        }
    }

    const u8 upper_part = llarm::util::bit_range<u8>(code, 20, 24);
    const u8 lower_part = llarm::util::bit_range<u8>(code, 4, 7);

    const u16 full_snippet = static_cast<u16>(upper_part << 5 | lower_part);

    switch (full_snippet) {
        case 0b0'1000'1001:
        case 0b0'1000'0001: return arm_id::PKHBT;
        case 0b0'1000'1101:
        case 0b0'1000'0101: return arm_id::PKHTB;
        case 0b0'1000'1011: return arm_id::SEL;


        case 0b0'0010'0001: return arm_id::QADD16;
        case 0b0'0010'1001: return arm_id::QADD8;
        case 0b0'0010'0011: return arm_id::QADD8;
        case 0b0'0010'0111: return arm_id::QSUB16;
        case 0b0'0010'1111: return arm_id::QSUB8;
        case 0b0'0010'0101: return arm_id::QSUBADDX;

        case 0b0'1011'0011: return arm_id::REV;
        case 0b0'1011'1011: return arm_id::REV16;
        case 0b0'1011'0111: 
            if (llarm::util::bit_range(code, 16, 19) == 0b1111) {
                return arm_id::SXTH;
            }

            return arm_id::SXTAH;

        case 0b0'1010'0011: return arm_id::SSAT16;
        case 0b0'1010'0111: 
            if (llarm::util::bit_range(code, 16, 19) == 0b1111) {
                return arm_id::SXTB;
            }

            return arm_id::SXTAB;

        case 0b0'1000'0111: 
            if (llarm::util::bit_range(code, 16, 19) == 0b1111) {
                return arm_id::SXTB16;
            }

            return arm_id::SXTAB16;

        case 0b0'0101'0011: return arm_id::UADDSUBX;
        case 0b0'0101'0001: return arm_id::UADD16;
        case 0b0'0101'1001: return arm_id::UADD8;
        case 0b0'0101'0111: return arm_id::USUB16;
        case 0b0'0101'1111: return arm_id::USUB8;
        case 0b0'0101'0101: return arm_id::USUBADDX;

        case 0b0'0110'0001: return arm_id::UQADD16;
        case 0b0'0110'1001: return arm_id::UQADD8;

        case 0b0'1111'1011: return arm_id::REVSH;
        case 0b0'0001'0001: return arm_id::SADD16;
        case 0b0'0001'1001: return arm_id::SADD8;
        case 0b0'0001'0011: return arm_id::SADDSUBX;

        case 0b0'0001'0111: return arm_id::SSUB16;
        case 0b0'0001'1111: return arm_id::SSUB8;
        case 0b0'0001'0101: return arm_id::SSUBADDX;

        case 0b0'0110'0011: return arm_id::UQADDSUBX;
        case 0b0'0110'0111: return arm_id::UQSUB16;
        case 0b0'0110'1111: return arm_id::UQSUB8;
        case 0b0'0110'0101: return arm_id::UQSUBADDX;

        case 0b0'1110'0011: return arm_id::USAT16;
        case 0b0'1110'0111: 
            if (llarm::util::bit_range(code, 16, 19) == 0b1111) {
                return arm_id::UXTB;
            }

            return arm_id::UXTAB;

        case 0b0'1100'0111: 
            if (llarm::util::bit_range(code, 16, 19) == 0b1111) {
                return arm_id::UXTB16;
            }

            return arm_id::UXTAB16;

        case 0b0'0011'0001: return arm_id::SHADD16;
        case 0b0'0011'1011: return arm_id::SHADD8;
        case 0b0'0011'0011: return arm_id::SHADDSUBX;
        case 0b0'0011'0111: return arm_id::SHSUB16;
        case 0b0'0011'1111: return arm_id::SHSUB8;
        case 0b0'0011'0101: return arm_id::SHSUBADDX;

        case 0b0'0111'0001: return arm_id::UHADD16;
        case 0b0'0111'1001: return arm_id::UHADD8;
        case 0b0'0111'0011: return arm_id::UHADDSUBX;
        case 0b0'0111'0111: return arm_id::UHSUB16;
        case 0b0'0111'1111: return arm_id::UHSUB8;
        case 0b0'0111'0101: return arm_id::UHSUBADDX;

        case 0b0'1111'0111: 
            if (llarm::util::bit_range(code, 16, 19) == 0b1111) {
                return arm_id::UXTH;
            }

            return arm_id::UXTAH;

        case 0b1'0000'0001:
        case 0b1'0000'0011: 
            if (llarm::util::bit_range(code, 12, 15) == 0b1111) {
                return arm_id::SMUAD;
            }

            return arm_id::SMLAD;

        case 0b1'0100'0001:
        case 0b1'0100'0011: return arm_id::SMLALD;
        case 0b1'0000'0101:
        case 0b1'0000'0111: return arm_id::SMLSD;

        case 0b1'0100'0101:
        case 0b1'0100'0111: 
            if (llarm::util::bit_range(code, 12, 15) == 0b1111) {
                return arm_id::SMUSD;
            }

            return arm_id::SMLSLD;

        case 0b1'0101'0001:
        case 0b1'0101'0011: 
            if (llarm::util::bit_range(code, 12, 15) == 0b1111) {
                return arm_id::SMMUL;
            }

            return arm_id::SMMLA;

        case 0b1'0101'1101:
        case 0b1'0101'1111: return arm_id::SMMLS;

        case 0b1'1000'0001: 
            if (llarm::util::bit_range(code, 12, 15) == 0b1111) {
                return arm_id::USAD8;
            }

            return arm_id::USADA8;
    }

    return arm_id::UNDEFINED;
}


arm_id ident::bin_arm::coproc_and_floats(const u32 code) {
    // coprocessor load/store and double register transfers [6]
    const u8 bytecode = llarm::util::bit_range<u8>(code, 20, 24);

    if (llarm::util::bit_fetch(code, 20) == 0) {
        if (bytecode == 0b00100) {

            if (llarm::util::bit_range(code, 28, 31) == 0b1111) {
                return arm_id::MCRR2;
            }

            return arm_id::MCRR;
        }

        const u8 middle_right_zone = llarm::util::bit_range<u8>(code, 8, 11);

        if (middle_right_zone == 0b1010) {
            if (
                (llarm::util::bit_fetch(code, 24)) &&
                (llarm::util::bit_fetch(code, 21) == 0) &&
                (llarm::util::bit_fetch(code, 20) == 0)
            ) {
                return arm_id::FSTS;
            }

            return arm_id::FSTMS;
        }
        
        if (middle_right_zone == 0b1011) {
            if (llarm::util::bit_fetch(code, 22) == 0) {
                if (
                    (llarm::util::bit_fetch(code, 24)) &&
                    (llarm::util::bit_fetch(code, 21) == 0)
                ) {
                    return arm_id::FSTD;
                }

                if (code & 1) {
                    return arm_id::FSTMX;
                }

                return arm_id::FSTMD;
            }
        }

        return arm_id::STC;
    }

    switch (bytecode) {
        case 0b00101: 
            if (llarm::util::bit_range(code, 28, 31) == 0b1111) {
                return arm_id::MRRC2;
            }

            return arm_id::MRRC;

        case 0b10001: 
        case 0b10101: 
        case 0b11001: 
        case 0b11101: 
            if (llarm::util::bit_range(code, 8, 11) == 0b1010) {
                return arm_id::FLDS;
            }
    }

    const u8 middle_right_zone = llarm::util::bit_range<u8>(code, 8, 11);
    if (middle_right_zone == 0b1010) {
        return arm_id::FLDMS;
    }
    
    if (
        (middle_right_zone == 0b1011) && 
        (llarm::util::bit_fetch(code, 22) == false)
    ) {
        // odd offset = FLDMX
        // even offset = FLDMD 
        if (code & 1) {
            return arm_id::FLDMX;
        }

        return arm_id::FLDMD;
    }

    return arm_id::LDC;
}


arm_id ident::bin_arm::arm(const u32 code) {
    // note: NOP is not handled because it's a pseudo 
    // instruction that's unique to this project. 
    
    if (llarm::util::bit_range(code, 28, 31) == 0b1111) {
        const arm_id tmp = unconditional(code);

        if (tmp != arm_id::UNDEFINED) {
            return tmp;
        }
    }

    switch (llarm::util::bit_range(code, 25, 27)) {
        // completed
        case 0b000: {
            const bool bit_4 = llarm::util::bit_fetch(code, 4);
            const bool bit_20 = llarm::util::bit_fetch(code, 20);
            const bool bit_23 = llarm::util::bit_fetch(code, 23);
            const bool bit_24 = llarm::util::bit_fetch(code, 24);

            if (bit_4) {
                const bool bit_7 = llarm::util::bit_fetch(code, 7);

                if (bit_7) {
                    // multiplies, extra load/stores
                    return multiply_extra_load_store(code);
                }

                if (bit_24 && !bit_23 && !bit_20) {
                    return misc_instructions(code);
                }

                // data processing register shift [2]
                return data_processing(code);
            }

            if (bit_24 && !bit_23 && !bit_20) {
                return misc_instructions(code);
            }

            if (
                (llarm::util::bit_range(code, 20, 27) == 0b00011010) &&
                (llarm::util::bit_range(code, 4, 11) == 0)
            ) {
                return arm_id::CPY;
            }

            // data processing immediate shift
            return data_processing(code);
        }

        // complete
        case 0b001: {
            const bool bit_20 = llarm::util::bit_fetch(code, 20);
            const bool bit_21 = llarm::util::bit_fetch(code, 21);
            const bool bit_23 = llarm::util::bit_fetch(code, 23);
            const bool bit_24 = llarm::util::bit_fetch(code, 24);

            const u8 bytecode = static_cast<u8>((bit_24 << 3) | (bit_23 << 2) | (bit_21 << 1) | bit_20);

            if (bytecode == 0b1000) {
                return arm_id::UNDEFINED;
            }
            
            if (bytecode == 0b1010) {
                return arm_id::MSR_IMM;
            }

            return data_processing(code);
        }


        // complete
        case 0b010: return load_store(code); // load/store immediate
        

        // complete
        case 0b011:
            if (llarm::util::bit_fetch(code, 4) == true) {
                return pack_and_saturates(code);
            }

            // load/store register offset
            return load_store(code);
        
        // complete
        case 0b100: {
            if (llarm::util::bit_range(code, 31, 28) == 0b1111) {
                return arm_id::UNDEFINED;
            }

            // load/store multiple

            const bool bit_22 = llarm::util::bit_fetch(code, 22);
            const bool bit_20 = llarm::util::bit_fetch(code, 20);
            
            if (!bit_22 && bit_20) {
                return arm_id::LDM1;
            }

            if (!bit_22 && !bit_20) {
                return arm_id::STM1;
            }

            const bool bit_21 = llarm::util::bit_fetch(code, 21);
            const bool bit_15 = llarm::util::bit_fetch(code, 15);

            if (bit_22 && !bit_21 && !bit_20) {
                return arm_id::STM2;
            }

            if (bit_22 && !bit_21 && bit_20 && !bit_15) {
                return arm_id::LDM2;
            }

            if (bit_22 && bit_20 && bit_15) {
                return arm_id::LDM3;
            }

            break;
        }

        // complete
        case 0b101:
            // branch and branch with link
            if (llarm::util::bit_fetch(code, 24)) {
                return arm_id::BL;
            } else {
                return arm_id::B;
            }
    
        // complete
        case 0b110: return coproc_and_floats(code);
        

        // complete
        case 0b111: {
            if (llarm::util::bit_fetch(code, 24) == 1) {
                if (llarm::util::bit_range(code, 31, 28) == 0b1111) {
                    return arm_id::UNDEFINED;
                }

                return arm_id::SWI;
            }

            if (llarm::util::bit_fetch(code, 4) == 1) {
                if (llarm::util::bit_fetch(code, 20) == 1) {
                    return arm_id::MRC;
                }

                return arm_id::MCR;
            }

            const u8 cp_num = llarm::util::bit_range<u8>(code, 8, 11);
            
            if (cp_num == 0b1010) {
                return vfp_single(code);
            }
            
            if (cp_num == 0b1011) {
                return vfp_double(code);
            }
        
            return arm_id::CDP;
        }
    }

    return arm_id::UNDEFINED;
}