#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <windows.h>

#define ERROR_OPEN_DIRECTORY 0b00000001
#define ERROR_REALLOCATIAN_MEMORY 0b00000010

#define EXIT_FROM_PROGRAMM 0b10000000

#define MAX_SIZE_PATH 256
#define START_SIZE_BUFFER_COMMAND 1

#define MESSAGE_NONEEXISTENT_COMMAND      \
	printf("\nThis command nonexistent\n"); \
	printf("Please entry correct command\n");

int Get_Current_Directory(char** current_path)
{
	*current_path = (char*) calloc (MAX_SIZE_PATH, sizeof(char));
	if(GetCurrentDirectory(MAX_SIZE_PATH,*current_path) == 0)
	{
		return ERROR_OPEN_DIRECTORY;
	}
	return 0;
}

void Print_Current_Path(char* current_path)
{
	printf("\r%s",current_path);
}

int Get_Command(char** command, int* size_command)
{
	char* buffer = NULL;
	char symbol = '0';
	int buffer_size = START_SIZE_BUFFER_COMMAND;
	buffer = (char*) calloc (START_SIZE_BUFFER_COMMAND, sizeof(char));
	*size_command = 0;
	for(short int i = 0; ((symbol != '\n') && (symbol != EOF)); i++)
	{
		symbol = getc(stdin);
		if(buffer_size <= i)
		{
			buffer_size = buffer_size + START_SIZE_BUFFER_COMMAND;
			buffer = (char*)realloc(buffer,buffer_size);
			if(buffer == NULL)
			{
				return ERROR_REALLOCATIAN_MEMORY;
			}
		}
		buffer[i] = symbol;
		*size_command = i;
	}
	(*command) = (char*) calloc ((*size_command), sizeof(char));
	for(short int i = 0; i < (*size_command); i++)
	{
		(*command)[i] = buffer[i];
	}
	buffer = NULL;
	return 0;
}

int Check_Alias_Command(char** command, int size_command)
{
	switch(size_command)
	{
		case(2):
		{
			char alias_ls[] = {"dir"};
			char buffer_ls[2] = {"ls"};
			char alias_ps[] = {"tasklist"};
			char buffer_ps[2] = {"ps"};
			int size_alias_ls = 3;
			int size_alias_ps = 8;
			for(short int i = 0; i < size_command; i++)
			{
				if((*command)[i] != buffer_ls[i])
				{
					break;
				}
				else
				{
					if(i == size_command-1)
					{
						free(*command);
						*command = (char*) calloc (size_alias_ls,sizeof(char));
						for(short int j = 0; j < size_alias_ls; j++)
						{
							(*command)[j] = alias_ls[j];	
						}
						return 1;
					}
				}
			}
			for(short int i = 0; i < size_command; i++)
			{
				if((*command)[i] != buffer_ps[i])
				{
					break;
				}
				else
				{
					if(i == size_command-1)
					{
						free(*command);
						*command = (char*) calloc (size_alias_ps,sizeof(char));
						for(short int j = 0; j < size_alias_ps; j++)
						{
							(*command)[j] = alias_ps[j];	
						}
						return 1;
					}
				}
			}
		}
		case(4):
		{
			char buffer[4] = {"exit"};
			for(short int i = 0; i < size_command; i++)
			{
				if((*command)[i] != buffer[i])
				{
					break;
				}
				else
				{
					if(i == size_command-1)
					{
						return EXIT_FROM_PROGRAMM;
					}
				}
			}
		}
		case(5):
		{
			char alias[3] = {"cls"};
			char buffer[5] = {"clear"};
			int size_alias = 3;
			for(short int i = 0; i < size_command; i++)
			{
				if((*command)[i] != buffer[i])
				{
					break;
				}
				else
				{
					if(i == size_command-1)
					{
						free(*command);
						*command = (char*) calloc (size_alias,sizeof(char));
						for(short int j = 0; j < size_alias; j++)
						{
							(*command)[j] = alias[j];	
						}
						return 1;
					}
				}
			}
		}
		default:
		{
			return 0;	
		}
	}
	return 0;
}

int Run_Command(char* command, int size_command)
{
	int exit_flag = Check_Alias_Command(&command,size_command);
	char* array_command[] = {"cmd","/C",command,NULL};
	if(exit_flag == 0)
	{
		return MESSAGE_NONEEXISTENT_COMMAND;
	}
	else
	{
		if(exit_flag == EXIT_FROM_PROGRAMM)
		{
			return EXIT_FROM_PROGRAMM;
		}
	}
	_spawnvp(_P_WAIT,array_command[0],array_command);
	return 0;
}

int main()
{
	char* current_path = NULL;
	char* command = NULL;
	int error_flag = 0b0;
	int size_command = 0;
	do
	{
		error_flag = (error_flag | Get_Current_Directory(&current_path));
		Print_Current_Path(current_path);
		error_flag = (error_flag | Get_Command(&command,&size_command));
		error_flag = (error_flag | Run_Command(command,size_command));
		if(error_flag == (error_flag | EXIT_FROM_PROGRAMM))
		{
			error_flag = (error_flag & (~EXIT_FROM_PROGRAMM));
			break;
		}
	}while(1);
	free(current_path);
	current_path = NULL;
	free(command);
	command = NULL;
	return error_flag;
}
