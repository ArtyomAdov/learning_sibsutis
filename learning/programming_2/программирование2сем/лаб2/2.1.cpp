#include <stdio.h>
#include <stdlib.h>
int zapis();
int vivod();
int main()
{
	printf("vvedite posledovatelnost s okonchaniem na 0\n");
	zapis();
	system("PAUSE");	
}
int zapis()
{
	int x,v;
	scanf("%d",&x);
	if(x==0)
	{
		v=0;
		return 0;
	};
	zapis();
	if(x>0)
	{
		printf("%d ",x);
		return 0;
	};
}
