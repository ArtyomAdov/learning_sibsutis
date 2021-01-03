#include <windows.h>
#include <stdio.h>
#include <process.h>
#include <time.h>
#include <iostream>
#include <fstream>

using namespace std;

int const N = 8;
int const M = 1000;

CRITICAL_SECTION cs;

void thread1(void *); 
void thread2(void *); 
void thread3(void *); 
void thread4(void *);
void thread5(void *); 
void thread6(void *); 
void thread7(void *); 
void thread8(void *);
void th1(void *); 
void th2(void *); 
void th3(void *); 
void th4(void *);
void th5(void *); 
void th6(void *); 
void th7(void *); 
void th8(void *);

void EnterCriticalRegion(int threadId);
void LeaveCriticalRegion(int threadId);

int sh = 0;  
int flag[N], fl[N]; 
int turn_last[N];  
int stage[N + 1];

ofstream fout("out2.txt", ofstream::out);

int main()
{
	SYSTEMTIME st1, st2;
	clock_t start, finish;
	
	for (int i = 0; i < N; i++) 
	{
		flag[i] = 1;
		fl[i] = 1;
	}
	start = clock();  
	
	_beginthread(thread1, 0, NULL); 
	_beginthread(thread2, 0, NULL); 
	_beginthread(thread3, 0, NULL); 
	_beginthread(thread4, 0, NULL); 
	_beginthread(thread5, 0, NULL); 
	_beginthread(thread6, 0, NULL); 
	_beginthread(thread7, 0, NULL); 
	_beginthread(thread8, 0, NULL);	
	
	while (flag[0] || flag[1] || flag[2] || flag[3] || flag[4] || flag[5] || flag[6] || flag[7]);
		
	fout << "Count of threads: " << N << endl << "Count of iterations of thread: " << M << endl;
	printf("%i\n", sh);
	fout << "Result of programm: " << sh << endl;
	
	finish = clock();  
	printf("%f\n", (float)(finish - start) / CLOCKS_PER_SEC);
	fout << "Worktime for algoritm Peterson: " << (float)(finish - start) / CLOCKS_PER_SEC << endl;
	                                 
	sh = 0;
	start = clock();  
	InitializeCriticalSection(&cs);
	
	_beginthread(th1, 0, NULL); 
	_beginthread(th2, 0, NULL); 
	_beginthread(th3, 0, NULL); 
	_beginthread(th4, 0, NULL); 
	_beginthread(th5, 0, NULL); 
	_beginthread(th6, 0, NULL); 
	_beginthread(th7, 0, NULL); 
	_beginthread(th8, 0, NULL);	
	
	while (fl[0] || fl[1] || fl[2] || fl[3] || fl[4] || fl[5] || fl[6] || fl[7]);
		
	printf("%i\n", sh);
	finish = clock();  
	fout << "Result of programm: " << sh << endl;
	
	printf("%f\n", (float)(finish - start) / CLOCKS_PER_SEC);
	fout << "Worktime for WinAPI: " << (float)(finish - start) / CLOCKS_PER_SEC << endl;
	
	return 0;
}

void EnterCriticalRegion(int threadId) 
{
	for (int i = 1; i <= N - 1; i++)  //������� ������ 
	{ 
		stage[threadId] = i;  //����� ������ � ������� ��������� ������� threadId
		turn_last[i] = threadId;  //�������� ��������� � ������ ��� ������� i
		for (int j = 1; j <= N; j++)  //����� ��������� ���������
		{
			if (j == threadId) 
				continue;
			while (stage[j] >= i && turn_last[i] == threadId); 
		}
	}
}

void LeaveCriticalRegion(int threadId) 
{
	stage[threadId] = 0;  //����� ����� �������� ������
}

void thread1(void * ignored)
{
	int i = 0;
	for (i; i < M; i++)
	{
		EnterCriticalRegion(1);
		sh++; //����������� �������
		LeaveCriticalRegion(1);
		Sleep(1); //������������� �������
	}
	flag[0] = 0;
}

