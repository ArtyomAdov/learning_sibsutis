#include "death_error.h"
#include "death_arg.h"
#include "death_char.h"
#include "death_file.h"
#include "death_matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

// #define PRINT_DEBUG

typedef struct Data_For_Thread
{
	int start;
	int final;
	int length;
	double* first;
	double* second;
	double* result;
} data_thread;

void* Function_By_Thread(void* original)
{
	data_thread* data = (data_thread*)original;
	double* a = data->first;
	double* b = data->second;
	double* c = data->result;
	double sum = 0.0;
	int begin = data->start;
	int end = data->final;
	int size = data->length;
	for(short int i = begin; i < end; i++)
	{
		for(short int j = 0; j < size; j++)
		{
			sum = 0.0;
			for(short int k = 0; k < size; k++)
			{
				sum = (sum + a[i*size+k] * b[k*size+j]);
			}
			c[i*size+j] = sum;
		}
	}
	pthread_exit(0);
}

int Multiple_Square_Matrix_With_Thread(double* result[], double first[], double second[], int length, int quantity_thread)
{
	pthread_t* array_pointer_thread = NULL;
	data_thread* data = NULL;
	int optimal = 0;
	array_pointer_thread = (pthread_t*)calloc(quantity_thread,sizeof(pthread_t));
	if(array_pointer_thread == NULL)
	{
		return ERROR_ALLOCATION_MEMORY;
	}
	data = (data_thread*)calloc((quantity_thread+1),sizeof(data_thread));
	if(data == NULL)
	{
		return ERROR_ALLOCATION_MEMORY;
	}
	*result = (double*)calloc((length*length),sizeof(double));
	if(*result == NULL)
	{
		return ERROR_ALLOCATION_MEMORY;
	}
	optimal = (length / quantity_thread);
	if((length % quantity_thread) != 0)
	{
		for(short int i = 0, temp = 0; i < quantity_thread; i++, temp = (temp + optimal))
		{
			data[i+1].first = first;
			data[i+1].second = second;
			data[i+1].result = (*result);
			data[i+1].length = length;
			data[i+1].start = temp;
			data[i+1].final = (temp + optimal);
			if(i == (quantity_thread - 1))
			{
				data[i+1].final = (data[i+1].final + 1);
			}
			pthread_create(&(array_pointer_thread[i]), NULL, Function_By_Thread, &(data[i+1]));
		}
	}
	else
	{
		for(short int i = 0, temp = 0; i < quantity_thread; i++, temp = (temp + optimal))
		{
			data[i+1].first = first;
			data[i+1].second = second;
			data[i+1].result = (*result);
			data[i+1].length = length;
			data[i+1].start = temp;
			data[i+1].final = (temp + optimal);
			pthread_create(&(array_pointer_thread[i]), NULL, Function_By_Thread, &(data[i+1]));
		}
	}
	for(short int i = 0; i < quantity_thread; i++)
	{
		pthread_join(array_pointer_thread[i], NULL);
	}
	free(array_pointer_thread);
	array_pointer_thread = NULL;
	for(short int i = 0, li = (i * length); i < quantity_thread; i++, li = (i * length))
	{
		for(short int j = 0; j < length; j++)
		{
			(*result)[li + j] = data[i+1].result[j];
		}
	}
	free(data);
	data = NULL;
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
	error_flag = (error_flag | Multiple_Square_Matrix_With_Thread(&matrix_result, matrix_first, matrix_second, length_square_matrix, quantity_thread));
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
