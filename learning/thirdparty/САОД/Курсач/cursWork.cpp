/*
     �������p��������� ���� ������ "����� ������������� �����"

     ��p����p� ������:
        ����p:          ��������� ���� 12 ��������
                        ��p��� <�������>_<�����>_<�����>
        ��������:       ��������� ���� 32 �������
                        ��p��� <���>_<��������>_<�������>
        ������������:   ��������� ���� 16 ��������
        ��� �������:    ����� �����
        ���-�� ��p����: ����� �����

     �p���p ������ �� ��:
        ��������_�_�
        ���_H���������_�������_________
        �������_���p���_
        1963
        864
    B = 1         (���� testBase1.dat)
    C = 2 - �� ���� ������� � ����p�, � = ��� �������;
    S = 4   ���p���� ��p��p����
    D = 2   �������� �-������
    E = 3   ��� ����
*/
const int N = 4000;
const int ESCAPE = 27;
const int n = 256;
int HR = 1;
int VR = 1;

#include <cstdio>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <cmath>
#include "fano.h"

using namespace std;

struct bookNote
{
    char author[12];
    char title[32];
    char publisher[16];
    short int year;
    short int pages;
};

struct queue
{
    bookNote *data;
    queue *next;
} * btree[1000];

struct tree
{
    bookNote *data;
    int bal;
    tree *left;
    tree *right;
} * root;

void print(struct bookNote **inx, int startNumber)
{
    int key;
    system("CLS");
    for (int i = startNumber; i < startNumber + 20; ++i)
    {
        cout << setw(4) << i + 1 << " " << setw(12) << inx[i]->author
             << " " << setw(32) << inx[i]->title << " "
             << setw(16) << inx[i]->publisher << " "
             << setw(4) << inx[i]->year << " " << setw(4)
             << inx[i]->pages << endl;
    }
    if (startNumber + 20 == N)
    {
        cout << endl
             << "End of DB. Press any key to return to menu";
        _getch();
        return;
    }
    cout << "\nPress ESC to exit" << endl
         << "OR press any key except ESC to print 20 more elements"
         << endl;
    key = _getch();
    if (key == ESCAPE)
    {
        key = 0;
        return;
    }
    print(inx, startNumber + 20);
}

void B2INSERT(bookNote *D, tree *&p)
{
    tree *q;
    if (p == NULL)
    {
        p = new tree;
        q = new tree;
        q = NULL;
        p->data = D;
        p->left = p->right = NULL;
        p->bal;
        VR = 1;
    }
    else if (p->data->pages > D->pages)
    {
        B2INSERT(D, p->left);
        if (VR == 1)
            if (p->bal == 0)
            {
                q = p->left;
                p->left = q->right;
                q->right = p;
                p = q;
                q->bal = 1;
                VR = 0;
                HR = 1;
            }
            else
            {
                p->bal = 0;
                VR = 1;
                HR = 0;
            }
        else
            HR = 0;
    }
    else if (p->data->pages <= D->pages)
    {
        B2INSERT(D, p->right);
        if (VR == 1)
        {
            p->bal = 1;
            HR = 1;
            VR = 0;
        }
        else if (HR == 1)
            if (p->bal == 1)
            {
                q = p->right;
                p->bal = 0;
                q->bal = 0;
                p->right = q->left;
                q->left = p;
                p = q;
                VR = 1;
                HR = 0;
            }
            else
                HR = 0;
    }
}

void treeSearch(tree *p, int key)
{
    if (p == NULL)
        return;
    while (p != NULL)
    {
        if (key < p->data->pages || key <= p->data->pages)
        {
            if (key == p->data->pages)
            {
                cout << " " << setw(12) << p->data->author
                     << " " << setw(32) << p->data->title << " "
                     << setw(16) << p->data->publisher << " "
                     << setw(4) << p->data->year << " " << setw(4)
                     << p->data->pages << endl;
            }
            p = p->left;
        }

        else if (key > p->data->pages || key >= p->data->pages)
        {
            if (key == p->data->pages)
            {
                cout << " " << setw(12) << p->data->author
                     << " " << setw(32) << p->data->title << " "
                     << setw(16) << p->data->publisher << " "
                     << setw(4) << p->data->year << " " << setw(4)
                     << p->data->pages << endl;
            }
            p = p->right;
        }
    }
}

void printTree(tree *p)
{
    static int i;
    if (p == NULL)
        return;
    printTree(p->left);
    cout << setw(4) << ++i << setw(12) << p->data->author
         << " " << setw(32) << p->data->title << " "
         << setw(16) << p->data->publisher << " "
         << setw(4) << p->data->year << " " << setw(4)
         << p->data->pages << endl;

    printTree(p->right);
}

void deleteTree(tree **p)
{
    if ((*p) == NULL)
        return;
    deleteTree(&((*p)->left));
    deleteTree(&((*p)->right));
    delete *p;
    *p = NULL;
}

