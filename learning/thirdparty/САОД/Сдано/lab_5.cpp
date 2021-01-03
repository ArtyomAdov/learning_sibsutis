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
bool height,lower;
vertex *qp;

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

void LL_turn(vertex *&p)
{
	vertex *q;
	q=p->left;
	q->balance=0;
	p->balance=0;
	p->left=q->right;
	q->right=p;
	p=q;
}

void LR_turn(vertex *&p)
{
	vertex *q,*r;
	q=p->left;
	r=q->right;
	if (r->balance<0) p->balance=1; else p->balance=0;
	if (r->balance>0) q->balance=-1; else q->balance=0;
	r->balance=0;
	p->left=r->right;
	q->right=r->left;
	r->left=q;
	r->right=p;
	p=r;	
}

void RR_turn(vertex *&p)
{
	vertex *q;
	q=p->right;
	q->balance=0;
	p->balance=0;
	p->right=q->left;
	q->left=p;
	p=q;
}

void RL_turn(vertex *&p)
{
	vertex *q,*r;
	q=p->right;
	r=q->left;
	if (r->balance>0) p->balance=-1; else p->balance=0;
	if (r->balance<0) q->balance=1; else q->balance=0;
	r->balance=0;
	p->right=r->left;
	q->left=r->right;
	r->left=p;
	r->right=q;
	p=r;	
}

void add_AVL(int d,vertex *&p)
{
	if (p==0)
	{
		p=new vertex;
		p->data=d;
		p->left=NULL;
		p->right=NULL;
		p->balance=0;
		height=true;	
	}
	else
	{
		if (p->data>d)
		{
			add_AVL(d,p->left);
			if (height==true)
				if (p->balance>0) 
				{
					p->balance=0;
					height=false;
				}
				else
					if (p->balance==0) p->balance=-1;
					else
						if (p->left->balance<0) 
						{
							LL_turn(p);
							height=false;
						}
						else
						{
							LR_turn(p);
							height=false;
						}
		}
		else
		if (p->data<d)
		{
			add_AVL(d,p->right);
			if (height==true)
				if (p->balance<0) 
				{
					p->balance=0;
					height=false;
				}
				else
					if (p->balance==0) p->balance=1;
					else
						if (p->right->balance>0) 
						{
							RR_turn(p);
							height=false;
						}
						else
						{
							RL_turn(p);
							height=false;
						}
			else return;			
		}	
	}
}

void LL1(vertex *&p)
{
	vertex *q;
	q=p->left;
	if (q->balance==0) 
	{
		p->balance=-1;
		q->balance=1;
		lower=false;
	}
	else
	{
		p->balance=0;
		q->balance=0;
	}
	p->left=q->right;
	q->right=p;
	p=q;
}

void RR1(vertex *&p)
{
	vertex *q;
	q=p->right;
	if (q->balance==0) 
	{
		p->balance=1;
		q->balance=-1;
		lower=false;
	}
	else
	{
		p->balance=0;
		q->balance=0;
	}
	p->right=q->left;
	q->left=p;
	p=q;
}

void BR(vertex *&p)
{
	if (p->balance==1) p->balance=0;
	else
		if (p->balance==0) 
		{
			p->balance=-1;
			lower=false;
		}
		else
			if (p->balance==-1) 
				if (p->left->balance<=0) LL1(p);
				else LR_turn(p);
}

void BL(vertex *&p)
{
	if (p->balance==-1) p->balance=0;
	else
		if (p->balance==0) 
		{
			p->balance=1;
			lower=false;
		}
		else
			if (p->balance==1) 
				if (p->right->balance>=0) RR1(p);
				else RL_turn(p);
}

void del(vertex *&r,vertex *&q)
{
	if (r->right!=NULL)
	{
		del(r->right,q);
		if (lower) BR(r);
	}
	else
	{
		qp->data=r->data;
		//q=r;
		r=r->left;
		//delete (q);
		qp=NULL;
		lower=true;
	}
	
}

void del_AVL(int x,vertex *&p)
{
	vertex *q;
	if (p==0) 
	{
		printf ("\nВведенный элемент отсутствует(enter - продолжить)");
		getch();
	}
	else
		if (p->data>x) 
		{
			del_AVL(x,p->left);
			if (lower) BL(p);
		}
		else
			if (p->data<x)
			{
				del_AVL(x,p->right);
				if (lower) BR(p);
			}
			else
			{
				q=p;
				if (q->left==NULL)
				{
					p=q->right;
					lower=true;
				}
				else
					if (q->right==NULL)
					{
						p=q->left;
						lower=true;
					}
					else
					{
						qp=q;
						del(q->left,q);
						if (lower) BL(p);
					}
			}
	//delete (q);
}

int main()
{
	setlocale (LC_ALL,"Russian");
	int *A,N=10,i,k;
	char key;
	A=new int [N];
    random(A,N);
	root=NULL;
	for (i=0;i<N;i++) 
		add_AVL(A[i],root); 
	PrintTree(root);
	while (/*root!=0*/1)
	{
		printf("\nВведите вершину для удаления (esc - выход): ");
		key=getch();
		if (key==27) break;
		else
		{
			scanf("%d",&k);
			del_AVL(k,root);
			printf("\n");
		}
		PrintTree(root);
	}
	printf("\nКонец программы");
	delete (A);
    getch ();
}
