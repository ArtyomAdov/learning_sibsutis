#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <clocale>
#include <math.h>
const int n=500;
int A[n];
void FillInc();
void FillDec();
void FillRand();
void BuildHeap(int,int);
void HeapSort();
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
	HeapSort();
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
}//
void BuildHeap(int L,int R)
{
	int p=A[L],i=L,j;
	while(1) 
	{
		j=2*i;
		if(j>R)
		{
			break;
		}
		if(j<R&&A[j+1]<A[j])
		{
			j=j+1;
		}
		if(p<=A[j])
		{
			break;
		}
		A[i]=A[j];
		i=j;
	}
	A[i]=p;	
}
void HeapSort()
{
	int L=(n-1)/2,R=n-1,temp;
	while(L>=0)
	{
		BuildHeap(L,n-1);
		L--;
	}
	while(R>0)
	{
		temp=A[0];
		A[0]=A[R];
		A[R]=temp;
		R--;
		BuildHeap(0,R);
	}
	printf("\notsortirovanii massiv\n");
	for(int i=0;i<n;i++)
	{
		printf("%4d",A[i]);
	}
	printf("\n");
}
