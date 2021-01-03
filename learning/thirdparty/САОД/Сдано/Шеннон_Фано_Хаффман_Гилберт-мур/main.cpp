//Фано.Шеннон.Гилберт-Мур.Хаффман
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <string.h>

struct coding {
    char symbol;
    float chance;
    char code[20];
    int length;
} array_code[128];

int BubbleSort_for_chance(coding *a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j > i; j--) {
            if (a[j].chance != (float)0) {
                if (a[j].chance > a[j - 1].chance) {
                    coding t = a[j];
                    a[j] = a[j - 1];
                    a[j - 1] = t;
                }
            }
        }
    }
}

int BubbleSort_for_symbols(coding *a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j > i; j--) {
            if (a[j].symbol != 2) {
                if ((int)a[j].symbol < (int)a[j - 1].symbol) {
                    coding t = a[j];
                    a[j] = a[j - 1];
                    a[j - 1] = t;
                }
            }
        }
    }
}

void Shennon(int size) {
    float Q[size];
    Q[0] = 0;
    array_code[0].length = (int)ceilf(-log2f(array_code[0].chance));
    for (int i = 1; i < size; i++) {
        Q[i] = Q[i - 1] + array_code[i - 1].chance;//
        array_code[i].length = (int)ceilf(-log2f(array_code[i].chance));
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < array_code[i].length; j++) {
            Q[i] *= 2;
            int dig = (int)Q[i];
            if (dig == 0) array_code[i].code[j] = '0';
            if (dig == 1) array_code[i].code[j] = '1';
            if (Q[i] > 1)Q[i]--;
        }
    }
}

int mediana(int L, int R) {
    float chance = 0, sum = 0;
    int i = 0;
    for (i = L; i < R; i++) chance += array_code[i].chance;
    for (i = L; i < R; i++) {
        if ((sum < chance / 2) && (sum + array_code[i].chance > chance / 2)) break;
        sum += array_code[i].chance;
    }
    return i;
}

int med(int L, int R) {
    float Sl = 0;
    for (int i = L; i < R; i++) Sl += array_code[i].chance;
    float Sr = array_code[R].chance;
    int m = R;
    while (Sl >= Sr) {
        m--;
        Sl -= array_code[m].chance;
        Sr += array_code[m].chance;
    }
    return m;
}

void Fano(int L, int R, int k) {
    if (L < R) {
        k++;
        int m = med(L, R);
        for (int i = L; i <= R; i++) {
            if (i <= m) {
                array_code[i].code[k] = '0';
                array_code[i].length++;
            }
            else {
                array_code[i].code[k] = '1';
                array_code[i].length++;
            }
        }
        Fano(L, m, k);
        Fano(m + 1, R, k);
    }
}

int up(int n, float q, float *array) { //находит в array место, куда вставить число q и вставляет его
    int i = 0, j = 0;                 //сдвигая вниз остальные элементы 
    for (i = n - 2; i >= 1; i--) {
        if (array[i - 1] < q) array[i] = array[i - 1];
        else {
            j = i;
            break;
        }
        if ((i - 1) == 0 && array_code[i - 1].chance < q) {
            j = 0;
            break;
        }
    }
    array[j] = q;
    return j;
}

void down(int n, int j) {//формирует кодовое слово
    char pref[20];
    for (int i = 0; i < 20; i++) pref[i] = array_code[j].code[i];
    int l = array_code[j].length;
    for (int i = j; i < n - 2; i++) {
        for (int k = 0; k < 20; k++) 
		array_code[i].code[k] = array_code[i + 1].code[k];
        array_code[i].length = array_code[i + 1].length;
    }
    for (int i = 0; i < 20; i++) {
        array_code[n - 2].code[i] = pref[i];
        array_code[n - 1].code[i] = pref[i];
    }
    array_code[n - 1].code[l] = '1';
    array_code[n - 2].code[l] = '0';
    array_code[n - 1].length = l + 1;
    array_code[n - 2].length = l + 1;
}

void huffman(int n, float *array) {
    if (n == 2) {
        array_code[0].code[0] = '0';
        array_code[0].length = 1;
        array_code[1].code[0] = '1';
        array_code[1].length = 1;
    }
    else {
        float q = array[n - 2] + array[n - 1];
        int j = up(n, q, array); //поиск и вставка суммы 
        huffman(n - 1, array);
        down(n, j); //достраиваем код 
    }
}

void gilbert_mur(int size) {
    float Q[size], sum = 0;
    char ch;
    Q[0] = array_code[0].chance / 2; array_code[0].length = (int)ceilf(-log2f(array_code[0].chance)) + 1;
    sum = array_code[0].chance;
    for (int i = 1; i < size; i++) {
        Q[i] = sum + array_code[i].chance / 2;
        array_code[i].length = (int)ceilf(-log2f(array_code[i].chance)) + 1; //используем соотношение
        sum += array_code[i].chance;
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < array_code[i].length; j++) {
            Q[i] *= 2; //формирование кодового слова в двоичном виде
            int digit = (int)Q[i];
            if (digit == 0) ch = '0';
            if (digit == 1) ch = '1';
            array_code[i].code[j] = ch;
            if (Q[i] > 1) Q[i]--;
        }
    }
}

void print_table(int size) {
    printf("Symbol      Chance       Code word          Length of code word\n");
    for (int i = 0; i < size; i++) {
        printf("  %c", array_code[i].symbol);
        printf("        ");
        printf("%f", array_code[i].chance);
        printf("        ");
        printf("%s\t\t", array_code[i].code);
        printf("        ");
        printf("%d\n", array_code[i].length);
    }
    float entropy = 0, average_length = 0;
    for (int i = 0; i < size; i++) {
        average_length += (float)array_code[i].length * array_code[i].chance;
        entropy += array_code[i].chance * -log2f(array_code[i].chance);
    }
    printf("\n\nAverage length of code word: %1.2f\n", average_length);
    printf("Entropy of source file: %1.2f\n\n", entropy);
}

int main() {
    char ch;
    int count = 0;
    int size = 0;
    FILE *file = fopen("text.txt", "r");
    for (int i = 0; i < 128; i++) {
        array_code[i].symbol = 2;
        array_code[i].chance = 0;
        array_code[i].length = 0;
    }
    while (!feof(file)) {
        fscanf(file, "%c", &ch);
        array_code[ch].symbol = ch;
        array_code[ch].chance += 1;
        count++;
    }
    fclose(file);
    for (int i = 0; i < 128; i++) {
        if (array_code[i].chance != (float)0) {
            array_code[i].chance /= (float)count;
            size++;
        }
    }
    BubbleSort_for_chance(array_code, 128);
    Shennon(size);
    printf("Shennon");
    print_table(size);
    for (int i = 0; i < size; i++) {
        memset(array_code[i].code, '\0', 20);
        array_code[i].length = 0;
    }
    #if 0
    printf("Fano");
    Fano(0, size - 1, -1);
    print_table(size);
    for (int i = 0; i < size; i++) {
        memset(array_code[i].code, '\0', 20);
        array_code[i].length = 0;
    }
    printf("Huffman");
    float chance_1[size];
    for (int i = 0; i < size; i++) chance_1[i] = array_code[i].chance;
    huffman(size, chance_1);
    print_table(size);
    for (int i = 0; i < size; i++) {
        memset(array_code[i].code, '\0', 20);
        array_code[i].length = 0;
    }
    printf("Gilbert-Mur");
    BubbleSort_for_symbols(array_code, 128);
    gilbert_mur(size);
    print_table(size);
    #endif
    system("pause");
}
