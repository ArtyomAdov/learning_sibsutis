//Арифметический код
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int size_copy_array = 0, count_symbols_in_file = 0, index = 0, size_encoding_array = 0, count_compressed_symbols = 0;
long double *Q;

struct code {
    char symbol;
    long double p;
} array[128], *array_copy;

struct encoding {
    char block[15];
    char code[60];
} *encoding_array;

int file_size(const char *namefile){
    FILE *f = fopen(namefile, "rb");
    int size = 0;
    fseek(f, 0, 2);
    size = ftell(f);
    return size;
}

unsigned long long int bin_to_int(encoding zap) {
    unsigned long long int number = 0;
    for (int i = strlen(zap.code) - 1, p = 0; i >= 0; i--, p++) {
        number += (zap.code[i] - '0') * pow(2, p);
    }
    return number;
}

void compressor(const char *file_name) {
    FILE *output = fopen(file_name, "wb");
    int byte = 0;
    unsigned long long int code;
    int length;
    int bit = 7;
    for (int var_1 = 0; var_1 < index; var_1++) {
        code = bin_to_int(encoding_array[var_1]);
        length = strlen(encoding_array[var_1].code);
        for (int var_2 = length - 1; var_2 >= 0; --var_2) {
            if ((code >> var_2) & 1) {
                byte |= (1 << bit);
            }
            bit--;
            if (bit < 0) {
                putc(byte, output);
                byte = 0;
                bit = 7;
                count_compressed_symbols++;
            }
        }
    }
    putc(byte, output);
    count_compressed_symbols++;
    fclose(output);
}

/*void decompressor(const char *file_name) {
    FILE *compressed_text = fopen(file_name, "rb");
    FILE *decompressed_text = fopen("decompressed.txt", "wb");
    int bit = 0;
    char symbol_in_binary[60];
    char buffer_1[100];
    char buffer_2[100];
    memset(symbol_in_binary, '\0', 60);
    memset(buffer_1, '\0', 100);
    memset(buffer_2, '\0', 100);
    while (count_compressed_symbols > 0) {
        int symbol = getc(compressed_text);
        count_compressed_symbols--;
        to_binary_string(symbol_in_binary, symbol);
        strcat(buffer_1, symbol_in_binary);
        while (strlen(buffer_1) > 24) {
            bit++;
            strncpy(buffer_2, buffer_1, bit);
            for (int i = 0; i <= size_encoding_array; i++) {
                if (strcmp(buffer_2, encoding_array[i].code) == 0) {
                    fprintf(decompressed_text, "%s", encoding_array[i].block);
                    for (int k = bit; k <= strlen(buffer_1); k++) buffer_1[k - bit] = buffer_1[k];
                    bit = 0;
                    memset(buffer_2, '\0', 100);
                    break;
                }
            }
        }
    }
    fclose(compressed_text);
    fclose(decompressed_text);
}*/

long double* get_chances(FILE *&file) {
    int read = 0;
    while (fread(&read, sizeof(char), 1, file) == 1) {
        array[read].symbol = char(read);
        array[read].p++;
        count_symbols_in_file++;
    }
    for (int k = 0; k < 128; k++) {
        if (array[k].p != 0.0) {
            array[k].p /= count_symbols_in_file;
            size_copy_array++;
        }
    }
    array_copy = new code [size_copy_array];
    for (int p = 0, k = 0; k < 128; k++) {
        if (array[k].p != 0.0) {
            array_copy[p] = array[k];
            p++;
        }
    }
    Q = new long double [size_copy_array + 1];
    Q[0] = 0.0;
    for (int k = 1; k <= size_copy_array; k++) {
        Q[k] = Q[k - 1] + array_copy[k - 1].p;
    }
    return Q;
}

void arifmetic_decode(long double code, int length) {
    FILE *output = fopen("encoding_text.txt", "ab");
    long double lefts[length + 1];
    long double rights[length + 1];
    long double lens[length + 1];
    lefts[0] = 0;
    rights[0] = 1;
    lens[0] = 1;
    for (int j = 1; j <= length; j++) {
        int k = 0;
        for (k = 1; k <= size_copy_array; k++) {
            lefts[j] = lefts[j - 1] + lens[j - 1] * Q[k - 1];
            rights[j] = lefts[j - 1] + lens[j - 1] * Q[k];
            lens[j] = rights[j] - lefts[j];
            if (lefts[j] <= code && code < rights[j]) {
                break;
            }
        }
        putc(array_copy[k - 1].symbol, output);
    }
    fclose(output);
}

long double arifmetic_code(int byte, int difference) {
    int m = 0, read = 0, i = 0;
    char buffer[60];
    char block[15];
    char symbol = 0;
    memset(buffer, '\0', 60);
    memset(block, '\0', 15);
    FILE *input = fopen("source_text.txt", "rb");
    long double *Q = NULL;
    Q = get_chances(input);
    long double lefts[difference + 1];
    long double rights[difference + 1];
    long double lens[difference + 1];
    lefts[0] = 0;
    rights[0] = 1;
    lens[0] = 1;
    rewind(input);
    fseek(input, byte, 0);
    while (fread(&read, sizeof(char), 1, input) == 1) {
        for (int j = 0; j < size_copy_array; j++) {
            if (char(read) == array_copy[j].symbol) {
                m = j + 1;
                break;
            }
        }
        i++;
        lefts[i] = lefts[i - 1] + lens[i - 1] * Q[m - 1];
        rights[i] = lefts[i - 1] + lens[i - 1] * Q[m];
        lens[i] = rights[i] - lefts[i];
        symbol = char(read);
        block[strlen(block)] = symbol;
        if (i == difference) {
            long double result = lefts[i];
            long double copy_result = result;
            long double log = log2(lens[i]) * -1;
            long double digits = ceil(log);
            for (int p = 0; p < digits; p++) {
                copy_result *= 2;
                int digit = (int)copy_result;
                if (digit == 0) strcat(buffer, "0");
                if (digit == 1) strcat(buffer, "1");
                if (copy_result > 1) copy_result--;
            }
            strcpy(encoding_array[index].code, buffer);
            strcpy(encoding_array[index].block, block);
            index++;
            fclose(input);
            return result;
        }
    }
}

int main() {
    char name[6];
    int symbol = 49;
    memset(name, '\0', 6);
    name[0] = char(symbol);
    strcat(name, ".txt");
    int length_of_block = 0;
    int size_of_block = 0;
    int size_of_source_text = file_size("source_text.txt");
    for (int loop = 1; loop < 10; loop++) {
        length_of_block = loop;
        size_encoding_array = (size_of_source_text / length_of_block) + 1;
        encoding_array = new encoding[size_encoding_array];
        int dif = length_of_block;
        while (size_of_block < size_of_source_text) {
            if (size_of_source_text - size_of_block < length_of_block) dif = size_of_source_text - size_of_block;
            long double code = arifmetic_code(size_of_block, dif);
            size_copy_array = 0;
            count_symbols_in_file = 0;
            size_of_block += length_of_block;
        }
        compressor(name);
        index = 0;
        size_encoding_array = 0;
        count_compressed_symbols = 0;
        size_of_block = 0;
        int size_output = file_size(name);
        float ratio = ((float)size_output/(float)size_of_source_text) * 100;
        printf("Size of block: %d  Compression ratio: %f\n", loop, ratio);
        symbol++;
        name[0] = char(symbol);
        delete[] encoding_array;
        delete[] array_copy;
        delete[] Q;
    }
    system("pause");
}
