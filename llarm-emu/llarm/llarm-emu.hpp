#pragma once

#include "src/id.hpp"
#include "src/cpu/cpu.hpp"


#include <llarm/shared/types.hpp>

#include <filesystem>
#include <fstream>

namespace llarm::emu {
    enum reg : u8 {
        reg_R0       = static_cast<u8>(id::reg::R0),
        reg_R1       = static_cast<u8>(id::reg::R1),
        reg_R2       = static_cast<u8>(id::reg::R2),
        reg_R3       = static_cast<u8>(id::reg::R3),
        reg_R4       = static_cast<u8>(id::reg::R4),
        reg_R5       = static_cast<u8>(id::reg::R5),
        reg_R6       = static_cast<u8>(id::reg::R6),
        reg_R7       = static_cast<u8>(id::reg::R7),
        reg_R8       = static_cast<u8>(id::reg::R8),
        reg_R8_fiq   = static_cast<u8>(id::reg::R8_fiq),
        reg_R9       = static_cast<u8>(id::reg::R9),
        reg_R9_fiq   = static_cast<u8>(id::reg::R9_fiq),
        reg_R10      = static_cast<u8>(id::reg::R10),
        reg_R10_fiq  = static_cast<u8>(id::reg::R10_fiq),
        reg_R11      = static_cast<u8>(id::reg::R11),
        reg_R11_fiq  = static_cast<u8>(id::reg::R11_fiq),
        reg_R12      = static_cast<u8>(id::reg::R12),
        reg_IP       = static_cast<u8>(id::reg::IP),
        reg_R12_fiq  = static_cast<u8>(id::reg::R12_fiq),
        reg_R13      = static_cast<u8>(id::reg::R13),
        reg_SP       = static_cast<u8>(id::reg::SP),
        reg_R13_fiq  = static_cast<u8>(id::reg::R13_fiq),
        reg_R13_irq  = static_cast<u8>(id::reg::R13_irq),
        reg_R13_und  = static_cast<u8>(id::reg::R13_und),
        reg_R13_svc  = static_cast<u8>(id::reg::R13_svc),
        reg_R13_abt  = static_cast<u8>(id::reg::R13_abt),
        reg_R14      = static_cast<u8>(id::reg::R14),
        reg_LR       = static_cast<u8>(id::reg::LR),
        reg_R14_fiq  = static_cast<u8>(id::reg::R14_fiq),
        reg_R14_irq  = static_cast<u8>(id::reg::R14_irq),
        reg_R14_und  = static_cast<u8>(id::reg::R14_und),
        reg_R14_svc  = static_cast<u8>(id::reg::R14_svc),
        reg_R14_abt  = static_cast<u8>(id::reg::R14_abt),
        reg_PC       = static_cast<u8>(id::reg::PC),
        reg_R15      = static_cast<u8>(id::reg::R15),
        reg_CPSR     = static_cast<u8>(id::reg::CPSR),
        reg_SPSR     = static_cast<u8>(id::reg::SPSR),
        reg_SPSR_svc = static_cast<u8>(id::reg::SPSR_svc),
        reg_SPSR_abt = static_cast<u8>(id::reg::SPSR_abt),
        reg_SPSR_und = static_cast<u8>(id::reg::SPSR_und),
        reg_SPSR_irq = static_cast<u8>(id::reg::SPSR_irq),
        reg_SPSR_fiq = static_cast<u8>(id::reg::SPSR_fiq)
    };

    static inline std::vector<u8> load_binary(const std::filesystem::path &file_path) {
        std::ifstream file(file_path, std::ios::binary | std::ios::ate);

        if (!file) {
            llarm::out::error("Failed to open file");
        }

        const std::size_t file_size = static_cast<std::size_t>(file.tellg());
        file.seekg(0);

        std::vector<u8> data(file_size);

        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
        file.read(reinterpret_cast<char*>(data.data()), static_cast<std::streamsize>(file_size));

        return data;
    }

    struct cpu_blockstep {
        std::vector<u8> binary;
        CPU cpu;

        explicit cpu_blockstep(const std::filesystem::path &file_path)
            : binary(load_binary(file_path)), cpu(binary) {}

        // starts the CPU cycle loop on a background thread;
        // the loop pauses after each instruction until next_instruction() is called
        void run() {
            cpu.run();
        }

        bool is_thumb_mode() const {
            return cpu.core.globals.instruction_set == id::instruction_sets::THUMB;
        }

        u32 current_arm_code() const {
            return cpu.core.current_arm_code;
        }

        u16 current_thumb_code() const {
            return cpu.core.current_thumb_code;
        }

        u32 read_reg(const reg id) {
            return cpu.core.reg.read(id);
        }

        void write_reg(const reg id, const u32 data) {
            cpu.core.reg.write(id, data);
        }

        template <typename T>
        T read_physical_mem(const u32 address) {
            return static_cast<T>(cpu.ram.read(address, sizeof(T)));
        }

        template <typename T>
        void write_physical_mem(const u32 address, const u64 value) {
            cpu.ram.write(value, address, sizeof(T));
        }

        template <typename T>
        T read_virtual_mem(const u32 address) {
            return static_cast<T>(cpu.core.memory.read(address, sizeof(T)));
        }

        template <typename T>
        void write_virtual_mem(const u32 address, const u64 value) {
            cpu.core.memory.write(value, address, sizeof(T));
        }

        void next_instruction() {
            cpu.core.continue_cycle = true;
        }
    };

    struct cpu_headless {
        static constexpr bool HEADLESS = true;

    
        std::vector<u8> binary;
        CPU cpu;

    
        explicit cpu_headless(const std::filesystem::path &file_path)
            : binary(load_binary(file_path)), cpu(binary) {}

        void run() {
            cpu.run(HEADLESS);
        }
    };
}