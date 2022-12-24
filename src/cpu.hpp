#ifndef CPU_H 
#define CPU_H

#include <vector>
#include <cstdint>

constexpr int REGISTER_COUNT = 16;
constexpr int STACK_SIZE = 16;

class Cpu {
    public:
        Cpu();
        ~Cpu();
        std::vector<uint8_t> get_general_registers();
        std::vector<uint8_t> get_stack();
        uint16_t get_program_counter_value();
        void set_program_counter_value(uint16_t value);
        void inc_program_counter_value();
    private:
        std::vector<uint8_t> general_registers;
        std::vector<uint8_t> stack;
        uint8_t delay_register;
        uint8_t sound_register;
        uint8_t stack_pointer;
        uint16_t program_counter;
        uint16_t i_register;
};

#endif
