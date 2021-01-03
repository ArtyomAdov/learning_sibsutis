#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

using namespace std;
struct record
{
	char FIO[32];
	char street[18];
	short int house;
	short int flat;
	char date[10];
} tvk;

typedef struct list{
	list *next;
	tvk *datal;
} ocher;

ocher *p, *head,*tail,*k;
void add(tvk **b,int m,int srh)
{
	int i;
	tail=(ocher*)&head;
	for(i=m;b[i]->sum<=srh;i++)
	{
		p=new ocher;
		p->datel=b[i];
		tail->next=p;
		tail=p;
		if(i==3999)
			break;
	}
	p->next=NULL;
}

struct spis {
	char FIO[32];
	char street[18];
	short int house;
	short int flat;
	char date[10];
	char key[7];
	spis *next;
};

void swap(tvk *&b1,tvk *&b2)
{
	tvk *t;
	t=b1;
	b1=b2;
	b2=t;

}

int sravn(tvk *sr1,tvk *sr2)
{
	if(sr1->street<sr2->street) return 1;
	if(sr1->street>sr2->street) return 0;
	if(sr1->date[6]<sr2->date[6])return 1;
	if(sr1->date[6]>sr2->date[6])return 0;
	if(sr1->date[7]<sr2->date[7])return 1;
	if(sr1->date[7]>sr2->date[7])return 0;
	if(sr1->date[3]<sr2->date[3])return 1;
	if(sr1->date[3]>sr2->date[3])return 0;
	if(sr1->date[4]<sr2->date[4])return 1;
	if(sr1->date[4]>sr2->date[4])return 0;
	if(sr1->date[0]<sr2->date[0])return 1;
	if(sr1->date[0]>sr2->date[0])return 0;
	if(sr1->date[1]<sr2->date[1])return 1;
	if(sr1->date[1]>sr2->date[1])return 0;
	return 0;
}

void QuickSort(int **b, int l, int r) {
     int i=l,j=r;
     tvk *x=b[l];
     while (i<=j) {
     	   x=b[l]; i=l; j=r;
           while (sravn(b[i],x)) i++;
           while (sravn(x,b[j]) j--;
           if (i<=j) {
             swap (b[i],b[j]);
              i++;
              j--;
           }
           if (j-l>r-i)
           {
           	  qs(b,l,j);
           	  r=j;
           }
           else
           {
           	qs (b,l,j);
           	l=i;
           }
     }
     
 void search (tvk **A, int N, int X,int &m, int &flag)
{
     int L,R;
     flag=0; L=0; R=N-1;
     while (L<R)
    { 
           m=(L+R)/2;
           if (A[m]->date<X) L=m+1;
           else R=m;
     }
     if (A[R]->date==X) flag=1;
}    
