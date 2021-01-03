#include "PrintAll.h"
#include "memory.c"
#include "cpu.c"

int bcint0[2] = {1717992960, 8283750};
int bcint1[2] = {471341056, 3938328};
int bcint2[2] = {538983424, 3935292};
int bcint3[2] = {2120252928, 8282238};
int bcint4[2] = {2120640000, 6316158};
int bcint5[2] = {2114092544, 8273984};
int bcint6[2] = {33701376, 4071998};
int bcint7[2] = {811630080, 396312};
int bcint8[2] = {2120646144, 8283750};
int bcint9[2] = {2087074816, 3956832};
int bcintA[2] = {2118269952, 4342338};
int bcintB[2] = {1044528640, 4080194};
int bcintC[2] = {37895168, 3949058};
int bcintD[2] = {1111637504, 4080194};
int bcintE[2] = {2114092544, 8258050};
int bcintF[2] = {33717760, 131646};
int bcintp[2] = {2115508224, 1579134};

int pa_ProgRun()
{
	enum keys key;

	pa_initComp();
	pa_printAllBox();
	pa_resetTerm();

	// int value = 0;
	accumulator = 0; 
	pa_resetTerm();
	FILE* test;
    test = fopen("output.o", "rb+");
    while (!feof(test)) {
        int data[3] = {0};
        fread(data, sizeof(int) * 3, 1, test);
        if (data[0] == 0 && data[1] == 0 && data[2] == 0)
            break;
        int value = 0;
        if(sc_commandEncode(data[1], data[2], &value) != 0)
        {
            printf("shkura %d",data[0]);
            fflush(stdout);
        }
        else
        {
            printf("norm\n");
            fflush(stdout);
        }
        sc_memorySet(data[0], value);
    }
    fclose(test);

	#if 0 //NOT
	int value = 0;
	value = (value | 0x51) << 7;
	value |= 74;
	sc_memorySet(25,value);
	// sc_memorySet(25,0x51);
	accumulator = 0xFFFC;
	pa_resetTerm();
	printf("%x",~accumulator);
	fflush(stdout);
	#endif

	#if 0
	sc_memorySet(99, 100);
	sc_memorySet(98, 2);

	int value = 0;
	value = (value | 0x20) << 7;
	value |= 99;
	sc_memorySet(0, value);

	#if 0
	// Test DIVIDE
	value = 0;
	value = (value | 0x32) << 7;
	value |= 98;
	sc_memorySet(1, value);
	#endif

	#if 1
	// Test JUMP
	value = 0;
	value = (value | 0x40) << 7;
	value |= 12;
	sc_memorySet(1, value);

	value = 0;
	value = (value | 0x43) << 7;
	sc_memorySet(13, value);
	#endif

	value = 0;
	value = (value | 0x21) << 7;
	value |= 96;
	sc_memorySet(2, value);

	value = 0;
	value = (value | 0x43) << 7;
	sc_memorySet(3, value);

	pa_resetTerm();
	#endif

	#if 1
	while (key != key_quit) {
		rk_readkey(&key);
		switch (key)
		{
			case (key_enter):
			{
				pa_keyNumber(key);
				break;
			}
			case (key_load):
			{
				pa_keyLoad();
				break;
			}
			case (key_save):
			{
				pa_keySave();
				break;
			}
			case (key_run):
			{
				pa_keyRun();
				break;
			}
			case (key_step):
			{
				pa_keyStep();
				break;
			}
			case (key_reset):
			{
				pa_keyReset();
				break;
			}
			case (key_accumulator):
			{
				pa_keyAccumulator();
				break;
			}
			case (key_instructionCounter):
			{
				pa_keyinstructionCounter();
				break;
			}
			case (key_up):
			{
				pa_moveUp();
				break;
			}
			case (key_down):
			{
				pa_moveDown();
				break;
			}
			case (key_right):
			{
				pa_moveRight();
				break;
			}
			case (key_left):
			{
				pa_moveLeft();
				break;
			}
			// case (key_plus):
			// {

			// 	break;
			// }
			default:
			{
				break;
			}
		}
	}
	#endif

	return 0;
}

