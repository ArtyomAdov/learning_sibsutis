#include <windows.h>
#include <process.h>
#include <stdio.h>

HANDLE hMutex;
char sh[6];
void Thread(void* pParams);

int main(void) 
{
 	hMutex = CreateMutex(NULL, FALSE, NULL);
 	_beginthread(Thread, 0, NULL);
 	while (1)
	{
 		WaitForSingleObject(hMutex, INFINITE);
 		printf("%s\n", sh);
 		ReleaseMutex(hMutex);
 	}
 	return 0;
}

void Thread(void* pParams)
{
 	int counter = 0;
 	while (1)
	{
 		WaitForSingleObject(hMutex, INFINITE);
 		if (counter % 2)
		{
 			sh[0]='H';
			sh[1]='e';
			sh[2]='l';
			sh[3]='l';
			sh[4]='o';
			sh[5]='\0';
 		}
 		else
		{
 			sh[0]='B';
			sh[1]='y';
			sh[2]='e';
			sh[3]='_';
			sh[4]='u';
			sh[5]='\0';
 		}
 		ReleaseMutex(hMutex);
 		counter++;
 	}
}
