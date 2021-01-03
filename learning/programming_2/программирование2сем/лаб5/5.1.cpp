#include <stdio.h>
#include <stdlib.h>
#include <ctime>
int main()
{
	int *A,**B,i=0,e=0,n,m,z;
	printf("vvedite m\n");
	scanf("%d",&n);
	printf("vvedite k\n");
	scanf("%d",&m);
	A=new int [n];
	if(n%m==0)
	{
		B=new int*[n/m];
		z=n/m;
	}
	else
	{
		B=new int*[n/m+1];
		z=n/m+1;
	}
	srand(time(NULL));
	for(int j=0;j<n;j++)
	{
			A[j]=rand()%100;
			printf("%4d",A[j]);
	}
	printf("\n\n");
	while (e<n)
	{
		B[i]=new int [m];
		for(int j=0;j<m;j++)
		{
			if(e<n)
			{
				B[i][j]=A[e];
				e++;
			}
			else
			{
				B[i][j]=0;	
			};
		}
		i++;
	}
	for(int i=0;i<z;i++)
	{
		for(int j=0;j<m;j++)
		{
			printf("%4d",B[i][j]);
		}
		printf("\n");
	}
	delete A;
	delete B;
	return 0;
	system("PAUSE");
}
