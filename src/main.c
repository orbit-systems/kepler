#include "../include/kepler.h"
#include "instructions.h"

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

typedef struct {
    const char* fmt;
    arg_enc_t arge;
} print_info_t;

const print_info_t infos[] = {
    #define _instr(name, op, func, enc, argfmt, arge) [op << 4 | func] = {argfmt, arge},
    INSTRUCTION_LIST
    #undef _instr
};

void printB(instr_t* instr) {
    print_info_t info = infos[instr->opcode << 4 | instr->data.b.func];
    arg_enc_t arge = info.arge;
    switch (arge) {
        case ARGE_IMM:
            printf(info.fmt, instr->data.b.imm);
            break;
        default:
            break;
    }
}

void printM(instr_t* instr) {
    print_info_t info = infos[instr->opcode << 4 | 0x00];
    arg_enc_t arge = info.arge;
    data_M data = instr->data.m;
    switch (arge) {
        case ARGE_IMM:
            printf(info.fmt, data.imm);
            break;
        case ARGE_RDE:
            printf(info.fmt, regname(data.rde));
            break;
        case ARGE_RS1:
            printf(info.fmt, regname(data.rs1));
            break;
        case ARGE_IMM_RS1:
            printf(info.fmt, data.imm, regname(data.rs1));
            break;
        case ARGE_RDE_IMM:
            printf(info.fmt, regname(data.rde), data.imm);
            break;
        case ARGE_RDE_RS1:
            printf(info.fmt, regname(data.rde), regname(data.rs1));
            break;
        case ARGE_RS1_IMM:
            printf(info.fmt, regname(data.rs1), data.imm);
            break;
        case ARGE_RS1_RDE:
            printf(info.fmt, regname(data.rs1), regname(data.rde));
            break;
        case ARGE_IMM_RDE:
            printf(info.fmt, data.imm, regname(data.rde));
            break;
        case ARGE_RDE_RS1_IMM:
            printf(info.fmt, regname(data.rde), regname(data.rs1), data.imm);
            break;
        case ARGE_RS1_IMM_RDE:
            printf(info.fmt, regname(data.rs1), data.imm, regname(data.rde));
            break;
        default:
            break;
    }
}

void printF(instr_t* instr) {
    print_info_t info = infos[instr->opcode << 4 | instr->data.f.func];
    arg_enc_t arge = info.arge;
    data_F data = instr->data.f;
    switch (arge) {
        case ARGE_IMM:
            printf(info.fmt, data.imm);
            break;
        case ARGE_RDE:
            printf(info.fmt, regname(data.rde));
        case ARGE_IMM_RDE:
            printf(info.fmt, data.imm, regname(data.rde));
            break;
        case ARGE_RDE_IMM:
            printf(info.fmt, regname(data.rde), data.imm);
        default:
            break;
    }
}

void printR(instr_t* instr) {
    print_info_t info = infos[instr->opcode << 4 | 0x00];
    arg_enc_t arge = info.arge;
    data_R data = instr->data.r;
    switch (arge) {
        case ARGE_NON:
            break;
        case ARGE_IMM:
            printf(info.fmt, data.imm);
            break;
        case ARGE_RDE:
            printf(info.fmt, regname(data.rde));
            break;
        case ARGE_RS1:
            printf(info.fmt, regname(data.rs1));
            break;
        case ARGE_RS2:
            printf(info.fmt, regname(data.rs2));
            break;
        case ARGE_IMM_RS1:
            printf(info.fmt, data.imm, regname(data.rs1));
            break;
        case ARGE_RDE_IMM:
            printf(info.fmt, regname(data.rde), data.imm);
            break;
        case ARGE_RDE_RS1:
            printf(info.fmt, regname(data.rde), regname(data.rs1));
            break;
        case ARGE_RS1_IMM:
            printf(info.fmt, regname(data.rs1), data.imm);
            break;
        case ARGE_RS1_RDE:
            printf(info.fmt, regname(data.rs1), regname(data.rde));
            break;
        case ARGE_RS1_RS2:
            printf(info.fmt, regname(data.rs1), regname(data.rs2));
            break;
        case ARGE_IMM_RDE:
            printf(info.fmt, data.imm, regname(data.rde));
            break;
        case ARGE_RDE_RS1_IMM:
            printf(info.fmt, regname(data.rde), regname(data.rs1), data.imm);
            break;
        case ARGE_RS1_IMM_RDE:
            printf(info.fmt, regname(data.rs1), data.imm, regname(data.rde));
            break;
        case ARGE_RDE_RS1_RS2:
            printf(info.fmt, regname(data.rde), regname(data.rs1), regname(data.rs2));
            break;
    }
}