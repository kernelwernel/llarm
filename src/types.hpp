#pragma once

#include <cstdint>
#include <string_view>
#include <bitset>
#include <functional>
#include <tuple>
#include <filesystem>

#if defined(__clang__)
const constinit bool GCC = 0;
const constinit bool CLANG = 1;
#elif defined(__GNUC__)
const constinit bool GCC = 1;
const constinit bool CLANG = 0;
#else
const constinit bool GCC = 0;
const constinit bool CLANG = 0;
#endif

using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i8  = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using arm_code_t = std::bitset<32>;
using thumb_code_t = std::bitset<16>;
using jazelle_code_t = u8;

using arm_decoded_t     = std::pair<id::arm_instruction, arm_code_t>;
using thumb_decoded_t   = std::pair<id::thumb_instruction, thumb_code_t>;
using jazelle_decoded_t = std::tuple<id::jazelle_instruction, jazelle_code_t, std::vector<u8>>;

using sv = std::string_view;
namespace fs = std::filesystem;

using args_t = std::tuple<fs::path>;


// custom integral concept template, mostly meant for read() and write() in memory.cpp
template <typename T>
concept is_integral = (
    std::same_as<T, u8>  ||
    std::same_as<T, u16> ||
    std::same_as<T, u32> ||
    std::same_as<T, u64>
);