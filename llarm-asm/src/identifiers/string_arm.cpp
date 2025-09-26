#include "string_arm.hpp"
#include "../instruction_id.hpp"

#include "llarm-asm/src/identifiers/interpreter.hpp"
#include "shared/types.hpp"
#include "shared/util.hpp"

using namespace internal;

id::arm string_arm::arm(const std::string &code) {
    const std::string assembly = shared::util::to_upper(code);

    const std::string raw_string = interpreter::fetch_instruction(assembly);
    const std::string_view mnemonic(raw_string);

    const std::vector<std::string_view> candidates = fetch_candidates(mnemonic);

    for (const auto candidate : candidates) {
        auto it = arm_instructions.find(candidate);
    
        if (it != arm_instructions.end()) {
            return it->second;
        }
    }

    // since there's no viable instruction found, 
    // the non-conventional ways will now be searched.

    // MSR has 2 instruction types
    if (mnemonic.starts_with("MSR")) {
        const tokens_t tokens = interpreter::tokenize(code);
        const lexemes_t lexemes = interpreter::lexer(tokens);

        return MSR(lexemes);
    }

    // SWPB has a cond between the P and B
    if (mnemonic.starts_with("SWP")) {    
        return SWPB(mnemonic);
    }


    if (mnemonic.starts_with("STR")) {
        return STR_family(mnemonic);
    }


    if (mnemonic.starts_with("LDR")) {
        return LDR_family(mnemonic);
    }

    return id::arm::UNDEFINED;
}


u16 string_arm::fetch_last_2_chars(const std::string_view str) {
    const std::string_view sub = (str.substr(str.size() - 2));
    return (sub.at(0) << 8) | sub.at(1);
};


std::vector<std::string_view> string_arm::fetch_candidates(const std::string_view raw_mnemonic) {
    std::vector<std::string_view> candidates = {};

    // may be modified and filtered afterwards
    std::string_view mnemonic = raw_mnemonic;
    
    // "mnemonic.extra" convention, i.e. "b.eq" (gcc does this)
    const std::size_t dot_pos = mnemonic.find('.');
    const bool has_dot = (dot_pos != std::string_view::npos);
    
    if (has_dot) {
        candidates.push_back(mnemonic.substr(0, dot_pos));
        
        // early return, no instruction should have a dot in the mnemonic 
        // other than the gcc convention mentioned above
        return candidates;
    }

    // raw 
    candidates.push_back(mnemonic);
    
    // potential addressing mode extension (note: no instruction 
    // mnemonic ends with these, so no conflict is expected)
    constexpr u16 IA = ('I' << 8 | 'A');
    constexpr u16 IB = ('I' << 8 | 'B');
    constexpr u16 DA = ('D' << 8 | 'A');
    constexpr u16 DB = ('D' << 8 | 'B');

    switch (fetch_last_2_chars(mnemonic)) {
        case IA:
        case IB:
        case DA:
        case DB: 
            mnemonic.remove_suffix(2);
            candidates.push_back(mnemonic);
    }

    // potential cond value
    if (interpreter::cond_match(fetch_last_2_chars(mnemonic))) {
        candidates.push_back(mnemonic.substr(0, mnemonic.size() - 2));
    }

    const char last_char = mnemonic.back();

    // potential S/L extension
    if (last_char == 'S' || last_char == 'L') {
        // remove last char
        mnemonic.remove_suffix(1);

        candidates.push_back(mnemonic);

        // potential cond value + S/L extension
        if (interpreter::cond_match(fetch_last_2_chars(mnemonic))) { // no S/L this time
            mnemonic.remove_suffix(2);
            candidates.push_back(mnemonic);
        }
    }

    return candidates;
}


id::arm string_arm::MSR(const lexemes_t &lexemes) {
    using namespace interpreter;

    // MSR_IMM
    if (
        (has_matching_pattern({ CPSR_FIELD, IMMED }, lexemes)) ||
        (has_matching_pattern({ SPSR_FIELD, REG }, lexemes))
    ) {
        return id::arm::MSR_IMM;
    }

    // MSR_REG
    if (
        (has_matching_pattern({ CPSR_FIELD, IMMED }, lexemes)) ||
        (has_matching_pattern({ SPSR_FIELD, REG }, lexemes))
    ) {
        return id::arm::MSR_REG;
    }

    return id::arm::UNDEFINED;
}


id::arm string_arm::SWPB(std::string_view str) {
    // no cond
    if (str == "SWPB") {
        return id::arm::SWPB;
    }

    if (str.back() != 'B' || str.size() != 6) {
        return id::arm::UNDEFINED;
    }

    str.remove_suffix(1); // remove the B and leave out the 2 cond characters at the back

    if (interpreter::cond_match(fetch_last_2_chars(str))) {
        return id::arm::SWPB;
    }

    return id::arm::UNDEFINED;
}


id::arm string_arm::LDR_family(std::string_view str) {
    str.remove_prefix(3); // "LDR"

    const u16 potential_cond = (str.at(0) << 8) | str.at(1);

    if (interpreter::cond_match(potential_cond)) {
        str.remove_prefix(2); // remove cond
    }

    // at this point only the suffix of the instruction should be left

    if (str.size() > 2) {
        return id::arm::UNDEFINED;
    }

    if (str == "BT") {
        return id::arm::LDRBT;
    }

    if (str == "SH") {
        return id::arm::LDRSH;
    }

    if (str == "SB") {
        return id::arm::LDRSB;
    }

    if (str.size() == 1) {
        switch (str.back()) {
            case 'B': return id::arm::LDRB;
            case 'T': return id::arm::LDRT;
            case 'H': return id::arm::LDRH;
        }
    }

    return id::arm::UNDEFINED;
}


id::arm string_arm::STR_family(std::string_view str) {
    // the parameter name and instruction name have no relation just to be clear

    str.remove_prefix(3); // "STR"

    const u16 potential_cond = (str.at(0) << 8) | str.at(1);

    if (interpreter::cond_match(potential_cond)) {
        str.remove_prefix(2); // remove cond
    }

    // at this point only the suffix of the instruction should be left

    if (str.size() > 2) {
        return id::arm::UNDEFINED;
    }

    if (str == "BT") {
        return id::arm::STRBT;
    }

    if (str.size() == 1) {
        switch (str.back()) {
            case 'B': return id::arm::STRB;
            case 'T': return id::arm::STRT;
            case 'H': return id::arm::STRH;
        }
    }

    return id::arm::UNDEFINED;
}