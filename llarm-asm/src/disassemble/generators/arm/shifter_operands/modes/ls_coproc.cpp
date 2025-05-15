#include "../shifters.hpp"
#include "../../../util.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"

#include <string>

using namespace internal;


std::string shifters::ls_coproc_imm(const u32 code) {
    const std::string Rn = util::reg_string(code, 16, 19);
    const u16 offset_8 = shared::util::bit_range<u16>(code, 0, 7) * 4;

    const char* op = (shared::util::bit_fetch(code, 23) ? "" : "-");

    return util::make_string("[", Rn, ", #", op, util::hex(offset_8), "]");
}


std::string shifters::ls_coproc_imm_pre(const u32 code) {
    return (ls_coproc_imm(code) + "!");
}


std::string shifters::ls_coproc_imm_post(const u32 code) {
    const std::string Rn = util::reg_string(code, 16, 19);
    const u16 offset_8 = shared::util::bit_range<u16>(code, 0, 7) * 4;

    const char* op = (shared::util::bit_fetch(code, 23) ? "" : "-");

    return util::make_string("[", Rn, "], #", op, util::hex(offset_8), "");
}


std::string shifters::ls_coproc_unindexed(const u32 code) {
    const std::string Rn = util::reg_string(code, 16, 19);
    const u8 option = shared::util::bit_range<u8>(code, 0, 7);

    return util::make_string("[", Rn, "], { ", option, " }");
}