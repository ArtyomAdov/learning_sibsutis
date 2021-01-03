#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>
using namespace std;
int random (int n) {return rand()%10;}

typedef struct st { 
	string surname;
	int ots[4];
    struct st *next;
}spis;

spis *create(void){
	spis *p, *pred, *h;
	int j, z=4;
	srand(time(NULL));
	h=pred=new spis;
	pred->surname="adov";
	for(j=0;j<4;j++){
		pred->ots[j]=rand()%(5-1+1)+1;
	}
	do{
		p=new spis;
		cout<<"vvedite familii\n ";
		cin>>p->surname;
		for(j=0;j<4;j++){
			p->ots[j]=rand()%(5-1+1)+1;
		}
		pred->next=p;
		pred=p;
		z--;
	} while(z!=0);
	p->next=NULL;
	return h;
}

void list(spis *head){
	spis *p;
	int i;
	p=head;
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

spis *sort_list(spis *head){
	spis *t, *m, *a, *b;
	if(head == NULL)
        return NULL;
	for(int i = 0;i<6;i++){
        a  = t = head;
        b  = head->next;
 
        while(b != NULL){
            if(a->surname > b->surname){
                if(t == a)
                    head = b;
                else
                    t->next = b;
 
                a->next = b->next;
                b->next = a;
 
                m  = a;
				a = b;
				b = m;
            }
            t = a;
            a = a->next;
            b = b->next;
        }
    }
    return head;
}

int main(){
	int i, j, k[4];
	spis *head;
	head=create();
	list (head);
	head=sort_list(head);
	cout<<endl;
	cout<<"otsortirovaniy spisok"<<endl;
	list (head);
	return 0;
}
