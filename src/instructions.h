#ifndef _INSTR_H_
#define _INSTR_H_

#include "../include/kepler.h"

#define IGNORE_NONE 0
#define IGNORE_IMM 1
#define IGNORE_RS1 2
#define IGNORE_RS2 4
#define IGNORE_RDE 8
#define IGNORE_FUNC 16
#define IGNORE_ALL_M (IGNORE_IMM | IGNORE_RS1 | IGNORE_RDE)

#define ARG_BYTE " %#04x"
#define ARG_16 " %#06x"
#define ARG_20 " %#07x"
#define ARG_NONE ""
#define ARG_SEP ","
#define ARG_REG " %2s" // No register name is longer than 2 chars
#define ARG_RR ARG_REG ARG_SEP ARG_REG
#define ARG_RI ARG_REG ARG_SEP ARG_16
#define ARG_IR ARG_16 ARG_SEP ARG_REG
#define ARG_RIR ARG_RI ARG_SEP ARG_REG
#define ARG_ROF ARG_REG ARG_SEP " [" ARG_REG " +" ARG_16 " ]"
#define ARG_OFR " [" ARG_REG " +" ARG_16 " ]," ARG_REG
#define ARG_RRR ARG_RR ARG_SEP ARG_REG
#define ARG_RRI ARG_RR ARG_SEP ARG_16


typedef enum {
    ARGE_NON,
    ARGE_RDE,
    ARGE_RS1,
    ARGE_RS2,
    ARGE_IMM,
    ARGE_RDE_RS1,
    ARGE_RDE_IMM,
    ARGE_RS1_IMM,
    ARGE_RS1_RDE,
    ARGE_RS1_RS2,
    ARGE_IMM_RS1,
    ARGE_IMM_RDE,
    ARGE_RS1_IMM_RDE,
    ARGE_RDE_RS1_IMM,
    ARGE_RDE_RS1_RS2,
} arg_enc_t;

