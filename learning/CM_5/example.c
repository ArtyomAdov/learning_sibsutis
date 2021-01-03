#include <stdio.h>
typedef struct
{
	double a,b;
} complex_t;

complex_t add(complex_t x, complex_t y) //+
 {
     complex_t t;
     t.a = x.a + y.a;
     t.b = x.b + y.b;
     return t;
 }
 
complex_t sub(complex_t x, complex_t y) //-
 {
     complex_t t;
     t.a = x.a - y.a;
     t.b = x.b - y.b;
     return t;
 }
 
 complex_t mul(complex_t x, complex_t y) //*
 {
     complex_t t;
     t.a = x.a * y.a - x.b * y.b;
     t.b = x.a * y.b + x.b * y.a;
     return t;
 }
 
 complex_t div(complex_t x, complex_t y) // /
 {
     complex_t t;
     t.a = (x.a * y.a + x.b * y.b)/(y.a*y.a+y.b*y.b);
     t.b = (x.a * y.b - x.b * y.a)/(y.a*y.a+y.b*y.b);
     return t;
 }

 
int main()
 {
     double a1,b1,a2,b2;
     printf ("write 4 numeric: \n");
     while(scanf ("%lf%lf%lf%lf", &a1,&b1,&a2,&b2) == 4) {//взять на заметку для ввода и потестить
     complex_t x = {a1,b1}; // ?????? ?.?.
     complex_t y = {a2,b2}; // ?????? ?.?.
     complex_t a = add(x,y); // ????? ?.?.
     complex_t s = sub(x,y); // ????????? ?.?.
     complex_t m = mul(x,y); // ????????? ?.?.
     complex_t d = div(x,y); // ??????? ?.?.
     printf ("a = (%5.2lf, %5.2lfi)\n", a.a, a.b ); // ????????? ????????????
     printf ("s = (%5.2lf, %5.2lfi)\n", s.a, s.b ); // ????????? ?????????
     printf ("m = (%5.2lf, %5.2lfi)\n", m.a, m.b ); // ????????? ?????????
     printf ("d = (%5.2lf, %5.2lfi)\n", d.a, d.b ); // ????????? ???????
        return 0;  
     }
     return 0;
 }
#if 0
//exp for z 
struct mycomplex { double real; double imag; }

struct mycomplex my_exp(struct mycomplex z) {
struct mycomplex w;
w.real = exp(z.real)*cos(z.imag);
w.imag = exp(z.real)*sin(z.imag);
return w;
}
#endif
