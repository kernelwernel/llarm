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

        static inline std::vector<u8> load_binary(const std::filesystem::path &file_path) {
            std::ifstream file(file_path, std::ios::binary | std::ios::ate);

            if (!file) {
                llarm::out::error("Failed to open file");
            }

            std::size_t file_size = static_cast<std::size_t>(file.tellg());
            file.seekg(0);

            std::vector<u8> data(file_size);

            if (!file.read(reinterpret_cast<char*>(data.data()), static_cast<std::streamsize>(file_size))) {
                llarm::out::error("Failed to read file");
            }

            return data;
        }

    public:
        inline u32 read_reg(const reg id) {
            return internal_core.reg.read(id);
        }

        inline void write_reg(const reg id, const u32 data) {
            internal_core.reg.write(id, data);
        }

        template <typename T>
        inline T read_physical_mem(const u32 address) {
            return static_cast<T>(internal_core.ram.read(address, sizeof(T)));
        }

        template <typename T>
        inline void write_physical_mem(const u32 address, const u64 value) {
            internal_core.ram.write(value, address, sizeof(T));
        }

        template <typename T>
        inline T read_virtual_mem(const u32 address) {
            return static_cast<T>(internal_core.memory.read(address, sizeof(T)));
        }

        template <typename T>
        inline void write_virtual_mem(const u32 address, const u64 value) {
            internal_core.memory.write(value, address, sizeof(T));
        }

        inline void next_instruction() {
            internal_core.continue_cycle = true;
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