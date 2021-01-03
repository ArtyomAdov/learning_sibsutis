#include <stdio.h>
#include <stdlib.h>
int main()
{
	int **A;
	int n;
	printf("vvedite chislo\n");
	scanf("%d",&n);
	A=new int*[n];
	for(int i=1;i<=n;i++)
	{
		A[i-1]=new int[i];
		for(int j=1;j<=i;j++)
		{
			A[i-1][j-1]=i*j;
			printf("%4d",A[i-1][j-1]);
		}
		printf("\n");
	}
	delete A;
	return 0;
	system("PAUSE");
}
