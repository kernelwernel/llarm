#include "util.hpp"

#include <charm/internal/shared/types.hpp>
#include <charm/internal/shared/out.hpp>
#include <charm/internal/shared/util.hpp>

using namespace internal;

util::reg_id util::identify_reg(const u8 reg_bits) {
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
        default: shared::out::error("charm-asm: No known binary code given for register identification");
    }
}


util::reg_id util::identify_reg(const u16 code, const u8 start, const u8 end) {
    const u8 reg_bits = shared::util::bit_fetcher(code, start, end);
    return identify_reg(reg_bits);
}


std::string util::reg_to_string(const util::reg_id id, const bool alias) {
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
        case reg_id::R11: return "R11";
        case reg_id::R12: return "R12";
        case reg_id::R13: return (alias ? "SP" : "R13");
        case reg_id::R14: return (alias ? "LR" : "R14");
        case reg_id::R15: return (alias ? "PC" : "R15");
        default: shared::out::error("charm-asm: No known binary code given for register identification");
    }
}