#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
using namespace std;
struct st         
    { int A;
      struct st *next;   
    };
void CheckSum(st *head){
	st *p=head;
	int m=0;
	while(p!=NULL){
		m+=p->A;
		p=p->next;
	}
	cout<<"summa  = "<<m<<endl;
}
int RunNumber(st *head){
	st *p=head;
	int m=1;
	for(p; p->next->next ;p=p->next){
		if((p->A)>(p->next->A)){
			m++;
		}
	}
	cout<<"kolichestvo seriy = "<<m<<endl;
	return m;
}
void PrintStack(st *head){
	st *p=head;
	while (p!=NULL){
	cout<<p->A<<"  ";
		p=p->next;
	}
	cout<<endl;
}
void StackDec(st *head, int n){
	int i;
	st *g;
	head->A=n;
	for(i=0; i<n; i++){
		g=new st;
		g->A=i;
		g->next=head->next;
		head->next=g;
	}
}
void StackInc(st *p, int n){
	int i;
	st *g;
	p->A=0;
		for(i=n-1; i>0; i--){
		g=new st;
		g->A=i;
		g->next=p->next;
		p->next=g;
	}
}   
void StackRand(st *head, int n){
	int i;
	st *g;
	head->A=rand()%200;
	for(i=1; i<n; i++){
		g=new st;
		g->A=rand()%200;
		g->next=head->next;
		head->next=g;
	}
}
int main(){ 
	st *h=new st;
  	h->next=NULL;
  	int c;
  	int n;
  	cout<<"vvedite kolichestvo elementov ";
  	cin>>n;
  	StackInc(h,n);
	PrintStack(h);
	RunNumber(h);
	CheckSum (h);
	h->next=NULL;
	StackDec(h,n-1);
	PrintStack(h);
	RunNumber(h);
	CheckSum (h);
	h->next=NULL;
	StackRand(h,n);
	PrintStack(h);
	RunNumber(h);
	CheckSum (h);
	return 0;
}
