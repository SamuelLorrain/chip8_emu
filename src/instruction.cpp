#include "instruction.hpp"

Instruction::Instruction() :
    x(0), y(0), i(0), addr(0), byte(0), nibble(0)
{}

// Setters
void Instruction::set_x(int value) {
    this->x = value;
}
void Instruction::set_y(int value) {
    this->y = value;
}
void Instruction::set_i(int value) {
    this->i = value;
}
void Instruction::set_addr(int value) {
    this->addr = value;
}
void Instruction::set_byte(int value) {
    this->byte = value;
}
void Instruction::set_nibble(int value) {
    this->nibble = value;
}

/*
 * A kind of factory method pattern
 * to create the proper instruction
 * from the given opcode.
 */
Instruction* decode_instruction(uint16_t opcode) {
    Instruction* instruction;
    if (opcode == 0x00e0) {
        return new CLS();
    }
    if (opcode == 0x00ee) {
        return new RET();
    }
    if ((opcode & 0xf000) == 0x1000) {
       instruction = new JPnnn();
       instruction->set_addr(opcode & 0x0fff);
       return instruction;
    }
    if ((opcode & 0xf000) == 0x2000) {
       instruction = new CALLnnn();
       instruction->set_addr(opcode & 0x0fff);
       return instruction;
    }
    throw "Invalid instruction";
}

CLS::CLS() : Instruction() {}
void CLS::process_instruction(Chip8* chip8) {
    // TODO clear display
}

RET::RET() : Instruction() {}
void RET::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    cpu->set_program_counter_value(cpu->pop_stack());
}

JPnnn::JPnnn() : Instruction() {}
void JPnnn::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    cpu->set_program_counter_value(this->addr);
}

CALLnnn::CALLnnn() : Instruction() {}
void CALLnnn::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    cpu->push_stack(cpu->get_program_counter_value());
    cpu->set_program_counter_value(this->addr);
}

SExb::SExb() : Instruction() {}
void SExb::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    if (cpu->get_general_registers()[this->x] == this->byte) {
        cpu->inc_program_counter_value(2);
    }
}

SNExb::SNExb() : Instruction() {}
void SNExb::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    if (cpu->get_general_registers()[this->x] != this->byte) {
        cpu->inc_program_counter_value(2);
    }
}

SExy::SExy() : Instruction() {}
void SExy::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    if (cpu->get_general_registers()[this->x] == cpu->get_general_registers()[this->y]) {
        cpu->inc_program_counter_value(2);
    }
}

LDxb::LDxb() : Instruction() {}
void LDxb::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    cpu->get_general_registers()[this->x] = this->byte;
}

ADDxb::ADDxb() : Instruction() {}
void ADDxb::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    cpu->get_general_registers()[this->x] =
        (cpu->get_general_registers()[this->x] + this->byte) & 0xff;
}

LDxy::LDxy() : Instruction() {}
void LDxy::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    cpu->get_general_registers()[this->x] = cpu->get_general_registers()[this->y];
}

ORxy::ORxy() : Instruction() {}
void ORxy::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    cpu->get_general_registers()[this->x] |= cpu->get_general_registers()[this->y];
}

ANDxy::ANDxy() : Instruction() {}
void ANDxy::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    cpu->get_general_registers()[this->x] &= cpu->get_general_registers()[this->y];
}

XORxy::XORxy() : Instruction() {}
void XORxy::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    cpu->get_general_registers()[this->x] ^= cpu->get_general_registers()[this->y];
}

ADDxy::ADDxy() : Instruction() {}
void ADDxy::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    if ((this->x + this->y) > 0xff) {
        cpu->get_general_registers()[0xf] = 1;
    } else {
        cpu->get_general_registers()[0xf] = 0;
    }
    cpu->get_general_registers()[this->x] += cpu->get_general_registers()[this->y];
}

SUBxy::SUBxy() : Instruction() {}
void SUBxy::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    if (this->x > this->y) {
        cpu->get_general_registers()[0xf] = 1;
    }
    else {
        cpu->get_general_registers()[0xf] = 0;
    }
    cpu->get_general_registers()[this->x] -= cpu->get_general_registers()[this->y];
}

SHRxy::SHRxy() : Instruction() {}
void SHRxy::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    if ((cpu->get_general_registers()[this->x] & 0x1) == 1) {
        cpu->get_general_registers()[0xf] = 1;
    } else {
        cpu->get_general_registers()[0xf] = 0;
    }
    cpu->get_general_registers()[this->x] >>= 1;
}

SUBNxy::SUBNxy() : Instruction() {}
void SUBNxy::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    if (this->y > this->x) {
        cpu->get_general_registers()[0xf] = 1;
    }
    else {
        cpu->get_general_registers()[0xf] = 0;
    }
    cpu->get_general_registers()[this->x] =
        cpu->get_general_registers()[this->y] - cpu->get_general_registers()[this->x];
}

SHLxy::SHLxy() : Instruction() {}
void SHLxy::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    if ((cpu->get_general_registers()[this->x] >> 7) == 1) {
        cpu->get_general_registers()[0xf] = 1;
    } else {
        cpu->get_general_registers()[0xf] = 0;
    }
    cpu->get_general_registers()[this->x] <<= 1;
}

SNExy::SNExy() : Instruction() {}
void SNExy::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    if (cpu->get_general_registers()[this->x] != cpu->get_general_registers()[this->y]) {
        cpu->inc_program_counter_value(2);
    }
}

LDinnn::LDinnn() : Instruction() {}
void LDinnn::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    cpu->set_i_register_value(this->addr);
}

JP0nnn::JP0nnn() : Instruction() {}
void JP0nnn::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    cpu->set_program_counter_value(
        cpu->get_general_registers()[0x0] + this->addr
    );
}

RNDxb::RNDxb() : Instruction() {}
void RNDxb::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    cpu->get_general_registers()[this->x] = (chip8->get_rng_engine()() & this->byte);
}

