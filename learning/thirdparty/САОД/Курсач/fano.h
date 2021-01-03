#include <cmath>
#include <iomanip>
#include <iostream>
#define FANO_H

unsigned long int number;
float entropy;
float averageLength;

struct codeStruct {
    unsigned char a;
    float p;
    char codeWord[50];
    int l;
} codeArray[n];


void openFile() {
    int i, j = 0;
    unsigned char ch;
    FILE *f = fopen("testBase1.dat", "rb");
    for (i = 0; i < n; i++) {
        codeArray[i].a = i;
        codeArray[i].p = (float)(0);
        codeArray[i].l = 0;
    }
    while (!feof(f)) {
        fscanf(f, "%c", &ch);
        codeArray[ch].p += 1.0;
        number++;
    }
    fclose(f);
    for (i = 0; i < n; i++)
        if (codeArray[i].p != (float)(0)) {
            codeArray[i].p /= (float)number;
            j++;
        }
    number = (unsigned long int)(j);
}

void deleteBlank() {
    unsigned int i, k;
    int j;
    codeStruct temp;
    for (i = 0; i < n - 1; i++) {
        k = 1;
        if (codeArray[i].p == (float)(0))
            for (j = i + 1; j < n; j++)
                if (k)
                    if (codeArray[j].p != (float)(0)) {
                        temp = codeArray[i];
                        codeArray[i] = codeArray[j];
                        codeArray[j] = temp;
                        k = 0;
                    }
    }
    i = 0;
    while (codeArray[i].p != 0.0) i++;
    number = (unsigned long int)(i);
    for (i = 0; i < number; ++i)
        for (j = 1; j < number; ++j) {
            if (codeArray[j].p > codeArray[j-1].p) {
                temp = codeArray[j-1];
                codeArray[j-1] = codeArray[j];
                codeArray[j] = temp;
            }
        }
}

int Med(int L, int R) {
    float Sl = 0;
    for (int i = L; i < R; i++) {
        Sl += codeArray[i].p;
    }
    float Sr = codeArray[R].p;
    int m = R;
    while (fabs(Sr - Sl)>fabs(Sr + codeArray[m-1].p - (Sl - codeArray[m-1].p))) {
        m--;
        Sl -= codeArray[m].p;
        Sr += codeArray[m].p;
    }
    return m - 1;
}

int FanoCoding(unsigned int L, unsigned int R, int k) {
    unsigned int m = 0;
    if (L < R) {
        k = k + 1;
        m = Med(L, R);
        for (unsigned int i = L; i <= R; i++) {
            if (i < m) {
                codeArray[i].codeWord[k] = '0';
                codeArray[i].l += 1;
            } else {
                codeArray[i].codeWord[k] = '1';
                codeArray[i].l += 1;
            }
        }
        FanoCoding(L, m, k);
        FanoCoding(m + 1, R, k);
    }
    return 0;
}


void codePrint() {
    system("cls");
    int j;
    unsigned i;
    float check = 0;
    for (i = 0; i < number; i++) {
        entropy += -codeArray[i].p * log(codeArray[i].p) / log(2);
        averageLength += codeArray[i].l * codeArray[i].p;
    }

    for (i = 0; i < number; i++) {
        std::cout.precision(6);
        std::cout.setf(std::ios::fixed);
        std::cout << std::setw(1) << (char)codeArray[i].a << " "
                  << (float)codeArray[i].p << " " << std::setw(2)
                  << (int)codeArray[i].l << " ";
        for (j = 0; j < codeArray[i].l; ++j)
            std::cout << (char)codeArray[i].codeWord[j];
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::setw(8) << entropy << " - Entropy" << std::endl;
    std::cout << std::setw(8) << averageLength << " - Average length"
              << std::endl;
    std::cout << std::setw(8) << entropy + 1 << " > " << averageLength
              << std::endl
              << std::endl;
    for (unsigned int i = 0; i < number; ++i) check += (float)codeArray[i].p;
    std::cout << "Sum of all chances: " << check << std::endl
              << std::endl;
    std::cout << "Press any key to return..." << std::endl;
    _getch();
}

void Fano() {
    number = 0;
    entropy = (float)(0);
    averageLength = (float)(0);
    openFile();
    deleteBlank();
    FanoCoding(0, number, -1);
    codePrint();
}
