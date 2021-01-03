#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float Dy(float *Y, int j, int i)
{
	if (i == 1) {
		return Y[j + 1] - Y[j];
	} else if (i == 0) {
		return Y[0];
	} else {
		return Dy(Y, j + 1, i - 1) - Dy(Y, j, i - 1);
	}

	return 0;
}

float Factorial(int n)
{
	if (n == 0) {
		return 1.0;
	} else {
		return n * Factorial(n - 1);
	}
	return 0;
}

float P(float *X, float *Y, float x, int n)
{
	float y, step;
	float *dy;

	y = 0;
	step = X[1] - X[0];
	dy = malloc(sizeof(float) * n);

	for (int i = 0; i < n; i++) {
		dy[i] = Dy(Y, 0, i);
	}

	// for (int i = 0; i < n; i++) {
	// 	printf("%.3f\n", dy[i]);
	// }

	for (int i = 0; i < n; i++) {
		float mult = 1;
		for (int j = 0; j < i; j++) {
			mult *= (x - X[0]) / step - j;
		}

		// printf("dy[%d] = %.3f\tmult = %.3f\n", i, dy[i], mult);

		y += (dy[i] / Factorial(i)) * mult;
	}

	free(dy);

	return y;
}

int main()
{
	int n = 3;
	float Y[3] = { 1.7321, 2.0, 2.2361 };
	float X[3] = { 3.0, 4.0, 5.0 };
	
	// float x = 3.6;
	// printf("x = %.3f y = %.3f\n", x, P(X, Y, x, n));

	#if 1
	FILE *out = fopen("out.txt", "w");

	float x = 3.0;

	for (int i = 0; i < 20; i++) {
		fprintf(out, "%.3f %.3f\n", x, P(X, Y, x, n));
		x += 0.2;
	}

	fclose(out);
	#endif

	//gnuplot "scen.plt"

	return 0;
}