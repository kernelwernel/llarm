#include "../identifiers/bin_thumb.hpp"

#include <llarm/shared/types.hpp>

using namespace internal;

namespace internal::validation::bin_thumb {
    bool is_thumb_instruction_valid(const u32 code); 
    bool is_thumb_instruction_valid(const thumb_id id); 
}