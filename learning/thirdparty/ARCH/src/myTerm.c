#include "myTerm.h"
#include <stdio.h>

int mt_clrscr()
{
	printf("\E[H\E[J");
	return 0;
}

int mt_gotoXY(int y, int x)
{
	printf("\E[%d;%dH", y, x);
	return 0;
}

int mt_getscreensize(int *rows, int *cols)
{
	struct winsize ws;
	if (ioctl(1, TIOCGWINSZ, &ws)) {
		return 1;
	} else {
		*rows = ws.ws_row;
		*cols = ws.ws_col;
	}
	return 0;
}

int mt_setscreensize(int rows, int cols)
{
	printf("\E[8;%d;%d;t", cols, rows);
	return 0;
}

int mt_ssetfgcolor(enum colors color)
{
	printf("\E[3%dm", color);
	return 0;
}

int mt_ssetbgcolor(enum colors color)
{
	printf("\E[4%dm", color);
	return 0;
}

int mt_stopcolor()
{
	printf("\E[0m");
	return 0;
}
