#include "string_arm.hpp"
#include "../id/instruction_id.hpp"
#include "../interpreter/IR.hpp"

#include <llarm/shared/types.hpp>

using namespace internal;

arm_id ident::string_arm::arm(const std::string &code, const u32 PC) {
    const IR_arm_struct IR = IR::generate(code, PC);
    return IR.mnemonic.id;
}