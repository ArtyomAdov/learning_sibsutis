#include <windows.h>
#include <stdio.h>

#define LECTION_EXAMPLE 1
#define QUANTITY_NEED_ITERATION_PROGRAMM 5
#define TIME_DELAY_PROGRAMM_IN_THOUSANDTH_OF_SECOND 5000

#if LECTION_EXAMPLE
typedef int (*function)(int); //new type that is pointer function for return integer
#endif

int main()
{
	int iteration = 0; //counter for exiting the program
	HINSTANCE hInst; //handle to the instance (void pointer for differently objects) 
	do
	{
		hInst = LoadLibrary("library_1.dll"); //loading the specified module(library.dll) in the program
		printf("loaded\n"); //message for clarity about what library loaded
		Sleep(TIME_DELAY_PROGRAMM_IN_THOUSANDTH_OF_SECOND); //program execution delay to allow time for the monitor to read the modules(with library.dll)
		#if LECTION_EXAMPLE
		function pf; //variable for first funtion
		function pg; //variable for second funtion
		int* pa; //variable for first value
		pa=(int*)GetProcAddress(hInst, "value_one"); //extract adress variable "value_one" from dll which it points to hInst
		pf=(function)GetProcAddress(hInst, "function_one"); //same as above but for the "function_one"
		pg=(function)GetProcAddress(hInst, "function_two"); //same as above but for the "function_two"
		printf("%i %i %i\n",*pa,pf(4),pg(5)); //print all gets
		#else
		FARPROC return_value_one = NULL; //pointer type reterned import function
		FARPROC return_function_one = NULL;
		FARPROC return_function_two = NULL;
		hInst = LoadLibrary("library_1.dll");
		return_value_one = GetProcAddress(hInst, "value_one");
		return_function_one = GetProcAddress(hInst, "function_one");
		return_function_two = GetProcAddress(hInst, "function_two");
		printf("1)%i\n", *(int*)return_value_one); //dereferencing pointer for value_one
		printf("2)%i\n", return_function_one(4));
		printf("3)%i\n", return_function_two(5));
		Sleep(5000);
		#endif
		FreeLibrary(hInst); //unloaded module which points to hInst
		printf("unloaded\n"); //message for clarity about what library loaded
		Sleep(TIME_DELAY_PROGRAMM_IN_THOUSANDTH_OF_SECOND); //program execution delay to allow time for the monitor to read the modules(without library.dll)
		iteration++; //increment iteration
	} while(iteration < QUANTITY_NEED_ITERATION_PROGRAMM);
	printf("End programm\n");
	getch();
	return 0;
}
