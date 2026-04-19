#include "../../id.hpp"
#include "../../settings.hpp"
#include "registers.hpp"

#include "addressing_modes.hpp"

#include <vector>

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>
#include <llarm/shared/out.hpp>


single_encoding_struct VFP_ADDRESS_MODE::single_precision(const u32 code) const {
    const u8 Fd = llarm::util::bit_range<u8>(code, 12, 15);
    const u8 Fn = llarm::util::bit_range<u8>(code, 16, 19);
    const u8 Fm = llarm::util::bit_range<u8>(code, 0, 3);

    const bool D = llarm::util::bit_fetch(code, 22);
    const bool N = llarm::util::bit_fetch(code, 7);
    const bool M = llarm::util::bit_fetch(code, 5);

    const u8 d_num = static_cast<u8>((Fd << 1) | D);
    const u8 n_num = static_cast<u8>((Fn << 1) | N);
    const u8 m_num = static_cast<u8>((Fm << 1) | M);

    const u8 d_bank = llarm::util::bit_range<u8>(d_num, 3, 4);

    /**
     * ===== scalar submode =====
     *
     * if d_bank == 0 then
     *     vec_len = 1
     *     Sd[0] = d_num
     *     Sn[0] = n_num
     *     Sm[0] = m_num
     */
    if (d_bank == 0) {
        // the ARM docs make it seem like it's doing something,
        // but the operation is completely redundant as it
        // basically boils down to Sx = Sx, which is pointless.

        single_reg_struct regs {
            /* Sd */ vfp_reg.fetch_single_reg_id(d_num),
            /* Sn */ vfp_reg.fetch_single_reg_id(n_num),
            /* Sm */ vfp_reg.fetch_single_reg_id(m_num)
        };

        return single_encoding_struct {
            /* vec_len */ 1,
            /* vec_regs */ { regs }
        };
    }

    const u8 n_bank = llarm::util::bit_range<u8>(n_num, 3, 4);
    const u8 m_bank = llarm::util::bit_range<u8>(m_num, 3, 4);

    u8 d_index = llarm::util::bit_range<u8>(d_num, 0, 2);
    u8 n_index = llarm::util::bit_range<u8>(n_num, 0, 2);
    u8 m_index = llarm::util::bit_range<u8>(m_num, 0, 2);

    const u8 vec_len = static_cast<u8>(vfp_reg.read(id::vfp_reg::FPSCR_LEN));
    const u8 stride = static_cast<u8>(vfp_reg.read(id::vfp_reg::FPSCR_STRIDE));

    
    /**
     * ===== mixed submode =====
     *
     * if d_bank != 0 and m_bank == 0 then
     *     vec_len = vector length specified by FPSCR
     *     for i = 0 to vec_len-1
     *         Sd[i] = (d_bank << 3) | d_index
     *         Sn[i] = (n_bank << 3) | n_index
     *         Sm[i] = m_num
     *         d_index = d_index + (vector stride specified by FPSCR)
     *         if d_index > 7 then
     *             d_index = d_index - 8
     *         n_index = n_index + (vector stride specified by FPSCR)
     *         if n_index > 7 then
     *             n_index = n_index - 8
     */
    if (m_bank == 0) { // d_bank cond is already true
        std::vector<single_reg_struct> vec_regs = {};
        
        const id::vfp_reg Sm_id = vfp_reg.fetch_single_reg_id(m_num);

        for (u8 i = 0; i < vec_len - 1; i++) {
            const single_reg_struct regs = {
                /* Sd */ vfp_reg.fetch_single_reg_id(static_cast<u8>(d_bank << 3) | d_index),
                /* Sn */ vfp_reg.fetch_single_reg_id(static_cast<u8>(n_bank << 3) | n_index),
                /* Sm */ Sm_id
            };

            d_index += stride;

            if (d_index > 7) {
                d_index -= 8;
            }

            n_index += stride;

            if (n_index > 7) {
                n_index -= 8;
            }

            vec_regs.push_back(regs);
        }

        return single_encoding_struct {
            vec_len,
            vec_regs
        };
    }


    /**
     * ===== vector submode =====
     * 
     * if d_bank != 0 and m_bank != 0 then
     *     vec_len = vector length specified by FPSCR
     *     for i = 0 to vec_len-1
     *         Sd[i] = (d_bank << 3) | d_index
     *         Sn[i] = (n_bank << 3) | n_index
     *         Sm[i] = (m_bank << 3) | m_index
     *         d_index = d_index + (vector stride specified by FPSCR)
     *         if d_index > 7 then
     *             d_index = d_index - 8
     *         n_index = n_index + (vector stride specified by FPSCR)
     *         if n_index > 7 then
     *             n_index = n_index - 8
     *         m_index = m_index + (vector stride specified by FPSCR)
     *         if m_index > 7 then
     *             m_index = m_index - 8
     */
     // d_bank and m_bank conds are already true, no check needed
    std::vector<single_reg_struct> vec_regs = {};

    for (u8 i = 0; i < vec_len - 1; i++) {
        const single_reg_struct regs = {
            /* Sd */ vfp_reg.fetch_single_reg_id(static_cast<u8>(d_bank << 3) | d_index),
            /* Sn */ vfp_reg.fetch_single_reg_id(static_cast<u8>(n_bank << 3) | n_index),
            /* Sm */ vfp_reg.fetch_single_reg_id(static_cast<u8>(m_bank << 3) | m_index)
        };

        d_index += stride;

        if (d_index > 7) {
            d_index -= 8;
        }

        n_index += stride;

        if (n_index > 7) {
            n_index -= 8;
        }

        m_index += stride;

        if (m_index > 7) {
            m_index -= 8;
        }

        vec_regs.push_back(regs);
    }

    return single_encoding_struct {
        vec_len,
        vec_regs
    };
}


