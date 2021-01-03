#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct tree
{
	int data;
	int balance;
	struct tree *left;
	struct tree *right;
}vertex;

struct vertex *root;
int size,sum,h,N=100;
float hm;
bool height,VR,HR;

int Tree_Size(vertex* root)
{
    if (root==NULL)
	{
		size=0;
	}
    else 
	{
		size=1+Tree_Size(root->left)+Tree_Size(root->right);
	}
}

int Control_Total(vertex* root)                                                         //
{
    if (root==NULL) 
	{
		sum=0;
	}
    else 
	{
		sum=root->data+Control_Total(root->left)+Control_Total(root->right);
	}
}

int max(int a,int b)
{
    if (a>b) 
	{
		return a; 
	}
	else 
	{
		return b;
	}
}

int Tree_h(vertex* root)
{
    if (root==NULL) 
	{
		h=0;
	}
    else 
	{
		h=1+max(Tree_h(root->left),Tree_h(root->right));
	}
}

float sdp(vertex* root, int L)
{
    if (root == 0)
    {
        return 0;
    }
    else
    {
        return (L + sdp(root->left, L + 1) + sdp(root->right, L + 1));
    }
}

float Average_Height(vertex* root)
{
    float h;
    h = sdp(root, 1) / Tree_Size(root);
    return h;
}

void Fill_Rand(int A[],int N)                                                         //
{
	int i,j;
	for(i=0;i<N;i++)
	{
        A[i]=rand()%500-200;
        for (j=0;j<i;j++)
		{
           if (A[i]==A[j]) 
		   	{
		   		j=0; 
		   		A[i]=rand()%199-100;
		   	}
		}
    }
}

void Print_Mas(int A[],int N)
{
	for(int i=0;i<N;i++)
	printf("%d ",A[i]);
}

void Print_Tree(vertex* root)
{
	if (root!=0)
	{
		Print_Tree(root->left);
		printf(" %2d",root->data);
		Print_Tree(root->right);
	}
}

void b2insert(int d,vertex *&root){                                                      //
    tree* q;
    if(root == NULL)
	{
        root = new vertex;
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
    	    b2insert(data,root->left);
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
    		    b2insert(data,root->right);
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
}

int main()
{
	setlocale (LC_ALL,"Russian");
	int A[N],i;
	size=0; sum=0; h=0; hm=0;
    root=NULL;
    Fill_Rand (A,N);
    for (i=0; i<N; i++)
    {
		b2insert(A[i],root);
    }
	printf ("\nДБД-дерево (обход слева направо):");
	Print_Tree(root);
	Tree_Size(root);
    Control_Total(root);
    Tree_h(root);
    hm=Average_Height(root);
    printf ("\n Size tree: %d",size);
    printf ("\n Check sum tree: %d",sum);
    printf ("\n Height tree: %d",h);
    printf ("\n Average heigth: %.2f",hm);
    getch ();
}
