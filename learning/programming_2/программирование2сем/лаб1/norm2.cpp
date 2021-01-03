#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ll long long
#define Pi 3.14159265358
ll  fact(int);
float cosinus(float);
main()
{
	float f,x,c;
	printf("vvedite x\n");
	scanf("%f",&x);
	c=cos(x);
	printf("cosinusom=%f\n",c);
	f=cosinus(x);
	printf("teylorom=%f\n",f);
	system("PAUSE");
}
ll fact(int n)
{
	ll f=1;
	for(int i=1;i<=n;i++)
		f=f*i;
	return f;
}
float cosinus(float x)
{
	while(x>2*Pi)
	{
		x=x-(2*Pi);
	};
	int z=1,n=0;
	float s=1,k=0,eps=0.0001;
	while(s>eps)
	{
		s=pow(x,2*n)/fact(2*n);
		k=k+z*s;
		z=-z;
		n++;
	}
	return k;
}
