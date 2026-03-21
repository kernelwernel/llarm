#pragma once

#include "../core/registers.hpp"
#include "../coprocessor/coprocessor.hpp"
#include "../memory/memory.hpp"
#include "../vfp/registers.hpp"
#include "arm/addressing_modes/addressing_modes.hpp"
#include "../vfp/exception.hpp"
#include "../vfp/addressing_modes.hpp"
#include "operation.hpp"

#include <llarm/shared/types.hpp>

struct INSTRUCTIONS {
private:
    REGISTERS& reg;
    ADDRESSING_MODE& address_mode;
    OPERATION& operation;
    COPROCESSOR& coprocessor;
    SETTINGS& settings;
    MEMORY& memory;

public:
    struct arm {
        struct math {
            REGISTERS& reg;
            OPERATION& operation;
            ADDRESSING_MODE& address_mode;

            math(
                REGISTERS& reg, 
                OPERATION& operation,
                ADDRESSING_MODE& address_mode
            ) : reg(reg), operation(operation), address_mode(address_mode) {}
    
            void ADC(const u32 code); // TODO, NOTE: MUST TEST CARRY AND OVERFLOW
            void ADD(const u32 code); // same
            void RSB(const u32 code); // TODO
            void RSC(const u32 code); // TODO
            void SBC(const u32 code); // TODO
            void SUB(const u32 code); // TODO
        } math;

        struct logic {
            REGISTERS& reg;
            OPERATION& operation;
            ADDRESSING_MODE& address_mode;

            logic(
                REGISTERS& reg, 
                OPERATION& operation,
                ADDRESSING_MODE& address_mode
            ) : reg(reg), operation(operation), address_mode(address_mode) {}
    
            void CMN(const u32 code); // TODO
            void AND(const u32 code); // TODO
            void CMP(const u32 code); // TODO
            void CLZ(const u32 code); // (test if this works, manually)
            void EOR(const u32 code); // TODO
            void ORR(const u32 code); // TODO
            void BIC(const u32 code); // TODO
            void TEQ(const u32 code); // TODO
            void TST(const u32 code); // TODO
        } logic;

        struct movement {
            REGISTERS& reg;
            OPERATION& operation;
            ADDRESSING_MODE& address_mode;

            movement(
                REGISTERS& reg, 
                OPERATION& operation,
                ADDRESSING_MODE& address_mode
            ) : reg(reg), operation(operation), address_mode(address_mode) {}
    
            void MOV(const u32 code); // TODO
            void MVN(const u32 code); // TODO
            void MRS(const u32 code); // TODO
            void MSR_IMM(const u32 code);
            void MSR_REG(const u32 code);
        } movement;

        struct multiply {
            REGISTERS& reg;
            OPERATION& operation;

            multiply(REGISTERS& reg, OPERATION& operation) : reg(reg), operation(operation) {}
    
            void MLA(const u32 code); // TODO
            void MUL(const u32 code); // TODO
            void SMLAL(const u32 code); // TODO
            void SMULL(const u32 code); // TODO
            void UMLAL(const u32 code); // TODO
            void UMULL(const u32 code); // TODO
        } multiply;

        struct branching {
            REGISTERS& reg; // Direct reference to the reg object
            OPERATION& operation;

            branching(REGISTERS& reg, OPERATION& operation) : reg(reg), operation(operation) {}
    
            void B(const u32 code); // TODO
            void BL(const u32 code); // TODO
            void BX(const u32 code); // TODO
            void BLX1(/*const u32 code*/); // TODO
            void BLX2(/*const u32 code*/); // TODO
        } branching;

        struct coproc {
            REGISTERS& reg;
            OPERATION& operation;
            ADDRESSING_MODE& address_mode;
            COPROCESSOR& coprocessor;

            coproc(
                REGISTERS& reg, 
                OPERATION& operation, 
                ADDRESSING_MODE& address_mode,
                COPROCESSOR& coprocessor
            ) : reg(reg), operation(operation), address_mode(address_mode), coprocessor(coprocessor) {}
    