//////////////////////////////
int pa_resetTerm()
{
	pa_printMemory();
	pa_resetBGColor();
	pa_printAccumulator();
	pa_printInstructionCounter();
	pa_printOperation();
	pa_printFlags();
	pa_printCase();

	#if 1
	// mt_gotoXY(23, 1);
	// printf("__________________________________\n");
	// printf("__________________________________\n");
	// printf("__________________________________\n");
	// printf("__________________________________\n");
	// printf("__________________________________\n");
	// printf("__________________________________\n");
	// printf("__________________________________\n");
	// printf("__________________________________\n");
	#endif

	#if 1
	int x, y;

	pa_getXY(&x, &y);

	mt_gotoXY(24, 1);
	printf("y = %d\n", y);
	printf("x = %d\n", x);
	printf("y_term(conv) = %d\n", y + 2);//
	printf("x_term(conv) = %d\n", 6 * (1 + x));//
	printf("instrCount = %d\n", instructionCounter);
	printf("instrCount(conv) = %d\n", y * 10 + x);
	printf("Size memory = %d\n", SIZE);//
	#endif

	mt_gotoXY(31, 1);
	fflush(stdout);
	return 0;
}

int pa_initComp()
{
	sc_memoryInit();
	sc_regInit();
	accumulator = 0;
	instructionCounter = 0;
	return 0;
}

int pa_printAllBox()
{
	mt_setscreensize(83, 47);

	mt_clrscr();

	pa_printBoxMemory();
	pa_printBoxAccumulator();
	pa_printBoxInstructionCounter();
	pa_printBoxOperation();
	pa_printBoxFlags();
	pa_printBoxCase();
	pa_printKeys();
	return 0;
}

//////////////////////////////
void pa_getXY(int *x, int *y)
{
	*x = instructionCounter % 10;
	*y = instructionCounter / 10;
}

//////////////////////////////
void pa_keyAccumulator()
{
	printf("Please enter need value for accumulator\n");
	fflush(stdout);
	scanf("%d",&accumulator);
	mt_clrscr();
	pa_printAllBox();
	pa_resetTerm();
}

void pa_keyinstructionCounter()
{
	printf("Please enter need value for instruction counter\n");
	fflush(stdout);
	scanf("%d",&instructionCounter);
	mt_clrscr();
	pa_printAllBox();
	pa_resetTerm();
}

void pa_keyLoad()
{
	#if 1
	int length = 15;
	char *filename = NULL;
	filename = (char*) calloc (length,sizeof(char));
	printf("\nWrite need file name (not more %d symbols) and click enter\n",length);
	fflush(stdout);
	scanf("%s",filename);
	if(sc_memoryLoad(filename) == 1)
	{
		mt_clrscr();
		pa_printAllBox();
		pa_resetTerm();
		printf("Error: not open file %s\n",filename);
		fflush(stdout);
	} else
	{
		pa_resetTerm();
	}
	free(filename);
	#else
	sc_memoryLoad("Test.bin");
	pa_resetTerm();
	#endif
}

void pa_keySave()
{
	#if 1
	int length = 15;
	char *filename = NULL;
	filename = (char*) calloc (length,sizeof(char));
	printf("\nWrite need file name (not more %d symbols) and click enter\n",length);
	fflush(stdout);
	scanf("%s",filename);
	if(sc_memorySave(filename) == 1)
	{
		mt_clrscr();
		pa_printAllBox();
		pa_resetTerm();
		printf("Error: not open file %s\n",filename);
		fflush(stdout);
	} else
	{
		pa_resetTerm();
	}
	free(filename);
	#else
	sc_memorySave("Test.bin");
	#endif
}

void pa_keyRun()
{
	int x, y;
	sc_regSet(T, 1);
	instructionCounter = 0;
	pa_getXY(&x, &y);
	while (!CU()) {
		pa_resetTerm();
		if ((instructionCounter + 1) < SIZE) 
			instructionCounter++;
		sleep(1);	// "Signal"
		pa_resetTerm();
	}
	// sc_regSet(T, 0);
	pa_resetTerm();
}

void pa_keyStep()
{
	int x, y;
	sc_regSet(T, 1);
	pa_getXY(&x, &y);
	CU();
	pa_resetTerm();
	if ((instructionCounter + 1) < SIZE) {
			instructionCounter++;
	}
	sleep(2);
	pa_resetTerm();
	sleep(2);
}

