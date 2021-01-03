#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <clocale>
#include <math.h>
const int n=10;
int A[n];
int FillInc();
int FillDec();
int FillRand();
int CheckSum();
int RunNumber();
int SelectSort();
int main() 
{
	int M=0, C=0, C1=0, M1=0;
    int x;
	printf("1) Zapolnit massiv po vozrastaniu\n");
	printf("2) Zapolnit massiv po ubivaniu\n");
	printf("3) Zapolnit massiv randomno\n");
	scanf("%d",&x);
	switch(x)
	{
	    case 1:
		{
	        FillInc();
	        goto vibral;
	    };
	    case 2:
		{
		    FillDec();
		    goto vibral;
	    };
	    case 3:
		{
		    FillRand();
		    goto vibral;
	    };
    };
    vibral:
	M=3*(n-1);
	C=(pow(n,2)-n)/2;
	printf("\nkol-vo sravneniy=  %d",C);
	printf("\nkol-vo smen mest=  %d\n",M);
	CheckSum();
	RunNumber();
	printf("\n");
	SelectSort();
    CheckSum();
	RunNumber();
system("PAUSE");
}
FillInc() 
{
	printf("massiv=  ");
	for(int i=0;i<n;i++) 
	{
		A[i]=i;
	    printf("%d ",A[i]);
	};
	printf("\n");
}
FillDec() 
{
	printf("massiv=  ");
	for(int i=0;i<n;i++) 
	{
		A[i]=n-i;
		printf("%d ",A[i]);
	};
	printf("\n");
}
FillRand() 
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
CheckSum() 
{
	printf("kontr summa=  ");
	int s=0;
	for(int i=0;i<n;i++) 
	{
		 s=s+A[i];
	};
	printf("%d\n",s);
}
int RunNumber() 
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
int SelectSort()
{
	int min,temp,M1=0,C1=0;
	printf("otsortirovanii massiv=  ");
	for(int i=0;i<n-1;i++)
	{
		min=i;
		for(int j=i+1;j<n;j++)
		{
			C1++;
			if(A[j]<A[min])
			{   
				min=j;
			};
		};
		if(i!=min)
		{
		    M1++;
		    temp=A[i];
		    M1++;
		    A[i]=A[min];
		    M1++;
		    A[min]=temp;
	    }
		printf("%d ",A[i]);
	}
	printf("%d",A[n-1]);
	printf("     C1=%d    M1=%d\n",C1,M1);
}
