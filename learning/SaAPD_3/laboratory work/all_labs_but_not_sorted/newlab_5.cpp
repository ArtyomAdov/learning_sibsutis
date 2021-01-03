#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
// nado skobki, qp kak zamenit', text(ob udalenii)

struct vertex
{
	int data;
	int balance;
	vertex *left;
	vertex *right;
};

vertex *root;
bool growth,reduction;
vertex *qp;

void Fill_Rand(int A[],int N)
{
	int i,j; 
	for(i=0;i<N;i++)
	{	
        A[i]=rand()%500-200;
        for (j=0;j<i;j++)
           if (A[i]==A[j]) {j=0; A[i]=rand()%199-100;} 
    } 
}

void Print_Tree(vertex *root)
{
	if (root!=0)
	{
		Print_Tree(root->left);
		printf(" %2d",root->data);
		Print_Tree(root->right);
	}
}

void LL_turn(vertex *&root)
{
	vertex *q;
	q=root->left;
	q->balance=0;
	root->balance=0;
	root->left=q->right;
	q->right=root;
	root=q;
}

void LR_turn(vertex *&root)
{
	vertex *q,*r;
	q=root->left;
	r=q->right;
	if (r->balance<0) root->balance=1; else root->balance=0;
	if (r->balance>0) q->balance=-1; else q->balance=0;
	r->balance=0;
	root->left=r->right;
	q->right=r->left;
	r->left=q;
	r->right=root;
	root=r;	
}

void RR_turn(vertex *&root)
{
	vertex *q;
	q=root->right;
	q->balance=0;
	root->balance=0;
	root->right=q->left;
	q->left=root;
	root=q;
}

void RL_turn(vertex *&root)
{
	vertex *q,*r;
	q=root->right;
	r=q->left;
	if (r->balance>0) root->balance=-1; else root->balance=0;
	if (r->balance<0) q->balance=1; else q->balance=0;
	r->balance=0;
	root->right=r->left;
	q->left=r->right;
	r->left=root;
	r->right=q;
	root=r;	
}

void Add_to_AVL(int d,vertex *&root)
{
	if (root==0)
	{
		root=new vertex;
		root->data=d;
		root->left=NULL;
		root->right=NULL;
		root->balance=0;
		growth=true;	
	}
	else
	{
		if (root->data>d)
		{
			Add_to_AVL(d,root->left);
			if (growth==true)
				if (root->balance>0) 
				{
					root->balance=0;
					growth=false;
				}
				else
					if (root->balance==0) root->balance=-1;
					else
						if (root->left->balance<0) 
						{
							LL_turn(root);
							growth=false;
						}
						else
						{
							LR_turn(root);
							growth=false;
						}
		}
		else
		if (root->data<d)
		{
			Add_to_AVL(d,root->right);
			if (growth==true)
				if (root->balance<0) 
				{
					root->balance=0;
					growth=false;
				}
				else
					if (root->balance==0) root->balance=1;
					else
						if (root->right->balance>0) 
						{
							RR_turn(root);
							growth=false;
						}
						else
						{
							RL_turn(root);
							growth=false;
						}
			else return;			
		}	
	}
}

void LL1(vertex *&root)
{
	vertex *q;
	q=root->left;
	if (q->balance==0) 
	{
		root->balance=-1;
		q->balance=1;
		reduction=false;
	}
	else
	{
		root->balance=0;
		q->balance=0;
	}
	root->left=q->right;
	q->right=root;
	root=q;
}

void RR1(vertex *&p)
{
	vertex *q;
	q=root->right;
	if (q->balance==0) 
	{
		root->balance=1;
		q->balance=-1;
		reduction=false;
	}
	else
	{
		root->balance=0;
		q->balance=0;
	}
	root->right=q->left;
	q->left=root;
	root=q;
}

void BR(vertex *&root)
{
	if(root->balance==1)
	{
		root->balance=0;	
	}
	else
	{
		if (root->balance==0) 
		{
			root->balance=-1;
			reduction=false;
		}
		else
		{
			if (root->balance==-1)
			{
				if (root->left->balance<=0)
				{
					LL1(root);	
				}
				else LR_turn(root);	
			}	
		}
	}
}

void BL(vertex *&root)
{
	if (root->balance==-1) root->balance=0;
	else
		if (root->balance==0) 
		{
			root->balance=1;
			reduction=false;
		}
		else
			if (root->balance==1) 
				if (root->right->balance>=0) RR1(root);
				else RL_turn(root);
}

void del(vertex *&r,vertex *&q)
{
	if (r->right!=NULL)
	{
		del(r->right,q);
		if (reduction) BR(r);
	}
	else
	{
		qp->data=r->data;
		r=r->left;
		qp=NULL;
		reduction=true;
	}
	
}

void Delete_Element(int delete_element,vertex *&root)
{
	vertex *q;
	if (root==0) 
	{
		printf ("\n Can't delete this element");
		getch();
	}
	else
		if (root->data>delete_element) 
		{
			Delete_Element(delete_element,root->left);
			if (reduction) BL(root);
		}
		else
			if (root->data<delete_element)
			{
				Delete_Element(delete_element,root->right);
				if (reduction) BR(root);
			}
			else
			{
				q=root;
				if (q->left==NULL)
				{
					root=q->right;
					reduction=true;
				}
				else
					if (q->right==NULL)
					{
						root=q->left;
						reduction=true;
					}
					else
					{
						qp=q;
						del(q->left,q);
						if (reduction) BL(root);
					}
	}
}

int main()
{
	int *Array,N=10,i,k;
	char key;
	Array=new int [N];
    Fill_Rand(Array,N);
	root=NULL;
	for (i=0;i<N;i++) 
	{
		Add_to_AVL(Array[i],root); 
	}
	Print_Tree(root);
	while (1)
	{
		printf("\nWrite element for delete: ");
		key=getch();
		if (key==27) break;
		else
		{
			scanf("%d",&k);
			Delete_Element(k,root);
			printf("\n");
		}
		Print_Tree(root);
	}
	delete (Array);
    getch ();
}
