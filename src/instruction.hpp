#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <cstdint>

class Instruction {
    protected:
        uint8_t x;
        uint8_t y;
        uint16_t i;
        uint16_t addr;
        int byte;
        int nibble;
    public:
        Instruction();
        inline void setX(int value);
        inline void setY(int value);
        inline void setI(int value);
        inline void setAddr(int value);
        inline void setByte(int value);
        inline void setNibble(int value);
        virtual void processInstruction(Chip8 chip8) = 0;
};

typedef instructionFlag int;
Instruction decode_instruction(uint16_t instruction);

class CLS : public Instruction {
    processInstruction(Chip8 chip8) {
        // TODO Clear display
    }
}

class RET : public Intruction {
    processInstruction(Chip8 chip8) {
        Cpu* cpu = chip8->getCpu();
        cpu->set_program_counter_value(cpu->pop_stack());
    }
}

class JPnnn: public Instruction {
    processInstruction(Chip8 chip8) {
        Cpu* cpu = chip8->getCpu();
        cpu->set_program_counter_value(this->addr);
    }
}

class CALLnnn : public Instruction {
    processInstruction(Chip8 chip8) {
        Cpu* cpu = chip8->getCpu();
        cpu->push_stack(chip->get_program_counter_value());
        cpu->set_program_counter_value(this->addr());
    }
}

class SExb : public Instruction {
    processInstruction(Chip8 chip8) {
        Cpu* cpu = chip8->getCpu();
        if (cpu->get_general_registers()[this->x] == this->byte) {
            cpu->inc_program_counter_value(2);
        }
    }
}

class SNExb : public Instruction {
    processInstruction(Chip8 chip8) {
        Cpu* cpu = chip8->getCpu();
        if (cpu->get_general_registers()[this->x] != this->byte) {
            cpu->inc_program_counter_value(2);
        }
    }
}

class SExy : public Instruction {
    processInstruction(Chip8 chip8) {
        Cpu* cpu = chip8->getCpu();
        if (cpu->get_general_registers()[this->x] == cpu->get_general_registers()[this->y]) {
            cpu->inc_program_counter_value(2);
        }
    }
}

class LDxb : public Instruction {
    processInstruction(Chip8 chip8) {
        Cpu* cpu = chip8->getCpu();
        if (cpu->get_general_registers()[this->x] == cpu->get_general_registers()[this->y]) {
            cpu->inc_program_counter_value(2);
        }
    }
}

class ADDxb : public Instruction {
    processInstruction(Chip8 chip8) {
        Cpu* cpu = chip8->getCpu();
        cpu->get_general_registers()[this->x] += this->byte;
    }
}

class LDxy : public Instruction {
    processInstruction(Chip8 chip8) {
        Cpu* cpu = chip8->getCpu();
        cpu->get_general_registers()[this->x] = cpu->get_general_registers()[this->y];
    }
}

class ORxy : public Instruction {
    processInstruction(Chip8 chip8) {
        Cpu* cpu = chip8->getCpu();
        cpu->get_general_registers()[this->x] |= cpu->get_general_registers()[this->y];
    }
}

class ANDxy : public Instruction {
    processInstruction(Chip8 chip8) {
        Cpu* cpu = chip8->getCpu();
        cpu->get_general_registers()[this->x] &= cpu->get_general_registers()[this->y];
    }
}

class XORxy : public Instruction {
    processInstruction(Chip8 chip8) {
        Cpu* cpu = chip8->getCpu();
        cpu->get_general_registers()[this->x] ^= cpu->get_general_registers()[this->y];
    }
}

class ADDxy : public Instruction {
    processInstruction(Chip8 chip8) {
        Cpu* cpu = chip8->getCpu();
        if ((this->x + this->y) > 0xff) {
            cpu->get_general_registers()[0xf] = 1;
        } else {
            cpu->get_general_registers()[0xf] = 0;
        }
        cpu->get_general_registers()[this->x] += cpu->get_general_registers()[this->y];
    }
}

class SUBxy : public Instruction {
    processInstruction(Chip8 chip8) {
        Cpu* cpu = chip8->getCpu();
        if (this->x > this->y) {
            cpu->get_general_registers()[0xf] = 1;
        }
        else {
            cpu->get_general_registers()[0xf] = 0;
        }
        cpu->get_general_registers()[this->x] -= cpu->get_general_registers()[this->y];
    }
}


class SHRxy : public Instruction {
    processInstruction(Chip8 chip8) {
        Cpu* cpu = chip8->getCpu();
        if (cpu->get_general_registers[this->x] & 0x1 == 1) {
            cpu->get_general_registers[0xf] = 1;
        } else {
            cpu->get_general_registers[0xf] = 0;
        }
        cpu->get_general_registers[this->x] >>= 1;
    }
}

#endif
