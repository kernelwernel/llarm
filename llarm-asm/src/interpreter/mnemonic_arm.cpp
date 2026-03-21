#include "mnemonic_arm.hpp"
#include "../id/instruction_id.hpp"
#include "../id/cond_id.hpp"
#include "../interpreter/interpreter.hpp"
#include "../interpreter/tokens.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>

using namespace internal;
using namespace interpreter;
using enum token_enum;

mnemonic_struct_arm mnemonic_arm::arm(const std::string &code) {
    const std::string assembly = llarm::util::to_upper(code);
    const sv mnemonic = interpreter::fetch_instruction(assembly);

    const arm_id id = fetch_arm_id(code, mnemonic, assembly);

    if (id != arm_id::UNKNOWN) {
        return fetch_mnemonic_args(id, mnemonic);
    }

    // invalid, this is the same as an undefined exception
    return mnemonic_struct_arm{};
}

arm_id mnemonic_arm::fetch_arm_id(const std::string &code, const sv mnemonic, const sv assembly) {
    const std::vector<sv> candidates = fetch_candidates(mnemonic);

    for (const auto candidate : candidates) {
        auto it = arm_instructions.find(candidate);
    
        if (it != arm_instructions.end()) {
            return it->second;
        }
    }

    // no conventional instruction found, potentially
    // an instruction variant (i.e BLX1 and BLX2)

    arm_id id = arm_id::UNKNOWN;

    if (mnemonic.starts_with("BLX")) {
        id = BLX(interpreter::analyze(assembly));
    } else if (mnemonic.starts_with("MSR")) {
        // since there's no viable instruction found, 
        // the non-conventional ways will now be searched.
    
        // MSR has 2 instruction types
        id = MSR(interpreter::analyze(assembly));
    } else if (mnemonic.starts_with("SWP")) {    
        // SWPB has a cond between the P and B
        id = SWPB(mnemonic);
    } else if (mnemonic.starts_with("STR")) {
        id = STR_family(mnemonic);
    } else if (mnemonic.starts_with("LDR")) {
        id = LDR_family(mnemonic);
    } else if (mnemonic.back() == 'P') {
        // 26-bit PSR instructions
        id = PSR_family(code);
    }
    
    return id;
}


std::vector<sv> mnemonic_arm::fetch_candidates(sv mnemonic) {
    std::vector<sv> candidates = {};

    // "mnemonic.extra" convention, i.e. "b.eq" (gcc does this)
    const std::size_t dot_pos = mnemonic.find('.');
    const bool has_dot = (dot_pos != sv::npos);
    
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
    if (mnemonic.front() != 'F') {
        return candidates;
    }

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

    return candidates;
}


arm_id mnemonic_arm::MSR(const lexemes_t &lexemes) {
    // MSR_IMM
    if (
        (verify_tokens({ PSR, HASHTAG, IMMED }, lexemes)) ||
        (verify_tokens({ PSR, HASHTAG, IMMED }, lexemes))
    ) {
        return arm_id::MSR_IMM;
    }

    // MSR_REG
    if (
        (verify_tokens({ PSR, REG }, lexemes)) ||
        (verify_tokens({ PSR, REG }, lexemes))
    ) {
        return arm_id::MSR_REG;
    }

    return arm_id::UNDEFINED;
}


arm_id mnemonic_arm::SWPB(sv mnemonic) {
    // no cond
    if (mnemonic == "SWPB") {
        return arm_id::SWPB;
    }

    if (mnemonic.back() != 'B' || mnemonic.size() != 6) {
        return arm_id::UNDEFINED;
    }

    mnemonic.remove_suffix(1); // remove the B and leave out the 2 cond characters at the back

    if (interpreter::cond_match(interpreter::fetch_last_2_chars(mnemonic))) {
        return arm_id::SWPB;
    }

    return arm_id::UNDEFINED;
}


arm_id mnemonic_arm::LDR_family(sv mnemonic) {
    mnemonic.remove_prefix(3); // "LDR"

    const u16 potential_cond = static_cast<u16>((mnemonic.at(0) << 8) | mnemonic.at(1));

    if (interpreter::cond_match(potential_cond)) {
        mnemonic.remove_prefix(2); // remove cond
    }

    // at this point only the suffix of the instruction should be left

    if (mnemonic.size() > 2) {
        return arm_id::UNDEFINED;
    }

    if (mnemonic == "BT") {
        return arm_id::LDRBT;
    }

    if (mnemonic == "SH") {
        return arm_id::LDRSH;
    }

    if (mnemonic == "SB") {
        return arm_id::LDRSB;
    }

    if (mnemonic.size() == 1) {
        switch (mnemonic.back()) {
            case 'B': return arm_id::LDRB;
            case 'T': return arm_id::LDRT;
            case 'H': return arm_id::LDRH;
        }
    }

    return arm_id::UNDEFINED;
}


