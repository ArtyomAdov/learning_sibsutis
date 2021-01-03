#include <stdio.h>
#include <stdlib.h>
#include <ctime>

#define SIZE_ARRAY 7

void Print_Array(int* Array)
{
	for(short int i = 0; i < SIZE_ARRAY; i++) 
	{
	    printf("%d ",Array[i]);
    }
	printf("\n\n");
}

int* FillRand(int* Array)
{
	Array = (int*) calloc (SIZE_ARRAY, sizeof(int));
	srand(time(NULL));
	for(short int i = 0; i < SIZE_ARRAY; i++)
	{
		Array[i] = rand()%SIZE_ARRAY;
	}
	return Array;
}

int* BubbleSort(int* Array)
{
	int temp = 0;
	int step = 0;
	bool flag = false;
	while(1)
	{
		step++;
		flag = false;
		for(short int i = 1; i < SIZE_ARRAY; i++) 
		{
			if(Array[i] < Array[i-1])
			{
				temp = Array[i];
				Array[i] = Array[i-1];
				Array[i-1] = temp;
				flag = true;
				printf("step = %d\t Array[i] = %d <-> Array[i-1] = %d\tresult:",step, Array[i], Array[i-1]);
				Print_Array(Array);
			}
		}
		if(flag == false)
		{
			printf("Exit on step number %d\n",step);
			break;
		}
	}
	return Array;
}

int main() 
{
	int* Array = NULL;
	Array = FillRand(Array);
	Print_Array(Array);
	Array = BubbleSort(Array);
	Print_Array(Array);
	free(Array);
	Array = NULL;
	system("PAUSE");
	return 0;
}
