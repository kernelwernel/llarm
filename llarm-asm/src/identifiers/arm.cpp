#include "identifiers.hpp"
#include "../instruction_id.hpp"
#include "../instruction_table.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"

using namespace internal;


id::arm identifiers::misc_instructions(const u32 code) {
    const u8 second_half = shared::util::bit_range(code, 20, 24);
    const u8 first_half = shared::util::bit_range(code, 4, 7);

    switch (first_half) {
        case 0b0000:
            switch (second_half) {
                case 0b10000: 
                case 0b10100: return id::arm::MSR_REG;
                case 0b10010:
                case 0b10110: return id::arm::MRS;
            }

            return id::arm::UNDEFINED;

        case 0b0001:
            if (second_half == 0b10110) {
                return id::arm::CLZ;
            } else if (second_half == 0b10010) {
                return id::arm::BX;
            }

            return id::arm::UNDEFINED;
            

        case 0b0011:
            if (second_half == 0b10010) {
                return id::arm::BLX2;
            }

            return id::arm::UNDEFINED;

        case 0b0101:
            switch (second_half) {
                case 0b10000: return id::arm::QADD;
                case 0b10010: return id::arm::QSUB;
                case 0b10100: return id::arm::QDADD;
                case 0b10110: return id::arm::QDSUB;
            }

            return id::arm::UNDEFINED;


        case 0b0111: 
            if (second_half == 0b10010) {
                return id::arm::BKPT;
            }
            
            return id::arm::UNDEFINED;
    }
}


id::arm identifiers::arm(const u32 code) {
    if (shared::util::bit_range(code, 27, 31) == 0b11110) {
        return id::arm::UNDEFINED;
    }

    switch (shared::util::bit_range(code, 25, 27)) {
        // completed
        case 0b000:
            const bool bit_4 = shared::util::bit_fetch(code, 4);
            const bool bit_20 = shared::util::bit_fetch(code, 20);
            const bool bit_23 = shared::util::bit_fetch(code, 23);
            const bool bit_24 = shared::util::bit_fetch(code, 24);

            if (bit_4) {
                const bool bit_7 = shared::util::bit_fetch(code, 7);
    
                if (bit_7) {
                    // multiplies, extra load/stores
                } else {
                    if (bit_24 && !bit_23 && !bit_20) {
                        return misc_instructions(code);
                    } else {
                        // data processing register shift [2]
                    }
                }
            } else {
                if (bit_24 && !bit_23 && !bit_20) {
                    return misc_instructions(code);
                } else {
                    // data processing immediate shift
                    const u8 bytecode = shared::util::bit_range(code, 21, 24);

                    switch (bytecode) {
                        case 0b0000: return id::arm::AND;
                        case 0b0100: return id::arm::ADD;
                        case 0b0101: return id::arm::ADC;
                        case 0b1110: return id::arm::BIC;
                        case 0b1011: 
                            if (shared::util::bit_fetch(code, 20) == true) {
                                return id::arm::CMN;
                            }
                    }
                }
            }



            break;





        // complete
        case 0b001:
            const bool bit_20 = shared::util::bit_fetch(code, 20);
            const bool bit_21 = shared::util::bit_fetch(code, 21);
            const bool bit_23 = shared::util::bit_fetch(code, 23);
            const bool bit_24 = shared::util::bit_fetch(code, 24);

            const u8 bytecode = ((bit_24 << 3) | (bit_23 << 2) | (bit_21 << 1) | bit_20);

            if (bytecode == 0b1000) {
                return id::arm::UNDEFINED;
            } else if (bytecode == 0b1010) {
                return id::arm::MSR_IMM;
            } else {
                // data processing immediate
            }

        
        // complete
        case 0b010: // load/store immediate
        

        // complete
        case 0b011:
            if (shared::util::bit_fetch(code, 4) == true) {
                return id::arm::UNDEFINED;
            } else {
                // load/store register offset
            }
        
        // complete
        case 0b100: 
            if (shared::util::bit_range(code, 31, 28) == 0b1111) {
                return id::arm::UNDEFINED;
            } else {
                // load/store multiple
            }

            // load/store multiple
            //const bool bit_22 = shared::util::bit_fetch(code, 22);
            //const bool bit_21 = shared::util::bit_fetch(code, 21);
            //const bool bit_20 = shared::util::bit_fetch(code, 20);
            //const bool bit_15 = shared::util::bit_fetch(code, 15);
//
            //if (!bit_22 && bit_20) {
            //    return id::arm::LDM1;
            //}
//
            //if (bit_22 && !bit_21 && bit_20 && !bit_15) {
            //    return id::arm::LDM2;
            //}
//
            //if (bit_22 && bit_20 && bit_15) {
            //    return id::arm::LDM3;
            //}


        // complete
        case 0b101:
            if (shared::util::bit_range(code, 31, 28) == 0b1111) {
                // branch and branch with link and change to thumb [4]
            } else {
                // branch and branch with link
            }
        
        // complete
        case 0b110: 
            // coprocessor load/store and double register transfers [6]
        

        // complete
        case 0b111:
            if (shared::util::bit_fetch(code, 24)) {
                if (shared::util::bit_range(code, 31, 28) == 0b1111) {
                    return id::arm::UNDEFINED;
                } else {
                    // software interrupt
                }
            } else {
                if (shared::util::bit_fetch(code, 4)) {
                    // coprocessor register transfers
                } else {
                    // coprocessor data processing
                }
            }

    }
}

//id::arm arm(const std::string string_code) {}