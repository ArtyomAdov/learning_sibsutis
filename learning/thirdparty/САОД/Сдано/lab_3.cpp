#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <graphics.h>

using namespace std;

int main_window = -1;

struct tree
{
	int data;
	tree *left;
	tree *right;
};

char buffer[256];

void TreeP(tree *p, int left, int right, int level);

const int mnoz = 40;


void QuickSort(int *a, int L, int R);
void CreateIdealTree(tree *&A, int *mas2, int n);
tree *ISDP(int L, int R, int *mas);
void PrintTree(tree * p, int level);
void LeftToRight(tree *p);
int SizeTree(tree *p);
int HighTree(tree *p);
int SumTree(tree *p);
double SHighTree(tree *p);
int SPD(tree *p, int L);

void LeftToRight(tree *p)
{
	if(!p) return;
	LeftToRight(p->left);
	cout<<p->data<<" ";
	LeftToRight(p->right);
}

int SizeTree(tree *p)
{
	if(!p) return 0;
	return 1 + SizeTree(p->left) + SizeTree(p->right);
}

int HighTree(tree *p)
{
	if(!p) return 0;
	return 1 + max(HighTree(p->left), HighTree(p->right));
}

int SumTree(tree *p)
{
	if(!p) return 0;
	return 1 + p->data + SumTree(p->left) + SumTree(p->right);
}

double SHighTree(tree *p)
{
	return (double)SPD(p, 1)/SizeTree(p);
}

int SPD(tree *p, int L)
{
	if(!p) return 0;
	return L + SPD(p->left, L + 1) + SPD(p->right, L + 1);
}

void QuickSort(int *a, int L, int R)
{
	int x= a[(L+R)/2];
	int i = L;
	int j = R;
	do
	{
		while(a[i] < x) i++;
		while(a[j] > x) j--;
		if(i<=j) 
		{
			swap(a[i],a[j]); 
			i++; 
			j--; 
		}	
	}while(i<=j);
	if(L<j) QuickSort(a, L, j);
	if(R>i) QuickSort(a, i, R);
}

void CreateIdealTree(tree *&A, int *mas2, int n)
{
	int mas[n];
	for(int i = 0; i < n; i++) mas[i] = mas2[i];
	QuickSort(mas, 0, n - 1);
	A = ISDP(0, n - 1, mas);
}

tree *ISDP(int L, int R, int *mas)
{
	int m;
	if(L > R) return NULL;
	else m = (L+R)/2;
	tree *x = new tree;
	x->data = mas[m];
	x->left = ISDP(L, m - 1, mas);
	x->right = ISDP(m + 1, R, mas);
	return x;
}

void SDP(tree *&Root, int data)
{
	tree **p = &Root;
	while(*p)
	{
		if((*p)->data < data) p = &((*p)->right);
		else if((*p)->data > data) p = &((*p)->left);
		else return;
	}
	//if(!*p)
	{
		(*p) = new tree;
		(*p)->data = data;
		(*p)->left = NULL;
		(*p)->right = NULL;
	}
}

void SDPRecursive(tree *&Root, int data)
{
	if(!Root)	
	{
		Root = new tree;
		Root->data = data;
		Root->left = NULL;
		Root->right = NULL;
		return;
	}
	if(Root->data < data) SDPRecursive(Root->right, data);
	else if(Root->data > data) SDPRecursive(Root->left, data);
	else if(Root->data == data) return;
}

void SDPRecursiveWacky(tree *Root, int data)
{
	if(Root->data < data) 
	{
		if(!Root->right)
		{
			Root->right = new tree;
			Root->right->data = data;
			Root->right->left = NULL;
			Root->right->right = NULL;
			return;
		}
		SDPRecursiveWacky(Root->right, data);
	}
	else if(Root->data > data) 
	{
		if(!Root->left)
		{
			Root->left = new tree;
			Root->left->data = data;
			Root->left->left = NULL;
			Root->left->right = NULL;
			return;
		}
		SDPRecursiveWacky(Root->left, data);
	}
	else if(Root->data == data) return;
}

