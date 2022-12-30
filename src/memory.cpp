#include "memory.hpp"
#include <cstdio>
#include <vector>

Memory::Memory(const long size) {
    this->memory_array = std::vector<uint8_t>(size);
    this->assign_font();
}

Memory::Memory() : Memory(MEMORY_SIZE) {}

Memory::~Memory() {}

uint16_t Memory::get_16_bits_value(uint16_t addr) {
    return ((this->memory_array[addr] << 8) | this->memory_array[addr+1]);
}

uint8_t Memory::get_8_bits_value(uint16_t addr) {
    return this->memory_array[addr];
}

void Memory::set_16_bits_value(uint16_t addr, uint16_t value) {
    this->memory_array[addr] = value >> 8;
    this->memory_array[addr+1] = value & 0xff;
}

void Memory::set_8_bits_value(uint16_t addr, uint8_t value) {
    this->memory_array[addr] = value;
}

void Memory::assign_font() {
    int current_font_addr = BEGIN_FONT_ARRAY_ADDR;
    int font_array[] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80 // F
    };
    for(int i : font_array) {
        this->memory_array[current_font_addr] = i;
        current_font_addr++;
    }

}
