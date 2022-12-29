#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <cstdint>
#include "chip8.hpp"

class Instruction {
    protected:
        uint8_t x;
        uint8_t y;
        uint16_t addr;
        int byte;
        int nibble;

    public:
        Instruction();
        Instruction* set_x(int value);
        Instruction* set_y(int value);
        Instruction* set_addr(int value);
        Instruction* set_byte(int value);
        Instruction* set_nibble(int value);
        virtual void process_instruction(Chip8* chip8) = 0;
        void set_values_from_opcode(uint16_t opcode);
};

Instruction* decode_instruction(uint16_t opcode);
Instruction* dispatch_instruction_type(uint16_t instruction);

class CLS : public Instruction {
    public:
        CLS();
        void process_instruction(Chip8* chip8) override;
};

class RET : public Instruction {
    public:
        RET();
        void process_instruction(Chip8* chip8) override;
};

class JPnnn: public Instruction {
    public:
        JPnnn();
        void process_instruction(Chip8* chip8) override; 
};

class CALLnnn : public Instruction {
    public:
        CALLnnn();
        void process_instruction(Chip8* chip8) override; 
};

class SExb : public Instruction {
    public:
        SExb();
        void process_instruction(Chip8* chip8) override;
};

class SNExb : public Instruction {
    public:
        SNExb();
        void process_instruction(Chip8* chip8) override;
};

class SExy : public Instruction {
    public:
        SExy();
        void process_instruction(Chip8* chip8) override;
};

class LDxb : public Instruction {
    public:
        LDxb();
        void process_instruction(Chip8* chip8) override;
};

class ADDxb : public Instruction {
    public:
        ADDxb();
        void process_instruction(Chip8* chip8) override;
};

class LDxy : public Instruction {
    public:
        LDxy();
        void process_instruction(Chip8* chip8) override;
};

class ORxy : public Instruction {
    public:
        ORxy();
        void process_instruction(Chip8* chip8) override;
};

class ANDxy : public Instruction {
    public:
        ANDxy();
        void process_instruction(Chip8* chip8) override;
};

class XORxy : public Instruction {
    public:
        XORxy();
        void process_instruction(Chip8* chip8) override;
};

class ADDxy : public Instruction {
    public:
        ADDxy();
        void process_instruction(Chip8* chip8) override;
};

class SUBxy : public Instruction {
    public:
        SUBxy();
        void process_instruction(Chip8* chip8) override;
};

class SHRxy : public Instruction {
    public:
        SHRxy();
        void process_instruction(Chip8* chip8) override;
};

class SUBNxy : public Instruction {
    public:
        SUBNxy();
        void process_instruction(Chip8* chip8) override;
};

class SHLxy : public Instruction {
    public:
        SHLxy();
        void process_instruction(Chip8* chip8) override;
};

class SNExy : public Instruction {
    public:
        SNExy();
        void process_instruction(Chip8* chip8) override; 
};

class LDinnn : public Instruction {
    public:
        LDinnn();
        void process_instruction(Chip8* chip8) override;
};

class JP0nnn : public Instruction {
    public:
        JP0nnn();
        void process_instruction(Chip8* chip8) override;
};

class RNDxb : public Instruction {
    public:
        RNDxb();
        void process_instruction(Chip8* chip8) override;
};

class DRWxyn : public Instruction {
    public:
        DRWxyn();
        void process_instruction(Chip8* chip8) override;
};

class SKPx : public Instruction {
    public:
        SKPx();
        void process_instruction(Chip8* chip8) override;
};

class SKNPx : public Instruction {
    public:
        SKNPx();
        void process_instruction(Chip8* chip8) override;
};

class LDxdt : public Instruction {
    public:
        LDxdt();
        void process_instruction(Chip8* chip8) override;
};

class LDxk : public Instruction {
    public:
        LDxk();
        void process_instruction(Chip8* chip8) override;
};

class LDdtx : public Instruction {
    public:
        LDdtx();
        void process_instruction(Chip8* chip8) override;
};

class LDstx : public Instruction {
    public:
        LDstx();
        void process_instruction(Chip8* chip8) override;
};

class ADDix : public Instruction {
    public:
        ADDix();
        void process_instruction(Chip8* chip8) override;
};

class LDfx : public Instruction {
    public:
        LDfx();
        void process_instruction(Chip8* chip8) override;
};

class LDbx : public Instruction {
    public:
        LDbx();
        void process_instruction(Chip8* chip8) override;
};

class LDpix : public Instruction {
    public:
        LDpix();
        void process_instruction(Chip8* chip8) override;
};

class LDxpi : public Instruction {
    public:
        LDxpi();
        void process_instruction(Chip8* chip8) override;
};

#endif
