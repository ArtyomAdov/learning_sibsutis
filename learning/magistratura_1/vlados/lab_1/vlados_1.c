#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define ERROR_ALLOCATION_MEMORY 0b00000001

#define COEFFICIENT_FOR_CONVERT_TO_BINARY 2
#define DIGIT_CAPACITY_IN_DECIMAL 10
#define QUANTITY_AUTO_ONE_DIGIT 1

#define TRIGGER_FI_ZERO 0
#define TRIGGER_FI_ONE 0
#define TRIGGER_FI_TWO 1

void Print_Encoded_Numeric(bool array_numeric[], int size_array)
{
	for(short int i = 0; i < size_array; i++)
	{
		printf("%d",array_numeric[i]);
	}
	printf("\n");
}

int Decoding_By_Fi_Zero(int* source_numeric, bool array_numeric[], int size_array)
{
	*source_numeric = size_array - 1;
	return 0;
}

int Encoding_By_Fi_Zero(int source_numeric, bool* array_numeric[], int* size_array)
{
	*size_array = source_numeric + 1;
	(*array_numeric) = (bool*)calloc(*size_array,sizeof(bool));
	if(*array_numeric == NULL)
	{
		return ERROR_ALLOCATION_MEMORY;
	}
	if(*array_numeric == NULL)
	{
		return ERROR_ALLOCATION_MEMORY;
	}
	(*array_numeric)[source_numeric] = 1;
	return 0;
}

int Get_Binary_Performance(int source_numeric, bool* binary_numeric[], int* size_binary)
{
	int temp = 0;
	temp = source_numeric;
	do
	{
		*size_binary = *size_binary + 1;
		source_numeric = source_numeric / COEFFICIENT_FOR_CONVERT_TO_BINARY;
	} while(source_numeric > 0);
	(*binary_numeric) = (bool*)calloc(*size_binary,sizeof(bool));
	if(*binary_numeric == NULL)
	{
		return ERROR_ALLOCATION_MEMORY;
	}
	source_numeric = temp;
	for(short int i = (*size_binary - 1); i >= 0; i--)
	{
		(*binary_numeric)[i] = (source_numeric % COEFFICIENT_FOR_CONVERT_TO_BINARY);
		source_numeric = (source_numeric / COEFFICIENT_FOR_CONVERT_TO_BINARY);
	}
	return 0;
}

int Encoding_By_Fi_One(bool binary_numeric[], int size_binary, bool* array_numeric[], int* size_array)
{
	*size_array = size_binary + size_binary;
	(*array_numeric) = (bool*)calloc(*size_array,sizeof(bool));
	if(*array_numeric == NULL)
	{
		return ERROR_ALLOCATION_MEMORY;
	}
//	for(short int i = 0; i < size_binary; i++)//чекунть работает ли без -- чекнул работает
//	{
//		(*array_numeric)[i] = 0;
//	}
	for(short int j = 0,i = size_binary; i < *size_array; j++, i++)
	{
		(*array_numeric)[i] = binary_numeric[j];
	}
	return 0;
}

int Decoding_By_Fi_One(int* source_numeric, bool array_numeric[], int size_array)
{
	*source_numeric = 0;
	int start_binary = 0;
	for(short int i = 0; i < size_array; i++)
	{
		if(array_numeric[i] == 1)
		{
			start_binary = i;
			break;
		}
	}
	for(short int j = 0, i = (size_array - 1); i >= start_binary; i--, j++)
	{
//		printf("%d\n",*source_numeric);
//		printf("%d\n",j);
		*source_numeric = *source_numeric + ((int)array_numeric[i] * pow(2,j));//
	}
	return 0;
}

