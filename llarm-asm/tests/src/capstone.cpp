#include "disassembler.hpp"

#include <iostream>


int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }

    const char* str = argv[1];
    int binary = atoi(str);

    std::cout << capstone_arm_disassembler(static_cast<u32>(binary)) << "\n";
}