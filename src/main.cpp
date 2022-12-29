#include <cstdio>
#include <cassert>
#include <iostream>
#include "chip8.hpp"
#include "memory.hpp"
#include "cpu.hpp"
#include "instruction.hpp"

constexpr int MEM_SIZE = 4096;

void test_set_get_memory() {
    Memory* memory = new Memory(MEM_SIZE);
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

void test_fetch_opcode() {
    Memory* memory = new Memory(MEM_SIZE);
    Cpu* cpu = new Cpu();
    Chip8* chip8 = new Chip8(memory, cpu);

    cpu->set_program_counter_value(200);
    memory->set_16_bits_value(200, 0xabcd);
    assert(0xabcd == chip8->fetch_opcode());

    delete(memory);
    delete(cpu);
    delete(chip8);
}

void test_ret_instruction() {
    Memory* memory = new Memory(MEM_SIZE);
    Cpu* cpu = new Cpu();
    Chip8* chip8 = new Chip8(memory, cpu);
    RET* ret = new RET();

    cpu->push_stack(0x1234);
    ret->process_instruction(chip8);
    assert(0x1234 == cpu->get_program_counter_value());

    delete(memory);
    delete(cpu);
    delete(chip8);
    delete(ret);
}

void test_jpnnn_instruction() {
    Memory* memory = new Memory(MEM_SIZE);
    Cpu* cpu = new Cpu();
    Chip8* chip8 = new Chip8(memory, cpu);
    JPnnn* jpnnn = new JPnnn();

    jpnnn->set_addr(0x1234);
    jpnnn->process_instruction(chip8);
    assert(0x1234 == cpu->get_program_counter_value());

    delete(memory);
    delete(cpu);
    delete(chip8);
    delete(jpnnn);
}

void test_callnnn_instruction() {
    Memory* memory = new Memory(MEM_SIZE);
    Cpu* cpu = new Cpu();
    Chip8* chip8 = new Chip8(memory, cpu);
    CALLnnn* callnnn = new CALLnnn();

    cpu->set_program_counter_value(0x200);
    callnnn->set_addr(0x1234);
    callnnn->process_instruction(chip8);
    assert(0x1234 == cpu->get_program_counter_value());
    assert(0x200 == cpu->pop_stack());

    delete(memory);
    delete(cpu);
    delete(chip8);
    delete(callnnn);
}

void test_sexb_instruction() {
    Memory* memory = new Memory(MEM_SIZE);
    Cpu* cpu = new Cpu();
    Chip8* chip8 = new Chip8(memory, cpu);
    SExb* sexb = new SExb();

    cpu->set_program_counter_value(0x200);
    cpu->get_general_registers()[0x0] = 0xaa;
    sexb->set_byte(0xaa);
    sexb->set_x(0);
    sexb->process_instruction(chip8);
    assert(cpu->get_program_counter_value() == 0x202);

    cpu->set_program_counter_value(0x200);
    cpu->get_general_registers()[0x0] = 0xaa;
    sexb->set_byte(0xbb);
    sexb->set_x(0);
    sexb->process_instruction(chip8);
    assert(cpu->get_program_counter_value() == 0x200);

    delete(memory);
    delete(cpu);
    delete(chip8);
    delete(sexb);
}

void test_snexb_instruction() {
    Memory* memory = new Memory(MEM_SIZE);
    Cpu* cpu = new Cpu();
    Chip8* chip8 = new Chip8(memory, cpu);
    SNExb* snexb = new SNExb();

    cpu->set_program_counter_value(0x200);
    cpu->get_general_registers()[0x0] = 0xaa;
    snexb->set_byte(0xaa);
    snexb->set_x(0);
    snexb->process_instruction(chip8);
    assert(cpu->get_program_counter_value() == 0x200);

    cpu->set_program_counter_value(0x200);
    cpu->get_general_registers()[0x0] = 0xaa;
    snexb->set_byte(0xbb);
    snexb->set_x(0);
    snexb->process_instruction(chip8);
    assert(cpu->get_program_counter_value() == 0x202);

    delete(memory);
    delete(cpu);
    delete(chip8);
    delete(snexb);
}

void test_sexy_instruction() {
    Memory* memory = new Memory(MEM_SIZE);
    Cpu* cpu = new Cpu();
    Chip8* chip8 = new Chip8(memory, cpu);
    SExy* sexy = new SExy();

    cpu->set_program_counter_value(0x200);
    cpu->get_general_registers()[0x0] = 0xaa;
    cpu->get_general_registers()[0x1] = 0xbb;
    sexy->set_x(0);
    sexy->set_y(1);
    sexy->process_instruction(chip8);
    assert(cpu->get_program_counter_value() == 0x200);

    cpu->set_program_counter_value(0x200);
    cpu->get_general_registers()[0x0] = 0xaa;
    cpu->get_general_registers()[0x1] = 0xaa;
    sexy->set_x(0);
    sexy->set_y(1);
    sexy->process_instruction(chip8);
    assert(cpu->get_program_counter_value() == 0x202);

    delete(memory);
    delete(cpu);
    delete(chip8);
    delete(sexy);
}

void test_ldxb_instruction() {
    Memory* memory = new Memory(MEM_SIZE);
    Cpu* cpu = new Cpu();
    Chip8* chip8 = new Chip8(memory, cpu);
    LDxb* ldxb = new LDxb();

    ldxb->set_byte(0x99);
    for(int i = 0x0; i <= 0xf; i++) {
        cpu->get_general_registers()[i] = 0x00;
        ldxb->set_x(i);
        ldxb->process_instruction(chip8);
        assert(cpu->get_general_registers()[i] == 0x99);
    }

    delete(memory);
    delete(cpu);
    delete(chip8);
    delete(ldxb);
}

void test_addxb_instruction() {
    Memory* memory = new Memory(MEM_SIZE);
    Cpu* cpu = new Cpu();
    Chip8* chip8 = new Chip8(memory, cpu);
    ADDxb* addxb = new ADDxb();

    addxb->set_x(0);
    addxb->set_byte(0xaa);
    cpu->get_general_registers()[0x0] = 0xaa;
    addxb->process_instruction(chip8);
    assert(cpu->get_general_registers()[0x0] == 0x54);

    addxb->set_x(0);
    addxb->set_byte(0x1);
    cpu->get_general_registers()[0x0] = 0xff;
    addxb->process_instruction(chip8);
    assert(cpu->get_general_registers()[0x0] == 0x0);

    delete(memory);
    delete(cpu);
    delete(chip8);
    delete(addxb);
}

void test_ldxy_instruction() {
    Memory* memory = new Memory(MEM_SIZE);
    Cpu* cpu = new Cpu();
    Chip8* chip8 = new Chip8(memory, cpu);
    LDxy* ldxy = new LDxy();

    ldxy->set_x(0);
    ldxy->set_y(1);
    cpu->get_general_registers()[0x0] = 0xaa;
    cpu->get_general_registers()[0x1] = 0xbb;
    ldxy->process_instruction(chip8);
    assert(cpu->get_general_registers()[0x0] == 0xbb);

    delete(memory);
    delete(cpu);
    delete(chip8);
    delete(ldxy);
}

void test_orxy_instruction() {
    Memory* memory = new Memory(MEM_SIZE);
    Cpu* cpu = new Cpu();
    Chip8* chip8 = new Chip8(memory, cpu);
    ORxy* orxy = new ORxy();

    orxy->set_x(0);
    orxy->set_y(1);
    cpu->get_general_registers()[0x0] = 0x9a;
    cpu->get_general_registers()[0x1] = 0x9c;
    orxy->process_instruction(chip8);
    assert(cpu->get_general_registers()[0x0] == 0x9e);

    delete(memory);
    delete(cpu);
    delete(chip8);
    delete(orxy);
}

void test_andxy_instruction() {
    Memory* memory = new Memory(MEM_SIZE);
    Cpu* cpu = new Cpu();
    Chip8* chip8 = new Chip8(memory, cpu);
    ANDxy* andxy = new ANDxy();

    andxy->set_x(0);
    andxy->set_y(1);
    cpu->get_general_registers()[0x0] = 0x9a;
    cpu->get_general_registers()[0x1] = 0x9c;
    andxy->process_instruction(chip8);
    assert(cpu->get_general_registers()[0x0] == 0x98);

    delete(memory);
    delete(cpu);
    delete(chip8);
    delete(andxy);
}

void test_xorxy_instruction() {
    Memory* memory = new Memory(MEM_SIZE);
    Cpu* cpu = new Cpu();
    Chip8* chip8 = new Chip8(memory, cpu);
    XORxy* xorxy = new XORxy();

    xorxy->set_x(0);
    xorxy->set_y(1);
    cpu->get_general_registers()[0x0] = 0x9a;
    cpu->get_general_registers()[0x1] = 0x9c;
    xorxy->process_instruction(chip8);
    assert(cpu->get_general_registers()[0x0] == 0x6);

    delete(memory);
    delete(cpu);
    delete(chip8);
    delete(xorxy);
}

void test_addxy_instruction() {
    Memory* memory = new Memory(MEM_SIZE);
    Cpu* cpu = new Cpu();
    Chip8* chip8 = new Chip8(memory, cpu);
    ADDxy* addxy = new ADDxy();

    addxy->set_x(0);
    addxy->set_y(1);
    cpu->get_general_registers()[0x0] = 0xff;
    cpu->get_general_registers()[0x1] = 0x1;
    addxy->process_instruction(chip8);
    assert(cpu->get_general_registers()[0x0] == 0x0);
    assert(cpu->get_general_registers()[0xf] == 0x1);

    cpu->get_general_registers()[0x0] = 0xaa;
    cpu->get_general_registers()[0x1] = 0x10;
    addxy->process_instruction(chip8);
    assert(cpu->get_general_registers()[0x0] == 0xba);
    assert(cpu->get_general_registers()[0xf] == 0x0);

    delete(memory);
    delete(cpu);
    delete(chip8);
    delete(addxy);
}

void test_subxy_instruction() {
    Memory* memory = new Memory(MEM_SIZE);
    Cpu* cpu = new Cpu();
    Chip8* chip8 = new Chip8(memory, cpu);
    SUBxy* subxy = new SUBxy();

    subxy->set_x(0);
    subxy->set_y(1);
    cpu->get_general_registers()[0x0] = 0x1;
    cpu->get_general_registers()[0x1] = 0x2;
    subxy->process_instruction(chip8);
    assert(cpu->get_general_registers()[0x0] == 0xff);
    assert(cpu->get_general_registers()[0xf] == 0x0);

    cpu->get_general_registers()[0x0] = 0x2;
    cpu->get_general_registers()[0x1] = 0x2;
    subxy->process_instruction(chip8);
    assert(cpu->get_general_registers()[0x0] == 0x0);
    assert(cpu->get_general_registers()[0xf] == 0x0);

    cpu->get_general_registers()[0x0] = 0x3;
    cpu->get_general_registers()[0x1] = 0x2;
    subxy->process_instruction(chip8);
    assert(cpu->get_general_registers()[0x0] == 0x1);
    assert(cpu->get_general_registers()[0xf] == 0x1);

    delete(memory);
    delete(cpu);
    delete(chip8);
    delete(subxy);
}

void test_shrxy_instruction() {
    Memory* memory = new Memory(MEM_SIZE);
    Cpu* cpu = new Cpu();
    Chip8* chip8 = new Chip8(memory, cpu);
    SHRxy* shrxy = new SHRxy();

    shrxy->set_x(0);
    cpu->get_general_registers()[0x0] = 0b1;
    shrxy->process_instruction(chip8);
    assert(cpu->get_general_registers()[0x0] == 0x0);
    assert(cpu->get_general_registers()[0xf] == 0x1);

    cpu->get_general_registers()[0x0] = 0b10;
    shrxy->process_instruction(chip8);
    assert(cpu->get_general_registers()[0x0] == 0b1);
    assert(cpu->get_general_registers()[0xf] == 0x0);

    cpu->get_general_registers()[0x0] = 0b101;
    shrxy->process_instruction(chip8);
    assert(cpu->get_general_registers()[0x0] == 0b10);
    assert(cpu->get_general_registers()[0xf] == 0x1);

    delete(memory);
    delete(cpu);
    delete(chip8);
    delete(shrxy);
}

void test_subnxy_instruction() {
    Memory* memory = new Memory(MEM_SIZE);
    Cpu* cpu = new Cpu();
    Chip8* chip8 = new Chip8(memory, cpu);
    SUBNxy* subnxy = new SUBNxy();

    subnxy->set_x(0);
    subnxy->set_y(1);
    cpu->get_general_registers()[0x0] = 0x2;
    cpu->get_general_registers()[0x1] = 0x1;
    subnxy->process_instruction(chip8);
    assert(cpu->get_general_registers()[0x0] == 0xff);
    assert(cpu->get_general_registers()[0xf] == 0x0);

    cpu->get_general_registers()[0x0] = 0x2;
    cpu->get_general_registers()[0x1] = 0x2;
    subnxy->process_instruction(chip8);
    assert(cpu->get_general_registers()[0x0] == 0x0);
    assert(cpu->get_general_registers()[0xf] == 0x0);

    cpu->get_general_registers()[0x0] = 0x2;
    cpu->get_general_registers()[0x1] = 0x3;
    subnxy->process_instruction(chip8);
    assert(cpu->get_general_registers()[0x0] == 0x1);
    assert(cpu->get_general_registers()[0xf] == 0x1);

    delete(memory);
    delete(cpu);
    delete(chip8);
    delete(subnxy);
}

void test_shlxy_instruction() {
    Memory* memory = new Memory(MEM_SIZE);
    Cpu* cpu = new Cpu();
    Chip8* chip8 = new Chip8(memory, cpu);
    SHLxy* shlxy = new SHLxy();

    shlxy->set_x(0);
    cpu->get_general_registers()[0x0] = 0b00000101;
    shlxy->process_instruction(chip8);
    assert(cpu->get_general_registers()[0x0] == 0b00001010);
    assert(cpu->get_general_registers()[0xf] == 0b0);

    cpu->get_general_registers()[0x0] = 0b10000101;
    shlxy->process_instruction(chip8);
    assert(cpu->get_general_registers()[0x0] == 0b00001010);
    assert(cpu->get_general_registers()[0xf] == 0b1);

    delete(memory);
    delete(cpu);
    delete(chip8);
    delete(shlxy);
}

void test_snexy_instruction() {
    Memory* memory = new Memory(MEM_SIZE);
    Cpu* cpu = new Cpu();
    Chip8* chip8 = new Chip8(memory, cpu);
    SNExy* snexy = new SNExy();

    cpu->set_program_counter_value(0x200);
    cpu->get_general_registers()[0x0] = 0xaa;
    cpu->get_general_registers()[0x1] = 0xbb;
    snexy->set_x(0);
    snexy->set_y(1);
    snexy->process_instruction(chip8);
    assert(cpu->get_program_counter_value() == 0x202);

    cpu->set_program_counter_value(0x200);
    cpu->get_general_registers()[0x0] = 0xaa;
    cpu->get_general_registers()[0x1] = 0xaa;
    snexy->set_x(0);
    snexy->set_y(1);
    snexy->process_instruction(chip8);
    assert(cpu->get_program_counter_value() == 0x200);

    delete(memory);
    delete(cpu);
    delete(chip8);
    delete(snexy);
}

void test_ldinnn_instruction() {
    Memory* memory = new Memory(MEM_SIZE);
    Cpu* cpu = new Cpu();
    Chip8* chip8 = new Chip8(memory, cpu);
    LDinnn* ldinnn = new LDinnn();

    cpu->set_i_register_value(0x0);
    ldinnn->set_addr(0x1234);
    ldinnn->process_instruction(chip8);
    assert(cpu->get_i_register_value() == 0x1234);

    delete(memory);
    delete(cpu);
    delete(chip8);
    delete(ldinnn);
}

void test_jp0nnn_instruction() {
    Memory* memory = new Memory(MEM_SIZE);
    Cpu* cpu = new Cpu();
    Chip8* chip8 = new Chip8(memory, cpu);
    JP0nnn* jp0nnn = new JP0nnn();

    jp0nnn->set_addr(0x1234);
    cpu->get_general_registers()[0x0] = 0xff;
    jp0nnn->process_instruction(chip8);
    assert(cpu->get_program_counter_value() == (0x1234+0xff));

    delete(memory);
    delete(cpu);
    delete(chip8);
    delete(jp0nnn);
}

void test_rndxb_instruction() {
    assert(0 == 1);
}

int main() {
    test_set_get_memory();
    test_get_set_pc();
    test_fetch_opcode();

    // instructions test
    test_ret_instruction();
    test_jpnnn_instruction();
    test_callnnn_instruction();
    test_sexb_instruction();
    test_snexb_instruction();
    test_sexy_instruction();
    test_ldxb_instruction();
    test_addxb_instruction();
    test_ldxy_instruction();
    test_orxy_instruction();
    test_andxy_instruction();
    test_xorxy_instruction();
    test_addxy_instruction();
    test_subxy_instruction();
    test_shrxy_instruction();
    test_subnxy_instruction();
    test_shlxy_instruction();
    test_snexy_instruction();
    test_ldinnn_instruction();
    test_jp0nnn_instruction();
    /* TODO TESTING following instructions */
    /* test_rndxb_instruction(); */

    std::cout << "all tests passed" << std::endl;
    return 0;
}
