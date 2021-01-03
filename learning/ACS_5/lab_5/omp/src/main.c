#include "death_error.h"
#include "death_arg.h"
#include "death_char.h"
#include "death_file.h"
#include "death_matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <sys/time.h>

// #define PRINT_DEBUG

int Multiple_Square_Matrix_With_Open_MP(double* result[], double first[], double second[], int length, int quantity_thread)
{
	double sum = 0.0;
	int i = 0, j = 0, k = 0;
	*result = (double*)calloc((length*length),sizeof(double));
	#pragma omp parallel for shared(first, second, result) private(j, k) num_threads(quantity_thread) schedule(static)
	for(i = 0; i < length; i++)
	{
		for(j = 0; j < length; j++)
		{
			sum = 0.0;
			for(k = 0; k < length; k++)
			{
				sum = (sum + first[i*length+k] * second[k*length+j]);
			}
			(*result)[i*length+j] = sum;
		}
	}
	return 0;
}

int main(int argc, char* argv[])
{
	struct timespec time_before, time_after;
	double *matrix_first, *matrix_second, *matrix_result;
	double value_time = 0.0;
	int error_flag = 0b0;
	int quantity_thread = 0;
	int length_square_matrix = 0;
	srand(time(NULL));
	error_flag = (error_flag | Check_Argc(argc));
	error_flag = (error_flag | Convert_Char_To_Int(&quantity_thread, argv[INDEX_QUANTITY_THREAD_FROM_ARGV]));
	error_flag = (error_flag | Convert_Char_To_Int(&length_square_matrix, argv[INDEX_LENGTH_SQUARE_MATRIX_FROM_ARGV]));
	if(length_square_matrix > MAX_LENGTH_SQUARE_MATRIX)
	{
		return (error_flag | ERROR_SIZE_MATRIX_TOO_LARGE);
	}
	error_flag = Fill_Rand_Square_Matrix(&matrix_first, length_square_matrix);
	error_flag = Fill_Rand_Square_Matrix(&matrix_second, length_square_matrix);
	#ifdef PRINT_DEBUG
	printf("\nmatrix_first:\n");
	Print_Square_Matrix(matrix_first, length_square_matrix);
	printf("\nmatrix_second:\n");
	Print_Square_Matrix(matrix_second, length_square_matrix);
	#endif
	clock_gettime(CLOCK_REALTIME, &time_before);
	error_flag = (error_flag | Multiple_Square_Matrix_With_Open_MP(&matrix_result, matrix_first, matrix_second, length_square_matrix, quantity_thread));
	clock_gettime(CLOCK_REALTIME, &time_after);
	value_time = ((double)(time_after.tv_sec - time_before.tv_sec) + (double)(time_after.tv_nsec - time_before.tv_nsec) / 1e9);
	#ifdef PRINT_DEBUG
	printf("\nmatrix_result:\n");
	Print_Square_Matrix(matrix_result, length_square_matrix);
	#endif
	free(matrix_first);
	free(matrix_result);
	free(matrix_second);
	matrix_first = NULL;
	matrix_second = NULL;
	matrix_result = NULL;
	error_flag = (error_flag | Write_In_Table_Time(quantity_thread, value_time));
	return error_flag;
}
