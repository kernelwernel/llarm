# llarm-cpu

Header-only C library (with C++ wrapper) for identifying ARM CPU information at runtime.

- Zero dependencies (not even GLIBC)
- C API with optional C++ namespace wrapper
- 170+ known CPU products (Cortex-A/R/M/X, Neoverse, Apple Silicon, Qualcomm Oryon, etc.)
- 30+ known CPU architectures and variants
- 20+ known CPU implementors 
- Highly configurable and modular
- Works with C++98 and C89

## What it identifies

| Field | Example |
|---|---|
| Implementor | `ARM`, `Apple`, `Qualcomm`, `Samsung`, ... |
| Product | `Cortex-A76`, `Apple M1 Firestorm`, `Neoverse-N1`, ... |
| Architecture | `ARMv8.2-A`, `ARMv9-A`, ... |
| Generation | `pre-ARM7`, `ARM7`, `post-ARM7` |
| PPN / Variant / Revision | Raw MIDR fields |

## Usage

### C

```c
#include "llarm/llarm-cpu.h"

unsigned int midr = llarm_cpu_fetch_midr();
const char*  impl = llarm_cpu_fetch_implementor_string();
const char*  prod = llarm_cpu_fetch_product_string(llarm_cpu_fetch_product());
const char*  arch = llarm_cpu_fetch_arch_string(llarm_cpu_fetch_arch());
```

### C++

```cpp
#include "llarm/llarm-cpu.hpp"

namespace cpu = llarm::cpu;
const char* impl = cpu::fetch_implementor_string();
const char* prod = cpu::fetch_product_string(cpu::fetch_product());
const char* arch = cpu::fetch_arch_string(cpu::fetch_arch());
```

### CMake

```cmake
find_package(llarm-cpu REQUIRED)
target_link_libraries(my_target PRIVATE llarm::llarm-cpu-lib)
```

## Building

```bash
mkdir build && cd build
cmake ..
make
```

## CLI tool

Run `llarm-cpu` on an ARM device to print a full CPU summary:

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

## Tests

```bash
cd tests
./run_tests.sh
```

The test runner supports two modes, selected automatically:

| Mode | Toolchain | Emulator |
|---|---|---|
| Linux user-mode | `arm-linux-gnueabi-g++` | `qemu-arm` |
| Bare-metal semihosting | `arm-none-eabi-g++` | `qemu-system-arm` |

Install on Arch: `sudo pacman -S arm-linux-gnueabihf-gcc qemu-user`
Install on Debian/Ubuntu: `sudo apt install g++-arm-linux-gnueabi qemu-user`

## API reference

See [docs/c_documentation.md](docs/c_documentation.md) and [docs/cpp_documentation.md](docs/cpp_documentation.md).
