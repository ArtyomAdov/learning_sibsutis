#include "myBigChars.h"

int bc_printA(char* str)
{
    printf("\E(0%s\E(B", str);
    return 0;
}

int bc_box(int x1, int y1, int x2, int y2)
{
    if (x1 < 0 || y1 < 0) {
        return -1;
    }
    mt_gotoXY(x1, y1);
    bc_printA(BC_ANGLE_LEFT_UP);
    for (int i = y1 + 1; i < y1 + y2 - 1; i++) {
        mt_gotoXY(x1, i);
        bc_printA(BC_LINE_HORIZONTAL);
    }
    bc_printA(BC_ANGLE_RIGHT_UP);
    for (int i = x1 + 1; i < x1 + x2 - 1; i++) {
        mt_gotoXY(i, y1);
        bc_printA(BC_LINE_VERTICAL);
    }
    mt_gotoXY(x1 + x2 - 1, y1);
    bc_printA(BC_ANGLE_LEFT_DOWN);
    for (int i = x1 + 1; i < x1 + x2 - 1; i++) {
        mt_gotoXY(i, y1 + y2 - 1);
        bc_printA(BC_LINE_VERTICAL);
    }
    for (int i = y1 + 1; i < y1 + y2 - 1; i++) {
        mt_gotoXY(x1 + x2 - 1, i);
        bc_printA(BC_LINE_HORIZONTAL);
    }
    bc_printA(BC_ANGLE_RIGHT_DOWN);
    printf("\n");
    return 0;
}

int bc_printbigchar(
        int a[2], int x, int y, enum colors f_color, enum colors b_color)
{
    if (x < 0 || y < 0) {
        return -1;
    }
    char str[8] = {0};
    mt_ssetfgcolor(f_color);
    mt_ssetbgcolor(b_color);
    for (int i = 0; i < 2; i++) {
        int a_buf = a[i];
        for (int j = 0; j < 4; j++) {
            int buf;
            a_buf = a[i] >> (j * 8);
            buf = a_buf & 0xFF;
            for (int k = 0; k < 8; k++) {
                int buf_bit = (buf & (1 << k)) >> k;
                if (buf_bit != 0) {
                    str[k] = BC_CAGED_CELL[0];
                } else {
                    str[k] = ' ';
                }
            }
            mt_gotoXY(x + (i * 4) + j, y);
            bc_printA(str);
        }
    }
    mt_stopcolor();
    mt_gotoXY(18, 0);
    return 0;
}

int bc_setbigcharpos(int* big, int x, int y, int value)
{
    if (x < 0 || x > 7 || y < 0 || y > 7 || value > 1 || value < 0) {
        return -1;
    }
    int ind = 0;
    if (x > 3) {
        ind = 1;
    }
    if (value == 1) {
        big[ind] |= 1 << (x * 8 + y);
    } else if (value == 0) {
        big[ind] &= ~(1 << (x * 8 + y));
    }
    return 0;
}

int bc_getbigcharpos(int* big, int x, int y, int* value)
{
    if (x < 0 || x > 7 || y < 0 || y > 7) {
        return -1;
    }
    int ind = 0;
    if (x > 3) {
        ind = 1;
    }
    *value = ((big[ind] >> (x * 8)) >> y) & 1;
    return 0;
}

int bc_bigcharwrite(int fd, int* big, int count)
{
    if (!big || fd < 0) {
        return -1;
    }
    while (count > 0) {
        int result;
        if ((result = write(fd, big, sizeof(int) * 2)) == -1) {
            return -1;
        }
        count--;
    }
    return 0;
}

int bc_bigcharread(int fd, int* big, int need_count, int* count)
{
    if (fd < 0) {
        return -1;
    }
    while (need_count > 0) {
        int result;
        if ((result = read(fd, big, sizeof(int) * 2)) == -1) {
            return -1;
        }
        need_count--;
        *count = *count + 1;
    }
    return 0;
}
