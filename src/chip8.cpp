#include <random>
#include <fstream>
#include <iterator>
#include "instruction.hpp"
#include "chip8.hpp"

Chip8::Chip8(Memory* memory, Cpu* cpu):
    memory(memory), cpu(cpu) {
    std::random_device rd;
    this->rng_engine.seed(rd());
    this->ownMemory = false;
    this->ownCpu = false;
    this->ownScreen = false;
}

Chip8::Chip8(Memory* memory, Cpu* cpu, Screen* screen):
    memory(memory), cpu(cpu), screen(screen){
    std::random_device rd;
    this->rng_engine.seed(rd());
    this->ownMemory = false;
    this->ownCpu = false;
    this->ownScreen = false;
}

Chip8::Chip8() {
    this->memory = new Memory();
    this->cpu = new Cpu();
    this->screen = new Screen();
    // FIXME
    // bad way of doing it, may use
    // smart pointers later
    this->ownMemory = true;
    this->ownCpu = true;
    this->ownScreen = true;

    std::random_device rd;
    this->rng_engine.seed(rd());
}

Chip8::~Chip8() {
    // see Chip8() method, may change later
    if (this->ownMemory) {
        delete this->memory;
    }
    if (this->ownCpu) {
        delete this->cpu;
    }
    if (this->ownScreen) {
        delete this->screen;
    }
}

void Chip8::next() {
    uint16_t opcode = this->fetch_opcode();
    Instruction* decoded_instruction = decode_instruction(opcode);
    decoded_instruction->process_instruction(this);
    if (!decoded_instruction->get_has_jmp()) {
        this->get_cpu()->inc_program_counter_value(2);
    }
}

uint16_t Chip8::fetch_opcode() {
    return this->memory->get_16_bits_value(
        this->cpu->get_program_counter_value()
    );
}

void Chip8::load_rom(const char* file_path) {
    std::ifstream fs;
    fs.open(file_path, std::fstream::in | std::fstream::binary);
    int addr = DEFAULT_PROGRAM_COUNTER_VALUE;
    char buffer = '\0';

    while(!fs.eof()) {
        fs.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
        this->memory->set_8_bits_value(addr, buffer);
        addr++;
    }
    fs.close();
}

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
