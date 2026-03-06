#include "../generators.hpp"
#include "../util.hpp"
#include "shifter_operands/shifters.hpp"
#include "../patterns/patterns.hpp"
#include "../../disassemble.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>

#include <string>

using namespace internal;


std::string generators::arm::dsp::LDRD(const u32 code, const settings& settings) {
    const util::reg_id Rd_id = util::identify_reg(code, 12, 15);

    const bool is_Rd_odd = ((static_cast<u8>(Rd_id) & 1) == true);

    if (is_Rd_odd && settings.strict_compliance) {
        return UNDEFINED;
    }

    if (Rd_id == util::reg_id::R15) {
        return ERROR;
    }

    const std::string addressing_mode = shifters::ls_misc(code, settings);

    if (addressing_mode == ERROR) {
        return ERROR;
    }

    const bool suf = settings.cond_always_suffix;

    const std::string Rd = util::reg_id_to_string(Rd_id, settings);

    const std::string Rn = [=]() -> std::string {
        if (settings.explicit_operands == false) {
            return "";
        }

        // this is really stupid
        const util::reg_id Rn_id = static_cast<util::reg_id>(static_cast<u8>(Rd_id) + 1); 

        return util::reg_id_to_string(Rn_id, settings);
    }();

    return util::make_string("LDR", (suf ? "D" : ""), util::cond(code, settings), (suf ? " ": "D "), Rd, ", ", Rn, (Rn == "" ? "" : ", "), addressing_mode);
}


std::string generators::arm::dsp::MCRR(const u32 code, const settings& settings) {
    const std::string coproc = util::reg_string(code, 8, 11, settings, util::prefix::P);

    const std::string Rd = util::reg_string(code, 12, 15, settings);
    const std::string Rn = util::reg_string(code, 16, 19, settings);
    const std::string CRm = util::reg_string(code, 0, 3, settings, util::prefix::C);

    const u8 opcode = llarm::util::bit_range<u8>(code, 4, 7);

    return util::make_string("MCRR", util::cond(code, settings), " ", coproc, ", #", opcode, ", ", Rd, ", ", Rn, ", ", CRm);
}


std::string generators::arm::dsp::MRRC(const u32 code, const settings& settings) {
    const std::string coproc = util::reg_string(code, 8, 11, settings, util::prefix::P);

    const std::string Rd = util::reg_string(code, 12, 15, settings);
    const std::string Rn = util::reg_string(code, 16, 19, settings);
    const std::string CRm = util::reg_string(code, 0, 3, settings, util::prefix::C);

    const u8 opcode = llarm::util::bit_range<u8>(code, 4, 7);

    return util::make_string("MRRC", util::cond(code, settings), " ", coproc, ", #", opcode, ", ", Rd, ", ", Rn, ", ", CRm);
}


std::string generators::arm::dsp::PLD(const u32 code, const settings& settings) {
    const std::string addressing_mode = shifters::ls(code, settings);
    return util::make_string("PLD ", addressing_mode);
}


std::string generators::arm::dsp::QADD(const u32 code, const settings& settings) {
    return patterns::dsp_Rd_Rm_Rn(code, "QADD", settings);
}


std::string generators::arm::dsp::QDADD(const u32 code, const settings& settings) {
    return patterns::dsp_Rd_Rm_Rn(code, "QDADD", settings);
}


std::string generators::arm::dsp::QDSUB(const u32 code, const settings& settings) {
    return patterns::dsp_Rd_Rm_Rn(code, "QDSUB", settings);
}


std::string generators::arm::dsp::QSUB(const u32 code, const settings& settings) {
    return patterns::dsp_Rd_Rm_Rn(code, "QSUB", settings);
}


