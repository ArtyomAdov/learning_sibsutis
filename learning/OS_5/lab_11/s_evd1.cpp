#include <windows.h>
#include <process.h>
#include <stdio.h>

#pragma comment(lib, "libevd1" )

HANDLE hSemaphore;
extern __declspec(dllimport)
char sh[6];

int main()
{
	hSemaphore = CreateSemaphore(NULL, 1, 1, "sem");
	do
	{
		WaitForSingleObject(hSemaphore, INFINITE);
		printf("sh: %s\n", sh);
		ReleaseSemaphore(hSemaphore, 1, NULL);
	}while(1);
	CloseHandle(hSemaphore);
	getchar();
	return 0;
}
