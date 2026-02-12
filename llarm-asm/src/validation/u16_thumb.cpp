#include "u16_thumb.hpp"

#include "../identifiers/u16_thumb.hpp"

#include <llarm/shared/types.hpp>

using namespace internal;

// binary thumb instructions don't really have much of a way to "fail".
// Even "faulty" arguments are encoded in ways where it can't be considered
// as an error. So the only real failure for a thumb instruction would
// be to identify an undefined or unknown instruction (me thinks)

bool validation::u16_thumb::is_thumb_instruction_valid(const u16 code) {
    const thumb_id id = ident::u16_thumb::thumb(code);
    return is_thumb_instruction_valid(id);
}


bool validation::u16_thumb::is_thumb_instruction_valid(const thumb_id id) {
    return (
        (id != thumb_id::UNDEFINED) &&
        (id != thumb_id::UNKNOWN)
    );
}