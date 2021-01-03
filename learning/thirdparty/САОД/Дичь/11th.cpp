#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <graphics.h>

using namespace std;

int A[10000000], Table[5][4], Mq=0, Cq=0;

int FillRand (int A[], int n){ 
     int i;
     for (i = 0; i < n; i++){
         A[i] = rand() % 100;
     }
} 
int QuickSort(int A[],int L,int R)
{
 int i,j,x,temp;
 x=A[L];
 Mq++;
 i=L;
 j=R;
 while (i<j)
   {
    Cq++;
    while (A[i]<x)
      {
       i++;
       Cq++;
      }
    Cq++;
    while (A[j]>x)
      {
       j--;
       Cq++;
      }
    if (i<=j)
      {
       temp=A[i];
       A[i]=A[j];
       A[j]=temp;
       Mq+=3;
       i++;
       j--;
      }
   }
 if (L<j) QuickSort(A,L,j);
 if (i<R) QuickSort(A,i,R);
}

struct spis {spis *next; union { int data; unsigned char Digit[20];};};
struct tle {spis *head; spis *tail;};

spis *DigitalSortInc(spis *&S, int L)
{
 int j,i,d;
 spis *p;
 tle Q[256];
 Mq=Cq=0;
 // инициализация очередей Q
 for (j=L;j>=0;j--)
  {
   for (i=0;i<256;i++)
    Q[i].tail=(spis *)&Q[i].head;
   p=S;
   //расстановка элементов из списка S в очереди Q по j - ой цифре 
   while (p) 
     {
      d=p->Digit[j];
      Q[d].tail->next=p;
      Q[d].tail=p; 
      p=p->next; 
     }
   p=(spis*)&S;
   // соединение очередей Q в список S 
   for (i=0;i<256;i++)
    {
     if (Q[i].tail!=(spis *)&Q[i].head) 
      {
       p->next=Q[i].head;
       p=Q[i].tail;
      }
    }
   p->next=NULL; 
  }
}

spis *DigitalSortDec(spis *&S, int L)
{
 int j,i,d;
 spis *p;
 tle Q[256];
 Mq=0;
 for (j=L;j>=0;j--)
  {
   for (i=255;i>=0;i--)
    Q[i].tail=(spis *)&Q[i].head;
   p=S;
   while (p) 
     {
      d=p->Digit[j];
      Q[d].tail->next=p;
      Q[d].tail=p; 
      p=p->next; 
     }
   p=(spis*)&S;
   
   for (i=255;i>=0;i--)
    {
     if (Q[i].tail!=(spis *)&Q[i].head) 
      {
       p->next=Q[i].head;
       p=Q[i].tail;
      }
    }
   p->next=NULL; 
  }
}

spis *SpisInc(int n)
{
 spis *head,*q;
 int i;
 head=new spis;
 head->data=5*n-rand()%5;
 head->next=0;
 for (i=1;i<n;i++)
  {
   q=new spis;
   q->data=head->data-rand()%5;
   q->next=head;
   head=q;
  }
 return head;
}
    
spis *SpisDec(int n)
{
 spis *head,*q;
 int i;
 head=new spis;
 head->data=rand()%5;
 head->next=0;
 for (i=1;i<n;i++)
  {
   q=new spis;
   q->data=head->data+1+rand()%5;
   q->next=head;
   head=q;
  }
 return head;
}
    
spis *SpisRand(int n, int t)
{
 spis *head,*q;
 int i;
 head=new spis;
 head->data=rand()%t;
 head->next=0;
 for(i=1;i<n;i++)
  {
   q=new spis;
   q->data=rand()%t;
   q->next=head;
   head=q;
  }
 return head;
}
    
void list (spis *head) 
{
   spis *p;
   p=head;
   while (p!=NULL)
   {  
    printf(" %d ",p->data);
    p=p->next;
   }
}   
int sum(spis *head) {
     if (head==NULL) return 0; else
        return (head->data+sum(head->next));
}
int RunNumber (spis *head) {
     spis *p;
     p=head;
     head=p->next;
     int c=0;
     while (head!=NULL) {
           if (head->data < p->data) c++;
           p=p->next;
           head=head->next;
     }
     return(c+1);
}
int main()
{
 int L,n=10,Mq=0;
 spis *p;
 setlocale(LC_ALL,"rus");
 printf("byte 2 or 4 - ");
 scanf("%d",&L);
 if ((L!=2)&(L!=4)) return 0;
 p=SpisRand(n,100);
 list(p);
 printf("\n");
 printf(" sum = %d, RunNumber= %d\n",sum(p),RunNumber(p));
 DigitalSortInc(p,L);
 list(p); 
 printf("\n"); 
 printf(" sum = %d, RunNumber= %d\n\n",sum(p),RunNumber(p));
 p=SpisRand(n,100);
 list(p);
 printf("\n"); 
 printf(" sum = %d, RunNumber= %d\n",sum(p),RunNumber(p)); 
 DigitalSortDec(p,L);
 list(p);
 printf("\n");  
 printf(" sum = %d, RunNumber= %d\n\n",sum(p),RunNumber(p)); 
 int cur,prev,qtime;
 n=10000000;
 FillRand(A,n);
 cur=prev=GetTickCount();
 QuickSort(A,0,n-1);
 cur=GetTickCount();
 qtime=cur-prev;
 printf("QuickSort %d - msec\n",qtime);
 int k=100,l=2;
 while (k<100000000) {
        prev=GetTickCount();
        p=SpisRand(n,k);
        DigitalSortInc(p,l);
        cur=GetTickCount();
        printf("%d - %d msec\n",l,cur-prev);
        l++;
        k*=10;
 }
 system("pause");
}
