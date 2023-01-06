#ifndef MEMORY_H 
#define MEMORY_H

#include <vector>
#include <cstdint>

constexpr int MEMORY_SIZE = 4096;
constexpr int BEGIN_FONT_ARRAY_ADDR = 0x50;
constexpr int SPRITE_SIZE = 5;

class Memory {
    public:
        Memory(const long size);
        Memory();
        ~Memory();
        uint8_t get_8_bits_value(uint16_t addr);
        uint16_t get_16_bits_value(uint16_t addr);
        void set_8_bits_value(uint16_t addr, uint8_t value);
        void set_16_bits_value(uint16_t addr, uint16_t value);
    private:
        std::vector<uint8_t> memory_array;
        void assign_font();
};

#endif
