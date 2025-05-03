#pragma once

#include <cstdint>
#include <string_view>
#include <filesystem>
#include <bitset>

using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i8  = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using sv = std::string_view;
namespace fs = std::filesystem;

using arm_code_t = std::bitset<32>;
using thumb_code_t = std::bitset<16>;