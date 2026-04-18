#pragma once

#include "../settings.hpp"
#include "../id/instruction_id.hpp"

#include <llarm/shared/types.hpp>

#include <string>

constexpr const char* UNDEFINED = "undefined";
constexpr const char* ERROR = "error";

namespace internal::disassemble {

    std::string thumb_generate(const u32 code, const u32 PC, const settings& settings);
    std::string arm_generate(const u32 code, const u32 PC, const settings& settings);

    std::string thumb(const u32 code, const u32 PC = 0, const settings& settings = default_dis_settings());
    std::string arm(const u32 code, const u32 PC = 0, const settings& settings = default_dis_settings());

    std::string thumb_id_to_string(const thumb_id id);
    std::string arm_id_to_string(const arm_id id);
}