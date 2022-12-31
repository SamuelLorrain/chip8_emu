#include <iostream>
#include "chip8.hpp"
#include "memory.hpp"
#include "cpu.hpp"
#include "instruction.hpp"

int main(int argc, char** argv) {
    std::cout << "chip8..." << std::endl;
    Memory* memory = new Memory();
    Cpu* cpu = new Cpu();
    Screen* screen = new Screen();
    Chip8* chip8 = new Chip8(memory, cpu, screen);
    if (argc < 2) {
        std::cout << "Please provide path to ROM as argument" << std::endl;
        return 1;
    }

chip8->load_rom(argv[1]);
    return 0;
}
