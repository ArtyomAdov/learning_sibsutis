#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <clocale>
#include <math.h>
const int n=100;
int A[n];
void FillInc();
void FillDec();
void FillRand();
void CheckSum();
void RunNumber();
void ShellSort();
int main() {
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
	//printf("\npered shell""");
	ShellSort();
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
void ShellSort() 
{int n1,i,k,j,temp,*h,m,M=0,C=0,T=0;
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
			printf("	%d",h[i]);
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
	printf("\nM= %d\n",M);
	printf("C= %d\n",C);
	printf("T= %d\n",T);
    delete h;
    h=NULL;
}
