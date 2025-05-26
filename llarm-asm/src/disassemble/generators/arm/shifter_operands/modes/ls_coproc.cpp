#include "../shifters.hpp"
#include "../../../util.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"

#include <string>

using namespace internal;


std::string shifters::ls_coproc_imm(const u32 code, const settings settings) {
    const std::string Rn = util::reg_string(code, 16, 19, settings);
    const u16 offset_8 = shared::util::bit_range<u16>(code, 0, 7) * 4;

    if ((offset_8 == 0) && settings.remove_nulls) {
        return util::make_string("[", Rn, "]");
    }

    const char* op = (shared::util::bit_fetch(code, 23) ? "" : "-");

    return util::make_string("[", Rn, ", #", op, util::hex(offset_8, settings), "]");
}


std::string shifters::ls_coproc_imm_pre(const u32 code, const settings settings) {
    return (ls_coproc_imm(code, settings) + "!");
}


std::string shifters::ls_coproc_imm_post(const u32 code, const settings settings) {
    const std::string Rn = util::reg_string(code, 16, 19, settings);
    const u16 offset_8 = shared::util::bit_range<u16>(code, 0, 7) * 4;

    if ((offset_8 == 0) && settings.remove_nulls) {
        return util::make_string("[", Rn, "]");
    }

    const char* op = (shared::util::bit_fetch(code, 23) ? "" : "-");

    return util::make_string("[", Rn, "], #", op, util::hex(offset_8, settings), "");
}


std::string shifters::ls_coproc_unindexed(const u32 code, const settings settings) {
    const std::string Rn = util::reg_string(code, 16, 19, settings);
    const u8 option = shared::util::bit_range<u8>(code, 0, 7);

    return util::make_string("[", Rn, "], { ", option, " }"); // not sure if this is supposed to be a hex
}