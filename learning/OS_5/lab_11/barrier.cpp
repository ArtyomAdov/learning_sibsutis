#include <windows.h>
#include <stdio.h>

void main()
{
	STARTUPINFO si[3];
	PROCESS_INFORMATION pi[3];
	char* exefile[] = {"C:\\Windows\\System32\\calc.exe","C:\\Windows\\write.exe"};
	char* cmdLine = "cmd /C C:\\Windows\\notepad.exe 1.cpp";
	HANDLE Handles[3];
	for(int i = 0; i < 3; i++)
	{
		ZeroMemory(&si[i], sizeof(si[i]));
		si[i].cb = sizeof(si[i]);
		ZeroMemory(&pi[i], sizeof(pi[i]));
	}
	for(int i = 0; i < 2; i++)
	{
		if(!CreateProcess(exefile[i],NULL,NULL,NULL,FALSE,CREATE_NO_WINDOW,NULL,NULL,&si[i],&pi[i]))
		{
			printf("System error code: %i\n",GetLastError());
		}
		Handles[i] = pi[i].hProcess;
	}
	if(!CreateProcess(NULL,cmdLine,NULL,NULL,FALSE,CREATE_NO_WINDOW,NULL,NULL,&si[2],&pi[2]))
	{
		printf("System error code: %i\n",GetLastError());
	}
	Handles[2] = pi[2].hProcess;
	WaitForMultipleObjects(3,Handles,TRUE,INFINITE);
	printf("Go home!");
	for(int i = 0; i < 3; i++)
	{
		CloseHandle(pi[i].hProcess);
		CloseHandle(pi[i].hThread);
	}
}
