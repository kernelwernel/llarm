- [ ] Prior to ARM architecture version 3, a condition field of 0b1111 meant that the instruction was never executed. The mnemonic extension for this condition was NV.

- [ ] reorder the opcodes so that opcodes that take in the MOST bits should be analysed first, and the least ones goes to the bottom of the table


- search "on reset" to see what kind of stuff needs to be set up upon a reset in the docs
- add noexcept throughout the code


notes:
- big endian in v1 and v2 while little by default in v3 and above (source: https://en.wikipedia.org/wiki/ARM_architecture_family)


- try the bolt post-link optimiser, looks super interesting and promising
- try [[gnu::pure]] and [[gnu::const]] optimisation opportunities
- allow for json settings files as an input argument for the emulator
- rewrite the whole decode (identifier) and execute cycle phases so that they use switches instead of std::maps
- install flamegraph and measure the difference between the std::map<key, std::function> thingy and the switch
- in the future, make a more "memory friendly" option such as making an inner virtual memory system for the memory 
  by using std::vector instead of std::array for the RAM, and using std::vector instead of std::unordered_map for the TLB lookup
- use a better alternative to std::unordered_map that's faster (https://martin.ankerl.com/2022/08/27/hashmap-bench-01/)
- remove the model of minimal types being used for local variables and function parameters, this has almost no benefit on performance. Use a u32 instead of a u8.
- implement LLARM_LOW_MEMORY preprocessor argument

- work on the cache
- finish the VFP extension
- implement the TLB lockdown