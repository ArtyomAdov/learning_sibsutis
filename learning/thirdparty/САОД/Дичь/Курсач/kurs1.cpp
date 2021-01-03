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
qel* MergeSort(qel* s);

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

char compare(char aDate[],char bDate[],char aStreet[],char bStreet[],int n, int m){
     char a[n], b[n],d[m], e[m];; int i;
     for (i=0;i<n;i++){
         a[i]=aDate[i];
         b[i]=bDate[i];
         }
     InvertDate(a,n);
     InvertDate(b,n);
     for (i=0;i<n;i++){
         if(a[i]>b[i])return 2;
         else if(a[i]<b[i])return 1;
     }
        for (i=0;i<m;i++){
            d[i]=aStreet[i];
            e[i]=bStreet[i];
        }
        if  (strcmp(aStreet,bStreet) < 0) return 1;
        else if (strcmp(aStreet,bStreet) > 0) return 2;
     return 1;
}

void Merging(qel* &a, qel* &b, queueS &c, int q, int r){
	 qel *p;
	
	 while ((q!=0)&&(r!=0)){ 
		   if (compare(a->date->hd,b->date->hd,a->date->street,b->date->street,8,18) == 1){
			  p=a;
			  a=a->next;
			  p->next=NULL;            
			  if (c.head) c.tail->next=p;
			  else c.head=p;
			  c.tail=p;
			  q--;
		   }
		   else{
			    p=b;
			    b=b->next;
			    p->next=NULL;      
			    if (c.head) c.tail->next=p;
			    else c.head=p;
			    c.tail=p;
			    r--;
           }
     }
	 while (q>0){
		   p=a;
		   a=a->next;
	       p->next=NULL;
		   if (c.head) c.tail->next=p;
		   else c.head=p;
		   c.tail=p;
		   q--;
     }
	 while (r>0){
		   p=b;
		   b=b->next;
		   p->next=NULL; 
		   if (c.head) c.tail->next=p;
		   else c.head=p;
		   c.tail=p;
		   r--;
	 }
}

qel* MergeSort(qel* s){
	 int n,p,q,r,m,i;
	 struct queueS Cs[2];
	 struct qel *a,*b;
	 n=Devide(s,a,b);
	 p=1;
	 while (p<n){
		   Cs[0].head=NULL;
		   Cs[1].head=NULL;
		   Cs[0].tail=Cs[0].head;
		   Cs[1].tail=Cs[1].head;
		   i=0;
		   m=n;
		   while (m>0){
			     if (m>=p) q=p;
			     else q=m;
			     m-=q;
			     if (m>=p) r=p;
			     else r=m;
			     m-=r;    
			     Merging(a,b,Cs[i],q,r);
			     i=1-i;
           } 
	       a=Cs[0].head;
	       b=Cs[1].head;
		   p*=2;
     }
	 Cs[0].tail->next=NULL;
	 return Cs[0].head;
}

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
                for (p=MergeSort(head);p!=NULL;p=p->next)
                {
                    el[index[i++]]=p->date;
 	            }
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
