//#include <cstdlib>
//#include <iostream>
//#include <math.h>
#include <conio.h>
//#include <io.h>
//#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct spis {
    int el;
    spis *next;
};

void Fillocheredinc(spis *head,int n){
      int k=n; spis *p;
   
     for(p=head->next;p;p=p->next){p->el=k-n;n--;}
     
     }
     void Fillochereddec(spis *head,int n){
      int k=n; spis *p;
   
     for(p=head->next;p;p=p->next){p->el=n;n--;}
     
     }
int main(){
    spis *head=NULL,*p=NULL,*tail=NULL;
    head=new spis;
      head->next=NULL;tail=head;
  int a=100;   
    
    while(a) {
      p=new spis;
      //p->el=a;
      
      
                //p->next=NULL;
                p->next=tail->next;
                tail->next=p;a--;
}
Fillocheredinc(head,99);
    for(p=head->next;p;p=p->next){printf("\n %d",p->el);
    }
    system("PAUSE");
    }
