#include "string_arm.hpp"
#include "../id/instruction_id.hpp"

#include "llarm-asm/src/interpreter/IR.hpp"
#include "shared/types.hpp"

using namespace internal;

arm_id ident::string_arm::arm(const std::string &code, const u32 PC) {
    const IR_arm_struct IR = IR::generate(code, PC);
    return IR.mnemonic.id;
}