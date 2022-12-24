#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <cstdint>

class Instruction {
    protected:
        instructionFlag instructionType;
        int x;
        int y;
        int i;
        int addr;
        int byte;
        int nibble;
    public:
        virtual Instruction();
        virtual ~Instruction();
        virtual void processInstruction(Chip8 chip8) = 0;
};

typedef instructionFlag int;
Instruction decode_instruction(uint16_t instruction);


#endif
