#include "util.hpp"
#include "../../settings.hpp"

#include "shared/types.hpp"
#include "shared/out.hpp"
#include "shared/util.hpp"

#include <vector>
#include <array>

using namespace internal;

util::reg_id util::identify_reg(const u8 reg_bits, const prefix prefix) {
    switch (prefix) {
        case prefix::R:
            switch (reg_bits) {
                case 0: return reg_id::R0;
                case 1: return reg_id::R1;
                case 2: return reg_id::R2;
                case 3: return reg_id::R3;
                case 4: return reg_id::R4;
                case 5: return reg_id::R5;
                case 6: return reg_id::R6;
                case 7: return reg_id::R7;
                case 8: return reg_id::R8;
                case 9: return reg_id::R9;
                case 10: return reg_id::R10;
                case 11: return reg_id::R11;
                case 12: return reg_id::R12;
                case 13: return reg_id::R13;
                case 14: return reg_id::R14;
                case 15: return reg_id::R15;
                default: shared::out::error("llarm-asm: No known binary code given for R register identification");
            }
    
        case prefix::S:
            switch (reg_bits) {
                case 0: return reg_id::S0;
                case 1: return reg_id::S1;
                case 2: return reg_id::S2;
                case 3: return reg_id::S3;
                case 4: return reg_id::S4;
                case 5: return reg_id::S5;
                case 6: return reg_id::S6;
                case 7: return reg_id::S7;
                case 8: return reg_id::S8;
                case 9: return reg_id::S9;
                case 10: return reg_id::S10;
                case 11: return reg_id::S11;
                case 12: return reg_id::S12;
                case 13: return reg_id::S13;
                case 14: return reg_id::S14;
                case 15: return reg_id::S15;
                case 16: return reg_id::S16;
                case 17: return reg_id::S17;
                case 18: return reg_id::S18;
                case 19: return reg_id::S19;
                case 20: return reg_id::S20;
                case 21: return reg_id::S21;
                case 22: return reg_id::S22;
                case 23: return reg_id::S23;
                case 24: return reg_id::S24;
                case 25: return reg_id::S25;
                case 26: return reg_id::S26;
                case 27: return reg_id::S27;
                case 28: return reg_id::S28;
                case 29: return reg_id::S29;
                case 30: return reg_id::S30;
                case 31: return reg_id::S31;
                default: shared::out::error("llarm-asm: No known binary code given for S register identification");
            }
        
        case prefix::D:
            switch (reg_bits) {
                case 0: return reg_id::D0;
                case 1: return reg_id::D1;
                case 2: return reg_id::D2;
                case 3: return reg_id::D3;
                case 4: return reg_id::D4;
                case 5: return reg_id::D5;
                case 6: return reg_id::D6;
                case 7: return reg_id::D7;
                case 8: return reg_id::D8;
                case 9: return reg_id::D9;
                case 10: return reg_id::D10;
                case 11: return reg_id::D11;
                case 12: return reg_id::D12;
                case 13: return reg_id::D13;
                case 14: return reg_id::D14;
                case 15: return reg_id::D15;
                default: shared::out::error("llarm-asm: No known binary code given for D register identification");
            }

        case prefix::C:
            switch (reg_bits) {
                case 0: return reg_id::C0;
                case 1: return reg_id::C1;
                case 2: return reg_id::C2;
                case 3: return reg_id::C3;
                case 4: return reg_id::C4;
                case 5: return reg_id::C5;
                case 6: return reg_id::C6;
                case 7: return reg_id::C7;
                case 8: return reg_id::C8;
                case 9: return reg_id::C9;
                case 10: return reg_id::C10;
                case 11: return reg_id::C11;
                case 12: return reg_id::C12;
                case 13: return reg_id::C13;
                case 14: return reg_id::C14;
                case 15: return reg_id::C15;
                default: shared::out::error("llarm-asm: No known binary code given for C register identification");
            }

        
        case prefix::P:
            switch (reg_bits) {
                case 0: return reg_id::P0;
                case 1: return reg_id::P1;
                case 2: return reg_id::P2;
                case 3: return reg_id::P3;
                case 4: return reg_id::P4;
                case 5: return reg_id::P5;
                case 6: return reg_id::P6;
                case 7: return reg_id::P7;
                case 8: return reg_id::P8;
                case 9: return reg_id::P9;
                case 10: return reg_id::P10;
                case 11: return reg_id::P11;
                case 12: return reg_id::P12;
                case 13: return reg_id::P13;
                case 14: return reg_id::P14;
                case 15: return reg_id::P15;
                default: shared::out::error("llarm-asm: No known binary code given for C register identification");
            }
    }
}


