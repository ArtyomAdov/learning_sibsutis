#include "PrintAll.h"

#include <signal.h>
#include <sys/time.h>

#include "transGeomAdd.h"

/* Test lab */
int test_memory()
{
	int value;
	sc_memoryInit();
	sc_memorySet(4, 24);
	sc_memoryGet(5, &value);
	printf("%d\n", value);

	sc_memorySave("Test.bin");

	sc_regInit();
	sc_regFlagPrint();

	sc_regSet(O, 1);
	sc_regSet(P, 1);
	printf("Flag B and A: "); 
	sc_regFlagPrint();

	
	sc_regGet(O, &value);
	printf("Reg B %d\n", value);
	return 0;
}

int test_term()
{
	mt_clrscr();

	mt_gotoXY(10, 10);


	int *r = malloc(sizeof(int));
	int *c = malloc(sizeof(int));

	mt_getscreensize(r, c);
	printf("row = %d\tcol = %d\n", *r, *c);

	enum colors f = cyan;
	mt_ssetfgcolor(f);

	enum colors a = white;
	mt_ssetbgcolor(a);

	printf("Test\n");

	mt_stopcolor();

	return 0;
}

int test_bigchar()
{
	mt_clrscr();
	int a[2] = {1010315264, 3158064};
	int value;
	
	bc_box(10, 5, 8, 8);
	bc_printbigchar(a, 10, 5, purple, cyan);

	bc_setbigcharpos(a, 1, 4, 0);
	bc_setbigcharpos(a, 1, 3, 1);
	bc_printbigchar(a, 10, 15, purple, cyan);

	bc_getbigcharpos(a, 1, 4, &value);
	printf("Value = %d\n", value);

	
	int fd = open("BigChar.txt", O_WRONLY);
	int count = 0;

	int *big = malloc(sizeof(int) * 1);
	big[0] = 0;
	big[1] = 0;

	bc_bigcharwrite(fd, a, 1);
	close(fd);

	fd = open("BigChar.txt", O_RDONLY);
	bc_bigcharread(fd, big, 1, &count);
	printf("%d\n", big[0]);
	printf("%d\n", big[1]);
	printf("%d\n", count);
	close(fd);

	free(big);

	return 0;
}

int test_readkey()
{
	mt_clrscr();
	enum keys key;

	while (key != 0) {
		rk_readkey(&key);
		printf("%d\n", key);
	}
	
	return 0;
}

void sighandler(int signo)
{
	instructionCounter = -1;
}

int test_signal()
{
	int x = 0;
	int y = 0;
	int x_term = 6;
	int y_term = 2;

	instructionCounter = 0;

	enum keys key;

	pa_printAll(y, x, y_term, x_term);
	int valueFT;

	while (key != key_q) {
		rk_readkey(&key);

		signal(SIGUSR1, sighandler);

		if (key == key_s) {
			sc_memorySave("Test.bin");
		} else if (key == key_l) {
			sc_memoryLoad("Test.bin");
			pa_printMemory();
			mt_gotoXY(23, 1);
			fflush(stdout);
		} else if (key == key_up) {

			raise(SIGUSR1);

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

		sc_regGet(T, &valueFT);
		if (valueFT == 0) {
			instructionCounter++;
			pa_printInstructionCounter();
		}

		pa_resetBGColor(y, x, y_term, x_term);
		pa_printCase(y, x);

		mt_gotoXY(26, 1);

		fflush(stdout);
	}

	return 0;
}

int test_trans()
{
	tCHS chs;
	tCHS chs_geom;
	// tLARGE large;
	tLBA lba;
	// tIDECHS idechs;

	// 15704065 10018890
	lba = 15704065;
	printf("LBA: %d\n", lba);

	g_lba2chs(lba, &chs_geom);
	printf("CHS_GEOM: %d %d %d\n", chs_geom.c, chs_geom.h, chs_geom.s);

	a_lba2chs(chs_geom, lba, &chs);
	printf("CHS: %d %d %d\n", chs.c, chs.h, chs.s);
	printf("CHS_GEOM: %d %d %d\n", chs_geom.c, chs_geom.h, chs_geom.s);

	a_chs2lba(chs_geom, chs, &lba);
	printf("LBA: %d\n", lba);

	return 0;
}

/* */

int main()
{
	// test_memory();	// 2
	// test_term();		// 3
	// test_bigchar();	// 4
	// test_readkey();	// 5
	// test_signal();	// 6
	test_trans();	// 7

	// pa_ProgRun();
	return 0;
}