void pa_keyReset()
{
	pa_initComp();
	pa_resetTerm();
}

void pa_keyNumber(enum keys key)
{
	int x, y, local_value = 0;
	// int temp_value[4];
	// char buf[8] = {0};
	pa_getXY(&x,&y);
	#if 1
//	while(1)
//	{
		// for(short int i = 0; i < 0; i++)
		// {
		// 	read(read(STDIN_FILENO, temp_value[i], 8));
		// 	printf('%x',temp_value[i]);
		// }
		scanf("%x",&local_value);
		//printf("AA\n");
		//fflush(stdin);
		// if((local_value > 0x0000) || (local_value < 0xFFFF))
		// {
		// 	// printf("%x",local_value);
		// 	break;
		// }
//	}
	if (sc_memorySet(y * 10 + x, local_value) == 1) {
		sc_regSet(P, 1);
	}

	#else
	sc_memoryGet(y * 10 + x, &value);
	do{
		rk_readkey(&key);
		if (key < -1 || key > 9)
		{
			break;
		}
	} while(1);
	if (sc_memorySet(y * 10 + x, key + value) == 1) {
		sc_regSet(P, 1);
	}
	#endif
	instructionCounter = y * 10 + x;
	mt_clrscr();
	pa_printAllBox();
	instructionCounter = y * 10 + x;
	pa_resetTerm();
}

//////////////////////////////
void pa_moveUp()
{
	int x, y;
	pa_getXY(&x, &y);
	if (y != 0) {
		pa_setBGColor(0);
		y--;
		pa_setBGColor(1);
	}
	instructionCounter = y * 10 + x;
	pa_resetTerm();
}

void pa_moveDown()
{
	int x, y;
	pa_getXY(&x, &y);			
	if (y != 9) {
		pa_setBGColor(0);
		y++;
		pa_setBGColor(1);
	}
	instructionCounter = y * 10 + x;
	pa_resetTerm();
}

void pa_moveRight()
{
	int x, y;
	pa_getXY(&x, &y);
	pa_setBGColor(0);
	if (x != 9) {
		x++;
	} else if (x == 9 && y != 9) {
		x = 0;
		y++;
	}
	pa_setBGColor(1);
	instructionCounter = y * 10 + x;
	pa_resetTerm();
}

void pa_moveLeft()
{
	int x, y;
	pa_getXY(&x, &y);
	pa_setBGColor(0);
	if (x != 0) {
		x--;
	} else if (x == 0 && y != 0) {
		x = 9;
		y--;
	}
	pa_setBGColor(1);
	instructionCounter = y * 10 + x;
	pa_resetTerm();
}

//////////////////////////////
int pa_resetBGColor()
{
	pa_setBGColor(0);
	pa_setBGColor(1);
	fflush(stdout);
	return 0;
}

int pa_setBGColor(int ind)
{
	int x, y;
	pa_getXY(&x, &y);
	if (ind == 1) {
		mt_ssetbgcolor(cyan);
		mt_gotoXY(y + 2, (6 + 6 * x) - 4);
		printf("+%.4X", memory[instructionCounter]);
		mt_stopcolor();
	} else if (ind == 0) {
		mt_stopcolor();
		mt_gotoXY(y + 2, (6 + 6 * x) - 4);
		printf("+%.4X", memory[instructionCounter]);
	} else {
		return 1;
	}
	return 0;
}

int pa_printMemory()
{
	for (int i = 0; i < 10; i++) {
		mt_gotoXY(2 + i, 2);
		for (int j = 0; j < 10; j++) {
			if (j != 0)
				printf(" ");
			printf("+%.4X", memory[i * 10 + j]);
		}
	}
	return 0;
}

int pa_printAccumulator()
{
	mt_gotoXY(2, 70);
	printf("+%.4x", accumulator);
	return 0;
}

int pa_printInstructionCounter()
{
	mt_gotoXY(5, 70);
	printf("+%.4X", instructionCounter);
	return 0;
}

int pa_printOperation()
{
	int value;
	int command;
	int operand;
	int x, y;
	pa_getXY(&x, &y);
	sc_memoryGet(y * 10 + x, &value);
	mt_gotoXY(8, 69);
	if (sc_commandDecode(value, &command, &operand)) {
		printf("+00 : 00");
		return 1;
	}
	printf("+%.2X : %.2X", command, operand);
	return 0;
}

