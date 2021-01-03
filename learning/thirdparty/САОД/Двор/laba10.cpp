#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<graphics.h>
int M = 0, C = 0;
struct spis {   
    spis *next;
    int el;
};
struct tle {
    spis *head; 
	spis *tail;
};



void Fillocheredinc(spis *head,int n){
      int k=n; spis *p,*tail=head;
     while (n){p=new spis;
     p->el=n;
     n--;
     p->next=tail->next;
     tail->next=p;}
     }
     
     
     void Fillochereddec(spis *head,int n){
      int k=n; spis *p,*tail=head;
   

     while (n){p=new spis;p->el=k-n+1;n--;p->next=tail->next;tail->next=p;}
     //for(p=head->next;p;p=p->next){printf("\n %d",p->el);}
     }
void Fillocheredrand(spis *head,int n){
      srand((unsigned int) time(NULL));
      int k=n; spis *p,*tail=head;
     while (n){p=new spis;p->el=rand()%1000;n--;p->next=tail->next;tail->next=p;}
     }
     
     void raspechatatspisok(spis *head){
                   spis *p;
                   
                   for(p=head->next;p;p=p->next){printf("\n %d",p->el);}
                   }







void separate(spis* S,spis* &a,spis* &b,int &n){
     spis *p,*q;
     a=S;
     //printf("%d",S->next->el);
     b=S->next;
     n=1;
     p=a;q=b;
     while(q!=NULL){n++;p->next=q->next;p=q;q=q->next;}
     }




void sliv(spis* &a,int &q,spis* &b,int &r,tle* c){

     while((q!=0)&&(r!=0)){
     if(a->el <= b->el){
              (*c).tail->next=a;
     (*c).tail=a;
     a=a->next;
     q--;}
     else 
     {
          (*c).tail->next=b;
     (*c).tail=b;
     b=b->next;
     r--;
     }
     }
     while(q>0){(*c).tail->next=a;
     (*c).tail=a;
     a=a->next;
     q--;}
     while(r>0){
                (*c).tail->next=b;
     (*c).tail=b;
     b=b->next;
     r--;}
     }
     
     
     void mergesort(spis* &S){
          int m,n;
          spis *a,*b;
          tle c[2];
          int p,q,r,i;
      separate(S,a,b,n);
      p=1;
      while (p<n){
            c[0].head=NULL;c[1].head=NULL;
      c[0].tail=(spis *)&c[0].head;
      c[1].tail=(spis *)&c[1].head;
      
      i=0;
      m=n;
         while(m>0){
                    if (m>=p)q=p; else q=m;
         m-=q;
         if(m>=p)r=p; else r=m;
         m-=r;
         

         sliv(a,q,b,r,&c[i]);
      
i=1-i;
}
a=c[0].head;
b=c[1].head;
p=2*p;
}
c[0].tail->next=NULL;
S=c[0].head;
          }
     spis *Spis_rand(int n) {
	int i;
	spis *p = NULL, *head = NULL;
	for(i = 1; i < (n + 1); i++) {
		p = new spis;
		p->el = rand()%100;
		p->next = head;
		head = p;
	}
	return head;
}
     
     
     int main(){
         
//for (int i=100;i<501;i=i+100 ){
    struct spis *q;
         //q = Spis_rand(500);
  spis *head=NULL;
     //head=new spis;
      //head->next=NULL;
    
    
    
    //int i=500;
    //q = Spis_rand(i);

//Fillocheredrand(head,i);
int t;t=0;M=0;C=0;
       Fillocheredinc(head,10);
       raspechatatspisok(head);
      //mergesort(q);
      t=M+C;
      //printf("%d ",t);
      //raspechatatspisok(head);
      //}
  //1268 2902 4922 6650 8366 merge
  //2084 4778 7650 10780 13869 heap
  //1464 3233 5398 7600 10074 quick
  /*initwindow(1000, 800);
     setcolor(15);
      moveto(0, 800);
      outtextxy(600,400,"heapsort");
      lineto(200,675);
     lineto(400,539);
     lineto(600,339);
     lineto(800,173);
     lineto(1000,0);
     setcolor(14);
      moveto(0, 800);
      outtextxy(900,400,"merge");
     lineto(200,725);
     lineto(400,631);
     lineto(600,515);
     lineto(800,412);
     lineto(1000,313);
     setcolor(13);
     moveto(0, 800);
      outtextxy(750,400,"quick");
      lineto(200,713);
     lineto(400,614);
     lineto(600,487);
     lineto(800,360);
     lineto(1000,214);*/
  
  
system("PAUSE");
}
