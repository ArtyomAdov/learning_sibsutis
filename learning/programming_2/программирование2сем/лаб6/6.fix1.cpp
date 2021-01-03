#include <stdlib.h>
#include <stdio.h>
#include <math.h>
int triangle(float*,float*,float,float,float);
int main()
{
	float s=0,p=0,a,b,c;
	printf("vvedite stotoni treugolnika\n");
	scanf("%f%f%f",&a,&b,&c);
	triangle(p,s,a,b,c);
	printf("perimetr=%f\nplohad=%f\n",p,s);
}
int triangle(float* p,float* s,float a,float b,float c){
	float p1;
	if(a+b<=c)
	{
		printf("error");
		exit(0);
	}
	else 
	if(a+c<=b)
	{
		printf("error");
		exit(0);
	}
	if(c+b<=a)
	{
		printf("error");
		exit(0);
	}
	*p=a+b+c;
	p1=(float)*p/2;
	*s=sqrt(p1*(p1-a)*(p1-b)*(p1-c));
	return 1;
}