util::reg_id util::identify_reg(const u32 code, const u8 start, const u8 end, const prefix prefix) {
    const u8 reg_bits = shared::util::bit_range<u8>(code, start, end);
    return identify_reg(reg_bits, prefix);
}


std::string util::reg_id_to_string(const util::reg_id id, const settings settings) {
    switch (id) {
        case reg_id::R0: return "R0";
        case reg_id::R1: return "R1";
        case reg_id::R2: return "R2";
        case reg_id::R3: return "R3";
        case reg_id::R4: return "R4";
        case reg_id::R5: return "R5";
        case reg_id::R6: return "R6";
        case reg_id::R7: return "R7";
        case reg_id::R8: return "R8";
        case reg_id::R9: return "R9";
        case reg_id::R10: return "R10";
        case reg_id::R11: return (settings.register_alias ? "FP" : "R11");
        case reg_id::R12: return (settings.register_alias ? "IP" : "R12");
        case reg_id::R13: return (settings.register_alias ? "SP" : "R13");
        case reg_id::R14: return (settings.register_alias ? "LR" : "R14");
        case reg_id::R15: return (settings.register_alias ? "PC" : "R15");
        case reg_id::S0: return "S0";
        case reg_id::S1: return "S1";
        case reg_id::S2: return "S2";
        case reg_id::S3: return "S3";
        case reg_id::S4: return "S4";
        case reg_id::S5: return "S5";
        case reg_id::S6: return "S6";
        case reg_id::S7: return "S7";
        case reg_id::S8: return "S8";
        case reg_id::S9: return "S9";
        case reg_id::S10: return "S10";
        case reg_id::S11: return "S11";
        case reg_id::S12: return "S12";
        case reg_id::S13: return "S13";
        case reg_id::S14: return "S14";
        case reg_id::S15: return "S15";
        case reg_id::S16: return "S16";
        case reg_id::S17: return "S17";
        case reg_id::S18: return "S18";
        case reg_id::S19: return "S19";
        case reg_id::S20: return "S20";
        case reg_id::S21: return "S21";
        case reg_id::S22: return "S22";
        case reg_id::S23: return "S23";
        case reg_id::S24: return "S24";
        case reg_id::S25: return "S25";
        case reg_id::S26: return "S26";
        case reg_id::S27: return "S27";
        case reg_id::S28: return "S28";
        case reg_id::S29: return "S29";
        case reg_id::S30: return "S30";
        case reg_id::S31: return "S31";
        case reg_id::D0: return "D0";
        case reg_id::D1: return "D1";
        case reg_id::D2: return "D2";
        case reg_id::D3: return "D3";
        case reg_id::D4: return "D4";
        case reg_id::D5: return "D5";
        case reg_id::D6: return "D6";
        case reg_id::D7: return "D7";
        case reg_id::D8: return "D8";
        case reg_id::D9: return "D9";
        case reg_id::D10: return "D10";
        case reg_id::D11: return "D11";
        case reg_id::D12: return "D12";
        case reg_id::D13: return "D13";
        case reg_id::D14: return "D14";
        case reg_id::D15: return "D15";
        case reg_id::C0: return "C0";
        case reg_id::C1: return "C1";
        case reg_id::C2: return "C2";
        case reg_id::C3: return "C3";
        case reg_id::C4: return "C4";
        case reg_id::C5: return "C5";
        case reg_id::C6: return "C6";
        case reg_id::C7: return "C7";
        case reg_id::C8: return "C8";
        case reg_id::C9: return "C9";
        case reg_id::C10: return "C10";
        case reg_id::C11: return "C11";
        case reg_id::C12: return "C12";
        case reg_id::C13: return "C13";
        case reg_id::C14: return "C14";
        case reg_id::C15: return "C15";
        case reg_id::P0: return "P0";
        case reg_id::P1: return "P1";
        case reg_id::P2: return "P2";
        case reg_id::P3: return "P3";
        case reg_id::P4: return "P4";
        case reg_id::P5: return "P5";
        case reg_id::P6: return "P6";
        case reg_id::P7: return "P7";
        case reg_id::P8: return "P8";
        case reg_id::P9: return "P9";
        case reg_id::P10: return "P10";
        case reg_id::P11: return "P11";
        case reg_id::P12: return "P12";
        case reg_id::P13: return "P13";
        case reg_id::P14: return "P14";
        case reg_id::P15: return "P15";
        default: shared::out::error("llarm-asm: No known binary code given for register identification");
    }
}


