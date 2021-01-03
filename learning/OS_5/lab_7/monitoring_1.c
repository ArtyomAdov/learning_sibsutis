#include <windows.h>
#include <psapi.h>
#include <stdlib.h>
#include <stdio.h>

#define TRIGGER_TEST

#define ERROR_ALLOCATION_MEMORY 0b00000001
#define ERROR_OPEN_FILE_TEMP_TXT 0b00000010
#define ERROR_ENUM_PROCESS_MODULS 0b00000100

#ifdef TRIGGER_TEST
#define TEST_PROCESS_NAME "programm_1.exe"
#define TEST_SIZE_PROCESS_NAME 20
#endif 

#define SIZE_STRING_TO_SYSTEM_COMMAND 31
#define CAPACITY_DIGIT_TO_DECIMAL 10
#define QUANTITY_NEED_ITERATION_PROGRAMM 5
#define TIME_DELAY_PROGRAMM_IN_THOUSANDTH_OF_SECOND 7000

#define FILE_NAME_FOR_TEMP_TXT "temp.txt"
#define READ_ONLY "r"

#define FIRST_CODE_NUMBER_TO_INTEGER_SYMBOL 0x30
#define LAST_CODE_NUMBER_TO_INTEGER_SYMBOL 0x39
#define CONVERT_CODE_NUMBER_FROM_SYMBOL 0x0F

int Copy_String_In_Char_Array(char* process_name[], char copy_string[], int size_process_name)
{
	*process_name = (char*)calloc(size_process_name,sizeof(char)); //allocation need memory
	if(*process_name == NULL) //if allocation fail
	{
		return ERROR_ALLOCATION_MEMORY;
	}
	for(short int i = 0; i < size_process_name; i++)
	{
		(*process_name)[i] = copy_string[i]; //copying in char array to char array
	}
	return 0;
}

int Get_Pid_Need_Procces_By_Name(int* pID, char* process_name, int size_process_name)
{
	FILE* file = NULL; //pointer for file
	char* system_command = NULL; // char array for system command string
	char symbol = '0';
	system_command = (char*)calloc((SIZE_STRING_TO_SYSTEM_COMMAND+size_process_name),sizeof(char));//allocation memmory
	if(system_command == NULL)
	{
		return ERROR_ALLOCATION_MEMORY;
	}
	sprintf(system_command,"tasklist | findstr %s > temp.txt", process_name); //fill system command by need command string
	system(system_command); //execute system command
	free(system_command); //free memory for char array system command
	system_command = NULL;
	file = fopen(FILE_NAME_FOR_TEMP_TXT,READ_ONLY);//open temp txt file in ode read
	if(file == NULL)
	{
		return ERROR_OPEN_FILE_TEMP_TXT;
	}
	do
	{
		symbol = getc(file); //read one symbol from temp file 
	} while((symbol != ' ') && (!feof(file))); //while dont run first field in result tasklist command
	do
	{
		symbol = getc(file); //read one symbol from temp file while not digital
	} while((symbol < FIRST_CODE_NUMBER_TO_INTEGER_SYMBOL) || (symbol > LAST_CODE_NUMBER_TO_INTEGER_SYMBOL) || feof(file));
	do
	{
		(*pID) = ((*pID) + (symbol & CONVERT_CODE_NUMBER_FROM_SYMBOL)); // convert digital char in digital int 
		(*pID) = ((*pID) * CAPACITY_DIGIT_TO_DECIMAL); //shift right number of digit in decimal system
		symbol = getc(file); //read one symbol from temp file while read digit char
	}while((symbol >= FIRST_CODE_NUMBER_TO_INTEGER_SYMBOL) && (symbol <= LAST_CODE_NUMBER_TO_INTEGER_SYMBOL) && !feof(file));
	(*pID) = ((*pID) / CAPACITY_DIGIT_TO_DECIMAL); // shift left number of digit in decimal system
	fclose(file); // close file 
	return 0;
}

int main()
{
	char modName[MAX_PATH]; //char array for path modules name
	char* process_name = NULL;
	int error_flag = 0b0;
	int size_process_name = 0;
	int iteration = 0;
	DWORD pID = 0; //id process
	HANDLE pHndl; //handle for process
	HMODULE* modHndls; //handle for modules
	DWORD b_alloc = 8, b_needed = 0; //size for allocation memory for array handle for moduls(in quantity bytes)
	#ifdef TRIGGER_TEST
	size_process_name = TEST_SIZE_PROCESS_NAME; // test quantity symbol in process name
	#endif
	if(Copy_String_In_Char_Array(&process_name, TEST_PROCESS_NAME, size_process_name) != 0) //copying name process in char arrray
	{
		return ERROR_ALLOCATION_MEMORY;
	}
	error_flag = (error_flag | Get_Pid_Need_Procces_By_Name(&pID, process_name, size_process_name)); //get processID by name this process
	if(error_flag != 0)
	{
		return error_flag;
	}
	pHndl = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID); //get handle for process by processID
	do
	{
		while(1)
		{
			modHndls=(HMODULE*)malloc(b_alloc); //allocation memory in quantity b_alloc(size in byte)
			if(EnumProcessModules(pHndl, modHndls, b_alloc, &b_needed) == 0) //get handle for every modules in specified dll(pHndl)
			{
				return ERROR_ENUM_PROCESS_MODULS;
			}
//			printf("%u %u\n", pID, pHndl);
//			printf("%u %u\n",b_alloc, b_needed);
			if(b_needed <= b_alloc)  // if allocation memory less need
			{
				break;	
			}
			else
			{
				free(modHndls); //free past allocation memory
				b_alloc = b_needed; //assign allocation size - needed quantity byte
			}
		}
		for(int i = 0; i < ((b_needed/sizeof(DWORD))); i++)
		{
			GetModuleBaseName(pHndl, modHndls[i], (LPSTR)modName, sizeof(modName)); //get name dll
			printf("%u\t%s", modHndls[i], modName);
			GetModuleFileName(modHndls[i], (LPSTR)modName, sizeof(modName)); //get full path for dll
			printf("\t:%s\n",modName);
		}
		Sleep(TIME_DELAY_PROGRAMM_IN_THOUSANDTH_OF_SECOND); //program execution delay to allow time for the programm loaded/unloaded the modules(library.dll)
		iteration++; //increment iteration
	}while(iteration < QUANTITY_NEED_ITERATION_PROGRAMM);
	printf("End monitoring\n");
	getch();
	return error_flag;
}
