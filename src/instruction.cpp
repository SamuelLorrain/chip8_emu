#include "instruction.hpp"

Instruction::Instruction() :
    x(0), y(0), addr(0), byte(0), nibble(0)
{}

Instruction::~Instruction() {}

Instruction* Instruction::set_x(int value) {
    this->x = value;
    return this;
}

Instruction* Instruction::set_y(int value) {
    this->y = value;
    return this;
}

Instruction* Instruction::set_addr(int value) {
    this->addr = value;
    return this;
}

Instruction* Instruction::set_byte(int value) {
    this->byte = value;
    return this;
}

Instruction* Instruction::set_nibble(int value) {
    this->nibble = value;
    return this;
}

void Instruction::set_values_from_opcode(uint16_t opcode) {
    this->set_x((opcode & 0x0f00) >> 8)
        ->set_y((opcode & 0x00f0) >> 4)
        ->set_addr(opcode & 0x0fff)
        ->set_byte(opcode & 0x00ff)
        ->set_nibble(opcode & 0x00f);
}

Instruction* dispatch_instruction_type(uint16_t opcode) {
    if (opcode == 0x00e0) { return new CLS(); }
    else if (opcode == 0x00ee) { return new RET(); }
    else if ((opcode & 0xf000) == 0x1000) { return new JPnnn(); }
    else if ((opcode & 0xf000) == 0x2000) { return new CALLnnn(); }
    else if ((opcode & 0xf000) == 0x3000) { return new SExb(); }
    else if ((opcode & 0xf000) == 0x4000) { return new SNExb(); }
    else if ((opcode & 0xf000) == 0x4000) { return new SNExb(); }
    else if ((opcode & 0xf000) == 0x5000) { return new SExy(); }
    else if ((opcode & 0xf000) == 0x6000) { return new LDxb(); }
    else if ((opcode & 0xf000) == 0x7000) { return new ADDxb(); }
    else if ((opcode & 0xf00f) == 0x8000) { return new LDxy(); }
    else if ((opcode & 0xf00f) == 0x8001) { return new ORxy(); }
    else if ((opcode & 0xf00f) == 0x8002) { return new ANDxy(); }
    else if ((opcode & 0xf00f) == 0x8003) { return new XORxy(); }
    else if ((opcode & 0xf00f) == 0x8004) { return new ADDxy(); }
    else if ((opcode & 0xf00f) == 0x8005) { return new SUBxy(); }
    else if ((opcode & 0xf00f) == 0x8006) { return new SHRxy(); }
    else if ((opcode & 0xf00f) == 0x8007) { return new SUBNxy(); }
    else if ((opcode & 0xf00f) == 0x800e) { return new SHLxy(); }
    else if ((opcode & 0xf00f) == 0x9000) { return new SNExy(); }
    else if ((opcode & 0xf000) == 0xa000) { return new LDinnn(); }
    else if ((opcode & 0xf000) == 0xa000) { return new LDinnn(); }
    else if ((opcode & 0xf000) == 0xb000) { return new JP0nnn(); }
    else if ((opcode & 0xf000) == 0xc000) { return new RNDxb(); }
    else if ((opcode & 0xf000) == 0xc000) { return new DRWxyn(); }
    else if ((opcode & 0xf0ff) == 0xe09e) { return new SKPx(); }
    else if ((opcode & 0xf0ff) == 0xe0a1) { return new SKNPx(); }
    else if ((opcode & 0xf0ff) == 0xf007) { return new LDxdt(); }
    else if ((opcode & 0xf0ff) == 0xf00a) { return new LDxk(); }
    else if ((opcode & 0xf0ff) == 0xf015) { return new LDdtx(); }
    else if ((opcode & 0xf0ff) == 0xf018) { return new LDstx(); }
    else if ((opcode & 0xf0ff) == 0xf01e) { return new ADDix(); }
    else if ((opcode & 0xf0ff) == 0xf029) { return new LDfx(); }
    else if ((opcode & 0xf0ff) == 0xf033) { return new LDbx(); }
    else if ((opcode & 0xf0ff) == 0xf055) { return new LDpix(); }
    else if ((opcode & 0xf0ff) == 0xf065) { return new LDxpi(); }
    else {
        throw "ErrorUnknownInstruction";
    }
}

