//RLE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int zero = 0;

void to_binary_string(char *string, size_t n) {
    string[0] = 0;
    int i = 0;
    do {
        string[i] = (n % 2) + '0';
        n = n / 2;
        i++;
    } while (n > 0);
    string[i] = 0;
    strrev(string);
}

void fix_var(int number, int exp, char *string, char *result) {
    to_binary_string(string, number);
    if (strcmp(string, "0") == 0) {
        for (int k = 0; k < exp; k++) result[k] = '0';
        return;
    }
    char temp[4];
    to_binary_string(temp, strlen(string));
    size_t difference = exp - strlen(temp);
    for (int k = 0; k < difference; k++) result[k] = '0';
    for (size_t k = difference, i = 0; k < exp; k++, i++) result[k] = temp[i];
    for (size_t k = strlen(result), i = 1; i < strlen(string); k++, i++) result[k] = string[i];
    size_t len = strlen(result);
    result[len] = 0;
}

void gamma_code(int number, char *string, char *result) {
    to_binary_string(string, number);
    if (strcmp(string, "0") == 0) return;
    for (int i = 0; i < strlen(string) - 1; i++) result[i] = '0';
    strcat(result, string);
}

void omega_code(int number, char *string, char *result) {
    to_binary_string(string, number);
    if (strcmp(string, "0") == 0) return;
    if (strcmp(string, "1") == 0) {
        result[0] = '0';
        return;
    }
    int n = 0;
    size_t length = strlen(string);
    while (length > 1)  {
        length--;
        n++;
    }
    size_t count = 0;
    int k = n;
    char **groups;
	groups = new char *[n];
    for (int i = 0; i < n; i++) {
        groups[i] = new char [20];
        memset(groups[i], '\0', 20);
    }
    groups[n - 1] = string;
    while (n > 1) {
        count = strlen(groups[n - 1]);
        if (count == 2) break;
        count--;
        to_binary_string(groups[n - 2], count);
        n--;
    }
    for (int i = 0; i < k; i++) strcat(result, groups[i]);
    result[strlen(result)] = '0';
}

void create_source_file(FILE *source, int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        if (rand() % 3 == 1) fprintf(source, "%c", '1');
        else {
            fprintf(source, "%c", '0');
            zero++;
        }
    }
}

void rle_series(FILE* source, int *array_of_series, const char *code) {
    int count = 0, index = 0;
    char ch;
    rewind(source);
    while (!feof(source)) {
        ch = fgetc(source);
        if (ch == '0') count++;
        else {
            if (strcmp(code, "omega") == 0 || strcmp(code, "gamma") == 0) {
                array_of_series[index] = count + 1;
            }
            else {
                array_of_series[index] = count;
            }
            count = 0;
            index++;
        }
    }
}

void rle_encoding(int *array_of_series, const char *code) {
    FILE *file_fix_var = fopen("result_fix_var.txt", "a");
    FILE *file_gamma = fopen("result_gamma.txt", "a");
    FILE *file_omega = fopen("result_omega.txt", "a");
    char bin_string[50];
    char result_string[50];
    int count_of_elements = 0;
    memset(bin_string, '\0', 50);
    memset(result_string, '\0', 50);
    for (int k = 0; k < 500; k++) {
        if (array_of_series[k] != 1000) count_of_elements++;
        else break;
    }
    for (int i = 0; i < count_of_elements; i++) {
        int temp = array_of_series[i];
        if (strcmp(code, "fix_var") == 0) {
            fix_var(temp, 4, bin_string, result_string);
            fprintf(file_fix_var, "%s", result_string);
        }
        if (strcmp(code, "gamma") == 0) {
            gamma_code(temp, bin_string, result_string);
            fprintf(file_gamma, "%s", result_string);
        }
        if (strcmp(code, "omega") == 0) {
            omega_code(temp, bin_string, result_string);
            fprintf(file_omega, "%s", result_string);

        }
		memset(bin_string, '\0', 50);
		memset(result_string, '\0', 50);
    }
    fclose(file_fix_var);
    fclose(file_gamma);
    fclose(file_omega);
}

int size_file(const char *name_file) {
    FILE *f = fopen(name_file, "r");
    int size = 0;
    fseek(f, 0, 2);
    size = ftell(f);
    return size;
}

int main() {
    int *array_series;
	array_series = new int [500];
    for (int i = 0; i < 500; i++) array_series[i] = 1000;
    int exp = 4;
    FILE *file;
    file = fopen("source.txt", "w");
    int size = 1024;
    create_source_file(file, size);
    fclose(file);
    file = fopen("source.txt", "r");
    rle_series(file, array_series, "fix_var");
    rle_encoding(array_series, "fix_var");
    for (int i = 0; i < 500; i++) array_series[i] = 1000;
    rle_series(file, array_series, "gamma");
    rle_encoding(array_series, "gamma");
    for (int i = 0; i < 500; i++) array_series[i] = 1000;
    rle_series(file, array_series, "omega");
    rle_encoding(array_series, "omega");
    fclose(file);
    float size_source = size_file("source.txt");
    float size_fix_var = size_file("result_fix_var.txt");
    float size_gamma = size_file("result_gamma.txt");
    float size_omega = size_file("result_omega.txt");
    printf("Chance: %f\n\n", (float)zero/size);
    printf("compression ratio for fix+var: %2.2f \n\n", (size_source/size_fix_var));
    printf("compression ratio for gamma_code: %2.2f \n\n", (size_source/size_gamma));
    printf("compression ratio for omega_code: %2.2f \n\n", (size_source/size_omega));
    system("pause");
}
