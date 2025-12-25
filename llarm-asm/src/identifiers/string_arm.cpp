#include "string_arm.hpp"
#include "../id/instruction_id.hpp"

#include "../interpreter/interpreter.hpp"
#include "llarm-asm/src/interpreter/tokens.hpp"
#include "shared/types.hpp"
#include "shared/util.hpp"

using namespace internal;
using namespace interpreter;
using enum token_enum;

arm_id ident::string_arm::arm(const std::string &code) {

}