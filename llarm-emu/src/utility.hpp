#pragma once

#include "id.hpp"

#include <llarm/shared/types.hpp>
#include <concepts>

namespace util {
    void modify_bit(u32 &original, const u8 index, const bool value);
    void modify_vfp_bit(u64 &original, const u8 index, const bool value);

    void swap_bits(u32 &original, const u8 start, const u8 end, const u32 value);
    void swap_bits_vfp(u64 &original, const u8 start, const u8 end, const u32 value);

    // custom integral concept template
    template <typename T>
    concept is_integral = (
        std::same_as<T, u8>  ||
        std::same_as<T, u16> ||
        std::same_as<T, u32> ||
        std::same_as<T, u64>
    );

    // this is a hot steaming pile of absolute garbage, might rewrite this in the future
    template <is_integral T>
    inline T swap_endianness(const T value) {
        if constexpr (std::is_same_v<T, u16>) {
            #ifdef _MSC_VER
                return _byteswap_ushort(value);
            #elif defined(__GNUC__) || defined(__clang__)
                return __builtin_bswap16(value);
            #else
                return (
                    ((value & 0x00FF) << 8) |
                    ((value & 0xFF00) >> 8)
                );
            #endif
        } else if constexpr (std::is_same_v<T, u32>) {
            #ifdef _MSC_VER
                return _byteswap_ulong(value);
            #elif defined(__GNUC__) || defined(__clang__)
                return __builtin_bswap32(value);
            #else
                return (
                    ((value & 0x000000FF) << 24) |
                    ((value & 0x0000FF00) << 8)  |
                    ((value & 0x00FF0000) >> 8)  |
                    ((value & 0xFF000000) >> 24)
                );
            #endif
        } else if constexpr (std::is_same_v<T, u64>) {
            #ifdef _MSC_VER
                return _byteswap_uint64(value);
            #elif defined(__GNUC__) || defined(__clang__)
                return __builtin_bswap64(value);
            #else
                return ( 
                    ((value & 0x00000000000000FF) << 56) |
                    ((value & 0x000000000000FF00) << 40) |
                    ((value & 0x0000000000FF0000) << 24) |
                    ((value & 0x00000000FF000000) << 8)  |
                    ((value & 0x000000FF00000000) >> 8)  |
                    ((value & 0x0000FF0000000000) >> 24) |
                    ((value & 0x00FF000000000000) >> 40) |
                    ((value & 0xFF00000000000000) >> 56)
                );
            #endif
        }
    }

    // for example, ARMv5TEJ will be simplified to ARMv5
    constexpr id::arch simplify_arch_version(const id::specific_arch arch) {
        switch (arch) {
            case id::specific_arch::UNKNOWN: return id::arch::UNKNOWN;
            case id::specific_arch::ARMv1: return id::arch::ARMv1;
            case id::specific_arch::ARMv2: 
            case id::specific_arch::ARMv2a: return id::arch::ARMv2;
            case id::specific_arch::ARMv3M:
            case id::specific_arch::ARMv3: return id::arch::ARMv3;
            case id::specific_arch::ARMv4:
            case id::specific_arch::ARMv4xM:
            case id::specific_arch::ARMv4TxM:
            case id::specific_arch::ARMv4T: return id::arch::ARMv4;
            case id::specific_arch::ARMv5: 
            case id::specific_arch::ARMv5xM: 
            case id::specific_arch::ARMv5TxM: 
            case id::specific_arch::ARMv5T: 
            case id::specific_arch::ARMv5TE: 
            case id::specific_arch::ARMv5TExP: 
            case id::specific_arch::ARMv5TEJ: return id::arch::ARMv5;
            case id::specific_arch::ARMv6: 
            case id::specific_arch::ARMv6T2: 
            case id::specific_arch::ARMv6Z: 
            case id::specific_arch::ARMv6K: 
            case id::specific_arch::ARMv6_M: return id::arch::ARMv6;
            case id::specific_arch::ARMv7_A: 
            case id::specific_arch::ARMv7_M: 
            case id::specific_arch::ARMv7_R: 
            case id::specific_arch::ARMv7E_M: return id::arch::ARMv7;
            case id::specific_arch::ARMv8_A: 
            case id::specific_arch::ARMv8_R: 
            case id::specific_arch::ARMv8_M_BASELINE: 
            case id::specific_arch::ARMv8_M_MAINLINE: 
            case id::specific_arch::ARMv8_1_M_MAINLINE: 
            case id::specific_arch::ARMv8_2_A: 
            case id::specific_arch::ARMv8_3_A: 
            case id::specific_arch::ARMv8_4_A: 
            case id::specific_arch::ARMv8_5_A: 
            case id::specific_arch::ARMv8_6_A: return id::arch::ARMv8;
            case id::specific_arch::ARMv9_A: 
            case id::specific_arch::ARMv9_2_A: return id::arch::ARMv9;
            //default: llarm::out::error("TODO");
        }
    }


    LLARM_CONSTEVAL u32 get_kb(const u16 kb) {
        switch (kb) {
            case 1:   return (1 << 10); // 1KB
            case 2:   return (1 << 11); // 2KB
            case 4:   return (1 << 12); // 4KB
            case 8:   return (1 << 13); // 8KB
            case 16:  return (1 << 14); // 16KB
            case 32:  return (1 << 15); // 32KB
            case 64:  return (1 << 16); // 64KB
            case 128: return (1 << 17); // 128KB
            case 256: return (1 << 18); // 256KB
            case 512: return (1 << 19); // 512KB
            // TODO: figure out an assert check if it's not valid
            default: return 0;
        }
    }

    LLARM_CONSTEVAL u32 get_mb(const u16 mb) {
        switch(mb) {
            case 1:   return (1 << 20); // 1MB
            case 2:   return (1 << 21); // 2MB
            case 4:   return (1 << 22); // 4MB
            case 8:   return (1 << 23); // 8MB
            case 16:  return (1 << 24); // 16MB
            case 32:  return (1 << 25); // 32MB
            case 64:  return (1 << 26); // 64MB
            case 128: return (1 << 27); // 128MB
            case 256: return (1 << 28); // 256MB
            case 512: return (1 << 29); // 512MB
            // TODO: figure out an assert check if it's not valid
            default: return 0;
        }
    }

    LLARM_CONSTEVAL u64 get_gb(const u16 gb) {
        switch (gb) {
            case 1:   return (1ULL << 30); // 1GB
            case 2:   return (1ULL << 31); // 2GB
            case 4:   return (1ULL << 32); // 4GB
            case 8:   return (1ULL << 33); // 8GB
            case 16:  return (1ULL << 34); // 16GB
            case 32:  return (1ULL << 35); // 32GB
            case 64:  return (1ULL << 36); // 64GB
            case 128: return (1ULL << 37); // 128GB
            case 256: return (1ULL << 38); // 256GB
            case 512: return (1ULL << 39); // 512GB
            // TODO: figure out an assert check if it's not valid
            default: return 0;
        }
    }

    // these are for development and debug purposes, ignore this section
    namespace dev {
        [[maybe_unused]] void pause();
    }
}