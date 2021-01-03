#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int M=0,C=0;
struct spis {
    spis *next;
    union {
        int el;
        unsigned char Digit[4];
    };
};
struct spisfamil {
    spisfamil *next;
    char str[25];
};


struct tle {
    spis *head; 
	spis *tail;
};
struct tles {
    spisfamil *head; 
	spisfamil *tail;
};
void Fillocheredrand(spis *head,int n){
      srand((unsigned int) time(NULL));
      int k=n; spis *p,*tail=head;
     while (n){
     p=new spis;
     p->el=rand()%100000;
     n--;
     p->next=tail->next;
     tail->next=p;}
     }
     void raspechatatspisok(spis *head){
                   spis *p;
                   
                   for(p=head->next;p;p=p->next){printf("\n %d",p->el);}
                   }
void raspechatatspisokfamil(spisfamil *head){
                   spisfamil *p;
                   
                   for(p=head;p;p=p->next){printf("\n %s",p->str);}
                   }

void digitsortdcp(spis* &S){
     spis *p;
tle c[10];
int d,k=10,i;int r=0,d1,z;
for (int j=4;j>0;j--) {
    
    for (i=0;i<10;i++){ c[i].tail=(spis*)&c[i].head;}
    p=S;
    while (p){d1=(p->el);for(z=r;z>0;z--){d1=d1/10;}d=d1%10;c[d].tail->next=p;c[d].tail=p;p=p->next;}r++;//printf("kek");
    p=(spis *)&S;
    for (i=0;i<10;i++) {if(c[i].tail!=(spis*)&c[i].head){p->next=c[i].head;p=c[i].tail;}}
    
    p->next=NULL;
    
    }
}

void digitsortinc(spis* &S){
     spis *p;
tle c[256];
int d,k=10,i;int r=0,d1,z;
for (int j=0;j<4;j++) {
    
    for (i=0;i<256;i++){ c[i].tail=(spis*)&c[i].head;M++;}
    p=S;
    while (p){d = int(p->Digit[j]);c[d].tail->next=p;c[d].tail=p;p=p->next;M=M+2;}r++;//printf("kek");
    p=(spis *)&S;
    for (i=0;i<256;i++) {if(c[i].tail!=(spis*)&c[i].head){p->next=c[i].head;p=c[i].tail;M=M+2;}}
    
    p->next=NULL;
    
    }
}
void digitsortdec(spis* &S){
     spis *p;
tle c[256];
int d,k=10,i;int r=0,d1,z;
for (int j=0;j<4;j++) {
    
    for (i=255;i>=0;i--){ c[i].tail=(spis*)&c[i].head;}
    p=S;
    while (p){d = int(p->Digit[j]);c[d].tail->next=p;c[d].tail=p;p=p->next;}r++;//printf("kek");
    p=(spis *)&S;
    for (i=255;i>=0;i--) {if(c[i].tail!=(spis*)&c[i].head){p->next=c[i].head;p=c[i].tail;}}
    
    p->next=NULL;
    
    }
}


void DigitalSortfamil(spisfamil* &S) {
    int j, i, d;
    spisfamil *p;
    tles c[149];
    for (j = 24; j >= 0; j--) {
        for (i = 0; i < 149; i++) {
            c[i].tail = (spisfamil *) &c[i].head;
        }
        p = S;
        while (p) {
              
            d = p->str[j];
            //if ((d>=65)&&(d<=90)) {d=d+58;printf("%d ",d);}
            c[d].tail->next = p;
            c[d].tail = p;
            p = p->next;
        }
        p = (spisfamil *) &S;
        for (i = 0; i < 149; i++) {
            if (c[i].tail != (spisfamil *) &c[i].head) {
                p->next = c[i].head;
                p = c[i].tail;
            }
        }
        p->next = NULL;
    }
}




int contrsumma(spis *head, int n){
         spis *p;int lol=0;
         p=head->next;
         while(n){lol=lol+p->el;n--;p=p->next;}
         return lol;
         }
int seriivspiske(spis *head)
         {
         spis *p;int lol=1;int i=0;
         p=head->next;
         while(p->next){if((p->el)>(p->next->el)){lol++;}p=p->next;}//povtory dlia dec >=
         return lol;
         }


spisfamil *Spisfamily(int n) {
    int i,max=0,st;
    spisfamil *p = NULL, *head = NULL;
    printf("Enter surname: \n");
    for(i = 0; i < n; i++) {
        p = new spisfamil;
        scanf("%s", p->str);
        p->next = head;
        head = p;
         if (max<strlen(p->str)) 
         max=strlen(p->str);
    }
    printf("%d",max);
    p=head;
    for(i = 0; i < n; i++) {st=strlen(p->str); {for(int j=st;j<25;j++)p->str[j]=0;}p=p->next;}
    
    return head;
}



void quicksort(int *A,int l,int r){
int x,t,i,j;

M++;x=A[(l+r)/2];i=l;j=r;
while (i<=j){
      C++;while(A[i]<x){C++;i++;}
      C++;while(A[j]>x){C++;j--;}
      if(i<=j)
      {M=M+3;t=A[i];A[i]=A[j];A[j]=t;i++;j--;}
      }
      if(l<j) {quicksort(A, l, j);}
      if(i<r) {quicksort(A, i, r);}
      }
      
      void Fillrand(int n,int *A){
int i,b=0;
srand((unsigned int) time(NULL));
for (i=0;i<n;i++) A[i]=rand()%100;
}
int main(){int j,S,serii,n=5,A[1000];
     
   spis *head=NULL;
     head=new spis;
      head->next=NULL; 
      
      spisfamil *q=NULL;
     q=new spisfamil;
      q->next=NULL; 
    Fillocheredrand(head,500);
    //S=contrsumma(head,100);
    //printf("contr summa do %d\n",S);
  //M=0;
    //digitsortinc(head->next);
    
    //printf("%d ",M);
    //Fillrand(500,A);
    //M=0;
   //quicksort(A,0,499);
    //M=M+C;
    //printf("%d ",M);
    //raspechatatspisok(head);
    //S=contrsumma(head,100);
    //serii=seriivspiske(head);
   // printf("contr summa posle %d \n",S);
   // printf("serii %d",serii);
   
    q = Spisfamily(5);
   DigitalSortfamil(q);
   raspechatatspisokfamil(q);
    system("PAUSE");
    }
