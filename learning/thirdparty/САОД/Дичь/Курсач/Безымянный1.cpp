#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

typedef struct vklad{
char fio[30];
unsigned short int sum;
char data[10];
char fioad[22];
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
		p->datal=b[i];
		tail->next=p;
		tail=p;
		if(i==3999)
			break;
	}
	p->next=NULL;
}
int sravn(tvk *sr1,tvk *sr2)
{
	if(sr1->sum<sr2->sum) return 1;
	if(sr1->sum>sr2->sum) return 0;
	if(sr1->data[6]<sr2->data[6])return 1;
	if(sr1->data[6]>sr2->data[6])return 0;
	if(sr1->data[7]<sr2->data[7])return 1;
	if(sr1->data[7]>sr2->data[7])return 0;
	if(sr1->data[3]<sr2->data[3])return 1;
	if(sr1->data[3]>sr2->data[3])return 0;
	if(sr1->data[4]<sr2->data[4])return 1;
	if(sr1->data[4]>sr2->data[4])return 0;
	if(sr1->data[0]<sr2->data[0])return 1;
	if(sr1->data[0]>sr2->data[0])return 0;
	if(sr1->data[1]<sr2->data[1])return 1;
	if(sr1->data[1]>sr2->data[1])return 0;
	return 0;
}
void swap(tvk *&b1,tvk *&b2)
{
	tvk *t;
	t=b1;
	b1=b2;
	b2=t;

}
void qs(tvk **b, int first, int last)
{
    int i = first, j = last;
	tvk *x=b[first];
    while(first<last)
	{
		
		x=b[first];i = first, j = last;
		while (i<=j)
		{
			while (sravn(b[i], x)) i++;
			while (sravn(x,b[j])) j--;
			if(i <= j)
			{
           			swap(b[i],b[j]);
					i++;
					j--;
			}
		}
		if (j-first > last-i)
		{
			qs(b, i, last);
		last=j;
		}
		else
		{
			qs(b, first, j);
			first =i;
		}
	}
}
void search (tvk **A, int N, int X,int &m, int &flag)
{
     int L,R;
     flag=0; L=0; R=N-1;
     while (L<R)
    { 
           m=(L+R)/2;
           if (A[m]->sum<X) L=m+1;
           else R=m;
     }
     if (A[R]->sum==X) flag=1;
}
void output1(tvk *b)
{
	int i,n=0;
	char c;
	printf("              FIO              | SUMMA |    DATA    |  FIO ADVOKATA\n\n");
	while(1)
    {
	  for(i=n;i<n+20;i++)
	  {
		  printf("%30s | %5d | %10s | %22s",b[i].fio,b[i].sum,b[i].data,b[i].fioad);
		  puts("");
		  puts("_______________________________________________________________________________");
	  }
	  printf("                          Vivesti eshe 20 zapisey? \n                                    Y|N\n");
	  c=getch();
	  if(c=='y')
	  {
		  n+=20;
	  }
	  else break;
	  if(n>=4000)
		  break;

  }
}
void output2(tvk **b)
{ 
	int i,n=0;
	char c;
	printf("              FIO              | SUMMA |    DATA    |  FIO ADVOKATA\n\n");
	while(1)
  {

	  for(i=n;i<n+20;i++)
	  {

		  printf("%30s | %5d | %10s | %22s",b[i]->fio,b[i]->sum,b[i]->data,b[i]->fioad);
		  puts("");
		  puts("_______________________________________________________________________________");
	  }
	  printf("                          Vivesti eshe 20 zapisey? \n                                    Y|N\n");
	  c=getch();
	  if(c=='y')
	  {
		  n+=20;
	  }
	  else break;
	  if(n>=4000)
		  break;

  }
}
void output3(ocher *head)
{
	for(p=head;p->next;p=p->next)
		{
			printf("%30s | %5d | %10s | %22s",p->datal->fio,p->datal->sum,p->datal->data,p->datal->fioad);
			puts("");
			puts	("_______________________________________________________________________________");
		}
}
int main(){
	int i,n=0,flag=0,m,srh,k;
	FILE *f;
	tvk *vk = NULL;
	tvk **b;
	b	= (tvk **) malloc (4000 * sizeof(tvk *));
	vk = (tvk *) malloc(4000 * sizeof(tvk));
	f = fopen("testBase3.dat", "rb");
	if (f == NULL)
	{
	  printf("Could not open file: '%s'\n", "testBase3.dat");
	  exit(1);
	}
	fread(vk, sizeof(tvk), 4000, f);
	
	for(i=0;i<4000;i++)
	{
	  b[i]=&vk[i];
	}
	printf("1) Vivesti 20 zapisey neotsortirovannogo massiva\n2)Vivesti 20 zapisey otsortirovannogo massiva\n3)Poisk elementa\n");
	scanf("%d",&k);
	system ("CLS");
	switch ( k ) {
	case 1: 
		output1(vk);
		break;
	case 2: 
		qs(b,0,3999);	
		output2(b);  
		break;
	case 3: 
		printf("input finding element\n");
		scanf("%d",&srh);
		system ("CLS");
		qs(b,0,3999);
		search(b,4000,srh,m,flag);		
		add(b,m,srh);
		if(flag)
		output3(head);
		else
		{
			printf("element ne najden\n");
			break;
		}		
	default: break;
	}
 system ("PAUSE");
}
