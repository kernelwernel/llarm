#include <chrono>
#include <iostream>
#include "constants.hpp"
#include "disassembler.hpp"
#include <llarm/shared/types.hpp>
#include <llarm/llarm-asm.hpp>

static constexpr u32 limit = 0x002000AF;

int main() {
    const auto start = std::chrono::high_resolution_clock::now();
    
    for (u32 i = 0; i < limit; i++) {
        volatile auto tmp = llarm::as::disassemble_arm(i, PC);
    }
    
    const auto end = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "LLARM time: " << duration.count() << " us\n";

    const auto start2 = std::chrono::high_resolution_clock::now();
    
    for (u32 i = 0; i < limit; i++) {
        volatile auto tmp = capstone_arm_disassembler(i);
    }
    
    const auto end2 = std::chrono::high_resolution_clock::now();
    const auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
    std::cout << "capstone time: " << duration2.count() << " us\n\n";

    std::cout << "total speed comparison: " << static_cast<double>(duration2.count()) / static_cast<double>(duration.count()) << "x faster than capstone\n";
}