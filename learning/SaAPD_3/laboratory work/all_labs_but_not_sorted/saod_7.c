#include <stdio.h>                    //вывод сверхувниз
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
bool reduction = false;                                   //if gr


void Print_Tree(vertex* root) 
{
	if (root != NULL) 
	{
		printf("%d ",root->data);
		Print_Tree(root->left);  
		Print_Tree(root->right); 
	}
}

void Free_Tree(vertex* root)
{
	if (root != NULL) 
	{ 
		Free_Tree(root->left);  
		Free_Tree(root->right);
		free(root);
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
	printf("\nll\n");
	return root;
}

vertex* RR_turn(vertex* root)                                         
{ 
	printf("\nrr\n");
	vertex *q;
	q = root->right;
	q->balance = 0;
	root->balance = 0;
	root->right = q->left;
	q->left = root;
	root = q;
	printf("\nrr\n");
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
	else 
	{
		q->balance = 0;
	}
	r->balance = 0;
	q->right = r->left;
	root->left = r->right;
	r->left = q;
	r->right = root;
	root = r;
	printf("\nlr\n");
	return root;
}

vertex* RL_turn(vertex* root)                  //
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
	q->left = r->left;
	root->right = r->right;
	r->right = q;
	r->left = root;
	root = r;
	printf("\nrl\n");
	return root;
}

vertex* Add_In_Avl(vertex* root, int value) 
{
	vertex* q = NULL; 
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
		if(root->data > value) //<=
		{
			q = root->left; 
			q = Add_In_Avl(q,value); 
			root->left = q;
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
						growth = true;
					}
					else 
					{
						if (root->left->balance < 0) //<0
						{
							printf("\nll!\n");
							root = LL_turn(root);
							growth = false;
						}
						else
						{
							printf("\nlr!\n");
							root = LR_turn(root);
							growth = false;
						}
					}
				}
			}
		}
		else
		{
			if (root->data < value) 
			{
				q = root->right; 
				q = Add_In_Avl(q,value);
				root->right = q; 
				if (growth == true) 
				{
					if(root->balance < 0) 
					{
						root->balance = 0;
						growth = false; 
					}
				
					else 
					{
						if (root->balance == 0) 
						{
							root->balance = 1;
							growth = true; 
						}
						else 
						{ 
							if (root->right->balance > 0) //>0
							{
								printf("\nrr!\n");
								root = RR_turn(root);
								growth = false;
							}
							else 
							{
								printf("\nrl!\n");
								root = RL_turn(root);
								growth = false;
							}
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
	for(short int i = 0, j = 0; i < ARRAY_SIZE; i++) 
	{
		j = rand()%ARRAY_SIZE;
		if(array[j] == 0)
		{
			array[j] = i;	
		}
		else
		{
			i--;
		}
	}
	return array; 
}

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

vertex* LL1(vertex* root)   // bool and &
{
	vertex* q = NULL;
	q = root->left;
	if (q->balance == 0) 
	{
		root->balance = -1;
		q->balance = 1;
		reduction = false;
	}
	else
	{
		root->balance = 0;
		q->balance = 0;
	}
	root->left = q->right;
	q->right = root;
	root = q; 
	return root;
}

vertex* RR1(vertex* root)
{
	vertex* q = NULL;
	q = root->right;
	if (q->balance == 0)
	{
		root->balance = 1;
		q->balance = -1;
		reduction = false;        
	}
    else
	{
		root->balance = 0;
		q->balance = 0;
	}
	root->right = q->left;
	q->left = root;
	root = q;
	return root;
}



vertex* BL(vertex* root)            //
{
	if(root->balance == -1)
	{
		root->balance = 0;
	}
	else
	{
		if (root->balance == 0)
		{
			root->balance = 1;
			reduction = false;
		}
		else
		{
			if (root->balance == 1)
			{
				if (root->right->balance >= 0)
				{
					root = RR1(root);
				} 
				else
				{
					root = RL_turn(root);
				}
			}
		}
	}
	return root;
}

vertex* BR(vertex* root)
{
	if(root->balance == 1)
	{
		root->balance = 0;
	}
	else
	{
		if(root->balance == 0)
		{
			root->balance = -1;
			reduction = false;
		}
		else
		{
			if(root->balance == -1)
			{
				if (root->left->balance <= 0)
				{
					root = LL1(root);
				}
				else
				{
					root = LR_turn(root);
				}
			}
		}
	}
	return root;
}

vertex* Delete_Element_With_Two_Subtree(vertex* q, vertex* r)    ////////// how?
{
	if(r->right != NULL)
	{
		r = Delete_Element_With_Two_Subtree(q,r->right);
		if(reduction == true)
		{
			r = BR(r);
		}
	}
	else
	{   q->data=r->data;
		q=r;
		r=r->left;
		reduction = true;
		//root = root->left;
		//reduction = true;
	}
	return r;//q?
}

vertex* Find_And_Delete_In_Avl(vertex* root, int delete_element)
{
	vertex* q = NULL;
	if(root == NULL)
	{
		printf("This element impossible delete\n");                //про пустое и эл нет
		return root;
	}
	else
	{
		if(delete_element < root->data)
		{
			q = root->left;
			q = Find_And_Delete_In_Avl(q,delete_element);
			if(reduction == true)
			{
				root = BL(root);   //q
			}
		}
		else
		{
			if(delete_element > root->data)
			{
				q = root->right;
				q = Find_And_Delete_In_Avl(q,delete_element);
				if(reduction == true)
				{
					root = BR(root);//q
				}
			}
			else
			{
				q = root;
				if (q->right == NULL) 
				{
					root = q->left; 
					reduction = true;
				}
				else
				{
					if (q->left == NULL)///
					{
						root = q->right;
						reduction = true;
					}
					else
					{
						//printf("TWO SUBTREE\n");
						root = Delete_Element_With_Two_Subtree(q,q->left);
						if (reduction == true)
						{	
							root = BL(q);//q
						}
					}
				}
			}
		}
	}
	return root;
}




int main() 
{
	vertex* root = NULL; 
	int* array = NULL; 
	float average_heigth = 0.0;
	int sum = 0;
	int size = 0;
	int delete_element = 0;
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
	//Free_Tree(root);            
	vertex* root_sdp = NULL;
	
	printf("\n\n!SDP!");
	for(short int i = 0; i < ARRAY_SIZE; i++)
	{
		SDPR(&root_sdp,array[i]);
		printf("\n%d) ",i);
		Print_Tree(root_sdp);
	}
	sum = 0;
	average_heigth = 0.0;
	sum = Check_Sum(root_sdp, 0);
	printf("\nCheck sum SDP: %d\n",sum);
	average_heigth = Average_Heigth(root_sdp);
	tree_h = Tree_h(root_sdp);
	printf("Average heigth SDP: %f\n",average_heigth);
	printf("Height SDP: %d\n",tree_h);
	Print_Tree(root_sdp);
	Free_Tree(root_sdp);
	printf("\n");

	Print_Tree(root);
	while(1)
	{
		printf("If you want delete element from AVL-tree write 1\n");
		scanf("%d",&delete_element);
		if(delete_element != 1)
		{
			break;
		}
		else
		{
			printf("Write need element for delete from AVL-tree\n");
			scanf("%d",&delete_element);
			root = Find_And_Delete_In_Avl(root,delete_element);
		}
		Print_Tree(root);
		printf("\n");
	}
	Print_Tree(root);
	free(array);
	array = NULL;
	Free_Tree(root);
	root = NULL;
	return 0; 
}
