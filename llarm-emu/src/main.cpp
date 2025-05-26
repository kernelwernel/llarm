#include "cpu/core/core.hpp"

#include "shared/types.hpp"
#include "shared/out.hpp"


#include <vector>
#include <fstream>

std::vector<u8> fetch_binary(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);

    if (!file) {
        shared::out::error("Failed to open file");
    }

    std::size_t file_size = static_cast<std::size_t>(file.tellg());
    file.seekg(0);

    std::vector<u8> buffer(file_size);

    if (!file.read(reinterpret_cast<char*>(buffer.data()), static_cast<std::streamsize>(file_size))) {
        shared::out::error("Failed to read file");
    }

    return buffer; // Return the vector containing the binary data
}


int main(int argc, char* argv[]) {
    //sanitize::handler(argc, argv);
    
    //std::array<u8, 2> machine_code = { 0b00100001, 0b11111110 }; // MOV R1, #0xFF  (thumb)

    std::vector<u8> machine_code = fetch_binary("../tests/gcd/gcd.bin");

    
    //std::array<u8, 2> machine_code = { 0b00000010, 0b00000001 };

    core::initialise(machine_code);

    return 0;
}