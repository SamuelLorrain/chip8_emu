#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <cstdint>

typedef int InstructionType;

constexpr InstructionType CLS = 1;
constexpr InstructionType RET = 2;
constexpr InstructionType SYS = 3;
constexpr InstructionType JP = 4;
constexpr InstructionType CALL = 5;
constexpr InstructionType SExb = 6;
constexpr InstructionType SNExb = 7;
constexpr InstructionType SExy = 8;
constexpr InstructionType LDxb = 9;
constexpr InstructionType ADDxb = 10;
constexpr InstructionType LDxy = 11;
constexpr InstructionType ORxy = 12;


constexpr InstructionType NON_EXISTANT_INSTRUCTION = 0xffff;

InstructionType decode_instruction(uint16_t instruction);

#endif
