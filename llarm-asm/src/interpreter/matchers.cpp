#include "matchers.hpp"
#include "tokens.hpp"

#include "shared/string_view.hpp"
#include "shared/util.hpp"

#include <cctype>

REG matchers::reg(sv str) {
    REG reg = {
        reg_type::UNKNOWN, // type
        WILDCARD,  // number
        false, // is_thumb_supported
        false, // is_malformed
        true // is_invalid
    };

    if (str.size() < 2) {
        return reg;
    }

    // check for register aliasing, for example PC = R15
    constexpr u16 PC = ('P' << 8) | 'C';
    constexpr u16 LR = ('L' << 8) | 'R';
    constexpr u16 SP = ('S' << 8) | 'P';

    // not sure if these 2 are even officially used, but i'll add them anyway
    constexpr u16 IP = ('I' << 8) | 'P';
    constexpr u16 FP = ('F' << 8) | 'P';

    const u16 key = str.at(0) << 8 | str.at(1);

    switch (key) {
        case PC: reg.number = 15; break;
        case LR: reg.number = 14; break;
        case SP: reg.number = 13; break;
        case IP: reg.number = 12; break;
        case FP: reg.number = 11; break;
    }

    const bool valid_register_found = (reg.number != WILDCARD);

    if (valid_register_found) {
        reg.type = reg_type::REGULAR;
        reg.is_invalid = false;
        return reg;
    } 

    // register format: <prefix>0~31 (i.e. R13, S28)
    // keep note that only VFP single regs have 0~31
    // range, otherwise it's 0~15. This section also
    // checks for special VFP regs like FPSCR

    switch (str.front()) {
        case 'R': reg.type = reg_type::REGULAR; break; // regular register
        case 'D': reg.type = reg_type::SINGLE; break; // VFP double register
        case 'S': reg.type = reg_type::DOUBLE; break; // VFP single register
        case 'P': reg.type = reg_type::COPROC; break; // coprocessor num
        case 'C': reg.type = reg_type::CR; break; // CRn/CRm register
        case 'F': { // special VFP register
            if (str == "FPSID") {
                reg.type = reg_type::FPSID;
            } else if (str == "FPSCR") {
                reg.type = reg_type::FPSCR;
            } else if (str == "FPEXC") {
                reg.type = reg_type::FPEXC;
            }

            if (reg.type != reg_type::UNKNOWN) {
                reg.number = WILDCARD;
                reg.is_invalid = false;
                return reg;
            }

            reg.is_invalid = false;
            return reg;
        }
        default: break;
    }

    str.remove_prefix(1);

    for (const char c : str) {
        if (std::isdigit(c) == false) {
            reg.is_invalid = true;
            return reg;
        }
    }

    const u32 raw_num = llarm::util::str_to_u32(str);
    
    const u8 limit = (reg.type == reg_type::SINGLE ? 31 : 15);
    
    const bool is_malformed = (raw_num > limit);

    if (is_malformed == false) {
        reg.number = static_cast<u8>(raw_num);
    }

    const bool is_thumb_supported = (reg.number < 8);

    constexpr bool is_invalid = false;

    return reg;
}


PSR matchers::cpsr_spsr(const sv str) {
    PSR psr = {
        0 // flags
    };

    if (str.starts_with("CPSR")) {
        psr.set_cpsr();
    } else if (str.starts_with("SPSR")) {
        psr.set_spsr();
    } else {
        psr.set_invalid();
        return psr;
    }

    if (str.size() == 4) {
        return psr;
    }

    // after this point, it's assumed field arguments
    // are being used, which looks like CPSR_<cxsf>

    // CPSR/SPSR must have 1 to 4 valid fields:
    // "CPSR":4 + "_":1 + "c/x/s/f":1~4 = 6~9
    if (str.size() < 6 || str.size() > 9) {
        psr.set_malformed();
        return psr;
    }

    if (str.at(4) != '_') {
        psr.set_malformed();
        return psr;
    }

    const sv fields = str.substr(5);
    
    u8 sum = 0;

    for (u8 i = 0; i < fields.size(); i++) {
        switch (fields.at(i)) {
            case 'C': psr.set_C(); break; 
            case 'X': psr.set_X(); break;
            case 'S': psr.set_S(); break;
            case 'F': psr.set_F(); break;
            default:
                psr.set_malformed();
                return psr;
        }
    }

    const u8 field_bitset = llarm::util::bit_range<u8>(psr.flags, (u8)PSR::C, (u8)PSR::F);
    const u8 count = llarm::util::popcount(field_bitset);

    // check for duplicates
    if (count != fields.size()) {
        psr.set_malformed();
        return psr;
    }

    return psr;
}


