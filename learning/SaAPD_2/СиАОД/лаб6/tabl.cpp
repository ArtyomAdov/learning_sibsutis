#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <clocale>
#include <math.h>
void DrawTable();
int InsertSort(int);
int ShellSort(int);
int main() 
{
	DrawTable();
system("PAUSE");
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
		M++;
		temp=A[i];
		C++;
		while(j>=0&&temp<A[j])
		{
			C++;
			M++;
			A[j+1]=A[j];
			j=j-1;
		};
		M++;
		A[j+1]=temp;
	};
    T=M+C;
    return T;
}
int ShellSort(int n) 
{
	int A[n],n1,i,k,j,temp,*h,m,M=0,C=0,T=0;
	m=log2(n)-1;
	h=new int [m];
	for(i=0;i<m;i++)
	{
		if(i==0)
		{
			h[i]=1;
		}
		else 
		{
			h[i]=(2*h[i-1])+1;
		};
	}
	for(int e=m-1;e>=0;e--)
	{
	    k=h[e]; 
        for(i=k;i<n;i++)
		{
            M++;
            temp=A[i];
            j=i-k;
            C++;
            n1=C;
            while(j>=0 && temp<A[j]){
                A[j+k]=A[j];
                j=j-k;
                C++;
                M++;
            }
            if (n1!=C) C--;  
            A[j+k]=temp;
            M++;
        }
    }
    T=M+C;
    return T;
    delete h;
    h=NULL;
}
void DrawTable()
{
	printf("\t______________________________________________\n");
	printf("\t|||   n  |||||||||Shell|||Insert|||\n");
	for(int k=100;k<=500;k=k+100)
	{
		int she,ins;
        she=ShellSort(k);
		ins=InsertSort(k);
		printf("\t|||______||||||______|||______|||______|||\n");
	    printf("\t|||%d          %d     %d   \n",k,she,ins);
	    printf("\t|||______||||||______|||______|||______|||\n");
    }
}