arm_id mnemonic_arm::STR_family(sv mnemonic) {
    // the parameter name and instruction name have no relation just to be clear

    mnemonic.remove_prefix(3); // "STR"

    const u16 potential_cond = static_cast<u16>((mnemonic.at(0) << 8) | mnemonic.at(1));

    if (interpreter::cond_match(potential_cond)) {
        mnemonic.remove_prefix(2); // remove cond
    }

    // at this point only the suffix of the instruction should be left

    if (mnemonic.size() > 2) {
        return arm_id::UNDEFINED;
    }

    if (mnemonic == "BT") {
        return arm_id::STRBT;
    }

    if (mnemonic.size() == 1) {
        switch (mnemonic.back()) {
            case 'B': return arm_id::STRB;
            case 'T': return arm_id::STRT;
            case 'H': return arm_id::STRH;
        }
    }

    return arm_id::UNDEFINED;
}


arm_id mnemonic_arm::STM(const lexemes_t &lexemes) {
    // pre-index is optional for LDM1, so both present and non-present pre-indexes are checked
    if (verify_tokens({ REG, PRE_INDEX, REG_LIST }, lexemes)) {
        return arm_id::STM1;
    } else if (verify_tokens({ REG, REG_LIST }, lexemes)) {
        return arm_id::STM1;
    }

    if (verify_tokens({ REG, REG_LIST, CARET }, lexemes)) {
        return arm_id::STM2;
    }

    return arm_id::UNDEFINED;   
}


arm_id mnemonic_arm::LDM(const lexemes_t &lexemes) {
    // pre-index is optional for LDM1, so both present and non-present pre-indexes are checked
    if (verify_tokens({ REG, PRE_INDEX, REG_LIST }, lexemes)) {
        return arm_id::LDM1;
    } else if (verify_tokens({ REG, REG_LIST }, lexemes)) {
        return arm_id::LDM1;
    }

    if (verify_tokens({ REG, REG_LIST, CARET }, lexemes)) {
        return arm_id::LDM2;
    }

    if (verify_tokens({ REG, PRE_INDEX, REG_LIST, CARET }, lexemes)) {
        return arm_id::LDM3;
    } else if (verify_tokens({ REG, REG_LIST, CARET }, lexemes)) {
        return arm_id::LDM3;
    }

    return arm_id::UNDEFINED;
}


arm_id mnemonic_arm::BLX(const lexemes_t &lexemes) {
    if (verify_tokens({ IMMED }, lexemes)) {
        return arm_id::BLX1;
    } else if (verify_tokens({ REG }, lexemes)) {
        return arm_id::BLX2;
    }

    return arm_id::UNDEFINED;
}


arm_id mnemonic_arm::PSR_family(const sv mnemonic_str) {
    if (mnemonic_str.size() == 6) {
        const char first_char = mnemonic_str.at(3);
        const char second_char = mnemonic_str.at(4);

        const u16 cond = static_cast<u16>((first_char << 8) | second_char);
   
        if (cond_match(cond) == false) {
            return arm_id::UNDEFINED;
        }
    }

    if (mnemonic_str.size() == 4 || mnemonic_str.size() == 6) {
        if (mnemonic_str.starts_with("CMN")) { return arm_id::CMNP; }
        else if (mnemonic_str.starts_with("CMP")) { return arm_id::CMPP; }
        else if (mnemonic_str.starts_with("TEQ")) { return arm_id::TEQP; }
        else if (mnemonic_str.starts_with("TST")) { return arm_id::TSTP; }
    }

    return arm_id::UNKNOWN;
}


