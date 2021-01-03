#include <windows.h>
#include <stdio.h>
#include <iostream>

using namespace std;  

int q = 0;
int e = 0;

DWORD WINAPI Thread1(void* pg) 
{
	//q = q + 1000;
	//cout << "Thread1 " << endl;
	for (int i = 0; i < 1000; i++)
		q++;
	//e++;
	return 0;
}

DWORD WINAPI Thread2(void* pg) 
{
	//q = q + 2000;
	//cout << "Thread2 " << endl;
	for (int i = 0; i < 1000; i++)
		q++;
	return 0;
}

DWORD WINAPI Thread3(void* pg) 
{
	//q = q + 3000;
	//cout << "Thread3 " << endl;
	for (int i = 0; i < 1000; i++)
		q++;
	return 0;
}

int main() 
{
	HANDLE h[180];
	DWORD thread3;
	for (int i = 0; i < 180; i++)
		h[i] = CreateThread(NULL, 0, Thread3, NULL, 0, &thread3);
	
	//for (int i = 0; i < 180; i++)	
	//	WaitForSingleObject(h[i], INFINITE);
		
	WaitForMultipleObjectsEx(180, h, TRUE, INFINITE, FALSE);
/*
	while (1)
	{
		if (e >= 180)
			break;
    }*/
	cout << q << endl;
	
	return 0;
}
