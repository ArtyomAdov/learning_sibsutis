#include <windows.h>
#include <process.h>
#include <stdio.h>

HANDLE hMutex1, hMutex2;
char sh[6];

void Thread()
{
	int counter = 0;
	do
	{
		WaitForSingleObject(hMutex1, INFINITE);
		if(counter%2)
		{
			sh[0] = 'H';
			sh[1] = 'e';
			sh[2] = 'l';
			sh[3] = 'l';
			sh[4] = 'o';
			sh[5] = '\0';
		}
		else
		{
			sh[0] = 'B';
			sh[1] = 'y';
			sh[2] = 'e';
			sh[3] = '_';
			sh[4] = 'u';
			sh[5] = '\0';
		}
		counter++;
		WaitForSingleObject(hMutex2, INFINITE);
        ReleaseMutex(hMutex2);
        ReleaseMutex(hMutex1);
	}while(1);
}

int main()
{
	hMutex1 = CreateMutex(NULL, FALSE, NULL);
	hMutex2 = CreateMutex(NULL, FALSE, NULL);
	_beginthread(Thread, 0, NULL);
	do
	{
		WaitForSingleObject(hMutex1, INFINITE);
		printf("%s\n",sh);
		WaitForSingleObject(hMutex2, INFINITE);
		ReleaseMutex(hMutex2);
		ReleaseMutex(hMutex1);
	}while(1);
	return 0;
}
