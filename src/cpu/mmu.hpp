#include "ram.hpp"

struct MMU {
private:
    RAM& ram;

public:
    auto address_translation();

    MMU(RAM& ram) : ram(ram) {
        
    }
};