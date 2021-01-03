#include <windows.h>
#include <process.h>
#include <stdio.h>

HANDLE hEvent1,hEvent2;
char sh[6];

void Thread(void* p);

int main()
{
	hEvent1 = CreateEvent(NULL,FALSE,TRUE,NULL);
	hEvent2 = CreateEvent(NULL,FALSE,FALSE,NULL);
	_beginthread(Thread, 0, NULL);
	while(1)
	{
		WaitForSingleObject(hEvent1, INFINITE);
		printf("%s\n",sh);
		SetEvent(hEvent2);
	}
	CloseHandle(hEvent1);
	CloseHandle(hEvent2);
	return 0;
}

void Thread(void* pParams)
{
	int counter = 0;
	while(1)
	{
		WaitForSingleObject(hEvent2,INFINITE);
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
		SetEvent(hEvent1);
		counter++;
	}
}
