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
} root;

vertex *ISDP(int A[], int L, int R) 
{
    int m;
    if (L > R) 
	{
        return 0;
    }
    else {
        m = (L + R) / 2;
        vertex *p = new vertex;
        p->data = A[m];
        p->Left = ISDP(A, L, m-1);
        p->Right = ISDP(A, m+1, R);
        return p;
    }
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

int SizeVertex(vertex *p)
{
    if (!p)
    {
        return 0;
    }
    else
    {
        return (1 + SizeVertex(p->Left) + SizeVertex(p->Right));
    }
}

int HeightVertex(vertex *p)
{
    if (!p)
    {
        return 0;
    }
    else
    {
        return (1 + max(HeightVertex(p->Left), HeightVertex(p->Right)));
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

float sdp(vertex *p, int L)
{
    if (p == 0)
    {
        return 0;
    }
    else
    {
        return (L + sdp(p->Left, L + 1) + sdp(p->Right, L + 1));
    }
}
float AverageHeight()
{
    float h;
    h = sdp(Root, 1) / SizeVertex(Root);
    return h;
}

int CheckSum(vertex *p)
{
    if (p == 0)
    {
        return 0;
    }
    else
    {
        return (p->data + CheckSum(p->Left) + CheckSum(p->Right));
    }
}

void menu()
{
    cout << "1) Opredelit razmer" << endl;
    cout << "2) Opredelit visotu" << endl;
    cout << "3) Opredelit srednuu visotu" << endl;
    cout << "4) Opredelit kontrolnuu summu " << endl;
    cout << "5) Obhod sleva napravo ->" << endl;
    cout << "6) Obhod sverhu vniz " << endl;
    cout << "7) Obhod snizu vverh " << endl;
    cout << "8) Ochistit ekran" << endl;
    cout << "0) Vihod iz programmi" << endl;
}

void FillInc( int A[],  int n)
{
    for (int i = 0; i < n; ++i)
    {
        A[i] = 1 + i;
    }
}

void FillRand(int A[], int n)
{
	srand(time(NULL));
	for(int i=0;i<n;i++)
	{
		A[i]=rand()%n;
	};
}

void PrintMas( int A[],  int n)
{
	cout << "==================" << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << A[i] << " ";
    }
    cout << endl << "==================" << endl;
}

int main()
{
	root* Root = NULL;
    short int key = 1;
    int n=100;
	int A[n];
	menu();
	FillInc(A,n);
    //FillRand(A, n);
    PrintMas(A, n);
    Root = ISDP(A, 0, n - 1);
	while (key != 0)
    {
        cin >> key;
        switch (key)
        {
        case 1:
        {
        	cout << endl;
            cout << SizeVertex(Root) << endl;
            break;
        }
        case 2:
        {
        	cout << endl;
            cout << HeightVertex(Root) << endl;
            break;
        }
        case 3:
        {
        	cout << endl;
            cout << AverageHeight() << endl;
            break;
        }
        case 4:
        {
        	cout << endl;
            cout << CheckSum(Root) << endl;
            break;
        }
        case 5:
        {
        	cout << endl;
            obhod_1(Root);
            cout << endl;
            break;
        }
        case 6:
        {
        	cout << endl;
            obhod_2(Root);
            cout << endl;
            break;
        }
        case 7:
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
            PrintMas(A,n);
            break;
        }
        case 0:
        {
            break;
        }
        }
    }
}
