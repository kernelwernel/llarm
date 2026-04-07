#pragma once

#include "src/id.hpp"
#include "src/cpu/cpu.hpp"


#include <llarm/shared/types.hpp>

#include <filesystem>
#include <fstream>
#include <thread>

namespace llarm::emu {
    using reg = id::reg;

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

    struct cpu_blockstep {
    private:
        CPU cpu;
        std::thread cpu_thread;

    public:
        explicit cpu_blockstep(const std::filesystem::path &file_path)
            : cpu(load_binary(file_path)) {}

        ~cpu_blockstep() {
            if (cpu_thread.joinable()) {
                cpu.core.continue_cycle = true;
                cpu_thread.detach();
            }
        }

        // starts the CPU cycle loop on a background thread;
        // the loop pauses after each instruction until next_instruction() is called
        void start() {
            cpu_thread = std::thread([this] { cpu.run(); });
        }

        inline bool is_thumb_mode() const {
            return cpu.core.globals.instruction_set == id::instruction_sets::THUMB;
        }

        inline u32 current_arm_code() const {
            return cpu.core.current_arm_code;
        }

        inline u16 current_thumb_code() const {
            return cpu.core.current_thumb_code;
        }

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

    struct cpu_headless {
        static constexpr bool HEADLESS = true;

    private:
        CPU cpu;

    public:
        explicit cpu_headless(const std::filesystem::path &file_path)
            : cpu(load_binary(file_path)) {}

        void run() {
            cpu.run(HEADLESS);
        }
    };
}