bool TreeRemove(tree *&Root, int data)
{
	tree **p = &Root, *q, *s, *r;
	while(*p)
	{
		if((*p)->data < data) p = &((*p)->right);
		else if((*p)->data > data) p = &((*p)->left);
		else break;
	}
	if(!*p) return false;
	q = *p;
	if(q->left == NULL) (*p) = q->right;
	else if(q->right == NULL) (*p) = q->left;
	else
	{
		r = q->left;
		s = q;
        if(!r->right)
        {
            r->right = q->right;
            *p = r;
        }	
        else
        {             
            while(r->right)
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

void TreeShow(tree *Main)
{
	if(!Main) return;
	TreeShow(Main->left);
	cout<<Main->data<<"\t";
	TreeShow(Main->right);
}

int main()
{
	setlocale(0, "RUS");
	int N = 10;
	int mas[N];
	tree *ISDPTree = NULL, *SDPTree = NULL;
	for(int i = 0; i < N; i++)
	{
        mas[i] = rand() % 100;
		SDP(SDPTree, mas[i]);
	}
	CreateIdealTree(ISDPTree, mas, N);
	//TreePaint(ISDPTree);
	cout<<"ISDP:"<<endl;
	TreeShow(ISDPTree);
	cout<<endl<<"SDP:"<<endl;
	TreeShow(SDPTree);
	cout<<endl<<"n=100\tРазмер\tКонтрольная сумма\tВысота\tСредняя высота\nИСДП\t"<<SizeTree(ISDPTree)<<"\t"<<SumTree(ISDPTree)<<"\t\t\t"<<HighTree(ISDPTree)<<"\t"<<SHighTree(ISDPTree)<<endl<<"СДП\t"<<SizeTree(SDPTree)<<"\t"<<SumTree(SDPTree)<<"\t\t\t"<<HighTree(SDPTree)<<"\t"<<SHighTree(SDPTree);
    int x;
	while(1)
	{
        cout<<endl<<"Введите вершину для удаления: ";
        cin>>x;
        for(int i = 0; i < 50; i++) cout<<endl;
        if(!TreeRemove(SDPTree, x)) cout<<"Не ";
        cout<<"Удалена вершина "<<x<<endl;
        TreeShow(SDPTree);
    }
	getch();
}
/*
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <graphics.h>

using namespace std;

int main_window = -1;

struct tree
{
	int data;
	tree *left;
	tree *right;
};

char buffer[256];

void TreeP(tree *p, int left, int right, int level);

const int mnoz = 40;


void QuickSort(int *a, int L, int R);
void CreateIdealTree(tree *&A, int *mas2, int n);
tree *ISDP(int L, int R, int *mas);
void PrintTree(tree * p, int level);
void LeftToRight(tree *p);
int SizeTree(tree *p);
int HighTree(tree *p);
int SumTree(tree *p);
double SHighTree(tree *p);
int SPD(tree *p, int L);

void LeftToRight(tree *p)
{
	if(!p) return;
	LeftToRight(p->left);
	cout<<p->data<<" ";
	LeftToRight(p->right);
}

int SizeTree(tree *p)
{
	if(!p) return 0;
	return 1 + SizeTree(p->left) + SizeTree(p->right);
}

int HighTree(tree *p)
{
	if(!p) return 0;
	return 1 + max(HighTree(p->left), HighTree(p->right));
}

int SumTree(tree *p)
{
	if(!p) return 0;
	return 1 + p->data + SumTree(p->left) + SumTree(p->right);
}

double SHighTree(tree *p)
{
	return (double)SPD(p, 1)/SizeTree(p);
}

int SPD(tree *p, int L)
{
	if(!p) return 0;
	return L + SPD(p->left, L + 1) + SPD(p->right, L + 1);
}

void QuickSort(int *a, int L, int R)
{
	int x= a[(L+R)/2];
	int i = L;
	int j = R;
	do
	{
		while(a[i] < x) i++;
		while(a[j] > x) j--;
		if(i<=j) 
		{
			swap(a[i],a[j]); 
			i++; 
			j--; 
		}	
	}while(i<=j);
	if(L<j) QuickSort(a, L, j);
	if(R>i) QuickSort(a, i, R);
}

void CreateIdealTree(tree *&A, int *mas2, int n)
{
	int mas[n];
	for(int i = 0; i < n; i++) mas[i] = mas2[i];
	QuickSort(mas, 0, n - 1);
	A = ISDP(0, n - 1, mas);
}

tree *ISDP(int L, int R, int *mas)
{
	int m;
	if(L > R) return NULL;
	else m = (L+R)/2;
	tree *x = new tree;
	x->data = mas[m];
	x->left = ISDP(L, m - 1, mas);
	x->right = ISDP(m + 1, R, mas);
	return x;
}

void SDP(tree *&Root, int data)
{
	tree **p = &Root;
	while(*p)
	{
		if((*p)->data < data) p = &((*p)->right);
		else if((*p)->data > data) p = &((*p)->left);
		else return;
	}
	//if(!*p)
	{
		(*p) = new tree;
		(*p)->data = data;
		(*p)->left = NULL;
		(*p)->right = NULL;
	}
}

void SDPRecursive(tree *&Root, int data)
{
	if(!Root)	
	{
		Root = new tree;
		Root->data = data;
		Root->left = NULL;
		Root->right = NULL;
		return;
	}
	if(Root->data < data) SDPRecursive(Root->right, data);
	else if(Root->data > data) SDPRecursive(Root->left, data);
	else if(Root->data == data) return;
}

void SDPRecursiveWacky(tree *Root, int data)
{
	if(Root->data < data) 
	{
		if(!Root->right)
		{
			Root->right = new tree;
			Root->right->data = data;
			Root->right->left = NULL;
			Root->right->right = NULL;
			return;
		}
		SDPRecursiveWacky(Root->right, data);
	}
	else if(Root->data > data) 
	{
		if(!Root->left)
		{
			Root->left = new tree;
			Root->left->data = data;
			Root->left->left = NULL;
			Root->left->right = NULL;
			return;
		}
		SDPRecursiveWacky(Root->left, data);
	}
	else if(Root->data == data) return;
}

bool TreeRemove(tree *&Root, int data)
{
	tree **p = &Root, *q, *s, *r;
	while(*p)
	{
		if((*p)->data < data) p = &((*p)->right);
		else if((*p)->data > data) p = &((*p)->left);
		else break;
	}
	if(!*p) return false;
	q = *p;
	if(q->left == NULL) (*p) = q->right;
	else if(q->right == NULL) (*p) = q->left;
	else
	{
		r = q->left;
		s = q;
        if(!r->right)
        {
            r->right = q->right;
            *p = r;
        }	
        else
        {             
            while(r->right)
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

void TreeShow(tree *Main)
{
	if(!Main) return;
	TreeShow(Main->left);
	cout<<Main->data<<"\t";
	TreeShow(Main->right);
}

int main()
{
	setlocale(0, "RUS");
	int N = 10;
	int mas[N];
	tree *ISDPTree = NULL, *SDPTree = NULL;
	for(int i = 0; i < N; i++)
	{
        mas[i] = rand() % 100;
		SDP(SDPTree, mas[i]);
	}
	CreateIdealTree(ISDPTree, mas, N);
	//TreePaint(ISDPTree);
	cout<<"ISDP:"<<endl;
	TreeShow(ISDPTree);
	cout<<endl<<"SDP:"<<endl;
	TreeShow(SDPTree);
	cout<<endl<<"n=100\tРазмер\tКонтрольная сумма\tВысота\tСредняя высота\nИСДП\t"<<SizeTree(ISDPTree)<<"\t"<<SumTree(ISDPTree)<<"\t\t\t"<<HighTree(ISDPTree)<<"\t"<<SHighTree(ISDPTree)<<endl<<"СДП\t"<<SizeTree(SDPTree)<<"\t"<<SumTree(SDPTree)<<"\t\t\t"<<HighTree(SDPTree)<<"\t"<<SHighTree(SDPTree);
    int x;
	while(1)
	{
        cout<<endl<<"Введите вершину для удаления: ";
        cin>>x;
        for(int i = 0; i < 50; i++) cout<<endl;
        if(!TreeRemove(SDPTree, x)) cout<<"Не ";
        cout<<"Удалена вершина "<<x<<endl;
        TreeShow(SDPTree);
    }
	getch();
}
*/
