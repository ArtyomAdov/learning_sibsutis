#include <stdio.h>    
#include <stdlib.h>
#include <stdbool.h>

struct vertex
{
	int data;
	int balance;
	vertex *left;
	vertex *right;
};

vertex *root;
int N=10;
float average_height;
int size;
int sum;
int height;
bool VR,HR;

int Tree_Size(vertex *root, int size)
{
    if (!root) 
    {
    	size = 0;
	}
    else 
    {
    	size= 1 + Tree_Size(root->left,size) + Tree_Size(root->right,size);
	}
	return size;
}

int Check_Sum(vertex *root,int sum)
{
    if (!root)
    {
    	sum = 0;
	}
    else 
    {
    	sum = root->data + Check_Sum(root->left,sum) + Check_Sum(root->right,sum);
	}
	return sum;
}

int max(int a,int b)
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

int Tree_h(vertex *root,int height)
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

float sdp(vertex *root, int length)
{
    if (!root)
    {
        return 0;
    }
    else
    {
        return (length + sdp(root->left, length + 1) + sdp(root->right, length + 1));
    }
}

float Average_Height(vertex *root)
{
    float height;
    height = sdp(root, 1) / Tree_Size(root,0);
    return height;
}

void Fill_Rand(int array[],int N)
{
	for(int i = 0;i < N;i++)
	{
        array[i] = rand()%500-200;
        for (int j = 0;j < i;j++)
        {
        	if (array[i]==array[j]) 
			{
				j = 0; array[i]=rand()%199-100;
			}
		}
    }
}

void Print_Mas(int array[],int N)
{
	for(int i = 0;i < N;i++)
	{
		printf("%d ",array[i]);	
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

void B2Insert(int data,vertex *&root)
{
    vertex* q;
    if(!root)
	{
        root = new vertex;
        root->data = data;
        root->left = NULL;
        root->right = NULL;
        root->balance = 0;
        VR = true;
    }
    else if(root->data > data) 
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
	else if(root->data < data) 
    	{
        	B2Insert(data,root->right);
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

int main()
{
	int array[N];
	int size;
	int sum;
	int height;
	float average_height;
    root = NULL;
    Fill_Rand (array,N);
    for (int i = 0; i < N; i++)
    {
		B2Insert(array[i],root);
    }
	printf ("\nDBD - tree (obhod L- R):\n");
	Print_Tree(root);
	size = Tree_Size(root,size);
    sum = Check_Sum(root,sum);
    height = Tree_h(root,height);
    average_height = Average_Height(root);
    printf ("\n\nSize: %d\nSum: %d\nHeight %d\nAverage Height %.2f",size,sum,height,average_height);
}
