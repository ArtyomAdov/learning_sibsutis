#include <windows.h>
#include <time.h>
#include <synchapi.h>
#include <stdio.h>
#include <process.h>

#define SEVERAL_ITERATION 10

#define ERROR_ALLOCATION_MEMORY 0b0000001

#define START_GLOBAL_VALUE 0
#define QUANTITY_THREAD 2
#define MAX_GLOBAL_VALUE 10000

#define HEAD_TABLE "Algorithm by Peterson:\n| Expected|   Real    |  Time  |\n"

CRITICAL_SECTION critical_section;

int global_value = START_GLOBAL_VALUE; //sh==global_value

int ready_flag[QUANTITY_THREAD] = {0};
int other_thread = 0, turn = 0;

void Enter_Critical_Section(int threadId)
{
	other_thread = (1 - threadId); //get number other thread
	ready_flag[threadId] = 1; //up ready flag
	turn = threadId; //get number present thread
	while(turn == threadId && ready_flag[other_thread]); //cycle for wait (while other thread dont change ready flag)
}

void Leave_Critical_Section(int threadId)
{
	ready_flag[threadId] = 0; //down ready flag
}

DWORD WINAPI Thread_For_First_Method(void* param)
{
	int c = *((int*)param);
	for(int i = 0; i < MAX_GLOBAL_VALUE; i++)
	{
		Enter_Critical_Section(c);
		global_value++;//increment
		Leave_Critical_Section(c);
	}
	return 0;
}

DWORD WINAPI Thread_For_Second_Method(void* param)
{
	for(int i = 0; i < MAX_GLOBAL_VALUE; i++)
	{
		EnterCriticalSection(&critical_section);//
		global_value++;
		LeaveCriticalSection(&critical_section);
	}
	return 0;
}

int main()
{
	long int value_time = 0;
	int array_number_thread[QUANTITY_THREAD];
	HANDLE lpHandles[QUANTITY_THREAD]; //array handle type for descriptors threads for peterson
	DWORD dwThreadId[QUANTITY_THREAD]; //array dword type for id threads for peterson
	HANDLE lpHandlesCS[QUANTITY_THREAD]; //array handle type for descriptors threads for critical section
	DWORD dwThreadIdCS[QUANTITY_THREAD]; //array dword type for id threads for critical section
	InitializeCriticalSection(&critical_section); //initialization critical section
	for(short int i = 0; i < QUANTITY_THREAD; i++) //fill array number thread by increment
	{
		array_number_thread[i] = i;
	}
	value_time = clock(); //get time before start peterson
	for(short int i = 0; i < QUANTITY_THREAD; i++)
	{
		lpHandles[i] = CreateThread(NULL, 0, Thread_For_First_Method, &array_number_thread[i], 0, &dwThreadId[i]); //function for create thread
		//first parametr == NULL: for handle couldn't be inherited child process
		//second parametr == 0: first size stack(if == 0 then used standart size)
		//third parametr == my function: pointer for function which should be executed by the thread
		//fourth parametr == &number_thread[i]: pointer for variable which should be to thread
		//fifth parametr == 0: flags for control create thread(if == 0 then start thread immediately after creation)
		//sixth parametr == &thread_id: pointer for variable which get id thread 
		SetThreadAffinityMask(lpHandles[i], 0x01); //set mask for specified thread
		//first parametr == thread_handle[i]: descriptor for thread
		//second parametr == 0x01: allows thread start only in this cores (if == 0x01 then start in first core)
	}
	WaitForMultipleObjects(QUANTITY_THREAD, lpHandles, TRUE, INFINITE);
	//first parametr == quant_thread: for number of object handles in the second parametr
	//second parametr == thread_handle: array of object handles
	//third parametr == true: the function returns when the state of (if == true then all) objects in the second parameter
	//fourth parametr == ifinite: interval time-out (if == infinite then fucntion returns only when objects are signaled)
	value_time = (clock() - value_time); //get difference time present(after peterson) and time before start
	printf(HEAD_TABLE);
	printf("|  %d  |   %d   |    %ld   | \n", (MAX_GLOBAL_VALUE * QUANTITY_THREAD), global_value, value_time);
	global_value = 0; //
	value_time = clock();
	for(short int i = 0; i < QUANTITY_THREAD; i++)
	{
		lpHandlesCS[i] = CreateThread(NULL, 0, Thread_For_Second_Method, &array_number_thread[i], 0, &dwThreadIdCS[i]);
		SetThreadAffinityMask(lpHandlesCS[i], 0x01);
	}
	WaitForMultipleObjects(QUANTITY_THREAD, lpHandlesCS, TRUE, INFINITE);
	value_time = (clock() - value_time);
	printf("WinAPI:\n");
	printf("|  %d  |   %d   |    %ld   | \n", (MAX_GLOBAL_VALUE * QUANTITY_THREAD), global_value, value_time);
	for(short int i = 0; i < QUANTITY_THREAD; i++) //functions for close handle for open object
	{
		CloseHandle(lpHandles[i]);
		CloseHandle(lpHandlesCS[i]);
	}
	return 0;
}
