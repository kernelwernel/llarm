#include <string>
#include "../instruction_id.hpp"
#include "../interpreter/interpreter.hpp"

using namespace internal;

namespace validation::string_arm {
    bool is_arm_instruction_valid(const std::string &code);
    bool is_arm_instruction_valid(const id::arm id, const interpreter::lexemes_t &lexemes);
}