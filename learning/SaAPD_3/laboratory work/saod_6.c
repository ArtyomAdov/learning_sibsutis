#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <stdbool.h> 

#define ARRAY_SIZE 10
#define RANDOM_INTERVAL 10 

typedef struct tree
{
	int data; 
	int balance; 
	struct tree* left; 
	struct tree* right; 
}vertex; 

bool growth = false;

void Print_Tree(vertex* root) 
{
	if (root != NULL) 
	{
		Print_Tree(root->left); 
		printf("%d ",root->data); 
		Print_Tree(root->right); 
	}
}

vertex* LL_turn(vertex* root)
{
	vertex *q;
	q = root->left;
	q->balance = 0;
	root->balance = 0;
	root->left = q->right;
	q->right = root;
	root = q;
	return root;
}

vertex* RR_turn(vertex* root)
{
	vertex *q;
	q = root->right;
	q->balance = 0;
	root->balance = 0;
	root->right = q->left;
	q->left = root;
	root = q;
	return root;
}

vertex* LR_turn(vertex* root)
{
	vertex *q,*r;
	q = root->left;
	r = q->right;
	if (r->balance < 0)
	{
		root->balance = 1;	
	}
	else
	{
		root->balance = 0;	
	}
	if (r->balance > 0)
	{
		q->balance = -1;	
	}
	else q->balance = 0;
	r->balance = 0;
	root->left = r->right;
	q->right = r->left;
	r->left = q;
	r->right = root;
	root = r;
	return root;
}

vertex* RL_turn(vertex* root)
{
	vertex *q,*r;
	q = root->right;
	r = q->left;
	if(r->balance > 0) 
	{
		root->balance = -1;	
	} 
	else
	{
		root->balance = 0;	
	} 
	if (r->balance < 0)
	{
		q->balance = 1;
	} 
	else
	{
		q->balance = 0;	
	} 
	r->balance = 0;
	root->right = r->left;
	q->left = r->right;
	r->left = root;
	r->right = q;
	root = r;
	return root;	
}

vertex* Add_In_Avl(vertex* root, int value) 
{
	vertex* pointer = NULL; 
	if(root == NULL) 
	{
		root = (vertex*) malloc (1 * sizeof(vertex)); 
		root->data = value; 
		root->left = NULL;
		root->right = NULL; 
		root->balance = 0; 
		growth = true;
	}
	else 
	{
		if(value <= root->data) 
		{
			pointer = root->left; 
			pointer = Add_In_Avl(pointer,value); 
			root->left = pointer; 
			if(growth == true) 
			{
				if(root->balance > 0)  
				{
					root->balance = 0;
					growth = false; 
				}
				else 
				{
					if (root->balance == 0) 
					{
						root->balance = -1;
					}
					else 
					{
						if (root->left->balance < 0) 
						{
							root = LL_turn(root);
							growth = false;
							/*FUNCTION_LEFT_LEFT_TURN*/
						}
						else
						{
							root = LR_turn(root);
							growth = false;
							/*FUNCTION_LEFT_RIGHT_TURN*/
						}
					}
				}
			}
		}
		else
		{
			if (value > root->data) 
			{
				pointer = root->right; 
				pointer = Add_In_Avl(pointer,value);
				root->right = pointer; 
				if (growth == true) 
				{
					if(root->balance < 0) 
					{
						root->balance = 0;
						growth = false; 
					}
				}
				else 
				{
					if (root->balance == 0) 
					{
						root->balance = 1; 
					}
					else 
					{ 
						if (root->right->balance > 0) 
						{
							root = RR_turn(root);
							growth = false;
							/*FUNCTION_RIGHT_RIGHT_TURN*/
						}
						else 
						{
							root = RL_turn(root);
							growth = false;
							/*FUNCTION_RIGHT_LEFT_TURN*/
						}
					}
				}
			}
		}
	}
	return root; 
}

int* Fill_Rand(int* array) 
{
	array = (int*) calloc (ARRAY_SIZE, sizeof(int)); 
	for(short int i = 0; i < ARRAY_SIZE; i++) 
	{
		array[i] = rand()%RANDOM_INTERVAL; 
	}
	return array; 
}

void LL1(vertex *root)
{
	vertex *q;
	q = root->left;
	if (q->balance==0) 
	{
		root->balance = -1;
		q->balance = 1;
		growth=false;
	}
	else
	{
		root->balance = 0;
		q->balance = 0;
	}
	root->left = q->right;
	q->right = root;
	root=q;
}

