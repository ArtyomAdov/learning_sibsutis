#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "libevd1" )

HANDLE hEvent1, hEvent2;
extern __declspec(dllimport)
char sh[6];

int main(void) 
{
 	hEvent1 = CreateEvent(NULL, FALSE, TRUE, "cmd /C C:\\Windows\\system32\\notepad.exe");
 	hEvent2 = CreateEvent(NULL, FALSE, FALSE, "cmd /C C:\\Windows\\System32\\calc.exe");
 	while (1) 
	{
 		WaitForSingleObject(hEvent1, INFINITE);
		printf("sh: %s\n", sh);
		SetEvent(hEvent2);
 	}
 	CloseHandle(hEvent1);
 	CloseHandle(hEvent2);
 	return 0;
}
