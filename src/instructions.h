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

// Instructions encoded as _instr(name, opcode, func, encoding, flags)
#define INSTRUCTION_LIST \
    _instr("INT",   0x01, 0, enc_B, IGNORE_NONE) \
    _instr("USR",   0x01, 1, enc_B, IGNORE_IMM) \
    _instr("FBF",   0x01, 2, enc_B, IGNORE_IMM) \
    \
    _instr("OUTR",  0x02, 0, enc_M, IGNORE_IMM) \
    _instr("OUTI",  0x03, 0, enc_F, IGNORE_RS1) \
    _instr("INR",   0x04, 0, enc_M, IGNORE_IMM) \
    _instr("INI",   0x05, 0, enc_F, IGNORE_RS1) \
    \
    _instr("JAL",   0x06, 0, enc_M, IGNORE_RDE) \
    _instr("JALR",  0x07, 0, enc_M, IGNORE_NONE) \
    _instr("RET",   0x08, 0, enc_M, IGNORE_ALL_M) \
    _instr("RETR",  0x09, 0, enc_M, (IGNORE_RDE | IGNORE_IMM)) \
    _instr("BRA",   0x0a, 0, enc_B, IGNORE_NONE) \
    _instr("BEQ",   0x0a, 1, enc_B, IGNORE_NONE) \
    _instr("BEZ",   0x0a, 2, enc_B, IGNORE_NONE) \
    _instr("BLT",   0x0a, 3, enc_B, IGNORE_NONE) \
    _instr("BLE",   0x0a, 4, enc_B, IGNORE_NONE) \
    _instr("BLTU",  0x0a, 5, enc_B, IGNORE_NONE) \
    _instr("BLEU",  0x0a, 6, enc_B, IGNORE_NONE) \
    \
    _instr("PUSH",  0x0b, 0, enc_M, (IGNORE_RDE | IGNORE_IMM)) \
    _instr("POP",   0x0c, 0, enc_M, (IGNORE_RS1 | IGNORE_IMM)) \
    _instr("ENTER", 0x0d, 0, enc_B, (IGNORE_RDE | IGNORE_IMM)) \
    _instr("LEAVE", 0x0e, 0, enc_B, (IGNORE_RDE | IGNORE_IMM)) \
    \
    _instr("LLI",   0x10, 0, enc_F, IGNORE_NONE) \
    _instr("LLIS",  0x10, 1, enc_F, IGNORE_NONE) \
    _instr("LUI",   0x10, 2, enc_F, IGNORE_NONE) \
    _instr("LUIS",  0x10, 3, enc_F, IGNORE_NONE) \
    _instr("LTI",   0x10, 4, enc_F, IGNORE_NONE) \
    _instr("LTIS",  0x10, 5, enc_F, IGNORE_NONE) \
    _instr("LTUI",  0x10, 6, enc_F, IGNORE_NONE) \
    _instr("LTUIS", 0x10, 7, enc_F, IGNORE_NONE) \
    _instr("LW",    0x11, 0, enc_M, IGNORE_NONE) \
    _instr("LH",    0x12, 0, enc_M, IGNORE_NONE) \
    _instr("LHS",   0x13, 0, enc_M, IGNORE_NONE) \
    _instr("LQ",    0x14, 0, enc_M, IGNORE_NONE) \
    _instr("LQS",   0x15, 0, enc_M, IGNORE_NONE) \
    _instr("LB",    0x16, 0, enc_M, IGNORE_NONE) \
    _instr("LBS",   0x17, 0, enc_M, IGNORE_NONE) \
    _instr("SW",    0x18, 0, enc_M, IGNORE_NONE) \
    _instr("SH",    0x19, 0, enc_M, IGNORE_NONE) \
    _instr("SQ",    0x1a, 0, enc_M, IGNORE_NONE) \
    _instr("SB",    0x1b, 0, enc_M, IGNORE_NONE) \
    _instr("BSWP",  0x1c, 0, enc_M, IGNORE_IMM) \
    _instr("XCH",   0x1d, 0, enc_M, IGNORE_IMM) \
    \
    _instr("CMPR",  0x1e, 0, enc_R, (IGNORE_RDE | IGNORE_FUNC)) \
    _instr("CMPI",  0x1f, 0, enc_M, IGNORE_RDE) \
    \
    _instr("ADDR",  0x20, 0, enc_R, IGNORE_FUNC) \
    _instr("ADDI",  0x21, 0, enc_M, IGNORE_NONE) \
    _instr("SUBR",  0x22, 0, enc_R, IGNORE_FUNC) \
    _instr("SUBI",  0x23, 0, enc_M, IGNORE_NONE) \
    _instr("IMULR", 0x24, 0, enc_R, IGNORE_FUNC) \
    _instr("IMULI", 0x25, 0, enc_M, IGNORE_NONE) \
    _instr("IDIVR", 0x26, 0, enc_R, IGNORE_FUNC) \
    _instr("IDIVI", 0x27, 0, enc_M, IGNORE_NONE) \
    _instr("UMULR", 0x28, 0, enc_R, IGNORE_FUNC) \
    _instr("UMULI", 0x29, 0, enc_M, IGNORE_NONE) \
    _instr("UDIVR", 0x2a, 0, enc_R, IGNORE_FUNC) \
    _instr("UDIVI", 0x2b, 0, enc_M, IGNORE_NONE) \
    _instr("REMR",  0x2c, 0, enc_R, IGNORE_FUNC) \
    _instr("REMI",  0x2d, 0, enc_M, IGNORE_NONE) \
    _instr("MODR",  0x2e, 0, enc_R, IGNORE_FUNC) \
    _instr("MODI",  0x2f, 0, enc_M, IGNORE_NONE) \
    \
    _instr("ANDR",  0x30, 0, enc_R, IGNORE_FUNC) \
    _instr("ANDI",  0x31, 0, enc_M, IGNORE_NONE) \
    _instr("ORR",   0x32, 0, enc_R, IGNORE_FUNC) \
    _instr("ORI",   0x33, 0, enc_M, IGNORE_NONE) \
    _instr("NORR",  0x34, 0, enc_R, IGNORE_FUNC) \
    _instr("NORI",  0x35, 0, enc_M, IGNORE_NONE) \
    _instr("XORR",  0x36, 0, enc_R, IGNORE_FUNC) \
    _instr("XORI",  0x37, 0, enc_M, IGNORE_NONE) \
    _instr("SHLR",  0x38, 0, enc_R, IGNORE_FUNC) \
    _instr("SHLI",  0x39, 0, enc_M, IGNORE_NONE) \
    _instr("ASRR",  0x3a, 0, enc_R, IGNORE_FUNC) \
    _instr("ASRI",  0x3b, 0, enc_M, IGNORE_NONE) \
    _instr("LSRR",  0x3c, 0, enc_R, IGNORE_FUNC) \
    _instr("LSRI",  0x3d, 0, enc_M, IGNORE_NONE) \
    _instr("BITR",  0x3e, 0, enc_R, IGNORE_FUNC) \
    _instr("BITI",  0x3f, 0, enc_M, IGNORE_NONE) \
    \
    _instr("PTO",   0x40, 0, enc_M, IGNORE_IMM) \
    _instr("PFROM", 0x41, 0, enc_M, IGNORE_IMM) \
    _instr("PNEG",  0x42, 0, enc_M, IGNORE_IMM) \
    _instr("PABS",  0x43, 0, enc_M, IGNORE_IMM) \
    _instr("PADD",  0x44, 0, enc_R, IGNORE_IMM) \
    _instr("PSUB",  0x45, 0, enc_R, IGNORE_IMM) \
    _instr("PMUL",  0x46, 0, enc_R, IGNORE_IMM) \
    _instr("PDIV",  0x47, 0, enc_R, IGNORE_IMM)


#endif // INSTR_H