void RR1(vertex *root)
{
	vertex *q;
	q = root->right;
	if (q->balance==0) 
	{
		root->balance=1;
		q->balance=-1;
		growth=false;   //true?
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

void BR(vertex *root)
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
			growth=false;
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

void BL(vertex *root)
{
	if (root->balance==-1)
	{
		root->balance=0;	
	} 
	else if (root->balance==0) 
		{
			root->balance=1;
			growth=false;
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


//vertex* Add_In_Sdp(vertex* root, int value)
//{
//	vertex** pointer = &root;
//	while(*pointer)
//	{
//		if(value > (*pointer)->data)
//		{
//			pointer = &(*pointer)->right;	
//		} 
//		else
//		{
//			if(value <= (*pointer)->data)
//			{
//				pointer = &(*pointer)->left;	
//			}	
//		}
//	}
//	(*pointer) = (vertex*) malloc (1 * sizeof(vertex));
//	(*pointer)->data = value;
//	(*pointer)->left = NULL;
//	(*pointer)->right = NULL;
//	return root;
//}

//void SDPR(vertex** Root, int data)
//{
//	if((*Root) == NULL)
//	{
//		(*Root) = (vertex*) malloc (1 * sizeof(vertex));
//		(*Root)->data = data;
//		(*Root)->left = NULL;
//		(*Root)->right = NULL;
////		return Root;
//	}
//	if((*Root)->data <= data)
//	{
//		SDPR((*Root)->right, data);
//	}
//	else if((*Root)->data > data) 
//	{
//		SDPR((*Root)->left, data);
//	}
////	else if(()Root->data == data) return;
//}

void SDPR(vertex** root, int value)
{
	if((*root) == NULL)
	{
		(*root) = (vertex*) malloc (1 * sizeof(vertex));
		(*root)->data = value;
		(*root)->left = NULL;
		(*root)->right = NULL;
	}
	else
	{
		if(value <= (*root)->data)
		{
			SDPR(&(*root)->left, value);
		}
		else
		{
			SDPR(&(*root)->right, value);
		}
	}
}

int Check_Sum(vertex *root, int sum)
{
	if(!root)
	{
		sum = 0;
	}
	else
	{
		sum = root->data + Check_Sum(root->left,sum) + Check_Sum(root->right,sum);	
	}
	return sum;
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

float Average_Height(vertex* root)
{
	float height;
	//float average_height = 0.0;
	//average_height = (sdp(root, 1) / Tree_Size(root,0));
	height = sdp(root, 1) / Tree_Size(root,0);
	return height;
}

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int Tree_h(vertex* root,int height)
{
    if (!root)
    {
        height = 0;
    }
    else
    {
    	height = 1 + max(Tree_h(root->left,height),Tree_h(root->right,height));
    }
    return height;
}

//void del_AVL(int delete_element,vertex *root)
//{
//	vertex *q;
//	if (root==0) 
//	{
//		printf ("\n Can not delete this element");
//		//getch();
//	}
//	else if (p->data>x) 
//		{
//			del_AVL(x,p->left);
//			if (lower) BL(p);
//		}
//		else
//			if (p->data<x)
//			{
//				del_AVL(x,p->right);
//				if (lower) BR(p);
//			}
//			else
//			{
//				q=p;
//				if (q->left==NULL)
//				{
//					p=q->right;
//					lower=true;
//				}
//				else
//					if (q->right==NULL)
//					{
//						p=q->left;
//						lower=true;
//					}
//					else
//					{
//						qp=q;
//						del(q->left,q);
//						if (lower) BL(p);
//					}
//	}
//}

int main() 
{
	vertex* root = NULL; 
	int* array = NULL; 
	int sum = 0;
	int size = 0;
	float average_height = 0.0;
	int height = 0;
	srand(time(NULL));
	array = Fill_Rand(array);
	for(short int i = 0; i < ARRAY_SIZE; i++)
	{
		printf("%d  ",array[i]);
	}
	printf("\n\n!AVL!");
	for(short int i = 0; i < ARRAY_SIZE; i++)  
	{
		root = Add_In_Avl(root,array[i]);
		printf("\n%d) ",i);
		Print_Tree(root);
	}
	sum = Check_Sum(root, 0);
	printf("\nCheck sum AVL: %d\n",sum);
	average_height = Average_Height(root);
	height = Tree_h(root,height);
	printf("Height AVL: %d\n",height);
	printf("Average height AVL: %f\n",average_height);
	Print_Tree(root);
	free(root);
	root = NULL;
	printf("\n\n!SDP!");
	for(short int i = 0; i < ARRAY_SIZE; i++)
	{
		SDPR(&root,array[i]);
		printf("\n%d) ",i);
		Print_Tree(root);
	}
	sum = 0;
	average_height = 0.0;
	height = 0;
	sum = Check_Sum(root, 0);
	printf("\nCheck sum SDP: %d\n",sum);
	average_height = Average_Height(root);
	height = Tree_h(root,height);
	printf("Height AVL: %d\n",height);
	printf("Height SDP: %f\n",height);
	printf("Average height SDP: %f\n",average_height);
	Print_Tree(root);
	free(array);
	array = NULL;
	free(root);
	root = NULL;
	return 0; 
}
