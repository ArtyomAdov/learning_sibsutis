#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <locale.h>

using namespace std;

const int N = 165;

int inc = 0,WH=0,WT=0;

int random(int n) { return rand() % n; }

int maxima(int a, int b) {
    if(a > b) return a;
    else return b;
}

struct tree {
    int num;
    int weight;
    tree *left, *right;   
};
//------------------------------------------------------------------------------
void add_sdp(tree *&root, int data, int weight) {
    tree **p;
    p = &root;
    while(*p != NULL) {
        if(data < (*p)->num) p = &((*p)->left);
        else if(data > (*p)->num) p = &((*p)->right);
        else break;
    }
    if(*p == NULL) {
        (*p) = new tree;
        (*p)->num = data;
        (*p)->weight = weight;
        (*p)->right = (*p)->left = NULL;
    }
}

void AWAPAR(int Aw[][N], int Ap[][N], int Ar[][N], int weights[], int n) {
    int j, i, h, m, min, k, x;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            Aw[i][j] = 0;
            Ap[i][j] = 0;
            Ar[i][j] = 0;
        }
    }
    for(i = 0; i < n; i++) {
        for(j = i+1; j < n; j++) {
            Aw[i][j] = Aw[i][j-1] + weights[j];
        }
    }
    for(i = 0; i < n-1; i++) {
        j = i + 1;
        Ap[i][j] = Aw[i][j];
        Ar[i][j] = j;
    }
    for(h = 2; h < n; h++) {
        for(i = 0; i < n-h; i++) {
            j = i + h;
            m = Ar[i][j-1];
            min = Ap[i][m-1] + Ap[m][j];
            for(k = m+1; k < Ar[i+1][j]; k++) {
                x = Ap[i][k-1] + Ap[k][j];
                if(x < min) {
                    m = k;
                    min = x;
                }
            }
            Ap[i][j] = min + Aw[i][j];
            Ar[i][j] = m;
        }
    }

}

void DOP(tree *&root, int L, int R, int numbers[], int weights[], int Ar[][N]) {
    int k;
    if(L < R) {
        k = Ar[L][R];
        add_sdp(root, numbers[k], weights[k]);
        DOP(root, L, k-1, numbers, weights, Ar);
        DOP(root, k, R, numbers, weights, Ar);
    }
}

void QuickSort(int A[], int B[], int L, int R) {
     
    int x = A[L], i = L, j = R, temp;
    while(i <= j) {
        while(A[i] < x) i++;
        while(A[j] > x) j--;
        if(i <= j) {
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            temp = B[i];
            B[i] = B[j];
            B[j] = temp;
            i++;
            j--;
        }
    }
    if(L < j) QuickSort(A, B, L, j);
    if(i < R) QuickSort(A, B, i, R);
}

void A1(tree *&root, int numbers[], int weights[], int n) {
    QuickSort(weights, numbers, 0, n-1);
    for(int i = 0; i < n; i++) {
        add_sdp(root, numbers[i], weights[i]);
    }
}

void A2(tree *&root, int numbers[], int weights[], int L, int R) {
int sum=0;
int wes=0;
int i;
if (L<=R)
{
    for(i=L;i<R;i++)
        wes+=weights[i];
    for(i=L;i<R;i++)
        {
            if ((sum<wes/2)&&(sum+weights[i]>wes/2)) break;
            sum+=weights[i];
        }
    add_sdp(root, numbers[i], weights[i]);
    A2(root, numbers, weights,L,i-1);
    A2(root, numbers, weights,i+1, R);
}
}

int wt(tree *p) {
    if(p == NULL) return 0;
    else 
    {
    WT+=p->weight;
    wt(p->left);
    wt(p->right);
        }
    return WT;
    
    //return (p->weight + wt(p->left) + wt(p->right));
}
int wh(tree *p) {
    inc++;
    if(p == NULL) return 0;
    else 
    {
    WH+=inc*p->weight;
    wh(p->left);
    wh(p->right);
}
return WH;
    //return (++inc*p->weight + wh(p->left) + wh(p->right));
}
//------------------------------------------------------------------------------
void print_tree(tree *p) {
    if(p != NULL) {
        print_tree(p->left);
        cout<<p->num<<" ";
        print_tree(p->right);
    }
}

int size_tree(tree *p) {
    if(p == NULL) return 0;
    else return (1 + size_tree(p->left) + size_tree(p->right));
}

int height_tree(tree *p) {
    if(p == NULL) return 0;
    else return (1 + maxima(height_tree(p->left), height_tree(p->right)));
}

int sdpf(tree *p, int l) {
    if(p == NULL) return 0;
    else return (l + sdpf(p->left, l+1) + sdpf(p->right, l+1));
}

int medium_height_tree(tree *root) {
    return (sdpf(root, 1)/size_tree(root));
}

int sum_tree(tree *p) {
    if(p == NULL) return 0;
    else return (p->num + sum_tree(p->left) + sum_tree(p->right));
}
//------------------------------------------------------------------------------

int main(){
    
    setlocale(LC_CTYPE, ".1251"); 
    setlocale(LC_MONETARY, ".1251");
    
    int numbers[N], weights[N], i, Aw[N][N], Ap[N][N], Ar[N][N];
    tree *opti_tree = NULL, *so_one_opti = NULL;
    tree *so_two_opti = NULL;
    
    for(i = 0; i < N; i++) {
        numbers[i] = random(N)+1;
       
        //printf("%d ",numbers[i]);
        weights[i] = random(100)+1;
    }
     printf("\n");
    AWAPAR(Aw, Ap, Ar, weights, N);

    DOP(opti_tree, 0, N-1, numbers, weights, Ar);
    print_tree(opti_tree);
    printf("\n");
    printf("\n");
    A1(so_one_opti, numbers, weights, N);
    print_tree(so_one_opti);
    printf("\n");
    printf("\n");
    QuickSort(numbers,weights,0,N-1);
//        for(i = 0; i < N; i++) {
//        printf("%d ",numbers[i]);
//    }
     printf("\n");
     printf("\n");
    A2(so_two_opti, numbers, weights, 0, N-1);
    print_tree(so_two_opti);
    printf("\n\n");
    //cout<<(float)wh(opti_tree);
    //cout<<(float)wt(opti_tree);
    WH=0;
    WT=0;
    inc=0;
    cout<<"\n\n\n\nN = 100\t\tSize\tControl Sum\tMedium Weight Height"<<endl;
    cout<<"DOP\t\t"<<size_tree(opti_tree)<<"\t"<<sum_tree(opti_tree)<<"\t\t"<<(float)wh(opti_tree)/wt(opti_tree)<<endl;
    WT=0;
    WH=0;
    inc=0;
    cout<<"A1\t\t"<<size_tree(so_one_opti)<<"\t"<<sum_tree(so_one_opti)<<"\t\t"<<(float)wh(so_one_opti)/wt(so_one_opti)<<endl;
    WT=0;
    WH=0;
    inc=0;
    cout<<"A2\t\t"<<size_tree(so_two_opti)<<"\t"<<sum_tree(so_two_opti)<<"\t\t"<<(float)wh(so_two_opti)/wt(so_two_opti)<<endl;    
    system("PAUSE");
    return 0;
}
