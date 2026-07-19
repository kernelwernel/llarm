#include "../core/exception.hpp"
#include "mmu.hpp"
#include "mpu.hpp"
#include "../../ram/ram.hpp"
#include "fcse.hpp"
#include "26_bit_arch.hpp"

#include "memory.hpp"

#include <llarm/shared/types.hpp>


void MEMORY::manage_abort(const id::aborts abort_code, const id::access_type access_type) {
    switch (abort_code) {
        case id::aborts::NO_ABORT: return;
        case id::aborts::ALIGNMENT:
        case id::aborts::ABORT:
        case id::aborts::VECTOR:
        case id::aborts::TERMINAL:
        case id::aborts::ADDRESS_EXCEPTION:
        case id::aborts::SECTION_TRANSLATION:
        case id::aborts::PAGE_TRANSLATION:
        case id::aborts::PAGE_DOMAIN:
        case id::aborts::SUB_PAGE_PERMISSION:
        case id::aborts::SECTION_DOMAIN:
        case id::aborts::SECTION_PERMISSION:
            if (access_type == id::access_type::INSTRUCTION_FETCH) {
                exception.prefetch_abort();
            } else {
                exception.data_abort();
            }
            return;
        case id::aborts::PREFETCH_ABORT: exception.prefetch_abort(); return;
    }
}


mem_write_struct MEMORY::write(u32 address, const u64 value, const u8 access_size) {
    if (arch_26.is_26_arch_backwards_compatible()) {
        if (
            (arch_26.is_26_arch_address()) &&
            (arch_26.is_26_arch_address_unsupported(address))
        ) {
            exception.address_exception_26(reg.read(id::reg::PC));
            return mem_write_struct {
                /* has_failed */ true,
                /* abort_code */ id::aborts::ADDRESS_EXCEPTION
            };
        }
    }

    if (fcse.is_fcse_enabled()) {
        address = fcse.modify_address(address);
    }

    if (mmu.is_mmu_enabled()) {
        return mmu.write(address, value, access_size);
    }

    if (mpu.is_mpu_enabled()) {
        return mpu.write(address, value, access_size);
    }

    if (settings.has_cache && coprocessor.read(id::cp15::R1_C)) {
        cache.write(address, static_cast<u32>(value), access_size, false);
        return mem_write_struct {
            /* has_failed */ false,
            /* abort_code */ id::aborts::NO_ABORT
        };
    }

    ram.write(address, value, access_size);

    return mem_write_struct {
        /* has_failed */ false,
        /* abort_code */ id::aborts::NO_ABORT,
    };
}


mem_read_struct MEMORY::read(
    u32 address,
    const u8 access_size,
    const id::access_type access_type
) {
    if (arch_26.is_26_arch_backwards_compatible()) {
        if (
            (arch_26.is_26_arch_address()) &&
            (arch_26.is_26_arch_address_unsupported(address))
        ) {
            exception.address_exception_26(reg.read(id::reg::PC));
            return mem_read_struct {
                /* has_failed  */ true,
                /* abort_code  */ id::aborts::ADDRESS_EXCEPTION,
                /* access_size */ access_size,
                /* value       */ 0
            };
        }
    }

    if (fcse.is_fcse_enabled()) {
        address = fcse.modify_address(address);
    }

    if (mmu.is_mmu_enabled()) {
        return mmu.read(address, access_size, access_type);
    }

    if (mpu.is_mpu_enabled()) {
        return mpu.read(address, access_size, access_type);
    }

    // horrendous nesting and indentation, find a way to de-nest this garbage TODO
    if (settings.has_cache) {
        if (access_type == id::access_type::INSTRUCTION_FETCH) {
            const bool inst_cache_on = settings.has_unified_cache
                ? coprocessor.read(id::cp15::R1_C)
                : coprocessor.read(id::cp15::R1_I);

            if (inst_cache_on) {
                return mem_read_struct {
                    /* has_failed  */ false,
                    /* abort_code  */ id::aborts::NO_ABORT,
                    /* access_size */ access_size,
                    /* value       */ cache.fetch_inst(address)
                };
            }
        } else {
            if (coprocessor.read(id::cp15::R1_C)) {
                return mem_read_struct {
                    /* has_failed  */ false,
                    /* abort_code  */ id::aborts::NO_ABORT,
                    /* access_size */ access_size,
                    /* value       */ cache.read(address, false)
                };
            }
        }
    }

    const u64 data = ram.read(address, access_size);

    return mem_read_struct {
        /* has_failed  */ false,
        /* abort_code  */ id::aborts::NO_ABORT,
        /* access_size */ access_size,
        /* value       */ data
    };
}


u32 MEMORY::resolve_physical_address(u32 address) {
    if (fcse.is_fcse_enabled()) {
        address = fcse.modify_address(address);
    }

    if (mmu.is_mmu_enabled()) {
        const translation_struct translation = mmu.translate_address(address, id::access_type::READ);

        if (!translation.has_failed) {
            return translation.physical_address;
        }
    }

    return address; // MPU or flat memory: physical address matches the virtual address
}


void MEMORY::mark_exclusive_local(const u32 physical_address) {
    exclusive_valid = true;
    exclusive_address = physical_address;
}


bool MEMORY::is_exclusive_local(const u32 physical_address) const {
    return (exclusive_valid) && (exclusive_address == physical_address);
}


void MEMORY::clear_exclusive_local() {
    exclusive_valid = false;
}


void MEMORY::reset() {
    if (mmu.is_mmu_enabled()) {
        mmu.reset(); // this also resets the TLB
    } else if (mpu.is_mpu_enabled()) {
        mpu.reset();
    }

    clear_exclusive_local();
}