#ifndef CHIP8_H
#define CHIP8_H

#include <random>
#include "memory.hpp"
#include "cpu.hpp"
#include "screen.hpp"

class Chip8 {
    public:
        Chip8(Memory* memory, Cpu* cpu);
        Chip8(Memory* memory, Cpu* cpu, Screen* screen);
        Chip8();
        ~Chip8();
        void next();
        uint16_t fetch_opcode();
        void load_rom(const char* file_path);
        inline bool* get_keys(){
            return this->keys;
        }

        Cpu* get_cpu();
        Memory* get_memory();
        Screen* get_screen();
        std::mt19937& get_rng_engine();
        bool waiting = false;
    private:
        Memory* memory;
        Cpu* cpu;
        Screen* screen;
        std::mt19937 rng_engine;
        bool ownMemory;
        bool ownCpu;
        bool ownScreen;
        bool keys[16] = {0};
};

#endif