            void CDP(/*const u32 code*/); // TODO
            void LDC(/*const u32 code*/); // TODO
            void MCR(const u32 code); // TODO
            void MRC(const u32 code); // TODO
            void STC(/*const u32 code*/); // TODO
            void CDP2(/*const u32 code*/); // TODO
            void LDC2(/*const u32 code*/); // TODO
            void MCR2(const u32 code); // TODO
            void MRC2(const u32 code); // TODO
            void STC2(/*const u32 code*/); // TODO
        } coproc;

        struct misc {
            REGISTERS& reg;
            OPERATION& operation;
            ADDRESSING_MODE& address_mode;
            COPROCESSOR& coprocessor;

            misc(
                REGISTERS& reg, 
                OPERATION& operation,
                ADDRESSING_MODE& address_mode,
                COPROCESSOR& coprocessor
            ) : reg(reg), operation(operation), address_mode(address_mode), coprocessor(coprocessor) {}

            void NOP(const u32 code);
            void PSR(const u32 code);
            void SWI(const u32 code);
            void BKPT(const u32 code);
        } misc;

        struct load {
            REGISTERS& reg;
            OPERATION& operation;
            MEMORY& memory;
            ADDRESSING_MODE& address_mode;
            SETTINGS& settings;

            load(
                REGISTERS& reg, 
                OPERATION& operation, 
                MEMORY& memory,
                ADDRESSING_MODE& address_mode,
                SETTINGS& settings
            ) : reg(reg), 
                operation(operation), 
                memory(memory), 
                address_mode(address_mode), 
                settings(settings) 
            {}
    
            void LDM1(const u32 code); // TODO, ADD CHECK FOR L4 BIT
            void LDM2(const u32 code);
            void LDM3(const u32 code);
            void LDR(const u32 code); // TODO, ADD CHECK FOR L4 BIT
            void LDRB(const u32 code);
            void LDRBT(const u32 code);
            void LDRH(const u32 code);
            void LDRSB(const u32 code);
            void LDRSH(const u32 code);
            void LDRT(const u32 code);
        } load; 

        struct store {
            REGISTERS& reg;
            OPERATION& operation;
            MEMORY& memory;
            ADDRESSING_MODE& address_mode;

            store(
                REGISTERS& reg, 
                OPERATION& operation, 
                MEMORY& memory, 
                ADDRESSING_MODE& address_mode
            ) : reg(reg), 
                operation(operation), 
                memory(memory), 
                address_mode(address_mode)
            {}

            void STM1(const u32 code);
            void STM2(const u32 code);
            void STR(const u32 code);
            void STRB(const u32 code);
            void STRBT(const u32 code);
            void STRH(const u32 code);
            void STRT(const u32 code);
            void SWP(const u32 code);
            void SWPB(const u32 code);
        } store;

        struct dsp {
            REGISTERS& reg;
            OPERATION& operation;
            MEMORY& memory;
            ADDRESSING_MODE& address_mode;
            EXCEPTION& exception;

            dsp(
                REGISTERS& reg, 
                OPERATION& operation, 
                MEMORY& memory,
                ADDRESSING_MODE& address_mode,
                EXCEPTION& exception
            ) : reg(reg), 
                operation(operation), 
                memory(memory),
                address_mode(address_mode),
                exception(exception)
            {

            }
    
            void LDRD(const u32 code); // TODO
            void MCRR(/*const u32 code*/); // TODO
            void MRRC(/*const u32 code*/); // TODO
            void PLD(/*const u32 code*/); // TODO
            void QADD(const u32 code); // TODO
            void QDADD(const u32 code); // TODO
            void QDSUB(const u32 code); // TODO
            void QSUB(const u32 code); // TODO
            void SMLAXY(const u32 code); // TODO
            void SMLALXY(const u32 code); // TODO
            void SMLAWY(const u32 code); // TODO
            void SMULXY(const u32 code); // TODO
            void SMULWY(const u32 code); // TODO
            void STRD(const u32 code); // TODO
        } dsp;

