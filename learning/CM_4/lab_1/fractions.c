#include <stdlib.h>
#include <stdio.h>

const int size=3;

typedef struct fractions_array
{
	int numerator;//числитель
	int	denominator;//знаменатель
} fractions; 

fractions* Print_Matrix(fractions *Arr)
{
	for(short int i=0;i<size;i++)
	{
		Arr[i].numerator=1;
		printf("%d\t",Arr[i].numerator);
	}
	printf("\n");
	for(short int i=0;i<size;i++)
	{
		printf("-\t");
	}
	printf("\n");
	for(short int i=0;i<size;i++)
	{
		Arr[i].denominator=2;
		printf("%d\t",Arr[i].denominator);
	}
	printf("\n");
}

int main()
{
	fractions *Arr=NULL;
	Arr= (fractions*) calloc (size, sizeof(fractions));
	//printf("%d",Arr[0].numerator);
	Print_Matrix(Arr);
	return 0;
}
