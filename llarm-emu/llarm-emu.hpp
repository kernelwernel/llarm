#pragma once

#include "src/id.hpp"
#include "src/cpu/core/core.hpp"


#include <llarm/shared/types.hpp>

#include <filesystem>
#include <fstream>

namespace llarm::emu {
    using reg = id::reg;

    struct core_blockstep {
    private:
        CORE internal_core;

        static inline std::vector<u8> load_binary(const std::filesystem::path file_path) {
            std::ifstream file(file_path, std::ios::binary | std::ios::ate);

            if (!file) {
                llarm::out::error("Failed to open file");
            }

            std::size_t file_size = static_cast<std::size_t>(file.tellg());
            file.seekg(0);

            std::vector<u8> buffer(file_size);

            if (!file.read(reinterpret_cast<char*>(buffer.data()), static_cast<std::streamsize>(file_size))) {
                llarm::out::error("Failed to read file");
            }

            return buffer; // Return the vector containing the binary data
        }

    public:
        inline u32 read_reg(const reg id) {

        }

        inline void write_reg() {

        }

        inline void write_physical_mem() {

        }

        inline void read_physical_mem() {

        }

        inline void write_virtual_mem() {

        }

        inline void read_virtual_mem() {

        }

        void next_instruction() {

        }

        core_blockstep(const std::filesystem::path& binary) 
        : internal_core(load_binary(binary)) {

        }
    };
}


/* ideas:
 * - blockstep struct 
 *
 */