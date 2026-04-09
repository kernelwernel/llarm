# llarm-emu

C++ ARM emulation library and tool. Supports ARMv1~ARMv5 user and system programs.

- Full ARM and Thumb instruction sets
- MMU and MPU support with TLB and FCSE
- VFP (Vector Floating Point) support
- Enhanced DSP support
- Coprocessor support
- 26-bit architecture backwards compatibility
- Modular: swap or extend any subsystem independently

It offers immense flexibility with a wide openness to the hardware components, with practically every aspect of the CPU being modifiable in a way that's as friendly and easy to anybody using the framework. The applications are endless. 

It should be mentioned that this project is still a work in progress. While the CPU itself is practically finished, the peripherals and SoC components are still being developed. The current goal is to emulate Linux. 

## Usage

### Headless execution

```cpp
#include <llarm/llarm-emu.hpp>

llarm::emu::cpu_headless cpu("program.bin");
cpu.run();
```

### Step-by-step execution

```cpp
llarm::emu::cpu_blockstep cpu("program.bin");
cpu.run();

// read state
u32 pc   = cpu.read_reg(llarm::emu::reg::PC);
u32 code = cpu.current_arm_code();

// advance one instruction
cpu.next_instruction();
```

### Register access

```cpp
u32 val = cpu.read_reg(llarm::emu::reg::R0);
cpu.write_reg(llarm::emu::reg::SP, 0x4000);
```

### Memory access

```cpp
// physical (raw RAM)
u32 word = cpu.read_physical_mem<u32>(0x1000);
cpu.write_physical_mem<u32>(0x1000, 0xDEADBEEF);

// virtual (goes through MMU/MPU if enabled)
u32 word = cpu.read_virtual_mem<u32>(0x1000);
```

## CLI tool

```
Usage:
 llarm-emu [option(s)] <binary>

Options:
 -h   | --help          print this help menu
 -v   | --version       print CLI version and other details
 -r   | --run           run binary headlessly (default)
 -s   | --step          interactive step-by-step execution
 -a   | --arm           start in ARM mode (default)
 -t   | --thumb         start in Thumb mode
      | --regs         print all registers at each step
      | --reg <name>   print a specific register (e.g. R0, SP, PC, CPSR)
      | --mem <addr>   read physical memory (e.g. 0x1000 or 0x1000:u32)
```

```
llarm-emu program.bin
llarm-emu --step --regs program.bin
llarm-emu --step --reg PC --mem 0x1000:u32 program.bin
llarm-emu --thumb program.bin
```

Step mode output:

```
[   0] PC=0x00000000  ARM: MOV R0, #10 (0xE3A0000A)
> [Enter]=step  [q]=quit
[   1] PC=0x00000004  ARM: MOV R1, #6 (0xE3A01006)
> [Enter]=step  [q]=quit
```


## Building

```bash
mkdir build && cd build
cmake ..
make
```


## CMake integration

```cmake
find_package(llarm-emu REQUIRED)
target_link_libraries(my_target PRIVATE llarm::llarm-emu-lib)
```