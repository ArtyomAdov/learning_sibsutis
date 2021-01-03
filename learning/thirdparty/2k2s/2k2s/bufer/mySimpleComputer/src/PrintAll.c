#include "PrintAll.h"

int bcint0 [2] = {1717992960, 8283750};
int bcint1 [2] = {471341056, 3938328};
int bcint2 [2] = {538983424, 3935292};
int bcint3 [2] = {2120252928, 8282238};
int bcint4 [2] = {2120640000, 6316158};
int bcint5 [2] = {2114092544, 8273984};
int bcint6 [2] = {33701376, 4071998};
int bcint7 [2] = {811630080, 396312};
int bcint8 [2] = {2120646144, 8283750};
int bcint9 [2] = {2087074816, 3956832};
int bcintA [2] = {2118269952, 4342338};
int bcintB [2] = {1044528640, 4080194};
int bcintC [2] = {37895168, 3949058};
int bcintD [2] = {1111637504, 4080194};
int bcintE [2] = {2114092544, 8258050};
int bcintF [2] = {33717760, 131646};
int bcintp [2] = {2115508224, 1579134};

int pa_ProgRun()
{
	int x = 0;
	int y = 0;
	int x_term = 6;
	int y_term = 2;

	enum keys key;

	pa_printAll(y, x, y_term, x_term);

	while (key != key_q) {
		rk_readkey(&key);

		if (key == key_s) {
			sc_memorySave("Test.bin");
		} else if (key == key_l) {
			sc_memoryLoad("Test.bin");
			pa_printMemory();
			mt_gotoXY(23, 1);
			fflush(stdout);
		} else if (key == key_up) {
			if (y != 0) {
				pa_setBGColor(0, y, x, y_term, x_term);
				y--;
				y_term--;
				pa_setBGColor(1, y, x, y_term, x_term);
			}
		} else if (key == key_down) {
			if (y != 9) {
				pa_setBGColor(0, y, x, y_term, x_term);
				y++;
				y_term++;
				pa_setBGColor(1, y, x, y_term, x_term);
			}
		} else if (key == key_right) {
			pa_setBGColor(0, y, x, y_term, x_term);
			if (x != 9) {
				x++;
				x_term += 6;		
			} else if (x == 9 && y != 9) {
				x = 0;
				x_term = 6;
				y++;
				y_term++;
			}
			pa_setBGColor(1, y, x, y_term, x_term);
		} else if (key == key_left) {
			pa_setBGColor(0, y, x, y_term, x_term);
			if (x != 0) {
				x--;
				x_term -= 6;
			} else if (x == 0 && y != 0) {
				x = 9;
				x_term = 60;
				y--;
				y_term--;
			}
			pa_setBGColor(1, y, x, y_term, x_term);
		} else if (key >= 0 && key <= 9) {
			int value;
			sc_memoryGet(y * 10 + x, &value);
			sc_memorySet(y * 10 + x, key + value);
		}

		pa_resetBGColor(y, x, y_term, x_term);
		pa_printCase(y, x);

		mt_gotoXY(26, 1);

		fflush(stdout);
	}

	return 0;
}

int pa_setBGColor(int ind, int y, int x, int y_term, int x_term)
{
	if (ind == 1) {
		enum colors a = cyan;
		mt_ssetbgcolor(a);
		mt_gotoXY(y_term, x_term - 4);
		printf("+%.4X", memory[y * 10 + x]);
		mt_stopcolor();
	} else if (ind == 0) {
		mt_stopcolor();
		mt_gotoXY(y_term, x_term - 4);
		printf("+%.4X", memory[y * 10 + x]);
	} else {
		return 1;
	}
	return 0;
}

int pa_resetBGColor(int y, int x, int y_term, int x_term)
{
	pa_setBGColor(0, y, x, y_term, x_term);
	pa_setBGColor(1, y, x, y_term, x_term);
	fflush(stdout);

	return 0;
}

int pa_printAll(int y, int x, int y_term, int x_term)
{
	mt_clrscr();

	pa_initprintMemory();
	pa_printAccumulator();
	pa_printBoxInstructionCounter();
	pa_printInstructionCounter();
	pa_printOperation();
	pa_printFlags();
	pa_printBoxCase();
	pa_printKeys();

	pa_setBGColor(1, y, x, y_term, x_term);
	pa_printCase(y, x);

	mt_gotoXY(26, 1);

	fflush(stdout);

	return 0;
}

int pa_initprintMemory()
{
	sc_memoryInit();
	pa_printBoxMemory();
	pa_printMemory();

	return 0;
}

int pa_printBoxMemory()
{
	bc_box(1, 1, BOX_ROW_MEMORY, BOX_COLUMN_MEMORY);
	return 0;
}

int pa_printMemory()
{
	mt_gotoXY(1, 28);
	printf(" Memory ");
	for (int i = 0; i < 10; i++) {
		mt_gotoXY(2 + i, 2);
		for (int j = 0; j < 10; j++) {
			if (j != 0) {
				printf(" ");
			}
			printf("+%.4X", memory[i * 10 + j]);
		}
		printf("\n");
	}

	return 0;
}

int pa_printAccumulator()
{
	int accumulator = 9999;

	bc_box(1, BOX_COLUMN_MEMORY + 1, MINI_BOX_ROW, MINI_BOX_COLUMN);
	mt_gotoXY(1, 67);
	printf(" accumulator ");
	mt_gotoXY(2, 70);
	printf("+%d", accumulator);

	return 0;
}

int pa_printBoxInstructionCounter()
{
	bc_box(4, BOX_COLUMN_MEMORY + 1, MINI_BOX_ROW, MINI_BOX_COLUMN);
	return 0;
}

int pa_printInstructionCounter()
{
	// int instructionCounter = 0;

	mt_gotoXY(4, 63);
	printf(" instructionCounter ");
	mt_gotoXY(5, 70);
	printf("+%.4X", instructionCounter);

	return 0;
}

int pa_printOperation()
{
	bc_box(7, BOX_COLUMN_MEMORY + 1, MINI_BOX_ROW, MINI_BOX_COLUMN);
	mt_gotoXY(7, 68);
	printf(" Operation ");
	mt_gotoXY(8, 69);
	printf("+00 : 00");

	return 0;
}

int pa_printFlags()
{
	int value_p, value_o, value_m, value_t, value_e;

	sc_regGet(P, &value_p);
	sc_regGet(O, &value_o);
	sc_regGet(M, &value_m);
	sc_regGet(T, &value_t);
	sc_regGet(E, &value_e);

	bc_box(10, BOX_COLUMN_MEMORY + 1, MINI_BOX_ROW, MINI_BOX_COLUMN);
	mt_gotoXY(10, 69);
	printf(" Flags ");
	mt_gotoXY(11, 64);
	printf("P-%d O-%d M-%d T-%d E-%d", 
		value_p, value_o, value_m, value_t, value_e);

	return 0;
}

int pa_printBoxCase()
{
	int column = 46;
	int row = 10;
	bc_box(BOX_ROW_MEMORY + 1, 1, row, column);
	return 0;
}

int pa_printCase(int y, int x)
{
	bc_printbigchar(bcintp, BOX_ROW_MEMORY + 2, 2, purple, cyan);
	
	int value;
	int rank[4];
	sc_memoryGet(y * 10 + x, &value);

	for (int i = 0; i < 4; ++i) {
		rank[i] = value % 16;
		value /= 16;
	}

	for (int i = 38, j = 0; i >= 11; i -= 9, j++) {
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