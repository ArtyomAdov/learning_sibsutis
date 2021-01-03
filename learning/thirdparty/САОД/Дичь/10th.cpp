#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
int n,M,C;
struct Tspis {Tspis *next; int data;};
struct Queue {Tspis *head; Tspis *tail;} Q;  
void fillincQ(int n) {
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
void filldecQ(int n) {
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
void fillrandQ(int n) {
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
void printQ(Tspis *t) {
     while (t!=NULL) {
           printf("%2d ",t->data);
           t=t->next;
     } 
     printf("\n"); 
}
void freeQ(Tspis *t) {
     Tspis *p;
     while (t!=NULL) {
           p=t->next;
           delete t;
           t=p;
     }
}
int sum(Tspis *t) {
     if (t==NULL) return 0; else
        return (t->data+sum(t->next));
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
     C=M=0;
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
}
void FillInc (int a[], int n) {
     a[0]=rand()%20-10;
     for (int i=1; i<n; i++) a[i]=a[i-1]+rand()%4;
}
void FillDec (int a[], int n) {
     a[0]=rand()%20+10;
     for (int i=1; i<n; i++) a[i]=a[i-1]-rand()%4;
}
void FillRand (int a[], int n) {
     for (int i=0; i<n; i++) a[i]=rand()%20-10;
}
void Heap (int a[], int l, int r) {
     int x=a[l],i=l,j;
     while (1) {
    	j=2*i;
    	C++;
    	if (j>r) break;
    	C+=2;
    	if ((j<r)&(a[j+1]>=a[j])) j++;
    	C++;
        if (x>=a[j]) break;
        a[i]=a[j];
        i=j;
        M++;        
     }
     a[i]=x;
}
void HeapSort(int a[], int n) {
     int l=n/2;
     int k;
     M=C=0;
     while (l>=0) {
           Heap(a,l,n-1);
           l--;
     }
     int r=n;
     while (r>0) {
           k=a[0];
           a[0]=a[r-1];
           a[r-1]=k;
           M++;
           r--;
           Heap(a,0,r-1);
     }
}
void QuickSort(int a[], int l, int r) {
     int i=l,j=r,q,x;
     x=a[l];
     while (i<j) {
           while (a[i]<x) {i++; C++;}
           while (a[j]>x) {j--; C++;}
           C++;
           if (i<=j) {
              q=a[i];
              a[i]=a[j];
              a[j]=q;
              M++;
              i++;
              j--;
           }
     }
     C++;
     if (l<j) QuickSort(a,l,j);
     C++;
     if (i<r) QuickSort(a,i,r);     
}
int main() {
    Tspis *p;
    int i,j;
    n=15; 
    int A[1000];   
    // inc
    p=new Tspis;
    p->data=0;
    p->next=NULL;
    Q.head=p;
    Q.tail=p;   
    fillincQ(n);
    printQ(Q.head);
    printf("sum = %d, RunNumber = %d\n",sum(Q.head),RunNumber(Q.head));    
    MergeSort(Q.head);
    printQ(Q.head);
    printf("sum = %d, RunNumber = %d\n\n",sum(Q.head),RunNumber(Q.head));
    freeQ(Q.head); 
    // dec
    p=new Tspis;
    p->data=0;
    p->next=NULL;
    Q.head=p;
    Q.tail=p;   
    filldecQ(n);
    printQ(Q.head);
    printf("sum = %d, RunNumber = %d\n",sum(Q.head),RunNumber(Q.head));    
    MergeSort(Q.head);
    printQ(Q.head);
    printf("sum = %d, RunNumber = %d\n\n",sum(Q.head),RunNumber(Q.head));
    freeQ(Q.head);  
    // rand
    p=new Tspis;
    p->data=rand()%n;
    p->next=NULL;
    Q.head=p;
    Q.tail=p;   
    fillrandQ(n);
    printQ(Q.head);
    printf("sum = %d, RunNumber = %d\n",sum(Q.head),RunNumber(Q.head));    
    MergeSort(Q.head);
    printQ(Q.head);
    printf("sum = %d, RunNumber = %d\n\n",sum(Q.head),RunNumber(Q.head));
    freeQ(Q.head);    
    printf("  n  |            MergeSort        |\n");                
    printf("     |   inc   |   dec   |   rand  |\n");                    
    for (n=100;n<501;n+=100) {
        printf(" %3d |",n); 
        p=new Tspis;
        p->data=0;
        p->next=NULL;
        Q.head=p;
        Q.tail=p;   
        fillincQ(n);
        MergeSort(Q.head);
        printf(" %7d |",M+C);
        freeQ(Q.head);
        p=new Tspis;
        p->data=n;
        p->next=NULL;
        Q.head=p;
        Q.tail=p;   
        filldecQ(n);
        MergeSort(Q.head);
        printf(" %7d |",M+C);
        freeQ(Q.head); 
        p=new Tspis;
        p->data=rand()%n;
        p->next=NULL;
        Q.head=p;
        Q.tail=p;   
        fillrandQ(n);
        MergeSort(Q.head);
        printf(" %7d |\n",M+C);
        freeQ(Q.head);               
    }
    system("pause");
    initwindow(1100,700);
      int merge=0,heap=0,quick=0;
      line(0,500,1100,500);
      line(0,0,0,750);
      outtextxy(0,0,"50000");
      outtextxy(0,100,"40000");
      outtextxy(0,200,"30000");
      outtextxy(0,300,"20000");
      outtextxy(0,400,"10000");
      outtextxy(100,500,"100");
      outtextxy(200,500,"200");
      outtextxy(300,500,"300");
      outtextxy(400,500,"400");
      outtextxy(500,500,"500");  
      outtextxy(600,500,"600");  
      outtextxy(700,500,"700");  
      outtextxy(800,500,"800");  
      outtextxy(900,500,"900");  
      outtextxy(1000,500,"1000");  
      setcolor(4);
      outtextxy(0,550,"HeapSort");
      setcolor(3);
      outtextxy(0,600,"MergeSort");  
      setcolor(5);
      outtextxy(0,650,"QuickSort");                      
      for (i=3;i<1000;i++) {
          FillRand(A,i);
          HeapSort(A,i);
          setcolor(4);
          line(i-1,500-(heap/100),i,500-((M+C)/100));
          heap=M+C;
          p=new Tspis;
          p->data=rand()%i;
          p->next=NULL;
          Q.head=p;
          Q.tail=p;   
          fillrandQ(i);
          MergeSort(Q.head);
          freeQ(Q.head);   
          setcolor(3);
          line(i-1,500-(merge/100),i,500-((M+C)/100));
          merge=M+C;
          FillRand(A,i);
          M=C=0;          
          QuickSort(A,0,i-1);
          setcolor(5);
          line(i-1,500-(quick/100),i,500-((M+C)/100));
          quick=M+C;          
      }
      system("pause");
      closegraph;
}
