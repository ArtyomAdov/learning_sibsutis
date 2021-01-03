#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "libd2")

extern __declspec(dllimport)
struct _shareTest 
{
	double g;
	int n;
}shareTest;

int main() 
{
	shareTest.g = 2.78;
	shareTest.n = 127;
	
	printf("%g\t%d\n", shareTest.g, shareTest.n);
	//getchar();
	return 0;
}

