#include <windows.h>
#include <process.h>
#include <stdio.h>

HANDLE hMutex1, hMutex2;
double global_value_first = 0.0;
int global_value_second = 0;

void Thread()
{
    do
    {
        WaitForSingleObject(hMutex1, INFINITE);//capture mutex
        global_value_second++;//increment
        WaitForSingleObject(hMutex2, INFINITE);//capture mutex
        global_value_first = global_value_first + 0.1;//increment for double(0.1)
        ReleaseMutex(hMutex2);//free mutex
        ReleaseMutex(hMutex1);//free mutex
    }while(1);
}

int main()
{
    hMutex1 = CreateMutex(NULL, FALSE, NULL);//create mutex
    //first parametr == null: handle dont inherited
    //second parametr == false: thread dont get ownership of the mutex
    //third parametr == null: mutex object name(if null then object create with no name)
    hMutex2 = CreateMutex(NULL, FALSE, NULL);//create mutex
    _beginthread(Thread, 0, NULL);//start thread
    //first parametr == thread: function name
    //second parametr == 0: first size stack(if == 0 then used standart size)
    //third parametr == null: list for argument for thread(or null if no arguments)
    do
    {
        WaitForSingleObject(hMutex1, INFINITE);//capture mutex
        //first parametr == handle mutex: 
        //second parametr == infinitive: the function returns when the object is signaled
        printf("%g\n", global_value_first);
        WaitForSingleObject(hMutex2, INFINITE);//capture mutex
        printf("%d\n", global_value_second);
        ReleaseMutex(hMutex2);//free mutex(last mutex need free first)
        ReleaseMutex(hMutex1);//free mutex
    }while(1);
    return 0;
}
