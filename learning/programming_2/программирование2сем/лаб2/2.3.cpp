#include <stdio.h>
#include <stdlib.h>
int perevod(int);
int main()
{
	int n;
	printf("vvedite chislo\n");
	scanf("%d",&n);
	printf("\n");
	perevod(n);	
	printf("\n");
	system("PAUSE");
}
int perevod(int n)
{
	if(n==0)
	{
		printf("%d",0);
		return 0;
	};
	if(n==1)
	{
		printf("%d",1);
		return 0;
	}
	else
	{
		perevod(n/2);
		printf("%d",n%2);
	}
	return 0;
}
