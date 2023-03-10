#include <stack>
#include <vector>
#include "cpu.hpp"

Cpu::Cpu() {
    this->general_registers = std::vector<uint8_t>(REGISTER_COUNT);
    this->stack = std::stack<uint16_t>();
    this->delay_register = 0;
    this->sound_register = 0;
    this->program_counter = DEFAULT_PROGRAM_COUNTER_VALUE;
    this->i_register = 0;
}

std::vector<uint8_t>& Cpu::get_general_registers() {
    return this->general_registers;
}

void Cpu::push_stack(uint16_t value) {
    this->stack.push(value);
}

uint16_t Cpu::pop_stack() {
    uint16_t value = this->stack.top();
    this->stack.pop();
    return value;
}

uint16_t Cpu::get_program_counter_value() {
    return this->program_counter;
}

void Cpu::set_program_counter_value(uint16_t value) {
    this->program_counter = value;
}

void Cpu::inc_program_counter_value(uint16_t value) {
    this->program_counter += value;
}

uint16_t Cpu::get_i_register_value() {
    return this->i_register;
}

void Cpu::set_i_register_value(uint16_t value) {
    this->i_register = value;
}


uint16_t Cpu::get_delay_register_value() {
    return this->delay_register;
}

void Cpu::set_delay_register_value(uint16_t value) {
    this->delay_register = value;
}

void Cpu::dec_delay_register_value() {
    this->delay_register--;
}

uint16_t Cpu::get_sound_register_value() {
    return this->sound_register;
}

void Cpu::set_sound_register_value(uint16_t value) {
    this->sound_register = value;
}

void Cpu::dec_sound_register_value() {
    this->sound_register--;
}

Cpu::~Cpu() {}
