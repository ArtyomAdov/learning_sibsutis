#include <windows.h>
#include <process.h>
#include <stdio.h>

#define START_GLOBAL_VALUE 0
#define QUANTITY_THREAD 4
#define MAX_GLOBAL_VALUE 10000

int global_value = START_GLOBAL_VALUE;

DWORD WINAPI Increase_Global_Value() //because parametr NULL in create thread function
{
	for(short int i = 0; i < MAX_GLOBAL_VALUE; i++)
	{
		global_value++;//increment
	}
	return 0;
}

int main()
{
	DWORD Array_Thread_Identifier[QUANTITY_THREAD]; //array dword type for id threads
	HANDLE Array_Tread_Handle[QUANTITY_THREAD]; //array handle type for descriptors threads 
	for(short int i = 0; i < QUANTITY_THREAD; i++)
	{
		Array_Tread_Handle[i] = CreateThread(NULL, 0, Increase_Global_Value, NULL, 0, &Array_Thread_Identifier[i]); //function for create thread
		//first parametr == NULL: for handle couldn't be inherited child process
		//second parametr == 0: first size stack(if == 0 then used standart size)
		//third parametr == my function: pointer for function which should be executed by the thread
		//fourth parametr == NULL: pointer for variable which should be to thread
		//fifth parametr == 0: flags for control create thread(if == 0 then start thread immediately after creation)
		//sixth parametr == &thread_id: pointer for variable which get id thread 
	}
	WaitForMultipleObjects(QUANTITY_THREAD, Array_Tread_Handle, TRUE, INFINITE); //function for wait until one or all of the specified threads are the signaled state
	//first parametr == quant_thread: for number of object handles in the second parametr
	//second parametr == thread_handle: array of object handles
	//third parametr == true: the function returns when the state of (if == true then all) objects in the second parameter
	//fourth parametr == ifinite: interval time-out (if == infinite then fucntion returns only when objects are signaled)
	for(short int i = 0; i < QUANTITY_THREAD; i++)
	{
		CloseHandle(Array_Tread_Handle[i]); //function for close handle for open object
	}
	printf("Real\tExpected\n");
	printf("%d\t%d\n", global_value, MAX_GLOBAL_VALUE * QUANTITY_THREAD);
	system("PAUSE");
	return 0;
}
