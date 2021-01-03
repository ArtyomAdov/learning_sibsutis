#include <windows.h>
#include <psapi.h>
#include <imagehlp.h>
#include <stdlib.h>
#include <stdio.h>

//#define TRIGGER_SYSTEM_COMMAND
//#define TRIGGER_USE_MONITORING

#define ERROR_QUANTITY_ARGUMENT 0b00000001
#define ERROR_SECOND_ARGUMENT 0b00000010
#define ERROR_THIRD_ARGUMENT 0b00000100
#define ERROR_UNKNOWN_MAP_AND_LOAD 0b00001000
#define ERROR_ALLOCATION_MEMORY 0b00010000
#define ERROR_ENUM_PROCESS_MODULS 0b00100000
#define ERROR_FOUND_PROCESS 0b10000000

#ifdef TRIGGER_SYSTEM_COMMAND

#define ERROR_OPEN_FILE_TEMP_TXT 0b01000000

#define SIZE_STRING_TO_SYSTEM_COMMAND 31
#define CAPACITY_DIGIT_TO_DECIMAL 10
#define TEST_SIZE_PROCESS_NAME 20

#define FILE_NAME_FOR_TEMP_TXT "temp.txt"
#define READ_ONLY "r"

#define FIRST_CODE_NUMBER_TO_INTEGER_SYMBOL 0x30
#define LAST_CODE_NUMBER_TO_INTEGER_SYMBOL 0x39
#define CONVERT_CODE_NUMBER_FROM_SYMBOL 0x0F

#else

#define ERROR_ENUM_PROCESSES 0b01000000

#endif

#define GET_EXPORT_FUNCTION 'E'
#define GET_IMPORT_FUNCTION 'I'

#define CORRECT_QUANTITY_ARGUMENT 3

#ifdef TRIGGER_USE_MONITORING
int Copy_String_In_Char_Array(char* process_name[], char copy_string[], int* size_process_name)
{
	for(short int i = 0; copy_string[i] != '\0'; i++) //counting quantity element in copt string
	{
		(*size_process_name)++; //increment future size process name
	}
	*process_name = (char*)calloc(*size_process_name,sizeof(char)); //allocation need memory
	if(*process_name == NULL)
	{
		return ERROR_ALLOCATION_MEMORY;
	}
	for(short int i = 0; i < *size_process_name; i++) 
	{
		(*process_name)[i] = copy_string[i]; //copying in char array to char array
	}
	return 0;
}

