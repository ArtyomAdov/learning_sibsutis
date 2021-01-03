#include <stdio.h>
#include <stdlib.h>
#include <ctime>
int main()
{
	int *A,**B,i=0,e=0,m,k;
	printf("vvedite m\n");
	scanf("%d",&m);
	printf("vvedite k\n");
	scanf("%d",&k);
	A=new int [m];
	B=new int *[m/k+(m%k==0?0:1)];
	srand(time(NULL));
	for(int j=0;j<m;j++)
	{
			A[j]=rand()%100;
			printf("%4d",A[j]);
	}
	printf("\n\n");
	while (e<m)
	{
		B[i]=new int [k];
		for(int j=0;j<k;j++)
		{
			if(e<m)
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
	for(int i=0;i<m/k+(m%k==0?0:1);i++){
		for(int j=0;j<k;j++){
			printf("%4d",B[i][j]);
		}
		printf("\n");
	}
	delete A;
	delete B;
	return 0;
	system("PAUSE");
}
