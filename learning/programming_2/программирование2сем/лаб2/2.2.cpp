#include <stdio.h>//сделать вызов по элементам типо каждый развызываем функцию передавая новый элемент
#include <stdlib.h>
#include <ctime>
const int n=10;
int A[n];
void Sravnenie(int*,int);
int FillRand();
int main()
{
	FillRand();
	Sravnenie(A,0);
	system("PAUSE");
}
FillRand()
{
	printf("massiv=  ");
	srand(time(NULL));
	for(int i=0;i<n;i++)
	{
		A[i]=rand()%n;
		A[i]=A[i]-5;
		if (A[i]==0)
		{
			A[i]=1;
		};
		printf("%d ",A[i]);
	};
	printf("\n");
}
void Sravnenie(int A[],int j)
{ if(j>=n) return;
	if(A[j]<0) 
	printf("%d ",A[j]);
    Sravnenie(A,j+1);
    if(A[j]>0)
    printf("%d ",A[j]);
}
