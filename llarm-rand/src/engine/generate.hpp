#pragma once

#include "../params.hpp"
#include "../settings.hpp"

#include <llarm/shared/types.hpp>

#include <vector>

#include <llarm/llarm-asm.hpp>


struct generate {
private:
    // these are specific to settings.occasional_cond_switch
    u8 current_cond;
    u8 cond_switch_count;

public:
    param_struct make_params(const settings_struct settings);
    u32 make_instruction(const settings_struct settings);
    std::vector<u32> make_blueprint();

};