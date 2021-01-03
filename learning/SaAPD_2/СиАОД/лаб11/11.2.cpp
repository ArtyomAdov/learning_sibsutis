#include <stdio.h>
#include <stdlib.h>
int n;
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
int main(){
    int i,j;
    n=15;    
    FillIncQ(n);
    PrintQ(Q.head);
    printf("sum = %d, \nRunNumber = %d\n",sum(Q.head),RunNumber(Q.head));
    FreeQ(Q.head); 
    FillDecQ(n);
    PrintQ(Q.head);
    printf("sum = %d, \nRunNumber = %d\n",sum(Q.head),RunNumber(Q.head));
    FreeQ(Q.head);  
    FillRandQ(n);
    PrintQ(Q.head);
    printf("sum = %d, \nRunNumber = %d\n",sum(Q.head),RunNumber(Q.head)+1);  
    FreeQ(Q.head);
    return 0;
}
