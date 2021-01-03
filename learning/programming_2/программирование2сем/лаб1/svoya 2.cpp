#include <stdlib.h>
#include <stdio.h>
#include <math.h>
const float Pi=3.14;
long fact(long);
float cosin(float);
int main()
{
	float t=0,f=0,x=0,c=0;
	printf("vvedite x\n");
	scanf("%f",&x);
	c=cos(x);
	  printf("cosinusom=%f\n",c);
	t=cosin(x);
	printf("teylorom=%f\n",t);
	system("PAUSE");
}float cosin(float x)
{
	float t1=1,eps=0.0001;
	long n=1;
	while(x>(2*Pi))
	{
		x=x-(2*Pi);
	};
	while(abs(t1)>eps)
	{
		t1=t1+(pow(-1,n)*pow(x,(2*n)))/(fact(2*n)); /////////n=1
		n++;
	};
	return t1;
}
long fact(long n)
{
	if(n<=1)
	{
		return 1;
	}
	else
	{
		return n*fact(n-1);
	};
}