single_encoding_struct VFP_ADDRESS_MODE::single_precision_monadic(const u32 code) const {
    const u8 Fd = llarm::util::bit_range<u8>(code, 12, 15);
    const u8 Fm = llarm::util::bit_range<u8>(code, 0, 3);

    const bool D = llarm::util::bit_fetch(code, 22);
    const bool M = llarm::util::bit_fetch(code, 5);

    const u8 d_num = static_cast<u8>((Fd << 1) | D);
    const u8 m_num = static_cast<u8>((Fm << 1) | M);

    const u8 d_bank = llarm::util::bit_range<u8>(d_num, 3, 4);
    
    /**
     * ===== scalar-to-scalar submode =====
     *
     * if d_bank == 0 then
     *     vec_len = 1
     *     Sd[0] = d_num
     *     Sm[0] = m_num
     */
    if (d_bank == 0) {
        const single_reg_struct regs {
            /* Sd */ vfp_reg.fetch_single_reg_id(d_num),
            /* Sn */ id::vfp_reg::UNKNOWN,
            /* Sm */ vfp_reg.fetch_single_reg_id(m_num)
        };

        return single_encoding_struct {
            /* vec_len */ 1,
            /* vec_regs */ { regs }
        };
    }

    const u8 m_bank = llarm::util::bit_range<u8>(m_num, 3, 4);

    u8 d_index = llarm::util::bit_range<u8>(d_num, 0, 2);
    u8 m_index = llarm::util::bit_range<u8>(m_num, 0, 2);

    const u8 vec_len = static_cast<u8>(vfp_reg.read(id::vfp_reg::FPSCR_LEN));
    const u8 stride = static_cast<u8>(vfp_reg.read(id::vfp_reg::FPSCR_STRIDE));

    /**
     * ===== scalar-to-vector submode =====
     *
     * if d_bank != 0 and m_bank == 0 then
     *     vec_len = vector length specified by FPSCR
     *     for i = 0 to vec_len-1
     *         Sd[i] = (d_bank << 3) | d_index
     *         Sm[i] = m_num
     *         d_index = d_index + (vector stride specified by FPSCR)
     *         if d_index > 7 then
     *             d_index = d_index - 8
     */
    if (m_bank == 0) { // d_bank cond is already true
        std::vector<single_reg_struct> vec_regs = {};

        const id::vfp_reg Sm_id = vfp_reg.fetch_single_reg_id(m_num);

        for (u8 i = 0; i < vec_len - 1; i++) {
            const single_reg_struct regs = {
                /* Sd */ vfp_reg.fetch_single_reg_id(static_cast<u8>(d_bank << 3) | d_index),
                /* Sn */ id::vfp_reg::UNKNOWN,
                /* Sm */ Sm_id
            };

            d_index += stride;

            if (d_index > 7) {
                d_index -= 8;
            }

            vec_regs.push_back(regs);
        }

        return single_encoding_struct {
            vec_len,
            vec_regs
        };
    }


    /**
     * ===== vector-to-vector submode =====
     *
     * if d_bank != 0 and m_bank != 0 then
     *     vec_len = vector length specified by FPSCR
     *     for i = 0 to vec_len-1
     *         Sd[i] = (d_bank << 3) | d_index
     *         Sm[i] = (m_bank << 3) | m_index
     *         d_index = d_index + (vector stride specified by FPSCR)
     *         if d_index > 7 then
     *             d_index = d_index - 8
     *         m_index = m_index + (vector stride specified by FPSCR)
     *         if m_index > 7 then
     *             m_index = m_index - 8
     *
     */
    // d_bank and m_bank conds are already true, no check needed
    std::vector<single_reg_struct> vec_regs = {};

    for (u8 i = 0; i < vec_len - 1; i++) {
        const single_reg_struct regs = {
            /* Sd */ vfp_reg.fetch_single_reg_id(static_cast<u8>(d_bank << 3) | d_index),
            /* Sn */ id::vfp_reg::UNKNOWN,
            /* Sm */ vfp_reg.fetch_single_reg_id(static_cast<u8>(m_bank << 3) | m_index),
        };

        d_index += stride;

        if (d_index > 7) {
            d_index -= 8;
        }

        m_index += stride;

        if (m_index > 7) {
            m_index -= 8;
        }

        vec_regs.push_back(regs);
    }

    return single_encoding_struct {
        vec_len,
        vec_regs
    };
}