int Get_Pid_Need_Procces_By_Name(int* pID, char process_name[], int size_process_name)
{
	#ifdef TRIGGER_SYSTEM_COMMAND
	FILE* file = NULL;
	char* system_command = NULL;
	char symbol = '0';
	system_command = (char*)calloc((SIZE_STRING_TO_SYSTEM_COMMAND+size_process_name),sizeof(char));
	if(system_command == NULL)
	{
		return ERROR_ALLOCATION_MEMORY;
	}
	sprintf(system_command,"tasklist | findstr %s > temp.txt", process_name);
	system(system_command);
	free(system_command);
	system_command = NULL;
	file = fopen(FILE_NAME_FOR_TEMP_TXT,READ_ONLY);
	if(file == NULL)
	{
		return ERROR_OPEN_FILE_TEMP_TXT;
	}
	do
	{
		symbol = getc(file);
	} while((symbol != ' ') && (!feof(file)));
	do
	{
		symbol = getc(file);
	} while((symbol < FIRST_CODE_NUMBER_TO_INTEGER_SYMBOL) || (symbol > LAST_CODE_NUMBER_TO_INTEGER_SYMBOL) || feof(file));
	do
	{
		(*pID) = ((*pID) + (symbol & CONVERT_CODE_NUMBER_FROM_SYMBOL));
		(*pID) = ((*pID) * CAPACITY_DIGIT_TO_DECIMAL);
		symbol = getc(file);
	}while((symbol >= FIRST_CODE_NUMBER_TO_INTEGER_SYMBOL) && (symbol <= LAST_CODE_NUMBER_TO_INTEGER_SYMBOL) && !feof(file));
	(*pID) = ((*pID) / CAPACITY_DIGIT_TO_DECIMAL);
	fclose(file);
	#else
	char temp_process_name[1000]; //temp array for process name
	DWORD buffer_process[1024]; //temp array for list process id
	DWORD size_buffer_process = 0; // significant element in buffer process
	HANDLE pHndl; //handle for process
	int index_equally = 0; //need index process
	int size_temp_process = 0; //significant element in char array process name
    if(EnumProcesses(buffer_process, sizeof(buffer_process), &size_buffer_process) == 0) //get process id for every process
    {
        return ERROR_ENUM_PROCESSES;
    }
    size_buffer_process = (size_buffer_process / sizeof(DWORD)); //calculate how many process identifiers were returned.
    for(short int i = 0; i < (short int)size_buffer_process; i++) //print the name and process identifier for each process.
    {
		pHndl = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, buffer_process[i]);  //get handle for process by processID
		GetProcessImageFileNameA(pHndl, temp_process_name, 1000); //get full path for process by handle on process
		size_temp_process = 0; //reset significant element in char array process name
		for(short int j = 0; ((j < 1000) && (temp_process_name[j] != '\0')); j++) // get significant element in char array process name
		{
			size_temp_process++;//increment significant element in char array process name
		}
		for(short int k = (size_temp_process - 1), j = (size_process_name - 1); ((k >-1) && (j >-1)); j--, k--)
		{
			if(process_name[j] != temp_process_name[k]) //if last symbol in process not equally
			{
				index_equally = -1; //reset index
				break; //end cycle
			}
			else
			{
				index_equally = i; //remember index for equally process names
			}
		}
		if(index_equally != -1)
		{
			*pID = buffer_process[i];//appoint process id for equally process names
			break;
		}
    }
	#endif
	return 0;
}
#endif
int Check_Argc(int argc)
{
    if(argc == CORRECT_QUANTITY_ARGUMENT)
    {
        return 0;
    }
    printf("Error: incorect quantity argument in programm - need three\n");
    return ERROR_QUANTITY_ARGUMENT;
}

int Get_Export_Function(PCSTR library_name)
{
	LOADED_IMAGE LoadedImage;
    PUCHAR BaseAddress;
    DWORD RVAExpDir, VAExpAddress;
    IMAGE_EXPORT_DIRECTORY* ExpTable;
    char* sName;
    DWORD nNames;
    char* pName;
    char** pNames;
    if(!MapAndLoad(library_name, NULL, &LoadedImage, TRUE, TRUE)) //load pe-file
    {
        printf("Need file dont find\n");
        printf("Maybe incorrect second argument, please check this\n");
        printf("Example correct second argument imagehlp.dll");
        return ERROR_UNKNOWN_MAP_AND_LOAD;
    }
    if(LoadedImage.FileHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size)//check size export directory
    {//if not zero
        BaseAddress = LoadedImage.MappedAddress; //get base adress loaded module
        printf("0x%lx - Base Address\n", (unsigned long)BaseAddress);
        RVAExpDir = LoadedImage.FileHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress; //get relativity virtual adress for export table
        printf("0x%lx -RVA\n", RVAExpDir);
        VAExpAddress = (DWORD)ImageRvaToVa(LoadedImage.FileHeader, BaseAddress, RVAExpDir, NULL); //get virtual adress for array string by him rva
        printf("0x%lx -VA\n",VAExpAddress);
        ExpTable=(IMAGE_EXPORT_DIRECTORY*)VAExpAddress;
        sName = (char*)ImageRvaToVa(LoadedImage.FileHeader, BaseAddress, ExpTable->Name, NULL); //get virtual adress string name pe-file by him rva
        printf("Name of PEF: %s\n", sName);
        pNames = (char**)ImageRvaToVa(LoadedImage.FileHeader, BaseAddress, ExpTable->AddressOfNames, NULL); //get virtual adress array string by him rva
        nNames = ExpTable->NumberOfNames; //get quantity export name from table export
        printf("Export:\n");
        for(unsigned int i=0; i<nNames; i++)
        {
            pName = (char*)ImageRvaToVa(LoadedImage.FileHeader, BaseAddress, (DWORD)*pNames, NULL);//get virtual adress name with index i by him rva
            printf("%s\n", pName);
            *pNames++;//go next string
        }
    }
    else
    {//if size entry directory equally zero
        printf("No export directory\n");
    }
    UnMapAndLoad(&LoadedImage);//unloaded pe-file
    return 0;
}

