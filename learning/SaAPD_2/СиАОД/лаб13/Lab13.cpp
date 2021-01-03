#include <fstream>
#include <iostream>
#include <stdio.h>
#include <math.h>

#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;


int QuickSort(int a[],int L,int R,int &c,int &m);

struct listName{
	listName *next;
	union{
		char lastname[20]; 
		unsigned char Digit[sizeof(lastname)];
	};
};

struct list{
	list *next;
	union{
		int num; 
		unsigned char Digit[sizeof(num)];
	};
};
struct Queue{
	list *head;
	list *tail;
};

struct QueueSpis{
	listName *head;
	listName *tail;
};

void print(list *h);
void print1(list *h);

void DigitalSort16(list* &S,int &m){ 
	m=0;
	int L=2; 
	int *KDI = new int [L];
	for(int i=0;i<L;i++){
		KDI[i]=i;
	}
	Queue c[256]; 
	list *p; 
	unsigned char d; 
	int k; 
	for(int j = L-1; j>=0; j--){ 
		for(int i = 0; i < 256; i++){ 
			c[i].tail=(list*)&(c[i].head); 
		} 
		p = S; 
		k = KDI[j]; 
		while(p != NULL){ 
			m++;
			d = p->Digit[k]; 
			c[d].tail->next = p; 
			c[d].tail=p; 
			p=p->next; 
		} 
		p = (list*)&S;
		for(int i=0;i< 256;i++){ 
			m++;
			if(c[i].tail != (list*)&(c[i].head)){ 
				p->next = c[i].head; 
				p = c[i].tail; 
			} 
		} 
		p->next = NULL; 
	} 
	
}

void DigitalSort32(list* &S,int &m){ 
	m=0;
	int L=4; 
	int *KDI = new int [L];
	for(int i=0;i<L;i++){
		KDI[i]=i;
	}
	Queue c[256]; 
	list *p; 
	unsigned char d; 
	int k; 
	for(int j = L-1; j>=0; j--){ 
		for(int i = 0; i < 256; i++){ 
			c[i].tail=(list*)&(c[i].head); 
		} 
		p = S; 
		k = KDI[j]; 
		while(p != NULL){ 
			m++;
			d = p->Digit[k]; 
			c[d].tail->next = p; 
			c[d].tail=p; 
			p=p->next; 
		} 
		p = (list*)&S;
		for(int i=0;i< 256;i++){ 
			m++;
			if(c[i].tail != (list*)&(c[i].head)){ 
				p->next = c[i].head; 
				p = c[i].tail; 
			} 
		} 
		p->next = NULL; 
	} 
	
}

int DigitalSort(int L,int n){ 
	int m=0;
	list *p; 
	for(int j = L-1; j>=0; j--){ 
		for(int i=0;i< n;i++){ 
			m++;
		}  
		for(int i=0;i< 256;i++){ 
			m++;
		} 
	}
	return m; 	
}


void DigitalSortSpis(listName* &S){ 
	int L=4; 
	int *KDI = new int [L];
	for(int i=0;i<L;i++){
		KDI[i]=i;
	}
	QueueSpis c[256]; 
	listName *p; 
	unsigned char d; 
	int k; 
	for(int j = L-1; j>=0; j--){ 
		for(int i = 0; i < 256; i++){ 
			c[i].tail=(listName*)&(c[i].head); 
		} 
		p = S; 
		k = KDI[j]; 
		while(p != NULL){ 
			d = p->Digit[k]; 
			c[d].tail->next = p; 
			c[d].tail=p; 
			p=p->next; 
		} 
		p = (listName*)&S;
		for(int i=0;i< 256;i++){ 
			if(c[i].tail != (listName*)&(c[i].head)){ 
				p->next = c[i].head; 
				p = c[i].tail; 
			} 
		} 
		p->next = NULL; 
	} 
	
}


void StackInc(list* &head,int n){
	head=new list;
	head->num = 1;
	head->next = NULL;
	for(int i=2;i<=n;i++){
		list *p;
		p=new list;
		p->num=i;
		p->next=head;
		head=p;
	}
}
void StackDec(list* &head,int n){
	head=new list;
	head->num = n;
	head->next = NULL;
	for(int i=1;i<n;i++){
		list *p;
		p=new list;
		p->num=n-i;
		p->next=head;
		head=p;
	}
}

void List(listName* &head){
	FILE *pf;
	char tmp[20];
	pf = fopen("data.txt","r");
	head=new listName;
	fscanf(pf,"%s",head->lastname);
	head->next = NULL;
	while (!feof(pf)){
		listName *p;
		p=new listName;
		fscanf(pf,"%s",p->lastname);
		p->next=head;
		head=p;
	}
	
}