double_encoding_struct VFP_ADDRESS_MODE::double_precision(const u32 code) const {
    const u8 Dd = llarm::util::bit_range<u8>(code, 12, 15);
    const u8 Dn = llarm::util::bit_range<u8>(code, 16, 19);
    const u8 Dm = llarm::util::bit_range<u8>(code, 0, 3);

    const u8 d_bank = llarm::util::bit_range<u8>(Dd, 2, 3);
    
    /**
     * ===== scalar submode =====
     *
     * if d_bank == 0 then
     *     vec_len = 1
     *     Dd[0] = Dd
     *     Dn[0] = Dn
     *     Dm[0] = Dm
     */
    if (d_bank == 0) {
        const double_reg_struct regs = {
            /* Dd */ vfp_reg.fetch_double_reg_id(Dd),
            /* Dn */ vfp_reg.fetch_double_reg_id(Dn),
            /* Dm */ vfp_reg.fetch_double_reg_id(Dm)
        };   

        return double_encoding_struct {
            /* vec_len */ 1,
            /* vec_regs */ { regs }
        };
    }

    const u8 n_bank = llarm::util::bit_range<u8>(Dn, 2, 3);
    const u8 m_bank = llarm::util::bit_range<u8>(Dm, 2, 3);
    
    u8 d_index = llarm::util::bit_range<u8>(Dd, 0, 1);
    u8 n_index = llarm::util::bit_range<u8>(Dn, 0, 1);
    u8 m_index = llarm::util::bit_range<u8>(Dm, 0, 1);

    const u8 vec_len = static_cast<u8>(vfp_reg.read(id::vfp_reg::FPSCR_LEN));
    const u8 stride = static_cast<u8>(vfp_reg.read(id::vfp_reg::FPSCR_STRIDE));

    /**
     * ===== mixed submode =====
     *
     * if d_bank != 0 and m_bank == 0 then
     *     vec_len = vector length specified by FPSCR
     *     for i = 0 to vec_len-1
     *         Dd[i] = (d_bank << 2) | d_index
     *         Dn[i] = (n_bank << 2) | n_index
     *         Dm[i] = Dm
     *         d_index = d_index + (vector stride specified by FPSCR)
     *         if d_index > 3 then
     *             d_index = d_index - 4
     *         n_index = n_index + (vector stride specified by FPSCR)
     *         if n_index > 3 then
     *             n_index = n_index - 4
     */
    if (m_bank == 0) { // d_bank cond is already true
        std::vector<double_reg_struct> vec_regs = {};

        const id::vfp_reg Dm_id = vfp_reg.fetch_double_reg_id(Dm);

        for (u8 i = 0; i < vec_len - 1; i++) {
            const double_reg_struct regs = {
                /* Dd */ vfp_reg.fetch_double_reg_id(static_cast<u8>(d_bank << 2) | d_index),
                /* Dn */ vfp_reg.fetch_double_reg_id(static_cast<u8>(n_bank << 2) | n_index),
                /* Dm */ Dm_id
            };

            d_index += stride;

            if (d_index > 3) {
                d_index -= 4;
            }

            n_index += stride;

            if (n_index > 3) {
                n_index -= 4;
            }

            vec_regs.push_back(regs);
        }

        return double_encoding_struct {
            vec_len,
            vec_regs
        };
    }


    /**
     * ===== vector submode =====
     * 
     * if d_bank != 0 and m_bank != 0 then
     *     vec_len = vector length specified by FPSCR
     *     for i = 0 to vec_len-1
     *         Dd[i] = (d_bank << 2) | d_index
     *         Dn[i] = (n_bank << 2) | n_index
     *         Dm[i] = (m_bank << 2) | m_index
     *         d_index = d_index + (vector stride specified by FPSCR)
     *         if d_index > 3 then
     *             d_index = d_index - 4
     *         n_index = n_index + (vector stride specified by FPSCR)
     *         if n_index > 3 then
     *             n_index = n_index - 4
     *         m_index = m_index + (vector stride specified by FPSCR)
     *         if m_index > 3 then
     *             m_index = m_index - 4
     */
    // d_bank and m_bank conds are already true, no check needed
    std::vector<double_reg_struct> vec_regs = {};

    for (u8 i = 0; i < vec_len - 1; i++) {
        const double_reg_struct regs = {
            /* Dd */ vfp_reg.fetch_double_reg_id(static_cast<u8>(d_bank << 2) | d_index),
            /* Dn */ vfp_reg.fetch_double_reg_id(static_cast<u8>(n_bank << 2) | n_index),
            /* Dm */ vfp_reg.fetch_double_reg_id(static_cast<u8>(m_bank << 2) | m_index),
        };

        d_index += stride;

        if (d_index > 3) {
            d_index -= 4;
        }

        n_index += stride;

        if (n_index > 3) {
            n_index -= 4;
        }

        m_index += stride;

        if (m_index > 3) {
            m_index -= 4;
        }

        vec_regs.push_back(regs);
    }

    return double_encoding_struct {
        vec_len,
        vec_regs
    };
}


