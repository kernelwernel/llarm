#pragma once

#include <tuple>
#include <concepts>

#include "shared/types.hpp"

//#if defined(__clang__)
//const constinit bool GCC = 0;
//const constinit bool CLANG = 1;
//#elif defined(__GNUC__)
//const constinit bool GCC = 1;
//const constinit bool CLANG = 0;
//#else
//const constinit bool GCC = 0;
//const constinit bool CLANG = 0;
//#endif

using args_t = std::tuple<fs::path>;


// custom integral concept template, mostly meant for read() and write() in memory.cpp
template <typename T>
concept is_integral = (
    std::same_as<T, u8>  ||
    std::same_as<T, u16> ||
    std::same_as<T, u32> ||
    std::same_as<T, u64>
);


#if __cplusplus > 202100L
#define CPP 23
#ifdef __LLARM_DEBUG__
#pragma message("using post-C++23, set back to C++23 standard")
#endif
#elif __cplusplus == 202100L
#define CPP 23
#ifdef __LLARM_DEBUG__
#pragma message("using C++23")
#endif
#elif __cplusplus == 202002L
#define CPP 20
#ifdef __LLARM_DEBUG__
#pragma message("using C++20")
#endif
#elif __cplusplus == 201703L
#define CPP 17
#ifdef __LLARM_DEBUG__
#pragma message("using C++17")
#endif
#elif __cplusplus == 201402L
#define CPP 14
#ifdef __LLARM_DEBUG__
#pragma message("using C++14")
#endif
#elif __cplusplus == 201103L
#define CPP 11
#ifdef __LLARM_DEBUG__
#pragma message("using C++11")
#endif
#elif __cplusplus < 201103L
#define CPP 1
#ifdef __LLARM_DEBUG__
#pragma message("using pre-C++11")
#endif
#else
#define CPP 0
#ifdef __LLARM_DEBUG__
#pragma message("Unknown C++ standard")
#endif
#endif


#if (CPP >= 20) 
#define LLARM_CONSTEVAL consteval
#else
#define LLARM_CONSTEVAL constexpr
#endif

static constexpr bool FORCED = true; // specifically for coprocessor.write()