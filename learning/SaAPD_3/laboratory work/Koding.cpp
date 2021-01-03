#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <map>

using namespace std;

int n=0;
char **c;



void InsertSort(double A[],int n,char B[])
{
	int i, j,P1;
	double t;
	char temp;
 	for (i=1;i<n;i++) 
  	{
    	t=A[i];
		temp=B[i] ;
    	j=i-1;
    	while(j>=1 && A[j]<t) 
    	{
       		A[j+1]=A[j];
			B[j+1]=B[j]; 
        	j=j-1;
    	}
    	B[j+1]=temp;
    	A[j+1]=t; 
	}
}

void Shenon(double *p,double *q,int *l)
{
	q[0]=0;l[0]=0;
	for(int i=1;i<n;i++)
	{
		q[i] = q[i-1] + p[i];
		double s=-log2(p[i]);
		l[i] = ceilf(s);
	}
	for(int i=1;i<n;i++)
	{
		for(int j=1;j<n;j++)
		{
			q[i-1] = q[i-1] * 2;
			int t=q[i-1];
			if(t==0)c[i][j]='0';
			if(t==1)c[i][j]='1';
			if(q[i-1]>1)q[i-1]=q[i-1]-1;
		}
	}
}

int med(int L,int R,double *p)
{
	double Sl=0,Sr=0;
	int m;
	for(int i=L;i<R;i++)
	{
		Sl=Sl+p[i];
	}
	Sr=p[R];
	m=R;
	while(Sl>=Sr)
	{
		m--;
		Sl=Sl-p[m];
		Sr=Sr+p[m];
	}
	return m;
}

void Fano(int R,int L,int k,int *l,double *p)
{
	if(L<R)
	{
		k++;
		int m=med(L,R,p);
		for(int i=L;i<=R;i++)
		{
			if(i>m)
			{
				c[i][k]='1';
				l[i]++;
			}
			else
			{
				c[i][k]='0';
				l[i]++;
			}
		}
		Fano(m,L,k,l,p);
		Fano(R,m+1,k,l,p);
	}
}

void Gilbert(double *p,double *q,int *l)
{
	double pr=0;
	for(int i=1;i<n;i++)
	{
		q[i] = pr + p[i]/2;
		pr+=p[i];
		double s=-log2(p[i]);
		l[i] = ceilf(s)+1;
	}
	for(int i=1;i<n;i++)
	{
		for(int j=1;j<=l[i];j++)
		{
			q[i]*=2;
			int t=q[i];
			if(t==0)c[i][j]='0';
			if(t==1)c[i][j]='1';
			if(q[i]>1)
			{
				q[i]--;
			}
		}
	}
}

int Up(int m,double q,double p[])
{
	int j=1;
	for(int i=m-1;i>1;i--)
	{
		if(p[i-1]<=q)
		{
			p[i]=p[i-1];
		}
		else
		{
			j=i;
			break;
		}
	}
	p[j]=q;
	return j;
}
void Down(int m,int j,int *l)
{
	char S[m];
	for(int i=0;i<m;i++)
	{
		S[i]=c[j][i];
	}
	int L=l[j];
	for(int i=j;i<=m-2;i++)
	{
		for(int k=0;k<m;k++)
		{
			c[i][k]=c[i+1][k];
		}
		l[i]=l[i+1];
	}
	for(int i=0;i<m;i++)
	{
		c[m][i] = S[i];
		c[m-1][i] = S[i];
	}
	c[m-1][L+1]='0';
	c[m][L+1]='1';
	l[m-1]=L+1;
	l[m]=L+1;
}
void Haff(int m,double p[],int *l)
{
	if(m==2)
	{
		c[1][1] = '0';l[1]=1;
		c[2][1] = '1';l[2]=1;
	}
	else
	{
		double q=p[m-1]+p[m];
		int j=Up(m,q,p);
		Haff(m-1,p,l);
		Down(m,j,l);
	}
}

int main()
{	
	string s;
	int suber=0;
	map<char,int>map;
	ifstream file("text.txt");
	getline(file,s);
	istringstream ist(s);
	
	while(ist >> s)
	{
		for(int i=0;i<sizeof(s);i++)
		{
			map[s[i]]++;
			suber++;
		}
	}
	
	for ( auto it = map.begin(); it != map.end(); ++it )
    {
    	//cout << it->first << "\t\t" << it->second << endl;
    	n++;
	}
	n++;
	double p[n],q[n],x=0;
	int l[n]={0},m=1,k;
	char Sim[n];
	c = new char *[n];
	for(int i=0;i<n;i++)
	{
		c[i] = new char [n];
	}
	
	for ( auto it = map.begin(); it != map.end(); ++it )
    {
    	k=it->second;
    	p[m]=(double)k/suber;
    	Sim[m]=it->first;
    	m++;
	}
	cout << endl;
	for(int i=1;i<n;i++)
	{
		//cout <<"|"<<Sim[i] <<"| - |"<<p[i]<<"| ";
		x+=p[i];
	}
	cout << x << endl;
	double lsr[4]={0},h[4]={0};
	InsertSort(p,n,Sim);
	
	Fano(n-1,1,0,l,p);
	cout << "FANO" << endl;
	cout << "Simvol \t\t" << "Ver \t\t" << "Kod slovo \t\t" << "Dlina" << endl;
	for(int i=1;i<n;i++)
	{
		cout << Sim[i] <<"|\t\t";
		cout << p[i] << "\t\t";
		for(int j=1;j<=l[i];j++)
		{
			cout << c[i][j] ;
		}
		cout << "\t\t\t" << l[i] << endl;
	}
	for(int i=1;i<n;i++)
	{
		lsr[0]+=p[i]*l[i];
		double y=-log2(p[i]);
		h[0]+=p[i]*y;
	}
	cout << "Lsr = " << lsr[0] << " < " << h[0] << " + 1" << endl;
	for(int i=0;i<n;i++)
	{
		l[i]=0;
		q[i]=0;
		for(int j=0;j<n;j++)
		{
			c[i][j]='0';
		}
	}
	double P[n];
	for(int i=1;i<n;i++)
	{
		P[i]=p[i];
	}
	Haff(n-1,P,l);
	cout << "Haffman" << endl;
	cout << "Simvol \t\t" << "Ver \t\t" << "Kod slovo \t\t" << "Dlina" << endl;
	for(int i=1;i<n;i++)
	{
		cout << Sim[i] <<"|\t\t";
		cout << p[i] << "\t\t";
		for(int j=1;j<=l[i];j++)
		{
			cout << c[i][j] ;
		}
		if(l[i] > 7)
		{
			cout << "\t\t" << l[i] << endl;
		}
		else
		{
			cout << "\t\t\t" << l[i] << endl;
		}
	}
	for(int i=1;i<n;i++)
	{
		lsr[1]+=p[i]*l[i];
		double y=-log2(p[i]);
		h[1]+=p[i]*y;
	}
	cout << "Lsr = " << lsr[1] << " < " << h[1] << " + 1" << endl;
}
