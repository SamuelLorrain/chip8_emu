#include "instruction.hpp"
#include "chip8.hpp"


Chip8::Chip8(Memory* memory, Cpu* cpu):
    memory(memory), cpu(cpu) {}

void Chip8::next() {
    uint16_t opcode = this->fetch_opcode();
    Instruction decoded_instruction = decode_instruction(opcode);
    /* process_instruction(decoded_instruction); */
}

uint16_t Chip8::fetch_opcode() {
    return this->memory->get_16_bits_value(
        this->cpu->get_program_counter_value()
    );
}

Chip8::~Chip8() {}
