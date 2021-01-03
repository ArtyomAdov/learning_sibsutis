#include "adov_fourier.c"

#include <stdio.h>
#include <stdlib.h>

#define TRIGGER_TEST

#define ERROR_ALLOCATION_MEMORY 0b00000001
#ifdef TRIGGER_TEST

#define ERROR_TEST_NUMBER_ARRAY 0b10000000

#define TEST_SIZE_ARRAY_FIRST 3
#define TEST_SIZE_ARRAY_SECOND 2

#define NUMBER_FIRST_ARRAY '1'
#define NUMBER_SECOND_ARRAY '2'

int Fill_Test(complex* array[], int size_array, int quantity_element, char number_array)
{
	(*array) = (complex*)calloc((size_array + size_array),sizeof(complex));
	#if 1
	if(*array == NULL)
	{
		return ERROR_ALLOCATION_MEMORY;
	}
	if(number_array == '1')
	{
		for(short int i = 0; i < quantity_element; i++)
		{
			(*array)[i].real = (double)(i + 1);
			(*array)[i].imaginary = 0.0;
		}
		return 0;	
	}
	if(number_array == '2')
	{
		for(short int i = 0; i < quantity_element; i++)
		{
			(*array)[i].real = (double)(size_array + i + 1);
			(*array)[i].imaginary = 0.0;
		}
		return 0;
	}
	#endif
	return ERROR_TEST_NUMBER_ARRAY;
}
#endif

int Convulation(complex* array_result[], complex array_first[], complex array_second[], int size_array)
{
	complex complex_coefficient;
	*array_result = (complex*)calloc(size_array,sizeof(complex));
	if(array_result == NULL)
	{
		return ERROR_ALLOCATION_MEMORY;
	}
	complex_coefficient = Convert_Real_In_Complex((double)size_array);
	for(short int i = 0; i < size_array; i++)
	{
		(*array_result)[i] = Multiplication_Complex_Number(array_first[i], array_second[i]);
		(*array_result)[i] = Multiplication_Complex_Number((*array_result)[i], complex_coefficient);
	}
	return 0;
}

int main()
{
	complex* array_first = NULL;
	complex* array_second = NULL;
	complex* array_result = NULL;
	int error_flag = 0b0;
	int size_array_first = 0;
	int size_array_second = 0;
	#ifdef TRIGGER_TEST
	size_array_first = TEST_SIZE_ARRAY_FIRST;
	size_array_second = TEST_SIZE_ARRAY_SECOND;
	if(size_array_first > size_array_second)
	{
		error_flag = (error_flag | Fill_Test(&array_first, size_array_first, size_array_first, NUMBER_FIRST_ARRAY));
		error_flag = (error_flag | Fill_Test(&array_second, size_array_first, size_array_second, NUMBER_SECOND_ARRAY));
		size_array_first = (size_array_first + size_array_first);
	}
	else
	{
		error_flag = (error_flag | Fill_Test(&array_first, size_array_second, size_array_first, NUMBER_FIRST_ARRAY));
		error_flag = (error_flag | Fill_Test(&array_second, size_array_second, size_array_second, NUMBER_SECOND_ARRAY));
		size_array_first = (size_array_second + size_array_second);
	}
	#endif
	printf("ORIGINAL:\n");
	Print_Complex_Array(array_first, size_array_first);
	Print_Complex_Array(array_second, size_array_first);
	array_first = Direct_Discrete_Conversion(array_first, size_array_first);
	array_second = Direct_Discrete_Conversion(array_second, size_array_first);
	printf("DIRECT:\n");
	Print_Complex_Array(array_first, size_array_first);
	Print_Complex_Array(array_second, size_array_first);
	printf("CONVULATION:\n");
	error_flag = (error_flag | Convulation(&array_result, array_first, array_second, size_array_first));
	free(array_first);
	free(array_second);
	array_first = NULL;
	array_second = NULL;
	Print_Complex_Array(array_result, size_array_first);
	printf("INVERSE:\n");
	array_result = Inverse_Discrete_Conversion(array_result, size_array_first);
	Print_Complex_Array(array_result, size_array_first);
	free(array_result);
	array_result = NULL;
	return error_flag;
}
