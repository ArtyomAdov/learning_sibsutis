#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <map>
using namespace std;
struct Vuz
{
	int nomer;
	double vipusk;
	double post;
	double procent;
};
int main()
{
	int n,r=0,s=0,t;
	cout << " Vvedite kol-vo vuzov - " << endl;
	cin >> n;
	int B[n];
	int C[n];
	Vuz A[n];
	for(int i=0;i<n;i++)
	{
		B[i]=i;
	}
	for(int i=0;i<n;i++)
	{
		cout << " Vvedite nomer vuza  - ";
		cin >> A[i].nomer;
		cout << " Vvedite kol-vo vipusknikov - ";
		cin >> A[i].vipusk;
		cout << " Vvedite kol-vo postupivshih - ";
		cin >> A[i].post;
	}   
	cout << endl;
	for(int i=0;i<n;i++)
	{
		A[i].procent=(A[i].post*100)/(A[i].post+A[i].vipusk);
	}
	cout << endl;
	for(int i=0;i<n;i++)
	{
		cout << " Vuz nomer - " << A[i].nomer << "\t |";
		cout << " Kol-vo vipusknikov - " << A[i].vipusk << "\t |";
		cout << " Kol-vo postupivshih - " << A[i].post << "\t |";
		cout << " Procent postupivshih - " << A[i].procent << "\t |";
		cout << endl; 
	}
	
	int i,j,min;
	for(int j=0;j<n-1;j++)
	{
		min=j;
		for(int i = j+1; i < n;i++)
		{
			if(A[B[i]].procent < A[B[min]].procent)
    		{
				min=i;
    		}
		}
		t = B[min];
		B[min] = B[j];
		B[j] = t;	
	}
	cout << " Sortirovka po procentu - " << endl << endl;
	for(int i=0;i<n;i++)
	{
		cout << " Vuz nomer - " << A[B[i]].nomer << "\t |";
		cout << " Kol-vo vipusknikov - " << A[B[i]].vipusk << "\t |";
		cout << " Kol-vo postupivshih - " << A[B[i]].post << "\t |";
		cout << " Procent postupivshih - " << A[B[i]].procent << "\t |";
		cout << endl; 
	}
}
