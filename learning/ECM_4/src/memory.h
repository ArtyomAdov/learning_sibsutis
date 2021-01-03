#ifndef MEMORY_H
#define MEMORY_H

#define SIZE 100

#define P 0b00000001
#define O 0b00000010
#define M 0b00000100
#define T 0b00001000
#define E 0b00010000

int memory[SIZE];

int flag;

int sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int* value);
int sc_memorySave(char* filename);
int sc_memoryLoad(char* filename);

int sc_regInit();
int sc_regSet(int reg, int value);
int sc_regGet(int reg, int* value);
int sc_commandEncode(int command, int operand, int* value);
int sc_commandDecode(int value, int* command, int* operand);
int sc_regFlagPrint();

#endif