int Check_Second_Argument(char* library_name)
{
	if(library_name != NULL)
	{
		return 0;
	}
	return ERROR_SECOND_ARGUMENT;
}

int Get_Import_Function(PCSTR library_name)
{
	#ifdef TRIGGER_USE_MONITORING
	char modName[MAX_PATH];
	int error_flag = 0b0;
	int temp_err = 0;//
	char* process_name = NULL;
	int size_process_name = 0;//TEST_SIZE_PROCESS_NAME;
	DWORD pID = -1; //id process
	HANDLE pHndl; //handle for process
	HMODULE* modHndls = NULL; //handle for modules
	DWORD b_alloc = 8, b_needed = 0; //size for allocation memory for array handle for moduls(in quantity bytes)
	if(Copy_String_In_Char_Array(&process_name, (char*)library_name, &size_process_name) != 0) //copying name process in char arrray
	{
		return ERROR_ALLOCATION_MEMORY;
	}
	error_flag = (error_flag | Get_Pid_Need_Procces_By_Name(&pID, process_name, size_process_name));//get processID by name this process
	if(error_flag != 0)
	{
		return error_flag;
	}
	if(pID == -1)
	{
		printf("this process dont founded\n");
		return ERROR_FOUND_PROCESS;
	}
	printf("PID: %d\n",pID);//
	pHndl = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID); //get handle for process by processID
	while(1)
	{
		printf("iterarion in while\n");
		modHndls=(HMODULE*)malloc(b_alloc); //allocation memory in quantity b_alloc(size in byte)
		if(EnumProcessModules(pHndl, modHndls, b_alloc, &b_needed) == 0) //get handle for every modules in specified dll(pHndl)
		{
			printf("%d\n",GetLastError());//
			printf("Error: EnumProcessModules fail\n");
			return ERROR_ENUM_PROCESS_MODULS;
		}
		else//
		{
			printf("srabotal enum\n");//
		}
//			printf("%u %u\n", pID, pHndl);
//			printf("%u %u\n",b_alloc, b_needed);
		if(b_needed <= b_alloc)
		{
			printf("norm\n");//
			break;	
		}
		else
		{
			printf("malo\n");//
			free(modHndls); //free past allocation memory
			b_alloc = b_needed; //assign allocation size - needed quantity byte
		}
	}
