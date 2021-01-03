#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>

struct vertex
{
	int data;
	int balance;
	vertex *left;
	vertex *right;
};

vertex *root;
int size,sum,h;

void random(int A[],int N)
{
	int i,j; 
	for(i=0;i<N;i++)
	{	
        A[i]=rand()%500-200;
        for (j=0;j<i;j++)
           if (A[i]==A[j]) {j=0; A[i]=rand()%199-100;} 
    } 
}

void PrintTree(vertex *p)
{
	if (p!=0)
	{
		PrintTree(p->left);
		printf(" %2d",p->data);
		PrintTree(p->right);
	}
}

int TreeSize(vertex *p)
{
    if (p==NULL) size=0;
    else size=1+TreeSize(p->left)+TreeSize(p->right);
}

int ControlTotal(vertex *p)
{
    if (p==NULL) sum=0;
    else sum=p->data+ControlTotal(p->left)+ControlTotal(p->right);
}

add_DOP(int L,int R,vertex *&p)
{
	int k;
	if (L<R)
	{
		k=Ar[L][R];
		add_DOP(p,);
		
	}
}

main()
{
	setlocale (LC_ALL,"Russian");
	int *A,N=100,i;
	size=0; sum=0; hm=0;
	A=new int [N];
    random(A,N);
    root=NULL;
	for (i=0;i<N;i++) 
		add_DOP(0,N,root);
	printf ("\nАВЛ-дерево (обход слева направо):");
	PrintTree(root);
	TreeSize(root);
    ControlTotal(root); 
    printf ("\n____________________________________________________");
    printf ("\n ДОП |  %4d    |   %4d    |   %4d   |   %4.2f   ",size,sum,h);
    printf ("\n____________________________________________________");
	delete (A);
    getch ();
}
