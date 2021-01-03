#include <iostream>

using namespace std;

struct vertex
{
    int data;
    vertex* Left;
    vertex* Right;
} Root;

vertex* BuildTree()
{
    vertex* root, *pl, *pr, *h;
    root = new vertex;
    pl = new vertex;
    pr = new vertex;
    h = root;
    root->data = 6;

    pl->data = 1; 
    root->Left = pl;
    
    pl->Left = NULL;
    pl->Right = pr;
    pl = new vertex;

    pr->data = 3;
    pr->Left = pl;
    pl->data = 2;
    
    pl->Left = NULL;
    pl->Right = NULL;
    pl = new vertex;
    
    pr->Right = pl;
    pr = new vertex;
    
    pl->data = 5;
    pl->Right = NULL;
    pl->Left = pr;
    
    pr->data = 4;
    pr->Left = NULL;
    pr->Right = NULL;
    
    return h;
}

void obhod_1(vertex* p)
{
    if (p != NULL)
    {
        obhod_1(p->Left);
        cout << p->data << " ";
        obhod_1(p->Right);
    }
}

void obhod_2(vertex* p)
{
    if (p != 0)
    {
        cout << p->data << " ";
        obhod_2(p->Left);
        obhod_2(p->Right);
    }
}

void obhod_3(vertex* p)
{
    if (p != 0)
    {
        obhod_3(p->Left);
        obhod_3(p->Right);
        cout << p->data << " ";
    }
}

void menu()
{
    cout << "1) Obhod sleva napravo " << endl;
    cout << "2) Obhod sverhu vniz " << endl;
    cout << "3) Obhod snizu vverh " << endl;
    cout << "8) Ochistit ekran" << endl;
    cout << "0) Vihod iz programmi" << endl;
}

int main()
{
    int key = 1;
    menu();
    vertex* Root;
    Root = BuildTree();
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
            break;
        }
        case 0:
        {
            break;
        }
        }
    }
}
