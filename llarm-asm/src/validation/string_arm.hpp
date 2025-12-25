#include "../interpreter/IR.hpp"
#include <string>

using namespace internal;

namespace validation::string_arm {
    bool is_arm_instruction_valid(const std::string &code, const u32 PC = 0);
    bool is_arm_instruction_valid(const IR_arm_struct &IR);
}