#include <llarm/llarm-asm.hpp>
#include <llarm/shared/types.hpp>

#include <capstone/capstone.h>

#include <format>

// this is relevant for branching instructions
static constexpr u32 PC = 0xDEADBEEF;
static constexpr const char* bold = "\033[1m";
static constexpr const char* underline = "\033[4m";
static constexpr const char* ansi_exit = "\x1B[0m";
static constexpr const char* red = "\x1B[38;2;239;75;75m"; 
static constexpr const char* orange = "\x1B[38;2;255;180;5m";
static constexpr const char* green = "\x1B[38;2;94;214;114m";
static constexpr const char* red_orange = "\x1B[38;2;247;127;40m";
static constexpr const char* green_orange = "\x1B[38;2;174;197;59m";
static constexpr const char* grey = "\x1B[38;2;108;108;108m";


std::string capstone_arm_disassembler(const u32 binary) {
    csh handle;
    cs_open(CS_ARCH_ARM, CS_MODE_ARM, &handle);  // plain ARM, no thumb, no v5+

    const u8 bytes[4] = {
        static_cast<u8>(binary & 0xFF),
        static_cast<u8>((binary >> 8) & 0xFF),
        static_cast<u8>((binary >> 16) & 0xFF),
        static_cast<u8>((binary >> 24) & 0xFF)
    };

    cs_insn* insn;
    const size_t count = cs_disasm(handle, bytes, sizeof(bytes), PC, 1, &insn);

    std::string result = "error";
    if (count > 0) {
        result = std::string(insn[0].mnemonic) + " " + std::string(insn[0].op_str);
        cs_free(insn, count);
    }

    cs_close(&handle);
    return result;
}


std::string highlight_mismatch(const std::string& a, const std::string& b) {
    std::string result;
    const size_t len = std::max(a.size(), b.size());

    for (size_t i = 0; i < len; i++) {
        const char ca = i < a.size() ? a[i] : '?';
        const char cb = i < b.size() ? b[i] : '?';

        if (ca != cb) {
            result += red;
            result += bold;
            result += ca;
            result += ansi_exit;
        } else {
            result += ca;
        }
    }

    return result;
}



int main() {
    u32 binary = 0;

    llarm::as::settings settings = {};
    settings.capitals = false;
    settings.register_alias = true;
    settings.register_alias = true;
    settings.cond_always_suffix = true;

    for (u32 i = 0; i < 0xFF'FF'FF'FF; i++) {
        const std::string& llarm_disassembly = llarm::as::disassemble_arm(binary, PC, settings);
        const std::string& capstone_disassembly = capstone_arm_disassembler(binary);

        const size_t cap_size = capstone_disassembly.size();
        const size_t llarm_size = llarm_disassembly.size();

        const bool is_size_exact = cap_size == llarm_size;

        if (llarm_disassembly == capstone_disassembly && is_size_exact) {
            binary++;
            continue;
        }

        std::cout << red << "\n===== DISASSEMBLY MISMATCH FOUND =====" << ansi_exit << "\n\n";

        std::cout << "int:    " << binary << "\n" << \
        "binary: " << std::bitset<32>(binary) << "\n" << \
        "hex:    " << std::format("0x{:08X}\n", binary) << "\n";

        if (!is_size_exact) {
            std::cout << "size mismatch: \nLLARM (" << llarm_size << ") => capstone (" << cap_size << ")\n\n";
        }

        const std::string& mismatch_str = highlight_mismatch(llarm_disassembly, capstone_disassembly);

        std::cout << mismatch_str << "\n\n";

        std::cout << "LLARM:    " << bold << llarm_disassembly << "\n" << ansi_exit << \
        "capstone: " << bold << capstone_disassembly << "\n" << ansi_exit << "\n\n";
        return 0;
    }
}