#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct vertex
{
	int data;
	int balance;
	vertex *left;
	vertex *right;
};

vertex *root;
int N=15;
bool reduction,growth; // lower = reduction , height = growth
//vertex *qp;

void Fill_Rand(int array[],int N)
{
	for(int i = 0;i < N;i++)
	{	
        array[i]=rand()%500-200;
        for (int j = 0;j < i;j++)
        {
        	if (array[i]==array[j]) 
			{
				j = 0; 
				array[i] = rand()%199-100;
			} 
		}
           
    } 
}

void Print_Tree(vertex *&root)
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
	if(r->balance < 0) 
	{
		root->balance=1;
	} 
	else 
	{
		root->balance=0;
	}
	if (r->balance> 0)
	{
		q->balance=-1;
	}  
	else 
	{
		q->balance=0;
	}
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
	if (r->balance>0)
	{
		root->balance=-1; 	
	}
	else
	{
		root->balance=0;	
	} 
	if (r->balance<0) 
	{
		q->balance=1;
	} 
	else
	{
		q->balance=0;
	}
	r->balance=0;
	root->right=r->left;
	q->left=r->right;
	r->left=root;
	r->right=q;
	root=r;	
}

void Add_in_AVL(int data,vertex *&root)
{
	if (root==0)
	{
		root=new vertex;
		root->data=data;
		root->left=NULL;
		root->right=NULL;
		root->balance=0;
		growth=true;	
	}
	else if (root->data>data)
		{
			Add_in_AVL(data,root->left);
			if (growth==true)
			{
				if (root->balance>0) 
				{
					root->balance=0;
					growth=false;
				}
				else if (root->balance==0)
				{
					root->balance=-1;
				} 
				else if (root->left->balance<0) 
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
		}
		else if (root->data<data)
		{
			Add_in_AVL(data,root->right);
			if (growth==true)
			{
				if (root->balance<0) 
				{
					root->balance=0;
					growth=false;
				}
				else if (root->balance==0)
				{
					root->balance=1;
				} 
				else if (root->right->balance>0) 
				{
					RR_turn(root);
					growth=false;
				}
				else
				{
					RL_turn(root);
					growth=false;
				}
			}
			else return;			
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

void RR1(vertex *&root)
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
		if (root ->balance==0) 
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
				else 
				{
					LR_turn(root);	
				}
			}	
		}
	}
}

void BL(vertex *&root)
{
	if (root->balance==-1)
	{
		root->balance=0;	
	} 
	else if (root->balance==0) 
		{
			root->balance=1;
			reduction=false;
		}
		else if (root->balance==1) 
		{
			if (root->right->balance>=0)
			{
				RR1(root);
			} 
			else
			{
				RL_turn(root);
			} 
		}
}

void Delete_Element_With_Two_Subtree(vertex *&r,vertex *&q)
{
	if (r->right!=NULL)
	{
		Delete_Element_With_Two_Subtree(r->right,q);
		if (reduction) 
		{
			BR(r);	
		}
	}
	else
	{
		q->data=r->data;
		q=r;
		r=r->left;
		//qp=NULL;
		reduction=true;
	}
	
}

void Find_And_Delete_In_Avl(int delete_element,vertex *&root)
{
	vertex *q;
	if (root==0) 
	{
		printf("This element impossible delete\n");
		//getch();
	}
	else if (root->data> delete_element) 
		{
			Find_And_Delete_In_Avl(delete_element,root->left);
			if (reduction)
			{
				BL(root);	
			} 
		}
		else if (root->data< delete_element)
			{
				Find_And_Delete_In_Avl(delete_element,root->right);
				if (reduction)
				{
					BR(root);	
				} 
			}
			else
			{
				q=root;
				if (q->left==NULL)
				{
					root=q->right;
					reduction=true;
				}
				else if (q->right==NULL)
					{
						root=q->left;
						reduction=true;
					}
					else
					{
						//qp=q;
						Delete_Element_With_Two_Subtree(q->left,q);
						if (reduction)
						{
							BL(root);	
						} 
					}
	}
}

int main()
{
	int array[N];
	//,i,k;
	//char key;
//	array=new int [N];
	int delete_element=0;
	root = NULL;
	Fill_Rand(array,N);
	for (int i = 0;i < N;i++) 
	{
		Add_in_AVL(array[i],root);
//		add_AVL(A[i],root); 
	}
	Print_Tree(root);
	while (1)
	{
//		printf("\nWrite element for delete: ");
//		key=getch();
        printf("If you want delete element from AVL-tree write 1\n");
//		scanf("%d",&delete_element);
		if( delete_element!=1)
		{
			break;
		}
		else
		{
			printf("Write need element for delete from AVL-tree\n");
			scanf("%d",&delete_element);
			Find_And_Delete_In_Avl(delete_element,root);
		}
		Print_Tree(root);
		printf("\n");
//		if (key==27) break;
//		else
//		{
//			scanf("%d",&k);
//			del_AVL(k,root);
//			printf("\n");
//		}
//		PrintTree(root);
	}
	Print_Tree(root);
	free(array);
	//array = NULL;
	free(root);
	root = NULL;
	return 0;
//	delete (A);
//    getch ();
}
