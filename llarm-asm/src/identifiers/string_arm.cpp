#include "string_arm.hpp"
#include "../id/instruction_id.hpp"
#include "../interpreter/mnemonic_arm.hpp"
#include "../interpreter/interpreter.hpp"

#include <llarm/shared/types.hpp>

using namespace internal;

arm_id ident::string_arm::arm(const std::string &code) {
    const std::string assembly = llarm::util::to_upper(code);
    const sv mnemonic = interpreter::fetch_instruction(assembly);

    return mnemonic_arm::fetch_arm_id(code, mnemonic, assembly);
}