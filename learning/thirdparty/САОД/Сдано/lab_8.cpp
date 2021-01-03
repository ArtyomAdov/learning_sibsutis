#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <graphics.h>
#include <conio.h>

int N = 10; // size of tree
int H; // fact height
int CHH; // height of local branch
int CS; // control summ
int S; // size (number of elem)
int MIDH; // middle height
int BR; // number of branches

struct tree{
       int wes;
       int data;
       tree *l;
       tree *r;
};
    
void print_struct (tree *m){	
	if ( !m ) return;
	print_struct (m->l);
	printf("%4d",m->data);
	CS += m->data;
	print_struct (m->r);
}

void RandTrMaking (int data, int wes, tree *&head){
   if (head == NULL){    
        head = new tree;
        head->data = data;
        head->wes = wes;
        head->l = head->r = NULL;  
        S++;
    }
    if (data > head->data) {
		RandTrMaking (data, wes, head->r);
	} else {
		if (data < head->data) {
			RandTrMaking (data, wes, head->l);
		} else {
			if (data == head->data) {
            	return;
            }
		}
	}
}

void TreeA1 (int *A, int *W, tree *&head){
	for (int i = 1; i<=N; i++){
		RandTrMaking(A[i], W[i], head);
	}
}

void TreeA2(int L, int R, int* A, int* W, tree *&head){
	int wes, sum, i;
	wes = sum = 0;
	if (L <= R){
		for (i = L; i <= R; i++) {
			wes += W[i];
		}
		for (i = L; i < R; i++) {
			if ((sum < wes/2)&&((sum + W[i]) >= wes/2)) break;
			sum += W[i];
		}
		RandTrMaking (A[i], W[i], head);
		TreeA2(L, i-1, A, W, head);
		TreeA2(i+1, R, A, W, head);
	}
}

void middleHeight (tree *m){
    MIDH += m->wes*CHH;
    if ( m->l ) {
        CHH++;
        middleHeight (m->l);
    }
    if ( m->r ) {
        CHH++;
        middleHeight (m->r);
    }
    if ((!m->l) && (!m->r)){
        BR++;
        if (H < CHH)
           H = CHH;
    }
    CHH--;
    return;
}
       
tree *t_search (tree *m, int key)
{
	if ( !m ) return NULL;
	if (key == m->data)
		return m;
	if (key < m->data)
		return t_search (m->l,key);
	else return t_search (m->r,key);
	
}
       
void ClearTree(tree *S){
	if ( S->l )
        ClearTree ( S->l );
    if ( S->r )
        ClearTree ( S->r );
    delete S;
}

int shir(int n){
    if (n <= 1) return 1;
    if (n == 2) return 5;
    return shir(n-1) * 2 + 1;
}


void InsertSort (int *a, int *w, int n){
	int i,j,key,keyW;
	for (j=2;j<=n;j++){
		key=a[j];
		keyW=w[j];
		i=j-1;
		while(i>=1 && a[i]>key){
			a[i+1]=a[i];
			w[i+1]=w[i];
			i--;
	    }
	 	a[i+1]=key;
	 	w[i+1]=keyW;
	}
} 

main(){
	srand (time(NULL));
    int key;
    int *A = new int [N+1];
    int *W = new int [N+1];
    int Wes = 0;
    tree *h = NULL;
    tree *see = NULL;
    int i,j;
    
    
    puts("\n\n A1:");
    puts("\n");
    printf("\nInput array: \n");
    for (i=1; i<=N; i++){
		A[i] = rand() % (N*2) + 10;
		CS += A[i];
		for(j=0;j<i;j++){
            if (A[j] == A[i]) break;   
        }
        W[i] = 2*N-i;
		Wes += W[i];
        if (j < i) {CS -= A[i]; i--;}
        else printf("%4d (%d)",A[i], W[i]);
    }
	printf("\nCS - %d", CS);
    
    CS = H = S = MIDH = BR = 0; 
    CHH = 1;
    
    TreeA1(A, W, h);
    middleHeight (h);
    printf("\nTree was maden! \n");
    print_struct (h);
    printf("\nA1: CS - %d, ", CS);
    printf("HEIGHT - %d, ", H);
    printf("SIZE - %d, ", S);
    printf("MIDDLEH - %2.2f, ", ((double)MIDH/Wes));

    ClearTree (h);
    h = NULL;
    
    puts("\n\n A2:");
    puts("\n");
	InsertSort (A, W, N);
	printf(" \nSorted array: \n");
	for (i=1;i<=N;i++){
        printf("%4d (%d)",A[i], W[i]);
    }
	printf("\nCS - %d", CS);
    
    CS = H = S = MIDH = BR = 0; 
    CHH = 1;
    
    TreeA2(1, N, A, W, h);
    middleHeight (h);
    printf("\nTree was maden! \n");
    print_struct (h);
    printf("\nA2: CS - %d, ", CS);
    printf("HEIGHT - %d, ", H);
    printf("SIZE - %d, ", S);
    printf("MIDDLEH - %2.2f, ", ((double)MIDH/Wes));
    ClearTree (h);
    h = NULL;
    
    delete A;
    system ("PAUSE");
}
