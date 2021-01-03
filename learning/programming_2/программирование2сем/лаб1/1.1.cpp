#include <stdio.h>
#include <stdlib.h>
float step (float, int);
int main(){
float y=1,x;
int n;
printf ("vvedite osnovanie x = ");
scanf ("%f",&x);
printf ("vvedite stepen n = ");
scanf ("%d",&n);
if (n!=0) {
    y=step (x,n);};
printf ("virajenie y = %f \n",y);
system("PAUSE");
}
float step (float x1, int n1) {
if (n1==0) {
    return 1;
};
float y1=1;
for (int i=0; i<abs(n1);i++) {
    y1=y1*x1;
};
if (n1<0) {
    y1=1/y1;
};
return y1;
}
