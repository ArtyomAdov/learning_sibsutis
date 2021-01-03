#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "windows.h"
#include <iostream>
#include <conio.h>
using namespace std;
bool Rost; 
int less;


struct TREE
{
	int data;
	int Balance;
	TREE *right;
	TREE *left;
};TREE *q;


int LL(TREE *&p)
{
cout<<"(LL)"<<endl;
TREE *q;
q = p->left;
q->Balance = 0;
p->Balance = 0;
p->left = q->right;
q->right = p;
p = q;

}
//
int RR(TREE *&p)
{
	cout<<"(RR)"<<endl;
TREE *q;
q = p->right;
p->Balance = 0;
q->Balance = 0;
p->right = q->left;
q->left = p;
p = q;		
}
//
int LR(TREE *&p)
{
	cout<<"(LR)"<<endl;
TREE *q, *r;
q = p->left;
r = q->right;
if(r->Balance < 0)  p->Balance = 1;
else                p->Balance = 0;
if(r->Balance > 0)	q->Balance = -1;
else				q->Balance = 0;
r->Balance = 0;
p->left = r->right;
q->right = r->left;

r->left = q;
r->right = p;
p = r;	
}
//
int RL(TREE *&p)
{
	cout<<"(RL)"<<endl;
TREE *q, *r;
q = p->right;
if(q==NULL){printf("lol");}else r = q->left;
if(r->Balance > 0) 	p->Balance = -1;
else				p->Balance = 0;

if((r==NULL)||(q==NULL)){printf("lol");}else {if(r->Balance < 0)	q->Balance = 1;
else				q->Balance = 0;}
if((r==NULL)||(q==NULL)){printf("lol");}else r->Balance = 0;
if((r==NULL)||(q==NULL)){printf("lol");}else p->right = r->left;
if((r==NULL)||(q==NULL)){printf("lol");}else q->left = r->right;
r->left = p;
r->right = q;
p = r;
}



int addTree(TREE *&p, int D) 
{
		
	if(p == NULL) 
	{	
		p = new TREE;
		p->data = D;
		p->left = NULL;
		p->right = NULL;
		p->Balance = 0;
		Rost = true;
	}
	else{ if	(p->data == D){printf("kek");return 0;}
    else	
		if(p->data > D){;addTree(p->left, D);if(Rost == true)                           {
            if(p->Balance > 0){p->Balance = 0;Rost = false;}else
			if(p->Balance == 0){p->Balance = -1;Rost = true;}else{
			if(p->left->Balance < 0){LL(p);Rost = false;}else
			{LR(p);Rost = false;}}                            
                                                                                         }
                       }
                       else
		if(p->data < D) {addTree(p->right, D);if(Rost == true)    {
			if(p->Balance < 0){p->Balance = 0;Rost = false;}else
			if(p->Balance == 0){p->Balance = 1;Rost = true;}else{
			if(p->right->Balance > 0){RR(p);Rost = false;}else
            {RL(p);Rost = false;}}
                                                                                    }
                         }
}
}



int print_tree(TREE *q){           
    if(!q)   return 0;       
    print_tree(q->left);
    printf("%d ",q->data);
    print_tree(q->right);
}


int heightt(TREE *p) 
{   
    int h1=0,h2=0;
    if(p==NULL)return 0;
    else {
		h1=heightt(p->left);
    	h2=heightt(p->right);
    	return(max(h1,h2)+1);
	}
}

int CDP(TREE *p, int L){ 
    int s1=0, s2=0;
    if(!p)  return 0; 
	else{                                                           
    	s1=CDP(p->left, L+1);
    	s2=CDP(p->right, L+1);
    	return (L+s1+s2);
	}
}

int razmer(TREE *p){  
    int r=0, r1=0, r2=0;                                               
    if(p==NULL)  return 0;                                                           
    else{
	    r1=razmer(p->left);
    	r2=razmer(p->right);
    	return (1+r1+r2);
	}
}

int Sum(TREE *p){ 
    int sum=0, sum1=0, sum2=0;
    if(!p)  return 0; 
	else{                                                            
    	sum1=Sum(p->left);
    	sum=p->data;
    	sum2=Sum(p->right);
    	return (sum+sum1+sum2);
	}
}