Instruction* decode_instruction(uint16_t opcode) {
    Instruction* instruction = dispatch_instruction_type(opcode);
    instruction->set_values_from_opcode(opcode);
    return instruction;
}

CLS::CLS() : Instruction() {}
CLS::~CLS() {}
void CLS::process_instruction(Chip8* chip8) {
    // TODO TO IMPLEMENT
}

RET::RET() : Instruction() {}
RET::~RET() {}
void RET::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    cpu->set_program_counter_value(cpu->pop_stack());
}

JPnnn::JPnnn() : Instruction() {}
JPnnn::~JPnnn() {}
void JPnnn::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    cpu->set_program_counter_value(this->addr);
}

CALLnnn::CALLnnn() : Instruction() {}
CALLnnn::~CALLnnn() {}
void CALLnnn::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    cpu->push_stack(cpu->get_program_counter_value());
    cpu->set_program_counter_value(this->addr);
}

SExb::SExb() : Instruction() {}
SExb::~SExb() {}
void SExb::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    if (cpu->get_general_registers()[this->x] == this->byte) {
        cpu->inc_program_counter_value(2);
    }
}

SNExb::SNExb() : Instruction() {}
SNExb::~SNExb() {}
void SNExb::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    if (cpu->get_general_registers()[this->x] != this->byte) {
        cpu->inc_program_counter_value(2);
    }
}

SExy::SExy() : Instruction() {}
SExy::~SExy() {}
void SExy::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    if (cpu->get_general_registers()[this->x] == cpu->get_general_registers()[this->y]) {
        cpu->inc_program_counter_value(2);
    }
}

LDxb::LDxb() : Instruction() {}
LDxb::~LDxb() {}
void LDxb::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    cpu->get_general_registers()[this->x] = this->byte;
}

ADDxb::ADDxb() : Instruction() {}
ADDxb::~ADDxb() {}
void ADDxb::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    cpu->get_general_registers()[this->x] =
        (cpu->get_general_registers()[this->x] + this->byte) & 0xff;
}

LDxy::LDxy() : Instruction() {}
LDxy::~LDxy() {}
void LDxy::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    cpu->get_general_registers()[this->x] = cpu->get_general_registers()[this->y];
}

ORxy::ORxy() : Instruction() {}
ORxy::~ORxy() {}
void ORxy::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    cpu->get_general_registers()[this->x] |= cpu->get_general_registers()[this->y];
}

ANDxy::ANDxy() : Instruction() {}
ANDxy::~ANDxy() {}
void ANDxy::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    cpu->get_general_registers()[this->x] &= cpu->get_general_registers()[this->y];
}

XORxy::XORxy() : Instruction() {}
XORxy::~XORxy() {}
void XORxy::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    cpu->get_general_registers()[this->x] ^= cpu->get_general_registers()[this->y];
}

ADDxy::ADDxy() : Instruction() {}
ADDxy::~ADDxy() {}
void ADDxy::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    int x_value = cpu->get_general_registers()[this->x];
    int y_value = cpu->get_general_registers()[this->y];
    if ((x_value + y_value) > 0xff) {
        cpu->get_general_registers()[0xf] = 1;
    } else {
        cpu->get_general_registers()[0xf] = 0;
    }
    cpu->get_general_registers()[this->x] += cpu->get_general_registers()[this->y];
}

SUBxy::SUBxy() : Instruction() {}
SUBxy::~SUBxy() {}
void SUBxy::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    int x_value = cpu->get_general_registers()[this->x];
    int y_value = cpu->get_general_registers()[this->y];
    if (x_value > y_value) {
        cpu->get_general_registers()[0xf] = 1;
    }
    else {
        cpu->get_general_registers()[0xf] = 0;
    }
    cpu->get_general_registers()[this->x] -= cpu->get_general_registers()[this->y];
}

SHRxy::SHRxy() : Instruction() {}
SHRxy::~SHRxy() {}
void SHRxy::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    if ((cpu->get_general_registers()[this->x] & 0x1) == 1) {
        cpu->get_general_registers()[0xf] = 1;
    } else {
        cpu->get_general_registers()[0xf] = 0;
    }
    cpu->get_general_registers()[this->x] >>= 1;
}

