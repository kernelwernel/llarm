#pragma once

#include "id.hpp"


inline void warning([[maybe_unused]] const char* warning) {
// TODO add switches here
}


[[noreturn]] inline void error([[maybe_unused]] const char* error) {
// TODO add switches here
    std::exit(1);
}


inline void dev_warning([[maybe_unused]] const char* error) {
// TODO add switches here
}


[[noreturn]] inline void dev_error([[maybe_unused]] const char* error) {
// TODO add switches here
    std::exit(1);
}


inline u32 unpredictable ([[maybe_unused]] const char* message) {
    // add message here
    return 0;
}
