#pragma once

#include "shared/types.hpp"

namespace internal::util {
    enum class reg_id : u8 {
        R0,
        R1,
        R2,
        R3,
        R4, 
        R5, 
        R6,
        R7,
        R8,
        R9,
        R10,
        R11,
        R12,
        R13,
        R14,
        R15,
        S0,
        S1,
        S2,
        S3,
        S4,
        S5,
        S6,
        S7,
        S8,
        S9,
        S10,
        S11,
        S12,
        S13,
        S14,
        S15,
        S16,
        S17,
        S18,
        S19,
        S20,
        S21,
        S22,
        S23,
        S24,
        S25,
        S26,
        S27,
        S28,
        S29,
        S30,
        S31,
        D0,
        D1,
        D2,
        D3,
        D4,
        D5,
        D6,
        D7,
        D8,
        D9,
        D10,
        D11,
        D12,
        D13,
        D14,
        D15
    };

    enum class prefix : u8 {
        R, // for regular ARM registers
        S, // for 32-bit VFP registers
        D  // for 64-bit VFP registers
    };

    reg_id identify_reg(const u8 reg_bits, const prefix prefix = prefix::R);

    reg_id identify_reg(const u16 code, const u8 start, const u8 end, const prefix prefix = prefix::R);

    std::string reg_list(const u8 list, const sv extra = "");

    std::string fetch_cond(const u8 cond);

    std::string reg_id_to_string(const reg_id id, const bool alias = false);

    std::string reg_string(const u32 code, const u8 start, const u8 end, const prefix prefix = prefix::R, const bool alias = false);

    std::string vfp_reg_string_bits(const u32 code, const u8 start, const u8 end, const bool bottom_bit);

    std::string reg_string_bits(const u32 code, const u8 start, const u8 end, const bool top_bit);

    std::string hex(const u32 integer);

    // i'm sorry to whoever is reading both of these functions.

    template<typename T>
    void append_arg(std::string& result, T&& arg) {
        if constexpr (std::is_arithmetic_v<std::decay_t<T>>) {
            // handle numbers
            result += std::to_string(std::forward<T>(arg));
        } else {
            // handle strings/string_views
            result += std::forward<T>(arg);
        }
    }

    // https://quick-bench.com/q/No_nYrHbcGwK5JTFl-qJtJ0ncc0
    template<typename... Args>
    std::string make_string(Args&&... args) {
        std::string result;
        
        size_t total_size = 0;
        ([&](auto&& arg) {
            if constexpr (std::is_arithmetic_v<std::decay_t<decltype(arg)>>) {
                total_size += std::to_string(arg).size();
            } else {
                total_size += std::string_view(arg).size();
            }
        }(args), ...);

        result.reserve(total_size);

        // append all arguments
        (append_arg(result, std::forward<Args>(args)), ...);
        
        return result;
    }
}