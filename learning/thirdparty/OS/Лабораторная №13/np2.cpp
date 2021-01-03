#include <stdio.h>
#include <windows.h>
#include <string>
#include <iostream>

using namespace std;  

void main()
{
	HANDLE hPipe;
	LPTSTR lpPipeName = TEXT("\\\\.\\pipe\\MyPipe");
	//TEXT("\\\\WANDERER\\pipe\\MyPipe");
	DWORD iBytesToWrite;
	char buff[1000];
	cin.get(buff, 1000);

	hPipe = CreateFile(lpPipeName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL); 
	WriteFile(hPipe, buff, strlen(buff), &iBytesToWrite, NULL);
	CloseHandle(hPipe);
}
