#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "libd2" )

extern __declspec(dllimport)
struct _shareTest 
{
	double g;
	int n;
}shareTest;

int main() 
{
	printf("%g\t%d\n", shareTest.g, shareTest.n);
	return 0;
}

