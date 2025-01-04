- [ ] Prior to ARM architecture version 3, a condition field of 0b1111 meant that the instruction was never
executed. The mnemonic extension for this condition was NV.

- [ ] reorder the opcodes so that opcodes that take in the MOST bits should be analysed first, and the least ones goes to the bottom of the table

- [ ] figure out how to deal with the BKPT instruction

- [ ] make the MMU
- [ ] make the coprocessor
- [ ] add an UNPREDICTABLE message throughout every part of the emulator once it's complete (based on the docs)
- [ ] add jazelle support
- [ ] add 26-bit support
- [ ] figure out a good mechanism for reading/writing to cp registers
- [ ] replace the cp15 writing lambdas with utility functions
- [ ] finish making the cp15 control register 1 