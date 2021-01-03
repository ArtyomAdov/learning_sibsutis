#include <stdio.h> 
#include <windows.h>
#include <iostream>

using namespace std; 

int main() 
{
	HANDLE hPipe;
	LPTSTR lpPipeName = TEXT("\\\\.\\pipe\\MyPipe");
		DWORD iBytesToWrite; 
	char buff[255]; 
	DWORD iBytesToRead = 255, i; 
	do
	{
		hPipe = CreateNamedPipe( lpPipeName, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES, 
				4096, 4096, NMPWAIT_USE_DEFAULT_WAIT, NULL); //buffer out/in, timeout, security
		
		if (hPipe == INVALID_HANDLE_VALUE) 
		{
			printf("CreatePipe failed: error code %d\n", (int)GetLastError()); 
			return 0; 
		}

		printf("\n---\n");
		if((ConnectNamedPipe(hPipe, NULL)) == 0) 
		{
			printf("client could not connect\n"); 
			return 0;
		}
		ReadFile(hPipe, buff, iBytesToRead, &iBytesToRead, NULL); 
		for(i = 0; i < iBytesToRead; i++) 
			printf("%c", buff[i]);
		iBytesToRead = 255;
		printf("\n");
		if (buff[0] == '0')
			return 0;

		//scanf("%s", buff);
		cin.get(buff, 255);
		hPipe = CreateFile(lpPipeName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL); 
		WriteFile(hPipe, buff, strlen(buff), &iBytesToWrite, NULL);
		
	} while (true);
}
