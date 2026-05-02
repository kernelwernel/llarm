#pragma once

#include "../id/shifter_id.hpp"

#include <llarm/shared/types.hpp>

namespace internal::ident::bin_shifters {
    shifter_id load_store(const u32 code);
    shifter_id data_processing(const u32 code);
    shifter_id load_store_multiple(const u32 code);
    shifter_id load_store_misc(const u32 code);
    shifter_id load_store_coprocessor(const u32 code);
    shifter_id vfp_single(const u32 code);
    shifter_id vfp_single_monadic(const u32 code);
    shifter_id vfp_double(const u32 code);
    shifter_id vfp_double_monadic(const u32 code);
    shifter_id vfp_ls_multiple(const u32 code);
    shifter_id usat_special(const u32 code);

    shifter_id identify_shifter(const u32 code);
    shifter_id identify_shifter(const shifter_category shift_category, const u32 code);

    std::string code_to_shifter_string(const u32 code);
    std::string shifter_id_to_string(const shifter_id id);
}