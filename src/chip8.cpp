#include <random>
#include "instruction.hpp"
#include "chip8.hpp"

Chip8::Chip8(Memory* memory, Cpu* cpu):
    memory(memory), cpu(cpu) {
    std::random_device rd;
    this->rng_engine.seed(rd());
}

Chip8::Chip8(Memory* memory, Cpu* cpu, Screen* screen):
    memory(memory), cpu(cpu), screen(screen){
    std::random_device rd;
    this->rng_engine.seed(rd());
}

Chip8::Chip8() {
    this->memory = new Memory();
    this->cpu = new Cpu();
    this->screen = new Screen();
    std::random_device rd;
    this->rng_engine.seed(rd());
}

void Chip8::next() {
    uint16_t opcode = this->fetch_opcode();
    Instruction* decoded_instruction = decode_instruction(opcode);
    decoded_instruction->process_instruction(this);
}

uint16_t Chip8::fetch_opcode() {
    return this->memory->get_16_bits_value(
        this->cpu->get_program_counter_value()
    );
}

Chip8::~Chip8() {}

Cpu* Chip8::get_cpu() {
    return this->cpu;
}

Memory* Chip8::get_memory() {
    return this->memory;
}

Screen* Chip8::get_screen() {
    return this->screen;
}

std::mt19937& Chip8::get_rng_engine() {
    return this->rng_engine;
}
