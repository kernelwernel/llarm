#include "../generators.hpp"
#include "../util.hpp"
#include "shifter_operands/shifters.hpp"
#include "../patterns/patterns.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"

#include <string>

using namespace internal;


std::string generators::arm::dsp::LDRD(const u32 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 12, 15, settings);

    const std::string addressing_mode = shifters::ls_misc(code, settings);

    return util::make_string("LDR", util::cond(code, settings), "D ", Rd, ", ", addressing_mode);
}


std::string generators::arm::dsp::MCRR(const u32 code, const settings settings) {
    const std::string coproc = util::reg_string(code, 8, 11, settings, util::prefix::P);

    const std::string Rd = util::reg_string(code, 12, 15, settings);
    const std::string Rn = util::reg_string(code, 16, 19, settings);
    const std::string CRm = util::reg_string(code, 0, 3, settings, util::prefix::C);

    const u8 opcode = llarm::util::bit_range<u8>(code, 4, 7);

    return util::make_string("MCRR", util::cond(code, settings), " ", coproc, ", #", opcode, ", ", Rd, ", ", Rn, ", ", CRm);
}


std::string generators::arm::dsp::MRRC(const u32 code, const settings settings) {
    const std::string coproc = util::reg_string(code, 8, 11, settings, util::prefix::P);

    const std::string Rd = util::reg_string(code, 12, 15, settings);
    const std::string Rn = util::reg_string(code, 16, 19, settings);
    const std::string CRm = util::reg_string(code, 0, 3, settings, util::prefix::C);

    const u8 opcode = llarm::util::bit_range<u8>(code, 4, 7);

    return util::make_string("MRRC", util::cond(code, settings), " ", coproc, ", #", opcode, ", ", Rd, ", ", Rn, ", ", CRm);
}


std::string generators::arm::dsp::PLD(const u32 code, const settings settings) {
    const std::string addressing_mode = shifters::ls(code, settings);
    return util::make_string("PLD ", addressing_mode);
}


std::string generators::arm::dsp::QADD(const u32 code, const settings settings) {
    return patterns::dsp_Rd_Rm_Rn(code, "QADD", settings);
}


std::string generators::arm::dsp::QDADD(const u32 code, const settings settings) {
    return patterns::dsp_Rd_Rm_Rn(code, "QDADD", settings);
}


std::string generators::arm::dsp::QDSUB(const u32 code, const settings settings) {
    return patterns::dsp_Rd_Rm_Rn(code, "QDSUB", settings);
}


std::string generators::arm::dsp::QSUB(const u32 code, const settings settings) {
    return patterns::dsp_Rd_Rm_Rn(code, "QSUB", settings);
}


std::string generators::arm::dsp::SMLAXY(const u32 code, const settings settings) {
    const char x = (llarm::util::bit_fetch(code, 5) ? 'T' : 'B');
    const char y = (llarm::util::bit_fetch(code, 6) ? 'T' : 'B');

    const std::string Rd = util::reg_string(code, 16, 19, settings);
    const std::string Rm = util::reg_string(code, 0, 3, settings);
    const std::string Rs = util::reg_string(code, 8, 11, settings);
    const std::string Rn = util::reg_string(code, 12, 15, settings);

    return util::make_string("SMLA", x, y, util::cond(code, settings), " ", Rd, ", ", Rm, ", ", Rs, ", ", Rn);
}


std::string generators::arm::dsp::SMLALXY(const u32 code, const settings settings) {
    const char x = (llarm::util::bit_fetch(code, 5) ? 'T' : 'B');
    const char y = (llarm::util::bit_fetch(code, 6) ? 'T' : 'B');

    const std::string Rm = util::reg_string(code, 0, 3, settings);
    const std::string Rs = util::reg_string(code, 8, 11, settings);
    const std::string RdHi = util::reg_string(code, 16, 19, settings);
    const std::string RdLo = util::reg_string(code, 12, 15, settings);

    return util::make_string("SMLAL", x, y, util::cond(code, settings), " ", RdLo, ", ", RdHi, ", ", Rm, ", ", Rs);
}


std::string generators::arm::dsp::SMLAWY(const u32 code, const settings settings) {
    const char y = (llarm::util::bit_fetch(code, 6) ? 'T' : 'B');

    const std::string Rd = util::reg_string(code, 16, 19, settings);
    const std::string Rm = util::reg_string(code, 0, 3, settings);
    const std::string Rs = util::reg_string(code, 8, 11, settings);
    const std::string Rn = util::reg_string(code, 12, 15, settings);

    return util::make_string("SMLAW", y, util::cond(code, settings), " ", Rd, ", ", Rm, ", ", Rs, ", ", Rn);
}


std::string generators::arm::dsp::SMULXY(const u32 code, const settings settings) {
    const char x = (llarm::util::bit_fetch(code, 5) ? 'T' : 'B');
    const char y = (llarm::util::bit_fetch(code, 6) ? 'T' : 'B');

    const std::string Rm = util::reg_string(code, 0, 3, settings);
    const std::string Rs = util::reg_string(code, 8, 11, settings);
    const std::string Rd = util::reg_string(code, 16, 19, settings);

    return util::make_string("SMUL", x, y, util::cond(code, settings), " ", Rd, ", ", Rm, ", ", Rs);
}


std::string generators::arm::dsp::SMULWY(const u32 code, const settings settings) {
    const char y = (llarm::util::bit_fetch(code, 6) ? 'T' : 'B');

    const std::string Rd = util::reg_string(code, 16, 19, settings);
    const std::string Rm = util::reg_string(code, 0, 3, settings);
    const std::string Rs = util::reg_string(code, 8, 11, settings);

    return util::make_string("SMULW", y, util::cond(code, settings), " ", Rd, ", ", Rm, ", ", Rs);
}


std::string generators::arm::dsp::STRD(const u32 code, const settings settings) {
    const std::string Rd = util::reg_string(code, 12, 15, settings);
    const std::string Rn = util::reg_string(code, 16, 19, settings);

    const std::string addressing_mode = shifters::ls_misc(code, settings);

    return util::make_string("STR", util::cond(code, settings), "D ", Rd, ", ", addressing_mode);
}