#include <cstdio>
#include <cassert>
#include <iostream>
#include "chip8.hpp"
#include "memory.hpp"
#include "cpu.hpp"

void test_set_get_memory() {
    Memory* memory = new Memory(4096);
    Cpu* cpu = new Cpu();
    Chip8* chip8 = new Chip8(memory, cpu);

    memory->set_8_bits_value(0, 0xaa);
    memory->set_8_bits_value(1, 0xbb);
    memory->set_16_bits_value(2, 0xccdd);

    assert(0xaa == memory->get_8_bits_value(0));
    assert(0xbb == memory->get_8_bits_value(1));
    assert(0xaabb == memory->get_16_bits_value(0));

    assert(0xcc == memory->get_8_bits_value(2));
    assert(0xdd == memory->get_8_bits_value(3));
    assert(0xccdd == memory->get_16_bits_value(2));
    
    delete(memory);
    delete(cpu);
    delete(chip8);
}

void test_get_set_pc() {
    Cpu* cpu = new Cpu();

    cpu->set_program_counter_value(0xff);
    assert(0xff == cpu->get_program_counter_value());

    cpu->set_program_counter_value(0xab);
    assert(0xab == cpu->get_program_counter_value());

    cpu->set_program_counter_value(0x1234);
    assert(0x1234 == cpu->get_program_counter_value());

    cpu->inc_program_counter_value();
    assert(0x1235 == cpu->get_program_counter_value());

    delete(cpu);
}

void test_fetch_instruction() {
    Memory* memory = new Memory(4096);
    Cpu* cpu = new Cpu();
    Chip8* chip8 = new Chip8(memory, cpu);

    cpu->set_program_counter_value(200);
    memory->set_16_bits_value(200, 0xabcd);
    assert(0xabcd == chip8->fetch_instruction());

    delete(memory);
    delete(cpu);
    delete(chip8);
}

int main() {
    test_set_get_memory();
    test_get_set_pc();
    test_fetch_instruction();
    std::cout << "all tests passed" << std::endl;
    return 0;
}
