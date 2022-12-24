#include <vector>
#include "cpu.hpp"

Cpu::Cpu() {
    this->general_registers = std::vector<uint8_t>(REGISTER_COUNT);
    this->stack = std::vector<uint8_t>(STACK_SIZE);
    this->delay_register = 0;
    this->sound_register = 0;
    this->stack_pointer = 0;
    this->program_counter = 0;
    this->i_register = 0;
}

std::vector<uint8_t> Cpu::get_general_registers() {
    return this->general_registers;
}

std::vector<uint8_t> Cpu::get_stack() {
    return this->stack;
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

Cpu::~Cpu() {}
