//Кодирование целых чисел
#include <iostream>
#include <string.h>

const int n = 101;

int bits(char *st) {
    int count = 0;
    for (int i = 0; i < strlen(st); i++) count++;
    return count;
}

void to_binary_string(char *string, int n) {
    int i = 0;
    do {
        string[i] = (n % 2) + '0';
        n = n / 2;
        i++;
    } while (n > 0);
    string[i] = 0;
    strrev(string);
}

void fix_var(int exp, char *string, char *result) {
    int count = 0;
    for (int i = 0; i < strlen(string); i++) {
        if (string[0] == '0') break;
        count++;
    }
    to_binary_string(result, count);
    size_t dif = exp - strlen(result);
    char success_string[15];
    memset(success_string, '\0', 15);
    for (int k = 0; k < dif; k++) success_string[k] = '0';
    for (size_t k = dif, i = 0; k < exp; k++, i++) success_string[k] = result[i];
    for (size_t k = strlen(success_string), i = 1; i < count; k++, i++) success_string[k] = string[i];
    success_string[strlen(success_string)] = 0;
    strcpy(result, success_string);
}

void gamma_code(char *string, char *result) {
    for (int i = 0; i < strlen(string); i++) {
        if (string[0] == '0') return;
        else {
            if (i < strlen(string) - 1) result[i] = '0';
        }
    }
    strcat(result, string);
}

void omega_code(char *string, char *result) {
    int count = 0;
    int n = 5;
    int k = n;
    char **groups = new char *[n];
    for (int i = 0; i < n; i++) {
        groups[i] = new char [8];
        memset(groups[i], '\0', 8);
    }
    if (string[0] == '0') return;
    if (strcmp(string, "1") == 0) {
        result[0] = '0';
        return;
    }
    groups[n - 1] = string;
    while (n > 1) {
        count = bits(groups[n - 1]);
        if (count == 2) break;
        count--;
        to_binary_string(groups[n - 2], count);
        n--;
    }
    for (int i = 0; i < k; i++) {
        if (strlen(groups[i]) != 0) strcat(result, groups[i]);
    }
    result[strlen(result)] = '0';
}

int main() {
    char **string = new char *[n];
    char **result = new char *[n];
    for (int i = 0; i < n; i++) {
        string[i] = new char [15];
        result[i] = new char [15];
        memset(string[i], '\0', 15);
        memset(result[i], '\0', 15);
    }
    int exp = 4;
    printf("         fix+var        gamma-code      omega-code\n\n");
    for (int i = 0; i < n; i++) {
        to_binary_string(string[i], i);
        fix_var(exp, string[i], result[i]);
        printf("n = %3d  ", i);
        for (int j = 0; j < strlen(result[i]); j++) printf("%c", result[i][j]);
        printf("    \t");
        for (int k = 0; k < n; k++) memset(result[k], '\0', 15);
        gamma_code(string[i], result[i]);
        for (int j = 0; j < strlen(result[i]); j++) printf("%c", result[i][j]);
        printf("       \t");
        for (int k = 0; k < n; k++) memset(result[k], '\0', 15);
        omega_code(string[i], result[i]);
        for (int j = 0; j < strlen(result[i]); j++) printf("%c", result[i][j]);
        printf("\n");
    }
    //free(string);
    //free(result);
    system("pause");
}
