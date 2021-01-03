#include <stdio.h>//posobie str 38
#include <stdlib.h>//первый последний средний и которого нет
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
void InsertSort();
void SearchOne(int);
void SearchTwo(int);
int main() 
{
	int x,X;
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
    printf("vvedite kluch\n");
    scanf("%d",&X);
	printf("\n");
	InsertSort();
 	SearchOne(X);
	SearchTwo(X);
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
void InsertSort()
{
	int temp,C=0,M=0,T=0;
	printf("otsortitovanii massiv= ");
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
	for(int i=0;i<n;i++)
	{
		printf("%d ",A[i]);
	};
}
void SearchOne(int X)
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
	int j=i;
	C++;
	while(j<n&&A[j+1]==X)
	{
		C++;
		j++;
		printf("SearchAllOne=%d ",j);
	}
	j=i;
	C++;
	while(j>0&&A[j-1]==X)
	{
		C++;
		j--;
		printf("SearchAllOne=%d ",j);
	}
	if(naid=false)
	{
		printf("\nSearchOne=nenaiden\n");
	}
	printf("C=%d\n",C);
}
void SearchTwo(int X)
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
	int j=R;
	C++;
	while(j<n&&A[j+1]==X)
	{
		C++;
		j++;
		printf("\nSearchTwo=%d\n",j);
	}
	if(A[R]==X)
	{
		cout << Numbers[D[i]].name << "         " << Numbers[D[i]].surname << "       " << Numbers[D[i]].flat << "        " << Numbers[D[i]].call << endl;
	}
	printf("C=%d\n",C);
}