mnemonic_struct_arm mnemonic_arm::fetch_mnemonic_args(const arm_id id, sv mnemonic) {
    mnemonic_struct_arm args{};

    args.instruction = mnemonic;
    args.id = id;

    switch (id) {
        case arm_id::UNKNOWN: return args;
        case arm_id::UNDEFINED: return args;
        
        // these don't have a condition code
        case arm_id::BLX1:
        case arm_id::CDP2:
        case arm_id::MCR2:
        case arm_id::MRC2:
        case arm_id::BKPT:
        case arm_id::NOP: // maybe this shouldn't be here since it's a unique instruction to the project, idk
        case arm_id::PLD: 
            args.cond_id = cond_id::NONE;
            return args;
        
        // <mnemonic>{<cond>} format
        case arm_id::LDR:
        case arm_id::MCR:
        case arm_id::MRC: mnemonic.remove_prefix(1); [[fallthrough]];
        case arm_id::BL: mnemonic.remove_prefix(1); [[fallthrough]];
        case arm_id::B: mnemonic.remove_prefix(1);
            args.cond_id = interpreter::fetch_cond_id(mnemonic);
            return args;

        // <mnemonic>{<cond>}{S} format
        case arm_id::SMLAL:
        case arm_id::SMULL:
        case arm_id::UMLAL:
        case arm_id::UMULL: mnemonic.remove_prefix(2); [[fallthrough]];
        case arm_id::ADC:
        case arm_id::ADD:
        case arm_id::AND:
        case arm_id::BIC:
        case arm_id::EOR:
        case arm_id::MLA:
        case arm_id::MOV:
        case arm_id::MUL:
        case arm_id::MVN:
        case arm_id::ORR:
        case arm_id::RSB:
        case arm_id::RSC:
        case arm_id::SBC:
        case arm_id::SUB:
            mnemonic.remove_prefix(3);
            args.cond_id = interpreter::fetch_cond_id(mnemonic);

            if (mnemonic.size() == 3) {
                args.has_S = (mnemonic.back() == 'S');
            }
            
            return args;
            
        // <mnemonic>{<cond>} format
        case arm_id::FLDMD: // while it may not seem like these VFP instructions have 
        case arm_id::FLDMS: // 7 characters to be removed to reach the cond value, 
        case arm_id::FLDMX: // the addressing mode extends them to have 2 more characters,
        case arm_id::FSTMD: // hence why it's added here.
        case arm_id::FSTMS:
        case arm_id::FSTMX:
        case arm_id::FCMPEZS:
        case arm_id::FCMPEZD: mnemonic.remove_prefix(1); [[fallthrough]];
        case arm_id::FCMPES:
        case arm_id::FCMPZS:
        case arm_id::FMSTAT:
        case arm_id::FNMACS:
        case arm_id::FNMSCS:
        case arm_id::FNMULS:
        case arm_id::FSITOS:
        case arm_id::FSQRTS:
        case arm_id::FUITOS:
        case arm_id::FCMPED:
        case arm_id::FCMPZD:
        case arm_id::FCVTDS:
        case arm_id::FCVTSD:
        case arm_id::FNMACD:
        case arm_id::FNMSCD:
        case arm_id::FNMULD:
        case arm_id::FSITOD:
        case arm_id::FSQRTD:
        case arm_id::FUITOD: mnemonic.remove_prefix(1); [[fallthrough]];
        case arm_id::FABSS:
        case arm_id::FADDS:
        case arm_id::FCMPS:
        case arm_id::FCPYS:
        case arm_id::FDIVS:
        case arm_id::FMACS:
        case arm_id::FMSCS:
        case arm_id::FMULS:
        case arm_id::FNEGS:
        case arm_id::FSUBS:
        case arm_id::FABSD:
        case arm_id::FADDD:
        case arm_id::FCMPD:
        case arm_id::FCPYD:
        case arm_id::FDIVD:
        case arm_id::FMACD:
        case arm_id::FMDHR:
        case arm_id::FMDLR:
        case arm_id::FMRDL:
        case arm_id::FMRDH:
        case arm_id::FMSCD:
        case arm_id::FMULD:
        case arm_id::FNEGD:
        case arm_id::FSUBD: 
        case arm_id::QDADD:
        case arm_id::QDSUB: mnemonic.remove_prefix(1); [[fallthrough]];
        case arm_id::FLDS:
        case arm_id::FMRS:
        case arm_id::FMRX:
        case arm_id::FMSR:
        case arm_id::FMXR:
        case arm_id::FSTS:
        case arm_id::FLDD:
        case arm_id::FSTD: 
        case arm_id::MCRR:
        case arm_id::MRRC:
        case arm_id::QADD:
        case arm_id::QSUB: mnemonic.remove_prefix(1); [[fallthrough]];
        case arm_id::CDP:
        case arm_id::CLZ:
        case arm_id::CMN:
        case arm_id::CMP:
        case arm_id::BLX2:
        case arm_id::MSR_IMM:
        case arm_id::MSR_REG:
        case arm_id::MRS:
        case arm_id::STR: 
        case arm_id::LDM1: // The format for LDM<x> and STM<x> should be <mnemonic>{<cond>}<addressing_mode>,
        case arm_id::LDM2: // but they're included here because the addressing modes are ignored. It's not 
        case arm_id::LDM3: // relevant to what we're looking for and they're already managed by the shifter
        case arm_id::STM1: // identification module in identifiers/string_shifters.cpp. So it basically boils
        case arm_id::STM2: // down to the <mnemonic>{<cond>} format.
        case arm_id::SWI:
        case arm_id::SWP:
        case arm_id::TEQ:
        case arm_id::LDRB:  // same here with LDR{<cond>}<suffix> and STR{<cond>}<suffix>. The suffix part is 
        case arm_id::LDRBT: // ignored for the same reasons with LDM and STM above. Only the first 3 characters  
        case arm_id::LDRH:  // should be removed to fetch the remaining cond value and that's it. Some of these 
        case arm_id::LDRSB: // instructions are formated as LDR{<cond>}BT, which is why they are included here
        case arm_id::LDRSH: // since the ending is not necessary for what we're looking for.
        case arm_id::LDRT:
        case arm_id::STRB: 
        case arm_id::STRBT:
        case arm_id::STRT: 
        case arm_id::STRH:
        case arm_id::SWPB:
        case arm_id::CMNP: // format: CMN{<cond>}P, same for the rest of the 26-bit instructions
        case arm_id::CMPP:
        case arm_id::TEQP:
        case arm_id::TSTP:
        case arm_id::STRD: // format STR{<cond>}D
        case arm_id::LDRD: // same as above
        case arm_id::TST: mnemonic.remove_prefix(1); [[fallthrough]];
        case arm_id::BX: mnemonic.remove_prefix(2);
            args.cond_id = interpreter::fetch_cond_id(mnemonic);
            return args;

        // <mnemonic>{<cond>}{L} format
        case arm_id::LDC:
        case arm_id::STC:
            mnemonic.remove_prefix(3);
            args.cond_id = interpreter::fetch_cond_id(mnemonic);

            if (mnemonic.size() >= 2) {
                mnemonic.remove_prefix(2); // remove cond
            }
            
            if (mnemonic.size() == 1) { // remaining L
                args.has_L = (mnemonic.back() == 'L');
            }
            
            return args;
            
        
        // <mnemonic>{L} format
        case arm_id::LDC2:
        case arm_id::STC2:
            mnemonic.remove_prefix(4);
            args.cond_id = cond_id::NONE;
            
            if (mnemonic.size() == 1) {
                args.has_L = (mnemonic.back() == 'L');
            }
            
            return args;
        
        // <mnemonic>{Z}<S|D>{<cond>} format
        case arm_id::FTOSID:
        case arm_id::FTOSIS:
        case arm_id::FTOUID:
        case arm_id::FTOUIS:
            mnemonic.remove_prefix(5);

            if (mnemonic.front() == 'Z') {
                args.has_Z = true;
                mnemonic.remove_prefix(2);
            } else {
                mnemonic.remove_prefix(1);
            }

            args.cond_id = interpreter::fetch_cond_id(mnemonic);
            return args;

        case arm_id::SMLALXY: mnemonic.remove_prefix(1); [[fallthrough]];
        case arm_id::SMLAXY:
        case arm_id::SMULXY:
            mnemonic.remove_prefix(4);

            args.x_char = mnemonic.front();
            mnemonic.remove_prefix(1);
            args.y_char = mnemonic.front();
            mnemonic.remove_prefix(1);
            args.cond_id = interpreter::fetch_cond_id(mnemonic);
            return args;
        
        case arm_id::SMULWY:
        case arm_id::SMLAWY: 
            mnemonic.remove_prefix(5);
            args.y_char = mnemonic.front();
            mnemonic.remove_prefix(1);
            args.cond_id = interpreter::fetch_cond_id(mnemonic);
            return args;
    }
}