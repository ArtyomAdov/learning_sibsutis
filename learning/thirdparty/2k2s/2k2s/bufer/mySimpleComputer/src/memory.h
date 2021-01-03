#ifndef MEMORY_H
#define MEMORY_H

#define SIZE 100

#define P 0b00000001//переполнение при выполнение операции
#define O 0b00000010//ошибка деления на 0
#define M 0b00000100//ошибка выхода за границы массива
#define T 0b00001000//игнорирование тактовых импульсов
#define E 0b00010000//указана неверная команда

int memory[SIZE];

int flag;

int sc_memoryInit();
int sc_memorySet(int, int);
int sc_memoryGet(int, int*);
int sc_memorySave(char*);
int sc_memoryLoad(char*);

int sc_regInit();
int sc_regSet(int, int);
int sc_regGet(int, int*);
int sc_commandEncode(int, int, int*);
int sc_commandDecode(int, int*, int*);
int sc_regFlagPrint();

#endif
