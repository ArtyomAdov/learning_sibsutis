#include <windows.h>
#include <stdio.h>
#include <conio.h>
#define N 80

int main(int argc, char* argv[]) 
{
	HANDLE hFile;
	char buff[N] = { '\0' };
	DWORD n;

	hFile = CreateFile("test.txt", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) 
	{
		printf("Could not open file.");
		return -1;
	}
	
	do 
	{
		gets_s(buff);
		WriteFile(hFile, buff, sizeof(buff), &n, NULL);
	} 
	while (getch() != 27);
	CloseHandle(hFile);
	
	return 0;
}
