#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

using namespace std;

struct vertex
{
    int data;
    vertex *Left;
    vertex *Right;
} * Root;

vertex *BuildTree(int A[], int n)
{
    vertex *root, *pl, *pr, *h;
    root = new vertex;
    pl = new vertex;
    pr = new vertex;
    h = root;
    root->data = 1;

    pl->data = 2; 
    root->Left = pl;
    
    pl->Left = NULL;
    pl->Right = NULL;
    pl = new vertex;

    pr->data = 3;
    root->Right = pr;
    
    pl->data = 4;
    pr->Left = pl;

    pl->Left = NULL;
    pl->Right = NULL;
    pl = new vertex;

    root = new vertex;
    root->data = 5;    
    pr->Right = root;
    
	root->Right = NULL;
    pl->data = 6;
    root->Left = pl;

    pl->Left = NULL;
    pl->Right = NULL;
    return h;
}
void obhod_1(vertex *p)
{
    if (p != NULL)
    {
        obhod_1(p->Left);
        cout << p->data << " ";
        obhod_1(p->Right);
    }
}

void obhod_2(vertex *p)
{
    if (p != 0)
    {
        cout << p->data << " ";
        obhod_2(p->Left);
        obhod_2(p->Right);
    }
}

void obhod_3(vertex *p)
{
    if (p != 0)
    {
        obhod_3(p->Left);
        obhod_3(p->Right);
        cout << p->data << " ";
    }
}

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

void menu()
{
    cout << "1) Obhod sleva napravo ->" << endl;
    cout << "2) Obhod sverhu vniz " << endl;
    cout << "3) Obhod snizu vverh " << endl;
    cout << "8) Ochistit ekran" << endl;
    cout << "0) Vihod iz programmi" << endl;
}

void PrintMas(int A[], int n)
{
    cout << "==================" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << A[i] << " ";
    }
    cout << endl
         << "==================" << endl;
}

int main()
{
	float sv;
    short int key = 1;
    int n = 6;
    int A[n];
    menu();
    PrintMas(A, n);
    vertex *Root;
    Root = BuildTree(A, n);
    while (key != 0)
    {
        cin >> key;
        switch (key)
        {
        case 1:
        {
        	cout << endl;
            obhod_1(Root);
            cout << endl;
            break;
        }
        case 2:
        {
           cout << endl;
            obhod_2(Root);
            cout << endl;
            break;
        }
        case 3:
        {
        	cout << endl;
            obhod_3(Root);
            cout << endl;
            break;
        }
        case 8:
        {
            system("CLS");
            menu();
            PrintMas(A, n);
            break;
        }
        case 0:
        {
            break;
        }
        }
    }
}
