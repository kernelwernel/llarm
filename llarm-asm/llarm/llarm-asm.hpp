#pragma once

#include "src/assemble/assemble.hpp"
#include "src/settings.hpp"
#include "src/id/instruction_id.hpp"
#include "src/identifiers/bin_shifters.hpp"
#include "src/identifiers/bin_arm.hpp"
#include "src/identifiers/bin_thumb.hpp"
#include "src/identifiers/string_arm.hpp"
#include "src/identifiers/string_thumb.hpp"
#include "src/identifiers/string_shifters.hpp"
#include "src/disassemble/disassemble.hpp"
#include "src/validation/bin_arm.hpp"
#include "src/validation/string_arm.hpp"
#include "src/validation/string_thumb.hpp"
#include "src/validation/bin_thumb.hpp"
#include "src/settings.hpp"


namespace llarm::as {
    // setting aliases, ignore these
    using settings = internal::settings;
    using default_func = settings(*)();
    inline default_func default_settings = &internal::default_dis_settings;

    // alternatives in case it's under C++17
    using arm_id = internal::arm_id;
    using thumb_id = internal::thumb_id;
    using shifter_id = internal::shifter_id;
    using shifter_category = internal::shifter_category;

    //enum class arm : internal::id::arm {};
    //enum class thumb : internal::id::thumb {};

    inline arm_id identify_arm(const u32 raw_code) {
        return internal::ident::bin_arm::arm(raw_code);
    }

    inline arm_id identify_arm(const std::string& code) {
        return internal::ident::string_arm::arm(code);
    }

    inline std::string identify_arm_string(const u32 raw_code) {
        const arm_id id = internal::ident::bin_arm::arm(raw_code);
        return internal::disassemble::arm_id_to_string(id);
    }

    inline thumb_id identify_thumb(const u32 raw_code) {
        return internal::ident::bin_thumb::thumb(raw_code);
    }

    inline thumb_id identify_thumb(const std::string& code) {
        return internal::ident::string_thumb::thumb(code);
    }

    inline std::string identify_thumb_string(const u32 raw_code) {
        const thumb_id id = internal::ident::bin_thumb::thumb(raw_code);
        return internal::disassemble::thumb_id_to_string(id);
    }

    inline shifter_id identify_shifter(const u32 raw_code) {
        return internal::ident::bin_shifters::identify_shifter(raw_code);
    }

    inline shifter_id identify_shifter(const std::string& code) {
        return internal::ident::string_shifters::identify_shifter(code);
    }

    inline shifter_id identify_shifter(const shifter_category category, const u32 raw_code) {
        return internal::ident::bin_shifters::identify_shifter(category, raw_code);
    }

    //inline u32 generate_arm(const id::arm code, const params params) {
    //    
    //}

    inline std::string disassemble_arm(
        const u32 code, 
        const u32 PC = 0, 
        const settings config = default_settings()
    ) {
        return internal::disassemble::arm(code, PC, config);
    }

    inline std::string disassemble_thumb(
        const u32 code,
        const u32 PC = 0,
        const settings config = default_settings()
    ) {
        return internal::disassemble::thumb(code, PC, config);
    }

    inline u32 assemble_arm(const std::string& code, const u32 PC = 0) {
        return internal::assemble::arm(code, PC);
    }

    inline u32 assemble_thumb(const std::string& code, const u32 PC = 0) {
        return internal::assemble::thumb(code, PC);
    }

    inline bool is_arm_instruction_valid(const u32 code) {
        return internal::validation::bin_arm::is_arm_instruction_valid(code);
    }

    inline bool is_arm_instruction_valid(const std::string& code) {
        return internal::validation::string_arm::is_arm_instruction_valid(code);
    }

    inline bool is_thumb_instruction_valid(const u32 code) {
        return internal::validation::bin_thumb::is_thumb_instruction_valid(code);
    }

    inline bool is_thumb_instruction_valid(const std::string& code) {
        return internal::validation::string_thumb::is_thumb_instruction_valid(code);
    }

    inline std::string arm_id_to_string(const arm_id id) {
        return internal::disassemble::arm_id_to_string(id);
    }

    inline std::string thumb_id_to_string(const thumb_id id) {
        return internal::disassemble::thumb_id_to_string(id);
    }

    inline std::string shifter_id_to_string(const shifter_id id) {
        return internal::ident::bin_shifters::shifter_id_to_string(id);
    }

    inline std::string code_to_shifter_string(const u32 code) {
        return internal::ident::bin_shifters::code_to_shifter_string(code);
    }
}