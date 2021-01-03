#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <locale.h>

using namespace std;

const int N = 151;

int summ = 0, wght = 0;

int random(int n) { return rand() % n; }

int maxima(int a, int b) {
    if(a > b) return a;
    else return b;
}

struct tree {
    int num;
    tree *left, *right;   
};
//------------------------------------------------------------------------------
void add_sdp(tree *&root, int data) {
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

void DOP(tree *&root, int L, int R, int numbers[], int Ar[][N]) {
    int k;
    if(L < R) {
        k = Ar[L][R];
        add_sdp(root, numbers[k]);
        DOP(root, L, k-1, numbers, Ar);
        DOP(root, k, R, numbers, Ar);
    }
}

int mwh(int L, int R, int weights[], int Ar[][N]) {
    int k;
    if(L < R) {
        k = Ar[L][R];
        summ += k*weights[k];
        wght += weights[k];
        mwh(L, k-1, weights, Ar);
        mwh(k, R, weights, Ar);
    }
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
    tree *opti_tree = NULL;
    
    for(i = 0; i < N; i++) {
        numbers[i] = random(N)+1;
        weights[i] = random(100)+1;
    }
    
    AWAPAR(Aw, Ap, Ar, weights, N);

    DOP(opti_tree, 0, N-1, numbers, Ar);
    print_tree(opti_tree);
    
    mwh(0, N-1, weights, Ar);
    cout<<"\n\n\n\nN = 100\t\tSize\tControl Sum\tMedium Weight Height"<<endl;
    cout<<"DOP\t\t"<<size_tree(opti_tree)<<"\t"<<sum_tree(opti_tree)<<"\t\t"<<(float)summ/wght<<endl;
    
    system("PAUSE");
    return 0;
}
