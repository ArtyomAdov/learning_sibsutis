#include <windows.h>
#include <stdlib.h>
#include <iostream>

#define DIV 1024
#define WIDTH 7

using namespace std;

int main() 
{
	
	setlocale(LC_ALL, "Russian");
	
	char path1[100];
	char path2[100];
	
	SYSTEM_INFO siSysInfo;
	GetSystemInfo(&siSysInfo); //проц и адрес пространство
	GetSystemDirectory(path1, 100); //буфер, размер, путь к систем каталогу
	GetTempPath(100, path2); //макс длинна пути, путь к каталогу времен файлов
	
	char *divisor = "Г";
	
	MEMORYSTATUS stat;
	GlobalMemoryStatus(&stat); //для памяти

    //память
	printf ("Структура состояния памяти имеет длину %ld байта.\n", stat.dwLength);
	printf ("----------------------------------------------------\n");
  	printf ("Она должна быть %d байта.\n", sizeof (stat));
  	printf ("----------------------------------------------------\n");
	printf ("%ld процент(а) используемой памяти\n", stat.dwMemoryLoad);
	printf ("----------------------------------------------------\n");
	printf ("Существует всего %*ld %sбайт(а) физической памяти.\n", WIDTH, stat.dwTotalPhys/(DIV*DIV), divisor);
	printf ("----------------------------------------------------\n");
  	printf ("Имеется свободно %*ld %sбайт(а) физической памяти.\n", WIDTH, stat.dwAvailPhys/(DIV*DIV), divisor);
  	printf ("----------------------------------------------------\n");
  	printf ("Существует всего %*ld %sбайт(а) файла подкачки.\n", WIDTH, stat.dwTotalPageFile/(DIV*DIV), divisor);
  	printf ("----------------------------------------------------\n");
  	printf ("Имеется свободно %*ld %sбайт(а) файла подкачки.\n", WIDTH, stat.dwAvailPageFile/(DIV*DIV), divisor);
  	printf ("----------------------------------------------------\n");
  	printf ("Существует всего %*lx %sбайт(а) виртуальной памяти.\n", WIDTH, stat.dwTotalVirtual/(DIV*DIV), divisor);
  	printf ("----------------------------------------------------\n");
  	printf ("Имеется свободно %*lx %sбайт(а) of виртуальной памяти.\n", WIDTH, stat.dwAvailVirtual/(DIV*DIV), divisor);
  	printf ("----------------------------------------------------\n");
  	//путь к систем каталогу
	cout << " Get System Directory - " << path1 << endl;
	printf ("----------------------------------------------------\n");
	//путь к каталогу времен файлов
	cout << " Get Temp Path - " << path2 << endl;
	printf ("----------------------------------------------------\n");
	//проц
	cout << " Число процессоров:  " << siSysInfo.dwNumberOfProcessors << endl;
	printf ("----------------------------------------------------\n");
	cout << " Архитектура процессора - " << siSysInfo.wProcessorArchitecture << endl;
	printf ("----------------------------------------------------\n");
	cout << " Тип процессора - " << siSysInfo.dwProcessorType << endl;
	printf ("----------------------------------------------------\n");
	cout << " lpMinimumApplicationAddress - " << siSysInfo.lpMinimumApplicationAddress << endl;
	printf ("----------------------------------------------------\n");
	cout << " lpMaximumApplicationAddress - " << siSysInfo.lpMaximumApplicationAddress << endl;
    printf ("----------------------------------------------------\n");
	
	system("PAUSE");
	return 0;
}