double_encoding_struct VFP_ADDRESS_MODE::double_precision_monadic(const u32 code) const {
    const u8 Dd = llarm::util::bit_range<u8>(code, 12, 15);
    const u8 Dm = llarm::util::bit_range<u8>(code, 0, 3);

    const u8 d_bank = llarm::util::bit_range<u8>(Dd, 2, 3);

    /**
     * ===== scalar-to-scalar submode =====
     *
     * if d_bank == 0 then
     *     vec_len = 1
     *     Dd[0] = Dd
     *     Dm[0] = Dm
     */
    if (d_bank == 0) {
        const double_reg_struct regs = {
            /* Dd */ vfp_reg.fetch_double_reg_id(Dd),
            /* Dn */ id::vfp_reg::UNKNOWN,
            /* Dm */ vfp_reg.fetch_double_reg_id(Dm)
        };   

        return double_encoding_struct {
            /* vec_len */ 1,
            /* vec_regs */ { regs }
        };
    }

    //const u8 Dn = llarm::util::bit_range<u8>(code, 16, 19);

    //const u8 n_bank = llarm::util::bit_range<u8>(Dn, 2, 3);
    const u8 m_bank = llarm::util::bit_range<u8>(Dm, 2, 3);

    u8 d_index = llarm::util::bit_range<u8>(Dd, 0, 1);
    //u8 n_index = llarm::util::bit_range<u8>(Dn, 0, 1);
    u8 m_index = llarm::util::bit_range<u8>(Dm, 0, 1);

    const u8 vec_len = static_cast<u8>(vfp_reg.read(id::vfp_reg::FPSCR_LEN));
    const u8 stride = static_cast<u8>(vfp_reg.read(id::vfp_reg::FPSCR_STRIDE));

    /**
     * ===== scalar-to-vector submode =====
     *
     * if d_bank != 0 and m_bank == 0 then
     *     vec_len = vector length specified by FPSCR
     *     for i = 0 to vec_len-1
     *         Dd[i] = (d_bank << 2) | d_index
     *         Dm[i] = m_num
     *         d_index = d_index + (vector stride specified by FPSCR)
     *         if d_index > 3 then
     *             d_index = d_index - 4
     */
    if (m_bank == 0) { // d_bank cond is already true
        std::vector<double_reg_struct> vec_regs = {};

        const id::vfp_reg Dm_id = vfp_reg.fetch_double_reg_id(Dm);

        for (u8 i = 0; i < vec_len - 1; i++) {
            const double_reg_struct regs = {
                /* Dd */ vfp_reg.fetch_double_reg_id(static_cast<u8>(d_bank << 2) | d_index),
                /* Dn */ id::vfp_reg::UNKNOWN,
                /* Dm */ Dm_id
            };

            d_index += stride;

            if (d_index > 3) {
                d_index -= 4;
            }

            vec_regs.push_back(regs);
        }

        return double_encoding_struct {
            vec_len,
            vec_regs
        };
    }


    /**
     * ===== vector-to-vector submode =====
     * 
     * if d_bank != 0 and m_bank != 0 then
     *     vec_len = vector length specified by FPSCR
     *     for i = 0 to vec_len-1
     *         Dd[i] = (d_bank << 2) | d_index
     *         Dm[i] = (m_bank << 2) | m_index
     *         d_index = d_index + (vector stride specified by FPSCR)
     *         if d_index > 3 then
     *             d_index = d_index - 4
     *         m_index = m_index + (vector stride specified by FPSCR)
     *         if m_index > 3 then
     *             m_index = m_index - 4
     */
    // d_bank and m_bank conds are already true, no check needed
    std::vector<double_reg_struct> vec_regs = {};

    for (u8 i = 0; i < vec_len - 1; i++) {
        const double_reg_struct regs = {
            /* Dd */ vfp_reg.fetch_double_reg_id(static_cast<u8>(d_bank << 2) | d_index),
            /* Dn */ id::vfp_reg::UNKNOWN,
            /* Dm */ vfp_reg.fetch_double_reg_id(static_cast<u8>(m_bank << 2) | m_index),
        };

        d_index += stride;

        if (d_index > 3) {
            d_index -= 4;
        }

        m_index += stride;

        if (m_index > 3) {
            m_index -= 4;
        }

        vec_regs.push_back(regs);
    }

    return double_encoding_struct {
        vec_len,
        vec_regs
    };
}


