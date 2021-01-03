#include <stdio.h>//posobie str 38
#include <stdlib.h>//первый последний средний и которого нет
#include <ctime>
#include <conio.h>
#include <clocale>
#include <math.h>
void FillInc(int,int*);
int SearchOne(int,int*,int);
int SearchTwo(int,int*,int);
int main() 
{
	int X=49,one,two;
	printf("\t____________________________________\n");
	printf("\t|||   n|||SearhOne|||SearchTwo|||\n");
	for(int n=100;n<=1000;n=n+100)
	{
		int A[n];
		FillInc(n,A);
 		one=SearchOne(X,A,n);
		two=SearchTwo(X,A,n);
		printf("\t|||______|||______|||______|||\n");
	    printf("\t|||%d        %d       %d   \n",n,one,two);
	    printf("\t|||______|||______|||______|||\n");
	}
system("PAUSE");
}
void FillInc(int n,int A[])
{
	for(int i=0;i<n;i++)
	{
		A[i]=i;
		if(i%10==0)
		{
			A[i]=68;
		}
	};
}
int SearchOne(int X,int A[],int n)
{
	bool naid=false;
	int C=0,i,L=0,R=n-1;
	while(L<=R)
	{
		i=(L+R)/2;
		C++;
		if(A[i]==X)
		{
			naid==true;
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
	return C;
}
int SearchTwo(int X,int A[],int n)
{
	int C=0,i,L=0,R=n-1;
	while(L<R)
	{
		i=(L+R)/2;
		C++;
		if(A[i]<X)
		{
			L=i+1;
		}
		else
		{
			R=i;
		}
	}
	return C;
}
