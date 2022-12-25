#include "instruction.hpp"

// Setters
inline void Instruction::setX(int value) {
    this->x = value;
}
inline void Instruction::setY(int value) {
    this->y = value;
}
inline void Instruction::setI(int value) {
    this->i = value;
}
inline void Instruction::setAddr(int value) {
    this->addr = value;
}
inline void Instruction::setByte(int value) {
    this->byte = value;
}
inline void Instruction::setNibble(int value) {
    this->nibble = value;
}

/*
 * A kind of factory method pattern
 * to create the proper instruction
 * from the given opcode.
 */
Instruction* decode_instruction(uint16_t opcode) {
    Instruction instruction;
    if (opcode == 0x00e0) {
        return new CLS();
    }
    if (opcode == 0x00ee) {
        return new RET();
    }
    if ((opcode & 0xf000) == 0x1000) {
       instruction = new JPnnn();
       instruction->setAddr(opcode & 0x0fff);
       return ins;
    }
    if ((opcode & 0xf000) == 0x2000) {
       instruction = new CALLnnn();
       instruction->setAddr(opcode & 0x0fff);
       return instruction;
    }
}

