#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
struct Obsh
{
	int nomer;
	double area;
	double sred;
	int stud;
	string fak;
};
int main()
{
	int n;
	cout << " Vvedite kol-vo komnat - " ;
	cin >> n;
	int s[n],flag[n];
	double f[n];
	Obsh A[n];
	int C[n];
	string B[n];
	for(int i=0;i<n;i++)
	{
		cout << " Vvedite fakulet - " ;
		cin >> A[i].fak;
		cout << " Vvedtie nomer komnati - ";
		cin >> A[i].nomer;
		cout << " Vvedite ploshad komnati - ";
		cin >> A[i].area;
		cout << " Vvedite kol-vo studentov v komnate - ";
		cin >> A[i].stud;
		A[i].sred = A[i].area/A[i].stud;
	}
	
	for(int i=0;i<n;i++)
	{
		B[i] = A[i].fak;
		s[i] = A[i].stud;
		C[i] = 1;
		f[i] = A[i].sred;
		flag[i] = 0;
	}
	for(int i=0;i<n;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			if(B[i] == A[j].fak)
			{
				C[i] += 1; 
				s[i] += A[j].stud;
				f[i] += A[j].sred;
				flag[i] += 1;
			}
		}
	}
	for(int i=0;i<n;i++)
	{
		if(flag[i] != 0)
		{
			cout << " Fakult - " << A[i].fak << "\t |";
			cout << " Komnat - " << C[i] << "\t |";
			cout << " Student - " << s[i] << "\t |";
			cout << " Sred plosh - " << f[i] << "\t |";
			cout << endl;
			i++;
		}
		else
		{
			cout << " Fakult - " << A[i].fak << "\t |";
			cout << " Komnat - " << C[i] << "\t |";
			cout << " Student - " << s[i] << "\t |";
			cout << " Sred plosh - " << f[i] << "\t |";
			cout << endl;
		}
	}	
}
