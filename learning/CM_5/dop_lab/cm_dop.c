#include <stdio.h>
#include <stdlib.h>

#define ERROR_ALLOCATION_MEMORY 0b00000001
#define ERROR_ONE_NUMBER_IN_MESSAGE 0b00000010

#define NUMBER_FOR_SAVE_FROM_DIVISION_BY_ZERO 0.5
#define DIGIT_CAPACITY_IN_DECIMAL 10
#define SIZE_MESSAGE 20

#define FIRST_CODE_SYMBOL_BY_DIGIT 0x30
#define LAST_CODE_SYMBOL_BY_DIGIT 0x39
#define CONVERT_CODE_SYMBOL_BY_DIGIT_IN_NUMBER 0x0F

void Print_Array_Integer(int array[], int size)
{
	for(short int i = 0; i < size; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}

int Convert_Char_Array_To_Integer_Array(int* integer_array[], int* size_array, char message[])
{
	for(short int i = 0; ;i++)
	{
		*size_array = i;
		if((message[i] < FIRST_CODE_SYMBOL_BY_DIGIT) || (message[i] < FIRST_CODE_SYMBOL_BY_DIGIT))
		{
			break;
		}
	}
	*integer_array = (int*)calloc(*size_array,sizeof(int));
	if(*integer_array == NULL)
	{
		return ERROR_ALLOCATION_MEMORY;
	}
	for(short int i = 0; i < *size_array; i++)
	{
		(*integer_array)[i] = (message[i] & CONVERT_CODE_SYMBOL_BY_DIGIT_IN_NUMBER);
	}
	return 0;
}

int Multiple_By_Column(int* array_result[], int array_first[], int array_second[], int* size_result, int size_first, int size_second)
{
	int* buffer = NULL;
	int temp = 0;
	temp = (size_first + size_second);
	buffer = (int*)calloc(temp, sizeof(int));
	for(short int i = (size_first - 1); i > -1; i--)
	{
		for(short int j = (size_first - 1); j > -1; j--)
		{
			buffer[i+j+1] = (buffer[i+j+1] + (array_first[i] * array_second[j]));
		}
	}
	for(short int i = (temp - 1); i > -1; i--)
	{
		if((DIGIT_CAPACITY_IN_DECIMAL <= buffer[i]))
		{
			buffer[i-1] = (buffer[i-1] + buffer[i] / DIGIT_CAPACITY_IN_DECIMAL);
			buffer[i] = (buffer[i] % DIGIT_CAPACITY_IN_DECIMAL);
		}
	}
	*size_result = temp;
	for(short int i = 0; buffer[i] == 0; i++)
	{
		*size_result = *size_result - 1;
	}
	*array_result = (int*)calloc(*size_result, sizeof(int));
	for(short int j = (temp - *size_result), i = 0; i < *size_result; i++, j++)
	{
		(*array_result)[i] = buffer[j];
	}
	return 0;
}

int main(char argv[])
{
	char first_message[] = {"3125"};
	char second_message[] = {"16"};
	int* array_number_first = NULL;
	int* array_number_second = NULL;
	int* array_number_result = NULL;
	int error_flag = 0b0;
	int size_array_first = 0;
	int size_array_second = 0;
	int size_array_result = 0;
	error_flag = (error_flag | Convert_Char_Array_To_Integer_Array(&array_number_first, &size_array_first, first_message));
	error_flag = (error_flag | Convert_Char_Array_To_Integer_Array(&array_number_second, &size_array_second, second_message));
	Print_Array_Integer(array_number_first, size_array_first);
	Print_Array_Integer(array_number_second, size_array_second);
	error_flag = (error_flag | Multiple_By_Column(&array_number_result, array_number_first, array_number_second, &size_array_result, size_array_first, size_array_second));
	Print_Array_Integer(array_number_result, size_array_result);
	return error_flag;
}
