#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <graphics.h>
int Md = 0, M = 0, C = 0;

struct spis {
    spis *next;
    union {
        int num;
        unsigned char Digit[4];
    };
};

struct spis_surname {
    spis_surname *next;
    char str[10];
};

struct tle {
    spis *head;
    spis *tail;
};

struct tle_surname {
    spis_surname *head;
    spis_surname *tail;
};

int QuickSort(int *array, int L, int R) {
    int X = array[L], i = L, j = R;
    M++;
    while (i <= j) {
        C++;
        while (array[i] < X) {
            C++;
            i++;
        }
        C++;
        while (array[j] > X) {
            C++;
            j--;
        }
        if (i <= j) {
            int t = array[i];
            M++;
            array[i] = array[j];
            M++;
            array[j] = t;
            M++;
            i++;
            j--;
        }
    }
    if (L < j) QuickSort(array, L, j);
    if (i < R) QuickSort(array, i, R);
    return M+C;
}

int DigitalSort_up(spis* &S, int L) {
    int j, i, d;
    spis *p;
    tle Q[256];
    for (j = 0; j < L; j++) {
        for (i = 0; i < 256; i++) {
            Q[i].tail = (spis *) &Q[i].head;
        }
        p = S;
        while (p) {
            d = int(p->Digit[j]);
            printf("%c ",p->Digit[j]);
            Q[d].tail->next = p;
            Q[d].tail = p;
            p = p->next;
            Md++;
            Md++;
        }
        p = (spis*) &S;
        for (i = 0; i < 256; i++) {
            if (Q[i].tail != (spis *) &Q[i].head) {
                p->next = Q[i].head;
                p = Q[i].tail;
                Md++;
                Md++;
            }
        }
        p->next = NULL;
    }
    return Md;
}

void DigitalSort_up_surname(spis_surname* &S) {
    int j, i, d;
    spis_surname *p;
    tle_surname Q[124];
    for (j = 0; j <= 2; ++j) {
        for (i = 65; i < 123; i++) {
            Q[i].tail = (spis_surname *) &Q[i].head;
        }
        p = S;
        while (p) {
            d = p->str[j];
            Q[d].tail->next = p;
            Q[d].tail = p;
            p = p->next;
        }
        p = (spis_surname *) &S;
        for (i = 65; i < 123; i++) {
            if (Q[i].tail != (spis_surname *) &Q[i].head) {
                p->next = Q[i].head;
                p = Q[i].tail;
            }
        }
        p->next = NULL;
    }
}

void DigitalSort_down(spis *&S, int L) {
    int j, i, d;
    spis *p;
    tle Q[256];
    for (j = 0; j < L; j++) {
        for (i = 255; i >= 0; i--) {
            Q[i].tail = (spis *) &Q[i].head;
        }
        p = S;
        while (p) {
            d = p->Digit[j];
            Q[d].tail->next = p;
            Q[d].tail = p;
            p = p->next;
        }
        p = (spis*) &S;
        for (i = 255; i >= 0; i--) {
            if (Q[i].tail != (spis *) &Q[i].head) {
                p->next = Q[i].head;
                p = Q[i].tail;
            }
        }
        p->next = NULL;
    }
}

void PrintSpis_surname(spis_surname *head) {
    spis_surname *p;
    printf("\n");
    for(p = head; p; p = p->next) printf("%s ", p->str);
    printf("\n\n");
}

void PrintSpis(spis *head) {
    spis *p;
    printf("\n");
    for(p = head; p; p = p->next) printf("%d ", p->num);
    printf("\n\n");
}

spis *Spis_rand(int n) {
    int i;
    spis *p = NULL, *head = NULL;
    for(i = 0; i < n; i++) {
        p = new spis;
        p->num = (rand()%100000)+990000;
        p->next = head;
        head = p;
    }
    return head;
}

spis_surname *Spis_surname(int n) {
    int i;
    spis_surname *p = NULL, *head = NULL;
    printf("Enter surname: \n");
    for(i = 0; i < n; i++) {
        p = new spis_surname;
        scanf("%s", p->str);
        p->next = head;
        head = p;
    }
    return head;
}

int Sum(spis *head) {
    int S = 0;
    spis *p;
    for(p = head; p; p = p->next) {
        S += p->num; }
    return S;
}

int Series(spis *head) {
    int S = 0;
    spis *p;
    for(p = head; p->next; p = p->next) {
        if (p->num > p->next->num) S++; }
    return S + 1;
}

int main() {
    initwindow(100,100);
    srand(time(0));
    int L, n, m, flag, k;
    spis *p;
    spis_surname *q;
    printf("1 - Digital Sort by numbers\n");
    printf("2 - Digital Sort by surnames");
    flag = getch();
    switch (flag) {
        case 49: {
            int array[30];
            for (int p = 0; p < 30; p++) array[p] = (rand()%10000)+1000;
            k = QuickSort(array, 0, 29);
            system("cls");
            printf("Enter size of spis: ");
            scanf("%d", &n);
            printf("Enter size of number: 2 bytes or 4 bytes ");
            scanf("%d", &L);
            printf("\n");
            if (L != 2 && L != 4) {
                printf("\n\nError!");
                return 0;
            }
            p = Spis_rand(n);
            printf("Origin spis: ");
            PrintSpis(p);
            printf("Ascending sorted spis: ");
            m = DigitalSort_up(p, L);
            PrintSpis(p);
            printf("Check sum: %d, Series: %d", Sum(p), Series(p));
            printf("\n\n");
            p = Spis_rand(n);
            printf("Origin spis: ");
            PrintSpis(p);
            printf("Descending sorted spis: ");
            DigitalSort_down(p, L);
            PrintSpis(p);
            printf("Check sum: %d, Series: %d", Sum(p), Series(p));
            printf("\n\n");
            printf("%d Digital %d Quick", m, k);
            system("pause");
        } break;
        case 50: {
            system("cls");
            printf("Enter number of surname: ");
            scanf("%d", &m);
            system("cls");
            q = Spis_surname(m);
            PrintSpis_surname(q);
            DigitalSort_up_surname(q);
            PrintSpis_surname(q);
            system("pause");
        } break;
    }
}
