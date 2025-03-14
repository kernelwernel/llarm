#include "../../../../types.hpp"
#include "../../../../types_extra.hpp"
#include "../../../core/registers.hpp"
#include "../../operation.hpp"

struct ADDRESSING_MODE {
private:
    REGISTERS& reg;
    OPERATION& operation;

public:
    struct data_struct {
        u32 value;
        bool carry;
    };

private:
    data_struct data_process_immediate_mode(const arm_code_t&);
    data_struct data_process_register(const arm_code_t&);
    data_struct data_process_logical_shift_left_immediate(const arm_code_t&);
    data_struct data_process_logical_shift_right_immediate(const arm_code_t&);
    data_struct data_process_arithmetic_shift_right_immediate(const arm_code_t&);
    data_struct data_process_rotate_right_immediate(const arm_code_t&);
    data_struct data_process_logical_shift_left_register(const arm_code_t&);
    data_struct data_process_logical_shift_right_register(const arm_code_t&);
    data_struct data_process_arithmetic_shift_right_register(const arm_code_t&);
    data_struct data_process_rotate_right_register(const arm_code_t&);
    data_struct data_process_rotate_right_extend(const arm_code_t&);


public:
    data_struct data_processing(const arm_code_t&);

    u32 load_store(const arm_code_t&);

    ADDRESSING_MODE(
        REGISTERS& reg, 
        OPERATION& operation
    ) : reg(reg),
        operation(operation) 
    {

    }
};