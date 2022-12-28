#include <stack>
#include <vector>
#include "cpu.hpp"

Cpu::Cpu() {
    this->general_registers = std::vector<uint8_t>(REGISTER_COUNT);
    this->stack = std::stack<uint16_t>();
    this->delay_register = 0;
    this->sound_register = 0;
    this->program_counter = 0;
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

void Cpu::inc_program_counter_value() {
    this->program_counter++;
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

Cpu::~Cpu() {}
