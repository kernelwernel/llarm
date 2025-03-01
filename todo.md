- [ ] Prior to ARM architecture version 3, a condition field of 0b1111 meant that the instruction was never
executed. The mnemonic extension for this condition was NV.

- [ ] reorder the opcodes so that opcodes that take in the MOST bits should be analysed first, and the least ones goes to the bottom of the table

- [ ] figure out how to deal with the BKPT instruction

- [ ] make the MMU
- [ ] make the coprocessor
- [ ] thumb
    - [X] branching
    - [X] comparison
    - [ ] load
    - [X] logic
    - [X] math
    - [ ] misc
    - [X] movement
    - [ ] store

- [ ] thumb instruction double checking and description update (and actually reading the instruction documentation)
    - [ ] branching
    - [ ] comparison
    - [ ] load
    - [ ] logic
    - [ ] math
    - [ ] misc
    - [ ] movement
    - [ ] store

- [ ] thumb 2
- [ ] add an UNPREDICTABLE message throughout every part of the emulator once it's complete (based on the docs)
- [ ] add jazelle support
- [ ] add 26-bit support
    - [X] PC (loopback functionality too)
    - [X] processor modes
    - [X] register 15 program status foundation
    - [X] register 15 program status specifics (read)
    - [ ] register 15 program status specifics (write)
    - [X] CPSR absence
    - [X] SPSR absence
    - [X] register accesses based on modes
    - [X] exceptions
    - [X] branches
    - [X] configuration (like switching from 32 to 26)
    - [X] is_26_bit_arch()
    - [X] address exception
    - [X] return from address
    - [ ] PSR update instructions
- [X] figure out a good mechanism for reading/writing to cp registers
- [ ] replace the cp15 writing lambdas with utility functions
- [ ] finish making the cp15 control register 1 
- [ ] make a PC read/write function wrapper

MMU EMULATION TODO:
- [X] understand the first level descriptor formats
- [ ] create the fault descriptor format
- [X] create the fine descriptor format
- [X] create the coarse descriptor format
- [X] create the section descriptor format
- [ ] check if the first-level fetch is actually just a u32 lookup
- [ ] create the second-level large descriptor
- [ ] create the second-level small descriptor
- [ ] create the second-level tiny descriptor
- [ ] create the second-level fault descriptor
- [ ] check if the second-level descriptors are basically coarse and fine tables that are separate, basically 2 tables rounded up as 1
- [ ] understand the protection unit architecture 
- [ ] understand the TLB walk hardware
- [ ] make the TLB walk hardware
- [ ] add the aborts in specific places
- [ ] create the abort handlers
- [ ] replace the swap_bits with something more reliable
- [ ] write the reference page for each instruction 


- search "on reset" to see what kind of stuff needs to be set up upon a reset



notes:
- big endian in v1 and v2 while little by default in v3 and above (source: https://en.wikipedia.org/wiki/ARM_architecture_family)

- [ ] A1
- [ ] A2
- [ ] A3
- [ ] A4
- [ ] A5
- [ ] A6
- [ ] A7
- [ ] A8 (WORKING)
- [ ] A9
- [ ] A10

- [ ] B1
- [ ] B2
- [ ] B3
- [ ] B4
- [ ] B5
- [ ] B6

- [ ] C1
- [ ] C2
- [ ] C3
- [ ] C4
- [ ] C5

- [ ] make the unpredictable notifier once everything is done