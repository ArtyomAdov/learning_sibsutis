#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <clocale>
#include <math.h>
void DrawTable();
int InsertSort(int);
int SearchOne(int,int*);
int SearchTwo(int,int*);
int main() 
{
	DrawTable();
system("PAUSE");
}
void SearchOne(int n,int A)
{
	bool naid=false;
	int X=n/3,C=0,i,L=0,R=n-1;
	while(L<=R)
	{
		i=(L+R)/2;
		C++;
		if(A[i]==X)
		{
			naid==true;
			printf("\nSearchOne=%d\n",i);
			break;
		}
		C++;
		if(A[i]<X)
		{
			L=i+1;
		}
		else
		{
			R=i-1;
		}
	}
	if(naid=false)
	{
		printf("\nSearchOne=nenaiden\n");
	}
	printf("C=%d\n",C);
	return C;
}
int InsertSort(int n)
{
	int A[n],temp,C=0,M=0,T=0;
	srand(time==(NULL));
	for(int i=1;i<n;i++)
	{
		A[i]=rand()%n;
	}
	for(int i=1;i<n;i++)
	{
		int j=i-1;
		temp=A[i];
		while(j>=0&&temp<A[j])
		{
			A[j+1]=A[j];
			j=j-1;
		};
		A[j+1]=temp;
	};
	SearhOne(n,A);
}
int InsertSort2(int n)
{
	int A[n],temp,C=0,M=0,T=0;
	srand(time==(NULL));
	for(int i=1;i<n;i++)
	{
		A[i]=rand()%n;
	}
	for(int i=1;i<n;i++)
	{
		int j=i-1;
		temp=A[i];
		while(j>=0&&temp<A[j])
		{
			A[j+1]=A[j];
			j=j-1;
		};
		A[j+1]=temp;
	};
	SearhTwo(n,A);
}
void SearchTwo(int n,int A[])
{
	int X=n/3,C=0,i,L=0,R=n-1;
	while(L<R)
	{
		i=(L+R)/2;
		printf("i=%d ",i);
		C++;
		if(A[i]<X)
		{
			L=i+1;
			printf("L=%d ",L);
		}
		else
		{
			R=i;
			printf("R=%d ",R);
		}
	}
	if(A[R]==X)
	{
		printf("\nSearchTwo=%d\n",R);
	}
	printf("C=%d\n",C);
}
void DrawTable()
{
	printf("\t______________________________________________\n");
	printf("\t|||   n  ||||||||SearhOne|||SearchTwo|||\n");
	for(int k=100;k<=1000;k=k+100)
	{
		int one,two;
		
        one=Insert1(k);
		two=Insert2(k);
		printf("\t|||______||||||______|||______|||______|||\n");
	    printf("\t|||%d          %d     %d   \n",k,one,two);
	    printf("\t|||______||||||______|||______|||______|||\n");
    }
}
