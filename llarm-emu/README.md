# llarm-emu

An ARM emulation framework for C++


# Technical features
llarm-emu has the goal of emulating pretty much everything about the ARM architecture up to v(something):
- deprecated 26-bit architecture compatibility
- Thumb, Thumb2 and Jazelle compatibility (WIP)
- MMU and MPU support (WIP)
- Enhanced DSP support (WIP)
- VFP support (WIP)
- optional clock configurations (WIP)
- selection of a wide variety of architectures



- completely modular


# Why not use unicorn engine and what are the differences?
While unicorn serves a similar purpose to llarm-emu, there are key differences between the two:
    - virtualization support 
    - and providing a wide range of CPU architectures (x86, RISC-V, SPARC, etc...),


llarm-emu is similar, except it is fully specialised for ARM processors whether old, new, or even deprecated. It offers immense flexibility with a much wider openness to the hardware components, with practically every aspect of the CPU being modifiable in a way that's as friendly and easy to anybody using the framework. 

Additionally, unicorn uses the GPLv2 license, which means proprietary software cannot make use of the project. Meanwhile, llarm-emu is MIT, which has little to no restrictions on its usage whatsoever, allowing corporations and proprietary software to freely use the project.


# What it's good for
- useful for:
    - debuggers
    - ARM-based device development (such as game consoles or phones)
    - program monitoring and logging
    - messing around and learning the architecure in a hands-on approach
    - embedded systems development
    - and much more