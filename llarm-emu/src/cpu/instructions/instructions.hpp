#pragma once

#include "../core/registers.hpp"
#include "../coprocessor/coprocessor.hpp"
#include "../memory/memory.hpp"
#include "arm/addressing_modes/addressing_modes.hpp"
#include "operation.hpp"

#include "shared/types.hpp"

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
    
            void ADC(const arm_code_t&); // TODO, NOTE: MUST TEST CARRY AND OVERFLOW
            void ADD(const arm_code_t&); // same
            void RSB(const arm_code_t&); // TODO
            void RSC(const arm_code_t&); // TODO
            void SBC(const arm_code_t&); // TODO
            void SUB(const arm_code_t&); // TODO
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
    
            void CMN(const arm_code_t&); // TODO
            void AND(const arm_code_t&); // TODO
            void CMP(const arm_code_t&); // TODO
            void CLZ(const arm_code_t&); // (test if this works, manually)
            void EOR(const arm_code_t&); // TODO
            void ORR(const arm_code_t&); // TODO
            void TEQ(const arm_code_t&); // TODO
            void TST(const arm_code_t&); // TODO
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
    
            void MOV(const arm_code_t&); // TODO
            void MVN(const arm_code_t&); // TODO
            void MRS(const arm_code_t&); // TODO
            void MSR_IMM(const arm_code_t&);
            void MSR_REG(const arm_code_t&);
        } movement;

        struct multiply {
            REGISTERS& reg;
            OPERATION& operation;

            multiply(REGISTERS& reg, OPERATION& operation) : reg(reg), operation(operation) {}
    
            void MLA(const arm_code_t&); // TODO
            void MUL(const arm_code_t&); // TODO
            void SMLAL(const arm_code_t&); // TODO
            void SMULL(const arm_code_t&); // TODO
            void UMLAL(const arm_code_t&); // TODO
            void UMULL(const arm_code_t&); // TODO
        } multiply;

        struct branching {
            REGISTERS& reg; // Direct reference to the reg object
            OPERATION& operation;

            branching(REGISTERS& reg, OPERATION& operation) : reg(reg), operation(operation) {}
    
            void B(const arm_code_t&); // TODO
            void BL(const arm_code_t&); // TODO
            void BX(const arm_code_t&); // TODO
            void BLX1(const arm_code_t&); // TODO
            void BLX2(const arm_code_t&); // TODO
        } branching;

        struct coprocessor_inst {
            REGISTERS& reg;
            OPERATION& operation;
            ADDRESSING_MODE& address_mode;
            COPROCESSOR& coprocessor;

            coprocessor_inst(
                REGISTERS& reg, 
                OPERATION& operation, 
                ADDRESSING_MODE& address_mode,
                COPROCESSOR& coprocessor
            ) : reg(reg), operation(operation), address_mode(address_mode), coprocessor(coprocessor) {}
    
            void CDP(const arm_code_t&); // TODO
            void LDC(const arm_code_t&); // TODO
            void MCR(const arm_code_t&); // TODO
            void MRC(const arm_code_t&); // TODO
            void STC(const arm_code_t&); // TODO
        } coprocessor_inst;

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

            void NOP(const arm_code_t&) noexcept;
            void PSR(const arm_code_t&) noexcept;
            void SWI(const arm_code_t&); // TODO
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
    
            void LDM1(const arm_code_t&); // TODO, ADD CHECK FOR L4 BIT
            void LDM2(const arm_code_t&);
            void LDM3(const arm_code_t&);
            void LDR(const arm_code_t&); // TODO, ADD CHECK FOR L4 BIT
            void LDRB(const arm_code_t&);
            void LDRBT(const arm_code_t&);
            void LDRH(const arm_code_t&);
            void LDRSB(const arm_code_t&);
            void LDRSH(const arm_code_t&);
            void LDRT(const arm_code_t&);
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

            void STM1(const arm_code_t&);
            void STM2(const arm_code_t&);
            void STR(const arm_code_t&);
            void STRB(const arm_code_t&);
            void STRBT(const arm_code_t&);
            void STRH(const arm_code_t&);
            void STRT(const arm_code_t&);
            void SWP(const arm_code_t&);
            void SWPB(const arm_code_t&);
        } store;

        struct dsp {
            REGISTERS& reg;
            OPERATION& operation;

            dsp(REGISTERS& reg, OPERATION& operation) : reg(reg), operation(operation) {}
    
            void LDRD(const arm_code_t&); // TODO
            void MCRR(const arm_code_t&); // TODO
            void MRRC(const arm_code_t&); // TODO
            void PLD(const arm_code_t&); // TODO
            void QADD(const arm_code_t&); // TODO
            void QDADD(const arm_code_t&); // TODO
            void QDSUB(const arm_code_t&); // TODO
            void QSUB(const arm_code_t&); // TODO
            void SMLAXY(const arm_code_t&); // TODO
            void SMLALXY(const arm_code_t&); // TODO
            void SMLAWY(const arm_code_t&); // TODO
            void SMULXY(const arm_code_t&); // TODO
            void SMULWY(const arm_code_t&); // TODO
            void STRD(const arm_code_t&); // TODO
        } dsp;

        struct vfp {
            REGISTERS& reg;
            OPERATION& operation;

            vfp(REGISTERS& reg, OPERATION& operation) : reg(reg), operation(operation) {}
    
            void FABSD(const arm_code_t&); // TODO, D
            void FABSS(const arm_code_t&); // TODO
            void FADDD(const arm_code_t&); // TODO, D
            void FADDS(const arm_code_t&); // TODO
            void FCMPD(const arm_code_t&); // TODO, D
            void FCMPED(const arm_code_t&); // TODO, D
            void FCMPES(const arm_code_t&); // TODO
            void FCMPEZD(const arm_code_t&); // TODO, D
            void FCMPEZS(const arm_code_t&); // TODO
            void FCMPS(const arm_code_t&); // TODO
            void FCMPZD(const arm_code_t&); // TODO, D
            void FCMPZS(const arm_code_t&); // TODO
            void FCPYD(const arm_code_t&); // TODO, D
            void FCPYS(const arm_code_t&); // TODO
            void FCVTDS(const arm_code_t&); // TODO, D
            void FCVTSD(const arm_code_t&); // TODO, D
            void FDIVD(const arm_code_t&); // TODO, D
            void FDIVS(const arm_code_t&); // TODO
            void FLDD(const arm_code_t&); // TODO, D
            void FLDMD(const arm_code_t&); // TODO, D
            void FLDMS(const arm_code_t&); // TODO
            void FLDMX(const arm_code_t&); // TODO
            void FLDS(const arm_code_t&); // TODO
            void FMACD(const arm_code_t&); // TODO, D
            void FMACS(const arm_code_t&); // TODO
            void FMDHR(const arm_code_t&); // TODO, D
            void FMDLR(const arm_code_t&); // TODO, D
            void FMRDH(const arm_code_t&); // TODO, D
            void FMRDL(const arm_code_t&); // TODO, D
            void FMRS(const arm_code_t&); // TODO
            void FMRX(const arm_code_t&); // TODO 
            void FMSCD(const arm_code_t&); // TODO, D
            void FMSCS(const arm_code_t&); // TODO
            void FMSR(const arm_code_t&); // TODO
            void FMSTAT(const arm_code_t&); // TODO
            void FMULD(const arm_code_t&); // TODO, D
            void FMULS(const arm_code_t&); // TODO
            void FMXR(const arm_code_t&); // TODO
            void FNEGD(const arm_code_t&); // TODO, D
            void FNEGS(const arm_code_t&); // TODO
            void FNMACD(const arm_code_t&); // TODO, D
            void FNMACS(const arm_code_t&); // TODO
            void FNMSCD(const arm_code_t&); // TODO, D
            void FNMSCS(const arm_code_t&); // TODO
            void FNMULD(const arm_code_t&); // TODO, D
            void FNMULS(const arm_code_t&); // TODO
            void FSITOD(const arm_code_t&); // TODO, D
            void FSITOS(const arm_code_t&); // TODO
            void FSQRTD(const arm_code_t&); // TODO, D
            void FSQRTS(const arm_code_t&); // TODO
            void FSTD(const arm_code_t&); // TODO, D
            void FSTMD(const arm_code_t&); // TODO, D
            void FSTMS(const arm_code_t&); // TODO
            void FSTMX(const arm_code_t&); // TODO
            void FSTS(const arm_code_t&); // TODO
            void FSUBD(const arm_code_t&); // TODO, D
            void FSUBS(const arm_code_t&); // TODO
            void FTOSID(const arm_code_t&); // TODO, D
            void FTOSIS(const arm_code_t&); // TODO
            void FTOUID(const arm_code_t&); // TODO, D
            void FTOUIS(const arm_code_t&); // TODO
            void FUITOD(const arm_code_t&); // TODO, D
            void FUITOS(const arm_code_t&); // TODO
        } vfp;

        arm(
            REGISTERS& reg, 
            OPERATION& operation,
            ADDRESSING_MODE& address_mode,
            COPROCESSOR& coprocessor,
            MEMORY& memory,
            SETTINGS& settings
        ) : math(reg, operation, address_mode),
            logic(reg, operation, address_mode),
            movement(reg, operation, address_mode),
            multiply(reg, operation),
            branching(reg, operation),
            coprocessor_inst(reg, operation, address_mode, coprocessor),
            misc(reg, operation, address_mode, coprocessor),
            load(reg, operation, memory, address_mode, settings),
            store(reg, operation, memory, address_mode),
            dsp(reg, operation),
            vfp(reg, operation)
        {

        }
    } arm;



















    struct thumb {
        struct math {
            REGISTERS& reg;
            OPERATION& operation;

            math(REGISTERS& reg, OPERATION& operation) : reg(reg), operation(operation) {}

            void ADC(const thumb_code_t&);
            void ADD1(const thumb_code_t&);
            void ADD2(const thumb_code_t&);
            void ADD3(const thumb_code_t&);
            void ADD4(const thumb_code_t&);
            void ADD5(const thumb_code_t&);
            void ADD6(const thumb_code_t&);
            void ADD7(const thumb_code_t&);
            void SBC(const thumb_code_t&); // NOTE: BORROW_SUB (TRIPLE) AND OVERFLOW_SUB (TRIPLE) MIGHT HAVE WRONG IMPL
            void SUB1(const thumb_code_t&);
            void SUB2(const thumb_code_t&);
            void SUB3(const thumb_code_t&);
            void SUB4(const thumb_code_t&);
            void MUL(const thumb_code_t&);
        } math;

        struct logic {
            REGISTERS& reg;
            OPERATION& operation;

            logic(REGISTERS& reg, OPERATION& operation) : reg(reg), operation(operation) {}
    
            void AND(const thumb_code_t&);
            void ASR1(const thumb_code_t&); // NOTE: ARITHMETIC_SHIFT_RIGHT IMPLEMENTATION MIGHT BE WRONG
            void ASR2(const thumb_code_t&); // NOTE: ARITHMETIC_SHIFT_RIGHT IMPLEMENTATION MIGHT BE WRONG
            void BIC(const thumb_code_t&);
            void EOR(const thumb_code_t&);
            void LSL1(const thumb_code_t&);
            void LSL2(const thumb_code_t&);
            void LSR1(const thumb_code_t&);
            void LSR2(const thumb_code_t&);
            void NEG(const thumb_code_t&); // NOTE: OVERFLOW_SUB MIGHT LEAD TO ERROR
            void ORR(const thumb_code_t&);
            void ROR(const thumb_code_t&);
            void TST(const thumb_code_t&);
        } logic;

        struct compare {
            REGISTERS& reg;
            OPERATION& operation;

            compare(REGISTERS& reg, OPERATION& operation) : reg(reg), operation(operation) {}

            void CMN(const thumb_code_t&); // NOTE: BORROW_FROM MIGHT LEAD TO ERROR
            void CMP1(const thumb_code_t&); // NOTE: OVERFLOW_SUB MIGHT LEAD TO ERROR
            void CMP2(const thumb_code_t&); // NOTE: OVERFLOW_SUB MIGHT LEAD TO ERROR
            void CMP3(const thumb_code_t&);
        } compare;

        struct movement {
            REGISTERS& reg;
            OPERATION& operation;

            movement(REGISTERS& reg, OPERATION& operation) : reg(reg), operation(operation) {}

            void MOV1(const thumb_code_t&);
            void MOV2(const thumb_code_t&);
            void MOV3(const thumb_code_t&);
            void MVN(const thumb_code_t&);
        } movement;

        struct branching {
            REGISTERS& reg;
            OPERATION& operation;

            branching(REGISTERS& reg, OPERATION& operation) : reg(reg), operation(operation) {}

            void B1(const thumb_code_t&);
            void B2(const thumb_code_t&);
            void BL(const thumb_code_t&);
            void BLX1(const thumb_code_t&); // (v5, idk if thumb2)
            void BLX2(const thumb_code_t&); // (v5, idk if thumb2), and double check
            void BX(const thumb_code_t&); // double check
        } branching;

        struct misc {
            REGISTERS& reg;
            OPERATION& operation;
            SETTINGS& settings;

            misc(REGISTERS& reg, OPERATION& operation, SETTINGS& settings) : reg(reg), operation(operation), settings(settings) {}

            void NOP(const thumb_code_t&) noexcept;
            void BKPT(const thumb_code_t&); // (v5)
            void SWI(const thumb_code_t&); // TODO
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

            void LDMIA(const thumb_code_t&); // TODO
            void LDR1(const thumb_code_t&); // TODO
            void LDR2(const thumb_code_t&); // TODO
            void LDR3(const thumb_code_t&); // TODO
            void LDR4(const thumb_code_t&); // TODO
            void LDRB1(const thumb_code_t&); // TODO
            void LDRB2(const thumb_code_t&); // TODO
            void LDRH1(const thumb_code_t&); // TODO
            void LDRH2(const thumb_code_t&); // TODO
            void LDRSB(const thumb_code_t&); // TODO
            void LDRSH(const thumb_code_t&); // TODO
            void POP(const thumb_code_t&); // TODO, ADD CHECK FOR L4 BIT
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

            void STMIA(const thumb_code_t&); // TODO
            void STR1(const thumb_code_t&); // TODO
            void STR2(const thumb_code_t&); // TODO
            void STR3(const thumb_code_t&); // TODO
            void STRB1(const thumb_code_t&); // TODO
            void STRB2(const thumb_code_t&); // TODO
            void STRH1(const thumb_code_t&); // TODO
            void STRH2(const thumb_code_t&); // TODO
            void PUSH(const thumb_code_t&); // TODO
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


   // struct jazelle {
   //     
   // }

    INSTRUCTIONS(
        REGISTERS& reg, 
        ADDRESSING_MODE& address_mode,
        OPERATION& operation,
        COPROCESSOR& coprocessor,
        SETTINGS& settings,
        MEMORY& memory
    ) : reg(reg),
        address_mode(address_mode),
        operation(operation),
        coprocessor(coprocessor),
        settings(settings),
        memory(memory),
        arm(reg, operation, address_mode, coprocessor, memory, settings),
        thumb(reg, operation, settings, memory)
    {

    }
};