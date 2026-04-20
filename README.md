<h1 align="center">LLARM</h1>

<div align="center">
  <img src="assets/logo/dog.png" height="250" title="LLARM">
  <br>
  <small>Artwork by <a href="https://t04st3r.carrd.co/">t04st3r</a></small>
  <p align="center">
   <br>
   <img align="center" src="https://img.shields.io/github/actions/workflow/status/kernelwernel/llarm/build-all.yml">
   <img align="center" src="https://img.shields.io/github/license/kernelwernel/llarm">
   <a href="https://deepwiki.com/kernelwernel/llarm"><img align="center" src="https://deepwiki.com/badge.svg" alt="Ask DeepWiki"></a>
</div>

<br>

**LLARM** (Low Level ARM) is an infrastructure toolchain for the ARM architecture. It is a collection of C/C++ libraries and tools that provide a unified foundation for low-level ARM work.

| Subproject | Description |
|---|---|
| [`llarm-asm`](#llarm-asm) | Assembly, disassembly, identification, and validation of ARM/Thumb instructions |
| [`llarm-emu`](#llarm-emu) | Full ARM CPU and system emulation framework |
| [`llarm-cpu`](#llarm-cpu) | Runtime ARM CPU identification for C and C++ |
| [`llarm-rand`](#llarm-rand) | Random instruction and binary generation for stress-testing |


> [!NOTE]
> **Note from the developer**
>
> This project is the result of nearly 2 years of work and ~40k lines of C++. In its current state it targets AArch32 only and is not yet ready for production use. The long-term goal is full AArch64 support and to grow LLARM into a practical framework for embedded and low-level ARM development as a foundation for others to build on, much like LLVM in the compiler world.
>
> I published the current progress in early April 2026 to gather feedback and share what's been built so far. Contributions and suggestions are very welcome.

- - -

## llarm-asm

C++ library and CLI for ARM/Thumb assembly and disassembly. Covers 135+ ARM instructions, 70+ Thumb instructions, and 70+ shifter operand types. Benchmarks show it is up to 2-4× faster than comparable tools.

> [!WARNING]
> Currently only supports ARMv5, but support for successor versions are planned or in development.


**Disassemble**
```cpp
#include <llarm/llarm-asm.hpp>

std::string inst1 = llarm::as::disassemble_arm(0xE0821003);          // "ADD R1, R2, R3"
std::string inst2 = llarm::as::disassemble_thumb(0x1888);            // "ADD R0, R1, R2"
std::string inst3 = llarm::as::disassemble_arm(0xEA000005, 0x1000);  // "B #0x101C"  (PC-relative)
```

**Assemble**
```cpp
uint32_t bin1 = llarm::as::assemble_arm("ADD R1, R2, R3");   // 0xE0821003
uint32_t bin2 = llarm::as::assemble_thumb("ADD R0, R1, R2"); // 0x1888
```

**Identify / Validate**
```cpp
llarm::as::arm_id   id1 = llarm::as::identify_arm(0xE0821003);    // arm_id::ADD
llarm::as::thumb_id id2 = llarm::as::identify_thumb(0x1888);      // thumb_id::ADD3

bool is_valid1 = llarm::as::is_arm_instruction_valid(0xE0821003);
bool is_valid2 = llarm::as::is_thumb_instruction_valid(0x1888);
```

**Configurable output**
```cpp
llarm::as::settings cfg = llarm::as::default_settings();
cfg.capitals       = false;  // lowercase mnemonics
cfg.register_alias = false;  // r13/r14/r15 instead of SP/LR/PC
cfg.gcc_convention = true;   // MOV.EQ instead of MOVEQ

std::string tmp = llarm::as::disassemble_arm(0xE0821003, 0, cfg);
```

See [`llarm-asm/docs/`](llarm-asm/docs/) for the full API reference.

- - -

## llarm-emu

A modular ARM emulation framework targeting ARMv5 and earlier. Every hardware component is exposed and configurable: registers, memory, coprocessors, MMU/MPU, TLB, VFP and much more, making it suitable for debuggers, device emulation, program tracing, and embedded systems work. 

> [!WARNING]
> Currently only supports ARMv5, but support for successor versions are planned or in development.


**Quick start**
```cpp
#include <llarm/llarm-emu.hpp>

llarm::emu::cpu_blockstep cpu("firmware.bin");

using namespace llarm::emu;

// read/write registers
u32 pc = cpu.read_reg(reg_PC);
cpu.write_reg(reg_R0, 0xDEADBEEF);

// read/write physical or virtual memory
u32 val = cpu.read_physical_mem<u32>(0x08000000);
cpu.write_virtual_mem<u16>(0x20000000, 0x1234);

// step one instruction
cpu.next_instruction();
```

- - -

## llarm-cpu

Header-only C library (with C++ wrapper) for identifying the host ARM CPU at runtime. Zero external dependencies, not even GLIBC. Supports all versions of ARM. 

**C**
```c
#include <llarm/llarm-cpu.h>

const char* impl = llarm_cpu_fetch_implementor_string();
const char* prod = llarm_cpu_fetch_product_string(llarm_cpu_fetch_product());
const char* arch = llarm_cpu_fetch_arch_string(llarm_cpu_fetch_arch());
```

**C++**
```cpp
#include <llarm/llarm-cpu.hpp>

namespace cpu = llarm::cpu;
const char* impl = cpu::fetch_implementor_string();
const char* prod = cpu::fetch_product_string(cpu::fetch_product());
```

**CLI**: run `llarm-cpu` on any ARM device:
```
MIDR        : 0x410FD0B1
Implementor : ARM
Product     : Cortex-A76
Architecture: ARMv8.2-A
PPN         : 0xD0B
Variant     : 1
Revision    : 1
Generation  : post-ARM7
```

See [`llarm-cpu/docs/`](llarm-cpu/docs/) for the full C and C++ API reference.

- - -

## Building

**Requirements:** CMake 3.29+

```bash
mkdir build && cd build
cmake ..
cmake --build .
cmake --install .
```

Individual subprojects can be built independently from their own directories using the same steps.

- - -

## Development roadmap and dependency tree

<br>
<img align="center" src="assets/roadmap/llarm_roadmap.png" title="LLARM roadmap">
<br>

- - -

## License

LLARM is released under the [Apache 2.0 License](LICENSE). All subprojects share the same license.