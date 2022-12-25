#ifndef CHIP8_H
#define CHIP8_H

#include "memory.hpp"
#include "cpu.hpp"

class Chip8 {
public:
    Chip8(Memory* memory, Cpu* cpu);
    ~Chip8();

    void next();
    uint16_t fetch_opcode();
    Cpu* get_cpu();
    Memory* get_memory();
private:
    Memory* memory;
    Cpu* cpu;
};

#endif
