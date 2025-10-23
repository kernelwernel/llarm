#pragma once

#include "../shifter_id.hpp"

#include "shared/types.hpp"

namespace internal::u32_shifters {
    shifter_enum load_store(const u32 code);
    shifter_enum data_processing(const u32 code);
    shifter_enum load_store_multiple(const u32 code);
    shifter_enum load_store_misc(const u32 code);
    shifter_enum load_store_coprocessor(const u32 code);
    shifter_enum vfp_single(const u32 code);
    shifter_enum vfp_single_monadic(const u32 code);
    shifter_enum vfp_double(const u32 code);
    shifter_enum vfp_double_monadic(const u32 code);
    shifter_enum vfp_ls_multiple(const u32 code);

    shifter_enum identify_shifter(const u32 code);
    shifter_enum identify_shifter(const shifter_category shift_category, const u32 code);
}