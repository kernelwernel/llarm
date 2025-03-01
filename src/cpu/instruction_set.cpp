#include "id.hpp"
#include "cpu/opcodes.hpp"
#include "cpu/instruction_set.hpp"
#include "cpu/instructions.hpp"
#include "cpu/core/registers.hpp"
#include "cpu/memory/memory.hpp"



INSTRUCTION_SET::INSTRUCTION_SET(
    REGISTERS& reg, 
    MEMORY& memory, 
    COPROCESSOR& coprocessor, 
    SETTINGS& settings
) : reg(reg), 
    memory(memory), 
    coprocessor(coprocessor),
    settings(settings)
{
    arm_table = {
        { id::arm_instruction::NOP, { opcodes::arm::NOP, instructions::arm::misc::NOP } }
        //{ id::arm_instruction::PSR, { opcodes::arm::PSR, instructions::misc::PSR } },
    };

    if (settings.is_enhanced_DSP_enabled) {
        arm_table.emplace_back(id::arm_instruction::LDRD, { opcodes::arm::LDRD, instructions::arm::DSP::LDRD });
        arm_table.emplace_back(id::arm_instruction::MCRR, { opcodes::arm::MCRR, instructions::arm::DSP::MCRR });
        arm_table.emplace_back(id::arm_instruction::MRRC, { opcodes::arm::MRRC, instructions::arm::DSP::MRRC });
        arm_table.emplace_back(id::arm_instruction::PLD, { opcodes::arm::PLD, instructions::arm::DSP::PLD });
        arm_table.emplace_back(id::arm_instruction::QADD, { opcodes::arm::QADD, instructions::arm::DSP::QADD });
        arm_table.emplace_back(id::arm_instruction::QDADD, { opcodes::arm::QDADD, instructions::arm::DSP::QDADD });
        arm_table.emplace_back(id::arm_instruction::QDSUB, { opcodes::arm::QDSUB, instructions::arm::DSP::QDSUB });
        arm_table.emplace_back(id::arm_instruction::QSUB, { opcodes::arm::QSUB, instructions::arm::DSP::QSUB });
        arm_table.emplace_back(id::arm_instruction::SMLA, { opcodes::arm::SMLA, instructions::arm::DSP::SMLA });
        arm_table.emplace_back(id::arm_instruction::SMLAL, { opcodes::arm::SMLAL, instructions::arm::DSP::SMLAL });
        arm_table.emplace_back(id::arm_instruction::SMLAW, { opcodes::arm::SMLAW, instructions::arm::DSP::SMLAW });
        arm_table.emplace_back(id::arm_instruction::SMUL, { opcodes::arm::SMUL, instructions::arm::DSP::SMUL });
        arm_table.emplace_back(id::arm_instruction::SMULW, { opcodes::arm::SMULW, instructions::arm::DSP::SMULW });
        arm_table.emplace_back(id::arm_instruction::STRD, { opcodes::arm::STRD, instructions::arm::DSP::STRD });
    }


    if (settings.is_vfp_enabled) {
        arm_table.emplace_back(id::arm_instruction::FABSS, { opcodes::arm::FABSS, instruction::arm::VFP::FABSS });
        arm_table.emplace_back(id::arm_instruction::FADDS, { opcodes::arm::FADDS, instruction::arm::VFP::FADDS });
        arm_table.emplace_back(id::arm_instruction::FCMPES, { opcodes::arm::FCMPES, instruction::arm::VFP::FCMPES });
        arm_table.emplace_back(id::arm_instruction::FCMPEZS, { opcodes::arm::FCMPEZS, instruction::arm::VFP::FCMPEZS });
        arm_table.emplace_back(id::arm_instruction::FCMPS, { opcodes::arm::FCMPS, instruction::arm::VFP::FCMPS });
        arm_table.emplace_back(id::arm_instruction::FCMPZS, { opcodes::arm::FCMPZS, instruction::arm::VFP::FCMPZS });
        arm_table.emplace_back(id::arm_instruction::FCPYS, { opcodes::arm::FCPYS, instruction::arm::VFP::FCPYS });
        arm_table.emplace_back(id::arm_instruction::FDIVS, { opcodes::arm::FDIVS, instruction::arm::VFP::FDIVS });
        arm_table.emplace_back(id::arm_instruction::FLDMS, { opcodes::arm::FLDMS, instruction::arm::VFP::FLDMS });
        arm_table.emplace_back(id::arm_instruction::FLDMX, { opcodes::arm::FLDMX, instruction::arm::VFP::FLDMX });
        arm_table.emplace_back(id::arm_instruction::FLDS, { opcodes::arm::FLDS, instruction::arm::VFP::FLDS });
        arm_table.emplace_back(id::arm_instruction::FMACS, { opcodes::arm::FMACS, instruction::arm::VFP::FMACS });
        arm_table.emplace_back(id::arm_instruction::FMRS, { opcodes::arm::FMRS, instruction::arm::VFP::FMRS });
        arm_table.emplace_back(id::arm_instruction::FMRX, { opcodes::arm::FMRX, instruction::arm::VFP::FMRX });
        arm_table.emplace_back(id::arm_instruction::FMSCS, { opcodes::arm::FMSCS, instruction::arm::VFP::FMSCS });
        arm_table.emplace_back(id::arm_instruction::FMSR, { opcodes::arm::FMSR, instruction::arm::VFP::FMSR });
        arm_table.emplace_back(id::arm_instruction::FMSTAT, { opcodes::arm::FMSTAT, instruction::arm::VFP::FMSTAT });
        arm_table.emplace_back(id::arm_instruction::FMULS, { opcodes::arm::FMULS, instruction::arm::VFP::FMULS });
        arm_table.emplace_back(id::arm_instruction::FMXR, { opcodes::arm::FMXR, instruction::arm::VFP::FMXR });
        arm_table.emplace_back(id::arm_instruction::FNEGS, { opcodes::arm::FNEGS, instruction::arm::VFP::FNEGS });
        arm_table.emplace_back(id::arm_instruction::FNMACS, { opcodes::arm::FNMACS, instruction::arm::VFP::FNMACS });
        arm_table.emplace_back(id::arm_instruction::FNMSCS, { opcodes::arm::FNMSCS, instruction::arm::VFP::FNMSCS });
        arm_table.emplace_back(id::arm_instruction::FNMULS, { opcodes::arm::FNMULS, instruction::arm::VFP::FNMULS });
        arm_table.emplace_back(id::arm_instruction::FSITOS, { opcodes::arm::FSITOS, instruction::arm::VFP::FSITOS });
        arm_table.emplace_back(id::arm_instruction::FSQRTS, { opcodes::arm::FSQRTS, instruction::arm::VFP::FSQRTS });
        arm_table.emplace_back(id::arm_instruction::FSTMS, { opcodes::arm::FSTMS, instruction::arm::VFP::FSTMS });
        arm_table.emplace_back(id::arm_instruction::FSTMX, { opcodes::arm::FSTMX, instruction::arm::VFP::FSTMX });
        arm_table.emplace_back(id::arm_instruction::FSTS, { opcodes::arm::FSTS, instruction::arm::VFP::FSTS });
        arm_table.emplace_back(id::arm_instruction::FSUBS, { opcodes::arm::FSUBS, instruction::arm::VFP::FSUBS });
        arm_table.emplace_back(id::arm_instruction::FTOSIS, { opcodes::arm::FTOSIS, instruction::arm::VFP::FTOSIS });
        arm_table.emplace_back(id::arm_instruction::FTOUIS, { opcodes::arm::FTOUIS, instruction::arm::VFP::FTOUIS });
        arm_table.emplace_back(id::arm_instruction::FUITOS, { opcodes::arm::FUITOS, instruction::arm::VFP::FUITOS });
        
        if (settings.is_vfp_double_precision_enabled) {
            arm_table.emplace_back(id::arm_instruction::FADDD, { opcodes::arm::FADDD, instruction::arm::VFP::FADDD });
            arm_table.emplace_back(id::arm_instruction::FABSD, { opcodes::arm::FABSD, instruction::arm::VFP::FABSD });
            arm_table.emplace_back(id::arm_instruction::FCMPD, { opcodes::arm::FCMPD, instruction::arm::VFP::FCMPD });
            arm_table.emplace_back(id::arm_instruction::FCMPED, { opcodes::arm::FCMPED, instruction::arm::VFP::FCMPED });
            arm_table.emplace_back(id::arm_instruction::FCMPEZD, { opcodes::arm::FCMPEZD, instruction::arm::VFP::FCMPEZD });
            arm_table.emplace_back(id::arm_instruction::FCMPZD, { opcodes::arm::FCMPZD, instruction::arm::VFP::FCMPZD });
            arm_table.emplace_back(id::arm_instruction::FCPYD, { opcodes::arm::FCPYD, instruction::arm::VFP::FCPYD });
            arm_table.emplace_back(id::arm_instruction::FCVTDS, { opcodes::arm::FCVTDS, instruction::arm::VFP::FCVTDS });
            arm_table.emplace_back(id::arm_instruction::FCVTSD, { opcodes::arm::FCVTSD, instruction::arm::VFP::FCVTSD });
            arm_table.emplace_back(id::arm_instruction::FDIVD, { opcodes::arm::FDIVD, instruction::arm::VFP::FDIVD });
            arm_table.emplace_back(id::arm_instruction::FLDD, { opcodes::arm::FLDD, instruction::arm::VFP::FLDD });
            arm_table.emplace_back(id::arm_instruction::FLDMD, { opcodes::arm::FLDMD, instruction::arm::VFP::FLDMD });
            arm_table.emplace_back(id::arm_instruction::FMACD, { opcodes::arm::FMACD, instruction::arm::VFP::FMACD });
            arm_table.emplace_back(id::arm_instruction::FMDHR, { opcodes::arm::FMDHR, instruction::arm::VFP::FMDHR });
            arm_table.emplace_back(id::arm_instruction::FMDLR, { opcodes::arm::FMDLR, instruction::arm::VFP::FMDLR });
            arm_table.emplace_back(id::arm_instruction::FMRDH, { opcodes::arm::FMRDH, instruction::arm::VFP::FMRDH });
            arm_table.emplace_back(id::arm_instruction::FMRDL, { opcodes::arm::FMRDL, instruction::arm::VFP::FMRDL });
            arm_table.emplace_back(id::arm_instruction::FMSCD, { opcodes::arm::FMSCD, instruction::arm::VFP::FMSCD });
            arm_table.emplace_back(id::arm_instruction::FMULD, { opcodes::arm::FMULD, instruction::arm::VFP::FMULD });
            arm_table.emplace_back(id::arm_instruction::FNEGD, { opcodes::arm::FNEGD, instruction::arm::VFP::FNEGD });
            arm_table.emplace_back(id::arm_instruction::FNMACD, { opcodes::arm::FNMACD, instruction::arm::VFP::FNMACD });
            arm_table.emplace_back(id::arm_instruction::FNMSCD, { opcodes::arm::FNMSCD, instruction::arm::VFP::FNMSCD });
            arm_table.emplace_back(id::arm_instruction::FNMULD, { opcodes::arm::FNMULD, instruction::arm::VFP::FNMULD });
            arm_table.emplace_back(id::arm_instruction::FSITOD, { opcodes::arm::FSITOD, instruction::arm::VFP::FSITOD });
            arm_table.emplace_back(id::arm_instruction::FSQRTD, { opcodes::arm::FSQRTD, instruction::arm::VFP::FSQRTD });
            arm_table.emplace_back(id::arm_instruction::FSTD, { opcodes::arm::FSTD, instruction::arm::VFP::FSTD });
            arm_table.emplace_back(id::arm_instruction::FSTMD, { opcodes::arm::FSTMD, instruction::arm::VFP::FSTMD });
            arm_table.emplace_back(id::arm_instruction::FSUBD, { opcodes::arm::FSUBD, instruction::arm::VFP::FSUBD });
            arm_table.emplace_back(id::arm_instruction::FTOSID, { opcodes::arm::FTOSID, instruction::arm::VFP::FTOSID });
            arm_table.emplace_back(id::arm_instruction::FTOUID, { opcodes::arm::FTOUID, instruction::arm::VFP::FTOUID });
            arm_table.emplace_back(id::arm_instruction::FUITOD, { opcodes::arm::FUITOD, instruction::arm::VFP::FUITOD });
        }
    }

    thumb_table = {
        // math
        { id::thumb_instruction::ADC,   { opcodes::thumb::ADC,   instructions::thumb::math::ADC } },
        { id::thumb_instruction::ADD1,  { opcodes::thumb::ADD1,  instructions::thumb::math::ADD1 } },
        { id::thumb_instruction::ADD2,  { opcodes::thumb::ADD2,  instructions::thumb::math::ADD2 } },
        { id::thumb_instruction::ADD3,  { opcodes::thumb::ADD3,  instructions::thumb::math::ADD3 } },
        { id::thumb_instruction::ADD4,  { opcodes::thumb::ADD4,  instructions::thumb::math::ADD4 } },
        { id::thumb_instruction::ADD5,  { opcodes::thumb::ADD5,  instructions::thumb::math::ADD5 } },
        { id::thumb_instruction::ADD6,  { opcodes::thumb::ADD6,  instructions::thumb::math::ADD6 } },
        { id::thumb_instruction::ADD7,  { opcodes::thumb::ADD7,  instructions::thumb::math::ADD7 } },
        { id::thumb_instruction::SBC,   { opcodes::thumb::SBC,   instructions::thumb::math::SBC } },
        { id::thumb_instruction::SUB1,  { opcodes::thumb::SUB1,  instructions::thumb::math::SUB1 } },
        { id::thumb_instruction::SUB2,  { opcodes::thumb::SUB2,  instructions::thumb::math::SUB2 } },
        { id::thumb_instruction::SUB3,  { opcodes::thumb::SUB3,  instructions::thumb::math::SUB3 } },
        { id::thumb_instruction::SUB4,  { opcodes::thumb::SUB4,  instructions::thumb::math::SUB4 } },
        { id::thumb_instruction::MUL,   { opcodes::thumb::MUL,   instructions::thumb::math::MUL } },

        // logic
        { id::thumb_instruction::AND,   { opcodes::thumb::AND,   instructions::thumb::logic::AND } },
        { id::thumb_instruction::ASR1,  { opcodes::thumb::ASR1,  instructions::thumb::logic::ASR1 } },
        { id::thumb_instruction::ASR2,  { opcodes::thumb::ASR2,  instructions::thumb::logic::ASR2 } },
        { id::thumb_instruction::BIC,   { opcodes::thumb::BIC,   instructions::thumb::logic::BIC } },
        { id::thumb_instruction::EOR,   { opcodes::thumb::EOR,   instructions::thumb::logic::EOR } },
        { id::thumb_instruction::LSL1,  { opcodes::thumb::LSL1,  instructions::thumb::logic::LSL1 } },
        { id::thumb_instruction::LSL2,  { opcodes::thumb::LSL2,  instructions::thumb::logic::LSL2 } },
        { id::thumb_instruction::LSR1,  { opcodes::thumb::LSR1,  instructions::thumb::logic::LSR1 } },
        { id::thumb_instruction::LSR2,  { opcodes::thumb::LSR2,  instructions::thumb::logic::LSR2 } },
        { id::thumb_instruction::NEG,   { opcodes::thumb::NEG,   instructions::thumb::logic::NEG } },
        { id::thumb_instruction::ORR,   { opcodes::thumb::ORR,   instructions::thumb::logic::ORR } },
        { id::thumb_instruction::ROR,   { opcodes::thumb::ROR,   instructions::thumb::logic::ROR } },
        { id::thumb_instruction::TST,   { opcodes::thumb::TST,   instructions::thumb::logic::TST } },

        // comparison
        { id::thumb_instruction::CMN,   { opcodes::thumb::CMN,   instructions::thumb::compare::CMN } },
        { id::thumb_instruction::CMP1,  { opcodes::thumb::CMP1,  instructions::thumb::compare::CMP1 } },
        { id::thumb_instruction::CMP2,  { opcodes::thumb::CMP2,  instructions::thumb::compare::CMP2 } },
        { id::thumb_instruction::CMP3,  { opcodes::thumb::CMP3,  instructions::thumb:: compare::CMP3} },

        // movement
        { id::thumb_instruction::MOV1,  { opcodes::thumb::MOV1,  instructions::thumb::movement::MOV1 } },
        { id::thumb_instruction::MOV2,  { opcodes::thumb::MOV2,  instructions::thumb::movement::MOV2 } },
        { id::thumb_instruction::MOV3,  { opcodes::thumb::MOV3,  instructions::thumb::movement::MOV3 } },
        { id::thumb_instruction::MVN,   { opcodes::thumb::MVN,   instructions::thumb::movement::MVN } },

        // branching
        { id::thumb_instruction::B1,    { opcodes::thumb::B1,    instructions::thumb::branching::B1 } },
        { id::thumb_instruction::B2,    { opcodes::thumb::B2,    instructions::thumb::branching::B2 } },
        { id::thumb_instruction::BL,    { opcodes::thumb::BL,    instructions::thumb::branching::BL } },
        { id::thumb_instruction::BX,    { opcodes::thumb::BX,    instructions::thumb::branching::BX } },

        // misc
        { id::thumb_instruction::NOP,   { opcodes::thumb::NOP,   instructions::thumb::misc::NOP } },
        { id::thumb_instruction::SWI,   { opcodes::thumb::SWI,   instructions::thumb::misc::SWI } },

        // load
        { id::thumb_instruction::LDMIA, { opcodes::thumb::LDMIA, instructions::thumb::load::LDMIA } },
        { id::thumb_instruction::LDR1,  { opcodes::thumb::LDR1,  instructions::thumb::load::LDR1 } },
        { id::thumb_instruction::LDR2,  { opcodes::thumb::LDR2,  instructions::thumb::load::LDR2 } },
        { id::thumb_instruction::LDR3,  { opcodes::thumb::LDR3,  instructions::thumb::load::LDR3 } },
        { id::thumb_instruction::LDR4,  { opcodes::thumb::LDR4,  instructions::thumb::load::LDR4 } },
        { id::thumb_instruction::LDRB1, { opcodes::thumb::LDRB1, instructions::thumb::load::LDRB1 } },
        { id::thumb_instruction::LDRB2, { opcodes::thumb::LDRB2, instructions::thumb::load::LDRB2 } },
        { id::thumb_instruction::LDRH1, { opcodes::thumb::LDRH1, instructions::thumb::load::LDRH1 } },
        { id::thumb_instruction::LDRH2, { opcodes::thumb::LDRH2, instructions::thumb::load::LDRH2 } },
        { id::thumb_instruction::LDRSB, { opcodes::thumb::LDRSB, instructions::thumb::load::LDRSB } },
        { id::thumb_instruction::LDRSH, { opcodes::thumb::LDRSH, instructions::thumb::load::LDRSH } },
        { id::thumb_instruction::POP,   { opcodes::thumb::POP,   instructions::thumb::load::POP } },
    
        // store
        { id::thumb_instruction::STMIA, { opcodes::thumb::STMIA, instructions::thumb::store::STMIA } },
        { id::thumb_instruction::STR1,  { opcodes::thumb::STR1,  instructions::thumb::store::STR1 } },
        { id::thumb_instruction::STR2,  { opcodes::thumb::STR2,  instructions::thumb::store::STR2 } },
        { id::thumb_instruction::STR3,  { opcodes::thumb::STR3,  instructions::thumb::store::STR3 } },
        { id::thumb_instruction::STRB1, { opcodes::thumb::STRB1, instructions::thumb::store::STRB1 } },
        { id::thumb_instruction::STRH1, { opcodes::thumb::STRH1, instructions::thumb::store::STRH1 } },
        { id::thumb_instruction::STRH2, { opcodes::thumb::STRH2, instructions::thumb::store::STRH2 } },
        { id::thumb_instruction::PUSH,  { opcodes::thumb::PUSH,  instructions::thumb::store::PUSH } }

        // { id::thumb_instruction::BKPT,    { opcodes::thumb::, instructions::thumb:: } },
        // { id::thumb_instruction::BLX1,    { opcodes::thumb::BLX1, instructions::thumb:: } },
        // { id::thumb_instruction::BLX2,    { opcodes::thumb::, instructions::thumb:: } }
    };

    jazelle_table = {
        { id::jazelle_instruction::UNKNOWN,         { opcodes::jazelle::UNKNOWN, instructions::jazelle:: } },
        { id::jazelle_instruction::AALOAD,          { opcodes::jazelle::AALOAD, instructions::jazelle:: } },
        { id::jazelle_instruction::AASTORE,         { opcodes::jazelle::AASTORE, instructions::jazelle:: } },
        { id::jazelle_instruction::ACONST_NULL,     { opcodes::jazelle::ACONST_NULL, instructions::jazelle:: } },
        { id::jazelle_instruction::ALOAD,           { opcodes::jazelle::ALOAD, instructions::jazelle:: } },
        { id::jazelle_instruction::ALOAD_0,         { opcodes::jazelle::ALOAD_0, instructions::jazelle:: } },
        { id::jazelle_instruction::ALOAD_1,         { opcodes::jazelle::ALOAD_1, instructions::jazelle:: } },
        { id::jazelle_instruction::ALOAD_2,         { opcodes::jazelle::ALOAD_2, instructions::jazelle:: } },
        { id::jazelle_instruction::ALOAD_3,         { opcodes::jazelle::ALOAD_3, instructions::jazelle:: } },
        { id::jazelle_instruction::ANEWARRAY,       { opcodes::jazelle::ANEWARRAY, instructions::jazelle:: } },
        { id::jazelle_instruction::ARETURN,         { opcodes::jazelle::ARETURN, instructions::jazelle:: } },
        { id::jazelle_instruction::ARRAYLENGTH,     { opcodes::jazelle::ARRAYLENGTH, instructions::jazelle:: } },
        { id::jazelle_instruction::ASTORE,          { opcodes::jazelle::ASTORE, instructions::jazelle:: } },
        { id::jazelle_instruction::ASTORE_0,        { opcodes::jazelle::ASTORE_0, instructions::jazelle:: } },
        { id::jazelle_instruction::ASTORE_1,        { opcodes::jazelle::ASTORE_1, instructions::jazelle:: } },
        { id::jazelle_instruction::ASTORE_2,        { opcodes::jazelle::ASTORE_2, instructions::jazelle:: } },
        { id::jazelle_instruction::ASTORE_3,        { opcodes::jazelle::ASTORE_3, instructions::jazelle:: } },
        { id::jazelle_instruction::ATHROW,          { opcodes::jazelle::ATHROW, instructions::jazelle:: } },
        { id::jazelle_instruction::BALOAD,          { opcodes::jazelle::BALOAD, instructions::jazelle:: } },
        { id::jazelle_instruction::BASTORE,         { opcodes::jazelle::BASTORE, instructions::jazelle:: } },
        { id::jazelle_instruction::BIPUSH,          { opcodes::jazelle::BIPUSH, instructions::jazelle:: } },
        { id::jazelle_instruction::BREAKPOINT,      { opcodes::jazelle::BREAKPOINT, instructions::jazelle:: } },
        { id::jazelle_instruction::CALOAD,          { opcodes::jazelle::CALOAD, instructions::jazelle:: } },
        { id::jazelle_instruction::CASTORE,         { opcodes::jazelle::CASTORE, instructions::jazelle:: } },
        { id::jazelle_instruction::CHECKCAST,       { opcodes::jazelle::CHECKCAST, instructions::jazelle:: } },
        { id::jazelle_instruction::D2F,             { opcodes::jazelle::D2F, instructions::jazelle:: } },
        { id::jazelle_instruction::D2I,             { opcodes::jazelle::D2I, instructions::jazelle:: } },
        { id::jazelle_instruction::D2L,             { opcodes::jazelle::D2L, instructions::jazelle:: } },
        { id::jazelle_instruction::DADD,            { opcodes::jazelle::DADD, instructions::jazelle:: } },
        { id::jazelle_instruction::DALOAD,          { opcodes::jazelle::DALOAD, instructions::jazelle:: } },
        { id::jazelle_instruction::DASTORE,         { opcodes::jazelle::DASTORE, instructions::jazelle:: } },
        { id::jazelle_instruction::DCMPG,           { opcodes::jazelle::DCMPG, instructions::jazelle:: } },
        { id::jazelle_instruction::DCMPL,           { opcodes::jazelle::DCMPL, instructions::jazelle:: } },
        { id::jazelle_instruction::DCONST_0,        { opcodes::jazelle::DCONST_0, instructions::jazelle:: } },
        { id::jazelle_instruction::DCONST_1,        { opcodes::jazelle::DCONST_1, instructions::jazelle:: } },
        { id::jazelle_instruction::DDIV,            { opcodes::jazelle::DDIV, instructions::jazelle:: } },
        { id::jazelle_instruction::DLOAD,           { opcodes::jazelle::DLOAD, instructions::jazelle:: } },
        { id::jazelle_instruction::DLOAD_0,         { opcodes::jazelle::DLOAD_0, instructions::jazelle:: } },
        { id::jazelle_instruction::DLOAD_1,         { opcodes::jazelle::DLOAD_1, instructions::jazelle:: } },
        { id::jazelle_instruction::DLOAD_2,         { opcodes::jazelle::DLOAD_2, instructions::jazelle:: } },
        { id::jazelle_instruction::DLOAD_3,         { opcodes::jazelle::DLOAD_3, instructions::jazelle:: } },
        { id::jazelle_instruction::DMUL,            { opcodes::jazelle::DMUL, instructions::jazelle:: } },
        { id::jazelle_instruction::DNEG,            { opcodes::jazelle::DNEG, instructions::jazelle:: } },
        { id::jazelle_instruction::DREM,            { opcodes::jazelle::DREM, instructions::jazelle:: } },
        { id::jazelle_instruction::DRETURN,         { opcodes::jazelle::DRETURN, instructions::jazelle:: } },
        { id::jazelle_instruction::DSTORE,          { opcodes::jazelle::DSTORE, instructions::jazelle:: } },
        { id::jazelle_instruction::DSTORE_0,        { opcodes::jazelle::DSTORE_0, instructions::jazelle:: } },
        { id::jazelle_instruction::DSTORE_1,        { opcodes::jazelle::DSTORE_1, instructions::jazelle:: } },
        { id::jazelle_instruction::DSTORE_2,        { opcodes::jazelle::DSTORE_2, instructions::jazelle:: } },
        { id::jazelle_instruction::DSTORE_3,        { opcodes::jazelle::DSTORE_3, instructions::jazelle:: } },
        { id::jazelle_instruction::DSUB,            { opcodes::jazelle::DSUB, instructions::jazelle:: } },
        { id::jazelle_instruction::DUP,             { opcodes::jazelle::DUP, instructions::jazelle:: } },
        { id::jazelle_instruction::DUP_X1,          { opcodes::jazelle::DUP_X1, instructions::jazelle:: } },
        { id::jazelle_instruction::DUP_X2,          { opcodes::jazelle::DUP_X2, instructions::jazelle:: } },
        { id::jazelle_instruction::DUP2,            { opcodes::jazelle::DUP2, instructions::jazelle:: } },
        { id::jazelle_instruction::DUP2_X1,         { opcodes::jazelle::DUP2_X1, instructions::jazelle:: } },
        { id::jazelle_instruction::DUP2_X2,         { opcodes::jazelle::DUP2_X2, instructions::jazelle:: } },
        { id::jazelle_instruction::F2D,             { opcodes::jazelle::F2D, instructions::jazelle:: } },
        { id::jazelle_instruction::F2I,             { opcodes::jazelle::F2I, instructions::jazelle:: } },
        { id::jazelle_instruction::F2L,             { opcodes::jazelle::F2L, instructions::jazelle:: } },
        { id::jazelle_instruction::FADD,            { opcodes::jazelle::FADD, instructions::jazelle:: } },
        { id::jazelle_instruction::FALOAD,          { opcodes::jazelle::FALOAD, instructions::jazelle:: } },
        { id::jazelle_instruction::FASTORE,         { opcodes::jazelle::FASTORE, instructions::jazelle:: } },
        { id::jazelle_instruction::FCMPG,           { opcodes::jazelle::FCMPG, instructions::jazelle:: } },
        { id::jazelle_instruction::FCMPL,           { opcodes::jazelle::FCMPL, instructions::jazelle:: } },
        { id::jazelle_instruction::FCONST_0,        { opcodes::jazelle::FCONST_0, instructions::jazelle:: } },
        { id::jazelle_instruction::FCONST_1,        { opcodes::jazelle::FCONST_1, instructions::jazelle:: } },
        { id::jazelle_instruction::FCONST_2,        { opcodes::jazelle::FCONST_2, instructions::jazelle:: } },
        { id::jazelle_instruction::FDIV,            { opcodes::jazelle::FDIV, instructions::jazelle:: } },
        { id::jazelle_instruction::FLOAD,           { opcodes::jazelle::FLOAD, instructions::jazelle:: } },
        { id::jazelle_instruction::FLOAD_0,         { opcodes::jazelle::FLOAD_0, instructions::jazelle:: } },
        { id::jazelle_instruction::FLOAD_1,         { opcodes::jazelle::FLOAD_1, instructions::jazelle:: } },
        { id::jazelle_instruction::FLOAD_2,         { opcodes::jazelle::FLOAD_2, instructions::jazelle:: } },
        { id::jazelle_instruction::FLOAD_3,         { opcodes::jazelle::FLOAD_3, instructions::jazelle:: } },
        { id::jazelle_instruction::FMUL,            { opcodes::jazelle::FMUL, instructions::jazelle:: } },
        { id::jazelle_instruction::FNEG,            { opcodes::jazelle::FNEG, instructions::jazelle:: } },
        { id::jazelle_instruction::FREM,            { opcodes::jazelle::FREM, instructions::jazelle:: } },
        { id::jazelle_instruction::FRETURN,         { opcodes::jazelle::FRETURN, instructions::jazelle:: } },
        { id::jazelle_instruction::FSTORE,          { opcodes::jazelle::FSTORE, instructions::jazelle:: } },
        { id::jazelle_instruction::FSTORE_0,        { opcodes::jazelle::FSTORE_0, instructions::jazelle:: } },
        { id::jazelle_instruction::FSTORE_1,        { opcodes::jazelle::FSTORE_1, instructions::jazelle:: } },
        { id::jazelle_instruction::FSTORE_2,        { opcodes::jazelle::FSTORE_2, instructions::jazelle:: } },
        { id::jazelle_instruction::FSTORE_3,        { opcodes::jazelle::FSTORE_3, instructions::jazelle:: } },
        { id::jazelle_instruction::FSUB,            { opcodes::jazelle::FSUB, instructions::jazelle:: } },
        { id::jazelle_instruction::GETFIELD,        { opcodes::jazelle::GETFIELD, instructions::jazelle:: } },
        { id::jazelle_instruction::GETSTATIC,       { opcodes::jazelle::GETSTATIC, instructions::jazelle:: } },
        { id::jazelle_instruction::GOTO,            { opcodes::jazelle::GOTO, instructions::jazelle:: } },
        { id::jazelle_instruction::GOTO_W,          { opcodes::jazelle::GOTO_W, instructions::jazelle:: } },
        { id::jazelle_instruction::I2B,             { opcodes::jazelle::I2B, instructions::jazelle:: } },
        { id::jazelle_instruction::I2C,             { opcodes::jazelle::I2C, instructions::jazelle:: } },
        { id::jazelle_instruction::I2D,             { opcodes::jazelle::I2D, instructions::jazelle:: } },
        { id::jazelle_instruction::I2F,             { opcodes::jazelle::I2F, instructions::jazelle:: } },
        { id::jazelle_instruction::I2L,             { opcodes::jazelle::I2L, instructions::jazelle:: } },
        { id::jazelle_instruction::I2S,             { opcodes::jazelle::I2S, instructions::jazelle:: } },
        { id::jazelle_instruction::IADD,            { opcodes::jazelle::IADD, instructions::jazelle:: } },
        { id::jazelle_instruction::IALOAD,          { opcodes::jazelle::IALOAD, instructions::jazelle:: } },
        { id::jazelle_instruction::IAND,            { opcodes::jazelle::IAND, instructions::jazelle:: } },
        { id::jazelle_instruction::IASTORE,         { opcodes::jazelle::IASTORE, instructions::jazelle:: } },
        { id::jazelle_instruction::ICONST_M1,       { opcodes::jazelle::ICONST_M1, instructions::jazelle:: } },
        { id::jazelle_instruction::ICONST_0,        { opcodes::jazelle::ICONST_0, instructions::jazelle:: } },
        { id::jazelle_instruction::ICONST_1,        { opcodes::jazelle::ICONST_1, instructions::jazelle:: } },
        { id::jazelle_instruction::ICONST_2,        { opcodes::jazelle::ICONST_2, instructions::jazelle:: } },
        { id::jazelle_instruction::ICONST_3,        { opcodes::jazelle::ICONST_3, instructions::jazelle:: } },
        { id::jazelle_instruction::ICONST_4,        { opcodes::jazelle::ICONST_4, instructions::jazelle:: } },
        { id::jazelle_instruction::ICONST_5,        { opcodes::jazelle::ICONST_5, instructions::jazelle:: } },
        { id::jazelle_instruction::IDIV,            { opcodes::jazelle::IDIV, instructions::jazelle:: } },
        { id::jazelle_instruction::IF_ACMPEQ,       { opcodes::jazelle::IF_ACMPEQ, instructions::jazelle:: } },
        { id::jazelle_instruction::IF_ACMPNE,       { opcodes::jazelle::IF_ACMPNE, instructions::jazelle:: } },
        { id::jazelle_instruction::IF_ICMPEQ,       { opcodes::jazelle::IF_ICMPEQ, instructions::jazelle:: } },
        { id::jazelle_instruction::IF_ICMPGE,       { opcodes::jazelle::IF_ICMPGE, instructions::jazelle:: } },
        { id::jazelle_instruction::IF_ICMPGT,       { opcodes::jazelle::IF_ICMPGT, instructions::jazelle:: } },
        { id::jazelle_instruction::IF_ICMPLE,       { opcodes::jazelle::IF_ICMPLE, instructions::jazelle:: } },
        { id::jazelle_instruction::IF_ICMPLT,       { opcodes::jazelle::IF_ICMPLT, instructions::jazelle:: } },
        { id::jazelle_instruction::IF_ICMPNE,       { opcodes::jazelle::IF_ICMPNE, instructions::jazelle:: } },
        { id::jazelle_instruction::IFEQ,            { opcodes::jazelle::IFEQ, instructions::jazelle:: } },
        { id::jazelle_instruction::IFGE,            { opcodes::jazelle::IFGE, instructions::jazelle:: } },
        { id::jazelle_instruction::IFGT,            { opcodes::jazelle::IFGT, instructions::jazelle:: } },
        { id::jazelle_instruction::IFLE,            { opcodes::jazelle::IFLE, instructions::jazelle:: } },
        { id::jazelle_instruction::IFLT,            { opcodes::jazelle::IFLT, instructions::jazelle:: } },
        { id::jazelle_instruction::IFNE,            { opcodes::jazelle::IFNE, instructions::jazelle:: } },
        { id::jazelle_instruction::IFNONNULL,       { opcodes::jazelle::IFNONNULL, instructions::jazelle:: } },
        { id::jazelle_instruction::IFNULL,          { opcodes::jazelle::IFNULL, instructions::jazelle:: } },
        { id::jazelle_instruction::IINC,            { opcodes::jazelle::IINC, instructions::jazelle:: } },
        { id::jazelle_instruction::ILOAD,           { opcodes::jazelle::ILOAD, instructions::jazelle:: } },
        { id::jazelle_instruction::ILOAD_0,         { opcodes::jazelle::ILOAD_0, instructions::jazelle:: } },
        { id::jazelle_instruction::ILOAD_1,         { opcodes::jazelle::ILOAD_1, instructions::jazelle:: } },
        { id::jazelle_instruction::ILOAD_2,         { opcodes::jazelle::ILOAD_2, instructions::jazelle:: } },
        { id::jazelle_instruction::ILOAD_3,         { opcodes::jazelle::ILOAD_3, instructions::jazelle:: } },
        { id::jazelle_instruction::IMPDEP1,         { opcodes::jazelle::IMPDEP1, instructions::jazelle:: } },
        { id::jazelle_instruction::IMPDEP2,         { opcodes::jazelle::IMPDEP2, instructions::jazelle:: } },
        { id::jazelle_instruction::IMUL,            { opcodes::jazelle::IMUL, instructions::jazelle:: } },
        { id::jazelle_instruction::INEG,            { opcodes::jazelle::INEG, instructions::jazelle:: } },
        { id::jazelle_instruction::INSTANCEOF,      { opcodes::jazelle::INSTANCEOF, instructions::jazelle:: } },
        { id::jazelle_instruction::INVOKEDYNAMIC,   { opcodes::jazelle::INVOKEDYNAMIC, instructions::jazelle:: } },
        { id::jazelle_instruction::INVOKEINTERFACE, { opcodes::jazelle::INVOKEINTERFACE, instructions::jazelle:: } },
        { id::jazelle_instruction::INVOKESPECIAL,   { opcodes::jazelle::INVOKESPECIAL, instructions::jazelle:: } },
        { id::jazelle_instruction::INVOKESTATIC,    { opcodes::jazelle::INVOKESTATIC, instructions::jazelle:: } },
        { id::jazelle_instruction::INVOKEVIRTUAL,   { opcodes::jazelle::INVOKEVIRTUAL, instructions::jazelle:: } },
        { id::jazelle_instruction::IOR,             { opcodes::jazelle::IOR, instructions::jazelle:: } },
        { id::jazelle_instruction::IREM,            { opcodes::jazelle::IREM, instructions::jazelle:: } },
        { id::jazelle_instruction::IRETURN,         { opcodes::jazelle::IRETURN, instructions::jazelle:: } },
        { id::jazelle_instruction::ISHL,            { opcodes::jazelle::ISHL, instructions::jazelle:: } },
        { id::jazelle_instruction::ISHR,            { opcodes::jazelle::ISHR, instructions::jazelle:: } },
        { id::jazelle_instruction::ISTORE,          { opcodes::jazelle::ISTORE, instructions::jazelle:: } },
        { id::jazelle_instruction::ISTORE_0,        { opcodes::jazelle::ISTORE_0, instructions::jazelle:: } },
        { id::jazelle_instruction::ISTORE_1,        { opcodes::jazelle::ISTORE_1, instructions::jazelle:: } },
        { id::jazelle_instruction::ISTORE_2,        { opcodes::jazelle::ISTORE_2, instructions::jazelle:: } },
        { id::jazelle_instruction::ISTORE_3,        { opcodes::jazelle::ISTORE_3, instructions::jazelle:: } },
        { id::jazelle_instruction::ISUB,            { opcodes::jazelle::ISUB, instructions::jazelle:: } },
        { id::jazelle_instruction::IUSHR,           { opcodes::jazelle::IUSHR, instructions::jazelle:: } },
        { id::jazelle_instruction::IXOR,            { opcodes::jazelle::IXOR, instructions::jazelle:: } },
        { id::jazelle_instruction::JSR,             { opcodes::jazelle::JSR, instructions::jazelle:: } }, // DEPRECATED
        { id::jazelle_instruction::JSR_W,           { opcodes::jazelle::JSR_W, instructions::jazelle:: } }, // DEPRECATED
        { id::jazelle_instruction::L2D,             { opcodes::jazelle::L2D, instructions::jazelle:: } },
        { id::jazelle_instruction::L2F,             { opcodes::jazelle::L2F, instructions::jazelle:: } },
        { id::jazelle_instruction::L2I,             { opcodes::jazelle::L2I, instructions::jazelle:: } },
        { id::jazelle_instruction::LADD,            { opcodes::jazelle::LADD, instructions::jazelle:: } },
        { id::jazelle_instruction::LALOAD,          { opcodes::jazelle::LALOAD, instructions::jazelle:: } },
        { id::jazelle_instruction::LAND,            { opcodes::jazelle::LAND, instructions::jazelle:: } },
        { id::jazelle_instruction::LASTORE,         { opcodes::jazelle::LASTORE, instructions::jazelle:: } },
        { id::jazelle_instruction::LCMP,            { opcodes::jazelle::LCMP, instructions::jazelle:: } },
        { id::jazelle_instruction::LCONST_0,        { opcodes::jazelle::LCONST_0, instructions::jazelle:: } },
        { id::jazelle_instruction::LCONST_1,        { opcodes::jazelle::LCONST_1, instructions::jazelle:: } },
        { id::jazelle_instruction::LDC,             { opcodes::jazelle::LDC, instructions::jazelle:: } },
        { id::jazelle_instruction::LDC_W,           { opcodes::jazelle::LDC_W, instructions::jazelle:: } },
        { id::jazelle_instruction::LDC2_W,          { opcodes::jazelle::LDC2_W, instructions::jazelle:: } },
        { id::jazelle_instruction::LDIV,            { opcodes::jazelle::LDIV, instructions::jazelle:: } },
        { id::jazelle_instruction::LLOAD,           { opcodes::jazelle::LLOAD, instructions::jazelle:: } },
        { id::jazelle_instruction::LLOAD_0,         { opcodes::jazelle::LLOAD_0, instructions::jazelle:: } },
        { id::jazelle_instruction::LLOAD_1,         { opcodes::jazelle::LLOAD_1, instructions::jazelle:: } },
        { id::jazelle_instruction::LLOAD_2,         { opcodes::jazelle::LLOAD_2, instructions::jazelle:: } },
        { id::jazelle_instruction::LLOAD_3,         { opcodes::jazelle::LLOAD_3, instructions::jazelle:: } },
        { id::jazelle_instruction::LMUL,            { opcodes::jazelle::LMUL, instructions::jazelle:: } },
        { id::jazelle_instruction::LNEG,            { opcodes::jazelle::LNEG, instructions::jazelle:: } },
        { id::jazelle_instruction::LOOKUPSWITCH,    { opcodes::jazelle::LOOKUPSWITCH, instructions::jazelle:: } },
        { id::jazelle_instruction::LOR,             { opcodes::jazelle::LOR, instructions::jazelle:: } },
        { id::jazelle_instruction::LREM,            { opcodes::jazelle::LREM, instructions::jazelle:: } },
        { id::jazelle_instruction::LRETURN,         { opcodes::jazelle::LRETURN, instructions::jazelle:: } },
        { id::jazelle_instruction::LSHL,            { opcodes::jazelle::LSHL, instructions::jazelle:: } },
        { id::jazelle_instruction::LSHR,            { opcodes::jazelle::LSHR, instructions::jazelle:: } },
        { id::jazelle_instruction::LSTORE,          { opcodes::jazelle::LSTORE, instructions::jazelle:: } },
        { id::jazelle_instruction::LSTORE_0,        { opcodes::jazelle::LSTORE_0, instructions::jazelle:: } },
        { id::jazelle_instruction::LSTORE_1,        { opcodes::jazelle::LSTORE_1, instructions::jazelle:: } },
        { id::jazelle_instruction::LSTORE_2,        { opcodes::jazelle::LSTORE_2, instructions::jazelle:: } },
        { id::jazelle_instruction::LSTORE_3,        { opcodes::jazelle::LSTORE_3, instructions::jazelle:: } },
        { id::jazelle_instruction::LSUB,            { opcodes::jazelle::LSUB, instructions::jazelle:: } },
        { id::jazelle_instruction::LUSHR,           { opcodes::jazelle::LUSHR, instructions::jazelle:: } },
        { id::jazelle_instruction::LXOR,            { opcodes::jazelle::LXOR, instructions::jazelle:: } },
        { id::jazelle_instruction::MONITORENTER,    { opcodes::jazelle::MONITORENTER, instructions::jazelle:: } },
        { id::jazelle_instruction::MONITOREXIT,     { opcodes::jazelle::MONITOREXIT, instructions::jazelle:: } },
        { id::jazelle_instruction::MULTIANEWARRAY,  { opcodes::jazelle::MULTIANEWARRAY, instructions::jazelle:: } },
        { id::jazelle_instruction::NEW,             { opcodes::jazelle::NEW, instructions::jazelle:: } },
        { id::jazelle_instruction::NEWARRAY,        { opcodes::jazelle::NEWARRAY, instructions::jazelle:: } },
        { id::jazelle_instruction::NOP,             { opcodes::jazelle::NOP, instructions::jazelle:: } },
        { id::jazelle_instruction::POP,             { opcodes::jazelle::POP, instructions::jazelle:: } },
        { id::jazelle_instruction::POP2,            { opcodes::jazelle::POP2, instructions::jazelle:: } },
        { id::jazelle_instruction::PUTFIELD,        { opcodes::jazelle::PUTFIELD, instructions::jazelle:: } },
        { id::jazelle_instruction::PUTSTATIC,       { opcodes::jazelle::PUTSTATIC, instructions::jazelle:: } },
        { id::jazelle_instruction::RET,             { opcodes::jazelle::RET, instructions::jazelle:: } }, // DEPRECATED
        { id::jazelle_instruction::RETURN,          { opcodes::jazelle::RETURN, instructions::jazelle:: } },
        { id::jazelle_instruction::SALOAD,          { opcodes::jazelle::SALOAD, instructions::jazelle:: } },
        { id::jazelle_instruction::SASTORE,         { opcodes::jazelle::SASTORE, instructions::jazelle:: } },
        { id::jazelle_instruction::SIPUSH,          { opcodes::jazelle::SIPUSH, instructions::jazelle:: } },
        { id::jazelle_instruction::SWAP,            { opcodes::jazelle::SWAP, instructions::jazelle:: } },
        { id::jazelle_instruction::TABLESWITCH,     { opcodes::jazelle::TABLESWITCH, instructions::jazelle:: } },
        { id::jazelle_instruction::WIDE,            { opcodes::jazelle::WIDE, instructions::jazelle::}
    }; 
}