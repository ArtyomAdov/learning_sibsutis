#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
using namespace std;
int random (int N){return rand ()%N;}
int main()
{
	int **B, n, *A, i, j, *tmp;
	cout<<"vvedite razmer massiva\n";
	cin>>n;
	cout<<endl;
	A=new int[n];
	if (A==NULL)
	{
		cout<<"error";
		return 1;
	};
	B=new int *[n];
	if (B==NULL)
	{
		cout<<"error";
		return 1;
	};
	cout<<"massiv"<<endl;
	for (i=0; i<n; i++)
	{
		A[i]=rand()%n-n/3;
		B[i]=&A[i];
	}
	for (i=0; i<n; i++)
	{
		cout<<A[i]<<"||"<<*B[i]<<endl;
	}
	for (i=n-1; i>0; i--)
	{
		for (j=0; j<i; j++)
		{
			if (*B[j]>*B[j+1])
			{
				tmp=B[j+1];
				B[j+1]=B[j];
				B[j]=tmp;
			}
		}
	}
	cout<<"otsortirovanii massiv"<<endl;
	for (i=0; i<n; i++){
		cout<<A[i]<<"||"<<*B[i]<<endl;
	}
	delete A;
	delete B;
	A=NULL; 
	B=NULL;
	return 0;
	system ("PAUSE");
}
