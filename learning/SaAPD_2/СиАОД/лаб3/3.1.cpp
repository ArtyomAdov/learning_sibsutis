#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <clocale>
#include <math.h>
const int n=500;
int A[n];
int FillInc();
int FillDec();
int FillRand();
int CheckSum();
int RunNumber();
int BubbleSort();
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
	M=3*(n-1);
	C=(pow(n,2)-n)/2;
	T=M+C;
	printf("\nkol-vo sravneniy=  %d",C);
	printf("\nkol-vo smen mest=  %d",M);
	printf("\ntredoemkost=   %d\n\n",T);
	CheckSum();
	RunNumber();
	printf("\n");
	BubbleSort();
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
int BubbleSort()
{
	int temp, M1=0, C1=0,T1=0;
	printf("otsortirovanii massiv=  ");
	for(int i=0;i<n;i++) 
	{
		for(int j=i+1;j<n;j++)
		{
			C1++;
			if(A[i]>A[j])
			{
				M1++;
				temp=A[i];
				M1++;
				A[i]=A[j];
				M1++;
				A[j]=temp;
			};
		};
	};
	for(int i=0;i<n;i++) 
	{
	    printf("%d ",A[i]);
    };
	T1=M1+C1;
    printf("\n\nkol-vo sravneniy=  %d",C1);
    printf("\nkol-vo smen mestt=  %d",M1);
    printf("\ntrudoemkost=   %d\n\n",T1);
}