int QuickSortStart(int a[],int n){
	int c=0,m=0;
	int *b=new int [n];
	for(int i=0;i<n;i++){
		b[i]=a[i];
	}
	QuickSort(b,0,n-1,c,m);
	return c+m;
}

int QuickSort(int a[],int L,int R,int &c,int &m){
	int mid=L+R>>1;
	m++;
	int x=a[mid],i=L,j=R;
	while(i<=j){
		while(a[i]<x){
			c++;
			i++;
		}
		while(a[j]>x){
			c++;
			j--;
		}
		if(i<=j){
			m+=3;
			int tmp=a[i];
			a[i]=a[j];
			a[j]=tmp;
			i++;
			j--;
		}
	}
	if(L<j)QuickSort(a,L,j,c,m);
	if(i<R)QuickSort(a,i,R,c,m);
}

void StackRand(list* &head,int n){
	head=new list;
	head->num = rand()%(n-1)+1;;
	head->next = NULL;
	for(int i=1;i<n;i++){
		list *p;
		p=new list;
		p->num=rand()%(n-1)+1; 
		p->next=head;
		head=p;
	}
}

void printSpis(listName *h){
	listName *p;
	p=h;
	cout << "Massive: "<<endl;
	while (p!=NULL){
		cout << p->lastname <<" ";
		p=p->next;
	}
	cout << endl;
	
}

void print1(list *h){
	list *p;
	p=h;
	cout << "Massive: "<<endl;
	while (p!=NULL){
		cout << p->num <<" ";
		p=p->next;
	}
	cout << endl;
}
void RunNumber(list *h){
	int k=1;
	list *p;
	p=h;
	cout << "Run Number: "<<endl;
	while (p->next!=NULL){
		if(p->num > p->next->num){
			k++;
		}
		p=p->next;
	}
	cout << k<<endl;
}
void CheckSum(list *h){
	int s=0;
	list *p;
	p=h;
	cout << "Sum: "<<endl;
	while (p!=NULL){
		s+= p->num;
		p=p->next;
	}
	cout << s<<endl;
}
void Info(list *head,int m){
	print1(head); 
	RunNumber(head);
	CheckSum(head); 
	cout << endl<<"T:="<<m<<endl;
}

int main(){
	int m16=0;
	int m32=0;
	//Stack
	list *head16=NULL;
	list *head32=NULL;
	listName *head=NULL;
	//Queue
	list *head1=new list;
	list *tail=NULL;
	head1->next=tail;
	
	cout << "Choose lenght of Mass: ";
	int n; 
	cin>>n; 
	char t; 
	while(1){ 
		cout << "Choose Mass?"<<endl; 
		cout << "1.FillStackInc"<<endl; 
		cout << "2.FillStackDec"<<endl; 
		cout << "3.FillStackRand"<<endl; 
		cout << "4.Sort"<<endl; 
		cout << "5.InfoStack"<<endl; 
		cout << "6.Full Info"<<endl; 
		cout << "7.Quit"<<endl;  
		cin>>t; 
		system("cls");
		if(t==7)break;
		switch(t){ 
			case 1 : StackInc(head16,n); StackInc(head32,n); List(head);
		break; 
			case 2 : StackDec(head16,n); StackDec(head32,n); List(head);
		break; 
			case 3 : StackRand(head16,n); StackRand(head32,n); List(head);
		break; 
			case 4 : DigitalSort16(head16,m16); DigitalSort32(head32,m32);DigitalSortSpis(head); 
		break;
			case 5 : cout << "2 byte:"<<endl; Info(head16,m16);cout <<endl<< "4 byte:"<<endl; Info(head32,m32); cout<<endl;printSpis(head); 
		break;
			case 6 :
				cout << "          ";
				for(int i=1;i<=5;i++){
					printf("%10.0d ",i*10000);
				}
				cout << endl;
				for(int i=2;i<=7;i++){
					printf("bytes %3.0d ",i*4);
					for(int j=1;j<=5;j++){
						printf("%10.0d ",DigitalSort(i*4,j*10000));
					}
					cout << endl;
				}
				int *a = new int [50000] ;
				for(int i=0;i<50000;i++){
					a[i]=rand()%(50000)+1;  
				}
					printf("Quick Sort");
				for(int i=1;i<=5;i++){
					int tmp = i*10000;
					printf("%10.0d ", QuickSortStart(a,tmp));
				}
				
				break;

		} 
		system("cls");
	}
	
}
