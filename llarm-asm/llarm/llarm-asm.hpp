#pragma once

#include "src/assemble/assemble.hpp"
#include "src/settings.hpp"
#include "src/id/instruction_id.hpp"
#include "src/identifiers/u32_shifters.hpp"
#include "src/identifiers/u32_arm.hpp"
#include "src/identifiers/u16_thumb.hpp"
#include "src/identifiers/string_arm.hpp"
#include "src/identifiers/string_thumb.hpp"
#include "src/identifiers/string_shifters.hpp"
#include "src/disassemble/disassemble.hpp"
#include "src/validation/u32_arm.hpp"
#include "src/validation/string_arm.hpp"
#include "src/validation/string_thumb.hpp"
#include "src/validation/u16_thumb.hpp"
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
        return internal::ident::u32_arm::arm(raw_code);
    }

    inline arm_id identify_arm(const std::string &code) {
        return internal::ident::string_arm::arm(code);
    }

    inline std::string identify_arm_string(const u32 raw_code) {
        const arm_id id = internal::ident::u32_arm::arm(raw_code);
        return internal::disassemble::arm_id_to_string(id);
    }

    inline thumb_id identify_thumb(const u16 raw_code) {
        return internal::ident::u16_thumb::thumb(raw_code);
    }

    inline thumb_id identify_thumb(const std::string &code) {
        return internal::ident::string_thumb::thumb(code);
    }

    inline shifter_id identify_shifter(const u32 raw_code) {
        return internal::ident::u32_shifters::identify_shifter(raw_code);
    }

    inline shifter_id identify_shifter(const std::string &code) {
        return internal::ident::string_shifters::identify_shifter(code);
    }

    inline shifter_id identify_shifter(const shifter_category category, const u32 raw_code) {
        return internal::ident::u32_shifters::identify_shifter(category, raw_code);
    }

    //inline u32 generate_arm(const id::arm code, const params params) {
    //    
    //}

    inline std::string disassemble_arm(
        const u32 code, 
        const u32 PC = 0, 
        const settings settings = default_settings()
    ) {
        return internal::disassemble::arm(code, PC, settings);
    }

    inline std::string disassemble_thumb(
        const u16 code,
        const u32 PC = 0,
        const settings settings = default_settings()
    ) {
        return internal::disassemble::thumb(code, PC, settings);
    }

    inline u32 assemble_arm(const std::string &code, const u32 PC = 0) {
        return internal::assemble::arm(code, PC);
    }

    inline bool is_arm_instruction_valid(const u32 code) {
        return internal::validation::u32_arm::is_arm_instruction_valid(code);
    }

    inline bool is_arm_instruction_valid(const std::string &code) {
        return internal::validation::string_arm::is_arm_instruction_valid(code);
    }

    inline bool is_thumb_instruction_valid(const u16 code) {
        return internal::validation::u16_thumb::is_thumb_instruction_valid(code);
    }

    inline bool is_thumb_instruction_valid(const std::string &code) {
        return internal::validation::string_thumb::is_thumb_instruction_valid(code);
    }

    inline std::string arm_id_to_string(const arm_id id) {
        return internal::disassemble::arm_id_to_string(id);
    }

    inline std::string thumb_id_to_string(const thumb_id id) {
        return internal::disassemble::thumb_id_to_string(id);
    }
}