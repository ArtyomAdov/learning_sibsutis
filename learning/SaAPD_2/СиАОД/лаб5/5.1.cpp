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
void CheckSum();
void RunNumber();
void InsertSort();
int main() {
	int M=0, C=0, C1=0, M1=0,T=0;
	int x;
	printf("1) Zapolnit massiv po vozrastaniu\n");
	printf("2) Zapolnit massiv po ubivaniu\n");
	printf("3) Zapolnit massiv randomno\n");
	scanf("%d",&x);
	switch(x) {
	    case 1:
		{
	        FillInc();
	        break;
	    };
	    case 2:
		{
		    FillDec();
		    break;
	    };
	    case 3:
		{
		    FillRand();
		    break;
	    };
    };
	CheckSum();
	RunNumber();
	printf("\n");
	InsertSort();
    CheckSum();
	RunNumber();
system("PAUSE");
}
void FillInc()
{
	printf("massiv=  ");
	for(int i=0;i<n;i++)
	{
		A[i]=i;
	    printf("%d ",A[i]);
	};
	printf("\n");
}
void FillDec()
{
	printf("massiv=  ");
	for(int i=0;i<n;i++)
	{
		A[i]=n-i;
		printf("%d ",A[i]);
	};
	printf("\n");
}
void FillRand()
{
	printf("massiv=  ");
	srand(time(NULL));
	for(int i=0;i<n;i++)
	{
		A[i]=rand()%n;
		printf("%d ",A[i]);
	};
	printf("\n");
}
void CheckSum() 
{
	printf("kontr summa=  ");
	int s=0;
	for(int i=0;i<n;i++)
	{
		 s=s+A[i];
	};
	printf("%d\n",s);
}
void RunNumber() 
{
	printf("serii=  ");
	int k=0;
	for(int i=0;i<n;i++)
	{
		if(i==(n-1)) 
		{
			if(A[i]<=A[i-1]) 
			{
				k++;
				printf("%d",A[i]);
				goto exit;
			};
		};
		if(A[i]<=A[i+1])
		{
			printf("%d",A[i]);
		}
		else 
		{
			k++;
			printf("%d ",A[i]);
		};
	};
	exit:
	printf("\nkol-vo seriy=  %d\n",k);
}
void InsertSort()
{
	int temp,C=0,M=0,T=0;
	printf("otsortitovanii massiv= ");
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
	for(int i=0;i<n;i++)
	{
		printf("%d ",A[i]);
	};
    T=M+C;
    printf("\nfact kol-vo sravneniy=  %d",C);
	printf("\nfact kol-vo smen mest=  %d",M);
	printf("\nfact tredoemkost=   %d\n\n",T);
}
