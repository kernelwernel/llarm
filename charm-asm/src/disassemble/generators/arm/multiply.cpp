#include "../generators.hpp"
#include "../util.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"
#include "shared/out.hpp"

#include <string>
#include <sstream>

using namespace internal;

            std::string MLA(const u32);
            std::string MUL(const u32);
            std::string SMLAL(const u32);
            std::string SMULL(const u32);
            std::string UMLAL(const u32);
            std::string UMULL(const u32);