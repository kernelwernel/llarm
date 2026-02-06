#include "assemble.hpp"

#include "../interpreter/IR.hpp"
#include "arm/generators.hpp"
#include <llarm/shared/types.hpp>

#include <string>

using namespace internal;

u32 assemble::arm(const std::string &code, const u32 PC) {
    return arm(IR::generate(code, PC));
}


//u16 assemble::thumb(const std::string &code) {
//    //return thumb(IR::generate_thumb(code));
//}


u32 assemble::arm(const IR_arm_struct &IR) {
    return generators::arm(IR);
}

//
//u16 assemble::thumb(const IR_thumb_struct &IR) {
//    const operand_struct args = args::IR_to_args(IR);
//    //return generators::thumb(IR.id, args);
//}