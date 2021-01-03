#ifndef MYBIGCHARS_H
#define MYBIGCHARS_H

#include "myTerm.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define BC_ANGLE_LEFT_UP "l"
#define	BC_ANGLE_LEFT_DOWN "m"
#define	BC_ANGLE_RIGHT_UP "k"
#define	BC_ANGLE_RIGHT_DOWN "j"
#define	BC_LINE_VERTICAL "x"
#define	BC_LINE_HORIZONTAL "q"
#define	BC_CAGED_CELL "a"

int bc_printA(char* str);
int bc_box(int x1, int y1, int x2, int y2);
int bc_printbigchar(int a[2], int x, int y, enum colors f_color, enum colors b_color);
int bc_setbigcharpos(int *big, int x, int y, int value);
int bc_getbigcharpos(int *big, int x, int y, int *value);
int bc_bigcharwrite(int fd, int *big, int count);
int bc_bigcharread(int fd, int *big, int need_count, int *count);

#endif
