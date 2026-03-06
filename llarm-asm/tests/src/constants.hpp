#pragma once

#include <llarm/shared/types.hpp>

// this is relevant for branching instructions
static inline constexpr u32 PC = 0xDEADBEEF;

static constexpr const char* bold = "\033[1m";
static constexpr const char* underline = "\033[4m";
static constexpr const char* ansi_exit = "\x1B[0m";
static constexpr const char* red = "\x1B[38;2;239;75;75m"; 
static constexpr const char* orange = "\x1B[38;2;255;180;5m";
static constexpr const char* green = "\x1B[38;2;94;214;114m";
static constexpr const char* red_orange = "\x1B[38;2;247;127;40m";
static constexpr const char* green_orange = "\x1B[38;2;174;197;59m";
static constexpr const char* grey = "\x1B[38;2;108;108;108m";