int Encoding_By_Fi_Two(bool binary_numeric[], int size_binary, bool* array_numeric[], int* size_array)
{
	bool* temp_binary = NULL;
	int temp_size = 0;
	if(Get_Binary_Performance(size_binary, &temp_binary, &temp_size) != 0)
	{
		return ERROR_ALLOCATION_MEMORY;
	}
	*size_array = (QUANTITY_AUTO_ONE_DIGIT + temp_size + (temp_size - 1) + (size_binary - 1));
	*array_numeric = (bool*)calloc(*size_array,sizeof(bool));
	if(*array_numeric == NULL)
	{
		return ERROR_ALLOCATION_MEMORY;
	}
//	for(short int i = 0; i < temp_size; i++) //itak nuli iz za calloc
//	{
//		(*array_numeric)[i] = 0;
//	}
	(*array_numeric)[temp_size] = 1; 
	for(short int i = (temp_size + 1), j = 1; ((i < (temp_size + temp_size)) && (j < temp_size)); i++, j++)
	{
		(*array_numeric)[i] = temp_binary[j];
	}
	for(short int i = (temp_size + temp_size), j = 1; ((i < *size_array) && (j < size_binary)); i++, j++)
	{
		(*array_numeric)[i] = binary_numeric[j];
	}
	return 0;
}

int Decoding_By_Fi_Two(int* source_numeric, bool array_numeric[], int size_array)
{
	int temp_index = 0;
	for(short int i = 0; array_numeric[i] != 1; i++)
	{
		temp_index++;
	}
	for(short int i = temp_index, j = (temp_index + temp_index - 1); i < j; i++)
	{
		temp_index++;
	}
	for(short int i = (size_array - 1), j = 0; i > temp_index; i--, j++)
	{
		*source_numeric = *source_numeric + ((int)array_numeric[i] * pow(2,j));
	}
	*source_numeric = *source_numeric + (1 * pow(2,(size_array - temp_index - 1)));
	return 0;
}

int main()
{
	bool* array_numeric = NULL;
	bool* binary_numeric = NULL;
	int error_flag = 0b0;
	int source_numeric = 0;
	int size_array = 0;
	int size_binary = 0;
	int test_iteration = 5000;//
	printf("Write source numeric\n");
	scanf("%d",&source_numeric);
	//
	#if TRIGGER_FI_ZERO
	error_flag = (error_flag | Encoding_By_Fi_Zero(source_numeric, &array_numeric, &size_array));
	source_numeric = 0;
	Print_Encoded_Numeric(array_numeric,size_array);
	error_flag = (error_flag | Decoding_By_Fi_Zero(&source_numeric, array_numeric, size_array));
	printf("Decoded numeric: %d\n",source_numeric);
	size_array = 0;
	free(array_numeric);
	array_numeric = NULL;
	#endif
	//
	#if TRIGGER_FI_ONE
	if(source_numeric != 0)
	{
		error_flag = (error_flag | Get_Binary_Performance(source_numeric, &binary_numeric, &size_binary));
		error_flag = (error_flag | Encoding_By_Fi_One(binary_numeric, size_binary, &array_numeric, &size_array));	
	}
	else
	{
		size_array = 1;
		array_numeric = (bool*)calloc(size_array,sizeof(bool));
		if(array_numeric == NULL)
		{
			return ERROR_ALLOCATION_MEMORY;
		}
		array_numeric[0] = 1;
	}
	source_numeric = 0;
	Print_Encoded_Numeric(array_numeric,size_array);
	error_flag = (error_flag | Decoding_By_Fi_One(&source_numeric, array_numeric, size_array));
	printf("Decoded numeric: %d\n",source_numeric);
	//
	size_array = 0;
	size_binary = 0;
	free(binary_numeric);
	binary_numeric = NULL;
	free(array_numeric);
	array_numeric = NULL;
	#endif
	//
	#if TRIGGER_FI_TWO
//	while(test_iteration < 32000)
	{
//		test_iteration++;
//		source_numeric = test_iteration;
		printf("Source numeric: %d\n",source_numeric);
		error_flag = (error_flag | Get_Binary_Performance(source_numeric, &binary_numeric, &size_binary));
		error_flag = (error_flag | Encoding_By_Fi_Two(binary_numeric, size_binary, &array_numeric, &size_array));
		source_numeric = 0;
		Print_Encoded_Numeric(array_numeric,size_array);
		error_flag = (error_flag | Decoding_By_Fi_Two(&source_numeric, array_numeric, size_array));
//		if(source_numeric != test_iteration)
//		{
//			printf("\nELDA\n");
//			return -1;
//		}
		printf("Decoded numeric: %d\n",source_numeric);
		size_array = 0;
		size_binary = 0;
		free(binary_numeric);
		binary_numeric = NULL;
		free(array_numeric);
		array_numeric = NULL;
	}
	#endif
	return error_flag;
}
