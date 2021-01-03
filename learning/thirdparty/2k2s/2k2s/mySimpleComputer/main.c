#include <stdio.h>
#include "memory.h"

int main()
{
	sc_memoryInit();
	sc_memorySet(4, 24);

	sc_memoryPrint();

	sc_memorySave("Test.bin");
	//sc_memoryInit();
	//sc_memoryPrint();
	//sc_memoryLoad("Test");
	//sc_memoryPrint();

	return 0;
}