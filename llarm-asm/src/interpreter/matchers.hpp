#pragma once

#include "tokens.hpp"

#include <nonstd/string_view.hpp>

namespace matchers {
    REG reg(sv str);
    PSR cpsr_spsr(const sv str);
    IMM immediate(const sv str);
    token_enum character(const sv str);
    token_enum address_mode(const sv str);
    bool comment(const sv str);
}