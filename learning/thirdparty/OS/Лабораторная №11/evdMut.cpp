#include <windows.h>
#include <process.h>
#include <stdio.h>

HANDLE hMutex, hMutex1;
char sh[6];
void Thread(void* pParams);
void Thread1(void* pParams);

int main(void) 
{
 	hMutex = CreateMutex(NULL, FALSE, NULL);
 	hMutex1 = CreateMutex(NULL, FALSE, NULL);
 	_beginthread(Thread, 0, NULL);
 	_beginthread(Thread1, 0, NULL);
 	while (1)
	{
 		WaitForSingleObject(hMutex, INFINITE);
 		printf("%s\n", sh);
 		ReleaseMutex(hMutex);
		 
 		WaitForSingleObject(hMutex1, INFINITE);
 		printf("%s\n", sh);
 		ReleaseMutex(hMutex1);	
 	}
 	return 0;
}

void Thread1(void* pParams)
{
 	int counter = 0;
 	while (1)
	{
 		WaitForSingleObject(hMutex1, INFINITE);
 		if (counter % 2)
		{
 			sh[0]='T';
			sh[1]='h';
			sh[2]='e';
			sh[3]='\0';
 		}
 		else
		{
 			sh[0]='E';
			sh[1]='n';
			sh[2]='d';
			sh[3]='\0';
 		}
 		ReleaseMutex(hMutex1);
 		counter++;
 	}
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
