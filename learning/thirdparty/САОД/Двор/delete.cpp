#include <iostream>
#include <stdio.h>
using namespace std;

struct vertex {
    int x;
    vertex *Left;
    vertex *Right;
} *Root;
       
vertex *ISDP(int a[], int L, int R) {
    int m;
    if (L > R) {
        return 0;
    }
    else {
        m = (L + R) / 2;
        vertex *p = new vertex;
        p->x = a[m];
        p->Left = ISDP(a, L, m-1);
        p->Right = ISDP(a, m+1, R);
        return p;
    }
}

void fillinc (int a[], int n) {
    for (int i = 0; i < n; ++i) 
    a[i] = i;
}    

float sdp(vertex *p, int L){
    if(p == 0){
        return 0;
    }
    else {
        return (L + sdp(p->Left, L + 1) + sdp(p->Right, L + 1));
    }    
}

int summa(vertex *p){
    if(p == 0){
        return 0;
    }
    else {
        return (p->x + summa(p->Left) + summa(p->Right));
    }    
}

void PrintMas (int a[], int n) {
    for (int i = 0; i < n; ++i) cout << a[i] << " ";
    cout << "\n";
}
// Слева направо
/*void obhod(vertex *p){
    if(p != 0){ 
        obhod(p->Left);
        cout << p->x << " ";
        obhod(p->Right);
    }
}
*/
// Сверху вниз

void obhod(vertex *p){
    if (p != 0) {
        cout << p->x << " ";
        obhod(p -> Left);
        obhod(p -> Right);        
    }
}


// Снизу вверх
/* 
void obhod(vertex *p){
    if (p != 0){
        obhod(p -> Left);
        obhod(p -> Right);
        cout << p -> x << " ";    
    }    
}        
*/

    


int razmer(vertex *p){
    if (!p)
        return 0;
    return (1 + razmer(p->Left) + razmer(p->Right));    
}

int max(int a,int b){
    if(a > b)
        return a;
    return b;    
}

int vysota(vertex *p){
    if(!p)
        return 0;
    return  (1 + max(vysota(p->Left), vysota(p->Right)));   
}

int poisk(vertex *p, int per){
    p = Root;
    while(p != NULL){
        if(p -> x < per) p = p -> Right;
        else if(p -> x > per) p = p -> Left;
        else break;
    }
    if (p != NULL) return p -> x;
    return -1;
}

int delver(int per, vertex *Root){
    vertex **p = &Root;
    vertex *s, *q, *r;
    while(*p != NULL){
        if((*p) -> x < per) p = &((*p) -> Right);
        else if (((*p) -> x > per)) p = &((*p) -> Left);
        else break;
    }
    if (*p != NULL){
        q = *p;
        if (q -> Left == NULL) *p = q -> Right;
        else { if (q -> Right == NULL) *p = q -> Left;
        else {
            r = q -> Left;
            s = q;
            while(r -> Right != NULL){
                s = r;
                r = r -> Right;    
            }
            s -> Right = r -> Left;
            r -> Left = q -> Left;
            r -> Right = q -> Right;
            *p = r;
        
        }
        }
        free(q);
    }
    obhod(Root);    
}

int main(){
    int n=10;
    int a[n];
    float h;
    int per;
    fillinc(a, n);
    PrintMas(a, n);
    cout << "======" << endl;
    Root = ISDP(a, 0, n-1);
    obhod(Root);
    
    h = sdp(Root, 1) / razmer(Root);
    cout << endl << "Razmer=" << razmer(Root) << endl;
    cout << "Kontrolnaya summa=" << summa(Root) << endl;
    cout << "Vysota=" << vysota(Root) << endl;
    cout << "Srednyaya vysota=" << h << endl;
    cout << "Enter smth to delete: ";
    cin >> per;
    if(poisk(Root, per) >= 0){
        cout << "Found, deleting " << poisk(Root, per) << endl;
        delver(per, Root);
    }
    else {
        cout << "Not found" <<endl; 
    }
    cout << endl;
    system ("pause");
}
    