vfp_address_struct VFP_ADDRESS_MODE::vfp_load_multiple(const u32 code) {
    const u8 offset = llarm::util::bit_range<u8>(code, 0, 7);
    const u8 cp_num = llarm::util::bit_range<u8>(code, 8, 11);

    /**
     * ===== unindexed submode =====
     *
     * if (offset[0] == 1) and (cp_num == 0b1011) then // FLDMX or FSTMX
     *     word_count = IMPLEMENTATION DEFINED value (<= offset)
     * else
     *     // Others
     *     word_count = offset
     * start_address = Rn
     * end_address = start_address + 4 * word_count - 4
     */
    if (
        (llarm::util::bit_range(code, 23, 27) == 0b11001) && 
        (llarm::util::bit_fetch(code, 21) == false)
    ) {
        u8 word_count = 0;

        if (
            ((offset & 1) == true) && 
            (cp_num == 0b1011)
        ) {
            word_count = settings.vfp_load_multiple_value;
        } else {
            word_count = offset;
        }

        const u32 start_address = reg.read(code, 16, 19);
        const u32 end_address = start_address + (4 * word_count) - 4;

        return vfp_address_struct {
            start_address,
            end_address
        };
    }


    /**
     * ===== increment submode =====
     *
     * if (offset[0] == 1) and (cp_num == 0b1011) then // FLDMX or FSTMX
     *     word_count = IMPLEMENTATION DEFINED value (<= offset)
     * else // Others
     *     word_count = offset
     * start_address = Rn
     * end_address = start_address + 4 * word_count - 4
     * if ConditionPassed(cond) then
     *     Rn = Rn + 4 * offset
     */
    if (
        (llarm::util::bit_range(code, 23, 27) == 0b11001) && 
        (llarm::util::bit_fetch(code, 21) == true)
    ) {
        u8 word_count = 0;

        if (
            ((offset & 1) == true) && 
            (cp_num == 0b1011) 
        ) {
            word_count = settings.vfp_load_multiple_value;
        } else {
            word_count = offset;
        }

        const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);
        const u32 Rn = reg.read(Rn_id);

        const u32 start_address = Rn;
        const u32 end_address = start_address + (4 * word_count) - 4;

        if (reg.is_cond_valid(code)) {
            reg.write(Rn_id, Rn + (4 * offset));
        }

        return vfp_address_struct {
            start_address,
            end_address
        };
    }


    /**
     * ===== decrement submode =====
     *
     * if (offset[0] == 1) and (cp_num == 0b1011) then // FLDMX or FSTMX
     *     word_count = IMPLEMENTATION DEFINED value (<= offset)
     * else // Others
     *     word_count = offset
     * start_address = Rn - 4 * offset
     * end_address = start_address - 4 * offset + 4 * word_count - 4
     * if ConditionPassed(cond) then
     *     Rn = Rn - 4 * offset
     */
    if (
        (llarm::util::bit_range(code, 23, 27) == 0b11010) && 
        (llarm::util::bit_fetch(code, 21) == true)
    ) {
        u8 word_count = 0;

        if (
            ((offset & 1) == true) && 
            (cp_num == 0b1011) 
        ) {
            word_count = settings.vfp_load_multiple_value;
        } else {
            word_count = offset;
        }

        const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);
        const u32 Rn = reg.read(Rn_id);

        const u32 start_address = Rn - (4 * offset);
        const u32 end_address = start_address - (4 * offset) + (4 * word_count) - 4;

        if (reg.is_cond_valid(code)) {
            reg.write(Rn_id, Rn - (4 * offset));
        }

        return vfp_address_struct {
            start_address,
            end_address
        };
    }

    llarm::out::error("No known instruction configuration for VFP load multiple addressing mode");
}