#include "disassemble.hpp"
#include "../identifiers/identifiers.hpp"
#include "../instruction_id.hpp"
#include "generators/generators.hpp"

#include <charm/internal/shared/types.hpp>

#include <string>

using namespace internal;

std::string disassemble::thumb(const u16 code) {
    const id::thumb id = identifiers::thumb(code);

    switch (id) {
        case id::thumb::ADC: return generators::thumb::math::ADC(code);
        default: return "lol";
    }
}