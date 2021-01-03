#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

struct st
{
    char familia [50];
    int kolichestvo_mest;
    int ves_bagaja;
}pass;

void vvesti(FILE *vvod)
{
	char ch;
	vvod = fopen("vivod.txt","wb");
	system("CLS");
	do
	{
		cout << "\nfamilia   ";
		cin >> pass.familia;
		cout << "\nkolichestvo_mest  "; 
		cin >> pass.kolichestvo_mest;
		cout << "\nves_bagaja "; 
		cin >> pass.ves_bagaja;
		fwrite(&pass,sizeof(pass), 1, vvod);
		cout << "\nzakonchit? (y/n)\n";
		cin >> ch;
	} while (ch != 'y');
	fclose(vvod);
}

void vivesti(FILE *vvod)
{
	int i;
	system("CLS");
	vvod = fopen("vivod.txt","rb");
	i = 1;
	fread(&pass, sizeof(pass), 1, vvod);
	while (!feof(vvod))
	{
		printf("\n %3d  familia   %s \t kolichestvo_mest %d \t ves_bagaja %.d \n",i, pass.familia, pass.kolichestvo_mest, pass.ves_bagaja);
		fread(&pass, sizeof(pass), 1, vvod);
		i++;
	}
	fclose(vvod);
	system("pause");
}

void dobavit(FILE *vvod)
{
	char ch;
	vvod = fopen("vivod.txt","ab");
	system("CLS");
	do
	{
		cout << "\nfamilia   ";
		cin >> pass.familia;
		cout << "\nkolichestvo_mest  "; 
		cin >> pass.kolichestvo_mest;
		cout << "\nves_bagaja "; 
		cin >> pass.ves_bagaja;
		fwrite(&pass,sizeof(pass), 1, vvod);
		cout << "\nzakonchit? (y/n)\n";
		cin >> ch;
	} while (ch != 'y');
	fclose(vvod);
}

void udalit(FILE *vvod)
{
	FILE* copia;
	vvod = fopen("vivod.txt","rb+");
	copia = fopen("copia.txt", "wb");
	system("CLS");
	fread(&pass, sizeof(pass), 1, vvod);
	while (!feof(vvod))
	{
		if (pass.ves_bagaja>=10)
		fwrite(&pass, sizeof(pass), 1, copia);
		fread(&pass, sizeof(pass), 1, vvod);
		 
	}
	fclose(vvod);
	fclose(copia);
	remove("vivod.txt");
	rename("copia.txt","vivod.txt");
}

int main ()
{
    char x;
    FILE *vvod, *vivod;
    while (1)
    {
        system ("CLS");
        cout << "1. sozdat noviy fail\n";
        cout << "2. prosmotret fail\n";
        cout << "3. dobavit novuu zapis\n";
        cout << "4. udalit s vesom bagaja menhe 10kg\n";
        cout << "5. vihod\n";
        cin >> x;
        switch (x)
        {
            case '1': vvesti (vvod); break;
            case '2': vivesti (vvod); break;
            case '3': dobavit (vvod); break;
            case '4': udalit (vvod); break;
            case '5': return 0;
            default : cout << "ohibka";
        }
    }
    system ("pause");
    return 0;
}
