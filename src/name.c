#include "../include/kepler.h"
#include "instructions.h"
#include <stdint.h>
#include <stdio.h>

const char* ins_name[] = {
    #define _instr(name, op, func, enc, flags) [op << 4 | func] = name,
    INSTRUCTION_LIST
    #undef _instr
};

const char* name(instr_t* instr) {
    uint8_t func;
    switch (instr->enc) {
        case enc_B: func = instr->data.b.func; break;
        case enc_F: func = instr->data.f.func; break;
        case enc_M: func = 0; break;
        case enc_R: func = 0; break;
    }
    return ins_name[instr->opcode << 4 | func];
}

const char* regnames[] = {
    "rz",
    "ra",
    "rb",
    "rc",
    "rd",
    "re",
    "rf",
    "rg",
    "rh",
    "ri",
    "rj",
    "rk",
    "pc",
    "sp",
    "fp",
    "st",
    "NR"
};

const char* regname(uint8_t reg) {
    if (reg > 0x15) return regnames[16];
    return regnames[reg];
}