IMM matchers::immediate(sv str) {
    IMM imm = {
        0, /* number */
        0, /* msb */
        0, /* divisor_constraint */
        false, // has_msb_range */
        false, // is_rotateable */
        false, /* is_negative */
        false, /* is_malformed*/
        true /* is_invalid*/
    };

    // check for unnacceptable chars 
    if (str.find_first_not_of("+-X0123456789ABCDEF") == std::string::npos) {
        imm.is_invalid = true;
        return imm;
    }

    const bool is_negative = (str.front() == '-');

    if (is_negative) {
        imm.is_negative = is_negative;
        str.remove_prefix(1); // remove the '-'
    }

    const bool has_hex_start = (str.at(0) == '0' && (str.at(1) == 'X'));
    bool is_hex = false;

    if (has_hex_start) {
        str.remove_prefix(2); // remove the "0x"

        if (
            (str.size() > 2) && 
            (str.find_first_not_of("0123456789ABCDEF") == std::string::npos)
        ) {
            is_hex = true;
        } else {
            imm.is_malformed = true;
            return imm;
        }
    }

    u64 num = 0;

    if (is_hex) {
        num = llarm::util::hex_to_i64(str);
    } else {
        for (const char c : str) {
            // verify if the int is valid
            if (std::isdigit(c) == false) {
                imm.is_malformed = true;
                return imm;
            }
        }

        num = llarm::util::str_to_u32(str);
    }

    if (num > 0xFFFFFFFF) {
        imm.is_malformed = true;
        return imm;
    }

    if (is_negative) {
        imm.number = -static_cast<i32>(num);
    } else {
        u8 msb = 31;
        
        for (u8 i = 31; i != 0; i--, msb--) {
            if (num & (1 << i)) {
                break;
            }
        }
        
        imm.number = static_cast<i32>(num);
        imm.msb = msb;
    }

    

    imm.is_invalid = false;

    return imm;
}


token_enum matchers::character(const sv str) {
    if (str.size() != 1) {
        return token_enum::UNKNOWN;
    }

    const char token = str.front();

    switch (token) {
        case '{': return token_enum::REG_LIST_START;
        case '}': return token_enum::REG_LIST_END;
        case '[': return token_enum::MEM_START;
        case ']': return token_enum::MEM_END;
        case '*': return token_enum::MUL_OP;
        case '#': return token_enum::HASHTAG;
        case '^': return token_enum::CARET;
        case '!': return token_enum::PRE_INDEX;
        case '-': return token_enum::MIN_OP;

        // both are basically comment starters
        case '@': return token_enum::COMMENT;
        case '<': return token_enum::COMMENT; // gcc uses this convention like "MOV R0, #1 <some commentary>"
    }

    return token_enum::UNKNOWN;
}


token_enum matchers::address_mode(const sv str) {
    if (str.size() != 3) {
        return token_enum::UNKNOWN;
    }

    constexpr u32 LSL = ('L' << 16) | ('S' << 8) | 'L';
    constexpr u32 LSR = ('L' << 16) | ('S' << 8) | 'R';
    constexpr u32 ASR = ('A' << 16) | ('S' << 8) | 'R';
    constexpr u32 ROR = ('R' << 16) | ('O' << 8) | 'R';
    constexpr u32 RRX = ('R' << 16) | ('R' << 8) | 'X';

    const u32 key = (str.at(0) << 16) | (str.at(1) << 8) | str.at(2);

    switch (key) {
        case LSL: return token_enum::LSL;
        case LSR: return token_enum::LSR;
        case ASR: return token_enum::ASR;
        case ROR: return token_enum::ROR;
        case RRX: return token_enum::RRX;
        default: return token_enum::UNKNOWN;
    }
}