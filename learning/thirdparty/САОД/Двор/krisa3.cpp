#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct spis {
    char ch;
    spis *next;
};

struct tle {
    spis *head;
    spis *tail;
};

void PrintSpis(spis *head) {
    spis *p;
    for(p = head; p; p = p->next)
        printf("%c ", p->ch);
    printf("\n\n");

}

int Hash_Insert_Line(int m, char *arr, char ch) {
    int i = 0, count = 0;
    while (i != m) {
        int j = (int(ch) + i) % m;
        if (arr[j] != 0) {
            count++;
        }
        if (arr[j] == ch) break;
        if (arr[j] == 0) {
            arr[j] = ch;
            break;
        }
        ++i;
    }
    return count;
}

int Hash_Insert_Quadra(int m, char *arr, char ch) {
    int count = 0;
    int h = int(ch) % m;
    int d = 1;
    while (1) {
        if (arr[h] != 0) {
            count++;
        }
        if (arr[h] = ch) {
            break;
        }
        if (arr[h] == 0) {
            arr[h] = ch;
            break;
        }
        if (d >= m) {
            break;
        }
        h = h + d;
        if (h >= m) h = h - m;
        d = d + 2;
    }
    return count;
}

int Hash_Search_Quadra(int m, char *array, char ch) {
    int h = int(ch) % m;
    int d = 1;
    while (1) {
        if (array[h] == ch) {
            printf("Key found = %c\n", ch);
            break;
        }
        if (array[h] == 0) {
            printf("Key not found\n");
            break;
        }
        if (d >= m) {
            break;
        }
        h = h + d;
        if (h >= m) h = h - m;
        d = d + 2;
    }
}

void Hash_Search(int m, char key, tle array[]) {
    int H;
    H = int(key) % m;
    spis *p = array[H].head;
    while (p) {
        if (p->ch == key) {
            printf("Key found = %c\n", p->ch);
            break;
        }
        p = p->next;
    }
    if (p == NULL) printf("Key not found\n");
}

int Hash_Search_Line(int m, char array[], char key) {
    int H;
    int i = 0;
    while (i != m) {
        H = int(key) % m;
        if (array[H] == key) {
            printf("Key found = %c\n", key);
            return H;
        }
        i++;
    }
    printf("Key not found\n");
}

void Hash_Spis(int m, char str[], tle array[]) {
    int H;
    for (int i = 0; i < m; ++i) {
        array[i].head = new spis;
        array[i].head->next = NULL;
        array[i].tail = array[i].head;
    }
    int length = strlen(str);
    for (int i = 0; i < length; ++i) {
        H = int(str[i]) % m;
        spis *p = new spis;
        p->ch = str[i];
        p->next = NULL;
        array[H].tail->next = p;
        array[H].tail = p;
    }
    for(int i = 0; i < m; ++i) {
        printf("Spis %d: ", i);
        PrintSpis(array[i].head->next);
    }
}

void Print_Hash_Line(int t, char *array, char string[]) {
    int length = strlen(string);
    for (int i = 0; i < length; ++i) {
        char ch = string[i];
        Hash_Insert_Line(t, array, ch);
    }
    printf("Number: ");
    for (int i = 0; i < t; ++i) {
        printf("%d  ", i);
    }
    printf("\n");
    printf("Symbol: ");
    for (int i = 0; i < t; ++i) {
        printf("%c  ", array[i]);
    }
    printf("\n");
}

void Print_Hash_Quadra(int t, char *array, char string[]) {
    int length = strlen(string);
    for (int i = 0; i < length; ++i) {
        char ch = string[i];
        Hash_Insert_Quadra(t, array, ch);
    }
    printf("Number: ");
    for (int i = 0; i < t; ++i) {
        printf("%d  ", i);
    }
    printf("\n");
    printf("Symbol: ");
    for (int i = 0; i < t; ++i) {
        printf("%c  ", array[i]);
    }
    printf("\n");
}

void Print_Table(int t, char *arr, char *arr_2, char *str) {
    int length = strlen(str);
    int S_1 = 0, S_2 = 0;
    length = strlen(str);
    printf("        %d                  ", t);
    printf("        %d             ", length);
    for (int n = 0; n < length; ++n) {
        char ch = str[n];
        int count_1 = Hash_Insert_Line(t, arr, ch);
        S_1 += count_1;
        int count_2 = Hash_Insert_Quadra(t, arr_2, ch);
        S_2 += count_2;
    }
    printf("                %d                    %d\n", S_1, S_2);
}

int main() {
    int t = 11;
    char array[t];
    char array_1[t];
    char st[] = "Sorting"; //Method of connection
    char string[] = "VLADIMIRPUTIN"; //Method of opened addressing
    char str = 'P'; //For search
    for (int i = 0; i < t; ++i) {
        array[i] = 0;
        array_1[i] = 0;
    }
    //Print_Hash_Line(t, array, string);
    //Hash_Search_Line(t, array, str);
    //Print_Hash_Quadra(t, array_1, string);
    //Hash_Search_Quadra(t, array_1, str);
    //
    tle arr[t];
    Hash_Spis(t, st, arr);
    Hash_Search(t, str, arr);
    //
    //
    printf("Size of hash-table         Count of origin symbols                  Count of collisions\n");
    printf("                                                             Linear probe        Quadratic probes\n\n");
    for (int i = 1; i <= 10; ++i) {
        Print_Table(i, array, array_1, string);
    }
    system("pause");
}
