#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <iostream>
#include <time.h>

using namespace std;

struct node{
	int data;
	node *next;
};

class spisok{
	protected:
		node *head;
		static int Sum;
		static int kol;
	public:
		spisok():head(NULL){
		}
		spisok(int A[], int N):head(NULL){
			create(A,N);
		}
		
		void create(int A[], int N){
			int i;
			node *pred, *p;
			pred=new node;
			pred->data=A[0];
			head=pred;
			if(N==1) pred->next=NULL;
			for(i=1;i<N;i++){
				p=new node;
				p->data=A[i];
				pred->next=p;
				pred=p;
			} 
			if(N!=1)p->next=NULL;
		}
		
		void Addnode(int g){
			int i, D;
			cout<<"¬ведите номер элемента за которым хотите добавить эле-мент: ";
			cin>>i;
			if(i>g || i<1){
				throw "некоректный ввод номера элемента!";
			}
			cout<<"¬ведите элемент который хотите добавить: ";
			cin>>D;
			node *p, *h;
			p=head;
			if(p==NULL){
				h=new node;
				h->data=D;
				head=h;
			}
			if(p!=NULL){
				while(i!=1){
					p=p->next;
					i--;
				}
			h=new node;
			h->data=D;
			h->next=p->next;
			p->next=h;
			}
		}
		
		void List(){
			node *p=head;
			int i=1;
			while(p!=NULL){
				cout<<i<<") "<<p->data<<endl;
				p=p->next;
				i++;
			}
		}
		void del(int z){
			node *p, *pred;
			int i;
			p=head;
			cout<<"¬ведите номер элемента, который нужно удалить: ";
			cin>>i;
			if(i>z || i<1){
				throw "некоректный ввод номера элемента!";
			}
			if(i==1){
				head=p->next;
			}
			while(i>2){
				p=p->next;
				i--;
			}
			pred=p->next;
			if(pred->next==NULL){
				p->next=NULL;
			}
			p->next=pred->next;
		}
		
		static int getSum(spisok &H){
			int Sum=0;
			node *h;
			h=H.head;
			while(h!=NULL){
				Sum+=h->data;
				h=h->next;
			}
			return Sum;
		}

		static int getKol(spisok &H){
			int kol=0;
			node *h;
			h=H.head;
			while(h!=NULL){
				kol++;
				h=h->next;
			}
			return kol;
		}
		
		void peremeshenie(int z){
			node *h, *pred, *p, *kop;
			int i, j, k;
			cout<<"¬ведите номер элемента который хотите переместить: ";
			cin>>i;
			if(i>z || i<1){
				throw "некоректный ввод номера перемещаемого элемента!";
			}
			i++;
			cout<<"¬ведите номер элемента за который хотите переместить элемент: ";
			cin>>j;
			if(j>z || j<1){
				throw "некоректный ввод номера элемента за который перемещаем элемент!";
			}
			j++;
			p=head;
			kop=head;
			if(i==2) head=head->next;
			if(i==3){
				p=head->next;
				head->next=p->next;
			}
			while(i>3){
				p=p->next;
				i--;
			}
			if(i==3 && head->next!=p->next){
				pred=p;
				p=pred->next;
				pred->next=p->next;
			}
			if(j==1){
				p->next=head->next;
				head->next=p;
			}
			while(j>2){
				kop=kop->next;
				j--;
			}
			p->next=kop->next;
			kop->next=p;
		}
};

class ocher:public spisok{
	private:
		node *tail;
	public:
		ocher(int A[], int N):spisok(), tail(NULL){
			create(A, N);
		}
		void create(int A[], int N){
			int i;
			node *pred, *p;
			pred=new node;
			pred->data=A[0];
			head=tail=pred;
			if(N==1) pred->next=NULL;
			for(i=1;i<N;i++){
				p=new node;
				p->data=A[i];
				pred->next=p;
				pred=p;
			} 
			if(N!=1){
				p->next=NULL;
				tail=p;
			}
		}
		void Addnode(){
			int i, D;
			cout<<"¬ведите элемент который хотите добавить: ";
			cin>>D;
			node *p, *h;
			p=head;
			while(p->next!=NULL){
				p=p->next;
			}
			if(p->next==NULL){
				h=new node;
				h->data=D;
				p->next=h;
				tail=h;
			}
		}
		void del(){
			node *p, *pred;
			int i;
			p=head;
			head=p->next;
			free(p);
		}
		void peremeshenie(int z){
			node *h, *pred, *p, *kop;
			int i, j, k, ch=0;
			cout<<"¬ведите номер элемента который хотите переместить: ";
			cin>>i;
			if(i>z || i<1){
				throw "некоректный ввод номера перемещаемого элемента!";
			}
			i--;
			cout<<"¬ведите номер элемента за который хотите переместить элемент: ";
			cin>>j;
			if(j>z || j<1){
				throw "некоректный ввод номера элемента за который перемещаем элемент!";
			}
			j--;
			p=head;
			if(i==0){
				head=p->next;
			}
			cout<<head->data<<endl;
			cout<<i<<endl;
			while(i>1){
				p=p->next;
				i--;
				ch=1;
			}
			if(ch==1){
				pred=p;
				p=p->next;
				pred->next=p->next;
					if(pred->next==NULL){
					tail=pred;
				}
			}
			kop=head;
			while(j>1){
				kop=kop->next;
				j--;
			}
			p->next=kop->next;
			kop->next=p;
			if(p->next==NULL){
				tail=p;
			}
		}
};

class stek:public spisok{
	public:
		stek(int A[], int N):spisok(){
			create(A, N);
		}
		void create(int A[], int N){
			int i;
			node *pred, *p;
			pred=new node;
			pred->data=A[0];
			head=pred;
			if(N==1) pred->next=NULL;
			for(i=1;i<N;i++){
				p=new node;
				p->data=A[i];
				pred->next=p;
				pred=p;
			} 
			if(N!=1)p->next=NULL;
		}
		void Addnode(){
			int i, D;
			cout<<"¬ведите элемент который хотите добавить: ";
			cin>>D;
			node *p;
			p=new node;
			p->data=D;
			p->next=head;
			head=p;
		}
		void del(){
  			if (head!=NULL){
    		node *temp=head;
    		head = head->next;
    		free(temp);
  			}
  			else throw "—тек весь уже удалЄн!";
		}
};
