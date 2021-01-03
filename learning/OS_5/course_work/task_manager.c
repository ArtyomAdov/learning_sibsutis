#include <stdio.h>
#include <stdlib.h>

#define SYSTEM_WINDOWS
//#define SYSTEM_LINUX

#define INCORRECT_END_PROGRAMM 0b00000001
#define ERROR_ALLOCATION_MEMORY 0b00000010
#define ERROR_REALLOCATION_MEMORY 0b00000100

#define SPACE_BETWEEN_COMPOSITE_AND_END_ZERO 2
#define MAXIMUM_BUFFER_SIZE 50

#define FIRST_CODE_SYMBOL_DIGIT 0x30
#define LAST_CODE_SYMBOL_DIGIT 0x39

#ifdef SYSTEM_WINDOWS

#define SIZE_COMMAND_KILL_PROCESS_PID 13
#define SIZE_COMMAND_KILL_PROCESS_NAME 12
#define SIZE_COMMAND_STOP_SERVICE 7
#define SIZE_COMMAND_START_SERVICE 8

#define COMMAND_SHOW_PROCESS "tasklist"
#define COMMAND_SHOW_SERVICE "sc query"
#define COMMAND_KILL_PROCESS_PID "taskkill /PID"
#define COMMAND_KILL_PROCESS_NAME "taskkill /IM"
#define COMMAND_STOP_SERVICE "sc stop"
#define COMMAND_START_SERVICE "sc start"
#define COMMAND_CLEAR_SCREEN "CLS"
#endif

#ifdef SYSTEM_LINUX

#define SIZE_COMMAND_KILL_PROCESS_PID 10
#define SIZE_COMMAND_KILL_PROCESS_NAME 11
#define SIZE_COMMAND_STOP_SERVICE 12
#define SIZE_COMMAND_START_SERVICE 13

#define COMMAND_SHOW_PROCESS "ps -a"
#define COMMAND_SHOW_SERVICE "service --status-all"
#define COMMAND_KILL_PROCESS_PID "kill -TERM"//
#define COMMAND_KILL_PROCESS_NAME "pkill -TERM"//
#define COMMAND_STOP_SERVICE "systemctl stop"
#define COMMAND_START_SERVICE "systemctl start"
#define COMMAND_CLEAR_SCREEN "clear"
#endif

void Draw_Menu()
{
	printf("1) Show Process\n");
	printf("2) Show Services\n");
	printf("3) Kill Process by pid\n");
	printf("4) Kill Process by name\n");
	printf("5) Stop Services\n");
	printf("6) Start Services\n");
	printf("9) Clear Screen\n");
	printf("0) Exit\n");
}

int Get_User_String(char* user_string[], int* size_user_string)
{
	char* buffer = NULL;
	int quantity_symbol = -1;
	buffer = (char*)calloc(MAXIMUM_BUFFER_SIZE, sizeof(char));
	if(buffer == NULL)
	{
		return ERROR_ALLOCATION_MEMORY;
	}
	printf("write pid or name\n");
	getchar();
	do
	{
		quantity_symbol++;
		fread(&(buffer[quantity_symbol]),sizeof(char),1,stdin);
		if(quantity_symbol > MAXIMUM_BUFFER_SIZE)
		{
			realloc(buffer,(quantity_symbol + MAXIMUM_BUFFER_SIZE));
			if(buffer == NULL)
			{
				return ERROR_REALLOCATION_MEMORY;
			}
		}
	}while(buffer[quantity_symbol] != '\n');
	*size_user_string = quantity_symbol;
	*user_string = (char*)calloc(quantity_symbol, sizeof(char));
	if(*user_string == NULL)
	{
		return ERROR_ALLOCATION_MEMORY;
	}
	for(short int i = 0; i < quantity_symbol; i++)
	{
		(*user_string)[i] = buffer[i];
	}
	free(buffer);
	buffer = NULL;
	return 0;
}

int Create_Composite_System_Command(char* system_command[], char user_string[], char composite[], int size_user_string)
{
	*system_command = (char*)calloc(size_user_string,sizeof(char));
	if(*system_command == NULL)
	{
		return ERROR_ALLOCATION_MEMORY;
	}
	sprintf(*system_command,"%s %s", composite, user_string);
	return 0;
}

int main()
{
	char* system_command = NULL;
	char* user_string = NULL;
	int size_user_string = 0;
	int error_flag = 0b0;
	char key_choice = '0';
	do
	{
		Draw_Menu();
		scanf(" %c",&key_choice);
		switch(key_choice)
		{
			case('1'):
			{
				system(COMMAND_SHOW_PROCESS);
				break;
			}
			case('2'):
			{
				system(COMMAND_SHOW_SERVICE);
				break;
			}
			case('3'):
			{
				error_flag = (error_flag | Get_User_String(&user_string, &size_user_string));
				size_user_string = (size_user_string + SIZE_COMMAND_KILL_PROCESS_PID + SPACE_BETWEEN_COMPOSITE_AND_END_ZERO);
				error_flag = (error_flag | Create_Composite_System_Command(&system_command, user_string, COMMAND_KILL_PROCESS_PID, size_user_string));
				system(system_command);
				size_user_string = 0;
				free(user_string);
				user_string = NULL;
				free(system_command);
				system_command = NULL;
				break;
			}
			case('4'):
			{
				error_flag = (error_flag | Get_User_String(&user_string, &size_user_string));
				size_user_string = (size_user_string + SIZE_COMMAND_KILL_PROCESS_NAME + SPACE_BETWEEN_COMPOSITE_AND_END_ZERO);
				error_flag = (error_flag | Create_Composite_System_Command(&system_command, user_string, COMMAND_KILL_PROCESS_NAME, size_user_string));
				system(system_command);
				size_user_string = 0;
				free(user_string);
				user_string = NULL;
				free(system_command);
				system_command = NULL;
				break;
			}
			case('5'):
			{
				error_flag = (error_flag | Get_User_String(&user_string, &size_user_string));
				size_user_string = (size_user_string + SIZE_COMMAND_STOP_SERVICE + SPACE_BETWEEN_COMPOSITE_AND_END_ZERO);
				error_flag = (error_flag | Create_Composite_System_Command(&system_command, user_string, COMMAND_STOP_SERVICE, size_user_string));
				system(system_command);
				size_user_string = 0;
				free(user_string);
				user_string = NULL;
				free(system_command);
				system_command = NULL;
				break;
			}
			case('6'):
			{
				error_flag = (error_flag | Get_User_String(&user_string, &size_user_string));
				size_user_string = (size_user_string + SIZE_COMMAND_START_SERVICE + SPACE_BETWEEN_COMPOSITE_AND_END_ZERO);
				error_flag = (error_flag | Create_Composite_System_Command(&system_command, user_string, COMMAND_START_SERVICE, size_user_string));
				system(system_command);
				size_user_string = 0;
				free(user_string);
				user_string = NULL;
				free(system_command);
				system_command = NULL;
				break;
			}
			case('9'):
			{
				system(COMMAND_CLEAR_SCREEN);
				break;
			}
			case('0'):
			{
				return error_flag;
			}
			default:
			{
				printf("error: incorrect choice\n");
				break;
			}
		}
	} while(key_choice != '0');
	return (error_flag | INCORRECT_END_PROGRAMM);
}
