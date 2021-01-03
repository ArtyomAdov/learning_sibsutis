#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

#define ARRAY_SIZE 10
#define RANDOM_INTERVAL 10

typedef struct tree
{
	int data;
	int balance;
	struct tree *left;
	struct tree *right;
}vertex;

struct vertex *root;
bool height,VR,HR;

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


//void Print_Mas(int A[],int N)
//{
//	for(int i=0;i<N;i++)
//	printf("%d ",A[i]);
//}

void Print_Tree(vertex* root) 
{
	if (root != NULL) 
	{
		printf("%d ",root->data);
		Print_Tree(root->left);  
		Print_Tree(root->right); 
	}
}

vertex* B2Insert(vertex* root, int data)
{                                                      //
    vertex* q;
    if(root == NULL)
	{
		root = (vertex*) malloc (1 * sizeof(vertex)); 
        root->data = data;
        root->left = NULL;
        root->right = NULL;
        root->balance = 0;
        VR = true;
    }
    else 
	{
		if(root->data > data) 
		{
    	    B2Insert(data,root->left);
    	    if(VR == true) 
    	    {
    	        if(root->balance == 0) 
    	     	   {
    	            q = root->left;
    	        	root->left = q->right;
    	        	q->right = root;
    	        	root = q;
    	        	q->balance = 1;
    	        	VR = false;
    	        	HR = true;
    	            }
    	       	else 
    	       	{
    	        	root->balance = 0;
    	        	VR = true;
    	        	HR = false;
    	       	}
    	    }
    	    else 
			{
				HR = false;
			}
    	}
    	else 
		{
			if(root->data < data) 
    		{
    		    root = B2Insert(data,root->right);
    		    if(VR == 1)
    		    {
    		        root->balance = 1;
    		        VR = false;
    		        HR = true;
    		    }
    		    else 
				{
					if(HR == true) 
    		    	{
    		    	    if(root->balance == 1)
    		    	    {
    		    	        q = root->right;
    		    	        root->balance = 0;
    		    	        q->balance = 0;
    		    	        root->right = q->left;
    		    	        q->left = root;
    		    	        root = q;
    		    	        VR = true;
    		    	        HR = false;
    		    	    }
    		    	    else 
						{
							HR = false;
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
	int* array=NULL;
	int sum = 0;
	int size = 0;
	float average_heigth = 0.0;
    srand(time(NULL));
	array = Fill_Rand(array);
	for(short int i = 0; i < ARRAY_SIZE; i++)
	{
		printf("%d  ",array[i]);
	}
	printf("\n\n!DBD!");
//    for (i=0; i<N; i++)
//    {
//		b2insert(A[i],root);
//    }
	
//	printf ("\nDBD-tree (obhod L-R):\n");
	for(short int i = 0; i < ARRAY_SIZE; i++)  
	{
		root = B2Insert(root, array[i]);
		printf("\n%d) ",i);
		Print_Tree(root);
	}
	sum = Check_Sum(root, 0);
	printf("\nCheck sum DBD: %d\n",sum);
	int tree_h;
	tree_h = Tree_h(root);
	average_heigth = Average_Heigth(root);
	
	printf("Average heigth DBD: %f\n",average_heigth);
	printf("Height DBD: %d\n",tree_h);
	Print_Tree(root);
	free(root);
	root = NULL;
	
    printf ("\n Size tree: %d",size);
//    printf ("\n Check sum tree: %d",sum);
//    printf ("\n Height tree: %d",tree_h);
//    printf ("\n Average heigth: %.2f",average_height);
}
