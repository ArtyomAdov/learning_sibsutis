#include <windows.h>
#include <stdio.h>

#define STANDART_BITS_TO_READ 255
#define SIZE_BUFFER_IN_AND_OUT 4096

#define INCORRECT_END_PROGRAMM 0b00000001
#define FAILED_CREATE_PIPE 0b00000010
#define FAILED_CLIENT_CONNECT 0b00000100 

int main()
{
	HANDLE hPipe;
	LPTSTR lpPipeName = TEXT("\\\\.\\pipe\\MyPipe");
	DWORD iBytesToWrite;
	DWORD iBytesToRead = STANDART_BITS_TO_READ;
	char buff[STANDART_BITS_TO_READ];
	do
	{
		hPipe = CreateNamedPipe(lpPipeName, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES, 
				SIZE_BUFFER_IN_AND_OUT, SIZE_BUFFER_IN_AND_OUT, NMPWAIT_USE_DEFAULT_WAIT, NULL);
		if(hPipe == INVALID_HANDLE_VALUE)
		{
			printf("error: CreatePipe failed: error code %d\n", (int)GetLastError());
			return FAILED_CREATE_PIPE;
		}
		if((ConnectNamedPipe(hPipe, NULL)) == 0)
		{
			printf("error: client could not connect\n");
			return FAILED_CLIENT_CONNECT;
		}
		printf("vlad1k:\t");
		ReadFile(hPipe, buff, iBytesToRead, &iBytesToRead, NULL);
		for(short int i = 0; i < iBytesToRead; i++)
		{
			printf("%c", buff[i]);	
		}
		iBytesToRead = 255;
		printf("\ndeath_angel:\t");
		gets(buff);
		hPipe = CreateFile(lpPipeName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
		WriteFile(hPipe, buff, strlen(buff), &iBytesToWrite, NULL);
	}while (buff[0] != '0');
	printf("error: incorrect exit from programm\n");
	return INCORRECT_END_PROGRAMM;
}
