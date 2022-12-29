#ifndef CPU_H 
#define CPU_H

#include <vector>
#include <stack>
#include <cstdint>

constexpr int REGISTER_COUNT = 16;

class Cpu {
    public:
        Cpu();
        ~Cpu();
        std::vector<uint8_t>& get_general_registers();
        void push_stack(uint16_t value);
        uint16_t pop_stack();

        uint16_t get_program_counter_value();
        void set_program_counter_value(uint16_t value);
        void inc_program_counter_value();
        void inc_program_counter_value(uint16_t value);

        uint16_t get_i_register_value();
        void set_i_register_value(uint16_t value);

        uint16_t get_delay_register_value();
        void set_delay_register_value(uint16_t value);

        uint16_t get_sound_register_value();
        void set_sound_register_value(uint16_t value);

    private:
        std::vector<uint8_t> general_registers;
        std::stack<uint16_t> stack;
        uint8_t delay_register;
        uint8_t sound_register;
        uint16_t program_counter;
        uint16_t i_register;
};

#endif
