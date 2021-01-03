#include <windows.h>
#include <process.h>
#include <stdio.h>

HANDLE hMutex1, hMutex2;
double sh1 = 0.0;
int sh2 = 0;

void Thread(void *pParams)
{
    while (1)
    {
        WaitForSingleObject(hMutex2, INFINITE); //capture mutex
        sh2++;
        WaitForSingleObject(hMutex1, INFINITE); //capture mutex
        sh1 += 0.1;
        ReleaseMutex(hMutex1); //free mutex
        ReleaseMutex(hMutex2); //free mutex
    }
}

int main()
{
    hMutex1 = CreateMutex(NULL, FALSE, NULL); //create mutex
    hMutex2 = CreateMutex(NULL, FALSE, NULL); //create mutex
    _beginthread(Thread, 0, NULL); //start thread
    while (1)
    {
        WaitForSingleObject(hMutex1, INFINITE); //capture mutex
        printf("%g\n", sh1);
        WaitForSingleObject(hMutex2, INFINITE); //capture mutex
        printf("%d\n", sh2);
        ReleaseMutex(hMutex2); //free mutex
        ReleaseMutex(hMutex1); //free mutex
    }
    return 0;
}
