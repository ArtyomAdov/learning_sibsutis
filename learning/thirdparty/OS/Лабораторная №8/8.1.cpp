#include <windows.h>
#include <stdio.h>
#include <iostream>  

using namespace std;  
//поток - параллельные процесс
typedef int(*fun)(char*, int* p);

int g(char* str, int* p) 
{
	*p = 0;
	printf("%s\n", str);
	return 0;
}

int q = 1;

DWORD WINAPI Thread(void* pg) 
{
	int counter = 0;
	while(q) 
	{
		printf("child\n");
		Sleep(10);
		if (counter++ > 10) 
			break;
	}
	((fun)pg)("thread_is_over!", &q);
	return 0;
}

int main(void) 
{
	DWORD dwThreadId;
	CreateThread(NULL, 0, Thread, g, 0, &dwThreadId);
	
	while(q) 
	{
		cout << "Parent " << q << " " << endl;
		Sleep(10);
	}
	return 0;
}
