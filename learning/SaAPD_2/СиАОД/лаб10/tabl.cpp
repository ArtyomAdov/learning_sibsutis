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
int QuickSort(int,int,int*);
int main() 
{
	int inc,dec,rand;
	printf("\t_________Quick___________________________\n");
	printf("\t|||   n|||FillInc|||FillDec|||FillRand|||\n");
	for(int n=100;n<=500;n=n+100)
	{
		int A[n];
		FillInc(n,A);
		inc=QuickSort(0,n,A);
		T=0;C=0;M=1;
		FillDec(n,A);
		dec=QuickSort(0,n,A);
		T=0;C=0;M=1;
		FillRand(n,A);
		rand=QuickSort(0,n,A);
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
int QuickSort(int L, int R,int A[]) 
{
     int i=L,j=R,q,x;
     M++;
     x=A[(L+R)/2];
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
     if (L<j) QuickSort(L,j,A);
     if (i<R) QuickSort(i,R,A);
	 T=M+C;
	 return T;    
}