        struct vfp {
            REGISTERS& reg;
            OPERATION& operation;
            COPROCESSOR& coprocessor;
            MEMORY& memory;
            VFP_REG& vfp_reg;
            VFP_EXCEPTION& vfp_exception;
            VFP_ADDRESS_MODE& vfp_addressing_mode;

            vfp(
                REGISTERS& reg, 
                OPERATION& operation, 
                COPROCESSOR& coprocessor,
                MEMORY& memory,
                VFP_REG& vfp_reg,
                VFP_EXCEPTION& vfp_exception,
                VFP_ADDRESS_MODE& vfp_addressing_mode
            ) : reg(reg), 
                operation(operation),
                coprocessor(coprocessor),
                memory(memory),
                vfp_reg(vfp_reg),
                vfp_exception(vfp_exception),
                vfp_addressing_mode(vfp_addressing_mode)
            {

            }
    
            void FABSD(const u32 code); // TODO, D
            void FABSS(const u32 code); // TODO
            void FADDD(const u32 code); // TODO, D
            void FADDS(const u32 code); // TODO
            void FCMPD(const u32 code); // TODO, D
            void FCMPED(const u32 code); // TODO, D
            void FCMPES(const u32 code); // TODO
            void FCMPEZD(const u32 code); // TODO, D
            void FCMPEZS(const u32 code); // TODO
            void FCMPS(const u32 code); // TODO
            void FCMPZD(const u32 code); // TODO, D
            void FCMPZS(const u32 code); // TODO
            void FCPYD(const u32 code); // TODO, D
            void FCPYS(const u32 code); // TODO
            void FCVTDS(const u32 code); // TODO, D
            void FCVTSD(const u32 code); // TODO, D
            void FDIVD(const u32 code); // TODO, D
            void FDIVS(const u32 code); // TODO
            void FLDD(const u32 code); // TODO, D
            void FLDMD(const u32 code); // TODO, D
            void FLDMS(const u32 code); // TODO
            void FLDMX(const u32 code); // TODO
            void FLDS(const u32 code); // TODO
            void FMACD(const u32 code); // TODO, D
            void FMACS(const u32 code); // TODO
            void FMDHR(const u32 code); // TODO, D
            void FMDLR(const u32 code); // TODO, D
            void FMRDH(const u32 code); // TODO, D
            void FMRDL(const u32 code); // TODO, D
            void FMRS(const u32 code); // TODO
            void FMRX(const u32 code); // TODO 
            void FMSCD(const u32 code); // TODO, D
            void FMSCS(const u32 code); // TODO
            void FMSR(const u32 code); // TODO
            void FMSTAT(const u32 code); // TODO
            void FMULD(const u32 code); // TODO, D
            void FMULS(const u32 code); // TODO
            void FMXR(const u32 code); // TODO
            void FNEGD(const u32 code); // TODO, D
            void FNEGS(const u32 code); // TODO
            void FNMACD(const u32 code); // TODO, D
            void FNMACS(const u32 code); // TODO
            void FNMSCD(const u32 code); // TODO, D
            void FNMSCS(const u32 code); // TODO
            void FNMULD(const u32 code); // TODO, D
            void FNMULS(const u32 code); // TODO
            void FSITOD(const u32 code); // TODO, D
            void FSITOS(const u32 code); // TODO
            void FSQRTD(const u32 code); // TODO, D
            void FSQRTS(const u32 code); // TODO
            void FSTD(const u32 code); // TODO, D
            void FSTMD(const u32 code); // TODO, D
            void FSTMS(const u32 code); // TODO
            void FSTMX(const u32 code); // TODO
            void FSTS(const u32 code); // TODO
            void FSUBD(const u32 code); // TODO, D
            void FSUBS(const u32 code); // TODO
            void FTOSID(const u32 code); // TODO, D
            void FTOSIS(const u32 code); // TODO
            void FTOUID(const u32 code); // TODO, D
            void FTOUIS(const u32 code); // TODO
            void FUITOD(const u32 code); // TODO, D
            void FUITOS(const u32 code); // TODO
        } vfp;

