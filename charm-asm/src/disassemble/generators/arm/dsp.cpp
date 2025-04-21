#include "../generators.hpp"
#include "../util.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"
#include "shared/out.hpp"

#include <string>
#include <sstream>

using namespace internal;


            std::string LDRD(const u32);
            std::string MCRR(const u32);
            std::string MRRC(const u32);
            std::string PLD(const u32);
            std::string QADD(const u32);
            std::string QDADD(const u32);
            std::string QDSUB(const u32);
            std::string QSUB(const u32);
            std::string SMLA(const u32);
            std::string SMLAL(const u32);
            std::string SMLAW(const u32);
            std::string SMUL(const u32);
            std::string SMULW(const u32);
            std::string STRD(const u32);