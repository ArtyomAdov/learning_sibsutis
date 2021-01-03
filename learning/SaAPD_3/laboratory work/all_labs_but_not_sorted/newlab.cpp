#include <stdio.h>
#include <stdlib.h>

struct vertex
{
	int data;
	int balance;
	vertex *left;
	vertex *right;
};

vertex *root;
bool growth,reduction;

void Fill_Rand(int Array[],int N)
{
	for(int i=0;i<N;i++)
	{	
        Array[i]=rand()%500-200;
        for (int j=0;j<i;j++)
        {
        	if (Array[i]==Array[j]) 
			{
				j=0;
				Array[i]=rand()%199-100;
			} 
		}
    } 
}

void Print_Tree(vertex *root)
{
	if (root!=NULL)
	{
		Print_Tree(root->left);
		printf(" %2d",root->data);
		Print_Tree(root->right);
	}
}

int Check_Sum(vertex *root, int sum)
{
	if(!root)
	{
		return sum;	
	}
	else
	{
		sum = root->data + Check_Sum(root->left,sum) + Check_Sum(root->right,sum);	
	}
}

int Tree_h(vertex* root)
{
	if(!root)
	{
		return 0;	
	}
	else 
	{
		int left = Tree_h(root->left);
		int right = Tree_h(root->right);
		if(left<right)
		{
			left = right;
		}
		return 1+left;	
	}
}

int Tree_Size(vertex* root, int size)
{
	if(!root)
	{
		size = 0;	
	}
	else 
	{
		size = (1 + Tree_Size(root->left, size) + Tree_Size(root->right, size));
		return size;	
	}
}



float sdp(vertex* root, int length)
{
    if(!root)
    {
    	return 0;
    }
    else
    {
		return (length + sdp(root->left, length + 1) + sdp(root->right, length + 1));
    }
}

float Average_Heigth(vertex* root)
{
	float average_heigth = 0.0;
	average_heigth = (sdp(root, 1) / Tree_Size(root,0));
	return average_heigth;
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
	if (r->balance<0)
	{
		root->balance=1;
	} 
	else
	{
		root->balance=0;
	} 
	if (r->balance>0) 
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

void Add_to_AVL(int data,vertex *&root)
{
	if (root==NULL)
	{
		root=new vertex;
		root->data=data;
		root->left=NULL;
		root->right=NULL;
		root->balance=0;
		growth=true;	
	}
	else
	{
		if (root->data>data)
		{
			Add_to_AVL(data,root->left);
			if (growth==true)
			{
				if (root->balance>0) 
				{
					root->balance=0;
					growth=false;
				}
				else
				{
					if (root->balance==0) 
					{
						root->balance=-1;
					}
					else
					{
						if (root->left->balance<0) 
						{
							LL_turn(root);
						}
						else
						{
							LR_turn(root);
							growth=false;
						}
					}
				}
			}
		}
		else
		{
			if (root->data<data)
			{
				Add_to_AVL(data,root->right);
				if (growth==true)
				{
					if (root->balance<0) 
					{
						root->balance=0;
						growth=false;
					}
					else
					{
						if (root->balance==0) 
						{
							root->balance=1;
						}
						else
						{
							if (root->right->balance>0) 
							{
								RR_turn(root);
							}
							else
							{
								RL_turn(root);
								growth=false;
							}
						}
					}
				}
				else
				{
					return;			
				} 
			}
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
	if (root->balance==-1)
	{
		root->balance=0;
	} 
	else 
	{
		if (root->balance==0) 
		{
			root->balance=1;
			reduction=false;
		}
		else
		{ 
			if (root->balance==1) 
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
	}
}

void del(vertex *&r,vertex *&q)
{
	if (r->right!=NULL)
	{
		del(r->right,q);
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
		reduction=true;
	}
	
}

void Delete_From_Avl(int delete_element,vertex *&root) 
{
	vertex *q;
	if (root==NULL) 
	{
		printf ("\n Can't delete this element");
	}
	else 
	{
		if (root->data>delete_element) 
		{
			Delete_From_Avl(delete_element,root->left);
			if (reduction) 
			{
				BL(root);
			}
		}
		else 
		{
			if (root->data<delete_element)
			{
				Delete_From_Avl(delete_element,root->right);
				if (reduction)
				{
					BR(root);
				} 
			}
			else
			{
				q=root;
				if (q->right==NULL)  
				{
					root=q->left;    
					reduction=true;
				}
				else
				{ 
					if (q->left==NULL)   
					{
						root=q->right;   
						reduction=true;
					}
					else
					{
						del(q->left,q);
						if (reduction)
						{
							BL(root);
						} 
					}
				}
			}
		}
	}
}

int main()
{
	int *Array,N=10,k,length;
	int sum, tree_h;
	float average_heigth;
	char key;
	Array=new int [N];
    Fill_Rand(Array,N);
	root=NULL;
	for (int i=0;i<N;i++) 
	{
		Add_to_AVL(Array[i],root); 
	}
	Print_Tree(root);
	while (1)
	{
		printf("\nWrite element for delete: ");
		if (key==27) 
		{
			break;
		}
		else
		{
			scanf("%d",&k);
			Delete_From_Avl(k,root);
			printf("\n");
		}
		Print_Tree(root);
		sum = Check_Sum(root, 0);
		printf("\nCheck sum AVL: %d\n",sum);
		int tree_h;
		tree_h = Tree_h(root);
		average_heigth = Average_Heigth(root);
	
		printf("Average heigth AVL: %f\n",average_heigth);
		printf("Height AVL: %d\n",tree_h);
	}
	delete (Array);
}
