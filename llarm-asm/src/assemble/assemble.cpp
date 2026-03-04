#include "assemble.hpp"
#include "../interpreter/IR.hpp"
#include "arm/generators.hpp"
#include "thumb/generators.hpp"

#include <llarm/shared/types.hpp>

#include <string>

using namespace internal;

u32 assemble::arm(const std::string &code, const u32 PC) {
    return arm(IR::generate(code, PC));
}


u32 assemble::arm(const IR_arm_struct &IR) {
    return generators::arm(IR);
}


u16 assemble::thumb(const std::string &code, const u32 PC) {
    return thumb(IR::generate_thumb(code, PC));
}


u16 assemble::thumb(const IR_thumb_struct &IR) {
    return generators::thumb(IR);
}