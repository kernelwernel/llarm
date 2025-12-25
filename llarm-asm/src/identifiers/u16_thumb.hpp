#pragma once 

#include "../id/instruction_id.hpp"

#include "shared/types.hpp"

namespace internal::ident::u16_thumb {
    thumb_id thumb(const u16 code);

    thumb_id bits_000(const u16 code);
    thumb_id bits_001(const u16 code);
    thumb_id bits_010(const u16 code);
    thumb_id bits_011(const u16 code);
    thumb_id bits_100(const u16 code);
    thumb_id bits_101(const u16 code);
    thumb_id bits_110(const u16 code);
    thumb_id bits_111(const u16 code);
}