//	printf("a==%d == n==%d",b_alloc,b_needed);
	for(int i = 0; i < ((b_needed/sizeof(DWORD))); i++)
	{
		GetModuleBaseName(pHndl, modHndls[i], (LPSTR)modName, sizeof(modName)); //get name dll
		printf("%u\t%s", modHndls[i], modName);
		GetModuleFileName(modHndls[i], (LPSTR)modName, sizeof(modName)); //get full path for dll
//		temp_err = Get_Export_Function(modName); //get export function in this dll
		printf("\t%s\n",modName);
	}
	#else
	LOADED_IMAGE LoadedImage;
    PIMAGE_IMPORT_DESCRIPTOR ImportDescriptor; //pointer type for descriptor import
    PIMAGE_THUNK_DATA OriginalFirstThunk;//rva for table name import
    PIMAGE_THUNK_DATA FirstThunk; //rva for table adress import
    PIMAGE_THUNK_DATA ThunkData; // tempurature for relativiry adress for table import
    PIMAGE_IMPORT_BY_NAME ImportFunctionName;// strings included name of dll
    DWORD uSize;
    if(!MapAndLoad(library_name, NULL, &LoadedImage, TRUE, TRUE)) //load pe-file
    {
        printf("Need file dont find\n");
        printf("Maybe incorrect second argument, please check this\n");
        printf("Example correct second argument notepad.exe");
        return ERROR_UNKNOWN_MAP_AND_LOAD;
    }
    ImportDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)ImageDirectoryEntryToData(LoadedImage.MappedAddress, FALSE, IMAGE_DIRECTORY_ENTRY_IMPORT, &uSize); //get value for descriptor for import table
	while(ImportDescriptor->Name || ImportDescriptor->TimeDateStamp)
	{
            OriginalFirstThunk = (PIMAGE_THUNK_DATA)ImageRvaToVa(LoadedImage.FileHeader, LoadedImage.MappedAddress, ImportDescriptor->OriginalFirstThunk, NULL); //get virtual adress for import table
            printf("\n\tOriginal First Thunk = %lx\n", (ULONG)((PUCHAR)OriginalFirstThunk - LoadedImage.MappedAddress));
            FirstThunk = (PIMAGE_THUNK_DATA)ImageRvaToVa(LoadedImage.FileHeader, LoadedImage.MappedAddress, ImportDescriptor->FirstThunk, NULL); //get relativity virtual adress for import table
            printf("\tFirst Thunk = %lx\n\n", (ULONG)((PUCHAR)FirstThunk - LoadedImage.MappedAddress));
            printf("Name of function: \t\t\t\t");
            printf("Library:\n");
            ThunkData = OriginalFirstThunk; //save in tempurature data of virtual adress table import
            if(ThunkData == NULL) //if virtual adress table import equally null
			{
				ThunkData = FirstThunk; //save in tempurature data of relativity virtual adress table import
			}
            while(ThunkData->u1.AddressOfData) //while adress of data exists
			{
                if(!IMAGE_SNAP_BY_ORDINAL(ThunkData->u1.Ordinal)) //if ordinal number end
				{
		            ImportFunctionName = (PIMAGE_IMPORT_BY_NAME)ImageRvaToVa(LoadedImage.FileHeader, LoadedImage.MappedAddress, ThunkData->u1.AddressOfData, NULL);//get function name of need dll
		            printf("%-40s\t",  ImportFunctionName->Name);
		            printf("%s\n",(PUCHAR)ImageRvaToVa(LoadedImage.FileHeader, LoadedImage.MappedAddress, ImportDescriptor->Name, NULL));
                }
                ThunkData++;
                OriginalFirstThunk++;
                FirstThunk++;
            }
            ImportDescriptor++;
	}
    UnMapAndLoad(&LoadedImage);//unloaded portable executable file
	#endif
    return 0;
}

int main(int argc, char* argv[])
{
    int error_flag = 0b0;
    if(Check_Argc(argc) == ERROR_QUANTITY_ARGUMENT)
    {
        error_flag = (error_flag | ERROR_QUANTITY_ARGUMENT);
        return error_flag;
    }
    if(Check_Second_Argument(argv[1]) == ERROR_SECOND_ARGUMENT)
    {
        error_flag = (error_flag | ERROR_SECOND_ARGUMENT);
        return error_flag;
    }
    if((argv[2][0] == GET_EXPORT_FUNCTION) && (argv[2][1] == '\0'))
    {
        error_flag = (error_flag | Get_Export_Function(argv[1]));
        printf("write enter for exit programm\n");
		getch();
        return error_flag;
    }
    else
    {
    	if((argv[2][0] == GET_IMPORT_FUNCTION) && (argv[2][1] == '\0'))
	    {
	        error_flag = (error_flag | Get_Import_Function(argv[1]));
	        printf("write enter for exit programm\n");
			getch();
	        return error_flag;
	    }
	    else
	    {
	    	printf("Error: incorrect third argument\n");
			printf("example correct argument - E");
			error_flag = (error_flag | ERROR_THIRD_ARGUMENT);
		}
	}
	printf("End programm\n");
    getch();
    return error_flag;
}
