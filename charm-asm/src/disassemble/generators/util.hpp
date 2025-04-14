#pragma once

#include <charm/internal/shared/types.hpp>


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
        R15
    };

    reg_id identify_reg(const u8 code);

    reg_id identify_reg(const u16 code, const u8 start, const u8 end);

    std::string reg_to_string(const reg_id id, const bool alias);



    // i'm sorry to whoever is reading this code.
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
    std::string make_instruction(Args&&... args) {
        std::string result;
        
        // calculate total size needed
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

    // TODO benchmark this


}