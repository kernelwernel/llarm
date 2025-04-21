#include "../generators.hpp"
#include "../util.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"
#include "shared/out.hpp"

#include <string>
#include <sstream>

using namespace internal;

            std::string NOP(const u32);
            std::string PSR(const u32);
            std::string SWI(const u32);