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

vertex *root,*root0;
int size,sum,h;
float hm;
bool height;

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

float sdp(vertex *p, int L)
{
    if (p == 0)
    {
        return 0;
    }
    else
    {
        return (L + sdp(p->left, L + 1) + sdp(p->right, L + 1));
    }
}

float AverageHeight(vertex *Root)
{
    float h;
    h = sdp(Root, 1) / TreeSize(Root);
    return h;
}

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

void PrintMas(int A[],int N)
{
	for(int i=0;i<N;i++)
	{
		printf("%d ",A[i]);
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

//void LL_turn(vertex *&p)
//{
//	vertex *q;
//	q=p->left;
//	q->balance=0;
//	p->balance=0;
//	p->left=q->right;
//	q->right=p;
//	p=q;
//}

//void LR_turn(vertex *&p)
//{
//	vertex *q,*r;
//	q=p->left;
//	r=q->right;
//	if (r->balance<0) p->balance=1; else p->balance=0;
//	if (r->balance>0) q->balance=-1; else q->balance=0;
//	r->balance=0;
//	p->left=r->right;
//	q->right=r->left;
//	r->left=q;
//	r->right=p;
//	p=r;	
//}

//void RR_turn(vertex *&p)
//{
//	vertex *q;
//	q=p->right;
//	q->balance=0;
//	p->balance=0;
//	p->right=q->left;
//	q->left=p;
//	p=q;
//}

//void RL_turn(vertex *&p)
//{
//	vertex *q,*r;
//	q=p->right;
//	r=q->left;
//	if (r->balance>0) p->balance=-1; else p->balance=0;
//	if (r->balance<0) q->balance=1; else q->balance=0;
//	r->balance=0;
//	p->right=r->left;
//	q->left=r->right;
//	r->left=p;
//	r->right=q;
//	p=r;	
//}

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
//					else
//						if (p->left->balance<0) 
//						{
//							LL_turn(p);
//							height=false;
//						}
//						else
//						{
//							LR_turn(p);
//							height=false;
//						}
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
//					else
//						if (p->right->balance>0) 
//						{
//							RR_turn(p);
//							height=false;
//						}
//						else
//						{
//							RL_turn(p);
//							height=false;
//						}
//			else return;			
//		}	
//	}
//}

//void add_SDP(int d,vertex *&p)
//{
//	if (p==NULL)
//     {
//	 	p=new vertex;
//        p->data=d;
//        p->left=NULL;
//		p->right=NULL;
//     }
//    else 
//    	if (p->data>d) add_SDP (d,p->left);
//        else
//        	if (p->data<d) add_SDP (d,p->right);
//}

int main()
{
	int *A,N=100,i;
	size=0; sum=0; h=0; hm=0;
	A=new int [N]; 
    random(A,N);
	root=root0=NULL;
	for (i=0;i<N;i++) 
	{
		add_AVL(A[i],root); 
		add_SDP(A[i],root0);
	}
	PrintTree(root);
	TreeSize(root);
    ControlTotal(root); 
    TreeH(root);
    hm=AverageHeight(root);
    printf ("\n     |Quantity element   |  CheckSum     |  Height    | Average   ");
    printf ("\n__________________________________________________________________");
    printf ("\n AVL |  %4d 		 |   %4d      	 |   %4d     |   %4.2f   ",size,sum,h,hm);
    printf ("\n__________________________________________________________________");
    size=0; sum=0; h=0; hm=0;
	TreeSize(root0);
    ControlTotal(root0); 
    TreeH(root0);
    hm=AverageHeight(root0);
    printf ("\n SDP |  %4d	         |   %4d      	 |   %4d     |   %4.2f   ",size,sum,h,hm);
    delete (A);
    getch ();
}
