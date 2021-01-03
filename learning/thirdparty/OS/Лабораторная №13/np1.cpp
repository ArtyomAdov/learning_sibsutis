#include <stdio.h>
#include <windows.h>

void main()
{
	HANDLE hPipe;
	LPTSTR lpPipeName = TEXT("\\\\.\\pipe\\MyPipe");
	char buff[255];
	DWORD iBytesToRead = 255, i;

	hPipe = CreateNamedPipe(lpPipeName, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES, 4096, 4096, NMPWAIT_USE_DEFAULT_WAIT, NULL); 
	if (hPipe == INVALID_HANDLE_VALUE) 
	{
		printf("CreatePipe failed: error code %d\n", (int)GetLastError());
 		return;
	}
	if((ConnectNamedPipe(hPipe, NULL)) == 0)
	{
		printf("client could not connect\n");
		return;
	}
	ReadFile(hPipe, buff, iBytesToRead, &iBytesToRead, NULL);
	for (i = 0; i < iBytesToRead; i++) 
		printf("%c", buff[i]);
}

