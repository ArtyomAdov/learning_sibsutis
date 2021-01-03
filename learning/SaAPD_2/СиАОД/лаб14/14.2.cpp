#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>

using namespace std;

const int m = 11;

struct spis{
	spis *next;
	int x;
} *head[m];

int hf(int *a, int i, int m){
	int j;
	j=a[i];
	while(j>m){
		j-=m;
	}
	return j;
}

void FillRand (int *a, int *b, int *c, int n) 
{
	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % 100 + 1;
	}
	for(int i=0; i<m;i++){
		b[i]=0;
		c[i]=0;
	}
	for(int i = 0; i < m; i++)
		head[i] = NULL;
}

void FillSpis (int *a, int n)
{	
for (int i = 0; i < n; i++)
	{
	int j = hf(a, i, m);
	spis *el = new spis;
	el -> x = a[i];
	el -> next = head[j];
	head[j]=el;
	}
}

void PrintSpis ()
{	
     spis *p;
	 for (int i = 0; i < m; i++)
	 {
		 cout<<i; 
		 for(p = head[i]; p != NULL; p = p -> next)
		 cout<<" "<<p -> x;
		 cout<<"\n";
	 }
}

void SearchSpis (int *a)
{ 
	int status = 0, element;
	spis *p;
	while (!status)
	{
		 cout<<"\n\nvvedite kluch poiska\n";
		 cin>>element;
		 int j = element % m;
		 for (p = head[j]; p; p = p -> next)
		 {
				if (p -> x == element) 
				{
					cout<<"naiden v "<<j<<" ocheredi\n";
					 break;
				}
				else 
					 if (p -> next == NULL) 
					 	cout<<"ne naiden\n";
					 	
		 }
		 cout<<"Zakonchit? (1 - da, 0 - net)";
		 cin>>status; 
	}
}

int Kvatro (int *a, int *b, int n)
{
	int kol = 0;
	for (int i = 0; i < n; i++)
	{
		 int j = hf(a, i, m);
		 int d = 1;
		 while (1)
		 {
			if (b[j] == a[i]) break;
			if (b[j] == 0)
			{	
				b[j] = a[i];
				break;
			}
			if (d >= m) return kol;
			j += d;
			kol++;
			if (j >=m) j -= m;
			d += 2;
		}
	}
	return kol;
}

int Line (int *a, int *c, int n)
{
	int kol = 0;
	for (int i = 0; i < m; i++)
	{
		int j = hf(a, i, m);
		while (1)
		{
			if (c[j] == a[i]) break;
			if (c[j] == 0)
			{	
				 c[j] = a[i];
				 break;
			}
			j++;
			if (j >= m) j -= m;
			kol++;
		}
	}
	return kol;
}

void PrintMas(int *a, int b)
{
	for(int i = 0;i < b;i++)
	if(a[i]<10) cout<<a[i]<<"  ";
	else cout<<a[i]<<" ";
}

void PrintMark(int n)
{
	 for(int i = 0;i < m;i++)
	 if(i>9) cout<<i<<" ";
	else cout<<i<<"  ";
}

int main()
{     
     srand(time(NULL));
     int n;
	 cout<<"Kol-vo elementov\n";
	 cin>>n;
	 int a[n], b[n], c[n];
	 FillRand (a, b, c, n);
	 FillSpis(a, n); 
	 int kolS = Kvatro (a, b, n);
	 int kolL = Line (a, c, n);
	 cout<<"\nIshodnii massiv\n";PrintMas(a, n);cout<<"\n";
	 cout<<"\nMetod pryamogo svyazivaniya\n";PrintSpis();
	 cout<<"\nKvadratichnaya proba\n";
	 PrintMark(n);
	 cout<<"\n"; 
 	 PrintMas(b, m); 
	 cout<<"\n";
	 cout<<"\nLineynaya proba\n";
	 PrintMark(n);
	 cout<<"\n"; 
 	 PrintMas(c, m); 
	 cout<<"\n\n";
	 cout<<"____________________________________________________________________\n";
	 cout<<"| Razmer hesh |     Kol-vo         |       kol-vo kollisiy         |\n";
	 cout<<"|  tablici    |    elementov       |  lineynie    |  kvadratichnie |\n\n";
	 cout<<"|_____________|____________________|______________|________________|\n"; 
	 cout<<"|      "<<m<<"      |         "<<n<<"         |      "<<kolL<<"      |    "<<kolS<<"          |\n";
	 cout<<"|_____________|____________________|______________|________________|\n";
	 SearchSpis (a); 
	 system("PAUSE");
}
