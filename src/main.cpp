#include "cpu/core/core.hpp"
#include "types.hpp"
#include "sanitize.hpp"

#include <vector>

int main(int argc, char* argv[]) {
    //sanitize::handler(argc, argv);
    std::vector<u8> machine_code = { 0b00100001, 0b11111111 }; // MOV R1, #0xFF  (thumb)

    core::initialise(machine_code);

    return 0;
}