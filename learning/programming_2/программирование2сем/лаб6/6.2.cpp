#include <stdio.h>
#include <stdlib.h>
#include <math.h>
long double fact(double);
void veroyatnost(float&,float&,float&,float,float,float,float);
int main()
{
	float m,n,p,q,vrd=1,vrm=2,c;
	printf("vvedite kol-vo detei\n");
	scanf("%f",&n);
	printf("vvedite kol-vo jelaemih malchikov ili devochek\n");
	scanf("%f",&m);
	p=0.45;
	q=1-p;
	veroyatnost(vrm,vrd,c,n,m,p,q);
	printf("veroyatnost s malchikami=%f\nveroyatnost s devochkami=%f\n",vrm,vrd);
	return 0;
	system("PAUSE");
}
long double fact(double x)
{
	if(x==0||x==1)
	{
		return 1;
	}
	return x+fact(x-1);
}
void veroyatnost(float& vrm,float& vrd,float& c,const float n,const float m,const float p,const float q)
{
	c=fact(n)/(fact(m)*fact(n-m));
	vrd=c*pow(p,m)*pow(q,n-m);
	vrm=c*pow(q,m)*pow(p,n-m);
}
