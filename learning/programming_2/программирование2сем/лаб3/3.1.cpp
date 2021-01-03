#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
int random (int N) {return rand()%N;}
void FillRand(int*,int);
main()
{
	int *b,*c,*d,n,m=0,k=0;
	printf("vvedite razmer massiva\n");
	scanf("%d",&n);
	b=(int*) malloc(n*sizeof(int));
	FillRand(b,n);
	if (b==NULL)  
	{  
    	printf("Ne udalos videlit pamyat\n");
		return 1;
    };
	printf("\n");
	for(int i=0;i<n;i++)
	{
		if(b[i]<0)
		{
			k++;
		};
		if(b[i]>0)
		{
			m++;
		}
	}
	c=(int *) malloc(m*sizeof(int));
	d=(int *) malloc(k*sizeof(int));
	for(int i=0,j=0,e=0;i<n;i++)
	{
		if(b[i]>0)
		{
			c[j]=b[i];
			j++;
		}
		if(b[i]<0)
		{
			d[e]=b[i];
			e++;
		}
	}
	printf("massiv polojitelnih= ");
	for(int i=0;i<m;i++)
	{
		printf("%d ",c[i]);
	};
	printf("\nmassiv otricatelnih= ");
	for(int i=0;i<k;i++)
	{
		printf("%d ",d[i]);
	};
	printf("\n");
	free(b);
	b=NULL;
	free(c);
	b=NULL;
	free(d);
	c=NULL;
	return 0;
}
void FillRand(int b[],int n) 
{
	int min=-50,max=50;
	printf("massiv=\n");
	for(int i=0;i<n;i++) 
	{
		b[i]=random(max-min+1)+min;
		printf("%d ",b[i]);
	}
	printf("\n");
}
