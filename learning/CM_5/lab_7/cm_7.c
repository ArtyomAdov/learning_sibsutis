#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ERROR_MEMORY_ALLOCATION 0b00000001;

#define SIZE_FIRST_ARRAY 3
#define SIZE_SECOND_ARRAY 2
#define SIZE_RESULT_ARRAY (SIZE_FIRST_ARRAY + SIZE_SECOND_ARRAY - 1)
#define INTERVAL_RANDOM_VALUE 10

#define TRIGGER_TEST 1
#define TRIGGER_PRINT_ITERATION 1

void Print_Array(double* array,int size_array)
{
	for(short int i = 0; i < size_array; i++)
	{
		printf("%f  ",array[i]);
	}
	printf("\n\n");
}

int Fill_Rand(double** array, int size_array)
{
	*array = (double*) calloc (size_array, sizeof(double));
	if(*array == NULL)
	{
		return ERROR_MEMORY_ALLOCATION;
	}
	for(short int i = 0; i < size_array; i++)
	{
		(*array)[i] = (((double)(1 + rand()%INTERVAL_RANDOM_VALUE)) / ((double)(1 + rand()%INTERVAL_RANDOM_VALUE)));
	}
	return 0;
}

int Convolution(double** result_array, double* first_array, double* second_array)
{
	*result_array = (double*) calloc ((SIZE_RESULT_ARRAY), sizeof(double));
	if(*result_array == NULL)
	{
		return ERROR_MEMORY_ALLOCATION;
	}
	for (short int i = 0; i < SIZE_RESULT_ARRAY; i++)
	{	
		for(short int j = SIZE_FIRST_ARRAY-1; j >= 0; j--)
//		for(short int j = 0; j < SIZE_FIRST_ARRAY; j++)
		{
			for (short int k = 0; k < SIZE_SECOND_ARRAY; k++)
			{
				if (i == j + k)
				{
					(*result_array)[i] = ((*result_array)[i] + first_array[j] * second_array[k]);
					#if TRIGGER_PRINT_ITERATION
					printf("res[%d] = res[%d] + fir[%d] * sec[%d] == %f + %f * %f == %f\n", i, i, j, k, ((*result_array)[i] - first_array[j] * second_array[k]), first_array[j], second_array[k], (*result_array)[i]);
					#endif
				}
			}
		}	
	}
	return 0;
}

int main()
{
	double* first_array = NULL;
	double* second_array = NULL;
	double* result_array = NULL;
	int error_flag = 0b0;
	srand(time(NULL));
	#if TRIGGER_TEST
	first_array = (double*)calloc(SIZE_FIRST_ARRAY,sizeof(double));
	second_array = (double*)calloc(SIZE_SECOND_ARRAY,sizeof(double));
	first_array[0] = 1.0;
	first_array[1] = 2.0;
	first_array[2] = 3.0;
	second_array[0] = 4.0;
	second_array[1] = 5.0;
	printf("first source array:\n");
	Print_Array(first_array,SIZE_FIRST_ARRAY);
	printf("second source array:\n");
	Print_Array(second_array,SIZE_SECOND_ARRAY);
	#else
	error_flag = (error_flag | Fill_Rand(&first_array, SIZE_FIRST_ARRAY));
	printf("first source array:\n");
	Print_Array(first_array,SIZE_FIRST_ARRAY);
	error_flag = (error_flag | Fill_Rand(&second_array, SIZE_SECOND_ARRAY));
	printf("second source array:\n");
	Print_Array(second_array,SIZE_SECOND_ARRAY);
	#endif
	error_flag = (error_flag | Convolution(&result_array, first_array, second_array));
	printf("result array:\n");
	Print_Array(result_array,SIZE_RESULT_ARRAY);
	return error_flag;
}
