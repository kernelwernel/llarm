#pragma once

#include <nonstd/string_view.hpp>
#include <robin_hood.h>
#include <cstdint>

using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i8  = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

#if __cplusplus > 202100L
    constexpr u8 CPP = 26;
#elif __cplusplus == 202100L
    constexpr u8 CPP = 23;
#elif __cplusplus == 202002L
    constexpr u8 CPP = 20;
#elif __cplusplus == 201703L
    constexpr u8 CPP = 17;
#elif __cplusplus == 201402L
    constexpr u8 CPP = 14;
#elif __cplusplus == 201103L
    constexpr u8 CPP = 11;
#elif __cplusplus < 201103L
    constexpr u8 CPP = 1;
#else
    constexpr u8 CPP = 0;
#endif

#if (CPP >= 20) 
    #define LLARM_CONSTEVAL consteval
#else
    #define LLARM_CONSTEVAL constexpr
#endif


namespace llarm {
    // This lib is mainly used for string interpretation in llarm-asm.
    // The reason why this is used is because llarm-asm has heavy usage
    // of string_views, but the fact that it was introduced in C++17
    // makes it a nonstarter, as I'm aiming to support at least C++11.
    // So to compensate, I've imported this header-only lib to make this
    // possible as it supports C++98. 
    // from https://github.com/nonstd-lite/string-view-lite
    using string_view = nonstd::string_view;

    // This is a replacement for std::unordered_map, as it's far too slow
    // for the computationally demanding tasks i'm trying to achieve. 
    // from https://github.com/martinus/robin-hood-hashing
    template <typename K, typename V>
    using unordered_map = robin_hood::unordered_map<K, V>;
}

using sv = llarm::string_view;