int sizet(TREE *p){  
    int r1=0, r2=0;                       
    if(p==NULL)  return 0;                                                  
    else{
	    r1=sizet(p->left);
    	r2=sizet(p->right);
    	return (1+r1+r2);
	}
}
void LL1(TREE *&p,bool *less) {
     printf("LL1");
    TREE *q = p->left;
    if (q->Balance == 0) {
        p->Balance = -1;
        q->Balance = 1;
        *less = false;
    }
    else {
        p->Balance = 0;
        q->Balance = 0;
    }
    p->left = q->right;
    q->right = p;
    p = q;
}

void RR1(TREE *&p,bool *less) {
    printf("RR1");
    TREE *q = p->right;
    if (q->Balance == 0) {
        p->Balance = 1;
        q->Balance = -1;
        *less = false;
    }
    else {
        p->Balance = 0;
        q->Balance = 0;
    }
    p->right = q->left;
    q->left = p;
    p = q;
}
void BL(TREE *&p,bool *less) {
    if (p->Balance == -1) p->Balance = 0;
    else if (p->Balance == 0) {
        p->Balance = 1;
        *less = false;
    }
    else if (p->Balance == 1) {
        if ((p->right!=NULL)&&(p->right->Balance >= 0))
        RR1(p,less);
        else RL(p);
    }
}

void BR(TREE *&p,bool *less) {
    if (p->Balance == 1) p->Balance = 0;
    else if (p->Balance == 0) {
        p->Balance = -1;
        *less = false;
    }
    else if (p->Balance == -1) {
        if (p->left->Balance <= 0) LL1(p,less);
        else LR(p);
    }
}
void del(TREE *&r,bool *less){
     if(r->right!=NULL)
     {del(r->right,less);
     if (less) BR(r,less);}
     else {q->data=r->data;
     q=r;
     r=r->left;
     *less=true;}
     }
void delfromAVL(int x,TREE *&p,bool *less)
{
 if(p==NULL){printf("lul");return;}
 else if(p->data>x){
      delfromAVL(x,p->left,less);
      if (less) BL(p,less);}
 else if(p->data<x){
      delfromAVL(x,p->right,less);
      if (less) BR(p,less);}
 else {q=p;
 if(q->right==NULL){p=q->left;*less=true;}
 else if(q->left==NULL){p=q->right;*less=true;}
 else {del(q->left,less);
 if (less) BL(p,less);}free(q);}
 
     }
int main(){
	srand((unsigned)time(NULL));
	TREE *root = NULL;
	int n, i, j, t; 
	int *mass;
	
	system("chcp 1251 > nul"); 
		
	cout << "Ââåäèòå êîëè÷åñòâî âåðøèí â äåðåâå (N):";
	cin >> n;
	
	mass = (int*)malloc(sizeof(int) * n); 
	if(mass == NULL) { cout << "Memory error!"; return 0; }


		system("CLS");
	cout << "Ìàññèâ ñëó÷àéíûõ íåïîâòîðÿþùèõñÿ ÷èñåë:" << endl;
	
	for(int i=0; i<n; i++)
	{
		mass[i] = i;
	}
	
	 
	for(i=n-1; i>0; i--)
	{
		j = rand()%i;
		t = mass[j];
		mass[j] = mass[i];
		mass[i] = t;
	}
	
	
	for(int i=0; i<n; i++)
	{
		cout<<" "<<mass[i];
	}
	
	cout<<endl;

	
	for(int i=0; i<n; i++){
		addTree(root, mass[i]);
	}
	
	cout <<endl<< "Îáõîä äåðåâà ñ âûâîäîì:" << endl;
	print_tree(root); cout<<endl;
	int vertexscore;bool less=false;
    for(int key=0;key<10;key++){
    printf("Enter vertex for delete: ");
		less=false;
        scanf("%d", &vertexscore);
    delfromAVL(vertexscore,root,&less);
    print_tree(root);}
	cout<<endl<<"^^^^Ïàðàìåòðû äåðåâà: ^^^^";
	cout<<endl<<"Âûñîòà äåðåâà = "<<heightt(root); 	
	cout<<endl<<"Ñðåäíÿÿ âûñîòà = "<<CDP(root,1);  
	cout<<endl<<"Êîíòðîëüíàÿ ñóììà = "<<Sum(root);

	getch();
}
