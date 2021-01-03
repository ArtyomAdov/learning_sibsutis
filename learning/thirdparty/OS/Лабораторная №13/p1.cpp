#include <windows.h>
#include <math.h>
#include <stdio.h>

int main()
{
	HANDLE hPipeIn, hPipeOut;
	SECURITY_ATTRIBUTES sa;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	char buff[80];
	unsigned long dw;
	double x;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE; //дочерние процессы наследуют
 	//дескрипторы

	if(!CreatePipe(&hPipeIn, &hPipeOut, &sa, 0))
	{
 		printf("The pipe could not be created\n");
 		exit(1);
	}// Создание канала с дескриптором ввода hPipeIn и
	// вывода hPipeOut
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESTDHANDLES;//использовать поля
 	//для стандартных потоков
	si.hStdInput = hPipeIn; //перенаправление потока ввода
	si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	
	if(!CreateProcess(NULL, "p2", NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
	{
		printf("Could not create process, %i\n",GetLastError());
		exit(1);
	}
	CloseHandle(hPipeIn);
	
	for (x = 0.0; x < 3.1416; x += 0.1)
	{
		sprintf(buff, "%g %g\n", x, sin(x));
		WriteFile(hPipeOut, buff, strlen(buff), &dw, NULL);
	}
	*buff = (char)26;
	WriteFile(hPipeOut, buff, 1, &dw, NULL);
	CloseHandle(hPipeOut);
	
	return 0;
} 
