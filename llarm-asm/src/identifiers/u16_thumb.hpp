
#include "../instruction_id.hpp"

#include "shared/types.hpp"

using namespace internal;

namespace u16_thumb {
    id::thumb thumb(const u16 code);

    id::thumb bits_000(const u16 code);
    id::thumb bits_001(const u16 code);
    id::thumb bits_010(const u16 code);
    id::thumb bits_011(const u16 code);
    id::thumb bits_100(const u16 code);
    id::thumb bits_101(const u16 code);
    id::thumb bits_110(const u16 code);
    id::thumb bits_111(const u16 code);
}