#include <stdio.h>
#include <stdlib.h>  
int n,M=0,C=0;
struct Tspis {Tspis *next; int data;};
struct Queue {Tspis *head; Tspis *tail;} Q;  
void FillIncQ(int n) {
    Tspis *p;
    int i;
    p=new Tspis;
    p->data=1;
    p->next=NULL;
    Q.head=p;
    Q.tail=p;
    for (i=1;i<n;i++) {
        p=new Tspis;
        p->data=i+1;
        p->next=NULL;
        Q.tail->next=p;
        Q.tail=p;
    }
}
void FillDecQ(int n) {
    Tspis *p;
    int i;
    p=new Tspis;
    p->data=n;
    p->next=NULL;
    Q.head=p;
    Q.tail=p;
    for (i=n-1;i>0;i--) {
        p=new Tspis;
        p->data=i;
        p->next=NULL;
        Q.tail->next=p;
        Q.tail=p;
    }
}
void FillRandQ(int n) {
    Tspis *p;
    int i;
    p=new Tspis;
    p->data=rand()%n;
    p->next=NULL;
    Q.head=p;
    Q.tail=p;
    for (i=n-1;i>0;i--) {
        p=new Tspis;
        p->data=rand()%n;
        p->next=NULL;
        Q.tail->next=p;
        Q.tail=p;
    }
}
void PrintQ(Tspis *t) {
    while (t!=NULL) {
        printf("%2d ",t->data);
        t=t->next;
    } 
    printf("\n"); 
}
void FreeQ(Tspis *t) {
    Tspis *p;
    while (t!=NULL) {
        p=t->next;
        delete t;
        t=p;
    }
}
int Summa(Tspis *t) {
    if (t==NULL) return 0; else
    	return (t->data+Summa(t->next));
}
int RunNumber (Tspis *t) {
    Tspis *p;
    p=t;
    t=p->next;
    int c=0;
    while (t!=NULL) {
        if (t->data < p->data) c++;
        p=p->next;
        t=t->next;
    }
    return(c+1);
}
void Split(Tspis *S, Tspis *&a, Tspis *&b, int &n) {
    Tspis *k,*p;
    a=S;
    b=S->next;
    n=1;
    k=a;
    p=b;
    while (p!=NULL) {
        n++;
        k->next=p->next;
        k=p;
        p=p->next;
    }
}
void MergeSort(Tspis *S) {
    Tspis *a,*b;
    Queue c[2];
    int p,i,m,q,r;
    Split(S,a,b,n);
    p=1;
    M=0;
    C=0;
    while (p<n) {
        c[0].tail=(Tspis *)&c[0].head;
        c[1].tail=(Tspis *)&c[1].head; 
        i=0; 
        m=n;
        while (m > 0) {
            if (m >= p) q = p; else q = m;
            m-=q;
            if (m >= p) r = p;  else r = m;
            m-=r;
            while ((q!=0)&(r!=0)) {
                C++;
                if (a->data <= b->data) {
                    c[i].tail->next=a;
                    c[i].tail=a;
                    a=a->next;
                    q--;
                    M++;
                    }  else { 
                        c[i].tail->next=b;
                        c[i].tail=b;
                        b=b->next;
                        r--;
                        M++;
                        }
                }
                while (q > 0) {
                    c[i].tail->next=a;
                    c[i].tail=a;
                    a=a->next;
                    q--;
                    M++;
                }
                while (r > 0) {
                    c[i].tail->next=b;
                    c[i].tail=b;
                    b=b->next;
                    r--;
                    M++;
                }
                i=1-i;
           }
           a=c[0].head;
           b=c[1].head;
           p=2*p;
    }
    c[0].tail->next=NULL;
    S=c[0].head;
    Q.head=S;
    M*=2;
}
int main() {
    Tspis *p;
    int i,j;
    n=500; 
    int A[1000];
    p=new Tspis;
    p->data=0;
    p->next=NULL;
    Q.head=p;
    Q.tail=p;   
    FillIncQ(n);//
    PrintQ(Q.head);
    printf("sum = %d, RunNumber = %d\n",Summa(Q.head),RunNumber(Q.head));    
    MergeSort(Q.head);
    PrintQ(Q.head);
    printf("sum = %d, RunNumber = %d\n\n",Summa(Q.head),RunNumber(Q.head));
    FreeQ(Q.head); 
    p=new Tspis;
    p->data=0;
    p->next=NULL;
    Q.head=p;
    Q.tail=p;   
    FillDecQ(n);//
    PrintQ(Q.head);
    printf("sum = %d, RunNumber = %d\n",Summa(Q.head),RunNumber(Q.head));    
    MergeSort(Q.head);
    PrintQ(Q.head);
    printf("sum = %d, RunNumber = %d\n\n",Summa(Q.head),RunNumber(Q.head));
    FreeQ(Q.head);  
    p=new Tspis;
    p->data=rand()%n;
    p->next=NULL;
    Q.head=p;
    Q.tail=p;   
    FillRandQ(n);//
    PrintQ(Q.head);
    printf("sum = %d, RunNumber = %d\n",Summa(Q.head),RunNumber(Q.head));    
    MergeSort(Q.head);
    PrintQ(Q.head);
    printf("sum = %d, RunNumber = %d\n\n",Summa(Q.head),RunNumber(Q.head));
    FreeQ(Q.head);    
    printf("  n  |            MergeSort        |\n");
	printf("____________________________________\n");                
    printf("     |   Inc   |   Dec   |   Rand  |\n");                    
    for (n=100;n<501;n+=100) {
    	printf("____________________________________\n");
        printf(" %3d |",n); 
        p=new Tspis;
        p->data=0;
        p->next=NULL;
        Q.head=p;
        Q.tail=p;   
        FillIncQ(n);
        MergeSort(Q.head);
        printf(" %7d |",M+C);
    	FreeQ(Q.head);
        p=new Tspis;
        p->data=n;
        p->next=NULL;
        Q.head=p;
        Q.tail=p;
        FillDecQ(n);
        MergeSort(Q.head);
        printf(" %7d |",M+C);
        FreeQ(Q.head); 
        p=new Tspis;
        p->data=rand()%n;
        p->next=NULL;
        Q.head=p;
        Q.tail=p;   
        FillRandQ(n);
        MergeSort(Q.head);
        printf(" %d |\n",(M+C)/*1.5*/);
        FreeQ(Q.head);           
    }
    printf("____________________________________\n");
    system("pause");
}
