#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
using namespace std;
void Summa(int *A[],int B[],int n)
{
	int sum;
	for(int i=0;i<n;i++)
	{
		sum=0;
		for(int j=0;j<B[i];j++)
		{
			sum+=A[i][j];
		}
		cout << " Summa " << i << " stroki = " << sum << endl;
	}
}

int main()
{
	int **A,n,c,*B,m;
	srand(time(NULL));
	cout << " Vvedite kol-vo strok -" << endl ;
	cin >> n;
	cout << " Vvedite max dlinu stroki -" << endl ;
	cin >> m;
	cout << endl ;
	B=new int [n];
	A = new int *[n];
	for(int i=0;i<n;i++)
	{
		c=rand()%m;
		B[i]=c;
		A[i]= new int [c];
		for(int j=0;j<c;j++)
		{
			A[i][j]=rand()%100;
		}
	}
	for(int i = 0;i<n;i++)
	{
		A[i][0] = B[i];
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<B[i];j++)
		{
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << endl ;
	Summa(A,B,n);
}
