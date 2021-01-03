#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <conio.h>

using namespace std;

struct base2
{
	char fio[30];
	short int num;
	char dol[22];
	char dat[10];
	struct base2 *next; 
};


int main()
{
	FILE *fp;
	fp=fopen("testBase2.dat", "rb");
	record tt[4000]={0};
	record1 mas[4000]={0};
	record2 mas2[4000]={0};
	record3 mas3[4000]={0};
	int i=0;
	i=fread((record2 *)mas2, sizeof(record2), 4000, fp);
	cout<<i<<endl;
	for(int i=0;i<4000;++i)
		cout<<tt[i].author<<endl<<tt[i].title<<endl<<tt[i].publisher<<endl<<tt[i].year<<endl<<tt[i].num_of_page<<endl<<endl;
		i=0;
	while((i++)<500)
	{
		getchar();
		cout<<mas3[i].a<<endl<<mas3[i].b<<endl<<mas3[i].c<<endl<<mas3[i].d<<endl<<mas3[i].e<<endl<<endl;
	}
	i=0;
	while((i++)<500)
	{
		getchar();
		cout<<mas[i].a<<endl<<mas[i].b<<endl<<mas[i].c<<endl<<mas[i].d<<endl<<endl;
	}
	while((i++)<500)
	{
		getchar();
		cout<<mas2[i].a<<endl<<mas2[i].b<<endl<<mas2[i].c<<endl<<mas2[i].d<<endl<<endl;
	}
	cout<<sizeof(record)<<endl<<sizeof(record1)<<endl<<sizeof(record2)<<endl<<sizeof(record3)<<endl<<endl;
	getch();
	return 0;
}
