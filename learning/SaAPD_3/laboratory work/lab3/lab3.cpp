#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <graphics.h>

using namespace std;

struct vertex
{
	int data;
	vertex *left;
	vertex *right;
};

char buffer[256];

void TreeP(vertex *p, int left, int right, int level);

const int mnoz = 40;

int SizeTree(vertex *p)
{
	if (!p)
		return 0;
	return 1 + SizeTree(p->left) + SizeTree(p->right);
}

int HeighTree(vertex *p)
{
	if (!p)
		return 0;
	return 1 + max(HeighTree(p->left), HeighTree(p->right));
}

int CheckSumTree(vertex *p)
{
	if (!p)
		return 0;
	return 1 + p->data + CheckSumTree(p->left) + CheckSumTree(p->right);
}

int SumDP(vertex *p, int L)
{
	if (!p)
		return 0;
	return L + SumDP(p->left, L + 1) + SumDP(p->right, L + 1);
}

double AverageHeight(vertex *p)
{
	return (double)SumDP(p, 1) / SizeTree(p);
}

void SDPR(vertex *&Root, int data)
{
	if (!Root)
	{
		Root = new vertex;
		Root->data = data;
		Root->left = NULL;
		Root->right = NULL;
		return;
	}
	if (Root->data < data)
	{
		SDPR(Root->right, data);
	}
	else if (Root->data > data)
	{
		SDPR(Root->left, data);
	}
	else if (Root->data == data)
		return;
}

bool Tree_Delete(vertex *&Root, int data)
{
	vertex **p = &Root, *q, *s, *r;
	while (*p)
	{
		if ((*p)->data < data)
			p = &((*p)->right);
		else if ((*p)->data > data)
			p = &((*p)->left);
		else
			break;
	}
	if (!*p)
		return false;
	q = *p;
	if (q->left == NULL)
		(*p) = q->right;
	else if (q->right == NULL)
		(*p) = q->left;
	else
	{
		r = q->left;
		s = q;
		if (!r->right)
		{
			r->right = q->right;
			*p = r;
		}
		else
		{
			while (r->right)
			{
				s = r;
				r = r->right;
			}
			s->right = r->left;
			r->left = q->left;
			r->right = q->right;
			*p = r;
		}
	}
	delete q;
	return true;
}

void obhod_1(vertex *Main)
{
	if (!Main)
		return;
	obhod_1(Main->left);
	cout << Main->data << "\t";
	obhod_1(Main->right);
}

int main()
{
	short int key = 1;
	setlocale(0, "RUS");
	int N = 10;
	int mas[N];
	vertex *SDPTree = NULL;
	for (int i = 0; i < N; i++)
	{
		mas[i] = rand() % 100;
		SDPR(SDPTree, mas[i]);
	}
	cout << endl
		 << "СДП:" << endl;
	obhod_1(SDPTree);
	cout << endl
		 << "n=100\tРазмер\tКонтрольная сумма\tВысота\tСредняя высота\nСДП\t" << SizeTree(SDPTree) << "\t" << CheckSumTree(SDPTree) << "\t\t\t" << HeighTree(SDPTree) << "\t" << AverageHeight(SDPTree);
	int x;
	while (1)
	{
		if (key != 1)
		{
			break;
		}
		cout << endl
			 << "Введите вершину для удаления: ";
		cin >> x;
		for (int i = 0; i < 50; i++)
			cout << endl;
		if (!Tree_Delete(SDPTree, x))
			cout << "Не ";
		cout << "Удалена вершина: " << x << endl;
		obhod_1(SDPTree);
		cout << endl;
		cout << "Продолжить: 1-да" << endl;
		cin >> key;
	}
	//getch();
}
