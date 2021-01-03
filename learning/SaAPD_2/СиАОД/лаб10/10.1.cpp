#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <clocale>
#include <math.h>
const int n=500;
int A[n],C=0,M=0,T=0;
void FillInc();
void FillDec();
void FillRand();
void BuildHeap(int,int);
void QuickSort(int,int);
void PrintMas();
int main() 
{
	int x,X;
	printf("1) Zapolnit massiv po vozrastaniu\n");
	printf("2) Zapolnit massiv po ubivaniu\n");
	printf("3) Zapolnit massiv randomno\n");
	scanf("%d",&x);
	switch(x) {
	    case 1:
		{
			system("CLS");
	        FillInc();
	        break;
	    };
	    case 2:
		{
			system("CLS");
		    FillDec();
		    break;
	    };
	    case 3:
		{
			system("CLS");
		    FillRand();
		    break;
	    };
    };
	QuickSort(0,n-1);
	PrintMas();
	T=M+C;
	printf("\n%d\n",T);
system("PAUSE");
}
void FillInc()
{
	printf("ishodnii massiv\n");
	for(int i=0;i<n;i++)
	{
		A[i]=i;
	    printf("%4d",A[i]);
	};
	printf("\n");
}
void FillDec()
{
	printf("ishodnii massiv\n");
	for(int i=0;i<n;i++)
	{
		A[i]=n-i;
		printf("%4d",A[i]);
	};
	printf("\n");
}
void FillRand()
{
	printf("ishodnii massiv\n");
	srand(time(NULL));
	for(int i=0;i<n;i++)
	{
		A[i]=rand()%n;
		printf("%4d",A[i]);
	};
	printf("\n");
}
void PrintMas() 
{
	printf("\notsortirovanii massiv\n");
	for(int i=0;i<n;i++) 
	{
		printf("%d ",A[i]);
	};
	printf("\n\n");
}
void QuickSort(int L, int R) 
{
     int i=L,j=R,q,x;
     M++;
	 x=A[L];
     while (i<=j) 
	 {
	 	   C++;
           while (A[i]<x) {i++; C++;}
		   C++;
		   while (A[j]>x) {j--; C++;}
           if (i<=j) {
              q=A[i];
              A[i]=A[j];
              A[j]=q;
              M=M+3;
              i++;
              j--;
           }
     }
     if (L<j) QuickSort(L,j);
     if (i<R) QuickSort(i,R);    
}
