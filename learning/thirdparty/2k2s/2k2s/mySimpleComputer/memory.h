#ifndef MEMORY_H
#define MEMORY_H

int sc_memoryInit();
int sc_memorySet(int, int);
int sc_memoryGet(int, int*);
int sc_memorySave(char*);
int sc_memoryLoad(char*);
//int sc_regInit(void);
//int sc_regSet(int, int);
//int sc_regGet(int, int*);
//int sc_commandEncode(int, int, int*);
//int sc_commandDecode(int, int*, int*);

int sc_memoryPrint();

#endif