#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

struct list
{
    int data;
    list *next;
} * head;

list *FillList()
{
    short int key = 1;
    list *h, *p, *s;
    h = s = new list;
    do
    {
        p = new list;
        cout << "Vvedite znachenie" << endl;
        cin >> s->data;
        s->next = p;
        s = p;
        cout << "Prodoljit 1-da" << endl;
        cin >> key;
    } while (key == 1);
    p = NULL;
    return h;
}

void PrintList(list *p)
{
    if (p->next != NULL)
    {
        cout << p->data << " ";
        PrintList(p->next);
    }
}

void CountingElements(list *p)
{
    short int q = 0;
    while (p->next != NULL)
    {
        q++;
        p = p->next;
    }
    cout << q << endl;
}

void menu()
{
    cout << "1) Fill list" << endl;
    cout << "2) Print list" << endl;
    cout << "3) Counting quantity elements" << endl;
    cout << "4) Adding elements after selected index element" << endl;
    cout << "5) Delete selected index element" << endl;
    cout << "6) Movement element" << endl;
    cout << "7) Ochistit ekran" << endl;
    cout << "0) Exit from programm" << endl;
}

list *AddElements(list *h, short int k, short int z)
{
    short int j = 1;
    list *pnew, *p = h;
    pnew = new list;
    pnew->data = z;
    if (k <= 0 || h == NULL)
    {
        pnew->next = h;
        h = pnew;
    }
    else
    {
        for (short int i = 0; i < k; i++)
        {
            if (p->next != NULL)
            {
                p = p->next;
                j++;
            }
        }
        if (k <= j + 1)
        {
            pnew->next = p->next;
            p->next = pnew;
        }
    }
    return h;
}

list *DeleteElements(list *h, short int k)
{
    list *p, *pnew;
    p = h;
    pnew = p->next;
    if (k == 0)
    {
        p = p->next;
    }
    else
    {
        while (k > 1)
        {
            k--;
            p = p->next;
            pnew = pnew->next;
            if (pnew == NULL)
            {
                break;
            }
        }
        if (pnew != 0)
        {
            p->next = pnew->next;
        }
    }
    return h;
}

list *MovementElements(list *h)
{
    short int g, k;
    list *p, *pold;
    p = pold = h;
    cout << "vvedite kakoi element peremestit" << endl;
    cin >> g;
    for (short int i = 0; i < g; i++)
    {
        if (pold->next != NULL)
        {
            pold = pold->next;
        }
    }
    DeleteElements(h, g);
    cout << "vvedite kuda peremestit" << endl;
    cin >> k;
    for (short int i = 0; i < k; i++)
    {
        if (p->next != NULL)
        {
            p = p->next;
        }
    }
    AddElements(h, k, pold->data);
    return h;
}

int main()
{
    short int komand = 1;
    list *head;
    while (komand != 0)
    {
        menu();
        cin >> komand;
        switch (komand)
        {
        case 1:
        {
            head = FillList();
            break;
        }
        case 2:
        {
            PrintList(head);
            cout << endl;
            break;
        }
        case 3:
        {
            CountingElements(head);
            break;
        }
        case 4:
        {
            short int k, z;
            cout << "vvedite posle kakogo vstavit" << endl;
            cin >> k;
            cout << "vvedite znachenie" << endl;
            cin >> z;
            head = AddElements(head, k, z);
            break;
        }
        case 5:
        {
            short int k;
            cout << "vvedite nomer elementa dlya udaleniya" << endl;
            cin >> k;
            head = DeleteElements(head, k);
            break;
        }
        case 6:
        {
            head = MovementElements(head);
            break;
        }
        case 7:
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
    cout << endl;
}