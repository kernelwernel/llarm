#pragma once

#include "tokens.hpp"

#include "shared/string_view.hpp"

namespace matchers {
    REG reg(const llarm::string_view str);
    PSR cpsr_spsr(const llarm::string_view str);
    IMM immediate(const llarm::string_view str);
    token character(const llarm::string_view str);
    token address_mode(const llarm::string_view str);
}