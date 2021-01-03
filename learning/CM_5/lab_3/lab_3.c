#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE_ARRAY 8
#define RANGE_RANDOM 10
#define COEFFICIENT_STEP 2
#define START_STEP 1

void Print_Array(int* array)
{
	for(short int i = 0; i < SIZE_ARRAY; i++) 
	{
	    printf("%d ",array[i]);
    }
	printf("\n\n");
}

int* Fill_Rand(int* array)
{
	array = (int*) calloc (SIZE_ARRAY, sizeof(int));
	srand(time(NULL));
	for(short int i = 0; i < SIZE_ARRAY; i++)
	{
		array[i] = rand()%RANGE_RANDOM;
	}
	return array;
}

int* Merge_Sort(int* array)
{
	int* temp = NULL;
	int step = START_STEP;
	int index,mediana,left_limit,right_limit,il,ir;
	temp = (int*)calloc(SIZE_ARRAY, sizeof(int));
	while(step < SIZE_ARRAY)
	{
	    index = 0;
	    left_limit = 0;
	    mediana = step;
	    right_limit = step * COEFFICIENT_STEP;
	    do
	    {
	    	if(mediana > SIZE_ARRAY)
	    	{
	    		mediana = SIZE_ARRAY;
			}
			if(right_limit > SIZE_ARRAY)
	    	{
	    		right_limit = SIZE_ARRAY;
			}
		    il = left_limit, ir = mediana;
		    while((il < mediana) && (ir < right_limit))
		    {
		        if (array[il] < array[ir])
				{
					printf("%d<->%d\n",index,il);
					temp[index] = array[il];
					index++;
					il++;
				}
		        else 
				{
					printf("%d<->%d\n",index,ir);
					temp[index] = array[ir];
					index++;
					ir++;
				}
		    }
		    while(il < mediana)
			{
				temp[index] = array[il];	
				index++;
				il++;
			}
		    while(ir < right_limit)
		    {
		    	temp[index] = array[ir];
				index++;
				ir++;
			}
		    left_limit = (left_limit + step * COEFFICIENT_STEP);
		    mediana = (mediana + step * COEFFICIENT_STEP);
		    right_limit =(right_limit + step * COEFFICIENT_STEP);
	    } while(left_limit < SIZE_ARRAY);
	    for(short int i = 0; i < SIZE_ARRAY; i++)
	    {
	    	array[i] = temp[i];	
	    	if(i%step == 0)
	    	{
	    		printf("|");
			}
	    	printf("%d ",array[i]);
		}
		printf("\n");
	    step = (step * COEFFICIENT_STEP);
	}
	return array;
}

int main() 
{
	int* array = NULL;
	array = Fill_Rand(array);
	printf("ORIGINAL:\n");
	Print_Array(array);
	array = Merge_Sort(array);
	printf("SORTED:\n");
	Print_Array(array);
	free(array);
	array = NULL;
	return 0;
}
