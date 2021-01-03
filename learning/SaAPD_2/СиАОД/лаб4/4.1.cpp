#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <clocale>
#include <math.h>
#include <graphics.h>
const int n=500;
int A[n];
int FillInc();
int FillDec();
int FillRand();
int CheckSum();
int RunNumber();
int ShakerSort();
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
    printf("___________________________________\n");
    printf("| n |ShakerSort    |BubbleSort    |\n");
	printf("___________________________________\n");
	printf("|___|vozr|rand|ubiv|vozr|rand|ubiv|\n");
	printf("___________________________________\n");
	CheckSum();
	RunNumber();
	printf("\n");
	ShakerSort();
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
RunNumber() 
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
int ShakerSort()
{
	int i, j, L=0, R=n-1, k=n-1, temp,C=0,M=0,T=0;
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
    printf("\nfact kol-vo sravneniy=  %d",C);
	printf("\nfact kol-vo smen mest=  %d",M);
	printf("\nfact tredoemkost=   %d\n\n",T);
    return 0;
}
