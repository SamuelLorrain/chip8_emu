#include "instruction.hpp"

int decode_instruction(uint16_t instruction) {
    if (instruction == 0x00e0) { return CLS; }
    if (instruction == 0x00ee) { return RET; }
    if ((instruction & 0xf000) == 0) { return SYS; }
    if ((instruction & 0xf000) == 0x1000) { return JP; }
    if ((instruction & 0xf000) == 0x2000) { return CALL; }
    if ((instruction & 0xf000) == 0x3000) { return SExb; }
    if ((instruction & 0xf000) == 0x4000) { return SNExb; }
    if ((instruction & 0xf000) == 0x5000) { return SExy; }
    if ((instruction & 0xf000) == 0x6000) { return LDxb; }
    if ((instruction & 0xf000) == 0x7000) { return ADDxb; }
    if ((instruction & 0xf00f) == 0x8000) { return LDxy; }
    if ((instruction & 0xf00f) == 0x8001) { return ORxy; }
    if ((instruction & 0xf00f) == 0x8002) { return NON_EXISTANT_INSTRUCTION; }
    if ((instruction & 0xf00f) == 0x8003) { return NON_EXISTANT_INSTRUCTION; }
    if ((instruction & 0xf00f) == 0x8004) { return NON_EXISTANT_INSTRUCTION; }
    if ((instruction & 0xf00f) == 0x8005) { return NON_EXISTANT_INSTRUCTION; }
    if ((instruction & 0xf00f) == 0x8006) { return NON_EXISTANT_INSTRUCTION; }
    if ((instruction & 0xf00f) == 0x8007) { return NON_EXISTANT_INSTRUCTION; }
    if ((instruction & 0xf00f) == 0x800e) { return NON_EXISTANT_INSTRUCTION; }
    if ((instruction & 0xf00f) == 0x9000) { return NON_EXISTANT_INSTRUCTION; }
    if ((instruction & 0xf000) == 0xa000) { return NON_EXISTANT_INSTRUCTION; }
    if ((instruction & 0xf000) == 0xb000) { return NON_EXISTANT_INSTRUCTION; }
    if ((instruction & 0xf000) == 0xc000) { return NON_EXISTANT_INSTRUCTION; }
    if ((instruction & 0xf000) == 0xd000) { return NON_EXISTANT_INSTRUCTION; }
    if ((instruction & 0xf0ff) == 0xe09e) { return NON_EXISTANT_INSTRUCTION; }
    if ((instruction & 0xf0ff) == 0xe0a1) { return NON_EXISTANT_INSTRUCTION; }
    if ((instruction & 0xf0ff) == 0xf007) { return NON_EXISTANT_INSTRUCTION; }
    if ((instruction & 0xf0ff) == 0xf00a) { return NON_EXISTANT_INSTRUCTION; }
    if ((instruction & 0xf0ff) == 0xf015) { return NON_EXISTANT_INSTRUCTION; }
    if ((instruction & 0xf0ff) == 0xf018) { return NON_EXISTANT_INSTRUCTION; }
    if ((instruction & 0xf0ff) == 0xf01e) { return NON_EXISTANT_INSTRUCTION; }
    return NON_EXISTANT_INSTRUCTION;
}
