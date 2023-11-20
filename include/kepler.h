#ifndef _KEPLER_H_
#define _KEPLER_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef enum {
    enc_R,
    enc_M,
    enc_F,
    enc_B,
} encoding_t;

typedef struct {
    uint16_t imm;
    uint8_t rde;
    uint8_t rs1;
    uint8_t rs2;
} data_R;

typedef struct {
    uint16_t imm;
    uint8_t rde;
    uint8_t rs1;
} data_M;

typedef struct {
    uint16_t imm;
    uint8_t rde;
    uint8_t func;
} data_F;

typedef struct {
    uint32_t imm;
    uint8_t func;
} data_B;

typedef union {
    data_R r;
    data_M m;
    data_F f;
    data_B b;
} instr_data_t;

typedef struct {
    instr_data_t data;
    encoding_t enc;
    uint8_t opcode;
    uint8_t flags;
} instr_t;

void decode(uint32_t instr, instr_t* decoded);
const char* name(instr_t* instr);
const char* regname(uint8_t reg);

#endif // KEPLER_H