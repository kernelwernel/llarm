#pragma once

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
    #define CPP 26
#elif __cplusplus == 202100L
    #define CPP 23
#elif __cplusplus == 202002L
    #define CPP 20
#elif __cplusplus == 201703L
    #define CPP 17
#elif __cplusplus == 201402L
    #define CPP 14
#elif __cplusplus == 201103L
    #define CPP 11
#elif __cplusplus < 201103L
    #define CPP 1
#else
    #define CPP 0
#endif

#if (CPP >= 20) 
    #define LLARM_CONSTEVAL consteval
#else
    #define LLARM_CONSTEVAL constexpr
#endif