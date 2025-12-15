#pragma once

#include "../../settings.hpp"

#include <string>

#include "shared/types.hpp"
#include "shared/string_view.hpp"

namespace internal::util {
    enum class reg_id : u8 {
        NULL_REG,
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
        D15,
        C0,
        C1,
        C2,
        C3,
        C4,
        C5,
        C6,
        C7,
        C8,
        C9,
        C10,
        C11,
        C12,
        C13,
        C14,
        C15,
        P0,
        P1,
        P2,
        P3,
        P4,
        P5,
        P6,
        P7,
        P8,
        P9,
        P10,
        P11,
        P12,
        P13,
        P14,
        P15
    };

    enum class prefix : u8 {
        R, // for regular ARM registers
        S, // for 32-bit VFP registers
        D, // for 64-bit VFP registers
        C, // for coprocessor registers 
        P  // for coprocessor processor number, 
           // the reason why this is encorporated
           // with the registers is because it
           // has the same effective syntax and
           // utility as the above registers,
           // so while the usage and context is
           // different, the overall syntax isn't.
    };

    reg_id identify_reg(const u8 reg_bits, const prefix prefix = prefix::R);

    reg_id identify_reg(const u32 code, const u8 start, const u8 end, const prefix prefix = prefix::R);

    std::string reg_list(const u16 list, const settings settings, const reg_id extra = reg_id::NULL_REG);

    std::string raw_cond(const u8 cond, const settings settings);

    std::string cond(const u32 code, const settings settings);

    std::string reg_id_to_string(const reg_id id, const settings settings);

    std::string vfp_reg_id_to_string(const reg_id id);

    std::string reg_string(const u32 code, const u8 start, const u8 end, const settings settings, const prefix prefix = prefix::R);

    std::string vfp_reg_string_bits(const u32 code, const u8 start, const u8 end, const bool bottom_bit, const settings settings);

    std::string reg_string_bits(const u32 code, const u8 start, const u8 end, const bool top_bit, const settings settings);

    std::string vfp_register_list(const u8 first_reg, const u8 offset, const settings settings, const prefix prefix);

    std::string hex(const u32 integer, const settings settings);

    //std::string hex_signed(const i32 integer, const settings settings);

    void to_lower(std::string &str);

    u32 thumb_sign_extend(u32 value, const u8 sign_index, const u32 PC);


    // i'm deeply sorry to whoever is reading this absolute mess, same for the function below.
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

    /**
     *  comparisons of string concatenation methods:
     *     https://quick-bench.com/q/No_nYrHbcGwK5JTFl-qJtJ0ncc0
     *  
     *  comparisons of string variation inputs for the string concatenator:
     *     https://quick-bench.com/q/a8aNl-AclWkONwP0JPcRSwb3Y6U
     */
    template<typename... Args>
    std::string make_string(Args&&... args) {
        std::string result;

        size_t total_size = 0;
        ([&](auto&& arg) {
            if constexpr (std::is_arithmetic_v<std::decay_t<decltype(arg)>>) {
                total_size += std::to_string(arg).size();
            } else {
                total_size += llarm::string_view(arg).size();
            }
        }(args), ...);

        result.resize(total_size);

        // append all arguments
        (append_arg(result, std::forward<Args>(args)), ...);
        
        return result;
    }
}