SUBNxy::SUBNxy() : Instruction() {}
SUBNxy::~SUBNxy() {}
void SUBNxy::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    int x_value = cpu->get_general_registers()[this->x];
    int y_value = cpu->get_general_registers()[this->y];
    if (y_value > x_value) {
        cpu->get_general_registers()[0xf] = 1;
    }
    else {
        cpu->get_general_registers()[0xf] = 0;
    }
    cpu->get_general_registers()[this->x] =
        cpu->get_general_registers()[this->y] - cpu->get_general_registers()[this->x];
}

SHLxy::SHLxy() : Instruction() {}
SHLxy::~SHLxy() {}
void SHLxy::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    if ((cpu->get_general_registers()[this->x] >> 7) == 1) {
        cpu->get_general_registers()[0xf] = 1;
    } else {
        cpu->get_general_registers()[0xf] = 0;
    }
    cpu->get_general_registers()[this->x] <<= 1;
}

SNExy::SNExy() : Instruction() {}
SNExy::~SNExy() {}
void SNExy::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    if (cpu->get_general_registers()[this->x] != cpu->get_general_registers()[this->y]) {
        cpu->inc_program_counter_value(2);
    }
}

LDinnn::LDinnn() : Instruction() {}
LDinnn::~LDinnn() {}
void LDinnn::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    cpu->set_i_register_value(this->addr);
}

JP0nnn::JP0nnn() : Instruction() {}
JP0nnn::~JP0nnn() {}
void JP0nnn::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    cpu->set_program_counter_value(
        cpu->get_general_registers()[0x0] + this->addr
    );
}

RNDxb::RNDxb() : Instruction() {}
RNDxb::~RNDxb() {}
void RNDxb::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    cpu->get_general_registers()[this->x] = (chip8->get_rng_engine()() & this->byte);
}

DRWxyn::DRWxyn() : Instruction() {}
DRWxyn::~DRWxyn() {}
void DRWxyn::process_instruction(Chip8* chip8) {
    // TODO TO IMPLEMENT
}

SKPx::SKPx() : Instruction() {}
SKPx::~SKPx() {}
void SKPx::process_instruction(Chip8* chip8) {
    // TODO TO IMPLEMENT
}

SKNPx::SKNPx() : Instruction() {}
SKNPx::~SKNPx() {}
void SKNPx::process_instruction(Chip8* chip8) {
    // TODO TO IMPLEMENT
}

LDxdt::LDxdt() : Instruction() {}
LDxdt::~LDxdt() {}
void LDxdt::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    cpu->get_general_registers()[this->x] = cpu->get_delay_register_value();
}

LDxk::LDxk() : Instruction() {}
LDxk::~LDxk() {}
void LDxk::process_instruction(Chip8* chip8) {
    // TODO TO IMPLEMENT
}

LDdtx::LDdtx() : Instruction() {}
LDdtx::~LDdtx() {}
void LDdtx::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    cpu->set_delay_register_value(cpu->get_general_registers()[this->x]);
}

LDstx::LDstx() : Instruction() {}
LDstx::~LDstx() {}
void LDstx::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    cpu->set_sound_register_value(cpu->get_general_registers()[this->x]);
}

ADDix::ADDix() : Instruction() {}
ADDix::~ADDix() {}
void ADDix::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    cpu->set_i_register_value(
            cpu->get_i_register_value() +
            cpu->get_general_registers()[this->x]
    );
}

LDfx::LDfx() : Instruction() {}
LDfx::~LDfx() {}
void LDfx::process_instruction(Chip8* chip8) {
    // TODO TO IMPLEMENT
}

LDbx::LDbx() : Instruction() {}
LDbx::~LDbx() {}
void LDbx::process_instruction(Chip8* chip8) {
    // TODO TO IMPLEMENT
}

LDpix::LDpix() : Instruction() {}
LDpix::~LDpix() {}
void LDpix::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    Memory* memory = chip8->get_memory();
    for(int i = 0; i <= this->x; i++) {
        memory->set_8_bits_value(
            cpu->get_i_register_value() + i,
            cpu->get_general_registers()[i]
        );
    }
}

LDxpi::LDxpi() : Instruction() {}
LDxpi::~LDxpi() {}
void LDxpi::process_instruction(Chip8* chip8) {
    Cpu* cpu = chip8->get_cpu();
    Memory* memory = chip8->get_memory();
    for(int i = 0; i <= this->x; i++) {
        cpu->get_general_registers()[i] = 
            memory->get_8_bits_value(cpu->get_i_register_value() + i);
    }
}
