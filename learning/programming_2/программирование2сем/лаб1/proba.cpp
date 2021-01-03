#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#define Pi 3.14159265358
int fact();
long double cosin(long double);
main(){
	float x,c,t;
	printf("vvedite x\n");
    scanf("%f",&x);
    c=cos(x);
    t=cosin(x);
    printf("cosinusom=%f\n",c);
    printf("teylorom=%f\n",t);
system("PAUSE");
}
int fact(int n){
	int f=1;
	for(int i=1;i<=n;i++)
		f=f*i;
	return f;
}
long double cosin(long double x){
	while(x>2*Pi)
		x=x-(2*Pi);
	int z=1,n=0;
	float s=1,k=0,eps=0.0001;
	while(s>eps) {
		s=pow(x,2*n)/fact(2*n);
		k=k+z*s;
		z=-z;
		n++;
	}
	return k;
}
