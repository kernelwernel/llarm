#pragma once

#include <string_view>
#include <iostream>

#include "types.hpp"

namespace llarm::out {
    constexpr sv
        black_bg = "\x1B[48;2;0;0;0m",
        bold     = "\033[1m",
        ansiexit = "\x1B[0m",
        green    = "\x1B[38;2;94;214;114m",
        orange   = "\x1B[38;2;255;180;5m",
        red      = "\x1B[38;2;239;75;75m",
        blue     = "\x1B[38;2;00;59;193m",
        grey     = "\x1B[38;2;108;108;108m",
        misc     = "\x1B[48;2;255;255;255m";


    template <typename... Args>
    static void info(const Args&... message) {
        std::cout << bold << "[" << blue << "INFO" << ansiexit << bold << "]" << ansiexit << " ";
        ((std::cout << message), ...);
        std::printf("\n");
    }

    template <typename... Args>
    static void warning(const Args&... message) {
        std::cout << bold << "[" << orange << "WARNING" << ansiexit << bold << "]" << ansiexit << " ";
        ((std::cout << message), ...);
        std::printf("\n");
    }

    template <typename... Args>
    static void failed_assert(const Args&... message) {
        std::cout << bold << "[" << grey << "FAILED ASSERT" << ansiexit << bold << "]" << ansiexit << " ";
        ((std::cout << message), ...);
        std::printf("\n");
    }

    template <typename... Args>
    static void unpredictable(const Args&... message) {
        std::cout << bold << "[" << grey << "UNPREDICTABLE" << ansiexit << bold << "]" << ansiexit << " ";
        ((std::cout << message), ...);
        std::printf("\n");
    }

    template <typename... Args>
    [[noreturn]] static void error(const Args&... message) {
        std::cout << bold << "[" << red << "ERROR" << ansiexit << bold << "]" << ansiexit << " ";
        ((std::cout << message),...);
        std::printf("\n");
        std::exit(1);
    }


    inline void dev_warning(const char* error) {
        std::cout << bold << "[" << red << "DEV WARNING" << ansiexit << bold << "]" << ansiexit << " ";
        std::printf("%s", error);
    }


    [[noreturn]] inline void dev_error(const char* error) {
        std::cout << bold << "[" << red << "DEV ERROR" << ansiexit << bold << "]" << ansiexit << " ";
        std::printf("%s", error);
        std::exit(1);
    }
}