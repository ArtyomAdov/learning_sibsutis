#include <stdio.h>//13-14к на 500эл
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <clocale>
#include <math.h>
int T=0,C=0,M=1;
void FillInc(int,int*);
void FillDec(int,int*);
void FillRand(int,int*);
int BuildHeap(int,int,int,int*);
int HeapSort(int,int*);
int main() 
{
	int inc,dec,rand;
	printf("\t___________________Heap___________________\n");
	printf("\t|||   n|||FillInc|||FillDec|||FillRand|||\n");
	for(int n=100;n<=500;n=n+100)
	{
		int A[n];
		FillInc(n,A);
		inc=HeapSort(n,A);
		T=0;C=0;M=1;
		FillDec(n,A);
		dec=HeapSort(n,A);
		T=0;C=0;M=1;
		FillRand(n,A);
		rand=HeapSort(n,A);
		T=0;C=0;M=1;
		printf("\t|||______|||______|||______|||______|||\n");
	    printf("\t||| %d  |||%d  |||%d  |||%d  |||\n",n,inc,dec,rand);
	    //printf("\t|||______|||______|||______|||______|||\n");
	}
system("PAUSE");
}
void FillInc(int n,int A[])
{
	for(int i=0;i<n;i++)
	{
		A[i]=i;
	};
}
void FillDec(int n,int A[])
{
	for(int i=0;i<n;i++)
	{
		A[i]=n-i;
	};
}
void FillRand(int n,int A[])
{
	srand(time(NULL));
	for(int i=0;i<n;i++)
	{
		A[i]=rand()%n;
	};
}
int BuildHeap(int L,int R,int n,int A[])
{
	int p=A[L],i=L,j;//,M=1,C=0,T=0;
	while(1) 
	{
		j=2*i;
		if(j>R)
		{
			break;
		}
		C++;
		if(j<R&&A[j+1]<A[j])
		{
			j=j+1;
		}
		C++;
		if(p<=A[j])
		{
			break;
		}
		M++;
		A[i]=A[j];
		i=j;
	}
	M++;
	A[i]=p;
	T=M+C;
	//return T;	
}
int HeapSort(int n,int A[])
{
	int L=(n-1)/2,R=n-1,temp;//,C=0,M=0,T=0,q=0,k=0;
	while(L>=0)
	{
		//q=BuildHeap(L,n-1,n,A);
		//k=k+q;
		BuildHeap(L,n-1,n,A);
		L--;
		//printf("\n%d\n",q);
	}
	while(R>0)
	{
		M++;
		temp=A[0];
		M++;
		A[0]=A[R];
		M++;
		A[R]=temp;
		R--;
		//q=BuildHeap(L,n-1,n,A);
		//k=k+q;
		BuildHeap(0,R,n,A);
	}
	//printf("\n%d\n",M+C);
	T=M+C;//+k;
	//printf("\n%d\n",k);
	//printf("\n%d\n",T);
	return T;
}
