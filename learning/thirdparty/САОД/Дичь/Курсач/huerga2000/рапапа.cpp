#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <stdio.h>
//irin.klimova@gmail.com
using namespace std;
const int n=4000;

struct srec {  // Структура, используемая при построении очереди из элементов
    char fio[32];
	char street[18];

	short int d;
	short int kv;
		char data[10];	
    srec *next;
};



struct record // Запись, используемая для работы с базой данных
{
	char fio[32];
	char street[18];
   
	short int d;
	short int kv;
	 char data[10];
	
};




int sravn(struct record *inx1, struct record *inx2){	
	if(inx1->data[6]<inx2->data[6])return 1;
	if(inx1->data[6]>inx2->data[6])return 0;
	if(inx1->data[7]<inx2->data[7])return 1;
	if(inx1->data[7]>inx2->data[7])return 0;
	if(inx1->data[3]<inx2->data[3])return 1;
	if(inx1->data[3]>inx2->data[3])return 0;
	if(inx1->data[4]<inx2->data[4])return 1;
	if(inx1->data[4]>inx2->data[4])return 0;
	if(inx1->data[0]<inx2->data[0])return 1;
	if(inx1->data[0]>inx2->data[0])return 0;
	if(inx1->data[1]<inx2->data[1])return 1;
	if(inx1->data[1]>inx2->data[1])return 0;
	if (strcmp(inx1->street,inx2->street)<0) return 1;
	else return 0;
}

int sravn2(char *inx1, char *inx2){	
	if(inx1[6]<inx2[0])return 1;
	if(inx1[6]>inx2[0])return 0;
	if(inx1[7]<inx2[1])return 1;
	if(inx1[7]>inx2[1])return 0;
	return 2;
}

void sort (struct record **inx, int l, int r){ // СОРТИРОВОЧКА
int t,i,j;
struct record *p;
struct record *x;
while(l<r){
x=inx[l]; i=l; j=r;	
	while (i<=j){
   	while (sravn(inx[i],x)) i++;
	while (sravn(x, inx[j])) j--;
	if (i<=j) {
	p=inx[i];
	inx[i]=inx[j];
	inx[j]=p;
	i++;
	j--;
    }
}
    if (j-l<r-i){ sort(inx,i,r); r=j;}
	else {sort(inx,l,j); l=i;} 
}
}



void search(struct record **inx, int n)	{ // ПОИСК
		int l=0,r=n-1,m,i;
		char k[2];
		srec *p,*pp,*head;
	
	puts("Search key:");
	scanf("%s",k);
		
	while(l<r){
	 m=(l+r)/2;
	 	if (sravn2(inx[m]->data,k)==1) l=m+1;
        	else r=m;
		}
if (sravn2(inx[r]->data,k)==2) printf("!");
 	 if (sravn2(inx[r]->data,k)==2) {
                                      p=new srec; head=p;
                                      for (i=0; i<32; i++)head->fio[i]=inx[r]->fio[i];
                                      for (i=0; i<18; i++) head->street[i]=inx[r]->street[i];
	                                  for (i=0; i<10; i++) head->data[i]=inx[r]->data[i];
									  head->kv=inx[r]->kv; head->d=inx[r]->d;
									  
		while ((++r<n)&&(sravn2(inx[r]->data,k)==2)) {	pp=new srec;p->next=pp; p=pp; 
	                                 for (i=0; i<32; i++)p->fio[i]=inx[r]->fio[i];
                                      for (i=0; i<18; i++) p->street[i]=inx[r]->street[i];
	                                  for (i=0; i<10; i++) p->data[i]=inx[r]->data[i];
									  p->kv=inx[r]->kv; p->d=inx[r]->d;}
									  p->next=NULL;
							
					for (p=head; p; p=p->next)  printf("%s %s %d %3d %s\n",p->fio,p->street,p->d,p->kv,p->data);}
		
	else printf("Not found!\n");

getch();
}	
	
void print(struct record **inx, int n){
	 
	for(int i=0; i<n; i++){
printf("%4d) %s %s %d %3d %s\n",i+1,inx[i]->fio,inx[i]->street,inx[i]->d,inx[i]->kv,inx[i]->data);
if ((i+1)%20==0){puts("To exit press Esc"); if (getch()==27) break;}}
}
	
int main()
{  record *inx[n];
  int i,m,f=1;
  srec *p,*head,*pp;
	FILE *fp;
	record mas[n];
	fp=fopen("testBase4.dat", "rb");
    i=fread((record *)mas, sizeof(record), n, fp); 
    for(int i=0;i<n; i++)
    inx[i]=&mas[i];

    
    
    while(1){
	system("cls");
    puts("Select void:\n1-Print\n2-Sort\n3-Search\n4-Exit");
    scanf("%d",&m);
    switch (m) {
case 1:system("cls"); print(inx,n);
break;
case 2:sort(inx,0,n-1); f=3;
break;
case 3:system("cls"); if (f!=3){ puts("Sorting was not performed!"); getch();}
                          else search(inx,n);
break;
case 4: return 4;
break;
default: puts("Error");
break;
}}
    
	
}
