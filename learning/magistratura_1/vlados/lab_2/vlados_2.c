#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERROR_OPEN_FILE_FOR_READ 0b00000001
#define ERROR_OPEN_FILE_FOR_WRITE 0b00000010
#define ERROR_ALLOCATION_MEMORY 0b00000100

#define FILE_NAME_ALPHABET_TXT "alphabet.txt"
#define FILE_NAME_MESSAGE_TXT "message.txt"
#define FILE_NAME_ENCODED_TXT "encoded.txt"

#define READ_ONLY "r"
#define WRITE_ONLY "w"

void Print_Char_Array(char array[], int size)
{
	for(short int i = 0; i < size; i++)
	{
		printf("%c",array[i]);
	}
	printf("\n");
}

int Read_From_File(char* array[], int* size, char file_name[])
{
	FILE* file = NULL;
	file = fopen(file_name, READ_ONLY);
	if(file == NULL)
	{
		return ERROR_OPEN_FILE_FOR_READ;
	}
	fscanf(file,"%d", &(*size));
	getc(file); //skip symbol \n
	*array = (char*)calloc(*size, sizeof(char));
	if(*array == NULL)
	{
		return ERROR_ALLOCATION_MEMORY;
	}
	fread(*array, sizeof(char), *size, file);
	fclose(file);
	return 0;
}

int Write_In_File(bool array[], int size, char file_name[])
{
	FILE* file = NULL;
	file = fopen(file_name, WRITE_ONLY);
	if(file == NULL)
	{
		return ERROR_OPEN_FILE_FOR_WRITE;
	}
	fprintf(file,"%d", size);
	putc('\n',file);
	fwrite(array, sizeof(char), size, file);
	fclose(file);
	return 0;
}

int Encoded_Message_By_Move_To_Front(bool* array_encoded[], int* size_encoded, char array_message[], int size_message, char array_alphabet[], int size_alphabet)
{
	//интовоый массив сообщений и потом прогнать по первой лабе и тогда получится енкодед
	return 0;
}

int main()
{
	char* array_alphabet = NULL;
	char* array_message = NULL;
	bool* array_encoded = NULL;
	int size_alphabet = 0;
	int size_message = 0;
	int size_encoded = 0;
	int error_flag = 0b0;
	error_flag = (error_flag | Read_From_File(&array_alphabet, &size_alphabet, FILE_NAME_ALPHABET_TXT));
	printf("alphabet:\n");
	Print_Char_Array(array_alphabet, size_alphabet);
	error_flag = (error_flag | Read_From_File(&array_message, &size_message, FILE_NAME_MESSAGE_TXT));
	printf("original message:\n");
	Print_Char_Array(array_message, size_message);
	error_flag = (error_flag | Encoded_Message_By_Move_To_Front(&array_encoded, &size_encoded, array_message, size_message, array_alphabet, size_alphabet));
	printf("encoded message:\n");
	Print_Char_Array((char*)array_encoded, size_encoded);//mb encod in char
	error_flag = (error_flag | Write_In_File(array_encoded, size_encoded, FILE_NAME_ENCODED_TXT));
	return error_flag;
}
