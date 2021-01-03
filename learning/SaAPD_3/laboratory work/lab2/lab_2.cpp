#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <ctime>

using namespace std;

struct Vertex
{
	int data;
	Vertex *left;
	Vertex *right;
};

int Size(Vertex *root,int n)
{
	if(root == NULL)
	return n;
	else
	n = 1 + Size(root->left,n) + Size(root->right,n);
}

int CheckSum(Vertex *root,int s)
{
	if(root == NULL)
	return s;
	else
	s = root->data + CheckSum(root->left,s) + CheckSum(root->right,s);
}

int AverageHeight(Vertex *root,int h)
{
	if(root == NULL)
	return h;
	else
	h = 1 + max(AverageHeight(root->left,h),AverageHeight(root->right,h));
}

int SumDP(Vertex *root,int L,int V)
{
	if(root == NULL)
	return V;
	else
	V = L+SumDP(root->left,L+1,V)+SumDP(root->right,L+1,V);
}

void obhod_1(Vertex *Main)
{
	if(!Main) return;
	obhod_1(Main->left);
	cout<<Main->data<<"\t";
	obhod_1(Main->right);
}

void SDP(Vertex *&Root, int data)
{
	Vertex **p = &Root;
	while(*p)
	{
		if((*p)->data < data) p = &((*p)->right);
		else if((*p)->data > data) p = &((*p)->left);
		else return;
	}
	{
		(*p) = new Vertex;
		(*p)->data = data;
		(*p)->left = NULL;
		(*p)->right = NULL;
	}
}

void SDPR(Vertex *&Root, int data)
{
	if(!Root)	
	{
		Root = new Vertex;
		Root->data = data;
		Root->left = NULL;
		Root->right = NULL;
		return;
	}
	if(Root->data < data)
	{
		SDPR(Root->right, data);
	}
	else if(Root->data > data) 
	{
		SDPR(Root->left, data);
	}
	else if(Root->data == data) return;
}

int main()
{
	srand(time(0));
	int N=100;
	Vertex *root2 = NULL,*root3 = NULL;	
	for(int i = 0; i < N; i++)
	{
		mas[i] = rand() % 100;
		SDP(root2, mas[i]);
	}
	
	for(int i = 0; i < N; i++)
	{
        
		SDPR(root3, mas[i]);
	}
	
	cout<<endl<<"SDP:"<<endl;
	obhod_1(root2);
	
	float sr=SumDP(root,1,0)/(float)(Size(root,0));
	cout << endl;
	cout << endl;
	cout << N <<"\t"<< "razmer\t" << "Contr. summa\t" <<"Visota\t"<<"Sr visota\t"<<endl; 
	cout << "ISDP\t" <<Size(root,0) << "\t"<<CheckSum(root,0)<<"\t\t"<<AverageHeight(root,0)<<"\t";printf("%.2f",sr);
	cout << endl;
	sr=SumDP(root2,1,0)/(float)(Size(root2,0));
	cout << "SDP\t" <<Size(root2,0) << "\t"<<CheckSum(root2,0)<<"\t\t"<<AverageHeight(root2,0)<<"\t";printf("%.2f",sr);
	cout << endl;
	sr=SumDP(root3,1,0)/(float)(Size(root3,0));
	cout << "SDP\t" <<Size(root3,0) << "\t"<<CheckSum(root3,0)<<"\t\t"<<AverageHeight(root3,0)<<"\t";printf("%.2f",sr);
}