std::string generators::arm::dsp::SMLAXY(const u32 code, const settings& settings) {
    const char x = (llarm::util::bit_fetch(code, 5) ? 'T' : 'B');
    const char y = (llarm::util::bit_fetch(code, 6) ? 'T' : 'B');

    const std::string Rd = util::reg_string(code, 16, 19, settings);
    const std::string Rm = util::reg_string(code, 0, 3, settings);
    const std::string Rs = util::reg_string(code, 8, 11, settings);
    const std::string Rn = util::reg_string(code, 12, 15, settings);

    return util::make_string("SMLA", x, y, util::cond(code, settings), " ", Rd, ", ", Rm, ", ", Rs, ", ", Rn);
}


std::string generators::arm::dsp::SMLALXY(const u32 code, const settings& settings) {
    const char x = (llarm::util::bit_fetch(code, 5) ? 'T' : 'B');
    const char y = (llarm::util::bit_fetch(code, 6) ? 'T' : 'B');

    const std::string Rm = util::reg_string(code, 0, 3, settings);
    const std::string Rs = util::reg_string(code, 8, 11, settings);
    const std::string RdHi = util::reg_string(code, 16, 19, settings);
    const std::string RdLo = util::reg_string(code, 12, 15, settings);

    return util::make_string("SMLAL", x, y, util::cond(code, settings), " ", RdLo, ", ", RdHi, ", ", Rm, ", ", Rs);
}


std::string generators::arm::dsp::SMLAWY(const u32 code, const settings& settings) {
    const char y = (llarm::util::bit_fetch(code, 6) ? 'T' : 'B');

    const std::string Rd = util::reg_string(code, 16, 19, settings);
    const std::string Rm = util::reg_string(code, 0, 3, settings);
    const std::string Rs = util::reg_string(code, 8, 11, settings);
    const std::string Rn = util::reg_string(code, 12, 15, settings);

    return util::make_string("SMLAW", y, util::cond(code, settings), " ", Rd, ", ", Rm, ", ", Rs, ", ", Rn);
}


std::string generators::arm::dsp::SMULXY(const u32 code, const settings& settings) {
    const char x = (llarm::util::bit_fetch(code, 5) ? 'T' : 'B');
    const char y = (llarm::util::bit_fetch(code, 6) ? 'T' : 'B');

    const std::string Rm = util::reg_string(code, 0, 3, settings);
    const std::string Rs = util::reg_string(code, 8, 11, settings);
    const std::string Rd = util::reg_string(code, 16, 19, settings);

    return util::make_string("SMUL", x, y, util::cond(code, settings), " ", Rd, ", ", Rm, ", ", Rs);
}


std::string generators::arm::dsp::SMULWY(const u32 code, const settings& settings) {
    const char y = (llarm::util::bit_fetch(code, 6) ? 'T' : 'B');

    const std::string Rd = util::reg_string(code, 16, 19, settings);
    const std::string Rm = util::reg_string(code, 0, 3, settings);
    const std::string Rs = util::reg_string(code, 8, 11, settings);

    return util::make_string("SMULW", y, util::cond(code, settings), " ", Rd, ", ", Rm, ", ", Rs);
}


std::string generators::arm::dsp::STRD(const u32 code, const settings& settings) {
    const util::reg_id Rd_id = util::identify_reg(code, 12, 15);
    const std::string Rd = util::reg_id_to_string(Rd_id, settings);

    const bool is_Rd_odd = ((static_cast<u8>(Rd_id) & 1) == true);

    if (is_Rd_odd && settings.strict_compliance) {
        return UNDEFINED;
    }

    if (Rd_id == util::reg_id::R15) {
        return ERROR;
    }

    const std::string addressing_mode = shifters::ls_misc(code, settings);

    if (addressing_mode == ERROR) {
        return ERROR;
    }

    const std::string Rn = [=]() -> std::string {
        if (settings.explicit_operands == false) {
            return "";
        }

        const util::reg_id Rn_id = static_cast<util::reg_id>(static_cast<u8>(Rd_id) + 1); 
        
        return util::reg_id_to_string(Rn_id, settings);
    }();

    const bool suf = settings.cond_always_suffix;

    return util::make_string("STR", (suf ? "D" : ""), util::cond(code, settings), (suf ? " " : "D "), Rd, ", ", Rn, (Rn == "" ? "" : ", "), addressing_mode);
}