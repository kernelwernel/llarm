#pragma once

#include "../../memory/memory.hpp"

#include <llarm/shared/types.hpp>

struct arm_fetch_struct {
    u32 code;
    bool has_failed;
};

struct thumb_fetch_struct {
    u16 code;
    bool has_failed;
};


struct FETCH {

    REGISTERS& reg;
    MEMORY& memory;
    GLOBALS& globals;



    arm_fetch_struct arm_fetch();

    thumb_fetch_struct thumb_fetch();

    //jazelle_code_t jazelle_fetch() const;


    FETCH(
        REGISTERS& reg,
        MEMORY& memory,
        GLOBALS& globals
    );
};