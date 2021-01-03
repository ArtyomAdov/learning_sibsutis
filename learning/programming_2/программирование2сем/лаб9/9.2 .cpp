#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include <math.h>
using namespace std;
int random (int n) {return rand()%10;}

typedef struct list{
	list *next;
	list *prev;
	string surname;
	int ots[4];
}spis;

void list(list *head){
	spis *p;
	int i;
	p=head->next;
	while(p!=NULL){
		cout<<"familiya "<<p->surname<<endl;
		cout<<"ocenki ";
		for(i=0;i<4;i++){
			cout<<p->ots[i]<<" ";
		}
		cout<<endl;
		p=p->next;

	}
}

int main(){
	spis *head,*tail=NULL;
	int z=4, j;
	head=new spis;
	head->prev=NULL;
	head->next=tail;
	spis *p;
		p=new spis;
		cout<<"vvedite familiu ";
		cin>>p->surname;
		srand(time(NULL));
		for(j=0;j<4;j++){
			p->ots[j]=rand()%(5-1+1)+1;
		}
		p->next=NULL;
		p->prev=head;
		head->next=p;
		tail=p;
	while(z!=0){
		p=new spis;
		cout<<"vvedite familiu ";
		cin>>p->surname;
		srand(time(NULL));
		for(j=0;j<4;j++){
			p->ots[j]=rand()%(5-1+1)+1;
		}
		p->next=NULL;
		p->prev=tail;
		tail->next=p;
		tail=p;
		z--;
	}
	list(head);
	p=head->next;
	while (p!=NULL) {
		if((p->ots[0]<3)||(p->ots[1]<3)||(p->ots[2]<3)||(p->ots[3]<3)){
			p->prev->next=p->next;
			if(p->next!=NULL)p->next->prev=p->prev;
		}
		p=p->next;
		z--;
	}
	cout <<endl;
	list (head);
	return 0;
}
