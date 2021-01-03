#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SEVERAL_ITERATION 10

#define ERROR_ALLOCATION_MEMORY 0b00000001

#define NUMBER_FOR_SAVE_FROM_DIVISION_BY_ZERO 0.5
#define DIGIT_CAPACITY_IN_DECIMAL 10

int Fill_Rand_Matrix_Square(double** matrix[], int size_matrix)
{
	(*matrix) = (double**)calloc(size_matrix,sizeof(double*));
	if(*matrix == NULL)
	{
		return ERROR_ALLOCATION_MEMORY;
	}
	for(short int i = 0; i < size_matrix; i++)
	{
		(*matrix)[i] = (double*)calloc(size_matrix,sizeof(double));
		if((*matrix)[i] == NULL)
		{
			return ERROR_ALLOCATION_MEMORY;
		}
		for(short int j = 0; j < size_matrix; j++)
		{
			(*matrix)[i][j] = ((double)(rand()%DIGIT_CAPACITY_IN_DECIMAL) / ((double)(rand()%DIGIT_CAPACITY_IN_DECIMAL) + NUMBER_FOR_SAVE_FROM_DIVISION_BY_ZERO));
		}
	}
	return 0;
}

int Multiple_Matrix_Square_Block_Enumeration(double** matrix_result[], double* matrix_first[], double* matrix_second[], int size_matrix, int block_size)
{
	(*matrix_result) = (double**)calloc(size_matrix, sizeof(double*));
	if(*matrix_result == NULL)
	{
		return ERROR_ALLOCATION_MEMORY;
	}
	for(short int i = 0; i < size_matrix; i++)
	{
		(*matrix_result)[i] = (double*)calloc(size_matrix, sizeof(double));
		if((*matrix_result)[i] == NULL)
		{
			return ERROR_ALLOCATION_MEMORY;
		}
	}
	double temp = 0;
	for(short int jj = 0; jj < size_matrix; jj += block_size)
	{
		for(short int kk = 0; kk < size_matrix; kk += block_size)
		{
			for(short int i=0; i < size_matrix; i++)
			{
				for(short int j = jj; j < ((jj + block_size) > size_matrix ? size_matrix:(jj + block_size)); j++)
				{
					temp = 0;
					for(short int k = kk; k < ((kk + block_size) > size_matrix ? size_matrix:(kk + block_size)); k++)
					{
						temp += (matrix_first[i][k] * matrix_second[k][j]);
					}
					(*matrix_result)[i][j] += temp;
				}
			}
		}
	}
	return 0;
}

int main()
{
    double** matrix_first = NULL;
	double** matrix_second = NULL;
	double** matrix_result = NULL;
    double value_time = 0.0;
	double average_time = 0.0;
    FILE* file = NULL;
    int size_square_matrix = 1000;
	int block_size = 0;
    int error_flag = 0b0;
	srand(time(NULL));
    file = fopen("opt_block_size.txt","a");
    if(file == NULL)
    {
        return -1;
    }
    for(short int rate_first = 0, rate_second = 0; block_size < 500;rate_second++)
    {
        if(rate_second > 3)
        {
            rate_second = 0;
            rate_first++;
        }
        block_size = (pow(5,rate_first) * (pow(2,rate_second)));
        printf("block: %d\n",block_size);
        error_flag = (error_flag | Fill_Rand_Matrix_Square(&matrix_first, size_square_matrix));
        error_flag = (error_flag | Fill_Rand_Matrix_Square(&matrix_second, size_square_matrix));
        printf("start\n");
        for(short int i = 0; i < SEVERAL_ITERATION; i++)
        {
            printf("%d)iterstart\n",i);
            value_time = clock();
            error_flag = (error_flag | Multiple_Matrix_Square_Block_Enumeration(&matrix_result, matrix_first, matrix_second, size_square_matrix, block_size));
            value_time = (clock() - value_time);
            for(short int i = 0; i < size_square_matrix; i++)
            {
                free(matrix_result[i]);
                matrix_result[i] = NULL;
            }
            free(matrix_result);
            average_time = (average_time + value_time);
        }
        value_time = (average_time / SEVERAL_ITERATION);
        average_time = 0.0;
        for(short int i = 0; i < size_square_matrix; i++)
        {
            free(matrix_first[i]);
            matrix_first[i] = NULL; 
        }
        for(short int i = 0; i < size_square_matrix; i++)
        {
            free(matrix_second[i]);
            matrix_second[i] = NULL;
        }
        free(matrix_first);
        free(matrix_second);
        matrix_first = NULL;
        matrix_second = NULL;
        matrix_result = NULL;
        value_time = (value_time / CLOCKS_PER_SEC);
        fprintf(file,"%-14d %lf\n", block_size, value_time);
    }
    fclose(file);
	file = NULL;
	return error_flag;
}