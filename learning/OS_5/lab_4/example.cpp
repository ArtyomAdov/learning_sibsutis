#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <process.h>

int main(void)
{
	printf("nachalo\n");
//	char* argv[] = {"cmd","/C","dir",NULL};
	char* argv[] = {"cmd","/C","cls",NULL};///����� �����
//	char arg[] = {"cmd"};
//	char arg[] = {"cmd cls"};
//	printf("%s",arg);
//	_spawnvp(P_NOWAIT,"C:\\Users\\����\\Desktop\\OS-5\\lab_4\\check.exe",argv);//�� � ��������� ��������� ���������� ������� ��������� � ��������(�����)
//	_spawnvp(P_NOWAIT,"cmd /C ",argv);
//	_spawnvp(P_WAIT,"cmd",argv);//�������� �� ��� ������ �������� � �� ������� // cmd �������� �������� � ������� ���������� � ��������� ����� ����� ������ 0
//	_spawnvp(P_WAIT,arg,argv);
//	_spawnvp(P_WAIT,arg,argv);
	_spawnvp(P_WAIT,argv[0],argv);
//	exit(1);
//	abort();
//	exit(0);
//	while(1)
//	{
//		printf("!");
//	}
	printf("!");
	return 0;//����� ����� �� ����
}
