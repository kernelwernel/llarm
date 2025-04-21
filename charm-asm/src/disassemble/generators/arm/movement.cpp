#include "../generators.hpp"
#include "../util.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"
#include "shared/out.hpp"

#include <string>
#include <sstream>

using namespace internal;

            std::string MOV(const u32);
            std::string MVN(const u32);
            std::string MRS(const u32);
            std::string MSR_IMM(const u32);
            std::string MSR_REG(const u32);