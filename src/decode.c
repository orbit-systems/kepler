#include "../include/kepler.h"
#include "instructions.h"
#include <stdint.h>


const encoding_t encoding[256] = {
    #define _instr(name, op, func, enc, flags) [op] = enc,
    INSTRUCTION_LIST
    #undef _instr
};

const uint8_t flags[] = {
    #define _instr(name, op, func, enc, flags) [op << 4 | func] = flags,
    INSTRUCTION_LIST
    #undef _instr
};

void decode(uint32_t instr, instr_t* decoded) {
    uint8_t opcode = instr & 0xFF;
    encoding_t enc = encoding[opcode];
    decoded->opcode = opcode;
    decoded->enc = enc;
    switch (enc) {
        case enc_R:
            {
                uint16_t imm = (instr >> 8) & 0x0FFF;
                uint8_t rs2 = (instr >> 20) & 0x0F;
                uint8_t rs1 = (instr >> 24) & 0x0F;
                uint8_t rde = (instr >> 28) & 0x0F;
                decoded->data.r.imm = imm;
                decoded->data.r.rs2 = rs2;
                decoded->data.r.rs1 = rs1;
                decoded->data.r.rde = rde;
                decoded->flags = flags[opcode << 4 | 0x00];
            }
            break;
        case enc_M:
            {
                uint16_t imm = (instr >> 8) & 0xFFFF;
                uint8_t rs1 = (instr >> 24) & 0x0F;
                uint8_t rde = (instr >> 28) & 0x0F;
                decoded->data.m.imm = imm;
                decoded->data.m.rs1 = rs1;
                decoded->data.m.rde = rde;
                decoded->flags = flags[opcode << 4 | 0x00];
            }
            break;
        case enc_F:
            {
                uint16_t imm = (instr >> 8) & 0xFFFF;
                uint8_t func = (instr >> 24) & 0x0F;
                uint8_t rde = (instr >> 28) & 0x0F;
                decoded->data.f.imm = imm;
                decoded->data.f.func = func;
                decoded->data.f.rde = rde;
                decoded->flags = flags[opcode << 4 | func];
            }
            break;
        case enc_B:
            {
                uint32_t imm = (instr >> 8) & 0x0FFFFF;
                uint8_t func = (instr >> 28) & 0x0F;
                decoded->data.b.imm = imm;
                decoded->data.b.func = func;
                decoded->flags = flags[opcode << 4 | func];
            }
            break;
    }
}