#pragma once 

#include "../id/instruction_id.hpp"

#include <llarm/shared/types.hpp>

namespace internal::ident::u16_thumb {
    thumb_id thumb(const u32 code);

    thumb_id bits_000(const u32 code);
    thumb_id bits_001(const u32 code);
    thumb_id bits_010(const u32 code);
    thumb_id bits_011(const u32 code);
    thumb_id bits_100(const u32 code);
    thumb_id bits_101(const u32 code);
    thumb_id bits_110(const u32 code);
    thumb_id bits_111(const u32 code);
}