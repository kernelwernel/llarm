#include "ram.hpp"

struct TLB {
private:
    RAM& ram;

public:
    void invalidate() {}
    void table_walk() {}

    // Holds both section translations and pointers to second-level tables.
    std::map first_level<> {

    };

    // Hold both large and small page translations. One type of second-level 
    // table can also hold tiny page translations.
    std::map second_level<> {

    };


    TLB(RAM& ram) : ram(ram) {
        
    }
};