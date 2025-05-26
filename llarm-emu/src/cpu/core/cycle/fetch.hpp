#pragma once

#include "../../memory/memory.hpp"

#include "shared/types.hpp"

struct arm_fetch_struct {
    arm_code_t code;
    bool has_failed;
};

struct thumb_fetch_struct {
    thumb_code_t code;
    bool has_failed;
};


struct FETCH {
private:
    REGISTERS& reg;
    MEMORY& memory;
    GLOBALS& globals;

public:

    arm_fetch_struct arm_fetch();

    thumb_fetch_struct thumb_fetch();

    //jazelle_code_t jazelle_fetch() const;


    FETCH(
        REGISTERS& reg,
        MEMORY& memory,
        GLOBALS& globals
    );
};