#include <stdlib.h>
#include <stdio.h>

struct vertex {
    int x;
    int Balance;
    vertex *Left;
    vertex *Right;
};

void Commies (vertex *&Root){
	vertex *q;
	
	q = Root -> Left;
	Root -> Balance = 0;
	q -> Balance = 0;
	Root -> Left = q -> Right;
	q -> Right = Root;
	Root = q;
}

void Liberals (vertex *&Root){
	vertex *q;
	vertex *r;
	
	q = Root -> Left;
	r = q -> Right;
	
	if (r -> Balance < 0) Root -> Balance = 1;
	else Root -> Balance = 0;
	
	if (r -> Balance > 0) q -> Balance = -1;
	else q -> Balance = 0;
	
	r -> Balance = 0;
	q -> Right = r -> Left;
	Root -> Left = r -> Right;
	r -> Left = q;
	r -> Right = Root;
	Root = r;
}

void Conservatives (vertex *&Root){
	vertex *q;
	vertex *r;
	
	q = Root -> Right;
	r = q -> Left;
	
	if (r -> Balance > 0) Root -> Balance = -1;
	else Root -> Balance = 0;
	
	if (r -> Balance < 0) q -> Balance = 1;
	else q -> Balance = 0;
	
	r -> Balance = 0;
	q -> Left = r -> Right;
	Root -> Right = r -> Left;
	r -> Right = q;
	r -> Left = Root;
	Root = r;
}

void Nazis (vertex *&Root){
	vertex *q;
	
	q = Root -> Right;
	Root -> Balance = 0;
	q -> Balance = 0;
	Root -> Right = q -> Left;
	q -> Left = Root;
	Root = q;
}

void AVL_tree (int d, vertex *&Root){
	int Growth;
	
	if (Root == NULL){
		Root = new vertex;
		Root -> x = d;
		Root -> Left = NULL;
		Root -> Right = NULL;
		Root -> Balance = 0;
		Growth = 1;
	}
	
	else if (Root -> x > d){
	
		AVL_tree (d, Root -> Left);
	
		if (Growth == 1){
		
			if (Root -> Balance > 0){
				Root -> Balance = 0;
				Growth = 0;
			}
		
			else if (Root -> Balance == 0){
				Root -> Balance = -1;
				Growth = 1;
			}
		
			else if (Root -> Left -> Balance < 0){
				Commies (Root);
				Growth = 0;
			}
		
			else {
				Liberals (Root);
				Growth = 0;
			}
		}
	}
	
	else if (Root -> x < d){
		
		AVL_tree (d, Root -> Right);
		
		if (Growth == 1){
			
			if (Root -> Balance < 0){
				Root -> Balance =0;
				Growth = 0;
			}
			
			else if (Root -> Balance == 0){
				Root -> Balance = 0;
				Growth = 1;
			}
			
			else if (Root -> Right -> Balance > 0){
				Nazis (Root);
				Growth = 0;
			}
			
			else {
				Conservatives (Root);
				Growth = 0;
			}	
		}
	}
}

void FillRand (int *a, int n) {
    for (int i = 0; i < n; i++) 
    a[i] = rand()%50 + 1;
}    

float paths_length (vertex *p, int L){
    if (p == NULL) return 0;
    else
		return (L + paths_length (p -> Left, L + 1) + paths_length (p -> Right, L + 1));  
}

int summ (vertex *p){
    if (p == 0)
        return 0;
    else {
        return (p -> x + summ (p -> Left) + summ (p -> Right));
    }    
}

void PrintMas (int *a, int n){
	int i;
	
    for (i = 0; i < n; ++i) printf ("%d ", a[i]);
    printf ("\n");
}

void tree_walk (vertex *p){
    if (p != 0){ 
        tree_walk (p -> Left);
        printf ("%d ", p -> x);
        tree_walk (p -> Right);
    }
}

int tree_size (vertex *p){
    if (!p) return 0;
    return (1 + tree_size(p -> Left) + tree_size(p -> Right));    
}

int max (int a,int b){
    if (a > b) return a;
    return b;    
}

int height (vertex *p){
    if (!p) return 0;
    return  (1 + max (height (p -> Left), height (p -> Right)));   
}
    
int main(){
    int i, n = 10;
    float h;
    int *a;
    int b[10];
    int d;
    vertex *Root = NULL;
    
    a = new int[n];

    FillRand (a, n);
    PrintMas (a, n);
    
    for (i = 0; i < n; i++){
    	AVL_tree(a[i], Root);
	}
	
    tree_walk (Root);
    
    h = (float) paths_length (Root, 1) / tree_size (Root);
    
    printf ("\nSize = %d\n", tree_size (Root));
    printf ("Summary = %d\n", summ (Root));
    printf ("Height = %d\n", height (Root));
    printf ("Average height = %0.2f\n", h);
    
    system ("PAUSE");
    return 0;
}
