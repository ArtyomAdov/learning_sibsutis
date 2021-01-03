#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <IO.H>
#include <FCNTL.H>
#include <math.h>

using namespace std;

int index[4000];
struct qel * LoadMem();
int Devide(qel* &s, qel* &a, qel* &b);

struct queue {
	   int index;
	   struct queue *next;
} *headq=NULL,*tailq,*spis;


struct Record
{
	char fio[32];
	char street[18];
	short int house;
	short int flat;
	char hd[10];	
};

struct qel{
	   struct qel *next;
	   struct Record *date;
};

struct Record *el[3999];

struct queueS {
	   qel *head;
	   qel *tail;
};



struct qel * LoadMem(){ 
	   int i=0, j, f;
	   struct qel *head,*p,*tail;

	   printf("\n  Base is loading...\n");

	   f = open("testBase4.dat", O_RDONLY | O_BINARY);
       head=NULL;
       tail=head;
       while (!eof(f)){
             p = (struct qel *)malloc(sizeof(struct qel));
		     if (p==NULL){
			    printf("\n  ERROR: Out of Memory");
			    getch();
		        exit(0);
             }
             p->date = (struct Record *)malloc(sizeof(struct Record));
		     if (p->date==NULL){
			    printf("\n  ERROR: Out of Memory");
			    getch();
			    exit(0);
		     }
			read(f, p->date,sizeof(struct Record));

			p->next=NULL;
	        if (head!=NULL) tail->next=p;
	        else head=p;
			tail=p;
			i++;
	   }
	   close(f);
	   printf("\n  Base was loaded\n");
       return(head);
}

void info(){
     printf("\n");
	 printf("  [ 1 ] Print base\n");
	 printf("  [ 2 ] Sort base\n");
	 printf("  [ 3 ] Search in base\n");
	 printf("  [ESC] Exit\n");
}


void ViewBase(struct Record **el,int iN){
     int i,j,end;
     char key;
     j=0;
     do {
         if (iN>=20*(j+1)) end=20*(j+1);
         else end=iN;
         for (i=20*j;i<end;i++){
             printf("\n%4d|",index[i]+1);
             printf("%32s",el[index[i]]->fio);
             printf("|%18s ",el[index[i]]->street);
             printf("|%d ",el[index[i]]->house);
             printf("|%3d ",el[index[i]]->flat);
             printf("|%10s|",el[index[i]]->hd);
             printf("\n");
         }
         printf("\n  ESC - back to menu, arrow down - following entries,");
         key=getch();
         if ((key==80)&&((j+1)*3<iN)){ j++; } 
         else {
                break;
            }
     } while(key!=27);
}


int Devide(qel* &s, qel* &a, qel* &b){
	qel *k,*p;
	int n;
    	
	a=s;
	b=s->next;
	
	n=1;
	k=a;
	p=b;
    while (p){
		  n++;
	      k->next=p->next;
		  k=p;
		  p=p->next;
	}
	return n;
}

void InvertDate(char aDate[],int n){
     char a[n];
     int i=0, j=n-2;
     while (i<n){
           a[i]=aDate[j];
           a[++i]=aDate[j+1];
           a[++i]='-';
           i++;
           j=j-3;
     }
     for (i=0;i<n;i++) aDate[i]=a[i];
}

/*
int compare(qel *sr1,qel *sr2)
{
	if(sr1->date->hd<sr2->date->hd) return 1;
	if(sr1->date->hd>sr2->date->hd) return 0;
	if(strcmp(sr1->date->street,sr2->date->street)<0) return 1;
	if(strcmp(sr1->date->street,sr2->date->street)>0) return 0;
	return 0;
	
}
*/
void swap(qel *&b1,qel *&b2)
{
	qel *t;
	t=b1;
	b1=b2;
	b2=t;

}




int compare(qel *sr1,qel *sr2){	
	if(sr1->date<sr2->date)return 1;
	if(sr1->date>sr2->date)return 0;
	if(sr1->date<sr2->date)return 1;
	if(sr1->date>sr2->date)return 0;
	if(sr1->date<sr2->date)return 1;
	if(sr1->date>sr2->date)return 0;
	if(sr1->date<sr2->date)return 1;
	if(sr1->date>sr2->date)return 0;
	if(sr1->date<sr2->date)return 1;
	if(sr1->date>sr2->date)return 0;
	if(sr1->date<sr2->date)return 1;
	if(sr1->date>sr2->date)return 0;
	if (strcmp(sr1->date->street,sr2->date->street)<0) return 1;
	else return 0;
}

int compare2(qel *sr1, qel *sr2){	
	if(sr1->date<sr2->date)return 1;
	if(sr1->date>sr2->date)return 0;
	if(sr1->date<sr2->date)return 1;
	if(sr1->date>sr2->date)return 0;
	return 2;
}

