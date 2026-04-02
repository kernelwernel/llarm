#pragma once
#include "llarm-cpu.h"

namespace llarm::cpu {
    inline unsigned int fetch_midr() { 
        return llarm_cpu_fetch_midr();
    }

    inline bool is_pre_arm7() { 
        return llarm_cpu_is_pre_arm7();
    }

    inline bool is_arm7() { 
        return llarm_cpu_is_arm7();
    }

    inline bool is_post_arm7() { 
        return llarm_cpu_is_post_arm7();
    }

    inline unsigned int fetch_revision() { 
        return llarm_cpu_fetch_revision();
    }

    inline unsigned int fetch_ppn() { 
        return llarm_cpu_fetch_ppn();
    }

    inline unsigned int fetch_variant() { 
        return llarm_cpu_fetch_variant();
    }

    inline enum implementor fetch_implementor() { 
        return llarm_cpu_fetch_implementor();
    }

    inline const char* fetch_implementor_string() { 
        return llarm_cpu_fetch_implementor_string();
    }

    inline enum product fetch_product() { 
        return llarm_cpu_fetch_product();
    }

    inline const char* fetch_product_string(enum product p) { 
        return llarm_cpu_fetch_product_string(p);
    }

    inline enum arch fetch_arch() { 
        return llarm_cpu_fetch_arch();
    }

    inline const char* fetch_arch_string(enum arch a) { 
        return llarm_cpu_fetch_arch_string(a);
    }
}
