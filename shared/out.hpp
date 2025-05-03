#pragma once

#include <string_view>
#include <iostream>
//#include <source_location>

#include "types.hpp"

namespace shared::out {
    constexpr sv
        black_bg = "\x1B[48;2;0;0;0m",
        bold     = "\033[1m",
        ansiexit = "\x1B[0m",
        green    = "\x1B[38;2;94;214;114m",
        orange   = "\x1B[38;2;255;180;5m",
        red      = "\x1B[38;2;239;75;75m",
        blue     = "\x1B[38;2;00;59;193m",
        misc     = "\x1B[48;2;255;255;255m";


    //static void info(const auto ...message) noexcept {
    //    std::cout << black_bg << bold << "[" << blue << "INFO" << ansiexit << bold << black_bg << "]" << ansiexit << " ";
    //    ((std::cout << message),...);
    //    std::printf("\n");
    //}

    template <typename... Args>
    static void info(const Args&... message) noexcept {
        std::cout << black_bg << bold << "[" << blue << "INFO" << ansiexit << bold << black_bg << "]" << ansiexit << " ";
        ((std::cout << message), ...);
        std::printf("\n");
    }

    template <typename... Args>
    static void warning(const Args&... message) noexcept {
        std::cout << black_bg << bold << "[" << orange << "WARNING" << ansiexit << bold << black_bg << "]" << ansiexit << " ";
        ((std::cout << message), ...);
        std::printf("\n");
    }

    template <typename... Args>
    [[noreturn]] static void error(const Args&... message) noexcept {
        std::cout << black_bg << bold << "[" << red << "ERROR" << ansiexit << bold << black_bg << "]" << ansiexit << " ";
        ((std::cout << message),...);
        std::printf("\n");
        std::exit(1);
    }
}