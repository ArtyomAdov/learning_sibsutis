#include <windows.h>

extern __declspec(dllexport)

int value_one = 44;

__declspec(dllexport)
int function_one(int b)
{
	return (b*b);
}
__declspec(dllexport)
int function_two(int b)
{
	return b*b*b;
}
