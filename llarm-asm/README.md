# llarm-asm

C++ library and CLI tool for ARM assembly and disassembly. Handles both ARM and Thumb instruction sets.

- Assemble mnemonics to binary and disassemble binary to mnemonics
- Identify instructions and shifter operands from binary or string
- Validate instructions
- 135+ ARM instructions, 70+ Thumb instructions, 70+ shifter operand types
- Configurable disassembly output via settings
- Fastest disassembler and assembler according to benchmarks (up to 2x or 4x faster)


## Usage

### Disassemble

```cpp
#include "llarm/llarm-asm.hpp"

// ARM
std::string s = llarm::as::disassemble_arm(0xE0821003);
// "ADD R1, R2, R3"

// Thumb
std::string s = llarm::as::disassemble_thumb(0x1888);
// "ADD R0, R1, R2"

// with PC (for PC-relative instructions)
std::string s = llarm::as::disassemble_arm(0xEA000005, 0x1000);
// "B #0x101C"
```

### Assemble

```cpp
u32 code = llarm::as::assemble_arm("ADD R1, R2, R3");
// 0xE0821003

u32 code = llarm::as::assemble_thumb("ADD R0, R1, R2");
// 0x1888
```

### Identify

```cpp
llarm::as::arm_id   id = llarm::as::identify_arm(0xE0821003);   // arm_id::ADD
llarm::as::thumb_id id = llarm::as::identify_thumb(0x1888);     // thumb_id::ADD3
llarm::as::shifter_id id = llarm::as::identify_shifter(0xE0821103); // shifter_id::DATA_IMM_LSL

// identify from string
llarm::as::arm_id id = llarm::as::identify_arm("ADD R1, R2, R3");
```

### Validate

```cpp
bool ok = llarm::as::is_arm_instruction_valid(0xE0821003);
bool ok = llarm::as::is_arm_instruction_valid("ADD R1, R2, R3");
bool ok = llarm::as::is_thumb_instruction_valid(0x1888);
```

### Settings

Disassembly output is configurable via a `settings` struct:

```cpp
llarm::as::settings config = llarm::as::default_settings();
config.capitals        = false;   // lowercase output
config.register_alias  = false;   // r13/r14/r15 instead of SP/LR/PC
config.gcc_convention  = true;    // MOV.EQ instead of MOVEQ

std::string s = llarm::as::disassemble_arm(0xE0821003, 0, config);
```

## Documentation

See [docs/documentation.md](docs/documentation.md) for the full settings reference.

## Building and installation

```bash
mkdir build && cd build
cmake ..
cmake --build .
cmake --install .
```

## CMake integration

```cmake
find_package(llarm-asm REQUIRED)
target_link_libraries(my_target PRIVATE llarm::llarm-asm-lib)
```