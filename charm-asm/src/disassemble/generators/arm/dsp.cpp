#include "../generators.hpp"
#include "../util.hpp"
#include "shifter_operands/shifters.hpp"
#include "../patterns/patterns.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"

#include <string>

using namespace internal;


std::string generators::arm::dsp::LDRD(const u32 code) {
    const std::string Rd = util::reg_string(code, 12, 15);

    const std::string addressing_mode = shifters::ls_misc_shifter(code);

    return util::make_string("LDR", util::cond(code), "D ", Rd, ", ", addressing_mode);
}


std::string generators::arm::dsp::MCRR(const u32 code) {
    const std::string coproc = util::reg_string(code, 8, 11, util::prefix::P);

    const std::string Rd = util::reg_string(code, 12, 15);
    const std::string Rn = util::reg_string(code, 16, 19);
    const std::string CRm = util::reg_string(code, 0, 3, util::prefix::C);

    const u8 opcode = shared::util::bit_fetcher<u8>(code, 4, 7);

    return util::make_string("MCRR", util::cond(code), " ", coproc, ", #", opcode, ", ", Rd, ", ", Rn, ", ", CRm);
}


std::string generators::arm::dsp::MRRC(const u32 code) {
    const std::string coproc = util::reg_string(code, 8, 11, util::prefix::P);

    const std::string Rd = util::reg_string(code, 12, 15);
    const std::string Rn = util::reg_string(code, 16, 19);
    const std::string CRm = util::reg_string(code, 0, 3, util::prefix::C);

    const u8 opcode = shared::util::bit_fetcher<u8>(code, 4, 7);

    return util::make_string("MRRC", util::cond(code), " ", coproc, ", #", opcode, ", ", Rd, ", ", Rn, ", ", CRm);
}


std::string generators::arm::dsp::PLD(const u32 code) {
    const std::string addressing_mode = shifters::ls_shifter(code);
    return util::make_string("PLD ", addressing_mode);
}


std::string generators::arm::dsp::QADD(const u32 code) {
    return patterns::dsp_Rd_Rm_Rn(code, "QADD");
}


std::string generators::arm::dsp::QDADD(const u32 code) {
    return patterns::dsp_Rd_Rm_Rn(code, "QDADD");
}


std::string generators::arm::dsp::QDSUB(const u32 code) {
    return patterns::dsp_Rd_Rm_Rn(code, "QDSUB");
}


std::string generators::arm::dsp::QSUB(const u32 code) {
    return patterns::dsp_Rd_Rm_Rn(code, "QSUB");
}


std::string generators::arm::dsp::SMLA(const u32 code) {
    const char x = ((code & (1 << 5)) ? 'T' : 'B');
    const char y = ((code & (1 << 6)) ? 'T' : 'B');

    const std::string Rd = util::reg_string(code, 16, 19);
    const std::string Rm = util::reg_string(code, 0, 3);
    const std::string Rs = util::reg_string(code, 8, 11);
    const std::string Rn = util::reg_string(code, 12, 15);

    return util::make_string("SMLA", x, y, util::cond(code), " ", Rd, ", ", Rm, ", ", Rs, ", ", Rn);
}


std::string generators::arm::dsp::SMLAL(const u32 code) {
    const char x = ((code & (1 << 5)) ? 'T' : 'B');
    const char y = ((code & (1 << 6)) ? 'T' : 'B');

    const std::string Rm = util::reg_string(code, 0, 3);
    const std::string Rs = util::reg_string(code, 8, 11);
    const std::string RdHi = util::reg_string(code, 16, 19);
    const std::string RdLo = util::reg_string(code, 12, 15);

    return util::make_string("SMLAL", x, y, util::cond(code), " ", RdLo, ", ", RdHi, ", ", Rm, ", ", Rs);
}


std::string generators::arm::dsp::SMLAW(const u32 code) {
    const char y = ((code & (1 << 6)) ? 'T' : 'B');

    const std::string Rd = util::reg_string(code, 16, 19);
    const std::string Rm = util::reg_string(code, 0, 3);
    const std::string Rs = util::reg_string(code, 8, 11);
    const std::string Rn = util::reg_string(code, 12, 15);

    return util::make_string("SMLAW", y, util::cond(code), " ", Rd, ", ", Rm, ", ", Rs, ", ", Rn);
}


std::string generators::arm::dsp::SMUL(const u32 code) {
    const char x = ((code & (1 << 5)) ? 'T' : 'B');
    const char y = ((code & (1 << 6)) ? 'T' : 'B');

    const std::string Rm = util::reg_string(code, 0, 3);
    const std::string Rs = util::reg_string(code, 8, 11);
    const std::string Rd = util::reg_string(code, 16, 19);

    return util::make_string("SMUL", x, y, util::cond(code), " ", Rd, ", ", Rm, ", ", Rs);
}


std::string generators::arm::dsp::SMULW(const u32 code) {
    const char y = ((code & (1 << 6)) ? 'T' : 'B');

    const std::string Rd = util::reg_string(code, 16, 19);
    const std::string Rm = util::reg_string(code, 0, 3);
    const std::string Rs = util::reg_string(code, 8, 11);

    return util::make_string("SMULW", y, util::cond(code), " ", Rd, ", ", Rm, ", ", Rs);
}


std::string generators::arm::dsp::STRD(const u32 code) {
    const std::string Rd = util::reg_string(code, 12, 15);
    const std::string Rn = util::reg_string(code, 16, 19);

    const std::string addressing_mode = shifters::ls_misc_shifter(code);

    return util::make_string("STR", util::cond(code), "D ", Rd, ", ", addressing_mode);
}