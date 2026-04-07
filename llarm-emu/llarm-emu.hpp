#pragma once

#include "src/id.hpp"
#include "src/cpu/cpu.hpp"


#include <llarm/shared/types.hpp>

#include <filesystem>
#include <fstream>

namespace llarm::emu {
    using reg = id::reg;

    struct cpu_blockstep {
    private:
        CPU cpu;

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
            return cpu.core.reg.read(id);
        }

        inline void write_reg(const reg id, const u32 data) {
            cpu.core.reg.write(id, data);
        }

        template <typename T>
        inline T read_physical_mem(const u32 address) {
            return static_cast<T>(cpu.ram.read(address, sizeof(T)));
        }

        template <typename T>
        inline void write_physical_mem(const u32 address, const u64 value) {
            cpu.ram.write(value, address, sizeof(T));
        }

        template <typename T>
        inline T read_virtual_mem(const u32 address) {
            return static_cast<T>(cpu.core.memory.read(address, sizeof(T)));
        }

        template <typename T>
        inline void write_virtual_mem(const u32 address, const u64 value) {
            cpu.core.memory.write(value, address, sizeof(T));
        }

        inline void next_instruction() {
            cpu.core.continue_cycle = true;
        }
    };
}