std::string util::reg_string(const u32 code, const u8 start, const u8 end, const settings settings, const prefix prefix) {
    const util::reg_id reg_id = identify_reg(code, start, end, prefix);
    std::string reg = reg_id_to_string(reg_id, settings);
    return reg;
}


std::string util::reg_list(const u16 list, const settings settings, const reg_id extra) {
    const u8 count = shared::util::popcount(list);

    std::string tmp(
        4 + // for the "{  }"
        (count * 4) - 1, // for the "Ri, " which is 4 characters, and - 1 for the trailing comma that shouldn't be there
        '\0'
    );

    std::vector<reg_id> reg_id_list = {};
    reg_id_list.resize(16);

    for (u8 i = 0; i < (sizeof(list) * 8); i++) {
        if (shared::util::bit_fetch(list, i) == 1) {
            reg_id_list.push_back(identify_reg(i));
        }
    }

    std::vector<std::string> registers = {};
    registers.resize(16);

    for (const auto id : reg_id_list) {
        registers.push_back(reg_id_to_string(id, settings));
    }

    if (registers.empty()) {
        // unpredictable TODO
    }

    tmp += "{ ";

    for (std::size_t i = 0; i < registers.size(); ++i) {
        if (i != 0) {
            tmp += ", ";
        }

        tmp += registers.at(i);
    }

    if (extra != reg_id::NULL_REG) {
        tmp += ", ";
        tmp += reg_id_to_string(extra, settings);
    }

    tmp += " }";

    return tmp;
}


// https://quick-bench.com/q/oqvSMt5BCEiN0odMXX68IdPTrBI
std::string util::raw_cond(const u8 cond) {
    switch (cond) {
        case 0b0000: return "EQ";
        case 0b0001: return "NE";
        case 0b0010: return "CS"; // CS/HS
        case 0b0011: return "CC"; // CC/LO
        case 0b0100: return "MI";
        case 0b0101: return "PL";
        case 0b0110: return "VS";
        case 0b0111: return "VC";
        case 0b1000: return "HI";
        case 0b1001: return "LS";
        case 0b1010: return "GE";
        case 0b1011: return "LT";
        case 0b1100: return "GT";
        case 0b1101: return "LE";
        case 0b1110: return "AL";
        case 0b1111: return "";
    }

    shared::out::error("TODO");
}


std::string util::cond(const u32 code) {
    const u8 condition_code = shared::util::bit_range<u8>(code, 28, 31);
    return raw_cond(condition_code);
}


