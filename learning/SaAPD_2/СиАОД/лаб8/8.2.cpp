 #include <iostream>//не доделал
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
	int A[n], B[n], C[n], D[n], i, key;	
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
	cout << "write key"<<endl;
	cin >> key;
	int C=0,i,L=0,R=n-1;
	while(L<R)
	{
		i=(L+R)/2;
		C++;
		if(A[i]<X)
		{
			L=i+1;
		}
		else
		{
			R=i;
		}
	}
	int j=R;
	C++;
	while(j<n&&A[j+1]==X)
	{
		C++;
		j++;
		printf("\nSearchTwo=%d\n",j);
	}
	if(A[R]==X)
	{
		
	}
	system("PAUSE");
	return 0;
	
}
