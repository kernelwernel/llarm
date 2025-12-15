#include "matchers.hpp"
#include "tokens.hpp"

#include "shared/string_view.hpp"
#include "shared/util.hpp"

#include <cctype>

REG matchers::reg(const llarm::string_view str) {
    REG reg = {
        reg_type::UNKNOWN, // type
        0,  // number
        false, // is_reg_vfp_special
        false, // is_malformed
        true // is_invalid
    };

    const reg_type type = [=]() -> reg_type {
        switch (str.front()) {
            case 'R': return reg_type::REGULAR; // regular register
            case 'D': return reg_type::SINGLE; // VFP double register
            case 'S': return reg_type::DOUBLE; // VFP single register
            case 'P': return reg_type::COPROC; // coprocessor num
            case 'C': return reg_type::CR; // CRn/CRm register
            default: return reg_type::UNKNOWN;
        }
    }();

    if (type == reg_type::UNKNOWN) {
        reg.is_invalid = true;
        return reg;
    }

    // register format: <prefix>0~31 (i.e. R13, S28)
    // keep note that only VFP single regs have 0~31
    // range, otherwise it's 0~15

    for (u8 i = 1; i < str.size(); i++) {
        if (std::isdigit(str.at(i)) == false) {
            reg.is_invalid = true;
            return reg;
        }
    }

    const u32 raw_num = llarm::util::str_to_u32(str);

    u8 num = 255;
    bool is_malformed = false;

    const u8 limit = (type == reg_type::SINGLE ? 31 : 15);
 
    if (raw_num > limit) {
        is_malformed = true;
    } else {
        num = static_cast<u8>(raw_num);
    }

    constexpr bool is_invalid = false;

    return REG { 
        type, 
        num, 
        is_malformed,
        is_invalid
    };
}


PSR matchers::cpsr_spsr(const llarm::string_view str) {
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

    const llarm::string_view fields = str.substr(5);
    
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


IMM matchers::immediate(llarm::string_view str) {
    IMM imm = {
        0, /* number */
        0, /* msb */
        false, /* is_negative */
        false, /* is_hex */
        false, /* is_multiple_of_4 */
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

    if (has_hex_start) {
        str.remove_prefix(2); // remove the "0x"

        if (
            (str.size() > 2) && 
            (str.find_first_not_of("0123456789ABCDEF") == std::string::npos)
        ) {
            imm.is_hex = true;
        } else {
            imm.is_malformed = true;
            return imm;
        }
    }

    u64 num = 0;

    if (imm.is_hex) {
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

    if ((imm.number & 0b11) == 0) {
        imm.is_multiple_of_4 = true;
    }

    imm.is_invalid = false;

    return imm;
}


token matchers::character(const llarm::string_view str) {
    if (str.size() != 1) {
        return token::UNKNOWN;
    }

    const char token = str.front();

    switch (token) {
        case '{': return token::REG_LIST_START;
        case '}': return token::REG_LIST_END;
        case '[': return token::MEM_START;
        case ']': return token::MEM_END;
        case '*': return token::MUL_OP;
        case '#': return token::HASHTAG;
        case '^': return token::CARET;
        case '!': return token::PRE_INDEX;
        case '-': return token::MIN_OP;

        // both are basically comment starters
        case '@': return token::COMMENT;
        case '<': return token::COMMENT; // gcc uses this convention like "MOV R0, #1 <some commentary>"
    }

    return token::UNKNOWN;
}


token matchers::address_mode(const llarm::string_view str) {
    if (str.size() != 3) {
        return token::UNKNOWN;
    }

    constexpr u32 LSL = ('L' << 16) | ('S' << 8) | 'L';
    constexpr u32 LSR = ('L' << 16) | ('S' << 8) | 'R';
    constexpr u32 ASR = ('A' << 16) | ('S' << 8) | 'R';
    constexpr u32 ROR = ('R' << 16) | ('O' << 8) | 'R';
    constexpr u32 RRX = ('R' << 16) | ('R' << 8) | 'X';

    const u32 key = (str.at(0) << 16) | (str.at(1) << 8) | str.at(2);

    switch (key) {
        case LSL: return token::LSL;
        case LSR: return token::LSR;
        case ASR: return token::ASR;
        case ROR: return token::ROR;
        case RRX: return token::RRX;
        default: return token::UNKNOWN;
    }
}