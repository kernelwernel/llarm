#include "string_arm.hpp"
#include "../instruction_id.hpp"

#include "../interpreter/interpreter.hpp"
#include "shared/types.hpp"
#include "shared/util.hpp"

using namespace internal;

id::arm ident::string_arm::arm(const std::string &code) {
    const std::string assembly = llarm::util::to_upper(code);

    const std::string raw_string = interpreter::fetch_instruction(assembly);
    const llarm::string_view mnemonic(raw_string);

    const std::vector<llarm::string_view> candidates = fetch_candidates(mnemonic);

    for (const auto candidate : candidates) {
        auto it = arm_instructions.find(candidate);
    
        if (it != arm_instructions.end()) {
            return it->second;
        }
    }

    // no conventional instruction found, potentially
    // an instruction variant (i.e BLX1 and BLX2)

    if (mnemonic.starts_with("BLX")) {
        return BLX(interpreter::analyze(assembly));
    }

    // since there's no viable instruction found, 
    // the non-conventional ways will now be searched.

    // MSR has 2 instruction types
    if (mnemonic.starts_with("MSR")) {
        return MSR(interpreter::analyze(assembly));
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

    // 26-bit PSR instructions
    if (mnemonic.back() == 'P') {
        return PSR_family(code);
    }

    return id::arm::UNDEFINED;
}


std::vector<llarm::string_view> ident::string_arm::fetch_candidates(llarm::string_view mnemonic) {
    std::vector<llarm::string_view> candidates = {};

    // "mnemonic.extra" convention, i.e. "b.eq" (gcc does this)
    const std::size_t dot_pos = mnemonic.find('.');
    const bool has_dot = (dot_pos != llarm::string_view::npos);
    
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

    switch (interpreter::fetch_last_2_chars(mnemonic)) {
        case IA:
        case IB:
        case DA:
        case DB: 
            mnemonic.remove_suffix(2);
            candidates.push_back(mnemonic);
    }

    // potential cond value
    if (interpreter::cond_match(interpreter::fetch_last_2_chars(mnemonic))) {
        candidates.push_back(mnemonic.substr(0, mnemonic.size() - 2));
    }

    const char last_char = mnemonic.back();

    // potential S/L extension
    if (last_char == 'S' || last_char == 'L') {
        // remove last char
        mnemonic.remove_suffix(1);

        candidates.push_back(mnemonic);
        
        // potential cond value + S/L extension
        if (interpreter::cond_match(interpreter::fetch_last_2_chars(mnemonic))) { // no S/L this time
            mnemonic.remove_suffix(2);
            candidates.push_back(mnemonic);
        }
    }

    // potential VFP instruction, funky shit happens here
    if (mnemonic.front() == 'F') {
        // potential cond value
        if (interpreter::cond_match(interpreter::fetch_last_2_chars(mnemonic))) {
            mnemonic.remove_suffix(2);
        }

        // precision check
        switch (mnemonic.back()) {
            case 'D':
            case 'S':
            case 'X': 
                mnemonic.remove_suffix(1);
                candidates.push_back(mnemonic);
        }

        switch (interpreter::fetch_last_2_chars(mnemonic)) {
            case IA:
            case IB:
            case DA:
            case DB:
                mnemonic.remove_suffix(2);
                candidates.push_back(mnemonic);
        }
    }

    return candidates;
}


id::arm ident::string_arm::MSR(const lexemes_t &lexemes) {
    using namespace interpreter;

    // MSR_IMM
    if (
        (has_matching_pattern({ CPSR_FIELD, HASHTAG, IMMED }, lexemes)) ||
        (has_matching_pattern({ SPSR_FIELD, REG }, lexemes))
    ) {
        return id::arm::MSR_IMM;
    }

    // MSR_REG
    if (
        (has_matching_pattern({ CPSR_FIELD, HASHTAG, IMMED }, lexemes)) ||
        (has_matching_pattern({ SPSR_FIELD, REG }, lexemes))
    ) {
        return id::arm::MSR_REG;
    }

    return id::arm::UNDEFINED;
}


id::arm ident::string_arm::SWPB(llarm::string_view mnemonic) {
    // no cond
    if (mnemonic == "SWPB") {
        return id::arm::SWPB;
    }

    if (mnemonic.back() != 'B' || mnemonic.size() != 6) {
        return id::arm::UNDEFINED;
    }

    mnemonic.remove_suffix(1); // remove the B and leave out the 2 cond characters at the back

    if (interpreter::cond_match(interpreter::fetch_last_2_chars(mnemonic))) {
        return id::arm::SWPB;
    }

    return id::arm::UNDEFINED;
}


id::arm ident::string_arm::LDR_family(llarm::string_view mnemonic) {
    mnemonic.remove_prefix(3); // "LDR"

    const u16 potential_cond = (mnemonic.at(0) << 8) | mnemonic.at(1);

    if (interpreter::cond_match(potential_cond)) {
        mnemonic.remove_prefix(2); // remove cond
    }

    // at this point only the suffix of the instruction should be left

    if (mnemonic.size() > 2) {
        return id::arm::UNDEFINED;
    }

    if (mnemonic == "BT") {
        return id::arm::LDRBT;
    }

    if (mnemonic == "SH") {
        return id::arm::LDRSH;
    }

    if (mnemonic == "SB") {
        return id::arm::LDRSB;
    }

    if (mnemonic.size() == 1) {
        switch (mnemonic.back()) {
            case 'B': return id::arm::LDRB;
            case 'T': return id::arm::LDRT;
            case 'H': return id::arm::LDRH;
        }
    }

    return id::arm::UNDEFINED;
}


id::arm ident::string_arm::STR_family(llarm::string_view mnemonic) {
    // the parameter name and instruction name have no relation just to be clear

    mnemonic.remove_prefix(3); // "STR"

    const u16 potential_cond = (mnemonic.at(0) << 8) | mnemonic.at(1);

    if (interpreter::cond_match(potential_cond)) {
        mnemonic.remove_prefix(2); // remove cond
    }

    // at this point only the suffix of the instruction should be left

    if (mnemonic.size() > 2) {
        return id::arm::UNDEFINED;
    }

    if (mnemonic == "BT") {
        return id::arm::STRBT;
    }

    if (mnemonic.size() == 1) {
        switch (mnemonic.back()) {
            case 'B': return id::arm::STRB;
            case 'T': return id::arm::STRT;
            case 'H': return id::arm::STRH;
        }
    }

    return id::arm::UNDEFINED;
}


id::arm ident::string_arm::STM(const lexemes_t &lexemes) {
    using namespace interpreter;

    // pre-index is optional for LDM1, so both present and non-present pre-indexes are checked
    if (has_matching_pattern({ REG, PRE_INDEX, REG_LIST }, lexemes)) {
        return id::arm::STM1;
    } else if (has_matching_pattern({ REG, REG_LIST }, lexemes)) {
        return id::arm::STM1;
    }

    if (has_matching_pattern({ REG, REG_LIST, CARET }, lexemes)) {
        return id::arm::STM2;
    }

    return id::arm::UNDEFINED;   
}


id::arm ident::string_arm::LDM(const lexemes_t &lexemes) {
    using namespace interpreter;

    // pre-index is optional for LDM1, so both present and non-present pre-indexes are checked
    if (has_matching_pattern({ REG, PRE_INDEX, REG_LIST }, lexemes)) {
        return id::arm::LDM1;
    } else if (has_matching_pattern({ REG, REG_LIST }, lexemes)) {
        return id::arm::LDM1;
    }

    if (has_matching_pattern({ REG, REG_LIST_NO_PC, CARET }, lexemes)) {
        return id::arm::LDM2;
    }

    if (has_matching_pattern({ REG, PRE_INDEX, REG_LIST_WITH_PC, CARET }, lexemes)) {
        return id::arm::LDM3;
    } else if (has_matching_pattern({ REG, REG_LIST_WITH_PC, CARET }, lexemes)) {
        return id::arm::LDM3;
    }

    return id::arm::UNDEFINED;
}


id::arm ident::string_arm::BLX(const lexemes_t &lexemes) {
    using namespace interpreter;

    if (has_matching_pattern({ CONST }, lexemes)) {
        return id::arm::BLX1;
    } else if (has_matching_pattern({ REG }, lexemes)) {
        return id::arm::BLX2;
    }

    return id::arm::UNDEFINED;
}


id::arm ident::string_arm::PSR_family(const llarm::string_view mnemonic) {
    if (mnemonic.size() == 6) {
        const u8 first_char = mnemonic.at(3);
        const u8 second_char = mnemonic.at(4);

        const u16 cond = (first_char << 8 | second_char);
        
        if (interpreter::cond_match(cond) == false) {
            return id::arm::UNDEFINED;
        }
    }

    if (mnemonic.size() == 4 || mnemonic.size() == 6) {
        if (mnemonic.starts_with("CMN")) { return id::arm::CMNP; }
        else if (mnemonic.starts_with("CMP")) { return id::arm::CMPP; }
        else if (mnemonic.starts_with("TEQ")) { return id::arm::TEQP; }
        else if (mnemonic.starts_with("TST")) { return id::arm::TSTP; }
    }

    return id::arm::UNKNOWN;
}