int pa_printFlags()
{
	int value_p, value_o, value_m, value_t, value_e;
	sc_regGet(O, &value_o);
	sc_regGet(P, &value_p);
	sc_regGet(T, &value_t);
	sc_regGet(E, &value_e);
	sc_regGet(M, &value_m);
	mt_gotoXY(11, 64);
	printf("P-%d O-%d M-%d T-%d E-%d", value_p, value_o, value_m, value_t, value_e);
	return 0;
}

int pa_printCase()
{
	bc_printbigchar(bcintp, BOX_ROW_MEMORY + 2, 2, purple, cyan);
	int value;
	int rank[4];
	int x, y;
	pa_getXY(&x, &y);
	sc_memoryGet(y * 10 + x, &value);
	for (int i = 0; i < 4; ++i) {
		rank[i] = value % 16;
		value /= 16;
	}
	for (int i = 38, j = 0; i >= 11; i -= 9, j++)
	{
		pa_printCaseBigChar(rank[j], i);
	}
	return 0;
}

int pa_printCaseBigChar(int value, int coord_y)
{
	switch (value) {
		case 0:
			bc_printbigchar(bcint0, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 1:
			bc_printbigchar(bcint1, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;		
		case 2:
			bc_printbigchar(bcint2, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 3:
			bc_printbigchar(bcint3, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 4:
			bc_printbigchar(bcint4, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 5:
			bc_printbigchar(bcint5, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 6:
			bc_printbigchar(bcint6, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 7:
			bc_printbigchar(bcint7, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 8:
			bc_printbigchar(bcint8, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 9:
			bc_printbigchar(bcint9, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 10:
			bc_printbigchar(bcintA, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 11:
			bc_printbigchar(bcintB, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 12:
			bc_printbigchar(bcintC, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 13:
			bc_printbigchar(bcintD, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 14:
			bc_printbigchar(bcintE, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 15:
			bc_printbigchar(bcintF, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
	}
	return 0;
}

//////////////////////////////
int pa_printBoxMemory()
{
	bc_box(1, 1, BOX_ROW_MEMORY, BOX_COLUMN_MEMORY);
	mt_gotoXY(1, 28);
	printf(" Memory ");
	return 0;
}

int pa_printBoxAccumulator()
{
	bc_box(1, BOX_COLUMN_MEMORY + 1, MINI_BOX_ROW, MINI_BOX_COLUMN);
	mt_gotoXY(1, 67);
	printf(" accumulator ");
	return 0;
}

int pa_printBoxInstructionCounter()
{
	bc_box(4, BOX_COLUMN_MEMORY + 1, MINI_BOX_ROW, MINI_BOX_COLUMN);
	mt_gotoXY(4, 63);
	printf(" instructionCounter ");
	return 0;
}

int pa_printBoxOperation()
{
	bc_box(7, BOX_COLUMN_MEMORY + 1, MINI_BOX_ROW, MINI_BOX_COLUMN);
	mt_gotoXY(7, 68);
	printf(" Operation ");
	return 0;
}

int pa_printBoxFlags()
{
	bc_box(10, BOX_COLUMN_MEMORY + 1, MINI_BOX_ROW, MINI_BOX_COLUMN);
	mt_gotoXY(10, 69);
	printf(" Flags ");
	return 0;
}

int pa_printBoxCase()
{
	int column = 46;
	int row = 10;
	bc_box(BOX_ROW_MEMORY + 1, 1, row, column);
	return 0;
}

int pa_printKeys()
{
	int column = 37;
	int row = 10;
	bc_box(13, 47, row, column);
	mt_gotoXY(13, 48);
	printf(" Keys: ");
	mt_gotoXY(14, 48);
	printf("l   - load");
	mt_gotoXY(15, 48);
	printf("s   - save");
	mt_gotoXY(16, 48);
	printf("r   - run");
	mt_gotoXY(17, 48);
	printf("t   - step");
	mt_gotoXY(18, 48);
	printf("i   - reset");
	mt_gotoXY(19, 48);
	printf("F5  - accumulator");
	mt_gotoXY(20, 48);
	printf("F6  - instructionCounter");
	mt_gotoXY(21, 48);
	printf("q   - exit");
	return 0;
}