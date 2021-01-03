#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

using namespace std;
struct base
{
 char fio[30];
 int number;
 char profession[22];
 char data[10];
}

int main()
{
FILE *f; //объ€вление файла, а - идентификатор
int stop, i=0, c=0; 
f=fopen ("testBase2.dat", "rb"); //им€ файла, режим доступа (только дл€ чтени€, бинарный файл)
base massive[4000]={0};
	i=fread((base *)massive, sizeof(base), 4000, f);
    for(i=0;i<4000;i++)
      {c++;
      cout<<massive[i].fio<<massive[i].number<< massive[i].profession<<massive[i].data<<endl;
      if(c==20)
      {
      printf("Pokazat eshe 20 zapisei? ( 1 - yes)");
       scanf("%d",&stop);
       if(stop==1)  c=0;
       else break;
	  }
      }

      }
 return 0;
}
