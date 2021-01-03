#include <stdio.h>
#include <stdlib.h>
#include <ctime>
int main()
{
	int** B;
	int** C;
	int n=5,m,temp,a=0,b=0;
	printf("vvedite kol-vo stolbcov\n");
	scanf("%d",&m);
	srand(time(NULL));
	B=(int**)malloc(n*sizeof(int*));
    for (int i=0;i<n;i++) 
	{
        B[i]=(int*)malloc(m*sizeof(int));
        for (int j=0;j<m;j++) 
		{
            B[i][j]=rand()%100;
        };
    };
    printf("matrica=\n");
    for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(B[i][j]>B[a][b])
			{
				a=i;
				b=j;
			}
			printf("%d ",B[i][j]);
		};
		printf("\n");
	};
	printf("maximalnii element=  %d\n",B[a][b]);
	C=(int**)malloc((n-1)*sizeof(int*));
    for (int e=0,i=0;e<n;i++,e++)
	{
		if(e==a)
		{
			e++;
		};
        C[i]=(int*)malloc((m-1)*sizeof(int));
        for (int q=0,j=0;q<m;j++,q++) 
		{
			if(q==b)
			{
				q++;
			};
			C[i][j]=B[e][q];
        };
    };
    printf("algebraicheskoe dopolnenie=\n");
    for(int i=0;i<n-1;i++)
	{
		for(int j=0;j<m-1;j++)
		{
			printf("%d ",C[i][j]);
		};
		printf("\n");
	};
	free(B);
	B==NULL;
	free(C);
	C==NULL;
	return 0;
	system("PAUSE");
}
