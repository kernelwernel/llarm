#include "assemble.hpp"

#include "../instruction_id.hpp"
#include "../identifiers/string_thumb.hpp"
#include "../identifiers/interpreter.hpp"

#include <string>
#include "shared/types.hpp"

using namespace internal;

u32 assemble::arm(const std::string &code) {

}


u16 assemble::thumb(const std::string &code) {
    const id::thumb id = string_thumb::thumb(code);
    const interpreter::lexemes_t lexemes = interpreter::analyze(code);

    
}