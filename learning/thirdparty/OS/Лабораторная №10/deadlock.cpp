#include <windows.h>
#include <process.h>
#include <stdio.h>

HANDLE hMutex1, hMutex2;
double sh1 = 0.0;
int sh2 = 0;

void Thread(void* pParams);

int main(void) 
{
	hMutex1 = CreateMutex(NULL, FALSE, NULL);
 	hMutex2 = CreateMutex(NULL, FALSE, NULL);	
	_beginthread(Thread, 0, NULL);

 	while (sh2 != 10)
 	{
 		//WaitForMultipleObjects(2, muTex, TRUE, INFINITE);
		
						//не блокировка
		WaitForSingleObject(hMutex2, INFINITE);//захват
 		printf("%d\n", sh2);
 		WaitForSingleObject(hMutex1, INFINITE);//захват
 		printf("%g\n", sh1);
 		
		 				//блокировка
 		/*WaitForSingleObject(hMutex1, INFINITE);//захват
 		printf("%g\n", sh1);
 		WaitForSingleObject(hMutex2, INFINITE);//захват
 		printf("%d\n", sh2);		
 		*/
 		ReleaseMutex(hMutex2);//освобождение
 		ReleaseMutex(hMutex1);//освобождение	 
	}
 	return 0;
}

void Thread(void* pParams)
{
 	while (sh2 != 10)
	{
 		WaitForSingleObject(hMutex2, INFINITE);//захват мьютекса
 		sh2 += 1;
 		//printf("%d\n", sh2);
 		WaitForSingleObject(hMutex1, INFINITE);//захват мьютекса
 		sh1 += 0.1;
 		//printf("%g\n", sh1);
 		ReleaseMutex(hMutex2);//освобождение
 		ReleaseMutex(hMutex1);//освобождение
 	}
}