std::string util::vfp_reg_string_bits(const u32 code, const u8 start, const u8 end, const bool bottom_bit, const settings settings) {
    u8 reg_bits = shared::util::bit_range<u8>(code, start, end);

    reg_bits = static_cast<u8>((reg_bits << 1) | bottom_bit);

    const reg_id id = identify_reg(reg_bits, prefix::S);

    return reg_id_to_string(id, settings);
}


std::string util::reg_string_bits(const u32 code, const u8 start, const u8 end, const bool top_bit, const settings settings) {
    u8 reg_bits = shared::util::bit_range<u8>(code, start, end);

    if ((end - start) != 2) { // 3-bit wide register check (mostly for thumb)
        shared::out::error("TODO");   
    }

    reg_bits = static_cast<u8>(reg_bits | (top_bit << 3));

    const reg_id id = identify_reg(reg_bits, prefix::R);

    return reg_id_to_string(id, settings);
}


std::string util::vfp_register_list(const u8 first_reg, const u8 offset, const settings settings, util::prefix prefix) {
    if (offset & 1) {
        shared::out::error("VFP register offset list should not be an odd number");
    }

    const u8 reg_count = (offset >> (prefix == util::prefix::S ? 0 : 1));
    
    std::vector<u8> reg_nums;
    reg_nums.resize(reg_count);
    
    for (u8 i = first_reg; i < offset; i++) {
        reg_nums.push_back(i);
    }

    std::string tmp(((reg_count) * 5) + 4, '\0'); // just an approximation, not exact but it should do the job 
    
    tmp += "{ ";
    
    for (u8 i = first_reg; i < offset; i++) {
        if (i != first_reg) {
            tmp += ", ";
        }

        const reg_id id = identify_reg(i, prefix);
        tmp += (reg_id_to_string(id, settings));
    }

    tmp += " }";

    return tmp;
}


// idea from https://johnnylee-sde.github.io/Fast-unsigned-integer-to-hex-string/
std::string util::hex(const u32 integer, const settings settings) {
    std::string ret;

    if (integer > 9 && settings.hex) {
        static constexpr std::array<char, 513> digits = {
            "000102030405060708090A0B0C0D0E0F"
            "101112131415161718191A1B1C1D1E1F"
            "202122232425262728292A2B2C2D2E2F"
            "303132333435363738393A3B3C3D3E3F"
            "404142434445464748494A4B4C4D4E4F"
            "505152535455565758595A5B5C5D5E5F"
            "606162636465666768696A6B6C6D6E6F"
            "707172737475767778797A7B7C7D7E7F"
            "808182838485868788898A8B8C8D8E8F"
            "909192939495969798999A9B9C9D9E9F"
            "A0A1A2A3A4A5A6A7A8A9AAABACADAEAF"
            "B0B1B2B3B4B5B6B7B8B9BABBBCBDBEBF"
            "C0C1C2C3C4C5C6C7C8C9CACBCCCDCECF"
            "D0D1D2D3D4D5D6D7D8D9DADBDCDDDEDF"
            "E0E1E2E3E4E5E6E7E8E9EAEBECEDEEEF"
            "F0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF"
        };

        u32 x = integer;
        int i = 3;
        const char* lut = digits.data();
        std::string s(8, '\0');

        for (std::size_t byte = 0; byte < 4; ++byte) {
            const u32 b = (x >> ((3 - byte) * 8)) & 0xFF;
            const std::size_t pos = static_cast<std::size_t>(b) * 2;

            s[byte * 2]     = lut[pos];
            s[byte * 2 + 1] = lut[pos + 1];
        }

        auto first_nonzero = s.find_first_not_of('0');

        if (first_nonzero == std::string::npos) {
            ret = "0x0";
        } else {
            ret = ("0x" + s.substr(first_nonzero));
        }
    } else {
        ret = std::to_string(integer);
    }

    return ret;
}

void util::to_lower(std::string& str) {
    for (char& c : str) {
        c = (c >= 'A' && c <= 'Z') ? (c | 0x20) : c;
    }
}