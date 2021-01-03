#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int N = 10;
int H; 
int CHH;
int BR;
int Check_Sum; 
int S; 
int MIDH;
int** AW; 
int** AP; 
int** AR; 

struct tree
{
    int wes;
    int data;
    tree *left;
    tree *right;
};
    
void print_struct (tree *m)
{	
	if ( !m ) return;
	print_struct (m->left);
	printf("%4d",m->data);
	Check_Sum = Check_Sum + (m->data);
	print_struct (m->right);
}

void Rand_Tree_Making (int data, int wes, tree *&head)
{
   if (head == NULL)
   {    
        head = new tree;
        head->data = data;
        head->wes = wes;
        head->left = head->right = NULL;  
        S++;
    }
    if (data > head->data) 
	{
		Rand_Tree_Making (data, wes, head->right);
	} 
	else 
	{
		if (data < head->data) 
		{
			Rand_Tree_Making (data, wes, head->left);
		} 
		else 
		{
			if (data == head->data) 
			{
            	return;
            }
		}
	}
}

void Matrix_AW(int** AW, int* W)
{
	for (int i=0; i<=N; i++)
	{
		for (int j=i+1; j<=N; j++)
		{
			AW[i][j] = AW[i][j-1] + W[j];
		}
	}
}

void Matrix_AP_AR(int** AP, int** AR, int** AW)
{
	int i,j,h,k,m,min;
	for (i=0; i<N; i++) 
	{
		j = i+1;
		AP[i][j] = AW[i][j];
		AR[i][j] = j;
	}
	for (h=2; h<=N; h++)
	{
		for (i=0; i<=N-h; i++)
		{
			j = i+h;
			m = AR[i][j-1];
			min = AP[i][m-1] + AP[m][j];
			for (k=m+1; k<=AR[i+1][j]; k++)
			{
				int x = AP[i][k-1] + AP[k][j];
				if (x < min) 
				{
					m = k;
					min = x;
				}
			}
			AP[i][j] = min + AW[i][j];
			AR[i][j] = m;
		}
	}
}

void Create_Tree(int L, int R, int* A, int* W, tree *&head)
{
	if (L < R)
	{
		int k = AR[L][R];
		Rand_Tree_Making (A[k], W[k], head);
		Create_Tree(L, k-1, A, W, head);
		Create_Tree(k, R, A, W, head);
	}
}

void Middle_Height (tree *m)
{
    MIDH = MIDH + (m->wes*CHH);
    if ( m->left ) 
	{
        CHH++;
        Middle_Height (m->left);
    }
    if ( m->right ) 
	{
        CHH++;
        Middle_Height (m->right);
    }
    if ((!m->left) && (!m->right))
	{
        BR++;
        if (H < CHH)
        {
        	H = CHH;
		} 
    }
    CHH--;
    return;
}
   
       
void Insert_Sort (int *a, int n)
{
	int i,j,key;
	for (j = 2; j<=n; j++)
	{
		key = a[j];
		i = j - 1;
		while(i>=1 && a[i]>key)
		{
			a[i + 1] = a[i];
			i--;
	    }
	 	a[i + 1] = key;
	}
} 

int main()
{
	srand (time(NULL));
    int key;
    int *A = new int [N+1];
    int *W = new int [N+1];
    int Wes = 0;
    tree *h = NULL;
    tree *see = NULL;
    int i,j;
    
    AW = new int* [N+1];
    for (i = 0; i < N + 1; i++)
	{
		AW[i] = new int [N+1];
	}
    AP = new int* [N+1];
    for (i = 0; i < N + 1; i++)
	{
		AP[i] = new int [N+1];
	}
    AR = new int* [N+1];
    for (i = 0; i < N + 1; i++)
	{
		AR[i] = new int [N+1];
	}
    printf("\nInput array: \n");
    for (i = 1; i<=N; i++)
	{
		A[i] = rand() % (N*2) + 10;
		Check_Sum = Check_Sum + A[i];
		for(j = 0; j < i; j++)
			{
	            if (A[j] == A[i]) break;   
	    	}
	    if (j < i)
		{
			Check_Sum = Check_Sum - A[i];
			i--;
		}
	    else
	    {
	    	printf("%3d",A[i]);
		}
    }
	Insert_Sort (A, N);
	printf(" \nSorted array: \n");
	for (i = 1; i<=N; i++)
	{
		W[i] = rand() % 50;
		Wes = Wes + W[i];
        printf("%2d(%d) ",A[i], W[i]);
    }
	printf("\nCheck_Sum - %d", Check_Sum);
	
    for (i = 0 ; i<=N; i++) 
	{
		for (j = 0; j<=N; j++) 
		{
			AW[i][j] = AR[i][j] = AP[i][j] = 0;
		}
	}
    Matrix_AW(AW, W);
    printf("\nMATRIX AW\n");
    for (int i=0; i < N; i++) 
	{
        for (int j=0; j < N; j++)
        {
        	printf("%5d ", AW[i][j]);
		}
    	printf("\n");
    }
    Matrix_AP_AR(AP, AR, AW);
    printf("\nMATRIX AP\n");
    for (int i = 0; i < N; i++) 
	{
        for (int j = 0; j < N; j++)
        {
        	printf("%5d ", AP[i][j]);
		}
        printf("\n");
    }
        
    Create_Tree(0, N, A, W, h);
    Middle_Height (h);
    printf("\nTree was made! \n");
    print_struct (h);
    printf("\nSDP: Check_Sum - %d, ", Check_Sum);
    printf("SIZE - %d, ", S);
    printf("MIDDLEH - %2.2f, ", ((double)AP[0][N]/AW[0][N]));
    printf("\nMATRIX AR\n");
    for (int i = 0; i < N; i++) 
	{
        for (int j = 0; j < N; j++)
        {
        	printf("%5d ", AR[i][j]);
		}
        printf("\n");
    }
    h = NULL;
    delete A;
    return 0;
}
