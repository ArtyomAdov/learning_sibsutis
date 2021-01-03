#include <stdlib.h>
#include <iostream>
using namespace std;
int random (int N) {return rand()%N;}
int SelectSort(double*,int);
int main()
{
	int n,min;
	double d=-50,r=50;
	cout << "vvedite razmer massiva" << endl;
	cin >> n;
	double *a = new double [n];
	double *b = new double [n];
	for(int i=0;i<n;i++)
	{
		a[i]=(float)rand()*(r-d)/RAND_MAX+d;
		*(b+i)=a[i];
	}
	cout << "massiv=  " << endl;
	for(int i=0;i<n;i++)
	{
		cout <<a[i]<<" ";
	}
	cout << endl;
	cout << "otsortirovanii massiv=  " << endl;
	SelectSort(b,n);
	for(int i=0;i<n;i++)
	{
		cout <<b[i]<<" ";
	}
	delete b;
	b=NULL;
	delete a;
	a=NULL;
	return 0;
}
int SelectSort(double b[],int n)
{
	int min,i;
	double temp;
	for(int j=0;j<n-1;j++)
	{
		min=j;
		for(int i = j+1; i < n;i++)
		{
			if(b[i] < b[min])
    		{
				min=i;
    		}
		}
		temp=b[min];
		b[min]=b[j];
		b[j]=temp;
	}
}//сделать индексную сортировку
