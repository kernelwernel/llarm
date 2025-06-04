#include "../../../id.hpp"
#include "../../instruction_set.hpp"

#include "decode.hpp"

#include "shared/types.hpp"

#include <llarm-asm/llarm-asm.hpp>


bool DECODE::condition_match(const id::cond cond) const {
    return (reg.check_cond(cond));
}


arm_decode_struct DECODE::arm_decode(const arm_code_t &raw_code) const {
    id::cond cond = reg.fetch_cond_id(raw_code);

    if (condition_match(cond)) {
        return arm_decode_struct {
            llarm::as::identify::arm(raw_code), // id
            raw_code // code
        };
    }

    return arm_decode_struct {
        llarm::as::id::arm::NOP, // id
        arm_code_t(0) // code
    };
}


thumb_decode_struct DECODE::thumb_decode(const thumb_code_t &raw_code) const {
    return thumb_decode_struct {
        llarm::as::identify::thumb(raw_code), // id
        raw_code // code
    };
}


llarm::as::id::jazelle DECODE::jazelle_decode(const u8 raw_code) const {
    return llarm::as::identify::jazelle(raw_code);
}


DECODE::DECODE(
    INSTRUCTION_SET& inst_set,
    REGISTERS& reg,
    SETTINGS& settings
) : inst_set(inst_set), reg(reg), settings(settings) {

}