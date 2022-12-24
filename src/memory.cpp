#include "memory.hpp"
#include <cstdio>
#include <vector>

Memory::Memory(const long size) {
    this->memory_array = std::vector<uint8_t>(size);
}

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

Memory::~Memory() {}
