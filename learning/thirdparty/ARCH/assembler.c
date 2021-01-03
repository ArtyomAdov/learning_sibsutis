#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getCommand(char* cmd)
{
    if (!strcmp(cmd, "READ")) {
        return 0x10;
    }
    if (!strcmp(cmd, "WRITE")) {
        return 0x11;
    }
    if (!strcmp(cmd, "LOAD")) {
        return 0x20;
    }
    if (!strcmp(cmd, "STORE")) {
        return 0x21;
    }
    if (!strcmp(cmd, "ADD")) {
        return 0x30;
    }
    if (!strcmp(cmd, "SUB")) {
        return 0x31;
    }
    if (!strcmp(cmd, "DIVIDE")) {
        return 0x32;
    }
    if (!strcmp(cmd, "MUL")) {
        return 0x33;
    }
    if (!strcmp(cmd, "JUMP")) {
        return 0x40;
    }
    if (!strcmp(cmd, "JNEG")) {
        return 0x41;
    }
    if (!strcmp(cmd, "JZ")) {
        return 0x42;
    }
    if (!strcmp(cmd, "HALT")) {
        return 0x43;
    }
    if (!strcmp(cmd, "NOT")) {
        return 0x51;
    }
    return -1;
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        printf("Need two arguments: input.sa output.o\n");
        return -1;
    }

    char* p = strrchr(argv[1], '.');
    if (p == NULL || strlen(argv[1]) <= 3 || strcmp(p, ".sa") != 0) {
        printf(".SA FILE ERROR\n");
    }
    p = strrchr(argv[2], '.');
    if (p == NULL || strlen(argv[2]) <= 2 || strcmp(p, ".o") != 0) {
        printf(".O FILE ERROR\n");
    }
    FILE *input, *output;
    if ((input = fopen(argv[1], "r")) == NULL) {
        printf(".SA FILE ERROR");
    }
    if ((output = fopen(argv[2], "wb+")) == NULL) {
        printf(".O FILE ERROR");
    }
    while (!feof(input)) {
        int a, b;
        char str[10], in[3], out[10], s[1024];
        fgets(s, 1024, input);
        int check = sscanf(s, "%s %s %s ", in, str, out);
        if (check != 3 || strlen(in) != 2
            || !(strlen(out) == 2 || strlen(out) == 5)) {
            printf("ERROR WRONG INPUT %s %s %s \n", in, str, out);
            break;
        }
        int i;
        for (i = 0; i < strlen(in); i++) {
            if (!(in[i] >= '0' && in[i] <= '9')) {
                printf("ERROR FIRST ARGUMENT INPUT\n");
                break;
            }
        }
        a = atoi(in);
        b = atoi(out);
        int data[3];
        data[0] = a;
        data[1] = getCommand(str);
        data[2] = b;
        fwrite(data, sizeof(int) * 3, 1, output);
    }
    fclose(input);
    fclose(output);
    return 0;
}
