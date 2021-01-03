#include <stdlib.h>
#include <stdio.h>
#include <ctime>
int main()
{
	int** A;
	int** D;
	int s=0,sum=0,n,m,a=0,b=0;
	printf("vvedite kol-vo strok\n");
	scanf("%d",&n);
	printf("vvedite kol-vo stolbcov\n");
	scanf("%d",&m);
	srand(time(NULL));
	A=(int**)malloc(n*sizeof(int*));
	D=(int**)malloc((n+1)*sizeof(int*));
	srand(time(NULL));
	for(int i=0;i<n;i++){
		A[i]=(int*)malloc(m*sizeof(int));
		D[i]=(int*)malloc(m*sizeof(int));
		for(int j=0;j<m;j++){
			A[i][j]=rand()%100;
			printf("|%d  |",A[i][j]);
			D[i][j]=A[i][j];

		}
		printf("\n");
	}
	D[n]=(int*)malloc((m+1)*sizeof(int));
	for(int j=0;j<n;j++)
		D[j][m]=0;
	for(int j=0;j<m+1;j++)
		D[n][j]=0;
	printf("\n");
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			D[i][m]+=A[i][j];
			D[n][j]+=A[i][j];
			D[n][m]+=A[i][j];
		}
	
	for(int i=0;i<n+1;i++){
		for(int j=0;j<m+1;j++){
			printf("|%d  |",D[i][j]);
		}
		printf("\n");
	}
	free(A);
	A==NULL;
	free(D);
	D==NULL;
	return 0;
	system("PAUSE");
}
