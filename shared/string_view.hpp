#include "lib/string-view-lite/include/nonstd/string_view.hpp"

// This lib is mainly used for string interpretation in llarm-asm.
// The reason why this is used is because llarm-asm has heavy usage
// of string_views, but the fact that it was introduced in C++17
// makes it a nonstarter, as I'm aiming to support at least C++11.
// So to compensate, I've imported this header-only lib to make this
// possible as it supports C++98. 

namespace llarm {
    using string_view = nonstd::string_view;
}