        arm(
            REGISTERS& reg, 
            OPERATION& operation,
            ADDRESSING_MODE& address_mode,
            COPROCESSOR& coprocessor,
            MEMORY& memory,
            SETTINGS& settings,
            EXCEPTION& exception,
            VFP_REG& vfp_reg,
            VFP_EXCEPTION& vfp_exception,
            VFP_ADDRESS_MODE& vfp_addressing_mode
        ) : math(reg, operation, address_mode),
            logic(reg, operation, address_mode),
            movement(reg, operation, address_mode),
            multiply(reg, operation),
            branching(reg, operation),
            coproc(reg, operation, address_mode, coprocessor),
            misc(reg, operation, address_mode, coprocessor),
            load(reg, operation, memory, address_mode, settings),
            store(reg, operation, memory, address_mode),
            dsp(reg, operation, memory, address_mode, exception),
            vfp(reg, operation, coprocessor, memory, vfp_reg, vfp_exception, vfp_addressing_mode)
        {

        }
    } arm;



    struct thumb {
        struct math {
            REGISTERS& reg;
            OPERATION& operation;

            math(REGISTERS& reg, OPERATION& operation) : reg(reg), operation(operation) {}

            void ADC(const u16 code);
            void ADD1(const u16 code);
            void ADD2(const u16 code);
            void ADD3(const u16 code);
            void ADD4(const u16 code);
            void ADD5(const u16 code);
            void ADD6(const u16 code);
            void ADD7(const u16 code);
            void SBC(const u16 code); // NOTE: BORROW_SUB (TRIPLE) AND OVERFLOW_SUB (TRIPLE) MIGHT HAVE WRONG IMPL
            void SUB1(const u16 code);
            void SUB2(const u16 code);
            void SUB3(const u16 code);
            void SUB4(const u16 code);
            void MUL(const u16 code);
        } math;

        struct logic {
            REGISTERS& reg;
            OPERATION& operation;

            logic(REGISTERS& reg, OPERATION& operation) : reg(reg), operation(operation) {}
    
            void AND(const u16 code);
            void ASR1(const u16 code); // NOTE: ARITHMETIC_SHIFT_RIGHT IMPLEMENTATION MIGHT BE WRONG
            void ASR2(const u16 code); // NOTE: ARITHMETIC_SHIFT_RIGHT IMPLEMENTATION MIGHT BE WRONG
            void BIC(const u16 code);
            void EOR(const u16 code);
            void LSL1(const u16 code);
            void LSL2(const u16 code);
            void LSR1(const u16 code);
            void LSR2(const u16 code);
            void NEG(const u16 code); // NOTE: OVERFLOW_SUB MIGHT LEAD TO ERROR
            void ORR(const u16 code);
            void ROR(const u16 code);
            void TST(const u16 code);
        } logic;

        struct compare {
            REGISTERS& reg;
            OPERATION& operation;

            compare(REGISTERS& reg, OPERATION& operation) : reg(reg), operation(operation) {}

            void CMN(const u16 code); // NOTE: BORROW_FROM MIGHT LEAD TO ERROR
            void CMP1(const u16 code); // NOTE: OVERFLOW_SUB MIGHT LEAD TO ERROR
            void CMP2(const u16 code); // NOTE: OVERFLOW_SUB MIGHT LEAD TO ERROR
            void CMP3(const u16 code);
        } compare;

        struct movement {
            REGISTERS& reg;
            OPERATION& operation;

            movement(REGISTERS& reg, OPERATION& operation) : reg(reg), operation(operation) {}

