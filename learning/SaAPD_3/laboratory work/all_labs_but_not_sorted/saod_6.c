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
		return sum;	
	}
	else
	{
		sum = root->data + Check_Sum(root->left,sum) + Check_Sum(root->right,sum);	
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

float Average_Heigth(vertex* root)
{
	float average_heigth = 0.0;
	average_heigth = (sdp(root, 1) / Tree_Size(root,0));
	return average_heigth;
}

int main() 
{
	vertex* root = NULL; 
	int* array = NULL; 
	float average_heigth = 0.0;
	int sum = 0;
	int size = 0;
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
	int tree_h;
	tree_h = Tree_h(root);
	average_heigth = Average_Heigth(root);
	
	printf("Average heigth AVL: %f\n",average_heigth);
	printf("Height AVL: %d\n",tree_h);
	Print_Tree(root);
	free(root);
	root = NULL;
	
	//printf("%d")
	
	printf("\n\n!SDP!");
	for(short int i = 0; i < ARRAY_SIZE; i++)
	{
		SDPR(&root,array[i]);
		printf("\n%d) ",i);
		Print_Tree(root);
	}
	sum = 0;
	average_heigth = 0.0;
	sum = Check_Sum(root, 0);
	printf("\nCheck sum SDP: %d\n",sum);
	average_heigth = Average_Heigth(root);
	tree_h = Tree_h(root);
	printf("Average heigth SDP: %f\n",average_heigth);
	printf("Height SDP: %d\n",tree_h);
	Print_Tree(root);
	free(array);
	array = NULL;
	free(root);
	root = NULL;
	return 0; 
}
