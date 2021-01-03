#include <windows.h>
#include <process.h>
#include <stdio.h>

#pragma comment(lib, "libevd1" )

HANDLE hMutex;
extern __declspec(dllimport)
char sh[6];

int main()
{
	hMutex = CreateMutex(NULL, FALSE, "mut");
	do
	{
		WaitForSingleObject(hMutex, INFINITE);
		printf("sh: %s\n", sh);
        ReleaseMutex(hMutex);
	}while(1);
	CloseHandle(hMutex);
	getchar();
	return 0;
}
