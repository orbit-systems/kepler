#include "../include/kepler.h"
#include "instructions.h"
#include <stdio.h>

void printM(instr_t* instr);
void printB(instr_t* instr);
void printF(instr_t* instr);
void printR(instr_t* instr);

int main(int argc, char** argv) {
    char* filename = argv[1];
    FILE* f;
    if (0 != fopen_s(&f, filename, "rb")) {
        perror("Error opening file");
        return 1;
    }

    uint8_t instrb[4];
    instr_t ins;
    size_t count = 0;
    while (fread(instrb, 4, 1, f)) {
        uint32_t instr = 0;
        instr |= ((uint32_t)instrb[0]) << 24;
        instr |= ((uint32_t)instrb[1]) << 16;
        instr |= ((uint32_t)instrb[2]) << 8;
        instr |= ((uint32_t)instrb[3]);
        decode(instr, &ins);
        printf("[%zx] %-5s", count, name(&ins));
        switch (ins.enc) {
            case enc_B:
                printB(&ins);
                break;
            case enc_M: 
                printM(&ins);
                break;
            case enc_F:
                printF(&ins);
                break;
            case enc_R:
                printR(&ins);
                break;
        }
        printf("\n");
        count++;
    }

    if (0 != fclose(f)) {
        perror("Error closing file");
        return 1;
    }
    return 0;
}

void printB(instr_t* instr) {
    if (!(instr->flags & IGNORE_IMM))
        printf(" %d", instr->data.b.imm);
}
void printM(instr_t* instr) {
    if (!(instr->flags & IGNORE_RDE))
        printf(" %s", regname(instr->data.m.rde));
    if (!(instr->flags & IGNORE_RS1))
        printf(" %s", regname(instr->data.m.rs1));
    if (!(instr->flags & IGNORE_IMM))
        printf(" %d", instr->data.m.imm);
}
void printF(instr_t* instr) {
    if (!(instr->flags & IGNORE_RDE))
        printf(" %s", regname(instr->data.f.rde));
    if (!(instr->flags & IGNORE_IMM))
        printf(" %d", instr->data.f.imm);
}
void printR(instr_t* instr) {
    if (!(instr->flags & IGNORE_RDE))
        printf(" %s", regname(instr->data.r.rde));
    if (!(instr->flags & IGNORE_RS1))
        printf(" %s", regname(instr->data.r.rs1));
    if (!(instr->flags & IGNORE_RS2))
        printf(" %s", regname(instr->data.r.rs2));
    if (!(instr->flags & IGNORE_IMM))
        printf(" %d", instr->data.r.imm);
}