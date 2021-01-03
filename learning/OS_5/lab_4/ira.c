#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <windows.h>

char* Convert_Command(char* buffer)
{
	if(strcmp(buffer,"clear"))
	{
		free(buffer);
		strcpy(buffer,"cls");
		return buffer;
	}
	printf("command not found\n");
	return NULL;	
}

char* Write_Command(char* command)
{
	char* buffer = NULL;
	int buffer_size = 10;
	int i = 0;
	char symbol = '0';
	buffer = (char*) calloc (buffer_size, sizeof(char));//еть вероятность что от малоков будет мусор
	while(symbol!='\n')
	{
		symbol = getc(stdin);
		if(buffer_size <= i)
		{
			buffer_size += buffer_size;
			buffer = (char*) realloc (buffer,buffer_size);
			if(buffer == NULL)
			{
				return NULL;
			}
		}
		buffer[i] = symbol;
		i++;
	}
	command = Convert_Command(buffer);
	if(command == NULL)
	{
		return NULL;
	}
	return command;
}

int main()
{ 
	char* command = NULL;
	char* path = NULL;
//	int q = 0;
	path = (char*) malloc (MAX_PATH * sizeof(char));
//	while(1)
//	{
		if(GetCurrentDirectory(MAX_PATH,path) == 0)
		{
			printf("couldn't get the current directory\n");
			return 1;
		}
		printf("%s ",path);
		command = Write_Command(command);
		printf("%s\n",command[2]);
		char* argv[] = {"cmd", "/C", command, NULL};
		if(command != NULL)//мб будет пизда с процессами тогда попробавть вынести ран в отдельную функцию
		{
			_spawnvp(_P_WAIT,argv[0],argv);
		}
//		while(command[q]!=NULL)
//		{
//			printf("%c\n",command[q][0]);
//			q++;
//		}
//	}
//	free(path);
//	path = NULL;
//	free(command);
//	command = NULL;
	return 0;
}