void thread2(void * ignored)
{
	int i = 0;
	for (i; i < M; i++)
	{
		EnterCriticalRegion(2);
		sh++; //����������� �������
		LeaveCriticalRegion(2);
		Sleep(1); //������������� �������
	}
	flag[1] = 0;
}

void thread3(void * ignored)
{
	int i = 0;
	for (i; i < M; i++)
	{
		EnterCriticalRegion(3);
		sh++; //����������� �������
		LeaveCriticalRegion(3);
		Sleep(1); //������������� �������
	}
	flag[2] = 0;
}

void thread4(void * ignored)
{
	int i = 0;
	for (i; i < M; i++)
	{
		EnterCriticalRegion(4);
		sh++; //����������� �������
		LeaveCriticalRegion(4);
		Sleep(1); //������������� �������
	}
	flag[3] = 0;
}

void thread5(void * ignored)
{
	int i = 0;
	for (i; i < M; i++)
	{
		EnterCriticalRegion(5);
		sh++; //����������� �������
		LeaveCriticalRegion(5);
		Sleep(1); //������������� �������
	}
	flag[4] = 0;
}

void thread6(void * ignored)
{
	int i = 0;
	for (i; i < M; i++)
	{
		EnterCriticalRegion(6);
		sh++; //����������� �������
		LeaveCriticalRegion(6);
		Sleep(1);  //������������� �������
	}
	flag[5] = 0;
}

void thread7(void * ignored)
{
	int i = 0;
	for (i; i < M; i++)
	{
		EnterCriticalRegion(7);
		sh++; //����������� �������
		LeaveCriticalRegion(7);
		Sleep(1); //������������� �������
	}
	flag[6] = 0;
}

void thread8(void * ignored)
{
	int i = 0;
	for (i; i < M; i++)
	{
		EnterCriticalRegion(8);
		sh++; //����������� �������
		LeaveCriticalRegion(8);
		Sleep(1); //������������� �������
	}
	flag[7] = 0;
}

void th1(void * ignored)
{
	int i = 0;
	for(i; i < M; i++)
	{
		EnterCriticalSection(&cs);
		sh++; 
		LeaveCriticalSection(&cs);
		Sleep(1);
	}
	fl[0] = 0;
}

void th2(void * ignored)
{
	int i = 0;
	for(i; i < M; i++)
	{
		EnterCriticalSection(&cs);
		sh++; 
		LeaveCriticalSection(&cs);
		Sleep(1);
	}
	fl[1] = 0;
}

void th3(void * ignored)
{
	int i = 0;
	for (i; i < M; i++)
	{
		EnterCriticalSection(&cs);
		sh++;
		LeaveCriticalSection(&cs);
		Sleep(1); 
	}
	fl[2] = 0;
}

void th4(void * ignored)
{
	int i = 0;
	for (i; i < M; i++)
	{
		EnterCriticalSection(&cs);
		sh++; 
		LeaveCriticalSection(&cs);
		Sleep(1); 
	}
	fl[3] = 0;
}

void th5(void * ignored)
{
	int i = 0;
	for (i; i < M; i++)
	{
		EnterCriticalSection(&cs);
		sh++; 
		LeaveCriticalSection(&cs);
		Sleep(1);
	}
	fl[4] = 0;
}

void th6(void * ignored)
{
	int i = 0;
	for (i; i < M; i++)
	{
		EnterCriticalSection(&cs);
		sh++; 
		LeaveCriticalSection(&cs);
		Sleep(1);
	}
	fl[5] = 0;
}

void th7(void * ignored)
{
	int i = 0;
	for (i; i < M; i++)
	{
		EnterCriticalSection(&cs);
		sh++; 
		LeaveCriticalSection(&cs);
		Sleep(1);
	}
	fl[6] = 0;
}

void th8(void * ignored)
{
	int i = 0;
	for (i; i < M; i++)
	{
		EnterCriticalSection(&cs);
		sh++; 
		LeaveCriticalSection(&cs);
		Sleep(1);
	}
	fl[7] = 0;
}

