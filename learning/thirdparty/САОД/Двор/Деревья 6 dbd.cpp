#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "windows.h"
#include <iostream>
#include <conio.h>
using namespace std;
bool Rost; 
int less;

/* Структура дерева */
struct TREE
{
	int data;
	int Balance;
	TREE *right;
	TREE *left;
}; TREE *q;
/* Построение DBD- дерева */
bool VR=true, HR=true;
int dbd(int D, TREE *&p)
{
	if(p == NULL) // Если дерево пустое, или если новая вершина
	{
		p = new TREE;
		p->data = D;
		p->left =NULL;
		p->right = NULL;
		p->Balance = 0;
		VR = true;
	}
	else
	{
		if(p->data > D) 
		{
			dbd(D, p->left);
			if(VR == true)
			{
				if(p->Balance == 0)
				{
					q = p->left;
					p->left = q->right;
					q->right = p;
					p = q;
					q->Balance = 1;
					VR = false;
					HR = true;
				}
				else
				{
					p->Balance = 0;
					HR = true; 
				}
			}
			else
			{
				HR = false;
			}
			
			
		}
		else if(p->data < D)
		{
			dbd(D, p->right);
			if(VR == true)
			{
				p->Balance = 1;
				VR = false;
				HR = true;
			}
			else if(HR == true)
			{
				if(p->Balance > 0)
				{
					q = p->right;
					p->right = q->left;
					p->Balance = 0;
					q->Balance = 0;
					q->left = p;
					p = q;
					VR = true;
					HR = false;
				}
				else
				{
					HR = false;
				}
			}		
		}
	}
}

/* Обход дерева */
int print_tree(TREE *q){           
    if(!q)   return 0;       //выходим из функции, при отсутствии вершмины
    print_tree(q->left);// влево
    printf("%d ",q->data);
    print_tree(q->right);//идем вправо
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////AVL
int LL(TREE *&p)
{
//cout<<"(LL)"<<endl;
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
	//cout<<"(RR)"<<endl;
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
	//cout<<"(LR)"<<endl;
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
	//cout<<"(RL)"<<endl;
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
////////////////////////////////////////////////////////////////func harakter
int razmer(TREE *p){  
    int r=0, r1=0, r2=0;                                               
    if(p==NULL)  return 0;                                                           
    else{
	    r1=razmer(p->left);
    	r2=razmer(p->right);
    	return (1+r1+r2);
	}
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
float CDP(TREE *p, int L){ 
    float s1=0, s2=0;
    if(!p)  return 0; 
	else{                                                           
    	s1=CDP(p->left, L+1);
    	s2=CDP(p->right, L+1);
    	return (L+s1+s2);
	}
}
int main(){
	srand((unsigned)time(NULL));
	TREE *root=NULL,*root2 = NULL;
	int n, i,j,t; // кол-во элементов, i,
	int *mass;
	
	system("chcp 1251 > nul"); // Русский язык в программе	
		
	cout << "vvedite kolvo vershin v dereve (N):";
	cin >> n;
	
	mass = (int*)malloc(sizeof(int) * n); // Выделяем память под динамический массив
	if(mass == NULL) { cout << "Memory error!"; return 0; }


	system("CLS");
	cout << "massiv slu4 4isel:" << endl;
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
    for(i=0; i<n; i++){
		cout<<" "<<mass[i];
		dbd(mass[i], root);
	}
	for(int i=0; i<n; i++){
		addTree(root2, mass[i]);
	}
	
	cout <<endl<< "obhod i vyvod:" << endl;
	print_tree(root); cout<<endl;
	print_tree(root2);

	
	int avlrazmer,dbdrazmer;
    dbdrazmer=razmer(root);avlrazmer=razmer(root2);
    cout<<endl<<"razmer dbd= "<<dbdrazmer;
     cout<<endl<<"razmer avl= "<<avlrazmer;
     int avlvysota,dbdvysota;
     dbdvysota=heightt(root);avlvysota=heightt(root2);
     
     cout<<endl<<"vysota dbd= "<<dbdvysota;
     cout<<endl<<"vysota avl= "<<avlvysota;
     int summadbd,summaavl;
     summadbd=Sum(root);
     summaavl=Sum(root2);
     cout<<endl<<"contrsumma dbd= "<<summadbd;
     cout<<endl<<"contrsumma avl= "<<summaavl;
     float sredvysotaadbd,sredvysotaavl;
     sredvysotaadbd=CDP(root,1)/dbdrazmer;
      sredvysotaavl=CDP(root2,1)/avlrazmer;
       cout<<endl<<"contrsumma dbd= "<<sredvysotaadbd;
     cout<<endl<<"contrsumma avl= "<<sredvysotaavl;
     
     _getch();
	return 0;
}
