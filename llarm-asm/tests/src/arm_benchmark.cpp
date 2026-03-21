#include <chrono>
#include <iostream>
#include "constants.hpp"
#include "disassembler.hpp"
#include "nyxstone.h"
#include <llarm/shared/types.hpp>
#include <llarm/llarm-asm.hpp>

static constexpr u32 limit = 0x000F'0000;

int main() {
    const auto start = std::chrono::high_resolution_clock::now();
    
    for (u32 i = 0; i < limit; i++) {
        volatile auto tmp = llarm::as::disassemble_arm(i, PC);
    }

    const auto end = std::chrono::high_resolution_clock::now();
    const auto llarm_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "LLARM time: " << llarm_duration.count() << " us\n";

    const auto start2 = std::chrono::high_resolution_clock::now();
    
    for (u32 i = 0; i < limit; i++) {
        volatile auto tmp = capstone_arm_disassembler(i);
    }
    
    const auto end2 = std::chrono::high_resolution_clock::now();
    const auto cap_duration = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);

    std::cout << "capstone time: " << cap_duration.count() << " us\n";

    using namespace nyxstone;

    auto nyxstone = NyxstoneBuilder("armv5te")
    .build()
    .value();

    const auto start3 = std::chrono::high_resolution_clock::now();

    for (u32 i = 0; i < limit; i++) {
        //  nyxstone uses a std::vector of u8 instead of a u32
        const std::vector<uint8_t> bytes = {
            static_cast<uint8_t>(i & 0xFF),
            static_cast<uint8_t>((i >> 8) & 0xFF),
            static_cast<uint8_t>((i >> 16) & 0xFF),
            static_cast<uint8_t>((i >> 24) & 0xFF),
        };

        auto result = nyxstone->disassemble(bytes, 0x1000, {});
        if (result) {
            volatile auto tmp = result.value();
        }
    }

    const auto end3 = std::chrono::high_resolution_clock::now();
    const auto nyx_duration = std::chrono::duration_cast<std::chrono::microseconds>(end3 - start3);

    std::cout << "nyxstone time: " << nyx_duration.count() << " us\n\n";

    std::cout << "total speed comparison: \n" << 
        static_cast<double>(cap_duration.count()) / static_cast<double>(llarm_duration.count()) << 
        "x faster than capstone\n" <<
        static_cast<double>(nyx_duration.count()) / static_cast<double>(llarm_duration.count()) << 
        "x faster than nyxstone\n";
}