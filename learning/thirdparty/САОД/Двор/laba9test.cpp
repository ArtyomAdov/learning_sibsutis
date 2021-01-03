//#include <cstdlib>
//#include <iostream>
//#include <math.h>
//#include <conio.h>
//#include <io.h>
//#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct spis {
    int el;
    spis *next;
};

void Fillochereddec(spis *head,int n){
      int k=n; spis *p,*tail=head;
   

     while (n){p=new spis;p->el=k-n+1;n--;p->next=tail->next;tail->next=p;}
     //for(p=head->next;p;p=p->next){printf("\n %d",p->el);}
     }
     void Fillocheredinc(spis *head,int n){
      int k=n; spis *p,*tail=head;
     while (n){p=new spis;p->el=n;n--;p->next=tail->next;tail->next=p;}
     }
     void Fillocheredrand(spis *head,int n){
      srand((unsigned int) time(NULL));
      int k=n; spis *p,*tail=head;
     while (n){p=new spis;p->el=rand()%1000;n--;p->next=tail->next;tail->next=p;}
     }
      void Fillstekdec(spis *head,int n){
      int k=n; spis *p,*tail=head;
     while (n){p=new spis;p->el=n;n--;p->next=NULL;tail->next=p;tail=p;}
     }
     void Fillstekrand(spis *head,int n){
      srand((unsigned int) time(NULL));
      int k=n; spis *p,*tail=head;
     while (n){p=new spis;p->el=rand()%1000;;n--;p->next=NULL;tail->next=p;tail=p;}
     }
     void Fillstekinc(spis *head,int n){
      int k=n; spis *p,*tail=head;
     while (n){p=new spis;p->el=k-n+1;n--;p->next=NULL;tail->next=p;tail=p;}
     }
     int contrsumma(spis *head, int n){
         spis *p;int lol=0;
         p=head->next;
         while(n){lol=lol+p->el;n--;p=p->next;}
         return lol;
         }
         
         
         int seriivspiske(spis *head)
         {
         spis *p;int lol=1;
         p=head->next;
         while(p->next){if((p->el)<(p->next->el))lol++;p=p->next;}
         return lol;
         }
         void udalitspisok(spis *head){
              spis *p,*t;
              p=head->next;
              while(p){t=p;p=p->next;delete t;t=NULL;}
              }
              void raspechatatspisok(spis *head){
                   spis *p;
                   
                   for(p=head->next;p;p=p->next){printf("\n %d",p->el);}
                   }
int main(){
    spis *head=NULL,*p=NULL,*tail=NULL;
     head=new spis;
      head->next=NULL;tail=head;
    
   //
Fillstekdec(head,10);
    //for(p=head->next;p;p=p->next){printf("\n %d",p->el);}
    //int k;k=serii(head);
    //printf("\n %d ",k);
    raspechatatspisok(head);
    system("PAUSE");
    }
