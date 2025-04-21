#pragma once

#include <charm/internal/charm-asm/src/identifiers/identifiers.hpp>
#include <charm/internal/charm-asm/src/opcodes/opcodes.hpp>
#include <charm/internal/charm-asm/src/instruction_id.hpp>
#include <charm/internal/charm-asm/src/instruction_table.hpp>

namespace charm {
    namespace assembly {
        namespace id {
            // alternatives in case it's under C++17
            using arm = internal::id::arm;
            using thumb = internal::id::thumb;
            using jazelle = internal::id::jazelle;

            //enum class arm : internal::id::arm {};
            //enum class thumb : internal::id::thumb {};
            //enum class jazelle : internal::id::jazelle {};
        }


        namespace identify {
            static id::arm arm(const arm_code_t &raw_code) {
                return internal::identifiers::arm(raw_code);
            }

            static id::arm arm(const u32 &raw_code) {
                return internal::identifiers::arm(raw_code);
            }

            static id::thumb thumb(const thumb_code_t &raw_code) {
                return internal::identifiers::thumb(raw_code);
            }

            static id::thumb thumb(const u16 &raw_code) {
                return internal::identifiers::thumb(raw_code);
            }

            static id::jazelle jazelle(const u8 raw_code) {
                return internal::identifiers::jazelle(raw_code);
            }
        }
    }

    // shortened alias, can't use charm::asm because "asm" is already a C/C++ keyword
    namespace as = assembly;
}
