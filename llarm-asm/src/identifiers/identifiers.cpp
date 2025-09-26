#include "identifiers.hpp"
#include "string_arm.hpp"
#include "string_thumb.hpp"
#include "u32_arm.hpp"
#include "u16_thumb.hpp"

using namespace internal;

id::arm identifiers::arm(const std::string &code) {
    return string_arm::arm(code);
}


id::thumb identifiers::thumb(const std::string &code) {
    return string_thumb::thumb(code);
}


id::arm identifiers::arm(const u32 code) {
    return u32_arm::arm(code);
}


id::thumb identifiers::thumb(const u16 code) {
    return u16_thumb::thumb(code);
}