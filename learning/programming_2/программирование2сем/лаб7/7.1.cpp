#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
const int N1=100 , N2=1000;
using namespace std;

void FillRand(int A[],int n) 
{
	srand(time(NULL));
	for(int i=0;i<n;i++) 
	{
		A[i]=rand()%300;
	//	printf("%d ",A[i]);
	}
}
void SelectSort(int A[],int n)
{
	int max,ind,temp,i;
	for(int j=0;j<n-1;j++)
	{
		max=j;
		for(int i = j+1; i < n;i++)
		{
			if(A[i] > A[max])
    		{
				max=i;
    		}
		}
		temp=A[max];
		A[max]=A[j];
		A[j]=temp;
	}
	for( int i=0;i<n;i++)
	{
		cout << A[i] << " " ;
	}
	cout << endl ;
}
void BSearch(int A[],int n,int x)
{
	int L=0,R=n-1,m;
	int N=0;
	int C=0;
	while(R > L)
	{
		m= (L+R)/2;
		//printf("%d \n",m);
		C++;
		if(x < A[m])
		{
			L = m + 1;
		}
		else
		{
			R = m;
		}
	}
	C++;
	if(A[R] == x)
	{
		printf(" Naiden ! \n");
	}
	else
	{
		printf(" Ne naiden !\n");
	}
	printf("\n C = %d \n",C);
}
void Perebor(int A[],int n, int x)
{
	int C=0,r=0;
	for(int i=0;i<n;i++)
	{
		C++;
		if(A[i]==x)
		{
			r++;
			cout << " Naiden ! " << endl ;
			break;
		}
	}
	if(r == 0)
	{
		cout << " Ne naiden !" << endl ;
	}
	cout << " C = " << C << endl ;
}
int main()
{
	int x, *A;
	A = new int [N1];
	cout << " Massiv 100 elemtov - " << endl ;
	FillRand(A,N1);
	SelectSort(A,N1);
	cout << " Vvedite x - " << endl ;
	cin >> x;
	cout << " Binarniy poisk - " << endl ;
	BSearch(A,N1,x);
	cout << " Poisk pereborom - " << endl ;
	Perebor(A,N1,x);
	cout << endl << endl ;
	A = new int [N2];
	cout << " Massiv 1000 elem - " << endl ;
	FillRand(A,N2);
	SelectSort(A,N2);
	cout << " Vvedite x - " << endl ;
	cin >> x;
	cout << " Binarniy poisk - " << endl ;
	BSearch(A,N2,x);
	cout << " Poisk pereborom - " << endl ;
	Perebor(A,N2,x);
}
