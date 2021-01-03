#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <process.h>

char* Convert_Command(char* buf)//������� ������� ��������� � ������� �������
{
	if(!strncmp(buf,"clear",5))//���� ��������� ������� ������������ clear ���������� cls
	{
		return "cls";
	}
	if(!strncmp(buf,"ifconfig",8))
	{
		return "ipconfig";
	}
	if(!strncmp(buf,"users",5))
	{
		return "net user";
	}
	if(!strncmp(buf,"bash",4))
	{
		return "cmd";
	}
	if(!strncmp(buf,"exit",4)) // ���� ��� ������ exit 
	{
		return NULL;//���������� NULL (��� ������ �� ������������ ����� � main)
	}
	printf("command not found in bash synonym\n");//������� ��������� � ��� ��� ������� ��
												// ���� ������� ����� ��������� bash ������
	return buf; // ���������� ������������ �������
}

int main()
{
	while(1)//����������� ����
	{
		char* buf = NULL; //���������� ��� ����� ������� �������������
		char* conv = NULL; // ���������� ��� ��������� �������� �� bash ������� ��� cmd
		char path[MAX_PATH]; // ���������� ��� �������� ������� ����������
		char symbol = '0'; // ���������� �������������� ��� ����� ������������� ������� �����������
		int buf_size = 10; // ��������� ���������� �������� � ������� ������������
		if(GetCurrentDirectory(MAX_PATH,path) == 0) //���������� ������� ��������� ������� ����������
		{
			printf("couldn't get the current directory\n");// ��������� � ��� ��� ���������� �� �������
			return 1; //���������� ������ � �������
		}
		printf("%s ",path); //������ ������� ����������
		buf = (char*) calloc (buf_size, sizeof(char)); //��������� ������ ��� ������� ������������
		for(short int i = 0; (symbol != '\n'); i++) //���� ������������ �� ������ enter ���������� ��������� ����
		{
			symbol = getc(stdin); // ���� ������ �������
			if(buf_size <= i) // �������� ��� ���������� �������� �� ��������� ������ ������� �������
			{//���� ��������� ��
				buf_size += buf_size; // ����������� ������ ������� ������� �����
				buf = (char*)realloc(buf,buf_size); // ������������ ������ ��� ������� �������
				if(buf == NULL)// ���� ��������� ������ �� ����� ��������� ������
				{
					printf("Error: fail realloc\n");// ��������� �� ������ ������� realloc
					return 1;//���������� ������ � �������
				}
			}
			buf[i] = symbol;//������ � ������ ������ ������� ���������� �������������
		}
		conv = Convert_Command(buf); // �������� ������� ��� ���������������
		if(conv==NULL) // ���� ��� ��������� NULL 
		{
			return 0;//��������� ������ ��� ������
		}
		char* com[] = {"cmd","/C",conv,NULL};  // ������� ��������� ������ ��� ������� spawnvp � ��������� ���
		_spawnvp(_P_WAIT,com[0],com);//��������� ������� spawnvp ��������������� ������������ �������
	}
	return 0;
}
