#include "memory.h"
#include <stdio.h>

int sc_memoryInit()
{
	for (int i = 0; i < SIZE; i++) {
		memory[i] = 0;
	}
	return 0;
}

int sc_memorySet(int address, int value)
{
	if (address >= SIZE || address < 0)
		return 1;//выход за границы памяти

	memory[address] = value;
	
	return 0;
}

int sc_memoryGet(int address, int *value)
{
	if (address >= SIZE || address < 0)
		return 1;//выход за границы памяти (C)

	*value = memory[address];

	return 0;
}

int sc_memorySave(char *filename)
{
	FILE *mem_file = fopen(filename, "wb");

	fwrite(memory, sizeof(int), SIZE, mem_file);
	fclose(mem_file);

	return 0;
}

int sc_memoryLoad(char *filename)
{
	FILE *mem_file = fopen(filename, "rb");

	fread(memory, sizeof(int), SIZE, mem_file);
	fclose(mem_file);

	return 0;
}

int sc_regInit()
{
	flag = 0;
	return 0;
}

int sc_regSet(int reg, int value)
{
	if (reg == P || reg == O || reg == M || reg == T || reg == E) {
		if (value == 0) {
			flag = flag & ~reg;
		} else if (value == 1) {
			flag = flag | reg;
		} else {
			return 0;
		}
	}
	return 0;
}

int sc_regGet(int reg, int *value)
{
	if (reg == P || reg == O || reg == M || reg == T || reg == E) {
		if ((flag & reg) != 0) {
			*value = 1;
		} else {
			*value = 0;
		}
	}
	return 0;
}

int sc_commandEncode(int command, int operand, int *value)
{
	if (command < 10 
		|| (command > 11 && command < 20) 
		|| (command > 21 && command < 30)
		|| (command > 33 && command < 40)
		|| (command > 43 && command < 51)
		|| command > 76)
	{
		return 1;
	}

	if (operand > 127 || operand < 0) {
		return 1;
	}

	*value = (command << 7) | operand;

	return 0;
}

int sc_commandDecode(int value, int *command, int *operand)
{
	if ((value >> 14) != 0) {
		return 1;
	}

	*command = value >> 7;
	*operand = value & 0x7F;
	return 0;
}

int sc_regFlagPrint()
{
	printf("%d\n", flag);
	return 0;
}
