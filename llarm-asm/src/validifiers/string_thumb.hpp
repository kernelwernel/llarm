#include <string>
#include "../instruction_id.hpp"
#include "../interpreter/interpreter.hpp"

using namespace internal;

namespace validation::string_thumb {
    bool is_thumb_instruction_valid(const std::string &code);
    bool is_thumb_instruction_valid(const id::thumb id, const interpreter::lexemes_t &lexemes);
}