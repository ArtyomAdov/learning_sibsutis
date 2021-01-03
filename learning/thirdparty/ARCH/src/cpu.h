#ifndef CPU_H
#define CPU_H

#include "memory.h"
#include "myTerm.h"
#include <stdio.h>

int accumulator;
int instructionCounter;

#define READ 0x10
#define WRITE 0x11

#define LOAD 0x20
#define STORE 0x21

#define ADD 0x30
#define SUB 0x31
#define DIVIDE 0x32
#define MUL 0x33

#define JUMP 0x40
#define JNEG 0x41
#define JZ 0x42
#define HALT 0x43

#define NOT 0x51
#define AND 0x52
#define OR 0x53

int CU();
int ALU(int command, int operand);

#endif