// Instructions encoded as
// _instr(
//      name,
//      opcode,
//      func,
//      encoding,
//      flags,
//      arg format string,
//      args encoding
//  )
#define INSTRUCTION_LIST \
    _instr("INT",   0x01, 0, enc_B, ARG_BYTE, ARGE_IMM) \
    _instr("USR",   0x01, 1, enc_B, ARG_NONE, ARGE_NON) \
    _instr("FBF",   0x01, 2, enc_B, ARG_NONE, ARGE_NON) \
    \
    _instr("OUTR",  0x02, 0, enc_M, ARG_RR,   ARGE_RDE_RS1) \
    _instr("OUTI",  0x03, 0, enc_F, ARG_IR,   ARGE_IMM_RS1) \
    _instr("INR",   0x04, 0, enc_M, ARG_RR,   ARGE_RS1_RDE) \
    _instr("INI",   0x05, 0, enc_F, ARG_IR,   ARGE_IMM_RDE) \
    \
    _instr("JAL",   0x06, 0, enc_M, ARG_RI,   ARGE_RS1_IMM) \
    _instr("JALR",  0x07, 0, enc_M, ARG_RIR,  ARGE_RS1_IMM_RDE) \
    _instr("RET",   0x08, 0, enc_M, ARG_NONE, ARGE_NON) \
    _instr("RETR",  0x09, 0, enc_M, ARG_REG,  ARGE_RS1) \
    _instr("BRA",   0x0a, 0, enc_B, ARG_20,   ARGE_IMM) \
    _instr("BEQ",   0x0a, 1, enc_B, ARG_20,   ARGE_IMM) \
    _instr("BEZ",   0x0a, 2, enc_B, ARG_20,   ARGE_IMM) \
    _instr("BLT",   0x0a, 3, enc_B, ARG_20,   ARGE_IMM) \
    _instr("BLE",   0x0a, 4, enc_B, ARG_20,   ARGE_IMM) \
    _instr("BLTU",  0x0a, 5, enc_B, ARG_20,   ARGE_IMM) \
    _instr("BLEU",  0x0a, 6, enc_B, ARG_20,   ARGE_IMM) \
    \
    _instr("PUSH",  0x0b, 0, enc_M, ARG_REG,  ARGE_RS1) \
    _instr("POP",   0x0c, 0, enc_M, ARG_REG,  ARGE_RDE) \
    _instr("ENTER", 0x0d, 0, enc_B, ARG_NONE, ARGE_NON) \
    _instr("LEAVE", 0x0e, 0, enc_B, ARG_NONE, ARGE_NON) \
    \
    _instr("LLI",   0x10, 0, enc_F, ARG_RI,   ARGE_RDE_IMM) \
    _instr("LLIS",  0x10, 1, enc_F, ARG_RI,   ARGE_RDE_IMM) \
    _instr("LUI",   0x10, 2, enc_F, ARG_RI,   ARGE_RDE_IMM) \
    _instr("LUIS",  0x10, 3, enc_F, ARG_RI,   ARGE_RDE_IMM) \
    _instr("LTI",   0x10, 4, enc_F, ARG_RI,   ARGE_RDE_IMM) \
    _instr("LTIS",  0x10, 5, enc_F, ARG_RI,   ARGE_RDE_IMM) \
    _instr("LTUI",  0x10, 6, enc_F, ARG_RI,   ARGE_RDE_IMM) \
    _instr("LTUIS", 0x10, 7, enc_F, ARG_RI,   ARGE_RDE_IMM) \
    _instr("LW",    0x11, 0, enc_M, ARG_ROF,  ARGE_RDE_RS1_IMM) \
    _instr("LH",    0x12, 0, enc_M, ARG_ROF,  ARGE_RDE_RS1_IMM) \
    _instr("LHS",   0x13, 0, enc_M, ARG_ROF,  ARGE_RDE_RS1_IMM) \
    _instr("LQ",    0x14, 0, enc_M, ARG_ROF,  ARGE_RDE_RS1_IMM) \
    _instr("LQS",   0x15, 0, enc_M, ARG_ROF,  ARGE_RDE_RS1_IMM) \
    _instr("LB",    0x16, 0, enc_M, ARG_ROF,  ARGE_RDE_RS1_IMM) \
    _instr("LBS",   0x17, 0, enc_M, ARG_ROF,  ARGE_RDE_RS1_IMM) \
    _instr("SW",    0x18, 0, enc_M, ARG_OFR,  ARGE_RS1_IMM_RDE) \
    _instr("SH",    0x19, 0, enc_M, ARG_OFR,  ARGE_RS1_IMM_RDE) \
    _instr("SQ",    0x1a, 0, enc_M, ARG_OFR,  ARGE_RS1_IMM_RDE) \
    _instr("SB",    0x1b, 0, enc_M, ARG_OFR,  ARGE_RS1_IMM_RDE) \
    _instr("BSWP",  0x1c, 0, enc_M, ARG_RR,   ARGE_RDE_RS1) \
    _instr("XCH",   0x1d, 0, enc_M, ARG_RR,   ARGE_RDE_RS1) \
    \
    _instr("CMPR",  0x1e, 0, enc_R, ARG_RR,   ARGE_RS1_RS2) \
    _instr("CMPI",  0x1f, 0, enc_M, ARG_RI,   ARGE_RS1_IMM) \
    \
    _instr("ADDR",  0x20, 0, enc_R, ARG_RRR,  ARGE_RDE_RS1_RS2) \
    _instr("ADDI",  0x21, 0, enc_M, ARG_RRI,  ARGE_RDE_RS1_IMM) \
    _instr("SUBR",  0x22, 0, enc_R, ARG_RRR,  ARGE_RDE_RS1_RS2) \
    _instr("SUBI",  0x23, 0, enc_M, ARG_RRI,  ARGE_RDE_RS1_IMM) \
    _instr("IMULR", 0x24, 0, enc_R, ARG_RRR,  ARGE_RDE_RS1_RS2) \
    _instr("IMULI", 0x25, 0, enc_M, ARG_RRI,  ARGE_RDE_RS1_IMM) \
    _instr("IDIVR", 0x26, 0, enc_R, ARG_RRR,  ARGE_RDE_RS1_RS2) \
    _instr("IDIVI", 0x27, 0, enc_M, ARG_RRI,  ARGE_RDE_RS1_IMM) \
    _instr("UMULR", 0x28, 0, enc_R, ARG_RRR,  ARGE_RDE_RS1_RS2) \
    _instr("UMULI", 0x29, 0, enc_M, ARG_RRI,  ARGE_RDE_RS1_IMM) \
    _instr("UDIVR", 0x2a, 0, enc_R, ARG_RRR,  ARGE_RDE_RS1_RS2) \
    _instr("UDIVI", 0x2b, 0, enc_M, ARG_RRI,  ARGE_RDE_RS1_IMM) \
    _instr("REMR",  0x2c, 0, enc_R, ARG_RRR,  ARGE_RDE_RS1_RS2) \
    _instr("REMI",  0x2d, 0, enc_M, ARG_RRI,  ARGE_RDE_RS1_IMM) \
    _instr("MODR",  0x2e, 0, enc_R, ARG_RRR,  ARGE_RDE_RS1_RS2) \
    _instr("MODI",  0x2f, 0, enc_M, ARG_RRI,  ARGE_RDE_RS1_IMM) \
    \
    _instr("ANDR",  0x30, 0, enc_R, ARG_RRR,  ARGE_RDE_RS1_RS2) \
    _instr("ANDI",  0x31, 0, enc_M, ARG_RRI,  ARGE_RDE_RS1_IMM) \
    _instr("ORR",   0x32, 0, enc_R, ARG_RRR,  ARGE_RDE_RS1_RS2) \
    _instr("ORI",   0x33, 0, enc_M, ARG_RRI,  ARGE_RDE_RS1_IMM) \
    _instr("NORR",  0x34, 0, enc_R, ARG_RRR,  ARGE_RDE_RS1_RS2) \
    _instr("NORI",  0x35, 0, enc_M, ARG_RRI,  ARGE_RDE_RS1_IMM) \
    _instr("XORR",  0x36, 0, enc_R, ARG_RRR,  ARGE_RDE_RS1_RS2) \
    _instr("XORI",  0x37, 0, enc_M, ARG_RRI,  ARGE_RDE_RS1_IMM) \
    _instr("SHLR",  0x38, 0, enc_R, ARG_RRR,  ARGE_RDE_RS1_RS2) \
    _instr("SHLI",  0x39, 0, enc_M, ARG_RRI,  ARGE_RDE_RS1_IMM) \
    _instr("ASRR",  0x3a, 0, enc_R, ARG_RRR,  ARGE_RDE_RS1_RS2) \
    _instr("ASRI",  0x3b, 0, enc_M, ARG_RRI,  ARGE_RDE_RS1_IMM) \
    _instr("LSRR",  0x3c, 0, enc_R, ARG_RRR,  ARGE_RDE_RS1_RS2) \
    _instr("LSRI",  0x3d, 0, enc_M, ARG_RRI,  ARGE_RDE_RS1_IMM) \
    _instr("BITR",  0x3e, 0, enc_R, ARG_RRR,  ARGE_RDE_RS1_RS2) \
    _instr("BITI",  0x3f, 0, enc_M, ARG_RRI,  ARGE_RDE_RS1_IMM) \
    \
    _instr("PTO",   0x40, 0, enc_M, ARG_RR,   ARGE_RDE_RS1) \
    _instr("PFROM", 0x41, 0, enc_M, ARG_RR,   ARGE_RDE_RS1) \
    _instr("PNEG",  0x42, 0, enc_M, ARG_RR,   ARGE_RDE_RS1) \
    _instr("PABS",  0x43, 0, enc_M, ARG_RR,   ARGE_RDE_RS1) \
    _instr("PADD",  0x44, 0, enc_R, ARG_RRR,  ARGE_RDE_RS1_RS2) \
    _instr("PSUB",  0x45, 0, enc_R, ARG_RRR,  ARGE_RDE_RS1_RS2) \
    _instr("PMUL",  0x46, 0, enc_R, ARG_RRR,  ARGE_RDE_RS1_RS2) \
    _instr("PDIV",  0x47, 0, enc_R, ARG_RRR,  ARGE_RDE_RS1_RS2)


#endif // INSTR_H