            void MOV1(const u16 code);
            void MOV2(const u16 code);
            void MOV3(const u16 code);
            void MVN(const u16 code);
        } movement;

        struct branching {
            REGISTERS& reg;
            OPERATION& operation;

            branching(REGISTERS& reg, OPERATION& operation) : reg(reg), operation(operation) {}

            void B1(const u16 code);
            void B2(const u16 code);
            void BL(const u16 code);
            void BLX1(const u16 code); // (v5, idk if thumb2)
            void BL_BLX1_PREFIX(const u16 code);
            void BLX2(const u16 code); // (v5, idk if thumb2), and double check
            void BX(const u16 code); // double check
        } branching;

        struct misc {
            REGISTERS& reg;
            OPERATION& operation;
            SETTINGS& settings;

            misc(REGISTERS& reg, OPERATION& operation, SETTINGS& settings) : reg(reg), operation(operation), settings(settings) {}

            void NOP(const u16 code);
            void BKPT(const u16 code); // (v5)
            void SWI(const u16 code); // TODO
        } misc;

        struct load {
            REGISTERS& reg;
            OPERATION& operation;
            MEMORY& memory;
            SETTINGS& settings;

            load(
                REGISTERS& reg, 
                OPERATION& operation,
                MEMORY& memory,
                SETTINGS& settings
            ) : reg(reg), operation(operation), memory(memory), settings(settings) {}

            void LDMIA(const u16 code); // TODO
            void LDR1(const u16 code); // TODO
            void LDR2(const u16 code); // TODO
            void LDR3(const u16 code); // TODO
            void LDR4(const u16 code); // TODO
            void LDRB1(const u16 code); // TODO
            void LDRB2(const u16 code); // TODO
            void LDRH1(const u16 code); // TODO
            void LDRH2(const u16 code); // TODO
            void LDRSB(const u16 code); // TODO
            void LDRSH(const u16 code); // TODO
            void POP(const u16 code); // TODO, ADD CHECK FOR L4 BIT
        } load;

        struct store {
            REGISTERS& reg;
            OPERATION& operation;
            MEMORY& memory;

            store(
                REGISTERS& reg, 
                OPERATION& operation,
                MEMORY& memory
            ) : reg(reg), operation(operation), memory(memory) {}

            void STMIA(const u16 code); // TODO
            void STR1(const u16 code); // TODO
            void STR2(const u16 code); // TODO
            void STR3(const u16 code); // TODO
            void STRB1(const u16 code); // TODO
            void STRB2(const u16 code); // TODO
            void STRH1(const u16 code); // TODO
            void STRH2(const u16 code); // TODO
            void PUSH(const u16 code); // TODO
        } store;

        thumb(
            REGISTERS& reg, 
            OPERATION& operation,
            SETTINGS& settings,
            MEMORY& memory
            //ADDRESSING_MODE& address_mode,
        ) : math(reg, operation),
            logic(reg, operation),
            compare(reg, operation),
            movement(reg, operation),
            branching(reg, operation),
            misc(reg, operation, settings),
            load(reg, operation, memory, settings),
            store(reg, operation, memory)
        {

        }
    } thumb;

    INSTRUCTIONS(
        REGISTERS& reg, 
        ADDRESSING_MODE& address_mode,
        OPERATION& operation,
        COPROCESSOR& coprocessor,
        SETTINGS& settings,
        MEMORY& memory,
        EXCEPTION& exception,
        VFP_REG& vfp_reg,
        VFP_EXCEPTION& vfp_exception,
        VFP_ADDRESS_MODE& vfp_addressing_mode
    ) : reg(reg),
        address_mode(address_mode),
        operation(operation),
        coprocessor(coprocessor),
        settings(settings),
        memory(memory),
        arm(reg, operation, address_mode, coprocessor, memory, settings, exception, vfp_reg, vfp_exception, vfp_addressing_mode),
        thumb(reg, operation, settings, memory)
    {

    }
};