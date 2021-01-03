#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define E 0.001
#define d 0.001
#define STEP 10000

float a;
float b;




float Non_line_function(float x);
float Derivative(float x);
float Method_half_division(float a, float b);
float Equation_line(float a, float b);
float Method_chords(float a, float b);
float Method_Newton();









int main()
{
	float x, a = 1, b = 6;

	x = Method_half_division(a, b);
	printf("Method_half_division: x = %f\n", x);
	x = Method_chords(a, b);
	printf("Method_chords: x = %f\n", x);
	x = Method_Newton();
	printf("Method_Newton: x = %f\n", x);
	//y = Non_line_function(x);
	//printf("x = %f\ny = %f\n", x, y);

	return 0;
}


//ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo

	float Non_line_function(float x)
	{
		return (x * x - 25);
	}


float Method_half_division(float a, float b)
{
	float fa, fb, c, fc;
	int n = 0;

	fa = Non_line_function(a);
	fb = Non_line_function(b);

	if (fa * fb > 0) {
		printf("Error, no roots\n");
		//exit(1);
		return 0;
	}

	for (;(fabsf(b - a) / 2) >= E;) {
		c = (a + b) / 2;
		fc = Non_line_function(c);
		if (fa * fc < 0) {
			b = c;
			fb = Non_line_function(b);
		} else {
			a = c;
			fa = Non_line_function(a);
		}

		n++;
		//printf("a = %f\n", a);
		//printf("fa = %f\n\n", fa);
		//printf("b = %f\n", b);
		//printf("fb = %f\n\n", fb);
		//printf("c = %f\n", c);
		//printf("fc = %f\n\n", fc);
	}

	printf("Iter: %d\n", n);

	return c;
}






float Method_chords(float a, float b)
{
	float fa, fb, c, fc, x = 0;
	int n = 1;

	fa = Non_line_function(a);
	fb = Non_line_function(b);

	if (fa * fb > 0) {
		printf("Error, no roots\n");
		//exit(1);
		return 0;
	}

	c = Equation_line(a, b);

	for (; fabsf(c - x) > E;) {
		fc = Non_line_function(c);
		fa = Non_line_function(a);
		if (fa * fc < 0) {
			b = c;
		} else {
			a = c;
		}

		x = c;
		c = Equation_line(a, b);
		n++;
		//printf("a = %f\n", a);
		//printf("fa = %f\n\n", fa);
		//printf("b = %f\n", b);
		//printf("fb = %f\n\n", fb);
		//printf("c = %f\n", c);
		//printf("fc = %f\n\n", fc);
	}
	printf("Iter: %d\n", n);

	return c;
}



	float Equation_line(float a, float b)
	{
		float fa = Non_line_function(a);
		float fb = Non_line_function(b);
		return ((a * fb - b * fa) / (fb - fa));
	}


float Method_Newton()
{
	float x = 1, h = 0;
	int n = 1;

	h = Non_line_function(x) / Derivative(x);
	x = x - h;

	for (; fabsf(h) > E;) {
		h = Non_line_function(x) / Derivative(x);
		x = x - h;
		n++;
	}
	printf("Iter: %d\n", n);

	return x;
}


	float Derivative(float x)
	{
		return (2 * x);
	}
