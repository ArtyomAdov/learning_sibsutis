#include <stdio.h>
#include <stdlib.h>
#include <iostream>	
// ���� ������ "��������� ��������"
using namespace std;
struct str
{
 char fio[30]; // ���  <�������>_<���>_<��������>
 unsigned short int summa; // ����� ������
 char data[10]; // ���� �������� ��-��-��
 char fioadv[22]; //��� ��������
};
main()
{
      FILE *f; int i=0;int c=0;int s=0;
      f=fopen("testBase3.dat","rb");
      str mass[4000]={0};
      i=fread((str *)mass, sizeof(str), 4000, f);
      for(i=0;i<4000;i++)
      {c++;
      cout<<mass[i].fio<<mass[i].summa<< mass[i].data<<mass[i].fioadv<<endl;
      if(c==20)
      {
      printf("Pokazat eshe 20 zapisei? ( 1 - yes)");
       scanf("%d",&s);
       if(s==1)  c=0;
       else break;}
       }
      system("PAUSE");
      }
      