qel* QuickSort(qel **b, int first, int last){
int t,i,j;
struct record *p;
while(first<last){
qel *x=b[i];
i=first; j=last;	
	while (i<=j){
   	while (compare(b[i],x)) i++;
	while (compare(x,b[j])) j--;
	if (i<=j) {
	swap (b[i], b[j]);
	i++;
	j--;
    }
}
    /*if (j-first<i-last){ compare(b,i,last); last=j;}
	else {compare(b,first,j); first=i;} */
	/*if (j-first > last-i)
		{
			compare(b, i, last);
		last=j;
		}
		else
		{
			compare(b, first, j);
			first =i;
		} */
/*		if (j-first<last-i){ compare(b,i,last); last=j;}
	else {Q(b,first,j); first=i;} 
}
}
*/



/*

qel* QuickSort(qel **b, int first, int last)
{
    int i = first, j = last;
	qel *x=b[first];
    while(first<last)
	{
		
		x=b[first];i = first, j = last;
		while (i<=j)
		{
			while (compare(b[i], x)) i++;
			while (compare(x,b[j])) j--;
			if(i <= j)
			{
           			swap(b[i],b[j]);
					i++;
					j--;
			}
		}
		if (j-first > last-i)
		{
			QuickSort(b, i, last);
		last=j;
		}
		else
		{
			QuickSort(b, first, j);
			first =i;
		}
	}
}
 */
// поиск

int BinSearch(struct Record **x,int N,int *pointers,char *key){
		int m,L,R;
		int i; char y[2];
		L=0;
		R=N;
		while(L<R){
				m=(L+R)/2;
				for(i=0;i<2;i++) y[i]=x[pointers[m]]->hd[i+6];
				if (strncmp(y,key,2)<0) L=m+1;
				else R=m;
		}
      for(i=0;i<2;i++) y[i]=x[pointers[R]]->hd[i+6];	
		if(strncmp(y,key,2)==0)return R;
		else return -1;
}

void FreeQueue(queue *p){
     queue *q;
     while (p!=NULL){
           q=p;
           p=p->next;
           free(q);
     }
     p=NULL;
}

void MakeQueue(char *n,struct queue *pq,int *index,int pos){
     char y[2];
     headq=NULL;
     while (1){
           for (int i=0;i<2;i++) y[i]=el[index[pos]]->hd[i+6];
           if (strncmp(y,n,2)!=0) break;
           pq = (queue *)malloc(sizeof(queue));
           pq -> next = NULL;
           pq -> index = index[pos];
           if (headq != NULL) tailq -> next = pq;
           else
           headq = pq;
           tailq = pq;
           pos++;
           if(pos==4000)break;
     }

}

void PrintQueue(struct queue *p){
	 while (p!=NULL){
             printf("|%32s",el[p->index]->fio);
             printf("|%18s ",el[p->index]->street);
             printf("|%d ",el[p->index]->house);
             printf("|%3d ",el[p->index]->flat);
             printf("|%10s|",el[p->index]->hd);
             printf("\n");
           p=p->next;                
	 }
}

int main()
{
   int i;
     char ch;
     struct qel *head,*tail,*p;
     head=LoadMem();
     printf("\n  Press any key to back to menu...");
     getch();
     getch();
     for (i=0;i<=3999;i++) index[i]=i;
     i=0;
     for (p=head;p!=NULL;p=p->next) el[index[i++]]=p->date;
     while (1){
           system("cls");
           info();
           ch=getch();
           
           switch (ch){
                   
            case '1':
                system("cls");
                printf("\n  BASE  \n");
                ViewBase(el,i);
                printf("\n  THE END OF BASE  \n");
                printf("\n  Press any key to back to menu...");
                getch();
                break;
                
            case '2':
                system("cls");
                i=0;
          	    qel *q;
                for (p=QuickSort(&head,0,3999);p!=NULL;p=p->next)
                {
                    el[index[i++]]=p->date;
 	            }  
 	            // QuickSort(&head,0,3999);
                printf("\n  Base was sorted");
                printf("\n  Press any key to back to menu...");
                getch();
                break;
                
            case '3':
                system("cls");
                printf("\n  Enter search key (format 'yy'): ");
                char x[2];
                int y;
                scanf("%s",x);
                y=BinSearch(el,3999,index,x);
                system("cls");
                if (y==-1){ printf("  Element not found");getch();break; }
                FreeQueue(spis);
                MakeQueue(x,spis,index,y);
                spis=headq;
                printf("\n  QUEUE  \n");
                PrintQueue(spis);
         	    printf("\n  THE END OF QUEUE  \n");
         	    printf("\n  Press any key to back to menu...");
                getch();
                break;
            case 27:
                exit(0);
        }

        

}
}
