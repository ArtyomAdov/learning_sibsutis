#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <clocale>
#include <math.h>
void DrawTable();
int InsertSort(int);
int ShakerSort(int);
int BubbleSort(int);
int SelectSort(int);
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
int SelectSort(int n)
{
	int A[n],min,temp,M=0,C=0,T=0;
	srand(time(NULL));
	for(int i=0;i<n;i++)
	{
		A[i]=rand()%n;
	}
	for(int i=0;i<n-1;i++)
	{
		min=i;
		for(int j=i+1;j<n;j++)
		{
			C++;
			if(A[j]<A[min])
			{   
				min=j;
			};
		};
		if(i!=min)
		{
		    M++;
		    temp=A[i];
		    M++;
		    A[i]=A[min];
		    M++;
		    A[min]=temp;
	    };
	};
	T=M+C;
	return T;
}
int BubbleSort(int n)
{
	int A[n],temp, M=0, C=0,T=0;
	srand(time(NULL));
	for(int i=0;i<n;i++)
	{
		A[i]=rand()%n;
	};
	for(int i=0;i<n;i++) 
	{
		for(int j=i+1;j<n;j++)
		{
			C++;
			if(A[i]>A[j])
			{
				M++;
				temp=A[i];
				M++;
				A[i]=A[j];
				M++;
				A[j]=temp;
			};
		};
	};
	T=M+C;
	return T;
}
int ShakerSort(int n)
{
	int A[n], i, j, L=0, R=n-1, k=n-1, temp,C=0,M=0,T=0;
	srand(time(NULL));
	for(int i=0;i<n;i++)
	{
		A[i]=rand()%n;
	};
	while(L<R)
	{
	    for(j=R;j>=L+1;j--)
		{
	    	C++;
	    	if(A[j]<A[j-1])
			{
	    		temp=A[j];
	    		A[j]=A[j-1];
	    		A[j-1]=temp;
	    		M+=3;
	    	    k=j;
			}
	    }
	    L=k;
	    for(j=L;j<R;j++)
		{
	    	C++;
	    	if(A[j]>A[j+1])
			{
	    		temp=A[j];
	    		A[j]=A[j+1];
	    		A[j+1]=temp;
	    		M+=3;
	    	    k=j;
			}
	    }
	    R=k;
    }
    T=M+C;
    return T;
}
void DrawTable()
{
	printf("\t______________________________________________\n");
	printf("\t|||   n  |||Select|||Bubble|||Shaker|||Insert|||\n");
	for(int k=100;k<=500;k=k+100)
	{
		int sel,bub,sha,ins;
		sel=SelectSort(k);
		bub=BubbleSort(k);
		sha=ShakerSort(k);
		ins=InsertSort(k);
		printf("\t|||______|||______|||______|||______|||______|||\n");
	    printf("\t|||%d      %d    %d    %d     %d   \n",k,sel,bub,sha,ins);
	    printf("\t|||______|||______|||______|||______|||______|||\n");
    }
}
