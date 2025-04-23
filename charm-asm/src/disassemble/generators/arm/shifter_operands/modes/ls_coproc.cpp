#include "../shifters.hpp"
#include "../../../util.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"

#include <string>

using namespace internal;


std::string shifters::ls_coproc_imm(const u32 code) {
    const std::string Rn = util::reg_string(code, 16, 19);
    const u16 offset_8 = shared::util::bit_fetcher(code, 0, 7) * 4;

    const char* op = (((code & (1 << 23)) == 0) ? "-" : "");

    return util::make_string("[", Rn, ", #", op, util::hex(offset_8), "]");
}


std::string shifters::ls_coproc_imm_pre(const u32 code) {
    return (ls_coproc_imm(code) + "!");
}


std::string shifters::ls_coproc_imm_post(const u32 code) {
    const std::string Rn = util::reg_string(code, 16, 19);
    const u16 offset_8 = shared::util::bit_fetcher(code, 0, 7) * 4;

    const char* op = (((code & (1 << 23)) == 0) ? "-" : "");

    return util::make_string("[", Rn, "], #", op, util::hex(offset_8), "");
}


std::string shifters::ls_coproc_unindexed(const u32 code) {
    const std::string Rn = util::reg_string(code, 16, 19);
    const u8 option = shared::util::bit_fetcher(code, 0, 7);

    //const char* op = (((code & (1 << 23)) == 0) ? "-" : "");

    return util::make_string("[", Rn, "], { ", option, " }");
}