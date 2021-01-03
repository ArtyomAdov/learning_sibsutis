 #include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
const int n=5;	
struct structure
	{
	char name[20];
	char surname[20];
	char flat[20];
	char call[20];
	};
int main()
{
	int A[n], B[n], C[n], D[n], i;	
	structure Numbers[n] = 
	{
		"Artyom", "Adov"       , "901"          , "89139183431", 
		"Nikita", "Zahlevniy"  , "901"          , "82835839100", 
		"Maxim" , "Flor"       , "33"           , "89932590111", 
		"Anna"  , "Anna"       , "45"           , "89451323545", 
		"Ivan"  , "Gromov"     , "914"          , "89423959123"
	};
	for (i = 0; i < n; i++)
	{
		A[i] = i;
		B[i] = i;
		C[i] = i;
		D[i] = i;
	}
	int min, tmp, j;
	for (i = 0; i < n - 1; i++)
	{
		min = i;
		for (j = i + 1; j < n; j++) 
		{
			if (strcmp(Numbers[A[j]].name, Numbers[A[min]].name) < 0)
			{
				min = j;
			}
		}
		if (i == min) continue;
		tmp = A[i];
		A[i] = A[min];
		A[min] = tmp;
	}
	for (i = 0; i < n - 1; i++)
	{
		min = i;
		for (j = i + 1; j < n; j++) 
		{
			if (strcmp(Numbers[B[j]].surname, Numbers[B[min]].surname) < 0)
			{
				min = j;
			}
		}
		if (i == min) continue;
		tmp = B[i];
		B[i] = B[min];
		B[min] = tmp;
	}
	for (i = 0; i < n - 1; i++)
	{
		min = i;
		for (j = i + 1; j < n; j++)
		{
			if (strcmp(Numbers[C[j]].flat, Numbers[C[min]].flat) < 0) 
			{
				min = j;
			}
		}
		if (i == min) continue;
		tmp = C[i];
		C[i] = C[min];
		C[min] = tmp;
	}
	for (i = 0; i < n - 1; i++) 
	{
		min = i;
		for (j = i + 1; j < n; j++)
		{
			if (strcmp(Numbers[D[j]].call, Numbers[D[min]].call) < 0) 
			{
				min = j;
			}
		}
		if (i == min) continue;
		tmp = D[i];
		D[i] = D[min];
		D[min] = tmp;
	}
	cout << "Sort name:\n\n";
	for (i = 0; i < n; i++) 
	{
		cout << Numbers[A[i]].name << "         " << Numbers[A[i]].surname << "       " << Numbers[A[i]].flat << "        " << Numbers[A[i]].call << endl;
	}
	cout << endl << "Sort surname:\n\n";
	for (i = 0; i < n; i++)
	{
		cout << Numbers[B[i]].name << "         " << Numbers[B[i]].surname << "       " << Numbers[B[i]].flat << "        " << Numbers[B[i]].call << endl;
	}
	cout << endl << "Sort flat:\n\n";
	for (i = 0; i < n; i++)
	{
		cout << Numbers[C[i]].name << "         " << Numbers[C[i]].surname << "       " << Numbers[C[i]].flat << "        " << Numbers[C[i]].call << endl;
	}
	cout << endl << "Sort call:\n\n";
	for (i = 0; i < n; i++)
	{
		cout << Numbers[D[i]].name << "         " << Numbers[D[i]].surname << "       " << Numbers[D[i]].flat << "        " << Numbers[D[i]].call << endl;
	}
	system("PAUSE");
	return 0;
}