void binSearch(struct bookNote **inx)
{
    queue *p, *head;
    head = new queue;
    head = NULL;
    system("CLS");
    std::cout << "Input key: " << std::endl;
    int l = 0, r = N - 1, m, i;
    int k;
    cin >> k;
    int index = 0;
    while (l < r)
    {
        m = (l + r) / 2;
        if (inx[m]->year < k)
            l = m + 1;
        else
            r = m;
    }
    if (inx[r]->year == k)
    {
        p = new queue;
        p->data = inx[r];
        head = p;
        btree[index] = new queue;
        btree[index]->data = inx[r];
        ++index;
        while ((++r < N) && (inx[r]->year == k))
        {
            p->next = new queue;
            p->next->data = inx[r];
            p = p->next;
            btree[index] = new queue;
            btree[index]->data = inx[r];
            ++index;
        }
        p->next = NULL;
        int u = 1;
        for (p = head; p; p = p->next)
        {

            cout << u << setw(12) << p->data->author
                 << " " << setw(32) << p->data->title << " "
                 << setw(16) << p->data->publisher << " "
                 << setw(4) << p->data->year << " " << setw(4)
                 << p->data->pages << endl;
            u++;
        }
    }
    else
    {
        printf("Not found!\n");
        return;
    }
    std::cout << "Queue created, press ESCAPE to return OR press any key EXCEPT "
                 "ESCAPE to create and print a tree..."
              << std::endl;
    int key = _getch();
    if (key == ESCAPE)
        return;
    for (p = head; p; p = p->next)
    {
        B2INSERT(p->data, root);
    }
    system("cls");
    printTree(root);
    cout << "To do a search, press any key EXCEPT ESCAPE..." << endl;
    key = _getch();
    if (key == ESCAPE)
        return;
    system("cls");
    int key_search;
    cout << "Input key (pages, XXX)" << endl;
    cin >> key_search;
    treeSearch(root, key_search);
    std::cout << " Press any key to return..." << std::endl;
    deleteTree(&root);
    _getch();
}

void Digital_Sort(struct bookNote **inx)
{
    bookNote *array[256][1000];
    int k = 1;
    int counter[256];
    for (int rank = 11; rank >= 0; --rank)
    {
        for (int i = 0; i < 256; ++i)
            counter[i] = 0;
        for (int i = 0; i < 4000; ++i)
        {
            int tmp = (int)(inx[i]->author[rank]);
            tmp = tmp < 0 ? tmp + 128 : tmp;
            array[tmp][counter[tmp]] = inx[i];
            counter[tmp]++;
        }
        int arrayNumber = 0;
        int inxNumber = 0;
        for (int i = 0; i <= 255; ++i)
        {
            while (arrayNumber != counter[i])
            {
                inx[inxNumber] = array[i][arrayNumber];
                arrayNumber++;
                inxNumber++;
            }
            arrayNumber = 0;
        }
    }
    for (int rank = 0; rank < 3; ++rank)
    {
        for (int i = 0; i < 10; ++i)
            counter[i] = 0;
        for (int i = 0; i < 4000; ++i)
        {
            array[inx[i]->year / k % 10][counter[inx[i]->year / k % 10]] = inx[i];
            counter[inx[i]->year / k % 10]++;
        }
        int arrayNumber = 0;
        int inxNumber = 0;
        for (int i = 0; i < 10; ++i)
        {
            while (arrayNumber != counter[i])
            {
                inx[inxNumber] = array[i][arrayNumber];
                arrayNumber++;
                inxNumber++;
            }
            arrayNumber = 0;
        }
        k *= 10;
    }
}

int main()
{
    int key;
    int sortFlag = 0;
    bookNote *inx[N];
    bookNote note[N];

    FILE *fp;
    fp = fopen("testBase1.dat", "rb");
    fread((bookNote *)note, sizeof(bookNote), N, fp);
    fclose(fp);

    for (int i = 0; i < N; ++i)
        inx[i] = &note[i];

    while (key != ESCAPE)
    {
        system("CLS");
        if (sortFlag)
            cout << "\t==Sorted!==\n"
                 << endl;
        cout << "\t1. Print DB" << endl
             << "\t2. Sort DB" << endl
             << "\t3. Coding" << endl
             << "\t4. BinSearch" << endl
             << "\tPress ESC to exit" << endl;
        key = _getch();
        switch (key - 48)
        {
        case 1:
        {
            print(inx, 0);
            break;
        }
        case 2:
        {
            sortFlag = 1;
            system("CLS");
            cout << "Sorting...";
            Digital_Sort(inx);
            break;
        }
        case 3:
        {
            system("CLS");
            Fano();
            _getch();
            break;
        }
        case 4:
        {
            if (sortFlag == 0)
            {
                system("CLS");
                std::cout << "DB not sorted!\n\n"
                          << "Press any key to continue..." << std::endl;
                _getch();
                break;
            }
            binSearch(inx);
            break;
        }
        }
    }
}
