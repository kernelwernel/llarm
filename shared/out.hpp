#pragma once

#include <cstdint>
#include <string_view>
#include <iostream>
#include <source_location>

namespace shared::out {
    constexpr std::string_view
        black_bg = "\x1B[48;2;0;0;0m",
        bold     = "\033[1m",
        ansiexit = "\x1B[0m",
        green    = "\x1B[38;2;94;214;114m",
        orange   = "\x1B[38;2;255;180;5m",
        red      = "\x1B[38;2;239;75;75m",
        blue     = "\x1B[38;2;00;59;193m",
        misc     = "\x1B[48;2;255;255;255m";


    static void info(const auto ...message) noexcept {
        std::cout << black_bg << bold << "[" << blue << "INFO" << ansiexit << bold << black_bg << "]" << ansiexit << " ";
        ((std::cout << message),...);
        std::printf("\n");
    }

    static void warning(const auto ...message) noexcept {
        std::cout << black_bg << bold << "[" << orange << "WARNING" << ansiexit << bold << black_bg << "]" << ansiexit << " ";
        ((std::cout << message),...);
        std::printf("\n");
    }

    [[noreturn]] static void error(const auto ...message) noexcept {
        std::cout << black_bg << bold << "[" << red << "ERROR" << ansiexit << bold << black_bg << "]" << ansiexit << " ";
        ((std::cout << message),...);
        std::printf("\n");
        std::exit(1);
    }
}