#include "../identifiers/u16_thumb.hpp"

#include <llarm/shared/types.hpp>

using namespace internal;

namespace internal::valid::u16_thumb {
    bool is_thumb_instruction_valid(const u16 code); 
    bool is_thumb_instruction_valid(const thumb_id id); 
}