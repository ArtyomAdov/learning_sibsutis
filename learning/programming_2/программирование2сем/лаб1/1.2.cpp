#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define Pi 3.14159265358
float cosin(float);
long fact(long);
main() {
    float x,c=0,t=0;
    printf("vvedite x\n");
    scanf("%f",&x);
    c=cos(x);
    t=cosin(x);
    printf("cosinusom=%f\n",c);
    printf("teylorom=%f\n",t);
system("PAUSE");
}
float cosin(float x1) {
float t1=1,eps=0.0001;
int n=1,p=1;
   while(abs(t1)>=eps) {//ошибка именно тут
   	    t1=t1+(pow(-1,n)*(pow(x1,2*n)/(fact(2*n))));
   	    n=n*2;
    };
return t1;
}
long fact(long n1) {
	if(n1<0) return 0;
	if(n1==0) return 1;
	if(n1==1) return 1;
	int f=1;
	for(int i=1;i<=n1;i++) {
		f=f*i;
	};
	return f;
}
//добавить деление на 2н факториал как новую переменную (через вайл от 1 до н перемножать)
/*double PI,z,n,a,g;
n=1;
a=0.00001;
z=0;
g=1;
while(1/n>a) {z=z+1/n*pow(-1,g+1);n=n+2;g++;}
PI=4*z;
printf("PI=%f ",PI);//3.141573*/
//провер€ть 3.14 как ѕи и при нем кос примерно -1
//“очность вычислени€ суммы дл€ убывающих знакочередующихс€ р€дов считаетс€ достигнутой, когда очередной элемент р€да по модулю становитьс€ меньше заданной точности.
