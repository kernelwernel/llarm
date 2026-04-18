#pragma once

#include "../id/instruction_id.hpp"

#include <string>


namespace internal::ident::string_thumb {
    thumb_id thumb(const std::string& code);
}