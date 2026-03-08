#include "assemble.hpp"
#include "../interpreter/IR.hpp"
#include "arm/generators.hpp"
#include "thumb/generators.hpp"
#include "../validation/string_arm.hpp"
#include "../validation/string_thumb.hpp"

#include <llarm/shared/types.hpp>

#include <string>

using namespace internal;

u32 assemble::arm(const std::string &code, const u32 PC) {
    return arm(IR::generate(code, PC));
}


u32 assemble::arm(const IR_arm_struct &IR) {
    if (validation::string_arm::is_arm_instruction_valid(IR) == false) {
        return ARM_UNDEFINED;
    }

    return generators::arm(IR);
}


u32 assemble::thumb(const std::string &code, const u32 PC) {
    return thumb(IR::generate_thumb(code, PC));
}


u32 assemble::thumb(const IR_thumb_struct &IR) {
    if (validation::string_thumb::is_thumb_instruction_valid(IR) == false) {
        return THUMB_UNDEFINED;
    }

    return generators::thumb(IR);
}