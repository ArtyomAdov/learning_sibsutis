#include <stdio.h>
#include <stdlib.h>
int n;
struct Tspis {Tspis *next; int data;} *head;
Tspis *tail;
void fillinc(int n) {
     Tspis *p;
     int i;
     head->data=n;
     head->next=NULL;
     for (i=0;i<n-1;i++) {
         p=new Tspis;
         p->data=n-i-1;
         p->next=head;
         head=p;
     }
}
void fillincQ(int n) {
     Tspis *p;
     int i;
     p=new Tspis;
     p->data=1;
     p->next=NULL;
     head=p;
     tail=p;
     for (i=1;i<n;i++) {
         p=new Tspis;
         p->data=i+1;
         p->next=NULL;
         tail->next=p;
         tail=p;
     }
}
void filldec(int n) {
     Tspis *p;
     int i;
     head->data=1;
     head->next=NULL;
     for (i=1;i<n;i++) {
         p=new Tspis;
         p->data=i+1;
         p->next=head;
         head=p;
     }
}
void filldecQ(int n) {
     Tspis *p;
     int i;
     p=new Tspis;
     p->data=n;
     p->next=NULL;
     head=p;
     tail=p;
     for (i=n-1;i>0;i--) {
         p=new Tspis;
         p->data=i;
         p->next=NULL;
         tail->next=p;
         tail=p;
     }
}
void fillrand(int n) {
     Tspis *p;
     int i;
     head->data=rand()%n;
     head->next=NULL;
     for (i=0;i<n-1;i++) {
         p=new Tspis;
         p->data=rand()%n;
         p->next=head;
         head=p;
     }
}
void fillrandQ(int n) {
     Tspis *p;
     int i;
     p=new Tspis;
     p->data=rand()%n;
     p->next=NULL;
     head=p;
     tail=p;
     for (i=1;i<n;i++) {
         p=new Tspis;
         p->data=rand()%n;
         p->next=NULL;
         tail->next=p;
         tail=p;
     }
}
void printS(Tspis *t) {
     while (t!=NULL) {
           printf("%2d ",t->data);
           t=t->next;
     }
     printf("\n");
}
void printQ(Tspis *t) {
     while (t!=tail) {
           printf("%2d ",t->data);
           t=t->next;
     }
     printf("%2d ",t->data);  
     printf("\n"); 
}
void freeS(Tspis *t) {
     Tspis *p;
     while (t!=NULL) {
           p=t->next;
           delete t;
           t=p;
     }
}
void freeQ(Tspis *t) {
     Tspis *p;
     while (t!=tail) {
           p=t->next;
           delete t;
           t=p;
     }
     delete t; 
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
int main() {
    Tspis *p;
    head = new Tspis;
    n=10;
    printf("-----------------------------Stack-----------------------------\n");
    fillinc(n);
    printS(head);
    printf("sum = %2d\n",sum(head));
    printf("RunNumber = %2d\n\n",RunNumber(head));
    freeS(head->next);
    
    filldec(n);
    printS(head);
    printf("sum = %2d\n",sum(head));
    printf("RunNumber = %2d\n\n",RunNumber(head));
    freeS(head->next); 
       
    fillrand(n);
    printS(head);  
    printf("sum = %2d\n",sum(head));      
    printf("RunNumber = %2d\n",RunNumber(head));
    freeS(head);  
    
    printf("-----------------------------Queue-----------------------------\n");
    tail=new Tspis;
    fillincQ(n);
    printQ(head);
    freeQ(head->next);

    filldecQ(n);
    printQ(head);
    freeQ(head->next);    
    
    fillrandQ(n);
    printQ(head);
    freeQ(head);
    printf("------------------------------End------------------------------\n");       
    system("pause");
}
