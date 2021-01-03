#include <iostream>
#include <ctime>
#include<stdio.h>
#include <locale.h>
#include<stdlib.h>
#include <math.h>

using namespace std;

struct stack {
    stack *next;
    int data;
};

void FillRandStack(stack **head, int n) {
    struct stack *p;
    for (int i = 0; i < n; i++) {
        p = new stack;
        p->data = rand()%(2 * n) + 1;
        p->next = *head;
        *head = p;
    }
}

int CheckSumStack(stack *head) {
    int s = 0;
    struct stack *p = head;
    while (p != NULL) {
        s += p->data;
        p = p->next;
    }
    return s;
}

int RunNumberStack(stack *head) {
    int r = 1;
    if (head != NULL) {
        struct stack *p = head, *q = p->next;
        while (q != NULL) {
            if (p->data > q->data) r++;
            p = p->next;
            q = p->next;
        }
    } else r = 0;
    return r;
}

void PrintStack(stack *head, int r, int s) {
    struct stack *p = head;
    cout << "\nNumber of series in the list: " << r << endl;
    cout << "\nChecksum: " << s << endl;
    while (p != NULL) {
        printf("%3d ", p->data);
        p = p->next;
    }
}

void SelectSort(stack *head) {
    stack *one = head, *two = head->next, *min;
    while (one != NULL) {
        min = one;
        while (two != NULL) {
            if (one->data > two->data) {
	       if (min->data > two->data) {
                   min = two;
		}
            }
            two = two->next;
        }

        if (one != min) {
            swap(min->data, one->data);
        }
        one = one->next;
        two = one->next;
	}
}

int main() {
	srand(time(0));
    struct stack *head;
    head = NULL;
    int n,s,r;
    cout << "Enter the stack size: ";
    cin >> n;

    cout << "\nStack of random numbers: \n";
    FillRandStack(&head, n);
    s = CheckSumStack(head);
    r = RunNumberStack(head);
    PrintStack(head,r,s);

    cout << endl;
    SelectSort(head);

    PrintStack(head,r,s);
    CheckSumStack(head);
    RunNumberStack(head);
    return 0;
}
