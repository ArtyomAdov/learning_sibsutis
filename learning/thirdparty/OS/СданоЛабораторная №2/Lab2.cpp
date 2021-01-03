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
	GetSystemInfo(&siSysInfo); //���� � ����� ������������
	GetSystemDirectory(path1, 100); //�����, ������, ���� � ������ ��������
	GetTempPath(100, path2); //���� ������ ����, ���� � �������� ������ ������
	
	char *divisor = "�";
	
	MEMORYSTATUS stat;
	GlobalMemoryStatus(&stat); //��� ������

    //������
	printf ("��������� ��������� ������ ����� ����� %ld �����.\n", stat.dwLength);
	printf ("----------------------------------------------------\n");
  	printf ("��� ������ ���� %d �����.\n", sizeof (stat));
  	printf ("----------------------------------------------------\n");
	printf ("%ld �������(�) ������������ ������\n", stat.dwMemoryLoad);
	printf ("----------------------------------------------------\n");
	printf ("���������� ����� %*ld %s����(�) ���������� ������.\n", WIDTH, stat.dwTotalPhys/(DIV*DIV), divisor);
	printf ("----------------------------------------------------\n");
  	printf ("������� �������� %*ld %s����(�) ���������� ������.\n", WIDTH, stat.dwAvailPhys/(DIV*DIV), divisor);
  	printf ("----------------------------------------------------\n");
  	printf ("���������� ����� %*ld %s����(�) ����� ��������.\n", WIDTH, stat.dwTotalPageFile/(DIV*DIV), divisor);
  	printf ("----------------------------------------------------\n");
  	printf ("������� �������� %*ld %s����(�) ����� ��������.\n", WIDTH, stat.dwAvailPageFile/(DIV*DIV), divisor);
  	printf ("----------------------------------------------------\n");
  	printf ("���������� ����� %*lx %s����(�) ����������� ������.\n", WIDTH, stat.dwTotalVirtual/(DIV*DIV), divisor);
  	printf ("----------------------------------------------------\n");
  	printf ("������� �������� %*lx %s����(�) of ����������� ������.\n", WIDTH, stat.dwAvailVirtual/(DIV*DIV), divisor);
  	printf ("----------------------------------------------------\n");
  	//���� � ������ ��������
	cout << " Get System Directory - " << path1 << endl;
	printf ("----------------------------------------------------\n");
	//���� � �������� ������ ������
	cout << " Get Temp Path - " << path2 << endl;
	printf ("----------------------------------------------------\n");
	//����
	cout << " ����� �����������:  " << siSysInfo.dwNumberOfProcessors << endl;
	printf ("----------------------------------------------------\n");
	cout << " ����������� ���������� - " << siSysInfo.wProcessorArchitecture << endl;
	printf ("----------------------------------------------------\n");
	cout << " ��� ���������� - " << siSysInfo.dwProcessorType << endl;
	printf ("----------------------------------------------------\n");
	cout << " lpMinimumApplicationAddress - " << siSysInfo.lpMinimumApplicationAddress << endl;
	printf ("----------------------------------------------------\n");
	cout << " lpMaximumApplicationAddress - " << siSysInfo.lpMaximumApplicationAddress << endl;
    printf ("----------------------------------------------------\n");
	
	system("PAUSE");
	return 0;
}
