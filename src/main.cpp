#include "cpu/core/core.hpp"
#include "types.hpp"
#include "sanitize.hpp"

#include <vector>

int main(int argc, char* argv[]) {
    //sanitize::handler(argc, argv);
    std::vector<u8> machine_code = { 0b01000000, 0b01000001 };

/*
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 0) &&
        (raw_code.test(8) == 1) &&
        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 1)
*/

    core::initialise(machine_code);
}