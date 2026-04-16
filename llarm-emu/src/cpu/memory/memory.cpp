#include "../core/exception.hpp"
#include "mmu.hpp"
#include "mpu.hpp"
#include "ram.hpp"
#include "fcse.hpp"
#include "26_bit_arch.hpp"

#include "memory.hpp"

#include <llarm/shared/types.hpp>


void MEMORY::manage_abort(const id::aborts abort_code) {
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
        case id::aborts::SECTION_PERMISSION: exception.data_abort(); return;
        case id::aborts::PREFETCH_ABORT: exception.prefetch_abort(); return;
    }
}


mem_write_struct MEMORY::write(const u64 value, u32 address, const u8 access_size) {
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
    } else if (mpu.is_mpu_enabled()) {
        return mpu.write(address, value, access_size);
    }

    ram.write(value, address, access_size);

    return mem_write_struct {
        /* has_failed */ false,
        /* abort_code */ id::aborts::NO_ABORT,
    };
}


mem_read_struct MEMORY::read(
    u32 address,
    const u8 access_size
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
        return mmu.read(address, access_size);
    } else if (mpu.is_mpu_enabled()) {
        return mpu.read(address, access_size);
    }

    const u64 data = ram.read(address, access_size);

    return mem_read_struct {
        /* has_failed  */ false,
        /* abort_code  */ id::aborts::NO_ABORT,
        /* access_size */ access_size,
        /* value       */ data
    };
}


void MEMORY::reset() {
    if (mmu.is_mmu_enabled()) {
        mmu.reset(); // this also resets the TLB
    } else if (mpu.is_mpu_enabled()) {
        mpu.reset();
    }
}